// Copyright 2023 RISC Zero, Inc.
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

pub use digital_signature_core::{Message, Passphrase, SignMessageCommit, SigningRequest};
use digital_signature_methods::{SIGN_ELF, SIGN_ID};
use risc0_zkvm::{
    serde::{from_slice, to_vec},
    Executor, ExecutorEnv, Result, SessionReceipt,
};
use sha2::{Digest, Sha256};

pub struct SignatureWithReceipt {
    receipt: Box<dyn SessionReceipt>,
}

impl SignatureWithReceipt {
    pub fn get_commit(&self) -> Result<SignMessageCommit> {
        let msg = &self.receipt.get_journal();
        Ok(from_slice(msg.as_slice()).unwrap())
    }

    pub fn get_identity(&self) -> Result<risc0_zkvm::sha::Digest> {
        let commit = self.get_commit()?;
        Ok(commit.identity)
    }

    pub fn get_message(&self) -> Result<Message> {
        let commit = self.get_commit()?;
        Ok(commit.msg)
    }

    pub fn verify(&self) -> Result<SignMessageCommit> {
        self.receipt.verify(SIGN_ID.into())?;
        self.get_commit()
    }
}

pub fn sign(pass_str: impl AsRef<[u8]>, msg_str: impl AsRef<[u8]>) -> Result<SignatureWithReceipt> {
    let params = SigningRequest {
        passphrase: Passphrase {
            pass: Sha256::digest(pass_str).try_into()?,
        },
        msg: Message {
            msg: Sha256::digest(msg_str).try_into()?,
        },
    };
    let vec = to_vec(&params)?;
    let env = ExecutorEnv::builder().add_input(&vec).build().unwrap();
    let mut exec = Executor::from_elf(env, SIGN_ELF)?;
    let session = exec.run()?;
    let receipt = session.prove().unwrap();
    Ok(SignatureWithReceipt { receipt })
}

#[cfg(test)]
mod tests {
    use test_log::test;

    use super::*;

    #[test]
    fn protocol() {
        let pass_str = "passphr4ase";
        let msg_str = "This message was signed by me";
        let signing_receipt = sign(pass_str, msg_str);
        let signing_receipt = match signing_receipt {
            Ok(signing_receipt) => signing_receipt,
            Err(err) => panic!("Problem generating receipt: {:?}", err),
        };
        match signing_receipt.verify() {
            Ok(_) => {}
            Err(err) => panic!("Problem verifying receipt: {:?}", err),
        };

        let mut msg_hasher = Sha256::new();
        msg_hasher.update(msg_str);
        let mut msg_hash = [0u8; 32];
        msg_hash.copy_from_slice(&msg_hasher.finalize());

        let message = signing_receipt.get_message();
        let message = match message {
            Ok(message) => message,
            Err(err) => panic!("Problem getting message: {:?}", err),
        };
        assert_eq!(msg_hash, message.msg);

        log::info!("msg: {:?}", &msg_str);
        log::info!("commit: {:?}", &message);
    }
}
