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

use risc0_zkvm::guest::env;
use substrate_bn::{Fr, G1, G2, Gt, pairing_batch};

fn main() {
    let inp: bn254_core::Inputs = env::read();

    let g1 = G1::from_compressed(&inp.g1_compressed).expect("Point on G1 expected");
    let g2 = G2::from_compressed(&inp.g2_compressed).expect("Point on G2 expected");
    let a_factor = Fr::from_slice(&inp.a).expect("Scalar factor expected");
    let b_factor = Fr::from_slice(&inp.b).expect("Scalar factor expected");

    let mut pairs = Vec::new();
    pairs.push((g1 * a_factor, g2 * b_factor));
    pairs.push((g1, g2 * (-a_factor * b_factor)));
    let result = pairing_batch(&pairs);

    env::commit(&(result == Gt::one()));
}
