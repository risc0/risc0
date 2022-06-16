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

use alloc::{vec, vec::Vec};

use risc0_zkp_core::sha::{Digest, Sha};
use serde::{Deserialize, Serialize};

use crate::zkp::verify::verify;
use crate::zkvm::verify::circuit::{MethodID, RV32Circuit};

#[derive(Deserialize, Serialize)]
pub struct Receipt {
    pub journal: Vec<u8>,
    pub seal: Vec<u32>,
}

impl Receipt {
    pub fn verify(&self, method_id: &MethodID) {
        let mut circuit = RV32Circuit::new(method_id);
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
