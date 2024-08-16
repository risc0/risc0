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
    let pub_witness: Vec<BytePoly> = [
        prime,
        a,
        b,
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
    ]
    .into_iter()
    .zip(prog_info.witness_info.iter())
    .map(|(val, wit_info)| BytePoly::from_biguint(val, wit_info.coeffs()))
    .collect();
    BigIntClaim::new(pub_witness)
}
