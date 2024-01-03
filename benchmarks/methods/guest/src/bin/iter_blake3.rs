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

fn main() {
    let (num_iter, data): (u32, Vec<u8>) = env::read();

    let mut output = blake3::hash(&data);
    for _ in 1..num_iter {
        output = blake3::hash(output.as_bytes());
    }

    let digest = Digest::try_from(*output.as_bytes()).unwrap();
    env::commit(&digest)
}
