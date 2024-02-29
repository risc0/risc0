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

use super::{MemoryTransaction, PreflightCycle};
use crate::prove::emu::{
    exec::{execute, Syscall, SyscallContext, DEFAULT_SEGMENT_PO2},
    rv32im::InsnKind,
    ByteAddr,
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

fn add_cycle(insn: InsnKind, mem_idx: usize, pc: Option<u32>) -> PreflightCycle {
    if let Some(pc) = pc {
        PreflightCycle::new(insn.into(), Some(ByteAddr(pc)), mem_idx, 0)
    } else {
        PreflightCycle::new(insn.into(), None, mem_idx, 0)
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

    let segments = execute(image, DEFAULT_SEGMENT_PO2, 1 << 20, &NullSyscall::default()).unwrap();
    let segment = segments.first().unwrap();

    let mut trace = super::preflight_segment(segment).unwrap();
    let expected_cycles = [
        add_cycle(InsnKind::LUI, 0, Some(0x4000)),
        add_cycle(InsnKind::LUI, 3, Some(0x4004)),
        add_cycle(InsnKind::ADD, 6, Some(0x4008)),
        add_cycle(InsnKind::LUI, 9, Some(0x400c)),
        add_cycle(InsnKind::EANY, 12, None),
    ];
    trace.body.cycles.truncate(expected_cycles.len());

    assert_slice_eq(&trace.body.cycles, &expected_cycles);
    assert_slice_eq(
        &trace.body.txns,
        &[
            MemoryTransaction::new(0, ByteAddr(0x00004000), 0x1234b137),
            MemoryTransaction::new(0, ByteAddr(0x0c000024), 0),
            MemoryTransaction::new(0, ByteAddr(0x0c00000c), 0),
            MemoryTransaction::new(1, ByteAddr(0x00004004), 0xf387e1b7),
            MemoryTransaction::new(1, ByteAddr(0x0c00003c), 0),
            MemoryTransaction::new(1, ByteAddr(0x0c000060), 0),
            MemoryTransaction::new(2, ByteAddr(0x00004008), 0x003100b3),
            MemoryTransaction::new(2, ByteAddr(0x0c000008), 0x1234b000),
            MemoryTransaction::new(2, ByteAddr(0x0c00000c), 0xf387e000),
            MemoryTransaction::new(3, ByteAddr(0x0000400c), 0x000055b7),
            MemoryTransaction::new(3, ByteAddr(0x0c000000), 0),
            MemoryTransaction::new(3, ByteAddr(0x0c000000), 0),
            MemoryTransaction::new(4, ByteAddr(0x00004010), 0x00000073),
            MemoryTransaction::new(4, ByteAddr(0x0c000014), 0),
            MemoryTransaction::new(4, ByteAddr(0x0c00002c), 0x00005000),
            MemoryTransaction::new(4, ByteAddr(0x0c000028), 0x00000000),
            // reset(1)
            MemoryTransaction::new(6324, ByteAddr(0x00005000), 0x00000000),
            MemoryTransaction::new(6324, ByteAddr(0x00005004), 0x00000000),
            MemoryTransaction::new(6324, ByteAddr(0x00005008), 0x00000000),
            MemoryTransaction::new(6324, ByteAddr(0x0000500c), 0x00000000),
            MemoryTransaction::new(6325, ByteAddr(0x00005010), 0x00000000),
            MemoryTransaction::new(6325, ByteAddr(0x00005014), 0x00000000),
            MemoryTransaction::new(6325, ByteAddr(0x00005018), 0x00000000),
            MemoryTransaction::new(6325, ByteAddr(0x0000501c), 0x00000000),
            // reset(2)
            MemoryTransaction::new(6326, ByteAddr(0x0d6b5ac0), 0x5540a93a),
            MemoryTransaction::new(6326, ByteAddr(0x0d6b5ac4), 0x5f49f0e7),
            MemoryTransaction::new(6326, ByteAddr(0x0d6b5ac8), 0xe8e63b65),
            MemoryTransaction::new(6326, ByteAddr(0x0d6b5acc), 0x67e2c509),
            MemoryTransaction::new(6327, ByteAddr(0x0d6b5ad0), 0x4bfcad79),
            MemoryTransaction::new(6327, ByteAddr(0x0d6b5ad4), 0x0943f0cb),
            MemoryTransaction::new(6327, ByteAddr(0x0d6b5ad8), 0xd99e50cf),
            MemoryTransaction::new(6327, ByteAddr(0x0d6b5adc), 0x2354b2e4),
        ],
    );

    assert_eq!(trace.body.extras.len(), 0);
}
