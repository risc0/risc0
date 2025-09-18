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
mod tests {
    use risc0_groth16::{ProofJson, PublicInputsJson, Verifier, VerifyingKeyJson};

    const TEST_VERIFICATION_KEY: &str = include_str!("data/verification_key.json");
    const TEST_PROOF: &str = include_str!("data/proof.json");
    const TEST_PUBLIC_INPUTS: &str = include_str!("data/public.json");

    #[test]
    fn test_verify() {
        let verifying_key: VerifyingKeyJson = serde_json::from_str(TEST_VERIFICATION_KEY).unwrap();
        let proof: ProofJson = serde_json::from_str(TEST_PROOF).unwrap();
        let public_inputs = PublicInputsJson {
            values: serde_json::from_str(TEST_PUBLIC_INPUTS).unwrap(),
        };
        let verifier = Verifier::from_json(proof, public_inputs, verifying_key).unwrap();
        verifier.verify().unwrap();
    }
}
