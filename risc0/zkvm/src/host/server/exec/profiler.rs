// Copyright 2025 RISC Zero, Inc.
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
//! guest. It counts the number of cycles spent in each unique stack
//! of call frames, allowing pprof to generate a flamegraph showing
//! where guest cycles are spent.
//!
//! Reported cycles are "user cycles". User cycles do not include
//! paging, and it does not include padding to extend the trace to
//! the nearest power of two.

mod inline;

use std::{
    cell::RefCell,
    collections::HashMap,
    fmt,
    fmt::Write,
    hash::{Hash, Hasher},
    rc::Rc,
};

use addr2line::{
    Context, LookupResult,
    fallible_iterator::FallibleIterator,
    gimli::{self, EndianRcSlice, RunTimeEndian},
};
use anyhow::{Result, anyhow};
use elf::{ElfBytes, abi::STT_FUNC, endian::LittleEndian};
use object::{Object as _, ObjectSegment as _};
use prost::Message;
use risc0_binfmt::ProgramBinary;
use risc0_zkvm_platform::memory::TEXT_START;
use rrs_lib::instruction_formats::{IType, JType, OPCODE_JAL, OPCODE_JALR};
use rustc_demangle::demangle;

use self::inline::{InlineFunction, InlineFunctionTable};
use super::proto;
use crate::{TraceCallback, TraceEvent};

type GimliReader = EndianRcSlice<RunTimeEndian>;
type ObjectContext = Context<GimliReader>;

const USER_END_ADDR: u32 = 0xc000_0000;

/// Operations effecting the function call stack.
#[derive(Debug)]
enum CallStackOp {
    Push,
    Pop,
    PopPush,
}

/// Partially decodes the given instruction to determine if it is a function
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

#[derive(Copy, Clone, Debug, PartialEq, Eq, Hash)]
enum ZkVmFunction {
    PageIn,
    PageOut,
}

impl fmt::Display for ZkVmFunction {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            Self::PageIn => write!(f, "[PageIn]"),
            Self::PageOut => write!(f, "[PageOut]"),
        }
    }
}

#[derive(Copy, Clone, Debug, PartialEq, Eq, Hash)]
enum FunctionStart {
    Real { pc: u32 },
    Inline(InlineFunction),
    ZkVm(ZkVmFunction),
}

impl FunctionStart {
    fn get_pc(&self) -> u32 {
        match self {
            Self::Real { pc } => *pc,
            Self::Inline(InlineFunction { low_pc, .. }) => *low_pc as u32,
            Self::ZkVm(_) => 0,
        }
    }
}

impl fmt::Display for FunctionStart {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            Self::Real { pc } => write!(f, "0x{pc:x}"),
            Self::Inline(InlineFunction {
                abstract_origin,
                low_pc,
                high_pc,
            }) => {
                write!(
                    f,
                    "[inline function: 0x{abstract_origin:x} (0x{low_pc:x}..0x{high_pc:x}]"
                )
            }
            Self::ZkVm(func) => write!(f, "{func}"),
        }
    }
}

/// Node in a tree tracking the call stacks and assigning cycles to stacks.
///
/// Each node represents a unique call-stack as defined by a list of return
/// addresses.
#[derive(Clone, Debug, Default)]
struct CallNode {
    /// Counter by program counter with the current call stack.
    pub(crate) counts: HashMap<FunctionStart, usize>,

    /// Nodes representing further calls from this context.
    pub(crate) calls: HashMap<FunctionStart, Rc<RefCell<CallNode>>>,
}

impl CallNode {
    /// Returns a formatted CallNode useful for debugging.
    fn fmt(&self, indent: usize, profiler: &Profiler) -> String {
        let mut output = String::new();
        let indent_str = " ".repeat(indent);

        writeln!(output, "{indent_str}Counts:").unwrap();
        for (key, value) in &self.counts {
            if let Some(frame) = &profiler.lookup_function_start(*key) {
                let name = &frame.name;
                writeln!(output, "{indent_str}  {name} ({key}): {value}").unwrap();
            }
        }

        writeln!(output, "{indent_str}Calls:").unwrap();
        for (key, node_ref) in &self.calls {
            let node = node_ref.borrow();
            writeln!(output, "{indent_str}  {key} ({key}):").unwrap();
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
    cycle: u64,

    // Pop stack
    pop_stack: Vec<u32>,

    // Path of the call stack as a series of program counters,
    // representing the journey to the current node from the root
    call_stack_path: Vec<FunctionStart>,

    // Root of the tree used to store samples attributable to a call stack.
    root: Rc<RefCell<CallNode>>,

    // Current CallNode in the stack
    current_node: Option<Rc<RefCell<CallNode>>>,

    // Current CallNode key in the stack
    current_key: Option<FunctionStart>,

    ctx: ObjectContext,

    profile: ProfileBuilder,
}

/// Represents a frame.
#[derive(Clone, Debug, PartialEq, Eq)]
pub struct Frame {
    /// Function name
    pub name: String,

    /// Line number
    pub lineno: i64,

    /// Filename where this function is defined
    pub filename: String,
}

fn decode_frame(fr: addr2line::Frame<GimliReader>) -> Option<Frame> {
    Some(Frame {
        name: fr.function.as_ref()?.demangle().ok()?.to_string(),
        lineno: fr.location.as_ref()?.line? as i64,
        filename: fr.location.as_ref()?.file?.to_string(),
    })
}

fn lookup_pc_in_dwarf(pc: u32, ctx: &ObjectContext) -> Vec<Frame> {
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

fn demangle_name(name: String) -> String {
    if let Some(index) = name.rfind("::") {
        let truncated = &name[0..index];
        truncated.to_string()
    } else {
        name
    }
}

fn load_dwarf<'data, O: object::Object<'data>>(
    file: &O,
) -> Result<gimli::Dwarf<gimli::EndianRcSlice<gimli::RunTimeEndian>>> {
    let endian = if file.is_little_endian() {
        gimli::RunTimeEndian::Little
    } else {
        gimli::RunTimeEndian::Big
    };

    fn load_section<'data, O, Endian>(
        id: gimli::SectionId,
        file: &O,
        endian: Endian,
    ) -> std::result::Result<gimli::EndianRcSlice<Endian>, gimli::Error>
    where
        O: object::Object<'data>,
        Endian: gimli::Endianity,
    {
        use object::ObjectSection as _;

        let data = file
            .section_by_name(id.name())
            .and_then(|section| section.uncompressed_data().ok())
            .unwrap_or(std::borrow::Cow::Borrowed(&[]));
        Ok(gimli::EndianRcSlice::new(Rc::from(&*data), endian))
    }

    Ok(gimli::Dwarf::load(|id| load_section(id, file, endian))?)
}

pub fn read_enable_inline_functions_env_var() -> bool {
    std::env::var("RISC0_PPROF_ENABLE_INLINE_FUNCTIONS")
        .ok()
        .map(|x| x.to_lowercase())
        .filter(|x| x == "1" || x == "true" || x == "yes")
        .is_some()
}

impl Profiler {
    /// Return a new profile from the given RISC-V ELF.
    pub fn new(
        binary: &ProgramBinary,
        filename: Option<&str>,
        enable_inline_functions: bool,
    ) -> Result<Self> {
        let file = object::File::parse(binary.user_elf)?;
        let dwarf = load_dwarf(&file)?;

        let inline_function_table_result = if enable_inline_functions {
            InlineFunctionTable::build_from_dwarf(&dwarf)
        } else {
            Err(anyhow!("inline functions disabled"))
        };

        let ctx = ObjectContext::from_dwarf(dwarf)?;
        let root = Rc::new(RefCell::new(CallNode::default()));
        let mut profiler = Profiler {
            pc: u32::MAX,
            insn: 0,
            cycle: 0,
            pop_stack: Vec::new(),
            root: Rc::clone(&root),
            current_node: Some(root),
            current_key: None,
            call_stack_path: Vec::new(),
            ctx,
            profile: ProfileBuilder::new(),
        };

        // Save the main binary name
        let bin_name = profiler.profile.get_string(filename.unwrap_or("unknown"));
        for segment in file.segments() {
            if segment.address() == TEXT_START as u64 {
                profiler.profile.profile.mapping.push(proto::Mapping {
                    id: 1,
                    memory_start: segment.address(),
                    memory_limit: segment.address() + segment.size(),
                    file_offset: segment.file_range().0,
                    filename: bin_name,
                    has_functions: true,
                    has_filenames: filename.is_some(),
                    has_line_numbers: true,
                    has_inline_frames: true,
                    ..Default::default()
                });
            }
        }

        profiler.profile.symbol_table = build_symbol_table(binary.user_elf)?;
        match inline_function_table_result {
            Ok(inline_function_table) => {
                profiler.profile.inline_function_table = inline_function_table
            }
            Err(error) => {
                if enable_inline_functions {
                    tracing::warn!(
                        "Error decoding DWARF data, inline functions not available: {error}"
                    )
                }
            }
        }

        Ok(profiler)
    }

    fn lookup_function_start(&self, f: FunctionStart) -> Option<Frame> {
        match f {
            FunctionStart::Real { pc } => self.lookup_pc(pc),
            FunctionStart::Inline(InlineFunction {
                abstract_origin, ..
            }) => self.lookup_inline_function(abstract_origin as u32),
            FunctionStart::ZkVm(f) => Some(Frame {
                name: f.to_string(),
                lineno: 0,
                filename: String::default(),
            }),
        }
    }

    fn lookup_pc(&self, pc: u32) -> Option<Frame> {
        let dwarf_frames = lookup_pc_in_dwarf(pc, &self.ctx);
        let symbol = self.profile.symbol_table.get(&(pc as u64)).cloned();

        if !dwarf_frames.is_empty() {
            Some(dwarf_frames.last().unwrap().clone())
        } else {
            symbol.map(|symbol| Frame {
                name: demangle_name(symbol).replace('&', ""),
                lineno: 0,
                filename: "unknown".into(),
            })
        }
    }

    fn lookup_inline_function(&self, abstract_origin: u32) -> Option<Frame> {
        Some(
            self.profile
                .inline_function_table
                .frames
                .get(&(abstract_origin as u64))?
                .clone(),
        )
    }

    /// Walk the profile tree rooted at node_ref, adding all call stacks in the profile to the
    /// profile under construction. All call stacks encountered build on top of the base_stack.
    fn walk_stacks(&mut self, node_ref: Rc<RefCell<CallNode>>, base_stack: Vec<Frame>) {
        let node = node_ref.borrow();
        for (function_start, count) in &node.counts {
            let mut new_stack = base_stack.clone();
            if let Some(frame) = self.lookup_function_start(*function_start) {
                new_stack.push(frame);
            }

            let pc = function_start.get_pc();

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

            if !sample.location_id.is_empty() && *count > 0 {
                self.profile.add_sample(sample);
            }

            if let Some(next_node_ref) = node.calls.get(function_start) {
                self.walk_stacks(next_node_ref.clone(), new_stack);
            }
        }
    }

    /// Count and save the profiling samples, write the results to `output_path`.
    #[cfg(test)]
    pub(crate) fn finalize(mut self) -> ProfileBuilder {
        let root_ref = Rc::clone(&self.root);
        tracing::debug!("{}", self.root.borrow().fmt(0, &self));
        self.walk_stacks(root_ref, Vec::new());
        self.profile
    }

    /// Count and save the profiling samples, consuming the profiler and
    /// returning the compiled profile protobuf, encoded as bytes.
    pub fn finalize_to_vec(&mut self) -> Vec<u8> {
        let root_ref = Rc::clone(&self.root);
        tracing::debug!("{}", self.root.borrow().fmt(0, self));
        self.walk_stacks(root_ref, Vec::new());
        self.profile.profile.encode_to_vec()
    }

    fn add_zkvm_frame(&mut self, function: ZkVmFunction, cycles: u64) {
        if !self.call_stack_path.is_empty() {
            let current_node = self
                .current_node
                .as_ref()
                .expect("current_node should always be Some after initialization");
            let current_key = self
                .current_key
                .expect("current_key should always be Some after initialization");

            let node = current_node
                .borrow_mut()
                .calls
                .entry(current_key)
                .or_insert_with(|| Rc::new(RefCell::new(CallNode::default())))
                .clone();

            node.borrow_mut()
                .counts
                .entry(FunctionStart::ZkVm(function))
                .and_modify(|e| *e += cycles as usize)
                .or_insert(cycles as usize);
        }
    }

    fn add_cycles_to_current_stack(&mut self, cycles: u64) {
        if !self.call_stack_path.is_empty() {
            let current_node = self
                .current_node
                .as_ref()
                .expect("current_node should always be Some after initialization");
            let mut current_node_borrowed = current_node.borrow_mut();
            let current_key = self
                .current_key
                .expect("current_key should always be Some after initialization");
            current_node_borrowed
                .counts
                .entry(current_key)
                .and_modify(|e| *e += cycles as usize)
                .or_insert(cycles as usize);
        }
    }

    fn handle_function_call(
        &mut self,
        op: CallStackOp,
        pc: u32,
        orig_pc: u32,
        update_stack: &mut bool,
    ) -> Result<(), anyhow::Error> {
        match op {
            CallStackOp::Push => {
                // Sometimes we confuse a jump and a function call. See if we are jumping to the
                // start of a function or not to disambiguate.
                if self.profile.symbol_table.contains_key(&(pc as u64)) {
                    self.call_stack_path.push(FunctionStart::Real { pc });
                    self.pop_stack.push(orig_pc);
                    *update_stack = true;
                }
            }
            CallStackOp::Pop => loop {
                while matches!(self.call_stack_path.last(), Some(FunctionStart::Inline(_))) {
                    self.call_stack_path.pop();
                }

                if self.call_stack_path.pop().is_none() {
                    break;
                }
                let Some(popped) = self.pop_stack.pop() else {
                    break;
                };
                *update_stack = true;
                if popped == pc - 4 {
                    break;
                }
            },
            CallStackOp::PopPush => {
                loop {
                    while matches!(self.call_stack_path.last(), Some(FunctionStart::Inline(_))) {
                        self.call_stack_path.pop();
                    }

                    if self.call_stack_path.pop().is_none() {
                        break;
                    }

                    let Some(popped) = self.pop_stack.pop() else {
                        break;
                    };
                    if popped == pc - 4 {
                        break;
                    }
                }
                self.call_stack_path.push(FunctionStart::Real { pc });
                self.pop_stack.push(orig_pc);
                *update_stack = true;
            }
        }
        Ok(())
    }

    fn handle_inline_functions(&mut self, pc: u32, update_stack: &mut bool) {
        loop {
            let Some(FunctionStart::Inline(InlineFunction {
                low_pc, high_pc, ..
            })) = self.call_stack_path.last()
            else {
                break;
            };

            if !(*low_pc..*high_pc).contains(&(pc as u64)) {
                self.call_stack_path.pop();
                *update_stack = true;
                continue;
            }
            break;
        }

        if let Some(inline_functions) = self.profile.inline_function_table.starts.get(&(pc as u64))
        {
            for func in inline_functions {
                let to_add = FunctionStart::Inline(*func);
                if self.call_stack_path.last() != Some(&to_add) {
                    self.call_stack_path.push(to_add);
                }
            }
            *update_stack = true;
        }
    }

    fn update_stack(&mut self, pc: u32) {
        tracing::debug!(
            "updating stack pc={pc:x}, stack={:?}",
            &self.call_stack_path
        );
        let mut curr_node = Rc::clone(&self.root);
        for (i, &call_stack_key) in self.call_stack_path.iter().enumerate() {
            if i == self.call_stack_path.len() - 1 {
                self.current_node = Some(Rc::clone(&curr_node));
                self.current_key = Some(call_stack_key);
            }
            let next_node = {
                let mut curr_node_borrowed = curr_node.borrow_mut();
                curr_node_borrowed.counts.entry(call_stack_key).or_default();
                curr_node_borrowed
                    .calls
                    .entry(call_stack_key)
                    .or_insert_with(|| Rc::new(RefCell::new(CallNode::default())))
                    .clone()
            };
            curr_node = next_node;
        }
    }
}

fn build_symbol_table(elf_data: &[u8]) -> Result<HashMap<u64, String>> {
    let mut symbol_table = HashMap::new();

    let elf = ElfBytes::<LittleEndian>::minimal_parse(elf_data)?;
    if let Some((symtab, strtab)) = elf.symbol_table()? {
        for sym in symtab {
            if sym.st_symtype() == STT_FUNC {
                let name = strtab.get(sym.st_name as usize)?;
                symbol_table.insert(sym.st_value, demangle(name).to_string());
            }
        }
    }

    Ok(symbol_table)
}

impl TraceCallback for Profiler {
    /// Interpret the provided trace event and add it to the ongoing profile of execution.
    fn trace_callback(&mut self, event: TraceEvent) -> anyhow::Result<()> {
        match event {
            TraceEvent::InstructionStart { cycle, pc, insn } => {
                let cycles = cycle - self.cycle;
                let orig_pc = self.pc;
                let orig_insn = self.insn;

                self.add_cycles_to_current_stack(cycles);

                if pc <= USER_END_ADDR {
                    let mut update_stack = false;

                    if let Some(op) = extract_call_stack_op(orig_insn) {
                        self.handle_function_call(op, pc, orig_pc, &mut update_stack)?;
                    }

                    self.handle_inline_functions(pc, &mut update_stack);

                    if update_stack {
                        self.update_stack(pc);
                    }
                }

                // Update pc, insn, and cycle
                self.pc = pc;
                self.insn = insn;
                self.cycle = cycle;
            }
            TraceEvent::PageIn { cycles } => self.add_zkvm_frame(ZkVmFunction::PageIn, cycles),
            TraceEvent::PageOut { cycles } => self.add_zkvm_frame(ZkVmFunction::PageOut, cycles),
            TraceEvent::RegisterSet { .. } => (),
            TraceEvent::MemorySet { .. } => (),
            _ => {
                tracing::trace!("ignoring unknown event {event:?}");
            }
        }
        Ok(())
    }
}

impl TraceCallback for &mut Profiler {
    /// Interpret the provided trace event and add it to the ongoing profile of execution.
    fn trace_callback(&mut self, event: TraceEvent) -> anyhow::Result<()> {
        (*self).trace_callback(event)
    }
}

pub(crate) struct ProfileBuilder {
    strings: HashMap<String, i64>,
    functions: HashMap<(String, String), u64>,
    locations: HashMap<LocationKey, u64>,
    symbol_table: HashMap<u64, String>,
    inline_function_table: InlineFunctionTable,
    profile: proto::Profile,
}

impl ProfileBuilder {
    fn new() -> Self {
        let mut builder = Self {
            strings: HashMap::new(),
            functions: HashMap::new(),
            locations: HashMap::new(),
            profile: Default::default(),
            symbol_table: Default::default(),
            inline_function_table: Default::default(),
        };

        // First string must always be the empty string
        assert_eq!(0, builder.get_string(""));

        // Set up defaults for us
        let sample_type = proto::ValueType {
            r#type: builder.get_string("cycles"),
            unit: builder.get_string("count"),
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

    /// Dereferences strings, etc. in the protobuf for testing purposes.
    /// Returns a tuple of (frames, program counter, cycles)
    #[cfg(test)]
    pub(crate) fn iter(&self) -> impl Iterator<Item = TestSample> + '_ {
        self.profile.sample.iter().map(move |sample| TestSample {
            frames: sample
                .location_id
                .iter()
                .map(|id| {
                    let loc = &self.profile.location[*id as usize - 1];
                    let line = &loc.line[0];
                    let func = &self.profile.function[line.function_id as usize - 1];
                    FrameWithAddress {
                        frame: Frame {
                            name: self.profile.string_table[func.name as usize].clone(),
                            lineno: line.line,
                            filename: self.profile.string_table[func.filename as usize].clone(),
                        },
                        address: loc.address as usize,
                    }
                })
                .collect(),
            count: sample.value[0] as usize,
        })
    }
}

#[cfg(test)]
#[derive(Debug)]
pub struct FrameWithAddress {
    pub frame: Frame,
    pub address: usize,
}

/// A profile sample that has been converted into a format easy for testing
#[cfg(test)]
#[derive(Debug)]
pub struct TestSample {
    pub frames: Vec<FrameWithAddress>,
    pub count: usize,
}

struct LocationKey {
    address: u64,
    lines: Vec<proto::Line>,
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
