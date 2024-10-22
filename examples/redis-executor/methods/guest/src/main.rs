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

#![no_main]

use risc0_zkvm::guest::{env, memory_barrier};

risc0_zkvm::guest::entry!(main);

pub fn main() {
    // 1,           // 16, 64K
    // 4 * 1024,    // 17, 128K
    // 16 * 1024,   // 18, 256K
    // 32 * 1024,   // 19, 512K
    // 64 * 1024,   // 20, 1M
    // 200 * 1024,  // 21, 2M
    // 400 * 1024,  // 22, 4M
    // 900 * 1024,  // 23, 8M
    // 1400 * 1024, // 24, 16M

    // let iters: u64 = 64 * 1024; // 1M
    let iter: u64 = env::read();

    // Special case to allow us to test failures from within the guest.
    if iter == 0 {
        panic!("GUEST CODE PANIC TEST STRING")
    }

    let iters: u64 = iter * 1024;
    for i in 0..iters {
        memory_barrier(&i);
    }

    env::commit(&iter);
}
