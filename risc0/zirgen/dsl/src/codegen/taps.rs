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

use risc0_zkp::taps::{TapData, TapSet};
use std::collections::{BTreeMap, BTreeSet};

pub struct TapSetOwned {
    taps: Vec<TapData>,
    combo_taps: Vec<u16>,
    combo_begin: Vec<u16>,
    group_begin: Vec<usize>,
    combos_count: usize,
    reg_count: usize,
    group_names: Vec<&'static str>,
}

pub struct Tap {
    pub group: usize,
    pub pos: usize,
    pub back: usize,
}

impl TapSetOwned {
    pub fn new(raw: &[Tap], group_names: &[&'static str]) -> Self {
        type Reg = BTreeSet<usize>;
        type Group = BTreeMap<usize, Reg>;
        type All = BTreeMap<usize, Group>;

        let mut all: All = BTreeMap::new();
        let mut num_groups: usize = 0;
        for tap in raw {
            all.entry(tap.group)
                .or_default()
                .entry(tap.pos)
                .or_default()
                .insert(tap.back);
            if tap.group >= num_groups {
                num_groups = tap.group + 1;
            }
        }

        // Downstream verifier requires that there be exactly 3 groups, all of which
        // must be nonempty.  TODO: Remove this restriction.
        assert_eq!(num_groups, 3);
        for group_id in 0..3 {
            if !all.contains_key(&group_id) {
                assert!(all.contains_key(&group_id), "All tap groups must have at least one register; tap group {group_id} is empty.");
            }
        }

        let mut group_begin = vec![0; num_groups + 1];
        let mut combo_begin = Vec::new();
        let mut combo_taps = Vec::new();
        let mut taps = Vec::new();
        let mut tot_reg_count = 0;
        // Pre-insert the 'only self' combo
        let myself = BTreeSet::from([0_usize]);
        let mut combos = vec![&myself];
        let mut combos_to_id = BTreeMap::from([(&myself, 0_usize)]);
        // Build flat table
        for group_id in 0..num_groups {
            group_begin[group_id] = taps.len();
            let regs = all.get(&group_id).unwrap();
            let reg_count = regs.keys().last().unwrap() + 1;
            tot_reg_count += reg_count;
            for reg in 0..reg_count {
                // Make sure all registers have at least one tap
                if !regs.contains_key(&reg) {
                    continue;
                }
                let combo = regs.get(&reg).unwrap();
                assert!(combo.len() > 0);
                let combo_id = combos_to_id.entry(&combo).or_insert_with(|| {
                    let ret = combos.len();
                    combos.push(combo);
                    ret
                });
                for back in combo {
                    taps.push(TapData {
                        group: group_id,
                        offset: reg.try_into().unwrap(),
                        back: (*back).try_into().unwrap(),
                        combo: (*combo_id).try_into().unwrap(),
                        skip: combo.len().try_into().unwrap(),
                    });
                }
            }
        }
        group_begin[num_groups] = taps.len();
        for combo in &combos {
            combo_begin.push(combo_taps.len().try_into().unwrap());
            for tap in *combo {
                combo_taps.push((*tap).try_into().unwrap());
            }
        }
        combo_begin.push(combo_taps.len().try_into().unwrap());
        assert!(combo_taps.len() < 64 * 1024);
        TapSetOwned {
            taps,
            combo_taps,
            combo_begin,
            group_begin,
            combos_count: combos.len(),
            reg_count: tot_reg_count,
            group_names: group_names.into(),
        }
    }
}

impl<'a> From<&'a TapSetOwned> for TapSet<'a> {
    fn from(owned: &'a TapSetOwned) -> Self {
        Self {
            taps: owned.taps.as_slice(),
            combo_taps: owned.combo_taps.as_slice(),
            combo_begin: owned.combo_begin.as_slice(),
            group_begin: owned.group_begin.as_slice(),
            combos_count: owned.combos_count,
            reg_count: owned.reg_count,
            group_names: owned.group_names.as_slice(),
            tot_combo_backs: owned.combo_taps.len(),
        }
    }
}

pub fn make_taps(taps: &[Tap], group_names: &[&'static str]) -> TapSet<'static> {
    let owned = Box::new(TapSetOwned::new(taps, group_names));
    let leaked: &'static TapSetOwned = Box::leak(owned);
    leaked.into()
}
