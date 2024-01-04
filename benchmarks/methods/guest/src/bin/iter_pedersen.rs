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

use core::hint::black_box;
use risc0_zkvm::{guest::env, sha::Digest};
use starknet_crypto::FieldElement;

fn main() {
    let (num_iter, _data): (u32, Vec<u8>) = env::read();

    let e0 = FieldElement::from_hex_be(
        "0x03d937c035c878245caf64531a5756109c53068da139362728feb561405371cb",
    )
    .unwrap();
    let e1 = FieldElement::from_hex_be(
        "0x0208a0a10250e382e1e4bbe2880906c2791bf6275695e02fbbc6aeff9cd8b31a",
    )
    .unwrap();

    for _ in 0..num_iter - 1 {
        black_box(starknet_crypto::pedersen_hash(&e0, &e1));
    }

    let hash = starknet_crypto::pedersen_hash(&e0, &e1);
    let digest = Digest::try_from(hash.to_bytes_be().as_slice()).unwrap();
    env::commit(&digest)
}
