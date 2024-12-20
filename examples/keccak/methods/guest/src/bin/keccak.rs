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

use risc0_zkvm::{guest::env, sha::Digest};
use tiny_keccak::{Hasher, Keccak};

// Example of using tiny-keccak with RISC Zero accelerator support.
fn main() {
    let data: String = env::read();
    let mut hasher = Keccak::v256();
    hasher.update(&data.as_bytes());
    let mut output = [0; 32];
    hasher.finalize(&mut output);
    let digest = Digest::from_bytes(output);
    env::commit(&digest);
}
