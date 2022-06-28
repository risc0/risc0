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

use alloc::{
    collections::{BTreeMap, BTreeSet},
    rc::Rc,
    vec,
    vec::Vec,
};
use core::{
    cmp::Ordering,
    fmt::{self, Debug},
};

#[derive(Clone, Copy, PartialEq, PartialOrd, Eq, Hash, Ord, Debug)]
pub enum RegisterGroup {
    Accum = 0,
    Code = 1,
    Data = 2,
}

const REGISTER_GROUPS: &[RegisterGroup] = &[
    RegisterGroup::Accum,
    RegisterGroup::Code,
    RegisterGroup::Data,
];

pub struct Tap {
    pub group: RegisterGroup,
    pub pos: usize,
    pub back: usize,
    pub tap: usize,
}

impl Tap {
    pub const fn new(group: RegisterGroup, pos: usize, back: usize, tap: usize) -> Self {
        Tap {
            group,
            pos,
            back,
            tap,
        }
    }
}

/// This class is an implementation detail and carefully built to be efficient on
/// RISC-V for use in recursion.
#[derive(Debug)]
pub struct TapData {
    // The offset in register group (reg #)
    pub offset: u16,
    // How many cycles back this tap is
    pub back: u16,
    // Which register group this tap is a part of
    pub group: RegisterGroup,
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

struct TapSetData {
    taps: Vec<TapData>,
    combo_taps: Vec<u16>,
    combo_begin: Vec<u16>,
    group_begin: [usize; REGISTER_GROUPS.len() + 1],
    combos_count: usize,
}

#[derive(Clone)]
pub struct TapSet {
    data: Rc<TapSetData>,
}

impl TapSet {
    pub fn new(raw: &[Tap]) -> Self {
        type Reg = BTreeSet<usize>;
        type Group = BTreeMap<usize, Reg>;
        type All = BTreeMap<RegisterGroup, Group>;

        let mut all: All = BTreeMap::new();
        for tap in raw {
            all.entry(tap.group)
                .or_default()
                .entry(tap.pos)
                .or_default()
                .insert(tap.back);
        }

        let mut group_begin = [0; REGISTER_GROUPS.len() + 1];
        let mut combo_begin = Vec::new();
        let mut combo_taps = Vec::new();
        let mut taps = Vec::new();

        // Pre-insert the 'only self' combo
        let myself = BTreeSet::from([0_usize]);
        let mut combos = vec![&myself];
        let mut combos_to_id = BTreeMap::from([(&myself, 0_usize)]);
        // Build flat table
        for group in REGISTER_GROUPS {
            let group_id = *group as usize;
            // Make sure there is always at least one tap per group
            assert!(all.contains_key(&group));
            group_begin[group_id] = taps.len();
            let regs = all.get(group).unwrap();
            let reg_count = regs.keys().last().unwrap() + 1;
            for reg in 0..reg_count {
                // Make sure all registers have at least one tap
                assert!(regs.contains_key(&reg));
                let combo = regs.get(&reg).unwrap();
                assert!(combo.len() > 0);
                let combo_id = combos_to_id.entry(&combo).or_insert_with(|| {
                    let ret = combos.len();
                    combos.push(combo);
                    ret
                });
                for back in combo {
                    taps.push(TapData {
                        group: *group,
                        offset: reg.try_into().unwrap(),
                        back: (*back).try_into().unwrap(),
                        combo: (*combo_id).try_into().unwrap(),
                        skip: combo.len().try_into().unwrap(),
                    });
                }
            }
        }
        group_begin[REGISTER_GROUPS.len()] = taps.len();
        for combo in &combos {
            combo_begin.push(combo_taps.len().try_into().unwrap());
            for tap in *combo {
                combo_taps.push((*tap).try_into().unwrap());
            }
        }
        combo_begin.push(combo_taps.len().try_into().unwrap());
        assert!(combo_taps.len() < 64 * 1024);
        TapSet {
            data: Rc::new(TapSetData {
                taps,
                combo_taps,
                combo_begin,
                group_begin,
                combos_count: combos.len(),
            }),
        }
    }

    pub fn tap_size(&self) -> usize {
        self.data.group_begin[REGISTER_GROUPS.len()]
    }

    pub fn taps(&self) -> TapIter {
        TapIter {
            data: &self.data.taps,
            cursor: 0,
            end: self.data.group_begin[REGISTER_GROUPS.len()],
        }
    }

    pub fn regs(&self) -> RegisterIter {
        RegisterIter {
            data: &self.data.taps,
            cursor: 0,
            end: self.data.group_begin[REGISTER_GROUPS.len()],
        }
    }

    pub fn group_taps(&self, group: RegisterGroup) -> TapIter {
        let group_id = group as usize;
        TapIter {
            data: &self.data.taps,
            cursor: self.data.group_begin[group_id],
            end: self.data.group_begin[group_id + 1],
        }
    }

    pub fn group_regs(&self, group: RegisterGroup) -> RegisterIter {
        let group_id = group as usize;
        RegisterIter {
            data: &self.data.taps,
            cursor: self.data.group_begin[group_id],
            end: self.data.group_begin[group_id + 1],
        }
    }

    pub fn group_size(&self, group: RegisterGroup) -> usize {
        let group_id = group as usize;
        let idx = self.data.group_begin[group_id + 1] - 1;
        let last = self.data.taps[idx].offset as usize;
        last + 1
    }

    // size_t combosSize() const { return data_->combos.count; }
    pub fn combos_size(&self) -> usize {
        self.data.combos_count
    }

    pub fn combos(&self) -> ComboIter {
        ComboIter {
            data: ComboData {
                taps: &self.data.combo_taps,
                offsets: &self.data.combo_begin,
            },
            id: 0,
            end: self.data.combos_count,
        }
    }

    pub fn get_combo(&self, id: usize) -> ComboRef {
        ComboRef {
            data: ComboData {
                taps: &self.data.combo_taps,
                offsets: &self.data.combo_begin,
            },
            id,
        }
    }
}

pub struct RegisterRef<'a> {
    data: &'a [TapData],
    cursor: usize,
}

impl<'a> RegisterRef<'a> {
    pub fn group(&self) -> RegisterGroup {
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

impl<'a> Debug for RegisterRef<'a> {
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

impl<'a> TapRef<'a> {
    pub fn group(&self) -> RegisterGroup {
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

impl<'a> Debug for TapRef<'a> {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        f.debug_struct("TapRef")
            .field("group", &self.group())
            .field("offset", &self.offset())
            .field("back", &self.back())
            .field("conmbo_id", &self.combo_id())
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
/// Basically, combo N consists of taps in the range [offsets[n], offsets[n+1]).
/// Again this is an implementation detail, and the format is designed to put
/// the actual arrays into static data.
#[derive(Clone)]
pub struct ComboData<'a> {
    taps: &'a [u16],
    offsets: &'a [u16],
}

pub struct ComboRef<'a> {
    data: ComboData<'a>,
    id: usize,
}

impl<'a> ComboRef<'a> {
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

pub mod legacy {
    use super::RegisterGroup;

    pub struct Register<'a> {
        pub group: RegisterGroup,
        pub offset: usize,
        pub back: &'a [usize],
        pub combo_id: usize,
    }

    pub struct Combo<'a> {
        pub back: &'a [usize],
    }

    pub struct Taps<'a> {
        pub registers: &'a [Register<'a>],
        pub combos: &'a [Combo<'a>],
    }

    pub struct TapsInfo {
        pub accum_size: usize,
        pub code_size: usize,
        pub data_size: usize,
        pub num_taps: usize,
    }

    impl<'a> Taps<'a> {
        pub fn get_info(&self) -> TapsInfo {
            let (accum_size, code_size, data_size, num_taps) = self.registers.iter().fold(
                (0, 0, 0, 0),
                |(mut accum_size, mut code_size, mut data_size, num_taps), reg| {
                    match reg.group {
                        RegisterGroup::Accum => {
                            accum_size += 1;
                        }
                        RegisterGroup::Code => {
                            code_size += 1;
                        }
                        RegisterGroup::Data => {
                            data_size += 1;
                        }
                    }
                    (accum_size, code_size, data_size, num_taps + reg.back.len())
                },
            );
            TapsInfo {
                accum_size,
                code_size,
                data_size,
                num_taps,
            }
        }
    }
}
