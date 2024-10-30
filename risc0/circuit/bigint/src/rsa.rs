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

use num_bigint::BigUint;
#[cfg(feature = "bigint-dig-shim")]
use num_bigint_dig::BigUint as BigUintDig;

use crate::{BigIntClaim, BigIntProgram};

// Re-export program info
pub use crate::generated::{RSA_256_X1, RSA_256_X2, RSA_3072_X1, RSA_3072_X15};

/// Construct a bigint claim that (S^e = M (mod N)), where e = 65537.
pub fn claim(prog_info: &BigIntProgram, n: BigUint, s: BigUint, m: BigUint) -> BigIntClaim {
    BigIntClaim::from_biguints(prog_info, &[n, s, m])
}

/// Construct a bigint claim that (S^e = M (mod N)), where e = 65537, using num-bigint-dig
#[cfg(feature = "bigint-dig-shim")]
pub fn claim_dig(prog_info: &BigIntProgram, n: &BigUintDig, s: &BigUintDig, m: &BigUintDig) -> BigIntClaim {
    // TODO: Investigate how expensive this shim is
    let n = BigUint::from_bytes_le(&n.to_bytes_le());
    let s = BigUint::from_bytes_le(&s.to_bytes_le());
    let m = BigUint::from_bytes_le(&m.to_bytes_le());

    BigIntClaim::from_biguints(prog_info, &[n, s, m])
}


// TODO: Better name
/// Compute M = S^e (mod N), where e = 65537, using num-bigint-dig, and return the `claim` to prove this
#[cfg(feature = "bigint-dig-shim")]
pub fn claim_dig(prog_info: &BigIntProgram, n: &BigUintDig, s: &BigUintDig) -> Result<BigIntClaim> {
    // TODO: Investigate how expensive this shim is
    let mut n = n.to_u32_digits();
    let mut s = s.to_u32_digits();
    // TODO: don't use magic number 96
    if (n.len() > 96 || s.len() > 96) {
        return Err("TODO: Message for oversized inputs");
    }
    n.resize(96, 0);
    s.resize(96, 0);
    let n: [u32; 96] = n.try_into()?;
    let s: [u32; 96] = s.try_into()?;
    n.map(|elem| elem.to_le());
    s.map(|elem| elem.to_le());
    // TODO: Nicer way to provide an empty output buffer?
    const fn zero() -> u32 { 0 }
    let mut m = [zero(); 96];
    // TODO: Write up the unsafe
    unsafe {
        sys_rsa(&mut m, &s, &n);
    }

            let n = BigUint::from_bytes_le(&n.to_bytes_le());
            let s = BigUint::from_bytes_le(&s.to_bytes_le());

                let n_claim = n.clone();
                let s_claim = s.clone();
                // let m = from_hex("1fb897fac8aa8870b936631d3af1a17930c8af0ca4376b3056677ded52adf5aa");
                // println!("The bitwidth of n is {}", n.bits());
                let mut n = n.to_u32_digits();  // Ugh `mut` what a hack TODO
                n.resize(96, 0); // TODO: need more care
                let n: [u32; 96] = n.try_into().expect("modulus should fit in 96 32-bit words");
                let mut s = s.to_u32_digits();  // Ugh `mut` what a hack TODO
                s.resize(96, 0); // TODO: need more care
                let s: [u32; 96] = s.try_into().expect("base should fit in 96 32-bit words");
                // TODO: Feels a bit hacky
                const fn zero() -> u32 {
                    0
                }
                let mut m = [zero(); 96];  // TODO: Feels a bit hacky
                unsafe {
                    sys_rsa(&mut m, &s, &n);  // TODO: Actually manage the 3 inputs (first is buffer for output) and call
                }
                // let m_claim = BigUint::from_bytes_le(m.map(|elem| elem.to_le_bytes()).flatten());
                // TODO: This code should be replaced with the `flatten` code above once `flatten` is stable
                let m_words = m.map(|elem| elem.to_le_bytes());
                let mut m_claim = Vec::<u8>::new();  // TODO: Clean up style
                for word in m_words {
                    for byte in word {
                        m_claim.push(byte);
                    }
                }
                let m_claim = BigUint::from_bytes_le(&m_claim);
                let claims = vec![[n_claim, s_claim, m_claim]];

    BigIntClaim::from_biguints(prog_info, &[n, s, m])
}
