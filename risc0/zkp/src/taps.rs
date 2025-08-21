// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use core::{
    cmp::Ordering,
    fmt::{self, Debug},
};

/// This class is an implementation detail and carefully built to be efficient
/// on RISC-V for use in recursion.
#[derive(Debug)]
pub struct TapData {
    // The offset in register group (reg #)
    pub offset: u16,
    // How many cycles back this tap is
    pub back: u16,
    // Which register group this tap is a part of
    pub group: usize,
    // Which combo this register is part of
    pub combo: u8,
    // How far to skip to next register
    pub skip: u8,
}

impl PartialEq for TapData {
    fn eq(&self, other: &Self) -> bool {
        self.offset == other.offset && self.back == other.back && self.group == other.group
    }
}

impl PartialOrd for TapData {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        match self.group.partial_cmp(&other.group) {
            Some(Ordering::Equal) => {}
            ord => return ord,
        }
        match self.offset.partial_cmp(&other.offset) {
            Some(Ordering::Equal) => {}
            ord => return ord,
        }
        self.back.partial_cmp(&other.back)
    }
}

#[derive(Debug)]
pub struct TapSet<'a> {
    pub taps: &'a [TapData],
    pub combo_taps: &'a [u16],
    pub combo_begin: &'a [u16],
    pub group_begin: &'a [usize],
    pub combos_count: usize,
    pub reg_count: usize,
    pub tot_combo_backs: usize,
    pub group_names: &'a [&'a str],
}

impl TapSet<'_> {
    pub fn num_groups(&self) -> usize {
        self.group_names.len()
    }

    pub fn tap_size(&self) -> usize {
        self.group_begin[self.num_groups()]
    }

    pub fn taps(&self) -> TapIter<'_> {
        TapIter {
            data: self.taps,
            cursor: 0,
            end: self.group_begin[self.num_groups()],
        }
    }

    pub fn regs(&self) -> RegisterIter<'_> {
        RegisterIter {
            data: self.taps,
            cursor: 0,
            end: self.group_begin[self.num_groups()],
        }
    }

    pub fn group_taps(&self, group_id: usize) -> TapIter<'_> {
        TapIter {
            data: self.taps,
            cursor: self.group_begin[group_id],
            end: self.group_begin[group_id + 1],
        }
    }

    pub fn group_regs(&self, group_id: usize) -> RegisterIter<'_> {
        RegisterIter {
            data: self.taps,
            cursor: self.group_begin[group_id],
            end: self.group_begin[group_id + 1],
        }
    }

    pub fn group_size(&self, group_id: usize) -> usize {
        let idx = self.group_begin[group_id + 1] - 1;
        let last = self.taps[idx].offset as usize;
        last + 1
    }

    pub fn group_name(&self, group_id: usize) -> &str {
        self.group_names[group_id]
    }

    pub fn combos_size(&self) -> usize {
        self.combos_count
    }

    pub fn reg_count(&self) -> usize {
        self.reg_count
    }

    pub fn combos(&self) -> ComboIter<'_> {
        ComboIter {
            data: ComboData {
                taps: self.combo_taps,
                offsets: self.combo_begin,
            },
            id: 0,
            end: self.combos_count,
        }
    }

    pub fn get_combo(&self, id: usize) -> ComboRef<'_> {
        ComboRef {
            data: ComboData {
                taps: self.combo_taps,
                offsets: self.combo_begin,
            },
            id,
        }
    }
}

pub struct RegisterRef<'a> {
    data: &'a [TapData],
    cursor: usize,
}

impl RegisterRef<'_> {
    pub fn group(&self) -> usize {
        self.data[self.cursor].group
    }

    pub fn offset(&self) -> usize {
        self.data[self.cursor].offset as usize
    }

    pub fn combo_id(&self) -> usize {
        self.data[self.cursor].combo as usize
    }

    /// Number of taps in the register
    pub fn size(&self) -> usize {
        self.data[self.cursor].skip as usize
    }

    /// Get a specific 'back' value
    pub fn back(&self, i: usize) -> usize {
        self.data[self.cursor + i].back as usize
    }
}

impl Debug for RegisterRef<'_> {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        f.debug_struct("RegisterRef")
            .field("group", &self.group())
            .field("offset", &self.offset())
            .field("combo_id", &self.combo_id())
            .field("size", &self.size())
            .finish()
    }
}

impl<'a> IntoIterator for RegisterRef<'a> {
    type Item = TapRef<'a>;
    type IntoIter = TapIter<'a>;

    fn into_iter(self) -> Self::IntoIter {
        TapIter {
            data: self.data,
            cursor: self.cursor,
            end: self.cursor + self.size(),
        }
    }
}

pub struct RegisterIter<'a> {
    data: &'a [TapData],
    cursor: usize,
    end: usize,
}

impl<'a> Iterator for RegisterIter<'a> {
    type Item = RegisterRef<'a>;

    fn next(&mut self) -> Option<Self::Item> {
        let cursor = self.cursor;
        if cursor >= self.data.len() {
            return None;
        }
        let next = cursor + self.data[cursor].skip as usize;
        if next > self.end {
            return None;
        }
        self.cursor = next;
        Some(RegisterRef {
            data: self.data,
            cursor,
        })
    }
}

pub struct TapRef<'a> {
    data: &'a TapData,
}

impl TapRef<'_> {
    pub fn group(&self) -> usize {
        self.data.group
    }

    pub fn offset(&self) -> usize {
        self.data.offset as usize
    }

    pub fn back(&self) -> usize {
        self.data.back as usize
    }

    pub fn combo_id(&self) -> usize {
        self.data.combo as usize
    }
}

impl Debug for TapRef<'_> {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        f.debug_struct("TapRef")
            .field("group", &self.group())
            .field("offset", &self.offset())
            .field("back", &self.back())
            .field("combo_id", &self.combo_id())
            .finish()
    }
}

pub struct TapIter<'a> {
    data: &'a [TapData],
    cursor: usize,
    end: usize,
}

impl<'a> Iterator for TapIter<'a> {
    type Item = TapRef<'a>;

    fn next(&mut self) -> Option<Self::Item> {
        let cursor = self.cursor;
        let next = self.cursor + 1;
        if next > self.end {
            return None;
        }
        self.cursor = next;
        Some(TapRef {
            data: &self.data[cursor],
        })
    }
}

/// Combo data holds the tap set for each 'combo'.
///
/// Basically, combo N consists of taps in the range [offsets\[n\],
/// offsets\[n+1\]). Again this is an implementation detail, and the format is
/// designed to put the actual arrays into static data.
#[derive(Clone)]
pub struct ComboData<'a> {
    taps: &'a [u16],
    offsets: &'a [u16],
}

pub struct ComboRef<'a> {
    data: ComboData<'a>,
    id: usize,
}

impl ComboRef<'_> {
    pub fn id(&self) -> usize {
        self.id
    }

    pub fn size(&self) -> usize {
        self.next_offset() - self.self_offset()
    }

    pub fn slice(&self) -> &[u16] {
        &self.data.taps[self.self_offset()..self.next_offset()]
    }

    fn self_offset(&self) -> usize {
        self.data.offsets[self.id] as usize
    }

    fn next_offset(&self) -> usize {
        self.data.offsets[self.id + 1] as usize
    }
}

pub struct ComboIter<'a> {
    data: ComboData<'a>,
    id: usize,
    end: usize,
}

impl<'a> Iterator for ComboIter<'a> {
    type Item = ComboRef<'a>;

    fn next(&mut self) -> Option<Self::Item> {
        let id = self.id;
        let next = self.id + 1;
        if next > self.end {
            return None;
        }
        self.id = next;
        Some(ComboRef {
            data: self.data.clone(),
            id,
        })
    }
}
