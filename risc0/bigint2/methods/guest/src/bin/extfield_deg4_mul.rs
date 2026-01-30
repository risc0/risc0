// Copyright 2026 RISC Zero, Inc.
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

#[cfg(feature = "num-bigint-dig")]
extern crate num_bigint_dig as num_bigint;

#[allow(unused)]
use risc0_zkvm::guest::env;

#[cfg(any(feature = "num-bigint-dig", feature = "num-bigint"))]
fn main() {
    use num_bigint::BigUint;
    use risc0_bigint2::ToBigInt2Buffer;

    let (
        lhs_0,
        lhs_1,
        lhs_2,
        lhs_3,
        rhs_0,
        rhs_1,
        rhs_2,
        rhs_3,
        monicirr_0,
        monicirr_1,
        monicirr_2,
        monicirr_3,
        prime,
    ): (
        BigUint,
        BigUint,
        BigUint,
        BigUint,
        BigUint,
        BigUint,
        BigUint,
        BigUint,
        BigUint,
        BigUint,
        BigUint,
        BigUint,
        BigUint,
    ) = env::read();
    let lhs = [
        lhs_0.to_u32_array(),
        lhs_1.to_u32_array(),
        lhs_2.to_u32_array(),
        lhs_3.to_u32_array(),
    ];
    let rhs = [
        rhs_0.to_u32_array(),
        rhs_1.to_u32_array(),
        rhs_2.to_u32_array(),
        rhs_3.to_u32_array(),
    ];
    let monicirr = [
        monicirr_0.to_u32_array(),
        monicirr_1.to_u32_array(),
        monicirr_2.to_u32_array(),
        monicirr_3.to_u32_array(),
    ];
    let prime = prime.to_u32_array();

    let mut result = [[0u32; risc0_bigint2::field::FIELD_256_WIDTH_WORDS]; 4];
    risc0_bigint2::field::extfield_deg4_mul_256(&lhs, &rhs, &monicirr, &prime, &mut result);

    let result = (
        BigUint::from_slice(&result[0]),
        BigUint::from_slice(&result[1]),
        BigUint::from_slice(&result[2]),
        BigUint::from_slice(&result[3]),
    );

    env::commit(&result);
}

#[cfg(not(any(feature = "num-bigint-dig", feature = "num-bigint")))]
fn main() {
    panic!("No bigint library enabled");
}
