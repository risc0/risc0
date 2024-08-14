// Copyright (c) 2024 RISC Zero, Inc.
//
// All rights reserved.

use crate::{BigIntClaim, BigIntProgram, BytePoly};
use num_bigint::BigUint;

// Re-export program info
pub use crate::generated::{RSA_256_X1, RSA_256_X2, RSA_3072_X15};

/// Construct a bigint claim that (S^e = M (mod N)), where e = 65537.
pub fn claim(prog_info: &BigIntProgram, n: BigUint, s: BigUint, m: BigUint) -> BigIntClaim {
    let pub_witness: Vec<BytePoly> = [n, s, m]
        .into_iter()
        .zip(prog_info.witness_info.iter())
        .map(|(val, wit_info)| BytePoly::from_biguint(val, wit_info.coeffs()))
        .collect();
    BigIntClaim::new(pub_witness)
}
