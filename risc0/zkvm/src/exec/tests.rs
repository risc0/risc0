// Copyright 2023 RISC Zero, Inc.
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

use std::collections::BTreeMap;

use risc0_zkvm_platform::{PAGE_SIZE, WORD_SIZE};
use test_log::test;

use super::{Executor, ExecutorEnv};
use crate::{ExitCode, MemoryImage, Program};

#[test]
fn basic() {
    let env = ExecutorEnv::new().build();
    let image = BTreeMap::from([
        (0x4000, 0x1234b137), // lui x2, 0x1234b000
        (0x4004, 0xf387e1b7), // lui x3, 0xf387e000
        (0x4008, 0x003100b3), // add x1, x2, x3
        (0x400c, 0x00000073), // ecall(halt)
    ]);
    let program = Program {
        entry: 0x4000,
        image,
    };
    let image = MemoryImage::new(&program, PAGE_SIZE as u32);
    let pre_image_id = image.get_root();

    let mut exec = Executor::new(env, image, program.entry);
    let session = exec.run().unwrap();

    assert_eq!(session.segments.len(), 1);
    assert_eq!(session.segments[0].exit_code, ExitCode::Halted(0));
    assert_eq!(session.segments[0].pre_image.get_root(), pre_image_id);
    assert_ne!(session.segments[0].post_image_id, pre_image_id);
}

#[test]
fn system_split() {
    let entry = 0x4000_u32;
    let env = ExecutorEnv::new()
        .segment_limit_po2(14) // 16K cycles
        .build();
    let mut image = BTreeMap::new();
    let mut pc = entry;
    for _ in 0..1000 {
        image.insert(pc, 0x1234b137); // lui x2, 0x1234b000
        pc += WORD_SIZE as u32;
    }
    image.insert(pc, 0x00000073); // ecall(halt)

    let program = Program { entry, image };
    let image = MemoryImage::new(&program, PAGE_SIZE as u32);
    let pre_image_id = image.get_root();

    let mut exec = Executor::new(env, image, program.entry);
    let session = exec.run().unwrap();

    assert_eq!(session.segments.len(), 2);
    assert_eq!(session.segments[0].exit_code, ExitCode::SystemSplit);
    assert_eq!(session.segments[0].pre_image.get_root(), pre_image_id);
    assert_ne!(session.segments[0].post_image_id, pre_image_id);
    assert_eq!(session.segments[1].exit_code, ExitCode::Halted(0));
    assert_eq!(
        session.segments[1].pre_image.get_root(),
        session.segments[0].post_image_id
    );
}
