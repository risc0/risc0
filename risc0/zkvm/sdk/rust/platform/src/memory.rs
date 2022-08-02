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

use super::WORD_SIZE;

pub const MEM_BITS: usize = 24;
pub const MEM_SIZE: usize = (1 << MEM_BITS) * 4;

pub struct Region {
    start: usize,
    len_bytes: usize,
}

const fn kb(kb: usize) -> usize {
    kb * 1024
}

const fn mb(mb: usize) -> usize {
    kb(mb * 1024)
}

impl Region {
    pub const fn new(start: usize, len_bytes: usize) -> Self {
        Self { start, len_bytes }
    }

    pub const fn start(&self) -> usize {
        self.start
    }

    pub const fn len_bytes(&self) -> usize {
        self.len_bytes
    }

    pub const fn len_words(&self) -> usize {
        assert!((self.len_bytes % WORD_SIZE) == 0);
        self.len_bytes / WORD_SIZE
    }

    pub const fn end(&self) -> usize {
        self.start + self.len_bytes
    }
}

// These should match zkvm/platform/memory.h and zkvm/platform/risc0.ld.
// Write-only section must match the range hardcoded in the circuit.
pub const STACK: Region = Region::new(0x0000_0000, mb(9));
pub const DATA: Region = Region::new(0x0090_0000, mb(1));
pub const HEAP: Region = Region::new(0x00A0_0000, mb(20));
pub const INPUT: Region = Region::new(0x01E0_0000, mb(1));
pub const GPIO: Region = Region::new(0x01F0_0000, mb(1));
pub const PROG: Region = Region::new(0x0200_0000, mb(10));
pub const SHA: Region = Region::new(0x02A0_0000, mb(1));
pub const WOM: Region = Region::new(0x02B0_0000, mb(21));
pub const OUTPUT: Region = Region::new(0x02B0_0000, mb(20));
pub const COMMIT: Region = Region::new(0x03F0_0000, mb(1));
