// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use std::{cell::RefCell, collections::BTreeSet, io::Read, rc::Rc};

use anyhow::{Context, Result, anyhow, bail};
use enum_map::EnumMap;
use ringbuffer::{AllocRingBuffer, RingBuffer};
use risc0_binfmt::{ByteAddr, MemoryImage, PovwJobId, PovwNonce, WordAddr};
use risc0_zkp::core::{
    digest::{DIGEST_BYTES, Digest},
    hash::poseidon2::ROUNDS_HALF_FULL,
    log2_ceil,
};

#[cfg(feature = "rv32im-m3")]
use super::block_tracker::{BlockTracker, POINTS_PER_ROW};

use crate::{
    EcallKind, EcallMetric, MAX_INSN_CYCLES, MAX_INSN_CYCLES_LOWER_PO2, Rv32imV2Claim,
    TerminateState,
    execute::{DEFAULT_SEGMENT_LIMIT_PO2, poseidon2::Poseidon2, rv32im::disasm},
    trace::{TraceCallback, TraceEvent},
};

use super::{
    SyscallContext, bigint,
    pager::{PageTraceEvent, PagedMemory, WorkingImage, compute_partial_image},
    platform::*,
    poseidon2::Poseidon2State,
    r0vm::{LoadOp, Risc0Context, Risc0Machine},
    rv32im::{DecodedInstruction, Emulator, InsnKind},
    segment::Segment,
    sha2::Sha2State,
    syscall::Syscall,
    unlikely,
};

/// Executor implementing the RISC Zero virtual machine for the `rv32im` circuit.
pub struct Executor<'a, S: Syscall> {
    pc: ByteAddr,
    user_pc: ByteAddr,
    machine_mode: u32,
    user_cycles: u32,
    initial_image: MemoryImage,
    pager: PagedMemory,
    terminate_state: Option<TerminateState>,
    read_record: Vec<Vec<u8>>,
    write_record: Vec<u32>,
    syscall_handler: Rc<S>,
    input_digest: Digest,
    output_digest: Option<Digest>,
    trace: Vec<Rc<RefCell<dyn TraceCallback + 'a>>>,
    cycles: SessionCycles,
    ecall_metrics: EnumMap<EcallKind, EcallMetric>,
    /// Ring buffer storing the most recent instructions executed. When the exec_debug feature is
    /// enabled, if the executor encounter an error, it dumps these recent instructions.
    ring: AllocRingBuffer<(ByteAddr, InsnKind, DecodedInstruction)>,
    povw_job_id: Option<PovwJobId>,
    circuit_version: u32,
    segment_counter: u32,
    insn_counter: u32,

    #[cfg(feature = "rv32im-m3")]
    block_tracker: BlockTracker,
}

/// Results from running the [Executor], including information about the initial and final memory
/// states as well metrics for the number of segments and cycles used.
///
/// This struct has the information required to compute the [Rv32imV2Claim] for the execution.
#[derive(Clone, Debug)]
#[non_exhaustive]
pub struct ExecutorResult {
    pub segments: u64,
    pub pre_image: MemoryImage,
    pub post_image: MemoryImage,
    pub user_cycles: u64,
    pub total_cycles: u64,
    pub paging_cycles: u64,
    pub reserved_cycles: u64,
    pub ecall_metrics: EnumMap<EcallKind, EcallMetric>,

    // Fields used to populate the [Rv32imV2Claim].
    pub input: Digest,
    pub output: Option<Digest>,
    pub terminate_state: Option<TerminateState>,
    pub shutdown_cycle: Option<u32>,
}

impl ExecutorResult {
    /// Construct the [Rv32imV2Claim] for this execution.
    ///
    /// Calling this function will compute the digests of the pre and post image, if needed.
    pub fn claim(&mut self) -> Rv32imV2Claim {
        Rv32imV2Claim {
            pre_state: self.pre_image.image_id(),
            post_state: self.post_image.image_id(),
            input: self.input,
            output: self.output,
            terminate_state: self.terminate_state,
            shutdown_cycle: self.shutdown_cycle,
        }
    }
}

#[derive(Default)]
struct SessionCycles {
    total: u64,
    user: u64,
    paging: u64,
    reserved: u64,
}

#[non_exhaustive]
pub struct SimpleSession {
    pub segments: Vec<Segment>,
    pub result: ExecutorResult,
}

/// Limits on the execution, ensuring each segment can be proven and the session terminates.
#[derive(Copy, Clone, Debug)]
#[non_exhaustive]
pub struct ExecutionLimit {
    /// Maximum size of a segment, expressed as a power-of-two.
    pub segment_po2: usize,
    /// Maximum number of cycles a single instruction is allowed to consume.
    ///
    /// Ecall instructions and paging can result in a single worst-case instruction taking
    /// thousands of cycles. This is the limit on a number of cycles a single instruction can take.
    /// If an instruction exceeds this limit, and falls at the end of segment, it may result in an
    /// execution failure.
    pub max_insn_cycles: Option<usize>,
    /// Limit on the number of cycles to execute in the session.
    pub session: CycleLimit,
}

impl Default for ExecutionLimit {
    fn default() -> Self {
        Self::DEFAULT
    }
}

impl ExecutionLimit {
    pub const DEFAULT: Self = Self {
        segment_po2: DEFAULT_SEGMENT_LIMIT_PO2,
        max_insn_cycles: None,
        session: CycleLimit::None,
    };

    pub const fn with_segment_po2(self, segment_po2: usize) -> Self {
        Self {
            segment_po2,
            ..self
        }
    }

    pub const fn with_max_insn_cycles(self, max_insn_cycles: usize) -> Self {
        Self {
            max_insn_cycles: Some(max_insn_cycles),
            ..self
        }
    }

    pub const fn with_session_limit(self, session: CycleLimit) -> Self {
        Self { session, ..self }
    }

    pub const fn with_soft_session_limit(self, cycles: u64) -> Self {
        Self {
            session: CycleLimit::Soft(cycles),
            ..self
        }
    }

    pub const fn with_hard_session_limit(self, cycles: u64) -> Self {
        Self {
            session: CycleLimit::Hard(cycles),
            ..self
        }
    }

    pub fn segment_limit(&self) -> u32 {
        1 << self.segment_po2 as u32
    }

    fn segment_threshold(&self) -> u32 {
        self.segment_limit() - self.max_insn_cycles() as u32
    }

    pub fn max_insn_cycles(&self) -> usize {
        self.max_insn_cycles.unwrap_or(if self.segment_po2 >= 15 {
            MAX_INSN_CYCLES
        } else {
            MAX_INSN_CYCLES_LOWER_PO2
        })
    }
}

#[derive(Copy, Clone, Debug, Default)]
pub enum CycleLimit {
    /// Hard limit on the number of cycles, it is an error to exceed this limit.
    Hard(u64),
    /// Soft limit on the number of cycles. Terminate, without error, if this limit is reached.
    Soft(u64),
    /// No limit on the number of cycles.
    #[default]
    None,
}

#[derive(thiserror::Error, Debug)]
#[non_exhaustive]
pub enum ExecutionError {
    /// Error when when a hard [CycleLimit] is exceeded.
    #[error("Session limit exceeded: {cycle} >= {limit}")]
    CycleLimitExceeded { limit: u64, cycle: u64 },
    /// Error when the execution encounters an error. Optionally includes a [SegmentUpdate] with
    /// the results of execution up to the point of error in the final segment.
    #[error("Execution failed at program counter {pc:?}: {error}")]
    ExecutionFailed {
        #[source]
        error: anyhow::Error,
        pc: ByteAddr,
        update: Option<Box<SegmentUpdate>>,
    },
    #[error(transparent)]
    Other(#[from] anyhow::Error),
}

/// Update message sent to the segment callback on each split.
///
/// Contains the updated memory pages as well as the pages accessed during the associated segment.
/// Can be used to construct a [Segment] starting from an an initial memory state and processing
/// each segment update.
#[non_exhaustive]
#[derive(Clone, derive_more::Debug)]
pub struct SegmentUpdate {
    /// Partial image containing pages that were written to in the segment.
    update_partial_image: WorkingImage,
    /// Indices of all pages that were accessed in the segment.
    access_page_indexes: BTreeSet<u32>,

    /// Record of what is read by the guest across all syscalls.
    #[debug("{}", read_record.len())]
    read_record: Vec<Vec<u8>>,
    /// Record of writen to the host across all syscalls.
    #[debug("{}", write_record.len())]
    write_record: Vec<u32>,

    /// Input digest available to the guest via the input ecall.
    input_digest: Digest,
    /// Output digest set by the guest upon termination.
    ///
    /// Will only be `Some` if `terminate_state` is `Some`.
    output_digest: Option<Digest>,
    /// Value set upon termination of execution, indicating the termination type.
    terminate_state: Option<TerminateState>,

    /// Count of "user cycles", the cycles directly associated with instructions executed by the
    /// user guest program, before suspend in this segment. Does not include paging costs.
    pub user_cycles: u32,
    /// Count of cycles associated with memory paging (i.e. page-in and page-out operations).
    pager_cycles: u32,
    insn_counter: u32,
    segment_threshold: u32,
    /// Power-of-two for the segment size required to prove this segment.
    pub po2: u32,
    /// Index of the segment in the session.
    index: u64,
    /// Gloablly unique nonce used within the proof of verifiable work system.
    povw_nonce: Option<PovwNonce>,
}

impl SegmentUpdate {
    /// Applies the update to the given [MemoryImage].
    ///
    /// Provided that the given memory image represents that state at the start of the segment, the
    /// memory image will be updated to the state after the segment.
    ///
    /// This function does not guarantee an update the node digests in the [MemoryImage] Merkle
    /// tree. To ensure that the digests are up to date, call [MemoryImage::update_digests].
    pub fn apply_to(&self, memory_image: &mut MemoryImage) -> Result<()> {
        for (idx, page) in self.update_partial_image.pages.iter() {
            memory_image.set_page(*idx, page.clone());
        }
        Ok(())
    }

    /// Compute a partially populated [MemoryImage] containing all pages from the given memory
    /// image that were accessed during this segment along with the Merkle tree uncles. The given
    /// memory image is updated to cache any hashes computed in the process.
    ///
    /// This function does not guarantee the digests are up to date on the returned [MemoryImage].
    /// Call [MemoryImage::update_digests] if needed to ensure the digests are up to date.
    pub fn compute_partial_image(&self, memory_image: &mut MemoryImage) -> Result<MemoryImage> {
        Ok(compute_partial_image(
            memory_image,
            &self.access_page_indexes,
        ))
    }

    /// Construct a [Segment] from this struct and the given initial memory image.
    ///
    /// The initial partial memory image can be calculated with [Self::compute_partial_image], as
    /// only accessed pages are required.
    pub fn into_segment(self, partial_image: MemoryImage) -> Segment {
        Segment {
            partial_image,
            input_digest: self.input_digest,
            output_digest: self.output_digest,
            terminate_state: self.terminate_state,
            read_record: self.read_record,
            write_record: self.write_record,
            suspend_cycle: self.user_cycles,
            paging_cycles: self.pager_cycles,
            insn_counter: self.insn_counter,
            po2: self.po2,
            index: self.index,
            segment_threshold: self.segment_threshold,
            povw_nonce: self.povw_nonce,
        }
    }

    /// Produces a [Segment] with the partial memory image fore all accessed pages, then applies
    /// the update to the given [MemoryImage].
    pub fn apply_into_segment(self, memory_image: &mut MemoryImage) -> Result<Segment> {
        let partial_image = self
            .compute_partial_image(memory_image)
            .context("Failed to compute partial memory image")?;
        self.apply_to(memory_image)
            .context("Failed to apply update to memory image")?;
        Ok(self.into_segment(partial_image))
    }
}

impl<'a, S: Syscall> Executor<'a, S> {
    pub fn new(
        image: MemoryImage,
        syscall_handler: S,
        input_digest: Option<Digest>,
        trace: Vec<Rc<RefCell<dyn TraceCallback + 'a>>>,
        povw_job_id: Option<PovwJobId>,
        circuit_version: u32,
    ) -> Self {
        Self::new_inner(
            image,
            Rc::new(syscall_handler),
            input_digest,
            trace,
            povw_job_id,
            circuit_version,
        )
    }

    /// An internal version of new that takes an Rc for syscall_handler to avoid ownership issues.
    fn new_inner(
        image: MemoryImage,
        syscall_handler: Rc<S>,
        input_digest: Option<Digest>,
        trace: Vec<Rc<RefCell<dyn TraceCallback + 'a>>>,
        povw_job_id: Option<PovwJobId>,
        circuit_version: u32,
    ) -> Self {
        Self {
            pc: ByteAddr(0),
            user_pc: ByteAddr(0),
            machine_mode: 0,
            user_cycles: 0,
            insn_counter: 0,
            pager: PagedMemory::new(image.clone(), /*tracing_enabled=*/ !trace.is_empty()),
            initial_image: image,
            terminate_state: None,
            read_record: Vec::new(),
            write_record: Vec::new(),
            syscall_handler,
            input_digest: input_digest.unwrap_or_default(),
            output_digest: None,
            trace,
            cycles: SessionCycles::default(),
            ecall_metrics: Default::default(),
            ring: AllocRingBuffer::new(10),
            povw_job_id,
            circuit_version,
            segment_counter: 0,
            #[cfg(feature = "rv32im-m3")]
            block_tracker: Default::default(),
        }
    }

    /// Execute up to the next segment split.
    ///
    /// If the machine is in a terminal state, no segment is returned. This function can be used to
    /// incrementally execute the program in an iterator-like fashion.
    pub fn run_segment(
        &mut self,
        limit: ExecutionLimit,
    ) -> Result<Option<SegmentUpdate>, ExecutionError> {
        // If the executor is in a normal termination state, return Ok(None).
        if self.terminate_state.is_some() {
            return Ok(None);
        }
        if let CycleLimit::Soft(soft_limit) = limit.session
            && self.cycles.user >= soft_limit
        {
            return Ok(None);
        }

        Risc0Machine::resume(self)?;

        loop {
            // Check if the machine has reached termination.
            let None = self.terminate_state else {
                break;
            };

            // Check the session-level cycle limit.
            match limit.session {
                CycleLimit::Hard(max_cycles) => {
                    if self.cycles.user >= max_cycles {
                        return Err(ExecutionError::CycleLimitExceeded {
                            limit: max_cycles,
                            cycle: self.cycles.user,
                        });
                    }
                }
                CycleLimit::Soft(max_cycles) => {
                    if self.cycles.user >= max_cycles {
                        break;
                    }
                }
                CycleLimit::None => {}
            }

            // Check the segment-level cycle limit.
            if self.should_split(limit.segment_threshold()) {
                // NOTE: If the max_insn_cycles is set accurately, this should never happen.
                if self.segment_cycles() > limit.segment_limit() {
                    return Err(anyhow!(
                        "segment limit ({}) too small for instruction at pc: {:?}",
                        limit.segment_limit(),
                        self.pc
                    )
                    .into());
                };

                break;
            }

            // Execute a step of the virtual machine.
            if let Err(error) = Risc0Machine::step(&mut Emulator {}, self) {
                // On error, log information about the most recent instructions (at `debug` level),
                // and include a SegmentUpdate for the segment up to the point of the error.
                self.dump_recent_instructions();
                return Err(ExecutionError::ExecutionFailed {
                    error,
                    pc: self.pc,
                    update: Some(Box::new(self.dump_segment(
                        limit.segment_po2,
                        0,
                        self.segment_counter,
                    ))),
                });
            }
            self.insn_counter += 1;
        }

        Risc0Machine::suspend(self)?;

        let cycles = self.segment_cycles().next_power_of_two();
        let po2 = log2_ceil(cycles as usize);
        let segment_threshold_min = u32::min(self.segment_cycles(), limit.segment_threshold());
        let update = self.split_segment(po2, segment_threshold_min)?;

        Ok(Some(update))
    }

    /// Execute until the program reaches a terminal state. Either due to the machine exiting, or
    /// an session limit being reached.
    pub fn run(
        mut self,
        limit: ExecutionLimit,
        mut callback: impl FnMut(SegmentUpdate) -> Result<()>,
    ) -> Result<ExecutorResult, ExecutionError> {
        while let Some(update) = self.run_segment(limit)? {
            callback(update).context("Segment update callback returned error")?;
        }
        Ok(self.state())
    }

    /// Execute a segment split, committing the current pager state, sending the segment to the
    /// segment callback thread thread, and resetting the pager and segment stats.
    ///
    /// Takes a handle to the segment callback thread so that it can get the error if the thread
    /// fails to receive the segment request (e.g. the thread has died).
    fn split_segment(
        &mut self,
        segment_po2: usize,
        segment_threshold: u32,
    ) -> Result<SegmentUpdate, ExecutionError> {
        tracing::debug!(
            "split(phys: {} + pager: {} + reserved: {RESERVED_CYCLES}) = {} >= {segment_threshold}",
            self.user_cycles,
            self.pager.cycles,
            self.segment_cycles()
        );

        let partial_image = self.pager.commit();

        let update = SegmentUpdate {
            update_partial_image: partial_image,
            access_page_indexes: self.pager.page_indexes(),
            input_digest: self.input_digest,
            output_digest: self.output_digest,
            read_record: std::mem::take(&mut self.read_record),
            write_record: std::mem::take(&mut self.write_record),
            user_cycles: self.user_cycles,
            pager_cycles: self.pager.cycles,
            insn_counter: self.insn_counter,
            terminate_state: self.terminate_state,
            segment_threshold,
            po2: segment_po2 as u32,
            index: self.segment_counter as u64,
            povw_nonce: self.povw_nonce(self.segment_counter),
        };

        // NOTE: There is no reasonable scenario where a session will have more than 4B
        // segments, but its possible.
        self.segment_counter = self
            .segment_counter
            .checked_add(1)
            .context("segment_counter overflow")?;

        let total_cycles = 1 << segment_po2;
        let pager_cycles = self.pager.cycles as u64;
        self.cycles.total += total_cycles;
        self.cycles.paging += pager_cycles;

        // XXX remi: For m3, these cycle counts no longer add up to the po2
        #[cfg(not(feature = "rv32im-m3"))]
        {
            let user_cycles = self.user_cycles as u64;
            self.cycles.reserved += total_cycles - pager_cycles - user_cycles;
        }

        self.user_cycles = 0;
        self.insn_counter = 0;
        self.pager.reset();

        #[cfg(feature = "rv32im-m3")]
        {
            self.block_tracker = Default::default();
        }

        Ok(update)
    }

    /// Access the syscall handler used by this executor.
    pub fn syscall_handler(&self) -> &S {
        &self.syscall_handler
    }

    /// Access the syscall handler used by this executor, allowing mutation.
    pub fn syscall_handler_mut(&mut self) -> &mut S {
        // unwrap will not fail because the only clones of this Rc are short-lived.
        Rc::get_mut(&mut self.syscall_handler).unwrap()
    }

    pub(crate) fn terminate_state(&self) -> Option<&TerminateState> {
        self.terminate_state.as_ref()
    }

    /// Compute the [ExecutorResult] from the initial to the current state of the executor.
    pub fn state(&self) -> ExecutorResult {
        ExecutorResult {
            segments: self.segment_counter as u64 + 1,
            pre_image: self.initial_image.clone(),
            post_image: self.pager.image.clone().into(),
            user_cycles: self.cycles.user,
            total_cycles: self.cycles.total,
            paging_cycles: self.cycles.paging,
            reserved_cycles: self.cycles.reserved,
            ecall_metrics: self.ecall_metrics.clone(),
            input: self.input_digest,
            output: self.output_digest,
            terminate_state: self.terminate_state,
            shutdown_cycle: None,
        }
    }

    fn dump_recent_instructions(&self) {
        tracing::debug!("Dumping last {} instructions:", self.ring.len());
        for (pc, kind, decoded) in self.ring.iter() {
            tracing::debug!("{pc:?}> {:#010x}  {}", decoded.insn, disasm(*kind, decoded));
        }
    }

    /// Produce a [SegmentUpdate] from the current state of the executor. Unlike
    /// [Executor::split_segment], this does not reset the state of the executor.
    fn dump_segment(&mut self, po2: usize, segment_threshold: u32, index: u32) -> SegmentUpdate {
        let partial_image = self.pager.commit();
        SegmentUpdate {
            update_partial_image: partial_image,
            access_page_indexes: self.pager.page_indexes(),
            input_digest: self.input_digest,
            output_digest: self.output_digest,
            read_record: self.read_record.clone(),
            write_record: self.write_record.clone(),
            user_cycles: self.user_cycles,
            pager_cycles: self.pager.cycles,
            insn_counter: self.insn_counter,
            terminate_state: self.terminate_state,
            segment_threshold,
            po2: po2 as u32,
            index: index as u64,
            povw_nonce: self.povw_nonce(index),
        }
    }

    /// Reset the state of the executor, such that a new session can be stated from the current
    /// memory state and with the same syscall handler and tracer (if any).
    pub fn reset(&mut self) {
        let image: MemoryImage = std::mem::take(&mut self.pager.image).into();
        *self = Self::new_inner(
            image,
            self.syscall_handler.clone(),
            Some(self.input_digest),
            std::mem::take(&mut self.trace),
            self.povw_job_id,
            self.circuit_version,
        )
    }

    #[cfg(not(feature = "rv32im-m3"))]
    fn segment_cycles(&self) -> u32 {
        self.user_cycles + self.pager.cycles + RESERVED_CYCLES as u32
    }

    #[cfg(feature = "rv32im-m3")]
    fn segment_cycles(&self) -> u32 {
        let blocks = self
            .block_tracker
            .get_blocks(self.user_cycles, self.pager.touched_pages());
        blocks.row_points().div_ceil(POINTS_PER_ROW) as u32
    }

    #[cfg(not(feature = "rv32im-m3"))]
    fn should_split(&self, segment_threshold: u32) -> bool {
        self.segment_cycles() > segment_threshold
    }

    #[cfg(feature = "rv32im-m3")]
    fn should_split(&self, segment_threshold: u32) -> bool {
        let blocks = self
            .block_tracker
            .get_blocks(self.user_cycles, self.pager.touched_pages());
        if blocks.row_points().div_ceil(POINTS_PER_ROW) as u32 > segment_threshold {
            tracing::debug!("block_tracker blocks = {blocks:?}");
            true
        } else {
            false
        }
    }

    fn inc_user_cycles(&mut self, count: usize, ecall: Option<EcallKind>) {
        self.cycles.user += count as u64;
        self.user_cycles += count as u32;
        if let Some(kind) = ecall {
            self.ecall_metrics[kind].cycles += count as u64;
        }
    }

    fn povw_nonce(&self, segment_index: u32) -> Option<PovwNonce> {
        self.povw_job_id.map(|job| job.nonce(segment_index))
    }

    #[cold]
    fn trace(&mut self, event: TraceEvent) -> Result<(), ExecutionError> {
        for trace in self.trace.iter() {
            trace.borrow_mut().trace_callback(event.clone())?;
        }
        Ok(())
    }

    #[cold]
    fn trace_pager(&mut self) -> Result<(), ExecutionError> {
        for &event in self.pager.trace_events() {
            let event = TraceEvent::from(event);
            for trace in self.trace.iter() {
                trace.borrow_mut().trace_callback(event.clone())?;
            }
        }
        self.pager.clear_trace_events();
        Ok(())
    }

    #[inline(always)]
    fn trace_instruction(&mut self, cycle: u64, kind: InsnKind, decoded: &DecodedInstruction) {
        if unlikely(tracing::enabled!(tracing::Level::TRACE)) {
            tracing::trace!(
                "[{}:{}:{cycle}] {:?}> {:#010x}  {}",
                self.user_cycles + 1,
                self.segment_cycles() + 1,
                self.pc,
                decoded.insn,
                super::rv32im::disasm(kind, decoded)
            );
        }
        if unlikely(tracing::enabled!(tracing::Level::DEBUG)) {
            self.ring.push((self.pc, kind, decoded.clone()));
        }
    }
}

impl<S: Syscall> Risc0Context for Executor<'_, S> {
    fn circuit_version(&self) -> u32 {
        self.circuit_version
    }

    fn get_pc(&self) -> ByteAddr {
        self.pc
    }

    fn set_pc(&mut self, addr: ByteAddr) {
        self.pc = addr;
    }

    fn set_user_pc(&mut self, addr: ByteAddr) {
        self.user_pc = addr;
    }

    fn get_machine_mode(&self) -> u32 {
        self.machine_mode
    }

    fn set_machine_mode(&mut self, mode: u32) {
        self.machine_mode = mode;
    }

    fn resume(&mut self) -> Result<()> {
        let input_words = self.input_digest.as_words().to_vec();
        for (i, word) in input_words.iter().enumerate() {
            self.store_u32(GLOBAL_INPUT_ADDR.waddr() + i, *word)?;
        }
        Ok(())
    }

    #[inline(always)]
    fn on_insn_start(&mut self, kind: InsnKind, decoded: &DecodedInstruction) -> Result<()> {
        #[cfg(feature = "rv32im-m3")]
        self.block_tracker.track_pc(self.user_pc.0);

        let cycle = self.cycles.user;
        self.trace_instruction(cycle, kind, decoded);
        if unlikely(!self.trace.is_empty()) {
            self.trace(TraceEvent::InstructionStart {
                cycle,
                pc: self.pc.0,
                insn: decoded.insn,
            })?;
        }
        Ok(())
    }

    #[inline(always)]
    fn on_insn_end(&mut self, #[allow(unused_variables)] kind: InsnKind) -> Result<()> {
        #[cfg(feature = "rv32im-m3")]
        self.block_tracker.track_instr(kind);

        self.inc_user_cycles(1, None);
        if unlikely(!self.trace.is_empty()) {
            self.trace_pager()?;
        }
        Ok(())
    }

    fn on_ecall_cycle(
        &mut self,
        cur: CycleState,
        _next: CycleState,
        _s0: u32,
        _s1: u32,
        _s2: u32,
        kind: EcallKind,
    ) -> Result<()> {
        if cur == CycleState::MachineEcall {
            self.ecall_metrics[kind].count += 1;
        }
        self.inc_user_cycles(1, Some(kind));

        if !self.trace.is_empty() {
            self.trace_pager()?;
        }
        Ok(())
    }

    #[inline(always)]
    fn load_u32(&mut self, op: LoadOp, addr: WordAddr) -> Result<u32> {
        let word = match op {
            LoadOp::Peek => self.pager.peek(addr)?,
            LoadOp::Load | LoadOp::Record => self.pager.load(addr)?,
        };
        // tracing::trace!("load_mem({:?}) -> {word:#010x}", addr.baddr());
        Ok(word)
    }

    #[inline(always)]
    fn load_register(&mut self, _op: LoadOp, base: WordAddr, idx: usize) -> Result<u32> {
        let word = self.pager.load_register(base, idx);
        // tracing::trace!("load_register({:?}) -> {word:#010x}", addr.baddr());
        Ok(word)
    }

    #[inline(always)]
    fn store_u32(&mut self, addr: WordAddr, word: u32) -> Result<()> {
        // tracing::trace!(
        //     "store_u32({:?}, {word:#010x}), pc: {:?}",
        //     addr.baddr(),
        //     self.pc
        // );
        if unlikely(!self.trace.is_empty()) {
            self.trace(TraceEvent::MemorySet {
                addr: addr.baddr().0,
                region: word.to_be_bytes().to_vec(),
            })?;
        }
        self.pager.store(addr, word)
    }

    #[inline(always)]
    fn store_register(&mut self, base: WordAddr, idx: usize, word: u32) -> Result<()> {
        // tracing::trace!("store_register({:?}, {word:#010x})", addr.baddr());
        if unlikely(!self.trace.is_empty()) {
            self.trace(TraceEvent::MemorySet {
                addr: (base + idx).baddr().0,
                region: word.to_be_bytes().to_vec(),
            })?;
        }
        self.pager.store_register(base, idx, word);
        Ok(())
    }

    fn on_terminate(&mut self, a0: u32, a1: u32) -> Result<()> {
        self.terminate_state = Some(TerminateState {
            a0: a0.into(),
            a1: a1.into(),
        });
        tracing::debug!("{:?}", self.terminate_state);

        let output: Digest = self
            .load_region(LoadOp::Peek, GLOBAL_OUTPUT_ADDR, DIGEST_BYTES)?
            .as_slice()
            .try_into()?;
        self.output_digest = Some(output);

        #[cfg(feature = "rv32im-m3")]
        self.block_tracker.track_ecall_terminate();

        Ok(())
    }

    fn host_read(&mut self, fd: u32, buf: &mut [u8]) -> Result<u32> {
        // NOTE: This clone is required to allow host_read to have mutable access to self.
        let rlen = self.syscall_handler.clone().host_read(self, fd, buf)?;
        let slice = &buf[..rlen as usize];
        self.read_record.push(slice.to_vec());
        Ok(rlen)
    }

    fn host_write(&mut self, fd: u32, buf: &[u8]) -> Result<u32> {
        // NOTE: This clone is required to allow host_read to have mutable access to self.
        let rlen = self.syscall_handler.clone().host_write(self, fd, buf)?;
        self.write_record.push(rlen);
        Ok(rlen)
    }

    fn on_sha2_cycle(&mut self, _cur_state: CycleState, _sha2: &Sha2State) {
        self.inc_user_cycles(1, Some(EcallKind::Sha2));
    }

    fn on_poseidon2_cycle(&mut self, _cur_state: CycleState, _p2: &Poseidon2State) {
        self.inc_user_cycles(1, Some(EcallKind::Poseidon2));
    }

    fn ecall_bigint(&mut self) -> Result<()> {
        let verify_program_size = bigint::ecall_execute(self)?;

        #[cfg(feature = "rv32im-m3")]
        self.block_tracker
            .track_ecall_bigint(verify_program_size as u64);

        self.inc_user_cycles(verify_program_size + 1, Some(EcallKind::BigInt));

        Ok(())
    }

    fn ecall_poseidon2(&mut self) -> Result<()> {
        let mut p2 = Poseidon2::load_ecall(self)?;

        #[cfg(feature = "rv32im-m3")]
        self.block_tracker.track_ecall_poseidon2(p2.count);

        p2.rest_with_mix(self, CycleState::Decode, |p2, _, ctx| {
            ctx.inc_user_cycles(ROUNDS_HALF_FULL * 2 + 1, Some(EcallKind::Poseidon2));
            // Convert to Montgomery form, run the mix function, then convert back.
            // NOTE: It's possible this could be optimized to not convert the back and forth on
            // every mix, and instead only convert the input, initial state and final state.
            // However, it does not seem that this conversion has a significant impact.
            let mut state = p2.inner.map(Into::into);
            risc0_zkp::core::hash::poseidon2::poseidon2_mix(&mut state);
            p2.inner = state.map(Into::into);
            Ok(())
        })
    }

    #[cfg(feature = "rv32im-m3")]
    fn on_ecall_read_end(&mut self, read_bytes: u64, read_words: u64) {
        self.block_tracker.track_ecall_read(read_bytes, read_words);
    }

    #[cfg(feature = "rv32im-m3")]
    fn on_ecall_write_end(&mut self) {
        self.block_tracker.track_ecall_write();
    }
}

impl<S: Syscall> SyscallContext for Executor<'_, S> {
    fn peek_register(&mut self, idx: usize) -> Result<u32> {
        if idx >= REG_MAX {
            bail!("invalid register: x{idx}");
        }
        self.load_register(LoadOp::Peek, USER_REGS_ADDR.waddr(), idx)
    }

    fn peek_u32(&mut self, addr: ByteAddr) -> Result<u32> {
        // let addr = Self::check_guest_addr(addr)?;
        self.load_u32(LoadOp::Peek, addr.waddr())
    }

    fn peek_u8(&mut self, addr: ByteAddr) -> Result<u8> {
        // let addr = Self::check_guest_addr(addr)?;
        self.load_u8(LoadOp::Peek, addr)
    }

    fn peek_region(&mut self, addr: ByteAddr, size: usize) -> Result<Vec<u8>> {
        // let addr = Self::check_guest_addr(addr)?;
        self.load_region(LoadOp::Peek, addr, size)
    }

    fn read_region(&mut self, addr: ByteAddr, size: usize) -> Result<impl Read> {
        // let addr = Self::check_guest_addr(addr)?;
        <Self as Risc0Context>::read_region(self, LoadOp::Peek, addr, size)
    }

    fn peek_page(&mut self, page_idx: u32) -> Result<&[u8; PAGE_BYTES]> {
        Ok(self.pager.peek_page(page_idx)?.data())
    }

    fn get_cycle(&self) -> u64 {
        self.cycles.user
    }

    fn get_pc(&self) -> u32 {
        self.user_pc.0
    }
}

impl From<PageTraceEvent> for TraceEvent {
    fn from(event: PageTraceEvent) -> Self {
        match event {
            PageTraceEvent::PageIn { cycles } => TraceEvent::PageIn {
                cycles: cycles as u64,
            },
            PageTraceEvent::PageOut { cycles } => TraceEvent::PageOut {
                cycles: cycles as u64,
            },
        }
    }
}
