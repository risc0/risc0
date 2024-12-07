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

use risc0_circuit_keccak::KECCAK_CONTROL_ROOT;
use risc0_zkvm::{guest::env, sha::Digest};
use risc0_zkvm_platform::syscall::sys_prove_keccak;

// Computes and proves the result of a given keccak input transcript
fn main() {
    let (po2, claim_digest, input): (u32, Digest, Vec<u32>) = env::read();

    unsafe {
        sys_prove_keccak(
            po2 as usize,
            input.as_ptr(),
            input.len(),
            KECCAK_CONTROL_ROOT.as_ref(),
        );
    }
    env::verify_assumption(claim_digest, KECCAK_CONTROL_ROOT).unwrap();
}
