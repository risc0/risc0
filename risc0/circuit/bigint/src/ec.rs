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

use crate::{BigIntClaim, BigIntProgram};

// Re-export program info
pub use crate::generated::EC_MUL_SECP256K1;

/// Construct a bigint claim that `s * (x, y) = (u, v)` on secp256k1
///
/// Specifically, for (x, y) already known to be an affine point on secp256k1 in affine coordinates
pub fn mul_claim(prog_info: &BigIntProgram, x: BigUint, y: BigUint, s: BigUint, u: BigUint, v: BigUint) -> BigIntClaim {
    BigIntClaim::from_biguints(prog_info, &[x, y, s, u, v])
}
