// Copyright (c) 2024 RISC Zero, Inc.
//
// All rights reserved.

use crate::{BigIntClaim, BigIntProgram, BytePoly};
use num_bigint::BigUint;

pub(crate) mod generated {
    #![allow(dead_code)]

    use crate::codegen_prelude::*;
    include! {"bigint.rs.inc"}
}

// Re-export program info
pub use generated::ECDSA_VERIFY_8;

/// Construct a bigint claim of an ECDSA Verification  // TODO: From here
pub fn claim(
    prog_info: &BigIntProgram,
    prime: BigUint,
    a: BigUint,
    b: BigUint,
    base_pt_X: BigUint,
    base_pt_Y: BigUint,
    base_pt_order: BigUint,
    pub_key_X: BigUint,
    pub_key_Y: BigUint,
    msg_hash: BigUint,
    r: BigUint,
    s: BigUint,
    arbitrary_X: BigUint,
    arbitrary_Y: BigUint,
) -> BigIntClaim {
    let pub_witness: Vec<BytePoly> = [
        prime,
        a,
        b,
        base_pt_X,
        base_pt_Y,
        base_pt_order,
        pub_key_X,
        pub_key_Y,
        msg_hash,
        r,
        s,
        arbitrary_X,
        arbitrary_Y,
    ]
    .into_iter()
    .zip(prog_info.witness_info.iter())
    .map(|(val, wit_info)| BytePoly::from_biguint(val, wit_info.coeffs()))
    .collect();
    BigIntClaim::new(pub_witness)
}
