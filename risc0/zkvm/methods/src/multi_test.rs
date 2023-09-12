// Copyright 2023 RISC Zero, Inc.
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

// Definitions for test selection codes used by the "multi_test" test.
extern crate alloc;

use alloc::vec::Vec;

use risc0_zkvm::declare_syscall;
use risc0_zkvm_platform::syscall::bigint;
use serde::{Deserialize, Serialize};

#[derive(Serialize, Deserialize, Debug)]
pub enum MultiTestSpec {
    DoNothing,
    ShaConforms,
    ShaCycleCount,
    ShaDigest {
        data: Vec<u8>,
    },
    ShaDigestIter {
        data: Vec<u8>,
        num_iter: u32,
    },
    EventTrace,
    Profiler,
    Fail,
    ReadWriteMem {
        /// Tuples of (address, value). Zero means read the value and
        /// output it; nonzero means write that value.
        values: Vec<(u32, u32)>,
    },
    Syscall {
        count: u32,
    },
    DoRandom,
    SysRead {
        // Buffer to read to
        buf: Vec<u8>,
        fd: u32,
        // Position and length to do reads
        pos_and_len: Vec<(u32, u32)>,
    },
    EchoStdout {
        nbytes: u32,
        fd: u32,
    },
    EchoWords {
        fd: u32,
        nwords: u32,
    },
    BigInt {
        x: [u32; bigint::WIDTH_WORDS],
        y: [u32; bigint::WIDTH_WORDS],
        modulus: [u32; bigint::WIDTH_WORDS],
    },
    PauseContinue,
    BusyLoop {
        /// Busy loop until the guest has run for at least this number of cycles
        cycles: u32,
    },
    LibM,
    Oom,
    OutOfBounds,
    RsaCompat,
}

declare_syscall!(pub SYS_MULTI_TEST);
