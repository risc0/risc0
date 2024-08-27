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

use std::{
    collections::BTreeMap,
    fmt::Debug,
    iter::Peekable,
    ops::{Index, IndexMut},
};

use risc0_core::{
    field::{baby_bear::BabyBearElem, Elem},
    scope,
};
use risc0_zkp::{
    adapter::TapsProvider,
    core::{
        digest::{Digest, DIGEST_WORDS},
        hash::sha::SHA256_INIT,
    },
    hal::Hal,
    prove::poly_group::PolyGroup,
    MAX_CYCLES_PO2, MIN_CYCLES_PO2, ZK_CYCLES,
};
use risc0_zkvm_platform::{memory, WORD_SIZE};

use crate::CIRCUIT;

pub const SHA_K_OFFSET: usize = memory::PRE_LOAD.start();
pub const SHA_K_SIZE: usize = 64;
pub const SHA_INIT_OFFSET: usize = SHA_K_OFFSET + SHA_K_SIZE * WORD_SIZE;
pub const ZEROS_OFFSET: usize = SHA_INIT_OFFSET + DIGEST_WORDS * WORD_SIZE;

// TODO: generate from zirgen
pub const SETUP_STEP_REGS: usize = 84;
pub const SETUP_CYCLES: usize = setup_count(SETUP_STEP_REGS);
pub const RAM_LOAD_CYCLES: usize = 27;

// The number of cycles needed before the body phase.
// BytesInit: 1
// BytesSetup: 1561
// RamInit: 1
// RamLoad: 27
// Reset(0): 2
pub const INIT_CYCLES: usize = 1 + SETUP_CYCLES + 1 + RAM_LOAD_CYCLES + 2;

// The number of cycles needed after the body phase.
// Reset(1): 2
// Reset(2): 2
// RamFini: 1
// BytesFini: 1
pub const FINI_CYCLES: usize = 2 + 2 + 1 + 1;

pub static SHA_K: [u32; SHA_K_SIZE] = [
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2,
];

const fn div_ceil(a: usize, b: usize) -> usize {
    (a + b - 1) / b
}

const fn setup_count(regs: usize) -> usize {
    let pairs = regs / 4;
    div_ceil(32 * 1024, pairs)
}

/// These are the registers of the control group.
#[derive(Copy, Clone)]
enum CtrlReg {
    _Cycle, // This register is handled by the loader
    BytesInit,
    BytesSetup,
    RamInit,
    RamLoad,
    Reset,
    Body,
    RamFini,
    BytesFini,
    Info,
    Data1Lo,
    Data1Hi,
    Data2Lo,
    Data2Hi,
    Data3Lo,
    Data3Hi,
    NumRegs,
}

#[derive(Clone)]
pub struct CtrlCycle([BabyBearElem; CtrlReg::NumRegs as usize]);

fn split_word16(value: u32) -> (BabyBearElem, BabyBearElem) {
    (
        BabyBearElem::new(value & 0xffff),
        BabyBearElem::new(value >> 16),
    )
}

impl CtrlCycle {
    fn bytes_init() -> Self {
        let mut row = Self([BabyBearElem::ZERO; CtrlReg::NumRegs as usize]);
        row[CtrlReg::BytesInit] = BabyBearElem::ONE;
        row
    }

    fn bytes_setup(info: BabyBearElem) -> Self {
        let mut row = Self([BabyBearElem::ZERO; CtrlReg::NumRegs as usize]);
        row[CtrlReg::BytesSetup] = BabyBearElem::ONE;
        row[CtrlReg::Info] = info;
        row
    }

    fn ram_init() -> Self {
        let mut row = Self([BabyBearElem::ZERO; CtrlReg::NumRegs as usize]);
        row[CtrlReg::RamInit] = BabyBearElem::ONE;
        row
    }

    fn ram_load(triple: TripleWord) -> Self {
        let mut row = Self([BabyBearElem::ZERO; CtrlReg::NumRegs as usize]);
        row[CtrlReg::RamLoad] = BabyBearElem::ONE;
        row[CtrlReg::Info] = BabyBearElem::new(triple.addr);
        (row[CtrlReg::Data1Lo], row[CtrlReg::Data1Hi]) = split_word16(triple.data[0]);
        (row[CtrlReg::Data2Lo], row[CtrlReg::Data2Hi]) = split_word16(triple.data[1]);
        (row[CtrlReg::Data3Lo], row[CtrlReg::Data3Hi]) = split_word16(triple.data[2]);
        row
    }

    fn reset(is_first: BabyBearElem, phase: CtrlReg) -> Self {
        let mut row = Self([BabyBearElem::ZERO; CtrlReg::NumRegs as usize]);
        row[CtrlReg::Reset] = BabyBearElem::ONE;
        row[CtrlReg::Info] = is_first;
        row[phase] = BabyBearElem::ONE;
        row
    }

    fn ram_fini() -> Self {
        let mut row = Self([BabyBearElem::ZERO; CtrlReg::NumRegs as usize]);
        row[CtrlReg::RamFini] = BabyBearElem::ONE;
        row
    }

    fn bytes_fini() -> Self {
        let mut row = Self([BabyBearElem::ZERO; CtrlReg::NumRegs as usize]);
        row[CtrlReg::BytesFini] = BabyBearElem::ONE;
        row
    }

    fn body() -> Self {
        let mut row = Self([BabyBearElem::ZERO; CtrlReg::NumRegs as usize]);
        row[CtrlReg::Body] = BabyBearElem::ONE;
        row
    }
}

impl Index<CtrlReg> for CtrlCycle {
    type Output = BabyBearElem;

    fn index(&self, index: CtrlReg) -> &Self::Output {
        &self.0[index as usize]
    }
}

impl IndexMut<CtrlReg> for CtrlCycle {
    fn index_mut(&mut self, index: CtrlReg) -> &mut Self::Output {
        &mut self.0[index as usize]
    }
}

#[derive(Clone, Copy, PartialEq)]
struct TripleWord {
    addr: u32,
    data: [u32; 3],
}

impl Debug for TripleWord {
    fn fmt(&self, f: &mut core::fmt::Formatter<'_>) -> core::fmt::Result {
        f.write_fmt(format_args!(
            "0x{:08X}[0x{:08X}, 0x{:08X}, 0x{:08X}]",
            self.addr * 4,
            self.data[0],
            self.data[1],
            self.data[2]
        ))
    }
}

struct TripleWordIter<'a> {
    it: Peekable<std::collections::btree_map::Iter<'a, u32, u32>>,
}

impl<'a> TripleWordIter<'a> {
    fn new(image: &'a BTreeMap<u32, u32>) -> Self {
        Self {
            it: image.iter().peekable(),
        }
    }
}

impl<'a> Iterator for TripleWordIter<'a> {
    type Item = TripleWord;

    fn next(&mut self) -> Option<Self::Item> {
        let mut cur = TripleWord {
            addr: 0,
            data: [0, 0, 0],
        };
        for i in 0..3 {
            match self.it.peek() {
                Some((addr, data)) => {
                    let addr = **addr / 4;
                    if i == 0 {
                        cur.addr = addr;
                    } else if addr != cur.addr + i as u32 {
                        continue;
                    }
                    cur.data[i] = **data;
                    self.it.next();
                }
                None => {
                    if i == 0 {
                        return None;
                    }
                }
            }
        }
        Some(cur)
    }
}

pub struct Loader {
    max_cycles: usize,
    pub ctrl: Vec<BabyBearElem>,
    cycle: usize,
    ram_load_cycles: Vec<CtrlCycle>,
}

pub fn ram_load_cycles() -> Vec<CtrlCycle> {
    let mut image: BTreeMap<u32, u32> = BTreeMap::new();

    // Setup 'k' for SHA
    for (i, word) in SHA_K.iter().enumerate() {
        image.insert((SHA_K_OFFSET + i * WORD_SIZE) as u32, *word);
    }

    // Setup SHA-256 Init
    for (i, word) in SHA256_INIT.as_words().iter().enumerate() {
        image.insert((SHA_INIT_OFFSET + i * WORD_SIZE) as u32, *word);
    }

    // Setup ZEROS
    for i in 0..DIGEST_WORDS {
        image.insert((ZEROS_OFFSET + i * WORD_SIZE) as u32, 0);
    }

    TripleWordIter::new(&image)
        .map(CtrlCycle::ram_load)
        .collect()
}

impl Loader {
    pub fn new(max_cycles: usize, ctrl_size: usize) -> Self {
        let ram_load_cycles = ram_load_cycles();
        assert_eq!(ram_load_cycles.len(), RAM_LOAD_CYCLES);
        Self {
            max_cycles,
            ctrl: vec![BabyBearElem::ZERO; max_cycles * ctrl_size],
            cycle: 0,
            ram_load_cycles,
        }
    }

    pub fn load(&mut self) -> usize {
        scope!("load");

        self.pre_steps();
        self.body();
        self.post_steps();
        self.cycle
    }

    fn pre_steps(&mut self) {
        self.bytes_init();
        self.bytes_setup();
        self.ram_init();
        self.ram_load();
        self.reset(0);
    }

    fn body(&mut self) {
        let body_cycles = self.max_cycles - self.cycle - FINI_CYCLES - ZK_CYCLES;
        tracing::debug!("[{}] BODY: {body_cycles}", self.cycle);
        for _ in 0..body_cycles {
            self.add_cycle(CtrlCycle::body());
        }
    }

    fn post_steps(&mut self) {
        self.reset(1);
        self.reset(2);
        self.fini();
    }

    fn bytes_init(&mut self) {
        tracing::debug!("[{}] BYTES_INIT", self.cycle);
        self.add_cycle(CtrlCycle::bytes_init());
    }

    fn bytes_setup(&mut self) {
        tracing::debug!("[{}] BYTES_SETUP", self.cycle);
        for _ in 0..SETUP_CYCLES - 1 {
            self.add_cycle(CtrlCycle::bytes_setup(BabyBearElem::ZERO));
        }
        self.add_cycle(CtrlCycle::bytes_setup(BabyBearElem::ONE));
    }

    fn ram_init(&mut self) {
        tracing::debug!("[{}] RAM_INIT", self.cycle);
        self.add_cycle(CtrlCycle::ram_init());
    }

    fn ram_load(&mut self) {
        for cycle in self.ram_load_cycles.clone() {
            self.add_cycle(cycle);
        }
    }

    fn reset(&mut self, phase: u32) {
        tracing::debug!("[{}] RESET({phase})", self.cycle);
        let phase = match phase {
            0 => CtrlReg::Data1Lo,
            1 => CtrlReg::Data1Hi,
            2 => CtrlReg::Data2Lo,
            _ => unimplemented!("Invalid phase"),
        };
        self.add_cycle(CtrlCycle::reset(BabyBearElem::ONE, phase));
        self.add_cycle(CtrlCycle::reset(BabyBearElem::ZERO, phase));
    }

    fn fini(&mut self) {
        tracing::debug!("[{}] RAM_FINI", self.cycle);
        self.add_cycle(CtrlCycle::ram_fini());
        tracing::debug!("[{}] BYTES_FINI", self.cycle);
        self.add_cycle(CtrlCycle::bytes_fini());
    }

    fn add_cycle(&mut self, row: CtrlCycle) {
        self.ctrl[self.cycle] = BabyBearElem::new(self.cycle as u32);
        for i in 1..row.0.len() {
            self.ctrl[self.max_cycles * i + self.cycle] = row.0[i];
        }
        self.cycle += 1;
    }

    // Compute the `ControlId` associated with the given HAL, along with a textual description.
    pub fn compute_control_id_table<H: Hal<Elem = BabyBearElem>>(hal: &H) -> Vec<(String, Digest)> {
        // Make the digest for each level
        let mut table = Vec::new();
        for po2 in MIN_CYCLES_PO2..=MAX_CYCLES_PO2 {
            table.push((
                format!("rv32im po2={po2}"),
                Self::compute_control_id(hal, po2),
            ));
        }
        table
    }

    pub fn compute_control_id<H: Hal<Elem = BabyBearElem>>(hal: &H, po2: usize) -> Digest {
        tracing::debug!("po2: {po2}");
        let cycles = 1 << po2;
        let ctrl_size = CIRCUIT.ctrl_size();
        let mut loader = Loader::new(cycles, ctrl_size);
        // Make a vector & set it up with the elf data
        loader.load();
        // Copy into accel buffer
        let coeffs = hal.copy_from_elem("coeffs", &loader.ctrl);
        // Do interpolate & shift
        hal.batch_interpolate_ntt(&coeffs, ctrl_size);
        hal.zk_shift(&coeffs, ctrl_size);
        // Make the poly-group & extract the root
        let group = PolyGroup::new(hal, coeffs, ctrl_size, cycles, "ctrl");
        *group.merkle.root()
    }
}

#[cfg(test)]
mod tests {
    use std::collections::BTreeMap;

    use test_log::test;

    use super::{TripleWord, TripleWordIter};

    fn triple_test(input: &[(u32, u32)], expected: &[TripleWord]) {
        let mut map = BTreeMap::new();
        for (addr, data) in input {
            map.insert(*addr, *data);
        }
        let result: Vec<TripleWord> = TripleWordIter::new(&map).collect();
        assert_eq!(result.as_slice(), expected);
    }

    #[test]
    fn triple_word_iter() {
        triple_test(&[], &[]);
        triple_test(
            &[(0, 1)],
            &[TripleWord {
                addr: 0,
                data: [1, 0, 0],
            }],
        );
        triple_test(
            &[(0, 1), (4, 2)],
            &[TripleWord {
                addr: 0,
                data: [1, 2, 0],
            }],
        );
        triple_test(
            &[(0, 1), (4, 2), (8, 3)],
            &[TripleWord {
                addr: 0,
                data: [1, 2, 3],
            }],
        );
        triple_test(
            &[(0, 1), (8, 3)],
            &[TripleWord {
                addr: 0,
                data: [1, 0, 3],
            }],
        );
        triple_test(
            &[(0, 1), (4, 2), (8, 3), (12, 4)],
            &[
                TripleWord {
                    addr: 0,
                    data: [1, 2, 3],
                },
                TripleWord {
                    addr: 3,
                    data: [4, 0, 0],
                },
            ],
        );
    }
}
