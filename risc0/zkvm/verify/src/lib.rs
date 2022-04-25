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

mod circuit;
mod eval;
mod poly_op;
mod poly_ops;
mod taps;

use arrayref::array_ref;

use serde::{Deserialize, Serialize};

use risc0_zkp_core::sha::Digest;
use risc0_zkp_verify::verify::verify;

use crate::circuit::Risc0Circuit;

#[derive(Deserialize, Serialize)]
pub struct Receipt {
    journal: Vec<u8>,
    seal: Vec<u32>,
}

impl Receipt {
    pub fn verify(&self) {
        let mut circuit = Risc0Circuit::default();
        verify(&mut circuit, &self.seal);
        assert!(self.journal.len() == (self.seal[8] as usize));
        if self.journal.len() > 32 {
            let digest = Digest::hash_bytes(&self.journal);
            assert!(digest == Digest::from_u32s(&self.seal[0..8]));
        } else {
            let mut vec = self.journal.clone();
            vec.resize(32, 0);
            for i in 0..8 {
                assert!(self.seal[i] == u32::from_le_bytes(*array_ref![&vec, i * 4, 4]));
            }
        }
    }

    pub fn get_journal_u32(&self) -> Vec<u32> {
        let mut as_words: Vec<u32> = vec![];
        assert!(self.journal.len() % 4 == 0);
        for i in 0..(self.journal.len() / 4) {
            as_words.push(u32::from_le_bytes(*array_ref![&self.journal, i * 4, 4]));
        }
        as_words
    }
}

// #[cfg(test)]
// mod tests {
//     use std::{fs, io};

//     use arrayref::array_ref;
//     use log::info;
//     use test_log::test;

//     use super::verify;
//     use crate::circuit::Risc0Circuit;

//     #[test]
//     fn test_verify() -> io::Result<()> {
//         let data = fs::read("seal.bin")?;
//         assert!(data.len() % 4 == 0);
//         let mut proof: Vec<u32> = vec![];
//         for i in 0..(data.len() / 4) {
//             proof.push(u32::from_le_bytes(*array_ref![&data, i * 4, 4]));
//         }
//         info!("Words: {}", proof.len());
//         let mut circuit = Risc0Circuit::default();
//         verify(&mut circuit, &proof);
//         Ok(())
//     }
// }
