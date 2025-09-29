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
mod tests;

use crate::field::FIELD_4096_WIDTH_WORDS;

type RsaArray = [u32; FIELD_4096_WIDTH_WORDS];

pub fn modpow_65537(base: &RsaArray, modulus: &RsaArray, result: &mut RsaArray) {
    let mut buffer = *base; // Note: copy semantics
    for _ in 0..16 {
        // Since we use the same modulus in every modmul, its safe to use `unchecked` internally
        crate::field::unchecked::modmul_4096(&buffer, &buffer, modulus, result);
        std::mem::swap(&mut buffer, result);
    }
    // An honest host will always return a result less than the modulus.
    // A dishonest prover could return a result greater than the modulus that differs by a multiple
    // of the modulus, e.g. they could return `4` (instead of `1`) as the answer to `1^65537 % 3`,
    // since `4 - 1 = 3`.
    // Therefore, we check that we are in the honest case for the final result.
    crate::field::modmul_4096(&buffer, base, modulus, result);
}
