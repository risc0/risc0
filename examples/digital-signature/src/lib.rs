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

pub use digital_signature_core::{SignMessageCommit, SigningRequest};
use digital_signature_methods::{SIGN_ELF, SIGN_ID};
use risc0_zkvm::{
    ExecutorEnv, Receipt, Result, default_prover,
    sha::{Digest, Impl, Sha256},
};

pub struct SignatureWithReceipt {
    receipt: Receipt,
}

impl SignatureWithReceipt {
    pub fn get_commit(&self) -> Result<SignMessageCommit> {
        Ok(self.receipt.journal.decode()?)
    }

    pub fn get_identity(&self) -> Result<Digest> {
        Ok(self.get_commit()?.identity)
    }

    pub fn get_message(&self) -> Result<Digest> {
        Ok(self.get_commit()?.msg)
    }

    pub fn verify(&self) -> Result<SignMessageCommit> {
        self.receipt.verify(SIGN_ID)?;
        self.get_commit()
    }
}

pub fn sign(pass_str: impl AsRef<[u8]>, msg_str: impl AsRef<[u8]>) -> Result<SignatureWithReceipt> {
    let params = SigningRequest {
        passphrase: *Impl::hash_bytes(pass_str.as_ref()),
        msg: *Impl::hash_bytes(msg_str.as_ref()),
    };
    let env = ExecutorEnv::builder().write(&params)?.build()?;

    // Obtain the default prover.
    let prover = default_prover();

    // Produce a receipt by proving the specified ELF binary.
    let receipt = prover.prove(env, SIGN_ELF)?.receipt;

    Ok(SignatureWithReceipt { receipt })
}

#[cfg(test)]
mod tests {
    use sha2::{Digest, Sha256};
    use test_log::test;

    use super::*;

    #[test]
    fn protocol() {
        let pass_str = "passphr4ase";
        let msg_str = "This message was signed by me";
        let signing_receipt = sign(pass_str, msg_str).unwrap();
        signing_receipt.verify().unwrap();

        let mut msg_hasher = Sha256::new();
        msg_hasher.update(msg_str);
        let msg_hash = msg_hasher.finalize();

        let message = signing_receipt.get_message().unwrap();
        assert_eq!(msg_hash.as_slice(), message.as_bytes());

        tracing::info!("msg: {msg_str:?}");
        tracing::info!("commit: {message:?}");
    }
}
