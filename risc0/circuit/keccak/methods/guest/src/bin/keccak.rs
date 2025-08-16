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

use risc0_circuit_keccak::{KECCAK_CONTROL_ROOT, KeccakState};
use risc0_zkvm::{guest::env, sha::Digest};
use risc0_zkvm_platform::syscall::{sys_keccak, sys_prove_keccak};

// Computes and proves the result of a given keccak input transcript
fn main() {
    let (claim_digest, po2): (Digest, u32) = env::read();

    for mut input in generate_input(po2 as usize) {
        unsafe { sys_keccak(&input, &mut input) };
    }

    unsafe {
        sys_prove_keccak(claim_digest.as_ref(), KECCAK_CONTROL_ROOT.as_ref());
    }
    env::verify_assumption2(claim_digest, KECCAK_CONTROL_ROOT).unwrap();
}

fn generate_input(po2: usize) -> Vec<KeccakState> {
    let mut state = KeccakState::default();
    let mut pows = 987654321_u64;
    for part in state.as_mut_slice() {
        *part = pows;
        pows = pows.wrapping_mul(123456789);
    }

    let cycles = 1 << po2;
    let count = cycles / 200; // roughly 200 cycles per keccakf
    vec![state; count]
}
