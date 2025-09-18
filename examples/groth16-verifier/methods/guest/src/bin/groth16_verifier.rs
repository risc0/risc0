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

use risc0_groth16::{ProofJson, PublicInputsJson, Verifier, VerifyingKeyJson};
use risc0_zkvm::{guest::env, sha::Digestible};

pub fn main() {
    let (proof_json, public_inputs_json, verifying_key_json): (
        ProofJson,
        PublicInputsJson,
        VerifyingKeyJson,
    ) = env::read();

    Verifier::from_json(
        proof_json,
        public_inputs_json.clone(),
        verifying_key_json.clone(),
    )
    .unwrap()
    .verify()
    .unwrap();

    let verifying_key_digest = verifying_key_json.verifying_key().unwrap().digest();
    let public_inputs_digest = public_inputs_json.to_scalar().unwrap().digest();
    env::commit(&(verifying_key_digest, public_inputs_digest));
}
