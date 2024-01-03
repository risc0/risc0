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

#![no_std]
#![no_main]

extern crate alloc;
use alloc::vec;

use risc0_zkvm::guest::{env, env::Read};

risc0_zkvm::entry!(main);

fn main() {
    let mut len: u32 = 0;
    env::stdin().read_slice(core::slice::from_mut(&mut len));
    let mut slice = vec![0u8; len as usize];
    env::stdin().read_slice(&mut slice);
    env::commit_slice(&slice);
}
