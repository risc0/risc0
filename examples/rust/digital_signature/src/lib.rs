// Copyright 2022 Risc0, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

use digital_signature_proof::{Message, Passphrase, SigningRequest, SignMessageCommit};
use r0vm_host::{Proof, Prover, Result};
use r0vm_serde::{from_slice, to_vec};

pub struct SigningCompleteMessage {
    proof: Proof,
}

impl SigningCompleteMessage {
    pub fn get_commit(&self) -> Result<SignMessageCommit> {
        let msg = self.proof.get_message_vec()?;
        Ok(from_slice(msg.as_slice()).unwrap())
    }

    pub fn verify_and_get_commit(&self) -> Result <SignMessageCommit> {
        self.proof.verify("examples/rust/digital_signature/proof/sign")?;
        self.get_commit()
    }
}

pub fn sign(pass: &Passphrase, msg: &Message) -> Result<SigningCompleteMessage> {
    let params = SigningRequest {
        passphrase: pass.clone(),
        msg: msg.clone()
    };
    let mut prover = Prover::new("examples/rust/digital_signature/proof/sign")?;
    let vec = to_vec(&params).unwrap();
    prover.add_input(vec.as_slice())?;
    let proof = prover.run()?;
    Ok(SigningCompleteMessage { proof })
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn protocol() {
        let pass = Passphrase {
            pass: 0x12345678abcd1234,
        };
        let msg = Message {
            msg: 0xc0ffee,
        };

        let signing_complete_message = sign(&pass, &msg).unwrap();

        let signing_commit = signing_complete_message.verify_and_get_commit();

        log::info!("msg: {:?}", &msg);
        log::info!("commit: {:?}", &signing_commit);
    }
}
