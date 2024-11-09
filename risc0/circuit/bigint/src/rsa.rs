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

#[cfg(test)]
#[cfg(feature = "prove")]
#[cfg(feature = "bigint-dig-shim")]
mod tests_dig;

use num_bigint::BigUint;
#[cfg(all(target_os = "zkvm", target_arch = "riscv32"))]
use num_traits::ops::bytes::ToBytes;
#[cfg(all(target_os = "zkvm", target_arch = "riscv32"))]
use risc0_zkvm_platform::syscall::sys_rsa;


#[cfg(all(target_os = "zkvm", target_arch = "riscv32"))]
use crate::prove;
use crate::{BigIntClaim, BigIntProgram};

// Re-export program info
pub use crate::generated::{RSA_256_X1, RSA_256_X2, RSA_3072_X1, RSA_3072_X15};

// Re-export RSA syscall width
pub use risc0_zkvm_platform::syscall::rsa::WIDTH_WORDS;

/// Construct a bigint claim that (S^e = M (mod N)), where e = 65537.
///
/// `S` is the `base``, `N` is the `modulus`, and `M` is the `result`
pub fn claim(
    prog_info: &BigIntProgram,
    modulus: BigUint,
    base: BigUint,
    result: BigUint,
) -> BigIntClaim {
    BigIntClaim::from_biguints(prog_info, &[modulus, base, result])
}

/// Compute M = S^e (mod N), where e = 65537, including an accelerated proof that the computation is correct
///
/// (`S` is the `base`, `N` is the `modulus`, and `M` is the `result`.)
/// 
/// Parameters are 3072 bits, given as 96 32-bit words (little endian). Zero-pad if using smaller values.
/// 
/// # Safety
///
/// `result`, `base`, and `modulus` must be aligned and dereferenceable.
// #[stability::unstable]  // TODO
#[cfg(all(target_os = "zkvm", target_arch = "riscv32"))]
#[no_mangle]
pub unsafe extern "C" fn modpow_65537(
    result: *mut [u32; WIDTH_WORDS],
    base: *const [u32; WIDTH_WORDS],
    modulus: *const [u32; WIDTH_WORDS],
) {
    unsafe {
        sys_rsa(result, base, modulus);
    }
    let result = (&*result)
        .iter()
        .flat_map(|elem| elem.to_le_bytes())
        .collect::<Vec<u8>>();
    let result = BigUint::from_bytes_le(&result);
    let base = (&*base)
        .iter()
        .flat_map(|elem| elem.to_le_bytes())
        .collect::<Vec<u8>>();
    let base = BigUint::from_bytes_le(&base);
    let modulus = (&*modulus)
        .iter()
        .flat_map(|elem| elem.to_le_bytes())
        .collect::<Vec<u8>>();
    let modulus = BigUint::from_bytes_le(&modulus);
    let claims = BigIntClaim::from_biguints(&RSA_3072_X1, &[modulus, base, result]);
    prove(&RSA_3072_X1, &[claims]).expect("Unable to compose with RSA");
}
