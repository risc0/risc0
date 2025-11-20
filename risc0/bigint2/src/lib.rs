// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

#[cfg(test)]
#[cfg(feature = "num-bigint-dig")]
extern crate num_bigint_dig as num_bigint;

pub mod ec;
pub mod ffi;
pub mod field;
pub mod rsa;

pub(crate) const WORD_SIZE: usize = 4;

/// Trait for converting values to a u32 array to be used for bigint2 acceleration.
pub trait ToBigInt2Buffer<const WIDTH: usize> {
    /// Convert value to a u32 array to be used for bigint2 acceleration.
    fn to_u32_array(&self) -> [u32; WIDTH];

    /// Convert from array into the original type.
    fn from_u32_array(array: [u32; WIDTH]) -> Self;
}

#[inline]
// Checks if two u32 arrays representing big integers with little-endian digit order satisfy lhs < rhs
fn is_less<const N: usize>(lhs: &[u32; N], rhs: &[u32; N]) -> bool {
    for i in (0..N).rev() {
        if lhs[i] < rhs[i] {
            return true;
        }
        if lhs[i] > rhs[i] {
            return false;
        }
    }
    false
}

// DO NOT MERGE
pub fn print_blob_addr_table() {
    use crate::ec::{ADD_256_BLOB, ADD_384_BLOB, DOUBLE_256_BLOB, DOUBLE_384_BLOB};
    use crate::field::unchecked::{
        EXTFIELD_DEG2_ADD_256_BLOB, EXTFIELD_DEG2_ADD_384_BLOB, EXTFIELD_DEG2_MUL_256_BLOB,
        EXTFIELD_DEG2_SUB_256_BLOB, EXTFIELD_DEG2_SUB_384_BLOB, EXTFIELD_DEG4_MUL_256_BLOB,
        EXTFIELD_XXONE_MUL_256_BLOB, EXTFIELD_XXONE_MUL_384_BLOB, MODADD_256_BLOB, MODADD_384_BLOB,
        MODINV_256_BLOB, MODINV_384_BLOB, MODMUL_256_BLOB, MODMUL_384_BLOB, MODMUL_4096_BLOB,
        MODSUB_256_BLOB, MODSUB_384_BLOB,
    };

    println!("bigint2 blob addrs");
    println!(
        "ec_add_256_blob: addr {:p} size {}",
        ADD_256_BLOB.as_ptr(),
        ADD_256_BLOB.len()
    );
    println!(
        "ec_double_256_blob: addr {:p} size {}",
        DOUBLE_256_BLOB.as_ptr(),
        DOUBLE_256_BLOB.len()
    );
    println!(
        "ec_add_384_blob: addr {:p} size {}",
        ADD_384_BLOB.as_ptr(),
        ADD_384_BLOB.len()
    );
    println!(
        "ec_double_384_blob: addr {:p} size {}",
        DOUBLE_384_BLOB.as_ptr(),
        DOUBLE_384_BLOB.len()
    );
    println!(
        "ec_modadd_256_blob: addr {:p} size {}",
        MODADD_256_BLOB.as_ptr(),
        MODADD_256_BLOB.len()
    );
    println!(
        "ec_modadd_384_blob: addr {:p} size {}",
        MODADD_384_BLOB.as_ptr(),
        MODADD_384_BLOB.len()
    );
    println!(
        "ec_modinv_256_blob: addr {:p} size {}",
        MODINV_256_BLOB.as_ptr(),
        MODINV_256_BLOB.len()
    );
    println!(
        "ec_modinv_384_blob: addr {:p} size {}",
        MODINV_384_BLOB.as_ptr(),
        MODINV_384_BLOB.len()
    );
    println!(
        "ec_modmul_256_blob: addr {:p} size {}",
        MODMUL_256_BLOB.as_ptr(),
        MODMUL_256_BLOB.len()
    );
    println!(
        "ec_modmul_384_blob: addr {:p} size {}",
        MODMUL_384_BLOB.as_ptr(),
        MODMUL_384_BLOB.len()
    );
    println!(
        "ec_modmul_4096_blob: addr {:p} size {}",
        MODMUL_4096_BLOB.as_ptr(),
        MODMUL_4096_BLOB.len()
    );
    println!(
        "ec_modsub_256_blob: addr {:p} size {}",
        MODSUB_256_BLOB.as_ptr(),
        MODSUB_256_BLOB.len()
    );
    println!(
        "ec_modsub_384_blob: addr {:p} size {}",
        MODSUB_384_BLOB.as_ptr(),
        MODSUB_384_BLOB.len()
    );
    println!(
        "ec_extfield_deg2_add_256_blob: addr {:p} size {}",
        EXTFIELD_DEG2_ADD_256_BLOB.as_ptr(),
        EXTFIELD_DEG2_ADD_256_BLOB.len()
    );
    println!(
        "ec_extfield_deg2_add_384_blob: addr {:p} size {}",
        EXTFIELD_DEG2_ADD_384_BLOB.as_ptr(),
        EXTFIELD_DEG2_ADD_384_BLOB.len()
    );
    println!(
        "ec_extfield_deg2_mul_256_blob: addr {:p} size {}",
        EXTFIELD_DEG2_MUL_256_BLOB.as_ptr(),
        EXTFIELD_DEG2_MUL_256_BLOB.len()
    );
    println!(
        "ec_extfield_deg4_mul_256_blob: addr {:p} size {}",
        EXTFIELD_DEG4_MUL_256_BLOB.as_ptr(),
        EXTFIELD_DEG4_MUL_256_BLOB.len()
    );
    println!(
        "ec_extfield_deg2_sub_256_blob: addr {:p} size {}",
        EXTFIELD_DEG2_SUB_256_BLOB.as_ptr(),
        EXTFIELD_DEG2_SUB_256_BLOB.len()
    );
    println!(
        "ec_extfield_deg2_sub_384_blob: addr {:p} size {}",
        EXTFIELD_DEG2_SUB_384_BLOB.as_ptr(),
        EXTFIELD_DEG2_SUB_384_BLOB.len()
    );
    println!(
        "ec_extfield_xxone_mul_256_blob: addr {:p} size {}",
        EXTFIELD_XXONE_MUL_256_BLOB.as_ptr(),
        EXTFIELD_XXONE_MUL_256_BLOB.len()
    );
    println!(
        "ec_extfield_xxone_mul_384_blob: addr {:p} size {}",
        EXTFIELD_XXONE_MUL_384_BLOB.as_ptr(),
        EXTFIELD_XXONE_MUL_384_BLOB.len()
    );
}

#[cfg(all(target_os = "zkvm", target_arch = "riscv32"))]
const _: () = {
    assert!(
        core::option_env!("RISC0_FEATURE_bigint2").is_some(),
        r#"
RISC Zero zkVM feature bigint2 is not available, and is required by this crate.

If you'd like to use bigint2, please upgrade to risc0-zkvm and risc0-build and ensure the required
feature flags are enabled. See the RISC Zero dev docs for more information.
https://dev.risczero.com/api/zkvm/acceleration
"#
    );
};

#[cfg(feature = "num-bigint")]
impl<const WIDTH: usize> ToBigInt2Buffer<WIDTH> for num_bigint::BigUint {
    fn to_u32_array(&self) -> [u32; WIDTH] {
        let digits = self.to_u32_digits();
        assert!(
            digits.len() <= WIDTH,
            "Input too large: {} words exceeds width of {} words",
            digits.len(),
            WIDTH,
        );

        let mut result = [0u32; WIDTH];
        result[..digits.len()].copy_from_slice(&digits);
        result
    }

    fn from_u32_array(array: [u32; WIDTH]) -> Self {
        Self::from_slice(&array)
    }
}

#[cfg(feature = "num-bigint-dig")]
impl<const WIDTH: usize> ToBigInt2Buffer<WIDTH> for num_bigint_dig::BigUint {
    fn to_u32_array(&self) -> [u32; WIDTH] {
        let mut result = [0u32; WIDTH];
        let bytes = self.to_bytes_le();
        let max_width = WIDTH * 4;
        assert!(
            bytes.len() <= max_width,
            "Input too large: {} bytes exceeds width of {} bytes",
            bytes.len(),
            max_width,
        );

        let mut chunks = bytes.chunks_exact(WORD_SIZE);
        for (i, chunk) in chunks.by_ref().enumerate() {
            result[i] = u32::from_le_bytes(chunk.try_into().unwrap());
        }

        let remainder = chunks.remainder();
        if !remainder.is_empty() {
            let idx = bytes.len() / WORD_SIZE;
            let mut word = 0u32;
            for (i, &byte) in remainder.iter().enumerate() {
                word |= (byte as u32) << (i * 8);
            }
            result[idx] = word;
        }

        result
    }

    fn from_u32_array(array: [u32; WIDTH]) -> Self {
        Self::from_slice(&array)
    }
}

#[cfg(test)]
struct BigUintWrap(num_bigint::BigUint);

#[cfg(test)]
impl std::str::FromStr for BigUintWrap {
    type Err = num_bigint::ParseBigIntError;

    fn from_str(s: &str) -> std::result::Result<Self, Self::Err> {
        use num_traits::Num as _;
        Ok(BigUintWrap(num_bigint::BigUint::from_str_radix(s, 16)?))
    }
}
