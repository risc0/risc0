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

#![doc = include_str!("../README.md")]

use hello_world_methods::MULTIPLY_ELF;
use risc0_zkvm::{ExecutorEnv, Receipt, default_prover};

// This is a Hello World demo for the RISC Zero zkVM.
// By running the demo, Alice can produce a receipt that proves that she knows
// some numbers a and b, such that a*b == 391.
// The factors a and b are kept secret.

// Compute the product a*b inside the zkVM
pub fn multiply(a: u64, b: u64) -> (Receipt, u64) {
    let env = ExecutorEnv::builder()
        // Send a & b to the guest
        .write(&a)
        .unwrap()
        .write(&b)
        .unwrap()
        .build()
        .unwrap();

    // Obtain the default prover.
    let prover = default_prover();

    // Produce a receipt by proving the specified ELF binary.
    let receipt = prover.prove(env, MULTIPLY_ELF).unwrap().receipt;

    // Extract journal of receipt (i.e. output c, where c = a * b)
    let c: u64 = receipt.journal.decode().expect(
        "Journal output should deserialize into the same types (& order) that it was written",
    );

    // Report the product
    println!("I know the factors of {c}, and I can prove it!");

    (receipt, c)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_hello_world() {
        const TEST_FACTOR_ONE: u64 = 17;
        const TEST_FACTOR_TWO: u64 = 23;
        let (_, result) = multiply(17, 23);
        assert_eq!(
            result,
            TEST_FACTOR_ONE * TEST_FACTOR_TWO,
            "We expect the zkVM output to be the product of the inputs"
        )
    }
}
