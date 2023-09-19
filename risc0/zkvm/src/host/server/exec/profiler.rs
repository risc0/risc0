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

// TODO:
//
//   * Count the full stack instead of the top frame; the "gimli"
//   crate's UnwindSection and Evaluation should help us do this
//
//  * Demangle symbols

use std::collections::HashMap;
use std::hash::{Hash, Hasher};

use addr2line::{
    fallible_iterator::FallibleIterator,
    object::{read::File, Object, ObjectSegment},
    Context, LookupResult,
};
use anyhow::{anyhow, Result};
use gimli::{EndianRcSlice, RunTimeEndian};
use prost::Message;
use rrs_lib::instruction_formats::{IType, JType, OPCODE_JAL, OPCODE_JALR};

use crate::TraceEvent;

use self::proto::Line;

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
                (false, false) => None,
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
    // TODO(victor): Is this horribly inefficient?
    pub(crate) counts: HashMap<u32, usize>,

    /// Nodes representing further calls from this context.
    pub(crate) calls: HashMap<u32, CallNode>,
}

/// Manages profiling state
pub struct Profiler {
    // Current program counter
    pc: u32,

    // Instruction at self.pc
    insn: u32,

    // Cycle count when the last instruction started
    cycle: u32,

    // Path of the call stack as a series of program counters,
    // representing the journey to the current node from the root
    call_stack_path: Vec<u32>,

    // Root of the tree used to store samples attributable to a call stack.
    root: CallNode,

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

impl Profiler {
    /// Return a new profile from the given RISCV ELF.
    pub fn new(filename: &str, elf_data: &[u8]) -> Result<Self> {
        let file = File::parse(elf_data)?;
        let ctx = Context::new(&file)?;
        let mut profiler = Profiler {
            pc: u32::MAX,
            insn: 0,
            cycle: 0,
            root: CallNode::default(),
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
                    ..Default::default()
                });
            }
        }

        Ok(profiler)
    }

    /// Dereferences strings, etc. in the protobuf for testing purposes.
    /// Returns a tuple of (frames, program counter, cycles)
    pub fn iter(&self) -> impl Iterator<Item = (Vec<Frame>, usize, usize)> + '_ {
        self.profile.iter()
    }

    /// Returns a callback to populate this profiler, suitable for
    /// passing to ProverOpts::with_trace_callback.
    pub fn make_trace_callback(&mut self) -> impl FnMut(TraceEvent) -> anyhow::Result<()> + '_ {
        move |event| {
            match event {
                TraceEvent::Instruction { cycle, pc, insn } => {
                    let cycles = cycle - self.cycle;
                    let orig_pc = self.pc;
                    let orig_insn = self.insn;

                    // We get a mutable reference to the deepest CallNode by following the call_stack_path
                    let mut curr_node = &mut self.root;
                    for &key in &self.call_stack_path {
                        curr_node = curr_node.calls.entry(key).or_insert_with(CallNode::default);
                    }

                    curr_node
                        .counts
                        .entry(orig_pc)
                        .and_modify(|e| *e += cycles as usize)
                        .or_insert(cycles as usize);

                    if let Some(op) = extract_call_stack_op(orig_insn) {
                        match op {
                            CallStackOp::Push => {
                                self.call_stack_path.push(orig_pc);
                            }
                            CallStackOp::Pop => {
                                self.call_stack_path.pop().ok_or_else(|| {
                                    anyhow!("attempted to follow a return with an empty call stack")
                                })?;
                            }
                            CallStackOp::PopPush => {
                                self.call_stack_path.pop().ok_or_else(|| {
                                    anyhow!("attempted to follow a return with an empty call stack")
                                })?;
                                self.call_stack_path.push(orig_pc);
                            }
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

    fn walk_stack(&mut self, node: &CallNode, stack: Vec<Frame>) {
        for (&pc, count) in &node.counts {
            let mut new_stack = stack.clone();

            let frames = lookup_pc(pc, &self.ctx);
            if !frames.is_empty() {
                new_stack.extend(frames);
            }

            let mut location_ids: Vec<_> = new_stack
                .iter()
                .map(|fr| {
                    let func_id = self.profile.get_function(&fr.name, &fr.filename);
                    // println!("{} - {} - {} - {}", pc, count, func_id, fr.name);
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
            location_ids.reverse();
            let sample = proto::Sample {
                location_id: location_ids,
                value: vec![*count as i64],
                ..Default::default()
            };
            // println!("{:?}", sample);

            self.profile.add_sample(sample);

            if let Some(next_node) = node.calls.get(&pc) {
                self.walk_stack(next_node, new_stack);
            }
        }
    }

    /// Count and save the profiling samples, consuming the profiler and
    /// returning the compiled profile protobuf.
    pub fn finalize(&mut self) {
        let root = self.root.clone();
        self.walk_stack(&root, Vec::new());
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

    profile: proto::Profile,
}

impl ProfileBuilder {
    fn new() -> Self {
        let mut builder = Self {
            strings: HashMap::new(),
            functions: HashMap::new(),
            locations: HashMap::new(),
            profile: Default::default(),
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
            loc.mapping_id = 0; // TODO: check this
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
        self.profile.sample.iter().map(|sample| {
            let loc = &self.profile.location[sample.location_id[0] as usize - 1];
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
