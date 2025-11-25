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

use anyhow::{Context, Result, bail};
use enum_map::EnumMap;
use ringbuffer::{AllocRingBuffer, RingBuffer};
use risc0_binfmt::{ByteAddr, MemoryImage, PovwJobId, PovwNonce, WordAddr};
use risc0_zkp::core::{
    digest::{DIGEST_BYTES, Digest},
    log2_ceil,
};

use crate::{
    EcallKind, EcallMetric, Rv32imV2Claim, TerminateState,
    execute::rv32im::disasm,
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

pub struct Executor<'a, 'b, S: Syscall> {
    pc: ByteAddr,
    user_pc: ByteAddr,
    machine_mode: u32,
    user_cycles: u32,
    initial_image: MemoryImage,
    pager: PagedMemory,
    terminate_state: Option<TerminateState>,
    read_record: Vec<Vec<u8>>,
    write_record: Vec<u32>,
    syscall_handler: &'a S,
    input_digest: Digest,
    output_digest: Option<Digest>,
    trace: Vec<Rc<RefCell<dyn TraceCallback + 'b>>>,
    cycles: SessionCycles,
    ecall_metrics: EnumMap<EcallKind, EcallMetric>,
    /// Ring buffer storing the most recent instructions executed. When the exec_debug feature is
    /// enabled, if the executor encounter an error, it dumps these recent instructions.
    ring: AllocRingBuffer<(ByteAddr, InsnKind, DecodedInstruction)>,
    povw_job_id: Option<PovwJobId>,
    circuit_version: u32,
    segment_counter: u32,
    insn_counter: u32,
}

#[non_exhaustive]
pub struct ExecutorResult {
    pub segments: u64,
    pub pre_image: MemoryImage,
    pub post_image: MemoryImage,
    pub user_cycles: u64,
    pub total_cycles: u64,
    pub paging_cycles: u64,
    pub reserved_cycles: u64,

    // Fields used to populate the [Rv32imV2Claim].
    pub input: Digest,
    pub output: Option<Digest>,
    pub terminate_state: Option<TerminateState>,
    pub shutdown_cycle: Option<u32>,
}

impl ExecutorResult {
    /// Construct the [Rv32imV2Claim] for this execution.
    ///
    /// Calling this function will update the digests on the pre and post image, if needed.
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

pub enum CycleLimit {
    Hard(u64), // it is an error to exceed this limit
    Soft(u64), // stop execution after this cycle count
    None,
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

pub trait SegmentUpdateCallbackFactory {
    type Callback: SegmentUpdateCallback;

    fn with_initial_image(self, initial_image: &MemoryImage) -> Result<Self::Callback>;
}

/// A callback used to collect each [SegmentUpdate] generated by execution.
pub trait SegmentUpdateCallback {
    /// Method called each time the executor completes execution of a segment.
    fn on_segment_update(&mut self, update: SegmentUpdate) -> Result<()>;

    /// Method called with a final update if the executor encounters an error.
    ///
    /// Default implementation is a no-op.
    #[expect(unused_variables)]
    fn on_execution_error(&mut self, final_update: SegmentUpdate) -> Result<()> {
        Ok(())
    }
}

impl<F> SegmentUpdateCallback for F
where
    F: FnMut(SegmentUpdate) -> Result<()>,
{
    fn on_segment_update(&mut self, update: SegmentUpdate) -> Result<()> {
        self(update)
    }
}

impl<T: SegmentUpdateCallback> SegmentUpdateCallbackFactory for T {
    type Callback = Self;

    /// Implement [SegmentUpdateCallbackFactory] simply by returning self.
    fn with_initial_image(self, _: &MemoryImage) -> Result<Self::Callback> {
        Ok(self)
    }
}

impl<'a, 'b, S: Syscall> Executor<'a, 'b, S> {
    pub fn new(
        image: MemoryImage,
        syscall_handler: &'a S,
        input_digest: Option<Digest>,
        trace: Vec<Rc<RefCell<dyn TraceCallback + 'b>>>,
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
        }
    }

    pub fn run(
        &mut self,
        segment_po2: usize,
        max_insn_cycles: usize,
        max_cycles: CycleLimit,
        callback_factory: impl SegmentUpdateCallbackFactory,
    ) -> Result<ExecutorResult> {
        let segment_limit: u32 = 1 << segment_po2;
        assert!(max_insn_cycles < segment_limit as usize);
        let segment_threshold = segment_limit - max_insn_cycles as u32;

        self.reset();
        let mut callback = callback_factory.with_initial_image(&self.initial_image)?;

        let mut emu = Emulator::new();
        Risc0Machine::resume(self)?;

        while self.terminate_state.is_none() {
            match max_cycles {
                CycleLimit::Hard(max_cycles) => {
                    if self.cycles.user >= max_cycles {
                        bail!(
                            "Session limit exceeded: {} >= {max_cycles}",
                            self.cycles.user
                        );
                    }
                }
                CycleLimit::Soft(max_cycles) => {
                    if self.cycles.user >= max_cycles {
                        break;
                    }
                }
                CycleLimit::None => {}
            }

            if self.segment_cycles() > segment_threshold {
                assert!(
                    self.segment_cycles() < segment_limit,
                    "segment limit ({segment_limit}) too small for instruction at pc: {:?}",
                    self.pc
                );

                Risc0Machine::suspend(self)?;
                self.split_segment(&mut callback, segment_po2, segment_threshold)?;
                Risc0Machine::resume(self)?;
            }

            let result = Risc0Machine::step(&mut emu, self);
            self.insn_counter += 1;

            if let Err(err) = result {
                self.dump();
                let result = self.dump_segment(
                    &mut callback,
                    segment_po2,
                    segment_threshold,
                    self.segment_counter,
                );
                return Err(if let Err(inner) = result {
                    err.context(inner)
                } else {
                    err
                });
            }
        }

        Risc0Machine::suspend(self)?;

        let final_cycles = self.segment_cycles().next_power_of_two();
        let final_po2 = log2_ceil(final_cycles as usize);
        self.split_segment(
            &mut callback,
            final_po2,
            0, // theshold is meaningless for final segment
        )?;

        Ok(ExecutorResult {
            segments: self.segment_counter as u64 + 1,
            pre_image: self.initial_image.clone(),
            post_image: self.pager.image.clone().into(),
            user_cycles: self.cycles.user,
            total_cycles: self.cycles.total,
            paging_cycles: self.cycles.paging,
            reserved_cycles: self.cycles.reserved,
            input: self.input_digest,
            output: self.output_digest,
            terminate_state: self.terminate_state,
            shutdown_cycle: None,
        })
    }

    /// Execute a segment split, committing the current pager state, sending the segment to the
    /// segment callback thread thread, and resetting the pager and segment stats.
    ///
    /// Takes a handle to the segment callback thread so that it can get the error if the thread
    /// fails to receive the segment request (e.g. the thread has died).
    fn split_segment(
        &mut self,
        callback: &mut impl SegmentUpdateCallback,
        segment_po2: usize,
        segment_threshold: u32,
    ) -> Result<()> {
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

        callback
            .on_segment_update(update)
            .context("Segment update callback returned error")?;

        // NOTE: There is no reasonable scenario where a session will have more than 4B
        // segments, but its possible.
        self.segment_counter = self
            .segment_counter
            .checked_add(1)
            .context("segment_counter overflow")?;

        let total_cycles = 1 << segment_po2;
        let pager_cycles = self.pager.cycles as u64;
        let user_cycles = self.user_cycles as u64;
        self.cycles.total += total_cycles;
        self.cycles.paging += pager_cycles;
        self.cycles.reserved += total_cycles - pager_cycles - user_cycles;
        self.user_cycles = 0;
        self.insn_counter = 0;
        self.pager.reset();

        Ok(())
    }

    pub(crate) fn terminate_state(&self) -> Option<&TerminateState> {
        self.terminate_state.as_ref()
    }

    fn dump(&self) {
        tracing::debug!("Dumping last {} instructions:", self.ring.len());
        for (pc, kind, decoded) in self.ring.iter() {
            tracing::debug!("{pc:?}> {:#010x}  {}", decoded.insn, disasm(*kind, decoded));
        }
    }

    fn dump_segment(
        &mut self,
        callback: &mut impl SegmentUpdateCallback,
        po2: usize,
        segment_threshold: u32,
        index: u32,
    ) -> anyhow::Result<()> {
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
            po2: po2 as u32,
            index: index as u64,
            povw_nonce: self.povw_nonce(index),
        };
        callback
            .on_execution_error(update)
            .context("Segment update callback returned error")
    }

    pub fn take_ecall_metrics(&mut self) -> EnumMap<EcallKind, EcallMetric> {
        std::mem::take(&mut self.ecall_metrics)
    }

    fn reset(&mut self) {
        self.pager.reset();
        self.terminate_state = None;
        self.read_record.clear();
        self.write_record.clear();
        self.output_digest = None;
        self.machine_mode = 0;
        self.user_cycles = 0;
        self.insn_counter = 0;
        self.cycles = SessionCycles::default();
        self.pc = ByteAddr(0);
        self.ecall_metrics = Default::default();
        self.segment_counter = 0;
        self.insn_counter = 0;
    }

    fn segment_cycles(&self) -> u32 {
        self.user_cycles + self.pager.cycles + RESERVED_CYCLES as u32
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
    fn trace(&mut self, event: TraceEvent) -> Result<()> {
        for trace in self.trace.iter() {
            trace.borrow_mut().trace_callback(event.clone())?;
        }
        Ok(())
    }

    #[cold]
    fn trace_pager(&mut self) -> Result<()> {
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

impl<S: Syscall> Risc0Context for Executor<'_, '_, S> {
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
    fn on_insn_end(&mut self, _kind: InsnKind) -> Result<()> {
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

        Ok(())
    }

    fn host_read(&mut self, fd: u32, buf: &mut [u8]) -> Result<u32> {
        let rlen = self.syscall_handler.host_read(self, fd, buf)?;
        let slice = &buf[..rlen as usize];
        self.read_record.push(slice.to_vec());
        Ok(rlen)
    }

    fn host_write(&mut self, fd: u32, buf: &[u8]) -> Result<u32> {
        let rlen = self.syscall_handler.host_write(self, fd, buf)?;
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
        let cycles = bigint::ecall_execute(self)?;
        self.inc_user_cycles(cycles, Some(EcallKind::BigInt));
        Ok(())
    }
}

impl<S: Syscall> SyscallContext for Executor<'_, '_, S> {
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
