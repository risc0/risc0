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

use std::{cmp::min, fmt::Write as _};

use anyhow::{Result, anyhow, bail};
use risc0_binfmt::{ByteAddr, WordAddr};

use super::{
    platform::*,
    poseidon2::{Poseidon2, Poseidon2State},
    rv32im::{EmuContext, Emulator, Exception, InsnKind},
    sha2::{self, Sha2State},
};
use crate::EcallKind;

#[derive(Clone, Copy, Eq, PartialEq)]
pub(crate) enum LoadOp {
    Peek,
    Load,
    Record,
}

pub(crate) trait Risc0Context {
    fn circuit_version(&self) -> u32;

    /// Get the program counter
    fn get_pc(&self) -> ByteAddr;

    /// Set the program counter
    fn set_pc(&mut self, addr: ByteAddr);

    // Set the user mode program counter
    fn set_user_pc(&mut self, addr: ByteAddr);

    /// Get the machine mode
    fn get_machine_mode(&self) -> u32;

    /// Set the machine mode
    fn set_machine_mode(&mut self, mode: u32);

    fn on_insn_start(
        &mut self,
        kind: InsnKind,
        decoded: &super::rv32im::DecodedInstruction,
    ) -> Result<()>;

    fn on_insn_end(&mut self, kind: InsnKind) -> Result<()>;

    fn load_u32(&mut self, op: LoadOp, addr: WordAddr) -> Result<u32>;

    #[inline(always)]
    fn load_register(&mut self, op: LoadOp, base: WordAddr, idx: usize) -> Result<u32> {
        self.load_u32(op, base + idx)
    }

    #[inline(always)]
    fn load_machine_register(&mut self, op: LoadOp, idx: usize) -> Result<u32> {
        self.load_register(op, MACHINE_REGS_ADDR.waddr(), idx)
    }

    #[inline(always)]
    fn load_aligned_addr_from_machine_register(
        &mut self,
        op: LoadOp,
        idx: usize,
    ) -> Result<WordAddr> {
        check_aligned_addr(ByteAddr(self.load_machine_register(op, idx)?))
    }

    #[inline(always)]
    fn load_u8(&mut self, op: LoadOp, addr: ByteAddr) -> Result<u8> {
        let word = self.load_u32(op, addr.waddr())?;
        let bytes = word.to_le_bytes();
        let byte_offset = addr.subaddr() as usize;
        Ok(bytes[byte_offset])
    }

    #[inline(always)]
    fn load_region(&mut self, op: LoadOp, addr: ByteAddr, size: usize) -> Result<Vec<u8>> {
        let mut region = Vec::with_capacity(size);
        if addr.is_aligned() && size.is_multiple_of(WORD_SIZE) {
            let mut waddr = addr.waddr();
            for _ in (0..size).step_by(WORD_SIZE) {
                let word = self.load_u32(op, waddr.postfix_inc())?;
                region.extend_from_slice(&word.to_le_bytes());
            }
        } else {
            for i in 0..size {
                region.push(self.load_u8(op, addr + i)?);
            }
        }
        Ok(region)
    }

    fn store_u32(&mut self, addr: WordAddr, word: u32) -> Result<()>;

    #[inline(always)]
    fn store_region(&mut self, addr: ByteAddr, input: &[u8]) -> Result<()> {
        let size = input.len();
        if addr.is_aligned() && size.is_multiple_of(WORD_SIZE) {
            let mut waddr = addr.waddr();
            for i in (0..size).step_by(WORD_SIZE) {
                self.store_u32(
                    waddr.postfix_inc(),
                    u32::from_le_bytes(input[i..(i + WORD_SIZE)].try_into().unwrap()),
                )?;
            }
        } else {
            for (i, byte) in input.iter().enumerate() {
                self.store_u8(addr + i, *byte)?;
            }
        }
        Ok(())
    }

    #[inline(always)]
    fn store_u8(&mut self, addr: ByteAddr, byte: u8) -> Result<()> {
        let byte_offset = addr.subaddr() as usize;
        let word = self.load_u32(LoadOp::Record, addr.waddr())?;
        let mut bytes = word.to_le_bytes();
        bytes[byte_offset] = byte;
        let word = u32::from_le_bytes(bytes);
        self.store_u32(addr.waddr(), word)
    }

    #[inline(always)]
    fn store_register(&mut self, base: WordAddr, idx: usize, word: u32) -> Result<()> {
        self.store_u32(base + idx, word)
    }

    fn suspend(&mut self) -> Result<()> {
        // default no-op
        Ok(())
    }

    fn resume(&mut self) -> Result<()> {
        // default no-op
        Ok(())
    }

    fn trap_rewind(&mut self) {
        // default no-op
    }

    fn trap(&mut self, _cause: Exception) {
        // default no-op
    }

    /// Record what was read during execution so we can replay
    fn host_read(&mut self, fd: u32, buf: &mut [u8]) -> Result<u32>;

    /// For writes, just pass through, record rlen only
    fn host_write(&mut self, fd: u32, buf: &[u8]) -> Result<u32>;

    fn on_terminate(&mut self, a0: u32, a1: u32) -> Result<()>;

    fn on_ecall_cycle(
        &mut self,
        cur: CycleState,
        next: CycleState,
        s0: u32,
        s1: u32,
        s2: u32,
        kind: EcallKind,
    ) -> Result<()>;

    fn on_sha2_cycle(&mut self, cur_state: CycleState, sha2: &Sha2State);

    fn on_poseidon2_cycle(&mut self, cur_state: CycleState, p2: &Poseidon2State);

    fn ecall_bigint(&mut self) -> Result<()>;
}

#[cfg(test)]
pub struct TestRisc0Context {
    pc: ByteAddr,
    user_pc: ByteAddr,
    machine_mode: u32,
    memory: std::collections::BTreeMap<WordAddr, u32>,
}

#[cfg(test)]
impl Default for TestRisc0Context {
    fn default() -> Self {
        Self {
            pc: ByteAddr(0),
            user_pc: ByteAddr(0),
            machine_mode: 0,
            memory: Default::default(),
        }
    }
}

#[cfg(test)]
impl TestRisc0Context {
    pub fn assert_uninit(&self, addr: ByteAddr) {
        assert_eq!(self.memory.get(&addr.waddr()), None);
    }
}

#[cfg(test)]
impl Risc0Context for TestRisc0Context {
    fn circuit_version(&self) -> u32 {
        RV32IM_V2_CIRCUIT_VERSION
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

    fn on_insn_start(
        &mut self,
        _kind: InsnKind,
        _decoded: &super::rv32im::DecodedInstruction,
    ) -> Result<()> {
        Ok(())
    }

    fn on_insn_end(&mut self, _kind: InsnKind) -> Result<()> {
        Ok(())
    }

    fn load_u32(&mut self, _op: LoadOp, addr: WordAddr) -> Result<u32> {
        Ok(self.memory.get(&addr).copied().unwrap_or_else(|| {
            panic!(
                "load_u32 of address 0x{:x} which has not been written to",
                addr.0
            )
        }))
    }

    fn store_u32(&mut self, addr: WordAddr, word: u32) -> Result<()> {
        self.memory.insert(addr, word);
        Ok(())
    }

    /// We need our own implementation in order to avoid uninitialized read of the u32 containing
    /// the u8.
    fn store_u8(&mut self, addr: ByteAddr, byte: u8) -> Result<()> {
        let byte_offset = addr.subaddr() as usize;
        let word = self.memory.get(&addr.waddr()).copied().unwrap_or(0);
        let mut bytes = word.to_le_bytes();
        bytes[byte_offset] = byte;
        let word = u32::from_le_bytes(bytes);
        self.store_u32(addr.waddr(), word)
    }

    fn host_read(&mut self, _fd: u32, _buf: &mut [u8]) -> Result<u32> {
        unimplemented!()
    }

    fn host_write(&mut self, _fd: u32, _buf: &[u8]) -> Result<u32> {
        unimplemented!()
    }

    fn on_terminate(&mut self, _a0: u32, _a1: u32) -> Result<()> {
        Ok(())
    }

    fn on_ecall_cycle(
        &mut self,
        _cur: CycleState,
        _next: CycleState,
        _s0: u32,
        _s1: u32,
        _s2: u32,
        _kind: super::r0vm::EcallKind,
    ) -> Result<()> {
        Ok(())
    }

    fn on_sha2_cycle(&mut self, _cur_state: CycleState, _sha2: &super::sha2::Sha2State) {}

    fn on_poseidon2_cycle(
        &mut self,
        _cur_state: CycleState,
        _p2: &super::poseidon2::Poseidon2State,
    ) {
    }

    fn ecall_bigint(&mut self) -> Result<()> {
        unimplemented!()
    }
}

fn check_aligned_addr(addr: ByteAddr) -> Result<WordAddr> {
    addr.waddr_aligned()
        .ok_or_else(|| anyhow!("{addr:?} is an unaligned address"))
}

pub struct Risc0Machine<'a, C: Risc0Context> {
    ctx: &'a mut C,
}

impl<'a, C: Risc0Context> Risc0Machine<'a, C> {
    #[inline(always)]
    pub fn step(emu: &mut Emulator, ctx: &'a mut C) -> Result<()> {
        emu.step(&mut Risc0Machine { ctx })
    }

    pub fn suspend(ctx: &'a mut C) -> Result<()> {
        let mut this = Risc0Machine { ctx };
        this.store_memory(SUSPEND_PC_ADDR.waddr(), this.ctx.get_pc().0)?;
        this.store_memory(SUSPEND_MODE_ADDR.waddr(), this.ctx.get_machine_mode())?;
        this.ctx.suspend()
    }

    pub fn resume(ctx: &'a mut C) -> Result<()> {
        let circuit_version = ctx.circuit_version();
        let mut this = Risc0Machine { ctx };
        let pc = guest_addr(this.load_memory(SUSPEND_PC_ADDR.waddr())?)?;
        let machine_mode = this.load_memory(SUSPEND_MODE_ADDR.waddr())?;
        if circuit_version == RV32IM_M3_CIRCUIT_VERSION {
            this.store_memory(RV32IM_VERSION_ADDR.waddr(), RV32IM_M3_CIRCUIT_VERSION)?;
        }
        // tracing::debug!("resume(entry: {pc:?}, mode: {machine_mode})");
        this.ctx.set_pc(pc);
        this.ctx.set_machine_mode(machine_mode);
        this.ctx.resume()
    }

    fn is_machine_mode(&self) -> bool {
        self.ctx.get_machine_mode() != 0
    }

    fn next_pc(&mut self) {
        self.ctx.set_pc(self.ctx.get_pc() + WORD_SIZE);
    }

    fn machine_ecall(&mut self) -> Result<bool> {
        match self.load_register(REG_A7)? {
            HOST_ECALL_TERMINATE => self.ecall_terminate(),
            HOST_ECALL_READ => self.ecall_read(),
            HOST_ECALL_WRITE => self.ecall_write(),
            HOST_ECALL_POSEIDON2 => self.ecall_poseidon2(),
            HOST_ECALL_SHA2 => self.ecall_sha2(),
            HOST_ECALL_BIGINT => self.ecall_bigint(),
            _ => unimplemented!(),
        }
    }

    fn user_ecall(&mut self) -> Result<bool> {
        let dispatch_addr = guest_addr(self.load_memory(ECALL_DISPATCH_ADDR.waddr())?)?;
        // tracing::trace!("user_ecall> addr: {dispatch_addr:?}");
        if !dispatch_addr.is_aligned() || !is_kernel_memory(dispatch_addr) {
            return self.trap(Exception::UserEnvCall(dispatch_addr));
        }

        self.enter_trap(dispatch_addr)?;
        Ok(true)
    }

    fn ecall_terminate(&mut self) -> Result<bool> {
        // tracing::trace!("ecall_terminate");
        self.ctx.on_ecall_cycle(
            CycleState::MachineEcall,
            CycleState::Terminate,
            0,
            0,
            0,
            EcallKind::Terminate,
        )?;
        let a0 = self.load_register(REG_A0)?;
        let a1 = self.load_register(REG_A1)?;
        self.ctx.on_terminate(a0, a1)?;
        self.next_pc();
        self.ctx.on_ecall_cycle(
            CycleState::Terminate,
            CycleState::Suspend,
            0,
            0,
            0,
            EcallKind::Terminate,
        )?;
        Ok(false)
    }

    fn ecall_read(&mut self) -> Result<bool> {
        self.ctx.on_ecall_cycle(
            CycleState::MachineEcall,
            CycleState::HostReadSetup,
            0,
            0,
            0,
            EcallKind::Read,
        )?;
        let mut cur_state = CycleState::HostReadSetup;
        let fd = self.load_register(REG_A0)?;
        let mut ptr = ByteAddr(self.load_register(REG_A1)?);
        let len = self.load_register(REG_A2)?;
        if ptr + len < ptr {
            bail!("Invalid length in host read: {len}");
        }
        if len > MAX_IO_BYTES {
            bail!("Invalid length (too big) in host read: {len}");
        }
        if len > 0 {
            guest_addr(ptr.0)?;
        }
        // tracing::trace!("ecall_read({fd}, {ptr:?}, {len})");
        // TODO(victor/perf): This line is implicated in about 5% of execution time, but there is
        // something funky about that because it claims the Rust allocator is calling host_read.
        let mut bytes = vec![0u8; len as usize];
        let mut rlen = self.ctx.host_read(fd, &mut bytes)?;
        self.store_register(REG_A0, rlen)?;
        // tracing::trace!("rlen: {rlen}");
        if rlen == 0 {
            self.next_pc();
        }

        fn next_io_state(ptr: ByteAddr, rlen: u32) -> CycleState {
            if rlen == 0 {
                CycleState::Decode
            } else if !ptr.is_aligned() || rlen < WORD_SIZE as u32 {
                CycleState::HostReadBytes
            } else {
                CycleState::HostReadWords
            }
        }

        macro_rules! add_cycle {
            ($ptr:expr, $rlen:expr) => {{
                let next_state = next_io_state($ptr, $rlen);
                self.ctx.on_ecall_cycle(
                    cur_state,
                    next_state,
                    $ptr.waddr().0,
                    $ptr.subaddr(),
                    $rlen,
                    EcallKind::Read,
                )?;
                cur_state = next_state;
            }};
        }

        add_cycle!(ptr, rlen);

        let mut i = 0;

        while rlen > 0 && !ptr.is_aligned() {
            // tracing::trace!("prefix");
            self.ctx.store_u8(ptr, bytes[i])?;
            ptr += 1u32;
            i += 1;
            rlen -= 1;
            if rlen == 0 {
                self.next_pc();
            }

            add_cycle!(ptr, rlen);
        }

        // HERE!
        while rlen >= MAX_IO_WORDS {
            let words = min(rlen / MAX_IO_WORDS, MAX_IO_WORDS);
            // tracing::trace!("body: {words}");
            for j in 0..MAX_IO_WORDS {
                if j < words {
                    let word = u32::from_le_bytes(bytes[i..i + WORD_SIZE].try_into()?);
                    // tracing::trace!("store: {i}, {j}, {word:#010x} -> {ptr:?}");
                    self.store_memory(ptr.waddr(), word)?;
                    ptr += WORD_SIZE;
                    i += WORD_SIZE;
                    rlen -= WORD_SIZE as u32;
                } else {
                    // tracing::trace!("store: {:#010x} -> null", 0);
                    self.store_memory(SAFE_WRITE_ADDR.waddr() + j, 0)?;
                }
            }

            if rlen == 0 {
                self.next_pc();
            }

            add_cycle!(ptr, rlen);
        }

        while rlen > 0 {
            // tracing::trace!("suffix");
            self.ctx.store_u8(ptr, bytes[i])?;
            ptr += 1u32;
            i += 1;
            rlen -= 1;

            if rlen == 0 {
                self.next_pc();
            }

            add_cycle!(ptr, rlen);
        }

        Ok(false)
    }

    fn ecall_write(&mut self) -> Result<bool> {
        tracing::trace!("ecall_write");
        self.ctx.on_ecall_cycle(
            CycleState::MachineEcall,
            CycleState::HostWrite,
            0,
            0,
            0,
            EcallKind::Write,
        )?;
        let fd = self.load_register(REG_A0)?;
        let ptr = ByteAddr(self.load_register(REG_A1)?);
        let len = self.load_register(REG_A2)?;
        if ptr + len < ptr {
            bail!("Invalid length in host write: {len}");
        }
        if len > MAX_IO_BYTES {
            bail!("Invalid length (too big) in host write: {len}");
        }
        let bytes = self.ctx.load_region(LoadOp::Peek, ptr, len as usize)?;
        let rlen = self.ctx.host_write(fd, &bytes)?;
        self.store_register(REG_A0, rlen)?;
        self.next_pc();
        self.ctx.on_ecall_cycle(
            CycleState::HostWrite,
            CycleState::Decode,
            0,
            0,
            0,
            EcallKind::Write,
        )?;
        Ok(false)
    }

    fn ecall_poseidon2(&mut self) -> Result<bool> {
        self.next_pc();
        self.ctx.on_ecall_cycle(
            CycleState::MachineEcall,
            CycleState::PoseidonEntry,
            0,
            0,
            0,
            EcallKind::Poseidon2,
        )?;
        Poseidon2::ecall(self.ctx)?;
        Ok(false)
    }

    fn ecall_sha2(&mut self) -> Result<bool> {
        self.next_pc();
        self.ctx.on_ecall_cycle(
            CycleState::MachineEcall,
            CycleState::ShaEcall,
            0,
            0,
            0,
            EcallKind::Sha2,
        )?;
        sha2::ecall(self.ctx)?;
        Ok(false)
    }

    fn ecall_bigint(&mut self) -> Result<bool> {
        self.next_pc();
        self.ctx.on_ecall_cycle(
            CycleState::MachineEcall,
            CycleState::BigIntEcall,
            0,
            0,
            0,
            EcallKind::BigInt,
        )?;
        self.ctx.ecall_bigint()?;
        Ok(false)
    }

    fn enter_trap(&mut self, dispatch_addr: ByteAddr) -> Result<()> {
        if self.is_machine_mode() {
            bail!("Illegal trap in machine mode");
        }
        let pc = self.ctx.get_pc();
        self.store_memory(MEPC_ADDR.waddr(), pc.0)?;
        self.ctx.set_pc(dispatch_addr);
        self.ctx.set_user_pc(pc);
        self.ctx.set_machine_mode(1);
        Ok(())
    }

    fn regs_base_addr(&self) -> WordAddr {
        if self.is_machine_mode() {
            MACHINE_REGS_ADDR.waddr()
        } else {
            USER_REGS_ADDR.waddr()
        }
    }

    fn dump_registers(&mut self, is_machine_mode: bool) -> Result<()> {
        let base_addr = if is_machine_mode {
            tracing::trace!("machine registers:");
            MACHINE_REGS_ADDR.waddr()
        } else {
            tracing::trace!("user registers:");
            USER_REGS_ADDR.waddr()
        };
        for i in 0..REG_MAX / 4 {
            let mut str = String::new();
            for j in 0..4 {
                let idx = i * 4 + j;
                let word = self.ctx.load_u32(LoadOp::Peek, base_addr + idx)?;
                write!(str, "  x{idx}: {word:#010x}")?;
            }
            tracing::trace!("  {str}");
        }
        Ok(())
    }
}

impl<T: Risc0Context> EmuContext for Risc0Machine<'_, T> {
    fn ecall(&mut self) -> Result<bool> {
        if self.is_machine_mode() {
            self.machine_ecall()
        } else {
            self.user_ecall()
        }
    }

    fn mret(&mut self) -> Result<bool> {
        if !self.is_machine_mode() {
            bail!("Illegal mret in user mode");
        }
        let dispatch_addr = guest_addr(self.load_memory(MEPC_ADDR.waddr())?)?;
        self.ctx.set_pc(dispatch_addr + WORD_SIZE);
        self.ctx.set_machine_mode(0);
        Ok(true)
    }

    fn trap(&mut self, cause: Exception) -> Result<bool> {
        self.ctx.trap_rewind();
        if let Exception::Breakpoint = cause {
            self.dump_registers(true)?;
            self.dump_registers(false)?;
        }
        if let Exception::IllegalInstruction(_, _) = cause {
            self.dump_registers(true)?;
            self.dump_registers(false)?;
        }
        let dispatch_addr =
            ByteAddr(self.load_memory(TRAP_DISPATCH_ADDR.waddr() + cause.as_u32())?);
        if !dispatch_addr.is_aligned() || !is_kernel_memory(dispatch_addr) {
            bail!("Invalid trap address: {dispatch_addr:?}, cause: {cause:?}");
        }
        self.enter_trap(dispatch_addr)?;
        self.ctx.trap(cause);
        Ok(false)
    }

    fn on_insn_decoded(
        &mut self,
        kind: InsnKind,
        decoded: &super::rv32im::DecodedInstruction,
    ) -> Result<()> {
        self.ctx.on_insn_start(kind, decoded)
    }

    fn on_normal_end(&mut self, kind: InsnKind) -> Result<()> {
        self.ctx.on_insn_end(kind)
    }

    fn get_pc(&self) -> ByteAddr {
        self.ctx.get_pc()
    }

    fn set_pc(&mut self, addr: ByteAddr) {
        self.ctx.set_pc(addr);
    }

    #[inline(always)]
    fn load_register(&mut self, idx: usize) -> Result<u32> {
        // tracing::trace!("load_reg: x{idx}");
        let base = self.regs_base_addr();
        self.ctx.load_register(LoadOp::Record, base, idx)
    }

    #[inline(always)]
    fn store_register(&mut self, idx: usize, word: u32) -> Result<()> {
        // tracing::trace!("store_reg: x{idx} <= {word:#010x}");
        let base = self.regs_base_addr();

        // To avoid the use of a degree in the circuit, all writes to REG_ZERO
        // are shunted to a memory location that is never read from.
        if idx == REG_ZERO {
            self.ctx.store_u32(base + REG_MAX * 2, word)
        } else {
            self.ctx.store_register(base, idx, word)
        }
    }

    #[inline(always)]
    fn load_memory(&mut self, addr: WordAddr) -> Result<u32> {
        self.ctx.load_u32(LoadOp::Record, addr)
    }

    #[inline(always)]
    fn store_memory(&mut self, addr: WordAddr, word: u32) -> Result<()> {
        self.ctx.store_u32(addr, word)
    }

    fn check_insn_load(&self, addr: ByteAddr) -> bool {
        !(addr < ZERO_PAGE_END_ADDR || (!self.is_machine_mode() && addr >= KERNEL_START_ADDR))
    }

    fn check_data_load(&self, addr: ByteAddr) -> bool {
        // self.is_machine_mode() || is_user_memory(addr)
        addr >= ZERO_PAGE_END_ADDR && self.is_machine_mode() || is_user_memory(addr)
        // self.check_insn_load(addr)
    }

    fn check_data_store(&self, addr: ByteAddr) -> bool {
        self.check_data_load(addr)
    }
}

pub(crate) fn guest_addr(addr: u32) -> Result<ByteAddr> {
    let addr = ByteAddr(addr);
    if addr < ZERO_PAGE_END_ADDR {
        Err(anyhow!("{addr:?} is an invalid guest address"))
    } else {
        Ok(addr)
    }
}
