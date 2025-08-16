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

use risc0_zkvm::guest::env;
use substrate_bn::{Fr, G1, G2, Gt, pairing_batch};

fn main() {
    let inp: bn254_core::Inputs = env::read();

    let g1 = G1::from_compressed(&inp.g1_compressed).expect("Point on G1 expected");
    let g2 = G2::from_compressed(&inp.g2_compressed).expect("Point on G2 expected");
    let a_factor = Fr::from_slice(&inp.a).expect("Scalar factor expected");
    let b_factor = Fr::from_slice(&inp.b).expect("Scalar factor expected");

    let mut pairs = Vec::new();
    pairs.push((g1 * a_factor, g2 * b_factor));
    pairs.push((g1, g2 * (-a_factor * b_factor)));
    let result = pairing_batch(&pairs);

    env::commit(&(result == Gt::one()));
}
