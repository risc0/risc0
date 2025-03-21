// Copyright 2025 RISC Zero, Inc.
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

use include_bytes_aligned::include_bytes_aligned;

#[allow(unused)]
use risc0_zkvm::guest::env;

const MODADD_256_BLOB: &[u8] = include_bytes_aligned!(4, "../../../../src/field/modadd_256.blob");

fn main() {
    let (lhs, rhs, result): (u32, u32, u32) = env::read();

    let mut modulus = [0u32; risc0_bigint2::field::FIELD_256_WIDTH_WORDS];
    modulus[0] = 3;

    unsafe {
        risc0_bigint2::ffi::sys_bigint2_4(
            MODADD_256_BLOB.as_ptr(),
            lhs as *const u32,
            rhs as *const u32,
            modulus.as_ptr(),
            result as *const u32,
        )
    };
}
