// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use derive_more::{Add, AddAssign, Debug, Sub};

use crate::{PAGE_WORDS, WORD_SIZE};

/// A memory address expressed in bytes
#[derive(Add, AddAssign, Clone, Copy, Debug, Eq, Hash, Ord, PartialEq, PartialOrd, Sub)]
#[debug("{_0:#010x}")]
pub struct ByteAddr(pub u32);

/// A memory address expressed in words
///
/// Only capable of representing aligned addresses, as adjacent [WordAddr]s are a word apart.
#[derive(Add, AddAssign, Clone, Copy, Debug, Eq, Hash, Ord, PartialEq, PartialOrd, Sub)]
#[debug("${_0:#010x}")]
pub struct WordAddr(pub u32);

impl ByteAddr {
    /// Convert to a [WordAddr]
    ///
    /// If the address is not aligned to a word boundary, this will return the highest aligned address smaller than the input address.
    pub const fn waddr(self) -> WordAddr {
        WordAddr(self.0 / WORD_SIZE as u32)
    }

    /// Convert to a [WordAddr] if aligned
    ///
    /// If the address is aligned to a word boundary, this will return the [WordAddr] for this memory location. If it is not aligned, it returns `None`.
    pub fn waddr_aligned(self) -> Option<WordAddr> {
        self.is_aligned().then(|| self.waddr())
    }

    /// Reports if the address is aligned
    ///
    /// Returns `true` if the address is aligned to a word boundary, otherwise returns `false`
    pub const fn is_aligned(&self) -> bool {
        self.0 % WORD_SIZE as u32 == 0
    }

    /// Reports if the address is null
    ///
    /// The address `0x00000000` is null and will return `true`, for all others returns `false`.
    pub const fn is_null(&self) -> bool {
        self.0 == 0
    }

    /// Add an offset to an address
    ///
    /// This will wrap on overflow, e.g. `0xFFFFFFFF + 0x00000001` is `0x00000000`.
    pub fn wrapping_add(self, rhs: u32) -> Self {
        Self(self.0.wrapping_add(rhs))
    }

    /// The subaddress of this address relative to its containing word
    ///
    /// The number of bytes this address is beyond the previous aligned address. So for example an aligned address will have a subaddress of `0`, while the address `0x00003001` will have subaddress `1`.
    pub fn subaddr(&self) -> u32 {
        self.0 % WORD_SIZE as u32
    }
}

impl WordAddr {
    /// Convert to a [ByteAddr]
    pub const fn baddr(self) -> ByteAddr {
        ByteAddr(self.0 * WORD_SIZE as u32)
    }

    /// Gives the [crate::image::Page] containing this memory address
    pub fn page_idx(&self) -> u32 {
        self.0 / PAGE_WORDS as u32
    }

    /// The subaddress of this address relative to its containing [crate::image::Page]
    ///
    /// The number of words this address is beyond the first word of the page which contains it.
    pub fn page_subaddr(&self) -> WordAddr {
        Self(self.0 % PAGE_WORDS as u32)
    }

    /// Increments this address to the next word
    ///
    /// This increments the address without returning any value.
    pub fn inc(&mut self) {
        self.0 += 1;
    }

    /// Increments this address to the next word and returns its previous value
    ///
    /// This is a postfixing increment, analogous to `addr++` in C; the value this evaluates to is the value prior to the increment.
    pub fn postfix_inc(&mut self) -> Self {
        let cur = *self;
        self.0 += 1;
        cur
    }

    /// Reports if the address is null
    ///
    /// The address `0x00000000` is null and will return `true`, for all others returns `false`.
    pub const fn is_null(&self) -> bool {
        self.0 == 0
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

impl core::ops::Add<i32> for WordAddr {
    type Output = WordAddr;

    fn add(self, rhs: i32) -> Self::Output {
        Self(self.0.checked_add_signed(rhs).unwrap())
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

impl core::ops::Add<i32> for ByteAddr {
    type Output = ByteAddr;

    fn add(self, rhs: i32) -> Self::Output {
        Self(self.0.checked_add_signed(rhs).unwrap())
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
