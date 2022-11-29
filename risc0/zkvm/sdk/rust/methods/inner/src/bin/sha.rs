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
#![no_std]
#![feature(alloc_error_handler)]

use risc0_zkvm_guest::{env, sha};
use risc0_zkvm_platform::io::SENDRECV_CHANNEL_INITIAL_INPUT;

risc0_zkvm_guest::entry!(main);
risc0_zkvm_guest::standalone_handlers!();

pub fn main() {
    let data: [u8; 32] = env::send_recv(SENDRECV_CHANNEL_INITIAL_INPUT, &[])
        .try_into()
        .unwrap();
    let digest = sha::digest_u8_slice(&data);
    env::commit(&digest);
}
