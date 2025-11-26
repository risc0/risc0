// Copyright 2025 RISC Zero, Inc.
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

use crate::TerminateState;

use super::{DEFAULT_SEGMENT_LIMIT_PO2, testutil};

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
        testutil::DEFAULT_SESSION_LIMIT,
        &testutil::NullSyscall,
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
        testutil::DEFAULT_SESSION_LIMIT,
        &testutil::NullSyscall,
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
