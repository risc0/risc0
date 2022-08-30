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

use risc0_zkvm_guest::env;

risc0_zkvm_guest::entry!(main);

pub fn main() {
    let channel_id = env::read();
    let count = env::read();

    let mut input: &[u8] = &[];
    let mut input_len: usize = 0;

    for _ in 0..count {
        let (host_data, host_len) = env::host_sendrecv(channel_id, &input[..input_len]);

        input = bytemuck::cast_slice(host_data);
        input_len = host_len;
    }
}
