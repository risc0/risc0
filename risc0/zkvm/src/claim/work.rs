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

//! [WorkClaim] and associated types and functions.

use alloc::vec::Vec;
use core::fmt;

use borsh::{BorshDeserialize, BorshSerialize};
use risc0_binfmt::{tagged_struct, Digestible, PovwNonce};
use serde::{Deserialize, Serialize};

use crate::{
    sha::{Digest, Sha256},
    MaybePruned,
};

// TODO: Move this into the risc0 repo
/// A wrapper around the underlying claim that additionally includes the amount of verifiable work
/// completed, and the nonces used, in the process of proving the claim.
///
/// This type is instantiated as [WorkClaim<ReceiptClaim>] when PoVW is used with zkVM proving.
#[derive(Clone, Serialize, Deserialize, BorshSerialize, BorshDeserialize)]
pub struct WorkClaim<Claim>
where
    Claim: Clone + Serialize,
{
    /// The wrapped claim (e.g. [ReceiptClaim][crate::ReceiptClaim]).
    pub claim: MaybePruned<Claim>,
    /// Work associated with proving the wrapped claim.
    pub work: MaybePruned<Work>,
}

impl<Claim> Digestible for WorkClaim<Claim>
where
    Claim: Digestible + Clone + Serialize,
{
    /// Hash the [ReceiptClaim] to get a digest of the struct.
    fn digest<S: Sha256>(&self) -> Digest {
        tagged_struct::<S>(
            "risc0.WorkClaim",
            &[self.claim.digest::<S>(), self.work.digest::<S>()],
            &[],
        )
    }
}

impl<Claim> fmt::Debug for WorkClaim<Claim>
where
    Claim: Clone + Serialize + Digestible + fmt::Debug,
{
    fn fmt(&self, fmt: &mut fmt::Formatter<'_>) -> fmt::Result {
        fmt.debug_struct("WorkClaim")
            .field("claim", &self.claim)
            .field("work", &self.work)
            .finish()
    }
}

/// A compact representation of completed work within Proof of Verifiable Work (PoVW).
///
/// This struct contains a compact representation of the range of used nonces, along with the value
/// of the work. It is used to represent the work within a single execution.
// TODO(povw): Rename this to be more clear that this is just one representation of work? (in
// particular that this is the compact range representation).
#[derive(Clone, Debug, Serialize, Deserialize, BorshSerialize, BorshDeserialize)]
pub struct Work {
    /// Lowest nonce in the range, inclusive.
    pub nonce_min: PovwNonce,
    /// Highest nonce in the range, inclusive.
    pub nonce_max: PovwNonce,
    /// Value of work (e.g. cycles) accumulated.
    pub value: u64,
}

fn u64_to_u16s(x: u64) -> [u16; 4] {
    let mut u16s = bytemuck::cast::<_, [u16; 4]>(x.to_le_bytes());
    // Bytes are little-endian, so on a big-endian machine, they need to be reversed.
    for x in u16s.iter_mut() {
        *x = u16::from_le(*x);
    }
    u16s
}

impl Digestible for Work {
    /// Hash the [ReceiptClaim] to get a digest of the struct.
    fn digest<S: Sha256>(&self) -> Digest {
        tagged_struct::<S>(
            "risc0.Work",
            &Vec::<Digest>::new(),
            &[
                self.nonce_min.to_u16s().as_slice(),
                self.nonce_max.to_u16s().as_slice(),
                u64_to_u16s(self.value).as_slice(),
            ]
            .into_iter()
            .flatten()
            .copied()
            .map(u32::from)
            .collect::<Vec<_>>(),
        )
    }
}
