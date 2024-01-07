// Copyright 2024 RISC Zero, Inc.
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

// Also available as risc0_zkvm::sha::rust_crypto
use risc0_zkvm::{guest::env, sha::Digest};
use sha2::{Digest as _, Sha256};

// Example of using RustCrypto with RISC Zero accelerator support.
fn main() {
    let data: String = env::read();
    let digest = Sha256::digest(&data.as_bytes());
    let digest = Digest::try_from(digest.as_slice()).unwrap();
    env::commit(&digest);
}
