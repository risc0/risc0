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

use super::WORD_SIZE;

pub const MEM_BITS: usize = 28;
pub const MEM_SIZE: usize = 1 << MEM_BITS;

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

/// Program (text followed by data and then bss) gets loaded in
/// starting at this location.  HEAP begins right afterwards.
pub const TEXT_START: u32 = 0x0000_0400;
/// Top of stack; stack grows down from this location.
pub const STACK_TOP: u32 = 0x0BF_FFC00;
/// Minimum mount of room to leave for the stack when allocating from the heap.
pub const RESERVED_STACK: u32 = mb(1) as u32;
pub const SYSTEM: Region = Region::new(0x0C00_0000, mb(16));
pub const PAGE_TABLE: Region = Region::new(0x0D00_0000, mb(16));
pub const PRE_LOAD: Region = Region::new(0x0D70_0000, mb(9));
