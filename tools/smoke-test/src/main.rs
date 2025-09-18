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

use methods::{GUEST_ELF, GUEST_ID};
use risc0_zkvm::{ExecutorEnv, default_prover};

fn main() {
    let segment_limit_po2 = 16; // 64k cycles
    let cycles: u32 = 1 << segment_limit_po2;
    let env = ExecutorEnv::builder()
        .write(&cycles)
        .unwrap()
        .build()
        .unwrap();

    let prover = default_prover();
    let receipt = prover.prove(env, GUEST_ELF).unwrap().receipt;
    receipt.verify(GUEST_ID).unwrap();
}
