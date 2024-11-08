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

#[cfg(all(target_os = "zkvm", target_arch = "riscv32"))]
use anyhow::{bail, Result};
use num_bigint::BigUint;
#[cfg(all(target_os = "zkvm", target_arch = "riscv32"))]
#[cfg(feature = "bigint-dig-shim")]
use num_bigint_dig::BigUint as BigUintDig;
#[cfg(all(target_os = "zkvm", target_arch = "riscv32"))]
use risc0_zkvm_platform::{
    syscall::{rsa::WIDTH_BITS, rsa::WIDTH_WORDS, sys_rsa},
    WORD_SIZE,
};

// TODO: Sort in
#[cfg(all(target_os = "zkvm", target_arch = "riscv32"))]
use num_traits::ops::bytes::ToBytes;

#[cfg(all(target_os = "zkvm", target_arch = "riscv32"))]
use crate::prove;
use crate::{BigIntClaim, BigIntProgram};

// Re-export program info
pub use crate::generated::{RSA_256_X1, RSA_256_X2, RSA_3072_X1, RSA_3072_X15};

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

// TODO: So this comes through as an extern just fine...
#[cfg(all(target_os = "zkvm", target_arch = "riscv32"))]
#[cfg(feature = "bigint-dig-shim")]
#[no_mangle]
pub fn todo_test_fn(x: u32) -> u32 {
    x
}

// TODO
#[no_mangle]
pub fn todo_test_types(test: &Vec<u32>) -> Result<Vec<u32>, &'static str> {
    let mut output = vec!{1u32};
    for elem in test {
        output.push(*elem);
    }
    if output.len() < 1 {
        return Err("test message");
    }
    Ok(output)
}

/// Compute M = S^e (mod N), where e = 65537, including an accelerated proof that the computation is correct
///
/// `S` is the `base`, `N` is the `modulus`, and the result `M` is returned
#[cfg(all(target_os = "zkvm", target_arch = "riscv32"))]
#[cfg(not(feature = "bigint-dig-shim"))]
#[no_mangle]
pub fn modpow_65537(base: &BigUint, modulus: &BigUint) -> Result<BigUint> {
    let claims = compute_claim_inner(base.to_u32_digits(), modulus.to_u32_digits())?;
    let result = claims[2].clone();
    let claims = BigIntClaim::from_biguints(&RSA_3072_X1, &claims);
    prove(&RSA_3072_X1, &[claims]).expect("Unable to compose with RSA");
    return Ok(result);
}

/// Compute M = S^e (mod N), where e = 65537, including an accelerated proof that the computation is correct
///
/// `S` is the `base`, `N` is the `modulus`, and the result `M` is returned
/// 
/// All are little endian
#[cfg(all(target_os = "zkvm", target_arch = "riscv32"))]
#[no_mangle]
pub fn modpow_65537_simple(base: &[u32], modulus: &[u32]) -> Result<Vec<u8>> {
    // TODO: Clean up where I have vecs vs. slices
    let base = base.to_vec();
    let modulus = modulus.to_vec();
    let claims = compute_claim_inner(base, modulus)?;
    let result = claims[2].clone().to_le_bytes();
    let claims = BigIntClaim::from_biguints(&RSA_3072_X1, &claims);
    prove(&RSA_3072_X1, &[claims]).expect("Unable to compose with RSA");
    return Ok(result);

    // // TODO: Not right, just hacking in a test
    // return Ok(base[0].to_le_bytes().to_vec());
}

// TODO: Document
#[cfg(all(target_os = "zkvm", target_arch = "riscv32"))]
#[no_mangle]
pub fn modpow_65537_vecs(base: Vec<u32>, modulus: Vec<u32>) -> Result<Vec<u8>> {
    // // TODO: Clean up where I have vecs vs. slices
    // let claims = compute_claim_inner(base, modulus)?;
    // let result = claims[2].clone().to_le_bytes();
    // let claims = BigIntClaim::from_biguints(&RSA_3072_X1, &claims);
    // prove(&RSA_3072_X1, &[claims]).expect("Unable to compose with RSA");
    // return Ok(result);

    // TODO: Not right, just hacking in a test
    return Ok(base[0].to_le_bytes().to_vec());
}

// // E.g.
// pub unsafe extern "C" fn env_commit(hasher: *mut sha256_state, bytes_ptr: *const u8, len: u32) {
// pub unsafe extern "C" fn env_read(bytes_ptr: *mut u8, len: u32) -> usize {

// // TODO: Document
// #[cfg(all(target_os = "zkvm", target_arch = "riscv32"))]
// #[no_mangle]
// pub extern "C" fn(base_ptr: *const u32, modulus_ptr: *const u32, base_len: u32, modulus_len: u32) -> TODO {

// }



/// Compute M = S^e (mod N), where e = 65537, including an accelerated proof that the computation is correct
///
/// `S` is the `base`, `N` is the `modulus`, and the result `M` is returned
#[cfg(all(target_os = "zkvm", target_arch = "riscv32"))]
#[cfg(feature = "bigint-dig-shim")]
#[no_mangle]
pub fn modpow_65537(base: &BigUintDig, modulus: &BigUintDig) -> Result<BigUintDig> {
    // Ensure inputs fill an even number of words
    let mut base = base.to_bytes_le();
    if base.len() % 4 != 0 {
        base.resize(base.len() + (4 - (base.len() % 4)), 0);
    }
    let mut modulus = modulus.to_bytes_le();
    if modulus.len() % 4 != 0 {
        modulus.resize(modulus.len() + (4 - (modulus.len() % 4)), 0);
    }
    // Convert inputs to Vecs of u32s
    let mut base_vec = Vec::new();
    for word in base.chunks(4) {
        let word: [u8; 4] = word.try_into()?;
        base_vec.push(u32::from_le_bytes(word));
    }
    let mut modulus_vec = Vec::<u32>::new();
    for word in modulus.chunks(4) {
        let word: [u8; 4] = word.try_into()?;
        modulus_vec.push(u32::from_le_bytes(word));
    }
    let claims = compute_claim_inner(base_vec, modulus_vec)?;
    let result = BigUintDig::from_bytes_le(&claims[2].to_bytes_le()).clone();
    let claims = BigIntClaim::from_biguints(&RSA_3072_X1, &claims);
    prove(&RSA_3072_X1, &[claims]).expect("Unable to compose with RSA");
    return Ok(result);
    // return Ok(base.clone());  // TODO: Wrong answer, just to test
}

/// Compute M = S^e (mod N), where e = 65537, and return the `claim` to prove this
///
/// `S` is the `base` and `N` is the `modulus`.
///
/// The return value has the claim inputs expected by the RSA accelerator, in the expected order, which is [modulus, base, result]
#[cfg(all(target_os = "zkvm", target_arch = "riscv32"))]
fn compute_claim_inner(mut base: Vec<u32>, mut modulus: Vec<u32>) -> Result<[BigUint; 3]> {
    assert!(WORD_SIZE == 4);
    if modulus.len() > WIDTH_WORDS || base.len() > WIDTH_WORDS {
        bail!("RSA acceleration supports up to {} bits, but received {} u32s for the modulus and {} u32s for the base.", WIDTH_BITS, modulus.len(), base.len());
    }
    modulus.resize(WIDTH_WORDS, 0);
    base.resize(WIDTH_WORDS, 0);
    let modulus: [u32; WIDTH_WORDS] = (*modulus).try_into()?;
    let base: [u32; WIDTH_WORDS] = (*base).try_into()?;
    const fn zero() -> u32 {
        0
    }
    let mut result = [zero(); WIDTH_WORDS];
    // Safety: inputs are aligned and dereferenceable
    unsafe {
        sys_rsa(&mut result, &base, &modulus);
    }
    let result = result
        .iter()
        .flat_map(|elem| elem.to_le_bytes())
        .collect::<Vec<u8>>();
    let result = BigUint::from_bytes_le(&result);
    let base = base
        .iter()
        .flat_map(|elem| elem.to_le_bytes())
        .collect::<Vec<u8>>();
    let base = BigUint::from_bytes_le(&base);
    let modulus = modulus
        .iter()
        .flat_map(|elem| elem.to_le_bytes())
        .collect::<Vec<u8>>();
    let modulus = BigUint::from_bytes_le(&modulus);
    Ok([modulus, base, result])
}

/// Compute and prove the modpow_65537 RSA operation
/// 
/// Uses the same signature as the `sys_rsa` syscall.
/// 
/// # Safety
///
/// `recv_buf`, `in_base`, and `in_modulus` must be aligned and dereferenceable.
#[stability::unstable]
#[cfg(all(target_os = "zkvm", target_arch = "riscv32"))]
#[no_mangle]
pub unsafe extern "C" fn sys_rsa_and_prove(  // TODO: Better name
    recv_buf: *mut [u32; risc0_zkvm_platform::syscall::rsa::WIDTH_WORDS],  // TODO nicer constant
    in_base: *const [u32; risc0_zkvm_platform::syscall::rsa::WIDTH_WORDS],
    in_modulus: *const [u32; risc0_zkvm_platform::syscall::rsa::WIDTH_WORDS],
) {
    unsafe {
        risc0_zkvm_platform::syscall::sys_rsa(recv_buf, in_base, in_modulus);
    }
    let result = (&*recv_buf)
        .iter()
        .flat_map(|elem| elem.to_le_bytes())
        .collect::<Vec<u8>>();
    let result = BigUint::from_bytes_le(&result);
    let base = (&*in_base)
        .iter()
        .flat_map(|elem| elem.to_le_bytes())
        .collect::<Vec<u8>>();
    let base = BigUint::from_bytes_le(&base);
    let modulus = (&*in_modulus)
        .iter()
        .flat_map(|elem| elem.to_le_bytes())
        .collect::<Vec<u8>>();
    let modulus = BigUint::from_bytes_le(&modulus);
    let claims = BigIntClaim::from_biguints(&RSA_3072_X1, &[modulus, base, result]);
    prove(&RSA_3072_X1, &[claims]).expect("Unable to compose with RSA");
}
