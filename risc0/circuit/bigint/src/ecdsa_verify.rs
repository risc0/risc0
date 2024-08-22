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
pub use crate::generated::ECDSA_VERIFY_8;

/// Construct a bigint claim of an ECDSA Verification  // TODO: From here
pub fn claim(
    prog_info: &BigIntProgram,
    base_pt_x: BigUint,
    base_pt_y: BigUint,
    base_pt_order: BigUint,
    pub_key_x: BigUint,
    pub_key_y: BigUint,
    msg_hash: BigUint,
    r: BigUint,
    s: BigUint,
    arbitrary_x: BigUint,
    arbitrary_y: BigUint,
) -> BigIntClaim {
    BigIntClaim::from_biguints(prog_info, &[
        base_pt_x,
        base_pt_y,
        base_pt_order,
        pub_key_x,
        pub_key_y,
        msg_hash,
        r,
        s,
        arbitrary_x,
        arbitrary_y,
    ])
}
