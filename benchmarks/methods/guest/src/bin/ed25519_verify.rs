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

#![no_main]

use ed25519_dalek::{Signature, Verifier, VerifyingKey};
use risc0_zkvm::guest::env;

risc0_zkvm::guest::entry!(main);

fn main() {
    // Decode the verifying key, message, and signature from the inputs.
    let (iterations, encoded_verifying_key, message, signature_bytes): (
        u32,
        [u8; 32],
        Vec<u8>,
        Vec<u8>,
    ) = env::read();
    let verifying_key = VerifyingKey::from_bytes(&encoded_verifying_key).unwrap();
    let signature: Signature = Signature::from_slice(&signature_bytes).unwrap();
    // Verify the signature, panicking if verification fails.
    for _ in 0..iterations {
        verifying_key
            .verify(&message, &signature)
            .expect("Ed25519 signature verification failed");
    }

    // Commit to the journal the verifying key and message that was signed.
    env::commit(&(encoded_verifying_key, message));
}
