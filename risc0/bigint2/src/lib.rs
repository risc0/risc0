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
