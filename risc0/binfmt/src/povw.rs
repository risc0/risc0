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

//! Core types for function specific to proof of verifiable work (PoVW).

use ruint::aliases::{U160, U256};
use serde::{Deserialize, Serialize};

/// TODO
pub type WorkLogId = U160;

/// TODO
#[derive(Copy, Clone, Debug, Serialize, Deserialize)]
pub struct PovwNonce {
    /// TODO
    pub log: WorkLogId,
    /// TODO
    pub job: u64,
    /// TODO
    pub segment: u32,
}

impl From<PovwNonce> for U256 {
    /// Convert a [PovwNonce] to its [U256] representation.
    fn from(value: PovwNonce) -> Self {
        (value.log.to::<U256>() << 96) | (U256::from(value.job) << 32) | U256::from(value.segment)
    }
}

impl From<U256> for PovwNonce {
    /// Convert a [U256] to a [PovwNonce].
    ///
    /// All [U256] can be mapped to a unique PoVW nonce.
    fn from(value: U256) -> Self {
        Self {
            log: (value >> 96usize).to(),
            job: ((value >> 32usize) & U256::from(u64::MAX)).to(),
            segment: (value & U256::from(u32::MAX)).to(),
        }
    }
}
