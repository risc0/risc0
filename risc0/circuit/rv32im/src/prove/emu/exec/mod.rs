// Copyright 2024 RISC Zero, Inc.
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

#[cfg(test)]
mod tests;

use std::mem;

use anyhow::{bail, Result};
use risc0_binfmt::MemoryImage;
use risc0_zkp::core::log2_ceil;
use risc0_zkvm_platform::{
    memory::is_guest_memory,
    syscall::{
        ecall, halt,
        reg_abi::{REG_A0, REG_A1, REG_A2, REG_MAX, REG_T0},
    },
    WORD_SIZE,
};

use super::{
    addr::{ByteAddr, WordAddr},
    pager::PagedMemory,
    rv32im::{DecodedInstruction, EmuContext, Emulator, InsnKind, TrapCause},
    Segment, SyscallRecord, SYSTEM_START,
};

pub const DEFAULT_SEGMENT_PO2: usize = 20;

/// A host-side implementation of a system call.
pub trait Syscall {
    /// Invokes the system call.
    fn syscall(
        &self,
        syscall: &str,
        ctx: &mut dyn SyscallContext,
        guest_buf: &mut [u32],
    ) -> Result<(u32, u32)>;
}

/// Access to memory and machine state for syscalls.
pub trait SyscallContext {
    /// Loads the value of the given register, e.g. REG_A0.
    fn peek_register(&mut self, idx: usize) -> Result<u32>;

    /// Loads an individual word from memory.
    fn peek_u32(&mut self, addr: ByteAddr) -> Result<u32>;

    /// Loads an individual byte from memory.
    fn peek_u8(&mut self, addr: ByteAddr) -> Result<u8>;

    /// Loads bytes from the given region of memory.
    fn peek_region(&mut self, addr: ByteAddr, size: u32) -> Result<Vec<u8>> {
        let mut region = Vec::new();
        for i in 0..size {
            region.push(self.peek_u8(addr + i)?);
        }
        Ok(region)
    }
}

pub struct Executor<'a, S: Syscall> {
    pager: PagedMemory,
    exit_code: Option<u32>,
    pc: ByteAddr,
    cycles: usize,
    syscalls: Vec<SyscallRecord>,
    syscall_handler: &'a S,
}

impl<'a, S: Syscall> SyscallContext for Executor<'a, S> {
    fn peek_register(&mut self, idx: usize) -> Result<u32> {
        if idx >= REG_MAX {
            bail!("invalid register: x{idx}");
        }
        self.pager.peek(SYSTEM_START + idx)
    }

    fn peek_u32(&mut self, addr: ByteAddr) -> Result<u32> {
        let addr = self.check_guest_addr(addr)?;
        self.pager.peek(addr.waddr())
    }

    fn peek_u8(&mut self, addr: ByteAddr) -> Result<u8> {
        let addr = self.check_guest_addr(addr)?;
        let word = self.pager.peek(addr.waddr())?;
        let bytes = word.to_le_bytes();
        let byte_offset = addr.0 as usize % WORD_SIZE;
        Ok(bytes[byte_offset])
    }
}

impl<'a, S: Syscall> Executor<'a, S> {
    fn new(image: MemoryImage, syscall_handler: &'a S) -> Self {
        let pc = ByteAddr(image.pc);
        Self {
            pager: PagedMemory::new(image),
            exit_code: None,
            pc,
            cycles: 0,
            syscalls: Vec::new(),
            syscall_handler,
        }
    }

    fn run(&mut self, segment_po2: usize, max_cycles: usize) -> Result<Vec<Segment>> {
        // Leave enough space at the end of a segment so that we don't overflow
        // This needs to be the worst case number of cycles needed to run a single step.
        let segment_threshold = (1 << segment_po2) - 10000;

        let mut segments = Vec::new();
        let mut emu = Emulator::new();
        let mut prev_pc = self.pc;
        let mut total_cycles = 0;

        while self.exit_code.is_none() && total_cycles < max_cycles {
            let paging_cycles = self.pager.get_paging_cycles();
            let segment_cycles = self.cycles + paging_cycles;
            if segment_cycles >= segment_threshold {
                tracing::debug!("split: {} + {}", self.cycles, paging_cycles);
                let (pre_state, partial_image, post_state) = self.pager.commit(prev_pc);
                segments.push(Segment {
                    partial_image,
                    pre_state,
                    post_state,
                    syscalls: mem::take(&mut self.syscalls),
                    insn_cycles: self.cycles,
                    po2: segment_po2,
                });
                self.pager.clear();
                prev_pc = self.pc;
                total_cycles += self.cycles;
                self.cycles = 0;
            }
            emu.step(self)?;
        }

        let (pre_state, partial_image, post_state) = self.pager.commit(prev_pc);
        let segment_cycles = self.cycles + self.pager.get_paging_cycles();
        let po2 = log2_ceil(segment_cycles.next_power_of_two()).try_into()?; // TODO
        segments.push(Segment {
            partial_image,
            pre_state,
            post_state,
            syscalls: mem::take(&mut self.syscalls),
            insn_cycles: self.cycles,
            po2,
        });

        Ok(segments)
    }

    fn ecall_halt(&mut self) -> Result<bool> {
        let a0 = self.load_register(REG_A0)?;
        let output_ptr = ByteAddr(self.load_register(REG_A1)?);
        self.check_guest_addr(output_ptr)?;

        let halt_type = a0 & 0xff;
        let user_exit = (a0 >> 8) & 0xff;

        self.exit_code = match halt_type {
            halt::TERMINATE => Some(user_exit),
            halt::PAUSE => todo!(),
            _ => bail!("Illegal halt type: {halt_type}"),
        };

        Ok(true)
    }

    fn ecall_software(&mut self) -> Result<bool> {
        let into_guest_ptr = ByteAddr(self.load_register(REG_A0)?);
        let into_guest_len = self.load_register(REG_A1)?;
        let name_ptr = ByteAddr(self.load_register(REG_A2)?);
        let syscall_name = self.load_string(name_ptr)?;
        let name_end = name_ptr + syscall_name.len();
        self.check_guest_addr(name_ptr)?;
        self.check_guest_addr(name_end)?;

        // let chunks = align_up(guest_len as usize, WORD_SIZE);
        let mut guest_buf = vec![0u32; into_guest_len as usize];

        let (a0, a1) = self
            .syscall_handler
            .syscall(&syscall_name, self, &mut guest_buf)?;

        // The guest uses a null pointer to indicate that a transfer from host
        // to guest is not needed.
        if !into_guest_ptr.is_null() {
            self.check_guest_addr(into_guest_ptr)?;
            self.check_guest_addr(into_guest_ptr + into_guest_len)?;
            self.store_region(into_guest_ptr, bytemuck::cast_slice(&guest_buf))?
        }

        self.store_register(REG_A0, a0)?;
        self.store_register(REG_A1, a1)?;

        Ok(true)
    }

    fn ecall_sha(&self) -> Result<bool> {
        todo!()
    }

    fn ecall_bigint(&self) -> Result<bool> {
        todo!()
    }

    fn check_guest_addr(&mut self, addr: ByteAddr) -> Result<ByteAddr> {
        if !is_guest_memory(addr.0) && addr.0 != 0 {
            bail!("{addr:?} is an invalid guest address");
        }
        Ok(addr)
    }

    fn load_string(&mut self, mut addr: ByteAddr) -> Result<String> {
        // tracing::trace!("load_string: 0x{addr:08x}");
        let mut buf = Vec::new();
        loop {
            let bytes = self.peek_u8(addr)?;
            if bytes == 0 {
                break;
            }
            buf.push(bytes);
            addr += 1u32;
        }
        Ok(String::from_utf8(buf)?)
    }

    fn store_u8(&mut self, addr: ByteAddr, byte: u8) -> Result<()> {
        let byte_offset = addr.0 as usize % WORD_SIZE;
        let word = self.peek_u32(addr)?;
        let mut bytes = word.to_le_bytes();
        bytes[byte_offset] = byte;
        let word = u32::from_le_bytes(bytes);
        self.store_memory(addr.waddr(), word)
    }

    fn store_region(&mut self, addr: ByteAddr, slice: &[u8]) -> Result<()> {
        // tracing::trace!("store_region: 0x{addr:08x}");
        slice
            .iter()
            .enumerate()
            .try_for_each(|(i, x)| self.store_u8(addr + i, *x))?;
        Ok(())
    }
}

impl<'a, S: Syscall> EmuContext for Executor<'a, S> {
    fn ecall(&mut self) -> Result<bool> {
        self.pc += WORD_SIZE;
        match self.load_register(REG_T0)? {
            ecall::HALT => self.ecall_halt(),
            ecall::SOFTWARE => self.ecall_software(),
            ecall::SHA => self.ecall_sha(),
            ecall::BIGINT => self.ecall_bigint(),
            ecall => bail!("Unknown ecall {ecall:?}"),
        }
    }

    fn mret(&self) -> Result<bool> {
        unimplemented!()
    }

    fn trap(&self, cause: TrapCause) -> Result<bool> {
        bail!("Trap: {cause:08x?}");
    }

    fn on_insn_decoded(&self, kind: InsnKind, _decoded: &DecodedInstruction) {
        tracing::trace!("{:?}> {kind:?}", self.pc);
    }

    fn on_normal_end(&mut self, _kind: InsnKind, _decoded: &DecodedInstruction) {
        // TODO: not all instructions are 1 cycle
        self.cycles += 1;
    }

    fn get_pc(&self) -> ByteAddr {
        self.pc
    }

    fn set_pc(&mut self, addr: ByteAddr) {
        self.pc = addr;
    }

    fn load_register(&mut self, idx: usize) -> Result<u32> {
        tracing::trace!("load_reg: x{idx}");
        self.pager.load(SYSTEM_START + idx)
    }

    fn store_register(&mut self, idx: usize, data: u32) -> Result<()> {
        if idx != 0 {
            tracing::trace!("store_reg: x{idx} <= 0x{data:08x}");
            self.pager.store(SYSTEM_START + idx, data)?;
        }
        Ok(())
    }

    fn load_memory(&mut self, addr: WordAddr) -> Result<u32> {
        tracing::trace!("load_mem: {:?}", addr.baddr());
        self.pager.load(addr)
    }

    fn store_memory(&mut self, addr: WordAddr, data: u32) -> Result<()> {
        tracing::trace!("store_mem: {:?} <= 0x{data:08x}", addr.baddr());
        self.pager.store(addr, data)
    }
}

#[tracing::instrument(skip_all)]
pub fn execute<S: Syscall>(
    image: MemoryImage,
    segment_po2: usize,
    max_cycles: usize,
    syscall_handler: &S,
) -> Result<Vec<Segment>> {
    Executor::new(image, syscall_handler).run(segment_po2, max_cycles)
}

// const fn align_up(addr: usize, align: usize) -> usize {
//     (addr + align - 1) & !(align - 1)
// }

// SysCycleCount:
//     ctx.get_cycle()

// SysGetenv:
//     let buf_ptr = ctx.load_register(REG_A3);
//     let buf_len = ctx.load_register(REG_A4);
//     let from_guest = ctx.load_region(buf_ptr, buf_len)?;

// SysPanic:
//     let buf_ptr = ctx.load_register(REG_A3);
//     let buf_len = ctx.load_register(REG_A4);
//     let from_guest = ctx.load_region(buf_ptr, buf_len)?;

// SysRandom:
//     write to_guest

// SysVerify:
//     let from_guest_ptr = ctx.load_register(REG_A3);
//     let from_guest_len = ctx.load_register(REG_A4);
//     let from_guest: Vec<u8> = ctx.load_region(from_guest_ptr, from_guest_len)?;

// SysArgs:
//     let arg_index = ctx.load_register(REG_A3);

// SysSliceIo:
//     let buf_ptr = ctx.load_register(REG_A3);
//     let buf_len = ctx.load_register(REG_A4);
//     let from_guest = ctx.load_region(buf_ptr, buf_len)?;

// PosixIo/sys_read:
//     let fd = ctx.load_register(REG_A3);
//     let nbytes = ctx.load_register(REG_A4) as usize;

// PosixIo/sys_write:
//     let fd = ctx.load_register(REG_A3);
//     let buf_ptr = ctx.load_register(REG_A4);
//     let buf_len = ctx.load_register(REG_A5);
//     let from_guest_bytes = ctx.load_region(buf_ptr, buf_len)?;

// PosixIo/sys_log:
//     let buf_ptr = ctx.load_register(REG_A3);
//     let buf_len = ctx.load_register(REG_A4);
//     let from_guest = ctx.load_region(buf_ptr, buf_len)?;
