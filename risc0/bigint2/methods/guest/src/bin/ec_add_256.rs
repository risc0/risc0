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

use risc0_bigint2::ec::{AffinePoint, Secp256k1Curve};
use risc0_zkvm::guest::env;

fn input_point() -> AffinePoint<8, Secp256k1Curve> {
    let point: Option<[[u32; 8]; 2]> = env::read();
    point
        .map(|[x, y]| AffinePoint::new_unchecked(x, y))
        .unwrap_or(AffinePoint::IDENTITY)
}

fn main() {
    let lhs = input_point();
    let rhs = input_point();

    let mut result = AffinePoint::<8, Secp256k1Curve>::IDENTITY;
    lhs.add(&rhs, &mut result);

    env::commit(&result.as_u32s());
}
