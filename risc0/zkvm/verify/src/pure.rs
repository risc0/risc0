use alloc::{vec, vec::Vec};

use serde::{Deserialize, Serialize};

use risc0_zkp_core::sha::{Digest, Sha};
use risc0_zkp_verify::verify::verify;

pub use crate::circuit::MethodID;
use crate::circuit::Risc0Circuit;

#[derive(Deserialize, Serialize)]
pub struct Receipt {
    journal: Vec<u8>,
    seal: Vec<u32>,
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

#[cfg(test)]
mod tests {
    extern crate std;
    use super::Receipt;
    use crate::MethodID;
    use core::convert::TryFrom;
    use std::fs;
    use std::io;
    use std::vec::Vec;
    use test_log::test;

    #[test]
    fn test_receipt() -> io::Result<()> {
        log::set_max_level(log::LevelFilter::Info);
        let data: Vec<u8> = fs::read("src/simple_receipt.receipt")?;
        let as_u32: Vec<u32> = data
            .chunks(4)
            .map(|bytes| u32::from_le_bytes(<[u8; 4]>::try_from(bytes).unwrap()))
            .collect();
        let receipt: Receipt = risc0_zkvm_serde::from_slice(&as_u32).unwrap();

        let method_id = MethodID::try_from(fs::read("src/simple_receipt.id")?.as_slice()).unwrap();

        std::println!(
            "Receipt: journal length {} seal length {}",
            receipt.journal.len(),
            receipt.seal.len(),
        );

        for i in 0..50 {
            std::print!(" {}", receipt.seal[i]);
        }
        std::println!("\n");

        receipt.verify(&method_id);
        Ok(())
    }
}
