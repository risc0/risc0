use alloc::{vec, vec::Vec};

use anyhow::Result;
use risc0_zkp_core::sha::{Digest, Sha};
use serde::{Deserialize, Serialize};

use crate::zkp::verify::verify;
use crate::zkvm::circuit::{MethodID, Risc0Circuit};

#[derive(Deserialize, Serialize)]
pub struct Receipt {
    pub(crate) journal: Vec<u8>,
    pub(crate) seal: Vec<u32>,
}

impl Receipt {
    pub fn verify(&self, method_id: &MethodID) {
        let mut circuit = Risc0Circuit::new(method_id);
        let sha = risc0_zkp_core::sha::default_implementation();
        verify(sha, &mut circuit, &self.seal).unwrap();
        assert!(self.journal.len() == (self.seal[8] as usize));
        if self.journal.len() > 32 {
            let digest = sha.hash_bytes(&self.journal);
            assert!(*digest == Digest::from_slice(&self.seal[0..8]));
        } else {
            let mut vec = self.journal.clone();
            vec.resize(32, 0);
            for i in 0..8 {
                assert!(
                    self.seal[i] == u32::from_le_bytes(vec[i * 4..i * 4 + 4].try_into().unwrap())
                );
            }
        }
    }

    pub fn get_seal(&self) -> Result<&[u32]> {
        todo!()
    }

    pub fn get_journal(&self) -> Result<&[u8]> {
        todo!()
    }

    pub fn get_journal_u32(&self) -> Vec<u32> {
        let mut as_words: Vec<u32> = vec![];
        assert!(self.journal.len() % 4 == 0);
        for i in 0..(self.journal.len() / 4) {
            as_words.push(u32::from_le_bytes(
                self.journal[i * 4..i * 4 + 4].try_into().unwrap(),
            ));
        }
        as_words
    }
}
