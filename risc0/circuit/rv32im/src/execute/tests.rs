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

use risc0_binfmt::MemoryImage;
use risc0_zkp::core::digest::Digest;
use test_log::test;

use crate::{TerminateState, MAX_INSN_CYCLES};

use super::{testutil, DEFAULT_SEGMENT_LIMIT_PO2};

/// Builds a `jalr x0, 0(x0)` raw word with the given `funct3`.
fn jalr_word(funct3: u32) -> u32 {
    (0 << 20) | (0 << 15) | (funct3 << 12) | (0 << 7) | 0b1100111
}

/// Runs a one-instruction program and returns the trap message, or `None` if it ran to
/// completion.
///
/// On unfixed code every `funct3` decodes as `jalr` and jumps to 0, so all eight encodings
/// produce the same `InstructionFault`. With the fix, only `funct3 == 0` reaches the jump.
fn trap_with(funct3: u32) -> Option<String> {
    let mut asm = testutil::Assembler::new();
    asm.push_word(jalr_word(funct3));

    let image = MemoryImage::new_kernel(asm.program());
    testutil::execute(
        image,
        DEFAULT_SEGMENT_LIMIT_PO2,
        MAX_INSN_CYCLES,
        testutil::DEFAULT_SESSION_LIMIT,
        &testutil::NullSyscall,
        None,
    )
    .err()
    .map(|err| format!("{err:?}"))
}

/// `jalr` is only defined for `funct3 == 0`. The fast executor matched
/// `(0b1100111, _, _)`, so a reserved encoding was decoded as `jalr` and the resulting jump
/// produced `InstructionFault` instead of the `IllegalInstruction` the preflight decoder
/// requires.
#[test]
fn jalr_with_reserved_funct3_traps_as_illegal_instruction() {
    for funct3 in 1..=7u32 {
        let message = trap_with(funct3).unwrap_or_else(|| {
            panic!("funct3 = {funct3:03b} should trap as IllegalInstruction, but it ran")
        });
        assert!(
            message.contains("IllegalInstruction"),
            "funct3 = {funct3:03b} should trap as IllegalInstruction, got {message}"
        );
    }
}

/// The control: with `funct3 == 0` the encoding is a real `jalr`, so the failure is the jump
/// landing at 0 rather than an illegal-instruction decode.
#[test]
fn jalr_with_valid_funct3_is_decoded_as_jalr() {
    let message = trap_with(0b000).expect("jalr to address 0 must fault");
    assert!(
        !message.contains("IllegalInstruction"),
        "funct3 = 000 is a valid jalr and must not decode as illegal, got {message}"
    );
    assert!(
        message.contains("InstructionFault"),
        "expected the jump itself to fault, got {message}"
    );
}

#[test]
fn basic() {
    let program = testutil::kernel::basic();
    let expected_cycles = program.size_in_words();
    let mut image = MemoryImage::new_kernel(program);
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
    assert_eq!(segment.suspend_cycle, expected_cycles as u32 + 1);
}

#[test]
fn system_split() {
    let program = testutil::kernel::simple_loop(2000);
    let mut image = MemoryImage::new_kernel(program);
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
