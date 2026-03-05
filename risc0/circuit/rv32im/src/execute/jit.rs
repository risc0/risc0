// Copyright 2026 RISC Zero, Inc.
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

use std::{cell::RefCell, io::Read, rc::Rc};

use anyhow::{Context, Result, anyhow, bail};
use enum_map::EnumMap;
use ringbuffer::{AllocRingBuffer, RingBuffer};
use risc0_binfmt::{ByteAddr, MemoryImage, PovwJobId, PovwNonce, WordAddr};
use risc0_zkp::core::{
    digest::{DIGEST_BYTES, Digest},
    log2_ceil,
};

use super::block_tracker::{BlockTracker, POINTS_PER_ROW};

use crate::{
    EcallKind, EcallMetric, TerminateState,
    execute::{
        executor::{
            ExecutionError, ExecutionLimit, ExecutorResult, RowInfo, RowLimit, SegmentUpdate,
        },
        poseidon2::Poseidon2,
        rv32im::disasm,
    },
    trace::{TraceCallback, TraceEvent},
};

use super::{
    SyscallContext, bigint,
    pager::PagedMemory,
    platform::*,
    poseidon2::Poseidon2State,
    r0vm::{LoadOp, Risc0Context, Risc0Machine},
    rv32im::{DecodedInstruction, InsnKind},
    sha2::Sha2State,
    syscall::Syscall,
    unlikely,
};

/// Executor implementing the RISC Zero virtual machine for the `rv32im` circuit.
pub struct Executor<'a, S: Syscall> {
    pc: ByteAddr,
    user_pc: ByteAddr,
    machine_mode: u32,
    preflight_user_cycles: u32,
    initial_image: MemoryImage,
    pager: PagedMemory,
    terminate_state: Option<TerminateState>,
    read_record: Vec<Vec<u8>>,
    write_record: Vec<u32>,
    syscall_handler: Rc<S>,
    input_digest: Digest,
    output_digest: Option<Digest>,
    trace: Vec<Rc<RefCell<dyn TraceCallback + 'a>>>,
    row_info: RowInfo,
    ecall_metrics: EnumMap<EcallKind, EcallMetric>,
    /// Ring buffer storing the most recent instructions executed. When the exec_debug feature is
    /// enabled, if the executor encounter an error, it dumps these recent instructions.
    ring: AllocRingBuffer<(ByteAddr, InsnKind, DecodedInstruction)>,
    povw_job_id: Option<PovwJobId>,
    circuit_version: u32,
    segment_counter: u32,
    insn_counter: u32,

    block_tracker: BlockTracker,
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
            preflight_user_cycles: 0,
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
            row_info: RowInfo::default(),
            ecall_metrics: Default::default(),
            ring: AllocRingBuffer::new(10),
            povw_job_id,
            circuit_version,
            segment_counter: 0,
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
        let used_rows = self.get_rows();
        if let RowLimit::Soft(soft_limit) = limit.session
            && used_rows >= soft_limit
        {
            return Ok(None);
        }

        Risc0Machine::resume(self)?;

        loop {
            // Check if the machine has reached termination.
            let None = self.terminate_state else {
                break;
            };

            // Check the session-level row limit.
            match limit.session {
                RowLimit::Hard(max_rows) => {
                    let used_rows = self.get_rows();
                    if used_rows >= max_rows {
                        return Err(ExecutionError::RowLimitExceeded {
                            limit: max_rows,
                            rows: used_rows,
                        });
                    }
                }
                RowLimit::Soft(max_rows) => {
                    let used_rows = self.get_rows();
                    if used_rows >= max_rows {
                        break;
                    }
                }
                RowLimit::None => {}
            }

            // Check the segment-level row limit.
            if self.should_split(limit.segment_threshold()) {
                // NOTE: If the max_insn_rows is set accurately, this should never happen.
                if self.segment_used_rows() > limit.segment_limit() {
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
            if let Err(error) = self.run_jit() {
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

        let rows = self.segment_used_rows().next_power_of_two();
        let po2 = log2_ceil(rows as usize);
        let segment_threshold_min = u32::min(self.segment_used_rows(), limit.segment_threshold());
        let update = self.split_segment(po2, segment_threshold_min)?;

        Ok(Some(update))
    }

    pub fn run_jit(&mut self) -> Result<()> {
        todo!()
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
        Ok(self.state(limit.segment_po2.try_into().unwrap()))
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
        tracing::debug!("split({} >= {segment_threshold}", self.segment_used_rows());

        let partial_image = self.pager.commit();
        let used_rows = self.segment_used_rows();

        let blocks = self.get_blocks();
        let update = SegmentUpdate {
            update_partial_image: partial_image,
            access_page_indexes: self.pager.page_indexes(),
            input_digest: self.input_digest,
            output_digest: self.output_digest,
            read_record: std::mem::take(&mut self.read_record),
            write_record: std::mem::take(&mut self.write_record),
            used_rows,
            insn_counter: self.insn_counter,
            terminate_state: self.terminate_state,
            segment_threshold,
            po2: segment_po2 as u32,
            index: self.segment_counter as u64,
            povw_nonce: self.povw_nonce(self.segment_counter),
            blocks: blocks.clone(),
        };

        // NOTE: There is no reasonable scenario where a session will have more than 4B
        // segments, but its possible.
        self.segment_counter = self
            .segment_counter
            .checked_add(1)
            .context("segment_counter overflow")?;

        let total_rows = 1u64 << segment_po2;
        let padding = total_rows - used_rows as u64;
        self.row_info.count += total_rows;
        self.row_info.insn_count += self.insn_counter as u64;
        self.row_info.padding_count += padding;
        self.row_info.row_points += blocks.row_points();
        blocks.add_counts(&mut self.row_info.block_counts);

        self.preflight_user_cycles = 0;
        self.insn_counter = 0;
        self.pager.reset();
        self.block_tracker = Default::default();

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

    /// Compute the [ExecutorResult] from the initial to the current state of the executor.
    pub fn state(&self, po2: u32) -> ExecutorResult {
        ExecutorResult {
            segments: self.segment_counter as u64 + 1,
            pre_image: self.initial_image.clone(),
            post_image: self.pager.image.clone().into(),
            row_count: self.row_info.count,
            padding_row_count: self.row_info.padding_count,
            insn_count: self.row_info.insn_count,
            ecall_metrics: self.ecall_metrics.clone(),
            block_counts: self.row_info.block_counts,
            output: self.output_digest,
            terminate_state: self.terminate_state,
            po2,
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
            insn_counter: self.insn_counter,
            terminate_state: self.terminate_state,
            used_rows: self.segment_used_rows(),
            segment_threshold,
            po2: po2 as u32,
            index: index as u64,
            povw_nonce: self.povw_nonce(index),
            blocks: self.get_blocks(),
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

    fn segment_used_rows(&self) -> u32 {
        let blocks = self
            .block_tracker
            .get_blocks(self.insn_counter, self.pager.touched_pages());
        blocks.row_points().div_ceil(POINTS_PER_ROW) as u32
    }

    fn should_split(&self, segment_threshold: u32) -> bool {
        let blocks = self
            .block_tracker
            .get_blocks(self.preflight_user_cycles, self.pager.touched_pages());
        if blocks.row_points().div_ceil(POINTS_PER_ROW) as u32 > segment_threshold {
            tracing::debug!("block_tracker blocks = {blocks:?}");
            true
        } else {
            false
        }
    }

    fn get_blocks(&self) -> super::block_tracker::BlockCollection {
        let blocks = self
            .block_tracker
            .get_blocks(self.preflight_user_cycles, self.pager.touched_pages());
        tracing::debug!("block_tracker blocks = {blocks:?}");
        blocks
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
    fn trace_instruction(&mut self, kind: InsnKind, decoded: &DecodedInstruction) {
        if unlikely(tracing::enabled!(tracing::Level::TRACE)) {
            tracing::trace!(
                "{:?}> {:#010x}  {}",
                self.pc,
                decoded.insn,
                super::rv32im::disasm(kind, decoded)
            );
        }
        if unlikely(tracing::enabled!(tracing::Level::DEBUG)) {
            self.ring.push((self.pc, kind, decoded.clone()));
        }
    }

    fn get_row_points(&self) -> u64 {
        let blocks = self
            .block_tracker
            .get_blocks(self.insn_counter, self.pager.touched_pages());
        self.row_info.row_points + blocks.row_points()
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
        self.block_tracker.track_pc(self.pc.0);

        self.trace_instruction(kind, decoded);
        if unlikely(!self.trace.is_empty()) {
            self.trace(TraceEvent::InstructionStart {
                cycle: self.get_row_points(),
                pc: self.pc.0,
                insn: decoded.insn,
            })?;
        }
        Ok(())
    }

    #[inline(always)]
    fn on_insn_end(&mut self, #[allow(unused_variables)] kind: InsnKind) -> Result<()> {
        self.block_tracker.track_instr(kind);

        self.preflight_user_cycles += 1;
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
        self.preflight_user_cycles += 1;

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

        self.block_tracker.track_ecall_terminate();

        Ok(())
    }

    fn host_read(&mut self, fd: u32, buf: &mut [u8]) -> Result<u32> {
        // NOTE: This clone is required to allow host_read to have mutable access to self.
        let rlen = self.syscall_handler.clone().host_read(self, fd, buf)?;
        if rlen as usize > buf.len() {
            bail!("syscall returned invalid length: fd={fd}");
        }
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
        self.preflight_user_cycles += 1;
    }

    fn on_poseidon2_cycle(&mut self, _cur_state: CycleState, _p2: &Poseidon2State) {
        self.preflight_user_cycles += 1;
    }

    fn ecall_bigint(&mut self) -> Result<()> {
        let verify_program_size = bigint::ecall_execute(self)?;

        self.block_tracker
            .track_ecall_bigint(verify_program_size as u64);

        self.preflight_user_cycles += (verify_program_size + 1) as u32;

        Ok(())
    }

    fn ecall_poseidon2(&mut self) -> Result<()> {
        let mut p2 = Poseidon2::load_ecall(self)?;

        self.block_tracker.track_ecall_poseidon2(p2.count as u64);
        self.preflight_user_cycles += p2.count;

        p2.rest_with_mix(self, CycleState::Decode, |p2, _, _| {
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

    fn on_ecall_read_end(&mut self, read_bytes: u64, read_words: u64) {
        self.block_tracker.track_ecall_read(read_bytes, read_words);
        self.preflight_user_cycles += (read_bytes + read_words) as u32;
    }

    fn on_ecall_write_end(&mut self) {
        self.block_tracker.track_ecall_write();
    }

    fn on_user_ecall(&mut self) {
        self.block_tracker.track_user_ecall();
    }

    fn on_trap(&mut self) {
        self.preflight_user_cycles += 1;
        self.block_tracker.track_trap();
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

    fn get_rows(&self) -> u64 {
        self.row_info.count + self.segment_used_rows() as u64
    }

    fn get_pc(&self) -> u32 {
        self.user_pc.0
    }
}
