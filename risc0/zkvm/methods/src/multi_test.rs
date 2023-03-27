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

use risc0_zeroio::{Deserialize, Serialize};
use risc0_zkvm::declare_syscall;

#[derive(Serialize, Deserialize, Debug)]
pub enum MultiTestSpec {
    DoNothing,
    ShaConforms,
    ShaCycleCount,
    ShaDigest {
        data: Vec<u8>,
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
        orig: Vec<u8>,
        fd: u32,
        // Position and length to do reads
        pos_and_len: Vec<(u32, u32)>,
    },
    PauseContinue,
}

declare_syscall!(pub SYS_MULTI_TEST);
