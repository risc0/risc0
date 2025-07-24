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

//! # Groth16 Prover

#[cfg(feature = "cuda_experimental")]
mod cuda;
#[cfg(not(feature = "cuda_experimental"))]
mod docker;
mod seal_format;
mod seal_to_json;

use anyhow::Result;

use crate::Seal;

/// Produce a Groth16 proof from an `identity_p254` seal.
pub fn shrink_wrap(identity_p254_seal_bytes: &[u8]) -> Result<Seal> {
    cfg_if::cfg_if! {
        if #[cfg(feature = "cuda_experimental")] {
            self::cuda::shrink_wrap(identity_p254_seal_bytes)
        } else {
            self::docker::shrink_wrap(identity_p254_seal_bytes)
        }
    }
}
