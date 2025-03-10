// Copyright 2025 RISC Zero, Inc.
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

use risc0_binfmt::MemoryImage2;
use risc0_zkp::core::digest::Digest;
use test_log::test;

use crate::{TerminateState, MAX_INSN_CYCLES};

use super::{testutil, DEFAULT_SEGMENT_LIMIT_PO2};

#[test]
fn basic() {
    let program = testutil::kernel::basic();
    let expected_cycles = program.image.len();
    let mut image = MemoryImage2::new_kernel(program);
    let pre_image_id = image.image_id();

    println!("image_id: {pre_image_id}");

    let session = testutil::execute(
        image,
        DEFAULT_SEGMENT_LIMIT_PO2,
        MAX_INSN_CYCLES,
        testutil::DEFAULT_SESSION_LIMIT,
        &testutil::NullSyscall,
        None,
    )
    .unwrap();

    let segments = session.segments;
    assert_eq!(segments.len(), 1);
    let segment = segments.first().unwrap();
    assert_eq!(segment.claim.pre_state, pre_image_id);
    assert_ne!(segment.claim.post_state, pre_image_id);
    assert_eq!(segment.claim.input, Digest::ZERO);
    assert_eq!(segment.claim.output, Some(Digest::ZERO));
    assert_eq!(
        segment.claim.terminate_state,
        Some(TerminateState::default())
    );
    assert!(segment.read_record.is_empty());
    assert!(segment.write_record.is_empty());
    assert_eq!(segment.user_cycles, expected_cycles as u32);
}

#[test]
fn system_split() {
    let program = testutil::kernel::simple_loop(2000);
    let mut image = MemoryImage2::new_kernel(program);
    let pre_image_id = image.image_id();

    let session = testutil::execute(
        image,
        testutil::MIN_CYCLES_PO2,
        100,
        testutil::DEFAULT_SESSION_LIMIT,
        &testutil::NullSyscall,
        None,
    )
    .unwrap();

    let segments = session.segments;
    assert_eq!(segments.len(), 2);
    assert_eq!(segments[0].claim.pre_state, pre_image_id);
    assert_ne!(segments[0].claim.post_state, pre_image_id);
    assert_eq!(segments[0].claim.input, Digest::ZERO);
    assert_eq!(segments[0].claim.output, None);
    assert_eq!(segments[0].claim.terminate_state, None);

    assert_eq!(segments[1].claim.pre_state, segments[0].claim.post_state);
    assert_ne!(segments[1].claim.post_state, segments[1].claim.pre_state);
    assert_eq!(segments[1].claim.input, Digest::ZERO);
    assert_eq!(segments[1].claim.output, Some(Digest::ZERO));
    assert_eq!(
        segments[1].claim.terminate_state,
        Some(TerminateState::default())
    );

    assert!(segments[0].read_record.is_empty());
    assert!(segments[0].write_record.is_empty());
}
