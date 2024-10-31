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

#[cfg(test)]
#[cfg(feature = "prove")]
mod tests;

use anyhow::{bail, Result};
use num_bigint::BigUint;
#[cfg(feature = "bigint-dig-shim")]
use num_bigint_dig::BigUint as BigUintDig;
use risc0_zkvm_platform::syscall::sys_rsa;

use crate::{BigIntClaim, BigIntProgram};
#[cfg(all(target_os = "zkvm", target_arch = "riscv32"))]
use crate::prove;
#[cfg(all(target_os = "zkvm", target_arch = "riscv32"))]
use risc0_zkvm::guest::env;

// Re-export program info
pub use crate::generated::{RSA_256_X1, RSA_256_X2, RSA_3072_X1, RSA_3072_X15};

/// Construct a bigint claim that (S^e = M (mod N)), where e = 65537.
pub fn claim(prog_info: &BigIntProgram, n: BigUint, s: BigUint, m: BigUint) -> BigIntClaim {
    BigIntClaim::from_biguints(prog_info, &[n, s, m])
}

/// Compute M = S^e (mod N), where e = 65537, including an accelerated proof that the computation is correct
#[cfg(all(target_os = "zkvm", target_arch = "riscv32"))]
#[cfg(not(feature = "bigint-dig-shim"))]
pub fn modpow_65537(n: &BigUint, s: &BigUint) -> Result<BigUint> {
    // TODO: Untested!
    // TODO: clean up to escalate error
    let claims = compute_claim_inner(n.to_u32_digits(), s.to_u32_digits()).expect("TODO");
    // TODO: wild hacks, clean up
    let expected = BigUint::from_bytes_le(&claims[2].to_bytes_le());
    let claims = [claims[0].clone(), claims[1].clone(), claims[2].clone()];
    let claims = BigIntClaim::from_biguints(&RSA_3072_X1, &claims);
    prove(&RSA_3072_X1, &[claims]).expect("Unable to compose with RSA");
    env::log("[TODO] `rsa_encrypt` ending");
    return Ok(expected);
}

/// Compute M = S^e (mod N), where e = 65537, including an accelerated proof that the computation is correct
#[cfg(all(target_os = "zkvm", target_arch = "riscv32"))]
#[cfg(feature = "bigint-dig-shim")]
pub fn modpow_65537(n: &BigUintDig, s: &BigUintDig) -> Result<BigUintDig> {
    // TODO: clean up to escalate error
    // let claims = compute_claim(n, s).expect("TODO");
    let mut n_vec = Vec::<u32>::new();
    for word in n.to_bytes_le().chunks(4) {
        let word: [u8; 4] = word.try_into()?;  // TODO: What about the "first byte (only) is zero case?"
        n_vec.push(u32::from_le_bytes(word));
    }
    let mut s_vec = Vec::<u32>::new();
    for word in s.to_bytes_le().chunks(4) {
        let word: [u8; 4] = word.try_into()?;  // TODO: What about the "first byte (only) is zero case?"
        s_vec.push(u32::from_le_bytes(word));
    }
    let claims = compute_claim_inner(n_vec, s_vec).expect("TODO");
    // TODO: wild hacks, clean up
    let expected = BigUintDig::from_bytes_le(&claims[2].to_bytes_le());
    let claims = [claims[0].clone(), claims[1].clone(), claims[2].clone()];
    let claims = BigIntClaim::from_biguints(&RSA_3072_X1, &claims);
    prove(&RSA_3072_X1, &[claims]).expect("Unable to compose with RSA");
    env::log("[TODO] `rsa_encrypt` ending");
    return Ok(expected);
}


// TODO: Better name
/// Compute M = S^e (mod N), where e = 65537, using num-bigint-dig, and return the `claim` to prove this
pub fn compute_claim_inner(mut n: Vec<u32>, mut s: Vec<u32>) -> Result<[BigUint; 3]> {
    // TODO: Investigate how expensive this shim is
    // TODO: don't use magic number 96
    if n.len() > 96 || s.len() > 96 {
        bail!("TODO: Message for oversized inputs");
    }
    n.resize(96, 0);
    s.resize(96, 0);
    let n: [u32; 96] = (*n).try_into().expect("TODO: can this be ?");
    let s: [u32; 96] = (*s).try_into().expect("TODO: can this be ?");
    // TODO: I think we have to be in the guest and so I think the endianness work in this function is overdone; review and clean up
    n.map(|elem| elem.to_le());
    s.map(|elem| elem.to_le());
    // TODO: Nicer way to provide an empty output buffer?
    const fn zero() -> u32 { 0 }
    let mut m = [zero(); 96];
    // TODO: Write up the unsafe
    unsafe {
        sys_rsa(&mut m, &s, &n);
    }
    // let m_claim = BigUint::from_bytes_le(m.map(|elem| elem.to_le_bytes()).flatten());
    // let s_claim = BigUint::from_bytes_le(s.map(|elem| elem.to_le_bytes()).flatten());
    // let n_claim = BigUint::from_bytes_le(n.map(|elem| elem.to_le_bytes()).flatten());
    // TODO: This code should be replaced with the `flatten` code above once `flatten` is stable
    let m_words = m.map(|elem| elem.to_le_bytes());
    let mut m_claim = Vec::<u8>::new();  // TODO: Clean up style
    for word in m_words {
        for byte in word {
            m_claim.push(byte);
        }
    }
    let m_claim = BigUint::from_bytes_le(&m_claim);
    let s_words = s.map(|elem| elem.to_le_bytes());
    let mut s_claim = Vec::<u8>::new();  // TODO: Clean up style
    for word in s_words {
        for byte in word {
            s_claim.push(byte);
        }
    }
    let s_claim = BigUint::from_bytes_le(&s_claim);
    let n_words = n.map(|elem| elem.to_le_bytes());
    let mut n_claim = Vec::<u8>::new();  // TODO: Clean up style
    for word in n_words {
        for byte in word {
            n_claim.push(byte);
        }
    }
    let n_claim = BigUint::from_bytes_le(&n_claim);
    Ok([n_claim, s_claim, m_claim])
}
