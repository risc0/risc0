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

#![no_main]
#![cfg_attr(not(feature = "std"), no_std)]

use risc0_zkp::core::sha::{Digest, Sha};
use risc0_zkvm_guest::{env, sha};

risc0_zkvm_guest::entry!(main);

pub fn main() {
    let impl_select: u32 = env::read();
    let data: &[u8] = env::read();
    let digest = sha::digest_u8_slice(data);
    env::commit(&digest);

    match impl_select {
        0 => risc0_zkp::core::sha::testutil::test_sha_impl(&risc0_zkvm_guest::sha::Impl {}),
        1 => {
            risc0_zkp::core::sha::testutil::test_sha_impl(&risc0_zkvm_guest::sha_insecure::Impl {})
        }
        2 => {
            // Time the simulated sha so that it estimates what we'd
            // see when it's a custom circuit.
            let a: &Digest = &Digest::new([1, 2, 3, 4, 5, 6, 7, 8]);

            let count1 = env::get_cycle_count();
            risc0_zkvm_guest::memory_barrier(&count1);
            let count2 = env::get_cycle_count();
            risc0_zkvm_guest::memory_barrier(&count2);
            let result = risc0_zkvm_guest::sha_insecure::Impl {}.hash_pair(a, a);
            risc0_zkvm_guest::memory_barrier(&result);
            let count3 = env::get_cycle_count();
            risc0_zkvm_guest::memory_barrier(&count3);

            let overhead = count2 - count1;
            let total = (count3 - count2) - overhead;

            assert!(total >= 76);
        }
        _ => unimplemented!(),
    }
}
