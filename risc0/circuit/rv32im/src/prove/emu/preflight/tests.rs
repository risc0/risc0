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

use std::fmt;

use risc0_binfmt::MemoryImage;
use risc0_zkvm_platform::PAGE_SIZE;
use test_log::test;

use super::{Back, MemoryTransaction, PreflightCycle};
use crate::prove::emu::{
    exec::{execute, DEFAULT_SEGMENT_LIMIT_PO2},
    mux::{Major, TopMux},
    rv32im::InsnKind,
    testutil::{self, NullSyscall, DEFAULT_SESSION_LIMIT},
    ByteAddr,
};

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
        PreflightCycle::new(
            insn.into(),
            Some(Back::Body { pc: ByteAddr(pc) }),
            mem_idx,
            0,
        )
    } else {
        PreflightCycle::new(insn.into(), None, mem_idx, 0)
    }
}

#[test]
fn basic() {
    let program = testutil::basic();
    let image = MemoryImage::new(&program, PAGE_SIZE as u32).unwrap();

    let result = execute(
        image,
        DEFAULT_SEGMENT_LIMIT_PO2,
        DEFAULT_SESSION_LIMIT,
        &NullSyscall::default(),
        None,
    )
    .unwrap();
    let segments = result.segments;
    let segment = segments.first().unwrap();

    let mut trace = segment.preflight().unwrap();
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
            MemoryTransaction::new(3, ByteAddr(0x0000400c), 0x000045b7),
            MemoryTransaction::new(3, ByteAddr(0x0c000000), 0),
            MemoryTransaction::new(3, ByteAddr(0x0c000000), 0),
            MemoryTransaction::new(4, ByteAddr(0x00004010), 0x00000073),
            MemoryTransaction::new(4, ByteAddr(0x0c000014), 0),
            MemoryTransaction::new(4, ByteAddr(0x0c00002c), 0x00004000),
            MemoryTransaction::new(4, ByteAddr(0x0c000028), 0x00000000),
            // reset(1)
            MemoryTransaction::new(5780, ByteAddr(0x00004000), 0x1234b137),
            MemoryTransaction::new(5780, ByteAddr(0x00004004), 0xf387e1b7),
            MemoryTransaction::new(5780, ByteAddr(0x00004008), 0x003100b3),
            MemoryTransaction::new(5780, ByteAddr(0x0000400c), 0x000045b7),
            MemoryTransaction::new(5781, ByteAddr(0x00004010), 0x00000073),
            MemoryTransaction::new(5781, ByteAddr(0x00004014), 0x00000000),
            MemoryTransaction::new(5781, ByteAddr(0x00004018), 0x00000000),
            MemoryTransaction::new(5781, ByteAddr(0x0000401c), 0x00000000),
            // reset(2)
            MemoryTransaction::new(5782, ByteAddr(0x0d6b5ac0), 0x2ea10cf3),
            MemoryTransaction::new(5782, ByteAddr(0x0d6b5ac4), 0x41559d09),
            MemoryTransaction::new(5782, ByteAddr(0x0d6b5ac8), 0x032b0b9e),
            MemoryTransaction::new(5782, ByteAddr(0x0d6b5acc), 0xda56a7af),
            MemoryTransaction::new(5783, ByteAddr(0x0d6b5ad0), 0x7c9d8024),
            MemoryTransaction::new(5783, ByteAddr(0x0d6b5ad4), 0x9bfea1c1),
            MemoryTransaction::new(5783, ByteAddr(0x0d6b5ad8), 0xc37b44c3),
            MemoryTransaction::new(5783, ByteAddr(0x0d6b5adc), 0x554f49f5),
        ],
    );

    assert_eq!(trace.body.extras.len(), 0);
}

#[test]
fn system_split() {
    let program = testutil::simple_loop();
    let image = MemoryImage::new(&program, PAGE_SIZE as u32).unwrap();

    let result = execute(
        image,
        14,
        DEFAULT_SESSION_LIMIT,
        &NullSyscall::default(),
        None,
    )
    .unwrap();
    let segments = result.segments;

    assert_eq!(segments.len(), 2);
    {
        let trace = segments[0].preflight().unwrap();
        assert_eq!(trace.pre.cycles.len(), 10004);
        assert_eq!(trace.pre.txns.len(), 9968);
        assert_eq!(trace.pre.extras.len(), 24);
        assert_eq!(trace.body.cycles.len(), 5786);
        assert_eq!(trace.body.txns.len(), 5377);
        assert_eq!(trace.body.extras.len(), 15);
        let page_reads: Vec<_> = trace
            .pre
            .cycles
            .iter()
            .filter(|x| x.mux == TopMux::Body(Major::PageFault, 0))
            .map(|x| trace.pre.extras[x.extra_idx + 1])
            .collect();
        assert_slice_eq(
            &page_reads,
            &[
                0x35ad6, 0x35ad0, 0x35ac0, 0x35a00, 0x35800, 0x34000, 0x30000, 0x00010,
            ],
        );
        let page_writes: Vec<_> = trace
            .body
            .cycles
            .iter()
            .filter(|x| {
                x.mux == TopMux::Body(Major::PageFault, 0)
                    && trace.body.extras[x.extra_idx + 2] == 0
                // !is_done
            })
            .map(|x| trace.body.extras[x.extra_idx + 1])
            .collect();
        assert_slice_eq(&page_writes, &[0x30000, 0x35800, 0x35ac0, 0x35ad6]);
    }
    {
        let trace = segments[1].preflight().unwrap();
        assert_eq!(trace.pre.cycles.len(), 10004);
        assert_eq!(trace.pre.txns.len(), 9968);
        assert_eq!(trace.pre.extras.len(), 24);
        assert_eq!(trace.body.cycles.len(), 5786);
        assert_eq!(trace.body.txns.len(), 20);
        assert_eq!(trace.body.extras.len(), 0);
        let page_reads: Vec<_> = trace
            .pre
            .cycles
            .iter()
            .filter(|x| x.mux == TopMux::Body(Major::PageFault, 0))
            .map(|x| trace.pre.extras[x.extra_idx + 1])
            .collect();
        assert_slice_eq(
            &page_reads,
            &[
                0x35ad6, 0x35ad0, 0x35ac0, 0x35a00, 0x35800, 0x34000, 0x30000, 0x00010,
            ],
        );
        let page_writes: Vec<_> = trace
            .body
            .cycles
            .iter()
            .filter(|x| x.mux == TopMux::Body(Major::PageFault, 0))
            .collect();
        assert_eq!(page_writes.len(), 0);
    }
}
