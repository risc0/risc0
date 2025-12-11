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

//! Claim types and utilities for the zkVM.

use borsh::{BorshDeserialize, BorshSerialize};
use risc0_binfmt::Digestible;
use risc0_zkp::core::digest::Digest;
use serde::{Deserialize, Serialize};

use crate::sha::Sha256;

pub(crate) mod maybe_pruned;
pub(crate) mod merge;
pub(crate) mod receipt;
pub(crate) mod work;

/// A receipt (e.g. [SuccinctReceipt][crate::SuccinctReceipt]) may have an unknown claim type when
/// only the digest of the claim is needed, and the full claim value cannot be determined by the
/// compiler. This allows for a collection of receipts to be created even when the underlying
/// claims are of heterogeneous types (e.g. `Vec<SuccinctReceipt<Unknown>>`).
///
/// Note that this is an uninhabited type, similar to the [never type].
///
/// [never type]: https://doc.rust-lang.org/std/primitive.never.html
#[derive(Clone, Debug, Serialize, Deserialize)]
#[cfg_attr(test, derive(PartialEq))]
pub enum Unknown {}

impl Digestible for Unknown {
    fn digest<S: Sha256>(&self) -> Digest {
        match *self { /* unreachable  */ }
    }
}

impl BorshSerialize for Unknown {
    fn serialize<W>(&self, _: &mut W) -> core::result::Result<(), borsh::io::Error> {
        match *self { /* unreachable  */ }
    }
}

impl BorshDeserialize for Unknown {
    fn deserialize_reader<R>(_: &mut R) -> core::result::Result<Self, borsh::io::Error> {
        Err(borsh::io::Error::new(
            borsh::io::ErrorKind::InvalidData,
            "BorshDeserialize attempted to deserialize Unknown; data is malformed",
        ))
    }
}
