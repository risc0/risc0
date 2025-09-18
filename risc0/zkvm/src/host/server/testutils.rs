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

use core::mem;

use crypto_bigint::{
    CheckedMul, Encoding, NonZero, Random, RandomMod, U256, U512, rand_core::CryptoRngCore,
};
use risc0_zkvm_platform::syscall::bigint;

// Convert to little-endian u32 array. Only reinterpretation on LE machines.
fn bigint_to_arr(num: &U256) -> [u32; bigint::WIDTH_WORDS] {
    let mut arr: [u32; bigint::WIDTH_WORDS] = bytemuck::cast(num.to_le_bytes());
    for x in arr.iter_mut() {
        *x = x.to_le();
    }
    arr
}

// Convert from little-endian u32 array. Only reinterpretation on LE machines.
fn arr_to_bigint(mut arr: [u32; bigint::WIDTH_WORDS]) -> U256 {
    for x in arr.iter_mut() {
        *x = x.to_le();
    }
    U256::from_le_bytes(bytemuck::cast(arr))
}

#[derive(Debug)]
pub struct BigIntTestCase {
    pub x: [u32; bigint::WIDTH_WORDS],
    pub y: [u32; bigint::WIDTH_WORDS],
    pub modulus: [u32; bigint::WIDTH_WORDS],
}

impl BigIntTestCase {
    pub fn expected(&self) -> [u32; bigint::WIDTH_WORDS] {
        // Load inputs.
        let x = arr_to_bigint(self.x);
        let y = arr_to_bigint(self.y);
        let n = arr_to_bigint(self.modulus);

        // Compute modular multiplication, or simply multiplication if n == 0.
        let z: U256 = if n == U256::ZERO {
            x.checked_mul(&y).unwrap()
        } else {
            let (w_lo, w_hi) = x.mul_wide(&y);
            let w = w_hi.concat(&w_lo);
            let z = w.rem(&NonZero::<U512>::from_uint(n.resize()));
            z.resize()
        };

        bigint_to_arr(&z)
    }

    // NOTE: Testing here could be significantly improved by creating a less uniform
    // test case generator. It is likely more important to test inputs of different
    // byte-lengths, with zero and 0xff bytes, and other boundary values than
    // testing values in the middle.
    fn sample(rng: &mut impl CryptoRngCore) -> BigIntTestCase {
        let modulus = NonZero::<U256>::random(rng);
        let mut x = U256::random(rng);
        let mut y = U256::random_mod(rng, &modulus);

        // x and y come from slightly different ranges because at least one input must
        // be less than the modulus, but it doesn't matter which one. Randomly swap.
        if (rng.next_u32() & 1) == 0 {
            mem::swap(&mut x, &mut y);
        }

        BigIntTestCase {
            x: bigint_to_arr(&x),
            y: bigint_to_arr(&y),
            modulus: bigint_to_arr(modulus.as_ref()),
        }
    }
}

/// Generate the test cases for the BigInt accelerator circuit that are applied
/// to both the simulator and circuit implementations.
pub fn generate_bigint_test_cases(rand_count: usize) -> Vec<BigIntTestCase> {
    let zero = [0, 0, 0, 0, 0, 0, 0, 0];
    let one = [1, 0, 0, 0, 0, 0, 0, 0];

    let mut cases = vec![
        BigIntTestCase {
            x: [1, 2, 3, 4, 5, 6, 7, 8],
            y: [9, 10, 11, 12, 13, 14, 15, 16],
            modulus: [17, 18, 19, 20, 21, 22, 23, 24],
        },
        BigIntTestCase {
            x: [1, 2, 3, 4, 5, 6, 7, 8],
            y: zero,
            modulus: [17, 18, 19, 20, 21, 22, 23, 24],
        },
        BigIntTestCase {
            x: [1, 2, 3, 4, 5, 6, 7, 8],
            y: one,
            modulus: [17, 18, 19, 20, 21, 22, 23, 24],
        },
        BigIntTestCase {
            x: one,
            y: [9, 10, 11, 12, 13, 14, 15, 16],
            modulus: [1, 2, 3, 4, 5, 6, 7, 8],
        },
        BigIntTestCase {
            x: [1, 2, 3, 4, 0, 0, 0, 0],
            y: [9, 10, 11, 12, 0, 0, 0, 0],
            modulus: zero,
        },
    ];

    let mut rng = crypto_bigint::rand_core::OsRng;
    cases.extend((0..rand_count).map(|_| BigIntTestCase::sample(&mut rng)));
    cases
}
