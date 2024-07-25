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

use std::{cell::RefCell, rc::Rc};

use anyhow::{bail, Context as _, Result};
use risc0_circuit_rv32im::prove::emu::{
    addr::{ByteAddr, WordAddr},
    rv32im::{DecodedInstruction, EmuContext, Emulator, Instruction, TrapCause},
};
use risc0_zkvm_platform::{
    fileno,
    memory::is_guest_memory,
    syscall::{
        ecall,
        nr::{SYS_EXIT, SYS_FORK},
        reg_abi::{REG_A0, REG_A1, REG_A2, REG_MAX, REG_T0},
    },
    PAGE_SIZE, WORD_SIZE,
};

use super::{Syscall, SyscallContext, SyscallTable};

const PAGE_WORDS: usize = PAGE_SIZE / WORD_SIZE;
const INVALID_IDX: u32 = u32::MAX;
const NUM_PAGES: usize = 192 * 1024;

const PID_CHILD: u32 = 0;
const PID_PARENT: u32 = 1;

pub(crate) struct SysFork;

impl Syscall for SysFork {
    fn syscall(
        &mut self,
        _syscall: &str,
        ctx: &mut dyn SyscallContext,
        _to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        let mut exec = ChildExecutor::new(ctx)?;
        exec.run()?;
        // Return a non-zero value for sys_fork, which means this is the 'parent' process.
        Ok((PID_PARENT, 0))
    }
}

struct Page(Vec<u8>);

struct ChildExecutor<'a, 'b> {
    ctx: &'b mut dyn SyscallContext<'a>,
    pc: ByteAddr,
    registers: [u32; REG_MAX],
    page_table: Vec<u32>,
    page_cache: Vec<Page>,
    exit: bool,
    syscall_table: SyscallTable<'a>,
}

impl<'a, 'b> ChildExecutor<'a, 'b> {
    pub fn new(ctx: &'b mut dyn SyscallContext<'a>) -> Result<Self> {
        // Start the child process one instruction past the ecall.
        let pc = ByteAddr(ctx.get_pc() + WORD_SIZE as u32);

        let mut registers = std::array::from_fn(|idx| ctx.load_register(idx));
        // The return value of sys_fork is the pid, so set a0 to PID_CHILD.
        registers[REG_A0] = PID_CHILD;

        let mut syscall_table = ctx.syscall_table().clone();

        // remove the ability to write to the JOURNAL from a child process.
        let mut posix_io = ctx.syscall_table().posix_io.borrow().clone();
        posix_io.write_fds.remove(&fileno::JOURNAL);
        syscall_table.posix_io = Rc::new(RefCell::new(posix_io));

        // avoid the possibility of fork bombs.
        syscall_table.inner.remove(&SYS_FORK.as_str().to_string());

        Ok(Self {
            ctx,
            pc,
            registers,
            page_table: vec![INVALID_IDX; NUM_PAGES],
            page_cache: vec![],
            exit: false,
            syscall_table,
        })
    }

    pub fn run(&mut self) -> Result<()> {
        let mut emu = Emulator::new();
        while !self.exit {
            emu.step(self)?;
        }
        Ok(())
    }

    fn ecall_software(&mut self) -> Result<bool> {
        tracing::debug!("ecall_software");
        let into_guest_ptr = ByteAddr(EmuContext::load_register(self, REG_A0)?);
        if !is_guest_memory(into_guest_ptr.0) && !into_guest_ptr.is_null() {
            bail!("{into_guest_ptr:?} is an invalid guest address");
        }
        let into_guest_len = EmuContext::load_register(self, REG_A1)? as usize;
        let name_ptr = self.load_guest_addr_from_register(REG_A2)?;
        let syscall_name = self.load_string(name_ptr)?;
        let name_end = name_ptr + syscall_name.len();
        Self::check_guest_addr(name_end)?;
        tracing::trace!("ecall_software({syscall_name}, into_guest: {into_guest_len})");

        if syscall_name == SYS_EXIT.as_str() {
            self.exit = true;
            return Ok(true);
        }

        let syscall = self
            .syscall_table
            .get_syscall(&syscall_name)
            .context(format!("Unknown syscall: {syscall_name:?}"))
            .cloned()?;

        let mut into_guest = vec![0u32; into_guest_len];
        let (a0, a1) = syscall
            .borrow_mut()
            .syscall(&syscall_name, self, &mut into_guest)?;

        // The guest uses a null pointer to indicate that a transfer from host
        // to guest is not needed.
        if !into_guest_ptr.is_null() {
            Self::check_guest_addr(into_guest_ptr + into_guest_len)?;
            self.store_region(into_guest_ptr, bytemuck::cast_slice(&into_guest))?
        }

        self.store_register(REG_A0, a0)?;
        self.store_register(REG_A1, a1)?;

        self.pc += WORD_SIZE;

        Ok(true)
    }

    fn check_guest_addr(addr: ByteAddr) -> Result<ByteAddr> {
        if !is_guest_memory(addr.0) {
            bail!("{addr:?} is an invalid guest address");
        }
        Ok(addr)
    }

    fn load_guest_addr_from_register(&mut self, idx: usize) -> Result<ByteAddr> {
        let addr = ByteAddr(EmuContext::load_register(self, idx)?);
        Self::check_guest_addr(addr)
    }

    fn load_string(&mut self, mut addr: ByteAddr) -> Result<String> {
        tracing::trace!("load_string: {addr:?}");
        let mut buf = Vec::new();
        loop {
            let byte = self.load_u8(addr)?;
            if byte == 0 {
                break;
            }
            buf.push(byte);
            addr += 1u32;
        }
        Ok(String::from_utf8(buf)?)
    }

    fn load_u8(&mut self, addr: ByteAddr) -> Result<u8> {
        let addr = Self::check_guest_addr(addr)?;
        let word = self.load_memory(addr.waddr())?;
        let bytes = word.to_le_bytes();
        let byte_offset = addr.0 as usize % WORD_SIZE;
        Ok(bytes[byte_offset])
    }

    fn store_region(&mut self, addr: ByteAddr, slice: &[u8]) -> Result<()> {
        slice
            .iter()
            .enumerate()
            .try_for_each(|(i, x)| self.store_u8(addr + i, *x))
    }

    fn store_u8(&mut self, addr: ByteAddr, byte: u8) -> Result<()> {
        let addr = Self::check_guest_addr(addr)?;
        let word = self.load_memory(addr.waddr())?;
        let mut bytes = word.to_le_bytes();
        let byte_offset = addr.0 as usize % WORD_SIZE;
        bytes[byte_offset] = byte;
        let word = u32::from_le_bytes(bytes);
        self.store_memory(addr.waddr(), word)
    }
}

impl<'a, 'b> EmuContext for ChildExecutor<'a, 'b> {
    fn ecall(&mut self) -> Result<bool> {
        match EmuContext::load_register(self, REG_T0)? {
            ecall::SOFTWARE => self.ecall_software(),
            ecall => bail!("Unknown ecall {ecall:?}"),
        }
    }

    fn mret(&self) -> Result<bool> {
        unimplemented!()
    }

    fn trap(&self, cause: TrapCause) -> Result<bool> {
        let msg = format!("Trap: {cause:08x?}, pc: {:?}", self.pc);
        tracing::info!("{msg}");
        bail!("{msg}");
    }

    fn on_insn_decoded(&self, insn: &Instruction, _decoded: &DecodedInstruction) {
        tracing::trace!("{:?}> {:?}", self.pc, insn.kind);
    }

    fn on_normal_end(&mut self, _insn: &Instruction, _decoded: &DecodedInstruction) {
        // no-op
    }

    fn get_pc(&self) -> ByteAddr {
        self.pc
    }

    fn set_pc(&mut self, addr: ByteAddr) {
        self.pc = addr;
    }

    fn load_register(&mut self, idx: usize) -> Result<u32> {
        let data = self.registers[idx];
        tracing::trace!("load_register: x{idx} -> 0x{data:08x}");
        Ok(data)
    }

    fn store_register(&mut self, idx: usize, data: u32) -> Result<()> {
        if idx != 0 {
            tracing::trace!("store_register: x{idx} <= 0x{data:08x}");
            self.registers[idx] = data;
        }
        Ok(())
    }

    fn load_memory(&mut self, addr: WordAddr) -> Result<u32> {
        let page_idx = addr.page_idx();
        let idx = self.page_table[page_idx as usize];
        let data = if idx == INVALID_IDX {
            self.ctx.load_u32(addr.baddr())?
        } else {
            self.page_cache[idx as usize].load(addr)
        };
        // tracing::trace!("load_memory: {addr:?} -> 0x{data:08x}");
        Ok(data)
    }

    fn store_memory(&mut self, addr: WordAddr, data: u32) -> Result<()> {
        tracing::trace!("store_memory: {addr:?} <= 0x{data:08x}");
        let page_idx = addr.page_idx();
        let mut idx = self.page_table[page_idx as usize];
        if idx == INVALID_IDX {
            idx = self.page_cache.len() as u32;
            tracing::trace!("load_page: {page_idx}, {idx}");
            self.page_table[page_idx as usize] = idx;
            self.page_cache.push(Page(self.ctx.load_page(page_idx)?));
        }
        self.page_cache[idx as usize].store(addr, data);

        Ok(())
    }

    fn check_data_load(&self, addr: ByteAddr) -> bool {
        is_guest_memory(addr.0)
    }

    fn check_data_store(&self, addr: ByteAddr) -> bool {
        is_guest_memory(addr.0)
    }

    fn check_insn_load(&self, addr: ByteAddr) -> bool {
        is_guest_memory(addr.0)
    }
}

impl<'a, 'b> SyscallContext<'a> for ChildExecutor<'a, 'b> {
    fn get_pc(&self) -> u32 {
        self.pc.0
    }

    fn get_cycle(&self) -> u64 {
        0
    }

    fn load_register(&mut self, idx: usize) -> u32 {
        EmuContext::load_register(self, idx).unwrap()
    }

    fn load_u8(&mut self, addr: ByteAddr) -> Result<u8> {
        ChildExecutor::load_u8(self, addr)
    }

    fn load_u32(&mut self, addr: ByteAddr) -> Result<u32> {
        ChildExecutor::load_memory(self, addr.waddr())
    }

    fn load_page(&mut self, page_idx: u32) -> Result<Vec<u8>> {
        let idx = self.page_table[page_idx as usize];
        if idx == INVALID_IDX {
            self.ctx.load_page(page_idx)
        } else {
            Ok(self.page_cache[idx as usize].0.clone())
        }
    }

    fn syscall_table(&self) -> &SyscallTable<'a> {
        &self.syscall_table
    }
}

impl Page {
    fn load(&self, addr: WordAddr) -> u32 {
        let word_addr = (addr.0 % PAGE_WORDS as u32) as usize;
        let byte_addr = word_addr * WORD_SIZE;
        let mut bytes = [0u8; WORD_SIZE];
        bytes.clone_from_slice(&self.0[byte_addr..byte_addr + WORD_SIZE]);
        let data = u32::from_le_bytes(bytes);
        tracing::trace!("load({addr:?}) -> 0x{data:08x}");
        data
    }

    fn store(&mut self, addr: WordAddr, data: u32) {
        let word_addr = (addr.0 % PAGE_WORDS as u32) as usize;
        let byte_addr = word_addr * WORD_SIZE;
        tracing::trace!("store({addr:?}, 0x{data:08x})");
        self.0[byte_addr..byte_addr + WORD_SIZE].clone_from_slice(&data.to_le_bytes());
    }
}
