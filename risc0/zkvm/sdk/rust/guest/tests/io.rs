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
#![allow(non_snake_case)]

use zkvm_guest::env;

zkvm_guest::entry!(main);

pub fn main() {
    let count: u32 = env::read();
    for _ in 0..count {
        let addr: u32 = env::read();
        let value: u32 = env::read();
        let ptr = addr as *mut u32;
        if value != 0 {
            unsafe { ptr.write_volatile(value) };
        } else {
            let value = unsafe { ptr.read_volatile() };
            env::write(&value);
        }
    }
}
