// Copyright 2023 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//! Support for profiling the guest.
//!
//! This counts cycles spent at each location when executing the
//! guest.  It does not trace full stack traces, but only provides the
//! top level stack frame.  (More than one stack frame may show up
//! in the case of inlined functions).

use std::{
    cell::RefCell,
    collections::HashMap,
    fmt::Write,
    hash::{Hash, Hasher},
    rc::Rc,
};

use addr2line::{fallible_iterator::FallibleIterator, Context, LookupResult};
use anyhow::{anyhow, Result};
use gimli::{EndianRcSlice, RunTimeEndian};
use goblin::elf::Elf;
use object::{read::File, Object, ObjectSegment};
use prost::Message;
use rrs_lib::instruction_formats::{IType, JType, OPCODE_JAL, OPCODE_JALR};
use rustc_demangle::demangle;

use self::proto::Line;
use crate::TraceEvent;

mod proto {
    // Generated proto interface.
    include!(concat!(env!("OUT_DIR"), "/perftools.profiles.rs"));
}

/// Operations effecting the function call stack.
#[derive(Debug)]
enum CallStackOp {
    Push,
    Pop,
    PopPush,
}

/// Partially decodes the given instruction to determine if it is a functon
/// call, or the return from a function call.
///
/// Uses the rules in section 2.5 as guidelines for operations on the return
/// address stack to determine whether a given JAL(R) instruction is a call, a
/// return, or neither.
///
/// [RISC-V ISA manual]: https://riscv.org/wp-content/uploads/2017/05/riscv-spec-v2.2.pdf
fn extract_call_stack_op(insn: u32) -> Option<CallStackOp> {
    let opcode: u32 = insn & 0x7f;

    match opcode {
        OPCODE_JAL => {
            let decode = JType::new(insn);
            if (decode.rd | 0x04) == 0x5 {
                Some(CallStackOp::Push)
            } else {
                None
            }
        }
        OPCODE_JALR => {
            let decode = IType::new(insn);
            let rd_link = (decode.rd | 0x04) == 0x5;
            let rs1_link = (decode.rs1 | 0x04) == 0x5;
            match (rd_link, rs1_link) {
                (false, false) => Some(CallStackOp::Push), // Custom push
                (false, true) => Some(CallStackOp::Pop),
                (true, false) => Some(CallStackOp::Push),
                (true, true) if decode.rd != decode.rs1 => Some(CallStackOp::PopPush),
                (true, true) => Some(CallStackOp::Push),
            }
        }
        _ => None,
    }
}

/// Node in a tree tracking the call stacks and assigning cycles to stacks.
///
/// Each node represents a unique call-stack as defined by a list of return
/// addresses.
#[derive(Clone, Debug, Default)]
struct CallNode {
    /// Counter by program counter with the current call stack.
    pub(crate) counts: HashMap<u32, usize>,

    /// Nodes representing further calls from this context.
    pub(crate) calls: HashMap<u32, Rc<RefCell<CallNode>>>,
}

impl CallNode {
    /// Returns a formatted CallNode useful for debugging.
    fn fmt(&self, indent: usize, profiler: &Profiler) -> String {
        let mut output = String::new();
        let indent_str = " ".repeat(indent);

        writeln!(output, "{}Counts:", indent_str).unwrap();
        for (key, value) in &self.counts {
            let frames = &profiler.lookup_pc(*key as u64);
            if !frames.is_empty() {
                let name = &frames[0].name;
                writeln!(output, "{}  {} ({}): {}", indent_str, name, key, value).unwrap();
            }
        }

        writeln!(output, "{}Calls:", indent_str).unwrap();
        for (key, node_ref) in &self.calls {
            let node = node_ref.borrow();
            writeln!(output, "{}  {} ({}):", indent_str, key, key).unwrap();
            output.push_str(&node.fmt(indent + 2, profiler));
        }

        output
    }
}

/// Manages profiling state
pub struct Profiler {
    // Current program counter
    pc: u32,

    // Instruction at self.pc
    insn: u32,

    // Cycle count when the last instruction started
    cycle: u32,

    // Pop stack
    pop_stack: Vec<u32>,

    // Path of the call stack as a series of program counters,
    // representing the journey to the current node from the root
    call_stack_path: Vec<u32>,

    // Root of the tree used to store samples attributable to a call stack.
    root: Rc<RefCell<CallNode>>,

    // Current CallNode in the stack
    current_node: Option<Rc<RefCell<CallNode>>>,

    // Current CallNode key in the stack
    current_key: u32,

    ctx: Context<EndianRcSlice<RunTimeEndian>>,

    profile: ProfileBuilder,
}

/// Represents a frame. Prefer to export the whole profiler proto using
/// profiler.as_protobuf().
#[derive(Clone, Debug)]
pub struct Frame {
    /// Function name
    pub name: String,

    /// Line number
    pub lineno: i64,

    /// Filename where this function is defined
    pub filename: String,
}

fn decode_frame(fr: addr2line::Frame<EndianRcSlice<RunTimeEndian>>) -> Option<Frame> {
    Some(Frame {
        name: fr.function.as_ref()?.demangle().ok()?.to_string(),
        lineno: fr.location.as_ref()?.line? as i64,
        filename: fr.location.as_ref()?.file?.to_string(),
    })
}

fn lookup_pc(pc: u32, ctx: &Context<EndianRcSlice<RunTimeEndian>>) -> Vec<Frame> {
    let frames = match ctx.find_frames(pc as u64) {
        LookupResult::Output(result) => result.unwrap(),
        LookupResult::Load {
            load: _,
            continuation: _,
        } => unimplemented!(),
    };
    frames
        .filter_map(|frame| Ok(decode_frame(frame)))
        .collect()
        .unwrap()
}

fn demangle_name(s: String) -> String {
    if let Some(index) = s.rfind("::") {
        let truncated = &s[0..index];
        return truncated.to_string();
    } else {
        return s;
    }
}

impl Profiler {
    /// Return a new profile from the given RISCV ELF.
    pub fn new(filename: &str, elf_data: &[u8]) -> Result<Self> {
        let file = File::parse(elf_data)?;
        let ctx = Context::new(&file)?;
        let root = Rc::new(RefCell::new(CallNode::default()));
        let mut profiler = Profiler {
            pc: u32::MAX,
            insn: 0,
            cycle: 0,
            pop_stack: Vec::new(),
            root: Rc::clone(&root),
            current_node: Some(root),
            current_key: 0,
            call_stack_path: Vec::new(),
            ctx,
            profile: ProfileBuilder::new(),
        };

        // Save the main binary name
        let bin_name = profiler.profile.get_string(filename);
        for segment in file.segments() {
            if segment.address() == risc0_zkvm_platform::memory::TEXT_START as u64 {
                profiler.profile.profile.mapping.push(proto::Mapping {
                    id: 1,
                    memory_start: segment.address(),
                    memory_limit: segment.address() + segment.size(),
                    file_offset: segment.file_range().0,
                    filename: bin_name,
                    has_functions: true,
                    has_filenames: true,
                    has_line_numbers: true,
                    has_inline_frames: true,
                    ..Default::default()
                });
            }
        }

        let binary = Elf::parse(&elf_data)?;

        for sym in &binary.syms {
            // Check if symbol is a function
            if sym.st_type() == goblin::elf::sym::STT_FUNC {
                let name = binary.strtab.get_at(sym.st_name).unwrap();
                profiler
                    .profile
                    .function_lookup
                    .insert(sym.st_value, demangle(name).to_string());
            }
        }

        Ok(profiler)
    }

    /// Dereferences strings, etc. in the protobuf for testing purposes.
    /// Returns a tuple of (frames, program counter, cycles)
    pub fn iter(&self) -> impl Iterator<Item = (Vec<Frame>, usize, usize)> + '_ {
        self.profile.iter()
    }

    /// Returns the frames name at the given pc.
    pub fn lookup_pc(&self, pc: u64) -> Vec<Frame> {
        let frames = if let Some(s) = self.profile.function_lookup.get(&pc).as_deref().cloned() {
            let mut dwarf_frames = lookup_pc(pc as u32, &self.ctx);
            dwarf_frames.reverse();
            let name = demangle_name(s).replace("&", "");
            let mut lineno: i64 = 0;
            let mut filename = "unknown".to_string();
            if dwarf_frames.len() > 0 {
                let debug_frame = &dwarf_frames[0];
                let debug_name = debug_frame.name.replace("&", "");
                if name == debug_name {
                    lineno = debug_frame.lineno;
                    filename = debug_frame.filename.clone();
                }
            }
            let mut frames = vec![Frame {
                name,
                lineno,
                filename,
            }];
            if dwarf_frames.len() > 1 {
                for fr in dwarf_frames[1..].iter() {
                    frames.push(fr.clone())
                }
            }
            frames
        } else {
            // only used when debug is set. However, it currently misinterprets when no_std
            // lookup_pc(pc as u32, &self.ctx)
            vec![]
        };
        frames
    }

    /// Returns a callback to populate this profiler, suitable for
    /// passing to ProverOpts::with_trace_callback.
    pub fn make_trace_callback(&mut self) -> impl FnMut(TraceEvent) -> anyhow::Result<()> + '_ {
        |event| {
            match event {
                TraceEvent::InstructionStart { cycle, pc, insn } => {
                    let cycles = cycle - self.cycle;
                    let orig_pc = self.pc;
                    let orig_insn = self.insn;

                    if self.call_stack_path.len() > 0 {
                        let current_node = self
                            .current_node
                            .as_ref()
                            .expect("current_node should always be Some after initialization");
                        let mut current_node_borrowed = current_node.borrow_mut();
                        current_node_borrowed
                            .counts
                            .entry(self.current_key)
                            .and_modify(|e| *e += cycles as usize)
                            .or_insert(cycles as usize);
                    }

                    if let Some(op) = extract_call_stack_op(orig_insn) {
                        match op {
                            CallStackOp::Push => {
                                self.call_stack_path.push(pc);
                                self.pop_stack.push(orig_pc);
                            }
                            CallStackOp::Pop => loop {
                                self.call_stack_path.pop().ok_or_else(|| {
                                    anyhow!("attempted to follow a return with an empty call stack")
                                })?;
                                let popped = self.pop_stack.pop().ok_or_else(|| {
                                    anyhow!("attempted to follow a return with an empty call stack")
                                })?;
                                if pc - 4 == popped {
                                    break;
                                }
                            },
                            CallStackOp::PopPush => {
                                loop {
                                    self.call_stack_path.pop().ok_or_else(|| {
                                        anyhow!(
                                            "attempted to follow a return with an empty call stack"
                                        )
                                    })?;
                                    let popped = self.pop_stack.pop().ok_or_else(|| {
                                        anyhow!(
                                            "attempted to follow a return with an empty call stack"
                                        )
                                    })?;
                                    if pc - 4 == popped {
                                        break;
                                    }
                                }
                                self.call_stack_path.push(pc);
                                self.pop_stack.push(orig_pc);
                            }
                        }

                        let mut curr_node = Rc::clone(&self.root);
                        for (i, &call_stack_key) in self.call_stack_path.iter().enumerate() {
                            if i == self.call_stack_path.len() - 1 {
                                self.current_node = Some(Rc::clone(&curr_node));
                                self.current_key =
                                    *self.call_stack_path.last().ok_or_else(|| {
                                        anyhow!("attempted to access an empty call stack")
                                    })?;
                            }
                            let next_node = {
                                let mut curr_node_borrowed = curr_node.borrow_mut();
                                curr_node_borrowed
                                    .calls
                                    .entry(call_stack_key)
                                    .or_insert_with(|| Rc::new(RefCell::new(CallNode::default())))
                                    .clone()
                            };
                            curr_node = next_node;
                        }
                    }

                    // Update pc, insn, and cycle
                    self.pc = pc;
                    self.insn = insn;
                    self.cycle = cycle;
                }
                _ => (),
            }
            Ok(())
        }
    }

    fn walk_stack(&mut self, node_ref: Rc<RefCell<CallNode>>, stack: Vec<Frame>) {
        let node = node_ref.borrow();
        for (&pc, count) in &node.counts {
            let mut new_stack = stack.clone();
            let frames = self.lookup_pc(pc.into());
            if !frames.is_empty() {
                new_stack.extend(frames);
            }

            let location_ids: Vec<_> = new_stack
                .iter()
                .rev()
                .map(|fr| {
                    let func_id = self.profile.get_function(&fr.name, &fr.filename);
                    let loc = proto::Location {
                        address: pc as u64,
                        line: vec![proto::Line {
                            function_id: func_id,
                            line: fr.lineno,
                        }],
                        ..Default::default()
                    };
                    self.profile.get_location(loc)
                })
                .collect();
            let sample = proto::Sample {
                location_id: location_ids,
                value: vec![*count as i64],
                ..Default::default()
            };

            if !sample.location_id.is_empty() {
                self.profile.add_sample(sample);
            }

            if let Some(next_node_ref) = node.calls.get(&pc) {
                self.walk_stack(next_node_ref.clone(), new_stack);
            }
        }
    }

    /// Count and save the profiling samples, consuming the profiler and
    /// returning the compiled profile protobuf.
    pub fn finalize(&mut self) {
        let root_ref = Rc::clone(&self.root);
        log::debug!("{}", self.root.borrow().fmt(0, &self));
        self.walk_stack(root_ref, Vec::new());
    }

    /// Returns the result of this profiling run as a protobuf.
    pub fn as_protobuf(&self) -> &proto::Profile {
        assert!(
            !self.profile.profile.sample.is_empty(),
            "Call finalize() first to generate the protobuf"
        );
        &self.profile.profile
    }

    /// Returns the result of this profiling run, encoded and ready for writing
    /// to a file.
    pub fn encode_to_vec(&mut self) -> Vec<u8> {
        self.as_protobuf().encode_to_vec()
    }
}

struct ProfileBuilder {
    strings: HashMap<String, i64>,

    functions: HashMap<(String, String), u64>,

    locations: HashMap<LocationKey, u64>,

    function_lookup: HashMap<u64, String>,

    profile: proto::Profile,
}

impl ProfileBuilder {
    fn new() -> Self {
        let mut builder = Self {
            strings: HashMap::new(),
            functions: HashMap::new(),
            locations: HashMap::new(),
            profile: Default::default(),
            function_lookup: Default::default(),
        };

        // First string must always be the empty string
        assert_eq!(0, builder.get_string(""));

        // Set up defaults for us
        let sample_type = proto::ValueType {
            r#type: builder.get_string("cycles"),
            unit: builder.get_string("count"),
            ..Default::default()
        };
        builder.profile.sample_type.push(sample_type);

        builder
    }

    fn get_location(&mut self, mut loc: proto::Location) -> u64 {
        // Check if a Location with the same characteristics already exists
        let key = LocationKey {
            address: loc.address,
            lines: loc.line.clone(),
        };
        if let Some(&id) = self.locations.get(&key) {
            return id;
        }

        let id = self.profile.location.len() as u64 + 1;
        loc.id = id;
        if !self.profile.mapping.is_empty() {
            loc.mapping_id = 1;
        }
        self.profile.location.push(loc);
        self.locations.insert(key, id);
        id
    }

    fn get_function(&mut self, name: &str, filename: &str) -> u64 {
        let key = (name.to_string(), filename.to_string());
        if let Some(&id) = self.functions.get(&key) {
            return id;
        }

        let id = self.profile.function.len() as u64 + 1;
        let name = self.get_string(name);
        let filename = self.get_string(filename);
        self.profile.function.push(proto::Function {
            id,
            name,
            filename,
            ..Default::default()
        });
        self.functions.insert(key, id);
        id
    }

    // Adds a string to the string table
    fn get_string(&mut self, s: &str) -> i64 {
        *self.strings.entry(s.to_string()).or_insert_with(|| {
            let idx = self.profile.string_table.len() as i64;
            self.profile.string_table.push(s.to_string());
            idx
        })
    }

    fn add_sample(&mut self, sample: proto::Sample) {
        self.profile.sample.push(sample)
    }

    fn iter(&self) -> impl Iterator<Item = (Vec<Frame>, usize, usize)> + '_ {
        self.profile.sample.iter().flat_map(move |sample| {
            sample.location_id.iter().map(move |id| {
                let loc = &self.profile.location[*id as usize - 1];
                (
                    loc.line
                        .iter()
                        .map(|line| {
                            let func = &self.profile.function[line.function_id as usize - 1];
                            Frame {
                                name: self.profile.string_table[func.name as usize].clone(),
                                lineno: line.line,
                                filename: self.profile.string_table[func.filename as usize].clone(),
                            }
                        })
                        .collect(),
                    loc.address as usize,
                    sample.value[0] as usize,
                )
            })
        })
    }
}

struct LocationKey {
    address: u64,
    lines: Vec<Line>,
}

impl Hash for LocationKey {
    fn hash<H: Hasher>(&self, state: &mut H) {
        self.address.hash(state);
        for line in &self.lines {
            line.function_id.hash(state);
            line.line.hash(state);
        }
    }
}

impl PartialEq for LocationKey {
    fn eq(&self, other: &Self) -> bool {
        self.address == other.address && self.lines == other.lines
    }
}

impl Eq for LocationKey {}
