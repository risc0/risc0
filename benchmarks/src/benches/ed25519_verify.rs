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

use ed25519_dalek::{Signature, Signer, SigningKey, VerifyingKey};
use rand_core::OsRng;
use risc0_zkvm::serde::to_vec;

use crate::Job;

pub fn new_jobs() -> Vec<Job> {
    // Generate a random ed25519 keypair and sign the message.
    let signing_key: SigningKey = SigningKey::generate(&mut OsRng);
    let verifying_key: VerifyingKey = signing_key.verifying_key();
    let message = b"This is a message that will be signed, and verified within the zkVM".to_vec();
    let signature: Signature = signing_key.sign(&message);

    let guest_input = to_vec(&(
        1,
        verifying_key.as_bytes(),
        message,
        signature.to_bytes().to_vec(),
    ))
    .unwrap();

    vec![Job::new(
        "ed25519_verify".to_string(),
        risc0_benchmark_methods::ED25519_VERIFY_ELF,
        risc0_benchmark_methods::ED25519_VERIFY_ID.into(),
        guest_input,
        1,
    )]
}
