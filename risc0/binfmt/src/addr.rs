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

// use anyhow::{anyhow, Result};
use derive_more::{Add, AddAssign, Debug, Sub};

use crate::{PAGE_WORDS, WORD_SIZE};

// use super::{pager::PAGE_WORDS, platform::WORD_SIZE, ZERO_PAGE_END_ADDR};

/// TODO
#[derive(Add, AddAssign, Clone, Copy, Debug, Eq, Ord, PartialEq, PartialOrd, Sub)]
#[debug("{_0:#010x}")]
pub struct ByteAddr(pub u32);

/// TODO
#[derive(Add, AddAssign, Clone, Copy, Debug, Eq, Ord, PartialEq, PartialOrd, Sub)]
#[debug("${_0:#010x}")]
pub struct WordAddr(pub u32);

impl ByteAddr {
    /// TODO
    pub const fn waddr(self) -> WordAddr {
        WordAddr(self.0 / WORD_SIZE as u32)
    }

    /// TODO
    pub const fn is_aligned(&self) -> bool {
        self.0 % WORD_SIZE as u32 == 0
    }

    /// TODO
    pub const fn is_null(&self) -> bool {
        self.0 == 0
    }

    /// TODO
    pub fn wrapping_add(self, rhs: u32) -> Self {
        Self(self.0.wrapping_add(rhs))
    }

    /// TODO
    pub fn subaddr(&self) -> u32 {
        self.0 % WORD_SIZE as u32
    }
}

impl WordAddr {
    /// TODO
    pub const fn baddr(self) -> ByteAddr {
        ByteAddr(self.0 * WORD_SIZE as u32)
    }

    /// TODO
    pub fn page_idx(&self) -> u32 {
        self.0 / PAGE_WORDS as u32
    }

    /// TODO
    pub fn page_subaddr(&self) -> WordAddr {
        Self(self.0 % PAGE_WORDS as u32)
    }

    /// TODO
    pub fn postfix_inc(&mut self) -> Self {
        let cur = *self;
        self.0 += 1;
        cur
    }
}

impl core::ops::Add<usize> for WordAddr {
    type Output = WordAddr;

    fn add(self, rhs: usize) -> Self::Output {
        Self(self.0 + rhs as u32)
    }
}

impl core::ops::Add<u32> for WordAddr {
    type Output = WordAddr;

    fn add(self, rhs: u32) -> Self::Output {
        Self(self.0 + rhs)
    }
}

impl core::ops::Sub<u32> for WordAddr {
    type Output = WordAddr;

    fn sub(self, rhs: u32) -> Self::Output {
        Self(self.0 - rhs)
    }
}

impl core::ops::AddAssign<usize> for WordAddr {
    fn add_assign(&mut self, rhs: usize) {
        self.0 += rhs as u32;
    }
}

impl core::ops::AddAssign<u32> for WordAddr {
    fn add_assign(&mut self, rhs: u32) {
        self.0 += rhs;
    }
}

impl core::ops::Add<usize> for ByteAddr {
    type Output = ByteAddr;

    fn add(self, rhs: usize) -> Self::Output {
        Self(self.0 + rhs as u32)
    }
}

impl core::ops::Add<u32> for ByteAddr {
    type Output = ByteAddr;

    fn add(self, rhs: u32) -> Self::Output {
        Self(self.0 + rhs)
    }
}

impl core::ops::AddAssign<usize> for ByteAddr {
    fn add_assign(&mut self, rhs: usize) {
        self.0 += rhs as u32;
    }
}

impl core::ops::AddAssign<u32> for ByteAddr {
    fn add_assign(&mut self, rhs: u32) {
        self.0 += rhs;
    }
}

impl From<ByteAddr> for WordAddr {
    fn from(addr: ByteAddr) -> Self {
        addr.waddr()
    }
}

impl From<WordAddr> for ByteAddr {
    fn from(addr: WordAddr) -> Self {
        addr.baddr()
    }
}
