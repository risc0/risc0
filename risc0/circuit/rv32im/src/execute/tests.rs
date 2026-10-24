// Copyright 2026 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use risc0_binfmt::MemoryImage;
use risc0_zkp::core::digest::Digest;
use test_log::test;

use crate::{
    TerminateState,
    execute::{ExecutionLimit, testutil},
};

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
        testutil::DEFAULT_EXECUTION_LIMIT,
        testutil::NullSyscall,
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
    let mut image = MemoryImage::new_kernel(program);
    let pre_image_id = image.image_id();

    println!("image_id: {pre_image_id}");

    let session = testutil::execute(
        image,
        testutil::DEFAULT_EXECUTION_LIMIT,
        testutil::NullSyscall,
        None,
    )
    .unwrap();

    let segments = session.segments;
    assert_eq!(segments.len(), 1);
    let segment = segments.first().unwrap();
    let segment_claim = segment.execute().unwrap().claim();
    assert_eq!(segment_claim.pre_state, pre_image_id);
    assert_ne!(segment_claim.post_state, pre_image_id);
    assert_eq!(segment.input_digest, Digest::ZERO);
    assert_eq!(segment.output_digest, Some(Digest::ZERO));
    assert_eq!(segment.terminate_state, Some(TerminateState::default()));
    assert!(segment.read_record.is_empty());
    assert!(segment.write_record.is_empty());
}

#[test]
fn system_split() {
    const ITERATIONS: u32 = 10_000;

    let program = testutil::kernel::simple_loop(ITERATIONS);
    let mut image = MemoryImage::new_kernel(program);
    let pre_image_id = image.image_id();

    let session = testutil::execute(
        image,
        ExecutionLimit::default()
            .with_segment_po2(testutil::MIN_CYCLES_PO2)
            .with_session_limit(testutil::DEFAULT_SESSION_LIMIT)
            .with_max_insn_rows(100),
        testutil::NullSyscall,
        None,
    )
    .unwrap();

    let segments = session.segments;
    assert_eq!(segments.len(), 2);
    let segment0_claim = segments[0].execute().unwrap().claim();
    assert_eq!(segment0_claim.pre_state, pre_image_id);
    assert_ne!(segment0_claim.post_state, pre_image_id);
    assert_eq!(segments[0].input_digest, Digest::ZERO);
    assert_eq!(segments[0].output_digest, None);
    assert_eq!(segments[0].terminate_state, None);

    let segment1_claim = segments[1].execute().unwrap().claim();
    assert_eq!(segment1_claim.pre_state, segment0_claim.post_state);
    assert_ne!(segment1_claim.post_state, segment1_claim.pre_state);
    assert_eq!(segments[1].input_digest, Digest::ZERO);
    assert_eq!(segments[1].output_digest, Some(Digest::ZERO));
    assert_eq!(segments[1].terminate_state, Some(TerminateState::default()));

    assert!(segments[0].read_record.is_empty());
    assert!(segments[0].write_record.is_empty());
}

#[test]
fn insufficient_segment_limit() {
    const ITERATIONS: u32 = 10_000;

    let program = testutil::kernel::simple_loop(ITERATIONS);
    let image = MemoryImage::new_kernel(program);

    let error = testutil::execute(
        image,
        ExecutionLimit::default()
            .with_segment_po2(13)
            .with_max_insn_rows(0),
        testutil::NullSyscall,
        None,
    )
    .map(|_| ())
    .unwrap_err();
    assert!(
        error.to_string().contains("too small"),
        "too small not found in {error}"
    );
}
