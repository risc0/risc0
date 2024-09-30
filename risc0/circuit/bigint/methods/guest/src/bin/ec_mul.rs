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

use num_bigint::BigUint;
use risc0_circuit_bigint::ec;
use risc0_zkvm::guest::env;

fn main() {
    // Read EC Mul input values
    let input: Vec<[BigUint; 5]> = env::read();
    let claims: Vec<_> = input
        .into_iter()
        .map(|[x, y, s, u, v]| ec::mul_claim(&ec::EC_MUL_SECP256K1, x, y, s, u, v))
        .collect();
    risc0_circuit_bigint::prove(&ec::EC_MUL_SECP256K1, &claims).expect("Unable to compose with EC Mul");
}
