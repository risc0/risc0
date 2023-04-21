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

use clap::{Arg, Command};
use risc0_zkvm::{
    serde::{from_slice, to_vec},
    sha::Digest,
    Executor, ExecutorEnv,
};
use sha_methods::HASH_ELF;

fn provably_hash(input: &str) -> Digest {
    let env = ExecutorEnv::builder()
        .add_input(&to_vec(input).unwrap())
        .build();

    let mut exec = Executor::from_elf(env, HASH_ELF).unwrap();
    let session = exec.run().unwrap();
    let receipt = session.prove().unwrap();

    from_slice(&receipt.journal).unwrap()
}

fn main() {
    // Parse command line
    let matches = Command::new("hash")
        .arg(Arg::new("message").default_value(""))
        .get_matches();
    let message = matches.get_one::<String>("message").unwrap();

    // Prove hash and verify it
    let digest = provably_hash(message);

    println!("I provably know data whose SHA-256 hash is {}", digest);
}

#[cfg(test)]
mod tests {
    #[test]
    fn main() {
        let digest = super::provably_hash("abc");
        assert_eq!(
            hex::encode(digest.as_bytes()),
            "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad",
            "We expect to match the reference SHA-256 hash of the standard test value 'abc'"
        );
    }
}
