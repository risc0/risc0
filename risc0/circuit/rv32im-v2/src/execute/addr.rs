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

use std::ops;

use anyhow::{anyhow, Result};
use derive_more::{Add, AddAssign, Debug, Sub};

use super::{pager::PAGE_WORDS, platform::WORD_SIZE, ZERO_PAGE_END_ADDR};

#[derive(Add, AddAssign, Clone, Copy, Debug, Eq, Ord, PartialEq, PartialOrd, Sub)]
#[debug("{_0:#010x}")]
pub struct ByteAddr(pub u32);

#[derive(Add, AddAssign, Clone, Copy, Debug, Eq, Ord, PartialEq, PartialOrd, Sub)]
#[debug("${_0:#010x}")]
pub struct WordAddr(pub u32);

impl ByteAddr {
    pub const fn waddr(self) -> WordAddr {
        WordAddr(self.0 / WORD_SIZE as u32)
    }

    pub const fn is_aligned(&self) -> bool {
        self.0 % WORD_SIZE as u32 == 0
    }

    pub const fn is_null(&self) -> bool {
        self.0 == 0
    }

    pub fn wrapping_add(self, rhs: u32) -> Self {
        Self(self.0.wrapping_add(rhs))
    }

    pub fn subaddr(&self) -> u32 {
        self.0 % WORD_SIZE as u32
    }

    pub fn check(&self) -> Result<ByteAddr> {
        if *self < ZERO_PAGE_END_ADDR {
            Err(anyhow!("{self:?} is an invalid guest address"))
        } else {
            Ok(*self)
        }
    }
}

impl WordAddr {
    pub const fn baddr(self) -> ByteAddr {
        ByteAddr(self.0 * WORD_SIZE as u32)
    }

    pub fn page_idx(&self) -> u32 {
        self.0 / PAGE_WORDS as u32
    }

    pub fn page_subaddr(&self) -> WordAddr {
        Self(self.0 % PAGE_WORDS as u32)
    }

    pub fn postfix_inc(&mut self) -> Self {
        let cur = *self;
        self.0 += 1;
        cur
    }
}

impl ops::Add<usize> for WordAddr {
    type Output = WordAddr;

    fn add(self, rhs: usize) -> Self::Output {
        Self(self.0 + rhs as u32)
    }
}

impl ops::Add<u32> for WordAddr {
    type Output = WordAddr;

    fn add(self, rhs: u32) -> Self::Output {
        Self(self.0 + rhs)
    }
}

impl ops::Sub<u32> for WordAddr {
    type Output = WordAddr;

    fn sub(self, rhs: u32) -> Self::Output {
        Self(self.0 - rhs)
    }
}

impl ops::AddAssign<usize> for WordAddr {
    fn add_assign(&mut self, rhs: usize) {
        self.0 += rhs as u32;
    }
}

impl ops::AddAssign<u32> for WordAddr {
    fn add_assign(&mut self, rhs: u32) {
        self.0 += rhs;
    }
}

impl ops::Add<usize> for ByteAddr {
    type Output = ByteAddr;

    fn add(self, rhs: usize) -> Self::Output {
        Self(self.0 + rhs as u32)
    }
}

impl ops::Add<u32> for ByteAddr {
    type Output = ByteAddr;

    fn add(self, rhs: u32) -> Self::Output {
        Self(self.0 + rhs)
    }
}

impl ops::AddAssign<usize> for ByteAddr {
    fn add_assign(&mut self, rhs: usize) {
        self.0 += rhs as u32;
    }
}

impl ops::AddAssign<u32> for ByteAddr {
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
