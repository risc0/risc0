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
    // TODO: switch away from example inputs
    let inp: Vec<(Vec<u8>, Vec<u8>, Vec<u8>, Vec<u8>, Vec<u8>, Vec<u8>, Vec<u8>)> = env::read();
    let mut pairs = Vec::new();
    for entry in inp {
        let g1x = Fq::from_slice(&entry.0).expect("Normalized Fq expected for g1x");
        let g1y = Fq::from_slice(&entry.1).expect("Normalized Fq expected for g1y");
        let g2x_i = Fq::from_slice(&entry.2).expect("Normalized Fq expected for g2x_r");
        let g2x_r = Fq::from_slice(&entry.3).expect("Normalized Fq expected for g2x_i");
        let g2x = Fq2::new(g2x_r, g2x_i);
        let g2y_i = Fq::from_slice(&entry.4).expect("Normalized Fq expected for g2y_r");
        let g2y_r = Fq::from_slice(&entry.5).expect("Normalized Fq expected for g2y_i");
        let g2y = Fq2::new(g2y_r, g2y_i);
        let g1 = G1::from(AffineG1::new(g1x, g1y).expect("Point on G1 expected"));
        let g2 = G2::from(AffineG2::new(g2x, g2y).expect("Point on G2 expected"));
        // TODO
        let scalar = Fr::from_slice(&entry.6).expect("Scalar factor expected");
        assert_eq!(scalar, Fr::one());
        let scalar_inv = scalar.inverse().expect("Scalar is invertible");
        assert_eq!(scalar_inv, Fr::one());
        let g1_alt = g1 * scalar;
        assert_eq!(g1, g1_alt);
        let g2_alt = g2 * scalar_inv;
        assert_eq!(g2, g2_alt);
        // / TODO
        pairs.push((g1, g2));
        // break;  // TODO
    }
    let result = pairing_batch(&pairs);
    
    env::commit(&(result == Gt::one()));
}
