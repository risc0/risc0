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

#![no_std]

#[cfg(feature = "cxx")]
#[cxx::bridge]
mod ffi {}

cfg_if::cfg_if! {
    if #[cfg(feature = "pure")] {
        extern crate alloc;

        pub mod fp;
        pub mod fp4;
        pub mod ntt;
        pub mod poly;
        pub mod rou;
        pub mod sha;
        pub mod sha_cpu;
        pub mod sha_rng;

        pub fn to_po2(x: usize) -> usize {
            (31 - (x as u32).leading_zeros()) as usize
        }
    }
}
