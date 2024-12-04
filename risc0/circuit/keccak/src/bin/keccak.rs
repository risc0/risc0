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

use risc0_circuit_keccak::prove::{keccak_prover, KeccakState};

fn main() {
    let mut state = KeccakState::default();
    let mut pows = 987654321_u64;
    for part in state.as_mut_slice() {
        *part = pows;
        pows = pows.wrapping_mul(123456789);
    }

    let po2 = 17; // 128K
    let cycles = 1 << po2;
    let count = cycles / 200; // roughly 200 cycles per keccakf
    let inputs = vec![state; count];

    let prover = keccak_prover().unwrap();
    let seal = prover.prove(&inputs, po2).unwrap();
    prover.verify(&seal).expect("Verification failed");
}
