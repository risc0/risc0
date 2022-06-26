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

mod poly_op;
mod poly_ops;
#[cfg(feature = "prove")]
mod prove;
mod receipt;
mod taps;
#[cfg(feature = "verify")]
mod verify;

#[cfg(feature = "prove")]
pub use prove::prover::Prover;
pub use receipt::Receipt;
pub use verify::circuit::MethodID;

#[cfg(test)]
mod tests {
    extern crate std;
    use super::{MethodID, Receipt};
    use risc0_zkp_core::sha::DIGEST_WORD_SIZE;
    use std::{convert::TryFrom, fs, io, vec::Vec};
    use test_log::test;

    #[test]
    fn test_receipt() {
        log::set_max_level(log::LevelFilter::Info);
        let data = fs::read("src/zkvm/simple_receipt.receipt").unwrap();
        let as_u32: Vec<u32> = data
            .chunks(DIGEST_WORD_SIZE)
            .map(|bytes| u32::from_le_bytes(<[u8; DIGEST_WORD_SIZE]>::try_from(bytes).unwrap()))
            .collect();
        let receipt: Receipt = risc0_zkvm_serde::from_slice(&as_u32).unwrap();

        let method_id =
            MethodID::try_from(fs::read("src/zkvm/simple_receipt.id").unwrap().as_slice()).unwrap();

        std::println!(
            "Receipt: journal length {} seal length {}",
            receipt.journal.len(),
            receipt.seal.len(),
        );

        for i in 0..50 {
            std::print!(" {}", receipt.seal[i]);
        }
        std::println!("\n");

        assert!(receipt.verify(&method_id).unwrap());
    }
}
