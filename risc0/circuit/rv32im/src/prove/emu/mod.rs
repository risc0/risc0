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

pub mod addr;
pub mod exec;
pub mod mux;
mod pager;
pub mod preflight;
pub mod rv32im;
pub mod testutil;

use risc0_zkvm_platform::{memory::SYSTEM, syscall::DIGEST_WORDS};

use self::addr::{ByteAddr, WordAddr};

const SYSTEM_START: WordAddr = ByteAddr(SYSTEM.start() as u32).waddr();

const SHA_INIT: usize = 5;
const SHA_LOAD: usize = DIGEST_WORDS * 2;
const SHA_MAIN_MIX: usize = 48;
const SHA_MAIN_FINI: usize = 4;

/// Number of cycles required to complete a BigInt operation.
const BIGINT_CYCLES: usize = 9;

/// The number of cycles required to compress a SHA-256 block.
const fn sha_cycles(count: usize) -> usize {
    SHA_INIT + (SHA_LOAD + SHA_MAIN_MIX + SHA_MAIN_FINI) * count
}
