// Copyright 2024 RISC Zero, Inc.
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

use anyhow::Result;
use risc0_zkp::core::digest::Digest;
use risc0_zkvm::guest::env;

/// Generates a proof of a set of keccak hashes.  claim_digest should
/// be the final sha computed by the keccak circuit, and input should
/// contain the input transcript.
pub fn prove(claim_digest: Digest, input: &[u32], po2: usize) -> Result<()> {
    let control_root = crate::get_control_root(po2);
    unsafe {
        risc0_zkvm_platform::syscall::sys_prove_keccak(
            po2,
            input.as_ptr(),
            input.len(),
            control_root.as_ref(),
        );
    }
    env::verify_assumption(claim_digest, *control_root)?;

    Ok(())
}
