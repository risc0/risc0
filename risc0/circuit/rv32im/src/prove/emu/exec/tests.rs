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

use std::cell::RefCell;

use anyhow::Result;
use risc0_binfmt::{Digestible, ExitCode, MemoryImage};
use risc0_zkp::core::hash::sha::cpu::Impl as ShaImpl;
use risc0_zkvm_platform::{
    syscall::reg_abi::{REG_A4, REG_A5},
    PAGE_SIZE,
};
use test_log::test;

use super::{Syscall, SyscallContext};
use crate::prove::emu::{
    addr::ByteAddr,
    exec::DEFAULT_SEGMENT_LIMIT_PO2,
    testutil::{self, DEFAULT_SESSION_LIMIT},
};

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
        let buf_ptr = ByteAddr(ctx.peek_register(REG_A4)?);
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
    let program = testutil::basic();
    let image = MemoryImage::new(&program, PAGE_SIZE as u32).unwrap();
    let pre_image_id = image.compute_id();

    let result = super::execute(
        image,
        DEFAULT_SEGMENT_LIMIT_PO2,
        DEFAULT_SESSION_LIMIT,
        &BasicSyscall::default(),
        None,
    )
    .unwrap();

    let segments = result.segments;
    assert_eq!(segments.len(), 1);
    let segment = segments.first().unwrap();
    assert_eq!(segment.pre_state.digest::<ShaImpl>(), pre_image_id);
    assert_ne!(segment.post_state.digest::<ShaImpl>(), pre_image_id);
    assert!(segment.syscalls.is_empty());
    assert_eq!(segment.insn_cycles, program.image.len());
    assert_eq!(segment.exit_code, ExitCode::Halted(0));
}

#[test]
fn system_split() {
    let program = testutil::simple_loop();
    let image = MemoryImage::new(&program, PAGE_SIZE as u32).unwrap();
    let pre_image_id = image.compute_id();

    let result = super::execute(
        image,
        14,
        DEFAULT_SESSION_LIMIT,
        &BasicSyscall::default(),
        None,
    )
    .unwrap();

    let segments = result.segments;
    assert_eq!(segments.len(), 2);
    assert_eq!(segments[0].exit_code, ExitCode::SystemSplit);
    assert_eq!(segments[0].pre_state.digest::<ShaImpl>(), pre_image_id);
    assert_ne!(segments[0].post_state.digest::<ShaImpl>(), pre_image_id);
    assert!(segments[0].syscalls.is_empty());
    assert_eq!(segments[1].exit_code, ExitCode::Halted(0));
    assert_eq!(
        segments[1].pre_state.digest::<ShaImpl>(),
        segments[0].post_state.digest::<ShaImpl>()
    );
}
