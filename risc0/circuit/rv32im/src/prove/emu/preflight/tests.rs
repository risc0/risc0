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

use std::{collections::BTreeMap, fmt};

use anyhow::Result;
use risc0_binfmt::{MemoryImage, Program};
use risc0_zkvm_platform::PAGE_SIZE;
use test_log::test;

use crate::prove::emu::{
    exec::{execute, Syscall, SyscallContext},
    preflight::{Major, MemoryTransaction, PreflightCycle},
};

#[derive(Default)]
struct NullSyscall;

impl Syscall for NullSyscall {
    fn syscall(
        &self,
        _syscall: &str,
        _ctx: &mut dyn SyscallContext,
        _guest_buf: &mut [u32],
    ) -> Result<(u32, u32)> {
        todo!()
    }
}

fn assert_slice_eq<T: fmt::Debug + PartialEq>(lhs: &[T], rhs: &[T]) {
    if lhs.len() != rhs.len() {
        assert_eq!(lhs, rhs);
    }
    for (i, (lhs, rhs)) in lhs.iter().zip(rhs).enumerate() {
        assert_eq!(lhs, rhs, "item: {i}");
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

    let segments = execute(image, 1 << 20, 1 << 4, &NullSyscall::default()).unwrap();
    let segment = segments.first().unwrap();

    let trace = super::preflight_segment(segment).unwrap();
    assert_slice_eq(
        &trace.cycles,
        &[
            PreflightCycle::new(0x4004, true, 0, 0, Major::Compute2, 5),
            PreflightCycle::new(0x4008, true, 3, 0, Major::Compute2, 5),
            PreflightCycle::new(0x400c, true, 6, 0, Major::Compute0, 0),
            PreflightCycle::new(0x4010, true, 9, 0, Major::Compute2, 5),
            PreflightCycle::new(0x4010, true, 12, 0, Major::ECall, 0),
        ],
    );

    assert_slice_eq(
        &trace.txns,
        &[
            MemoryTransaction::new(0, 0x00004000 / 4, 0x1234b137),
            MemoryTransaction::new(0, 0x0c000024 / 4, 0),
            MemoryTransaction::new(0, 0x0c00000c / 4, 0),
            MemoryTransaction::new(1, 0x00004004 / 4, 0xf387e1b7),
            MemoryTransaction::new(1, 0x0c00003c / 4, 0),
            MemoryTransaction::new(1, 0x0c000060 / 4, 0),
            MemoryTransaction::new(2, 0x00004008 / 4, 0x003100b3),
            MemoryTransaction::new(2, 0x0c000008 / 4, 0x1234b000),
            MemoryTransaction::new(2, 0x0c00000c / 4, 0xf387e000),
            MemoryTransaction::new(3, 0x0000400c / 4, 0x000055b7),
            MemoryTransaction::new(3, 0x0c000000 / 4, 0),
            MemoryTransaction::new(3, 0x0c000000 / 4, 0),
            MemoryTransaction::new(4, 0x00004010 / 4, 0x00000073),
            MemoryTransaction::new(4, 0x0c000014 / 4, 0),
            MemoryTransaction::new(4, 0x0c00002c / 4, 0x00005000),
            MemoryTransaction::new(4, 0x0c000028 / 4, 0x00000000),
            MemoryTransaction::new(5, 0x00005000 / 4, 0x00000000),
            MemoryTransaction::new(5, 0x00005004 / 4, 0x00000000),
            MemoryTransaction::new(5, 0x00005008 / 4, 0x00000000),
            MemoryTransaction::new(5, 0x0000500c / 4, 0x00000000),
            MemoryTransaction::new(5, 0x00005010 / 4, 0x00000000),
            MemoryTransaction::new(5, 0x00005014 / 4, 0x00000000),
            MemoryTransaction::new(5, 0x00005018 / 4, 0x00000000),
            MemoryTransaction::new(5, 0x0000501c / 4, 0x00000000),
            MemoryTransaction::new(5, 0x0d6b5ac0 / 4, 0x00000000),
            MemoryTransaction::new(5, 0x0d6b5ac4 / 4, 0x00000000),
            MemoryTransaction::new(5, 0x0d6b5ac8 / 4, 0x00000000),
            MemoryTransaction::new(5, 0x0d6b5acc / 4, 0x00000000),
            MemoryTransaction::new(5, 0x0d6b5ad0 / 4, 0x00000000),
            MemoryTransaction::new(5, 0x0d6b5ad4 / 4, 0x00000000),
            MemoryTransaction::new(5, 0x0d6b5ad8 / 4, 0x00000000),
            MemoryTransaction::new(5, 0x0d6b5adc / 4, 0x00000000),
        ],
    );

    assert_eq!(trace.extras.len(), 0);
}
