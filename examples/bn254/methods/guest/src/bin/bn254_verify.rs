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

use substrate_bn::{AffineG1, AffineG2, Fq, Fq2, Fr, G1, G2, Gt, pairing_batch};
use risc0_zkvm::guest::env;

fn main() {
    // TODO: Don't need this assert, just confirming
    assert_eq!(G2::b() * (
        (Fq2::one() + Fq2::one() + Fq2::one() + Fq2::one() + Fq2::one() + Fq2::one() + Fq2::one() + Fq2::one() + Fq2::one()) + Fq2::i()),
        (Fq2::one() + Fq2::one() + Fq2::one())
    );
    // TODO above

    // TODO: switch away from example inputs
    let inp: (Vec<u8>, Vec<u8>, Vec<u8>, Vec<u8>) = env::read();
    // let g1x = Fq::from_slice(&inp.0).expect("Normalized Fq expected for g1x");
    // let g1y = Fq::from_slice(&inp.1).expect("Normalized Fq expected for g1y");
    // let g2x_i = Fq::from_slice(&inp.2).expect("Normalized Fq expected for g2x_r");
    // let g2x_r = Fq::from_slice(&inp.3).expect("Normalized Fq expected for g2x_i");
    // let g2x = Fq2::new(g2x_r, g2x_i);
    // let g2y_i = Fq::from_slice(&inp.4).expect("Normalized Fq expected for g2y_r");
    // let g2y_r = Fq::from_slice(&inp.5).expect("Normalized Fq expected for g2y_i");
    // let g2y = Fq2::new(g2y_r, g2y_i);
    // let g1 = G1::from(AffineG1::new(g1x, g1y).expect("Point on G1 expected"));
    // let g2 = G2::from(AffineG2::new(g2x, g2y).expect("Point on G2 expected"));
    let g1 = G1::from_compressed(&inp.0).expect("Point on G1 expected");
    let g2 = G2::from_compressed(&inp.1).expect("Point on G2 expected");
    let a_factor = Fr::from_slice(&inp.2).expect("Scalar factor expected");
    let b_factor = Fr::from_slice(&inp.3).expect("Scalar factor expected");

    let mut pairs = Vec::new();
    pairs.push((g1 * a_factor, g2 * b_factor));
    pairs.push((g1, g2 * (-a_factor * b_factor)));
    let result = pairing_batch(&pairs);
    
    env::commit(&(result == Gt::one()));
}
