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

use risc0_zkp::core::digest::Digest;
use risc0_zkp::digest;

const CONTROL_ID_ENTRIES: usize = risc0_zkp::MAX_CYCLES_PO2 - risc0_zkp::MIN_CYCLES_PO2 + 1;

pub type ControlIds = [Digest; CONTROL_ID_ENTRIES];

/// Control IDs for each power-of-two of the rv32im circuit using SHA-256.
pub const SHA256_CONTROL_IDS: ControlIds = [{}];

/// Control IDs for each power-of-two of the rv32im circuit using Poseidon2.
pub const POSEIDON2_CONTROL_IDS: ControlIds = [{}];

/// Control IDs for each power-of-two of the rv32im circuit using Blake2b.
pub const BLAKE2B_CONTROL_IDS: ControlIds = [{}];
