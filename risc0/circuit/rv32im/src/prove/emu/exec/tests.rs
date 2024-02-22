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

use std::{cell::RefCell, collections::BTreeMap};

use anyhow::Result;
use risc0_binfmt::{Digestible, MemoryImage, Program};
use risc0_zkp::core::hash::sha::cpu::Impl as ShaImpl;
use risc0_zkvm_platform::{
    syscall::reg_abi::{REG_A4, REG_A5},
    PAGE_SIZE, WORD_SIZE,
};
use test_log::test;

use super::{Syscall, SyscallContext};

#[derive(Default, Clone)]
struct BasicSyscallState {
    syscall: String,
    from_guest: Vec<u8>,
    into_guest: Vec<u8>,
}

#[derive(Default)]
struct BasicSyscall {
    state: RefCell<BasicSyscallState>,
}

#[allow(unused)]
impl BasicSyscall {
    fn new(into_guest: Vec<u8>) -> Self {
        Self {
            state: RefCell::new(BasicSyscallState {
                syscall: String::new(),
                from_guest: Vec::new(),
                into_guest,
            }),
        }
    }

    fn state(&self) -> BasicSyscallState {
        self.state.borrow().clone()
    }
}

impl Syscall for BasicSyscall {
    fn syscall(
        &self,
        syscall: &str,
        ctx: &mut dyn SyscallContext,
        guest_buf: &mut [u32],
    ) -> Result<(u32, u32)> {
        self.state.borrow_mut().syscall = syscall.to_string();
        let buf_ptr = ctx.peek_register(REG_A4)?;
        let buf_len = ctx.peek_register(REG_A5)?;
        self.state.borrow_mut().from_guest = ctx.peek_region(buf_ptr, buf_len)?;
        let guest_buf_bytes: &mut [u8] = bytemuck::cast_slice_mut(guest_buf);
        let into_guest = &self.state.borrow().into_guest;
        guest_buf_bytes[..into_guest.len()].clone_from_slice(into_guest);
        Ok((0, 0))
    }
}

#[test]
fn basic() {
    let raw_image = BTreeMap::from([
        (0x4000, 0x1234b137), // lui x2, 0x1234b000
        (0x4004, 0xf387e1b7), // lui x3, 0xf387e000
        (0x4008, 0x003100b3), // add x1, x2, x3
        (0x400c, 0x000055b7), // lui a1, 0x00005000
        (0x4010, 0x00000073), // ecall(halt)
    ]);
    let program = Program {
        entry: 0x4000,
        image: raw_image.clone(),
    };
    let image = MemoryImage::new(&program, PAGE_SIZE as u32).unwrap();
    let pre_image_id = image.compute_id();

    let segments = super::execute(image, 1 << 20, 1 << 4, &BasicSyscall::default()).unwrap();

    assert_eq!(segments.len(), 1);
    let segment = segments.first().unwrap();
    assert_eq!(segment.pre_state.digest::<ShaImpl>(), pre_image_id);
    assert_ne!(segment.post_state.digest::<ShaImpl>(), pre_image_id);
    assert!(segment.syscalls.is_empty());
    assert_eq!(segment.insn_cycles, raw_image.len());
}

#[test]
fn system_split() {
    let entry = 0x4000;
    let mut image = BTreeMap::new();
    let mut pc = entry;
    for _ in 0..2500 {
        image.insert(pc, 0x1234b137); // lui x2, 0x1234b000
        pc += WORD_SIZE as u32;
    }
    image.insert(pc, 0x000055b7); // lui a1, 0x00005000
    pc += WORD_SIZE as u32;
    image.insert(pc, 0xc0058593); // addi a1, a1, -0x400
    pc += WORD_SIZE as u32;
    image.insert(pc, 0x00000073); // ecall(halt)

    let program = Program { entry, image };
    let image = MemoryImage::new(&program, PAGE_SIZE as u32).unwrap();
    let pre_image_id = image.compute_id();

    let segments = super::execute(image, 1 << 15, 1 << 20, &BasicSyscall::default()).unwrap();

    assert_eq!(segments.len(), 2);
    // assert_eq!(segments[0].exit_code, ExitCode::SystemSplit);
    assert_eq!(segments[0].pre_state.digest::<ShaImpl>(), pre_image_id);
    assert_ne!(segments[0].post_state.digest::<ShaImpl>(), pre_image_id);
    assert!(segments[0].syscalls.is_empty());
    // assert_eq!(segments[1].exit_code, ExitCode::Halted(0));
    assert_eq!(
        segments[1].pre_state.digest::<ShaImpl>(),
        segments[0].post_state.digest::<ShaImpl>()
    );
}
