// Copyright 2025 RISC Zero, Inc.
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

use clap::Parser;
use keccak_methods::{KECCAK_ELF, KECCAK_ID};
use risc0_zkvm::{ExecutorEnv, Receipt, default_prover, sha::Digest};

/// Hash the given bytes, returning the digest and a [Receipt] that can
/// be used to verify that the that the hash was computed correctly (i.e. that
/// the Prover knows a preimage for the given keccak-256 hash)
///
/// KECCAK_ELF uses the `tiny-keccak` crate, patched to use the RISC
/// Zero accelerator. See `src/methods/guest/Cargo.toml` for the patch
/// definition, which can be used to enable keccak-256 accelerator support
/// everywhere the `tiny-keccak` crate is used.
fn provably_hash(input: &str) -> (Digest, Receipt) {
    let env = ExecutorEnv::builder()
        .write(&input)
        .unwrap()
        .build()
        .unwrap();

    // Obtain the default prover.
    let prover = default_prover();

    // Produce a receipt by proving the specified ELF binary.
    let receipt = prover.prove(env, KECCAK_ELF).unwrap().receipt;

    let digest = receipt.journal.decode().unwrap();
    (digest, receipt)
}

#[derive(Parser)]
struct Cli {
    #[arg(default_value = "")]
    message: String,
}

fn main() {
    // Parse command line
    let args = Cli::parse();

    // Prove hash the message.
    let (digest, receipt) = provably_hash(&args.message);

    // Verify the receipt, ensuring the prover knows a valid keccak preimage.
    receipt
        .verify(KECCAK_ID)
        .expect("receipt verification failed");

    println!("I provably know data whose keccak hash is {digest:x?}");
}

#[cfg(test)]
mod tests {
    use keccak_methods::KECCAK_ID;

    #[test]
    fn hash_abc() {
        let (digest, receipt) = super::provably_hash("abc");
        receipt.verify(KECCAK_ID).unwrap();
        assert_eq!(
            hex::encode(digest.as_bytes()),
            "4e03657aea45a94fc7d47ba826c8d667c0d1e6e33a64a036ec44f58fa12d6c45",
            "We expect to match the reference keccak hash of the standard test value 'abc'"
        );
    }

    #[test]
    fn hash_long() {
        let input = [0xau8; 100_000];
        let (digest, receipt) = super::provably_hash(core::str::from_utf8(&input).unwrap());
        receipt.verify(KECCAK_ID).unwrap();
        assert_eq!(
            hex::encode(digest.as_bytes()),
            "1d2563dc302864dbb7ef2c8a66485adaee9827d47dc608acb7e89e7aa88d77f1",
            "keccak example: digest mismatch"
        );
    }
}
