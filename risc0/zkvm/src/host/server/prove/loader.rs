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

use alloc::collections::BTreeMap;
use core::{
    fmt::Debug,
    iter::Peekable,
    ops::{Index, IndexMut},
};

use anyhow::Result;
use log::{debug, trace};
use risc0_core::field::{baby_bear::BabyBearElem, Elem};
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

use crate::host::CIRCUIT;

// TODO: get from circuit
const SETUP_STEP_REGS: usize = 84;

// The number of cycles needed after the body phase.
// 4: Reset(fini)
// 1: RamFini
// 1: BytesFini
const FINI_TAILROOM: usize = 6;

const SHA_K_OFFSET: usize = memory::PRE_LOAD.start();
const SHA_K_SIZE: usize = 64;
const SHA_INIT_OFFSET: usize = SHA_K_OFFSET + SHA_K_SIZE * WORD_SIZE;
const ZEROS_OFFSET: usize = SHA_INIT_OFFSET + DIGEST_WORDS * WORD_SIZE;

static SHA_K: [u32; SHA_K_SIZE] = [
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2,
];

/// These are the columns of the control group.
/// Entries of each column are elements of the Baby Bear Field.
#[derive(Copy, Clone)]
enum ControlIndex {
    Cycle,
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
}

struct ControlGroup(Vec<BabyBearElem>);

impl ControlGroup {
    fn new() -> Self {
        Self(vec![BabyBearElem::ZERO; CIRCUIT.code_size()])
    }

    fn reset(&mut self) {
        self.0.fill(BabyBearElem::ZERO);
    }
}

impl Index<ControlIndex> for ControlGroup {
    type Output = BabyBearElem;

    fn index(&self, index: ControlIndex) -> &Self::Output {
        &self.0[index as usize]
    }
}

impl IndexMut<ControlIndex> for ControlGroup {
    fn index_mut(&mut self, index: ControlIndex) -> &mut Self::Output {
        &mut self.0[index as usize]
    }
}

struct LoaderImpl<F>
where
    F: FnMut(&[BabyBearElem], usize) -> Result<bool>,
{
    cycle: usize,
    code: ControlGroup,
    step: F,
}

impl<F> LoaderImpl<F>
where
    F: FnMut(&[BabyBearElem], usize) -> Result<bool>,
{
    pub fn new(step: F) -> Self {
        Self {
            cycle: 0,
            code: ControlGroup::new(),
            step,
        }
    }

    /// Initialize bytes
    pub fn bytes_init(&mut self) -> Result<bool> {
        debug!("BYTES_INIT");
        self.start();
        self.code[ControlIndex::BytesInit] = BabyBearElem::ONE;
        self.next()
    }

    /// Setup bytes lookup tables
    pub fn bytes_setup(&mut self, count: usize) -> Result<bool> {
        debug!("BYTES_SETUP");
        for _ in 0..count - 1 {
            self.start();
            self.code[ControlIndex::BytesSetup] = BabyBearElem::ONE;
            self.next()?;
        }
        self.start();
        self.code[ControlIndex::BytesSetup] = BabyBearElem::ONE;
        self.code[ControlIndex::Info] = BabyBearElem::ONE;
        self.next()
    }

    /// Initialize ram
    pub fn ram_init(&mut self) -> Result<bool> {
        debug!("RAM_INIT");
        self.start();
        self.code[ControlIndex::RamInit] = BabyBearElem::ONE;
        self.next()
    }

    /// Load Phase: Write binary instructions from ELF into control columns
    /// Instructions are written three words at a time.
    pub fn ram_load(&mut self, triple: &TripleWord) -> Result<bool> {
        trace!("RAM_LOAD[{}]: {triple:?}", self.cycle);
        self.start();
        self.code[ControlIndex::RamLoad] = BabyBearElem::ONE;
        self.code[ControlIndex::Info] = BabyBearElem::new(triple.addr);
        (
            self.code[ControlIndex::Data1Lo],
            self.code[ControlIndex::Data1Hi],
        ) = split_word16(triple.data[0]);
        (
            self.code[ControlIndex::Data2Lo],
            self.code[ControlIndex::Data2Hi],
        ) = split_word16(triple.data[1]);
        (
            self.code[ControlIndex::Data3Lo],
            self.code[ControlIndex::Data3Hi],
        ) = split_word16(triple.data[2]);
        self.next()
    }

    /// Reset Phase
    pub fn reset(&mut self, phase: u32) -> Result<bool> {
        let phase_enum = match phase {
            0 => ControlIndex::Data1Lo,
            1 => ControlIndex::Data1Hi,
            2 => ControlIndex::Data2Lo,
            _ => unimplemented!("Invalid phase"),
        };
        debug!("RESET");
        self.start();
        self.code[ControlIndex::Reset] = BabyBearElem::ONE;
        self.code[ControlIndex::Info] = BabyBearElem::ONE; // isFirst
        self.code[phase_enum] = BabyBearElem::ONE;
        self.next()?;

        self.start();
        self.code[ControlIndex::Reset] = BabyBearElem::ONE;
        self.code[ControlIndex::Info] = BabyBearElem::ZERO; // isFirst
        self.code[phase_enum] = BabyBearElem::ONE;
        self.next()
    }

    /// Body Phase: In this phase, the zkVM executes the loaded instructions.
    pub fn body(&mut self) -> Result<()> {
        debug!("BODY");
        loop {
            self.start();
            self.code[ControlIndex::Body] = BabyBearElem::ONE;
            if !self.next_fini(FINI_TAILROOM)? {
                break;
            }
        }
        Ok(())
    }

    /// Fini Phase: Initialize RamFini and BytesFini
    pub fn fini(&mut self) -> Result<bool> {
        debug!("FINI");
        self.start();
        self.code[ControlIndex::RamFini] = BabyBearElem::ONE;
        self.next()?;

        self.start();
        self.code[ControlIndex::BytesFini] = BabyBearElem::ONE;
        self.next()
    }

    fn start(&mut self) {
        self.code.reset();
        self.code[ControlIndex::Cycle] = BabyBearElem::new(self.cycle as u32);
    }

    fn next(&mut self) -> Result<bool> {
        self.cycle += 1;
        let keep_going = (self.step)(&self.code.0, 0)?;
        assert!(keep_going, "Premature halt, cycle: {}", self.cycle);
        Ok(keep_going)
    }

    fn next_fini(&mut self, fini: usize) -> Result<bool> {
        self.cycle += 1;
        (self.step)(&self.code.0, fini)
    }
}

fn split_word16(value: u32) -> (BabyBearElem, BabyBearElem) {
    (
        BabyBearElem::new(value & 0xffff),
        BabyBearElem::new(value >> 16),
    )
}

const fn div_ceil(a: usize, b: usize) -> usize {
    (a + b - 1) / b
}

const fn setup_count(regs: usize) -> usize {
    let pairs = regs / 4;
    div_ceil(32 * 1024, pairs)
}

#[derive(PartialEq)]
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
    it: Peekable<alloc::collections::btree_map::Iter<'a, u32, u32>>,
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

/// Loads data into the zkVM image
///
/// Handles both loading the initial zkVM data and also loading updated data for
/// each time step.
pub struct Loader {
    system: Vec<TripleWord>,
}

impl Default for Loader {
    fn default() -> Self {
        Self::new()
    }
}

impl Loader {
    const SETUP_CYCLES: usize = setup_count(SETUP_STEP_REGS);

    /// Construct a Loader
    ///
    /// Loads the common setup data used by all zkVMs
    pub fn new() -> Self {
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

        Self {
            system: TripleWordIter::new(&image).collect(),
        }
    }

    /// Load data specific to this zkVM instance
    ///
    /// Starting from the initialized image created by [Loader::new], use the
    /// function `step` to repeatedly update the image, thereby creating an
    /// execution trace.
    #[tracing::instrument(skip_all)]
    pub fn load<F>(&self, step: F) -> Result<usize>
    where
        F: FnMut(&[BabyBearElem], usize) -> Result<bool>,
    {
        let mut loader = LoaderImpl::new(step);
        self.pre_steps(&mut loader)?;
        loader.body()?;
        self.post_steps(&mut loader)?;
        Ok(loader.cycle)
    }

    /// Compute the number of cycles needed for initialization.
    pub fn init_cycles(&self) -> usize {
        let mut loader = LoaderImpl::new(|_, _| Ok(true));
        self.pre_steps(&mut loader).unwrap();
        loader.cycle
    }

    /// Compute the number of cycles needed for finalization.
    pub fn fini_cycles(&self) -> usize {
        let mut loader = LoaderImpl::new(|_, _| Ok(true));
        self.post_steps(&mut loader).unwrap();
        loader.cycle
    }

    fn pre_steps<F>(&self, loader: &mut LoaderImpl<F>) -> Result<()>
    where
        F: FnMut(&[BabyBearElem], usize) -> Result<bool>,
    {
        loader.bytes_init()?;
        loader.bytes_setup(Self::SETUP_CYCLES)?;
        loader.ram_init()?;
        for triple in &self.system {
            loader.ram_load(triple)?;
        }
        loader.reset(0)?;
        Ok(())
    }

    fn post_steps<F>(&self, loader: &mut LoaderImpl<F>) -> Result<()>
    where
        F: FnMut(&[BabyBearElem], usize) -> Result<bool>,
    {
        loader.reset(1)?;
        loader.reset(2)?;
        loader.fini()?;
        Ok(())
    }

    /// Compute the `ControlId` associated with the given HAL
    pub fn compute_control_id<H: Hal<Elem = BabyBearElem>>(&self, hal: &H) -> Vec<Digest> {
        let code_size = CIRCUIT.code_size();

        // Start with an empty table
        let mut table = Vec::new();

        // Make the digest for each level
        for i in MIN_CYCLES_PO2..MAX_CYCLES_PO2 {
            let cycles = 1 << i;
            log::info!("po2: {i}");
            // Make a vector & set it up with the elf data
            let mut code = vec![BabyBearElem::default(); cycles * code_size];
            self.load_code(&mut code, cycles);
            // Copy into accel buffer
            let coeffs = hal.copy_from_elem("coeffs", &code);
            // Do interpolate & shift
            hal.batch_interpolate_ntt(&coeffs, code_size);
            hal.zk_shift(&coeffs, code_size);
            // Make the poly-group & extract the root
            let code_group = PolyGroup::new(hal, coeffs, code_size, cycles, "code");
            table.push(*code_group.merkle.root());
        }

        table
    }

    fn load_code(&self, code: &mut [BabyBearElem], max_cycles: usize) {
        let code_size = CIRCUIT.code_size();
        let mut cycle = 0;
        self.load(|chunk, fini| {
            for i in 0..code_size {
                code[max_cycles * i + cycle] = chunk[i];
            }
            let total = cycle + fini + ZK_CYCLES;
            if total < max_cycles {
                cycle += 1;
                Ok(true)
            } else {
                log::info!("Halting. {cycle} + {fini} + ZK_CYCLES ({total}) < {max_cycles}");
                Ok(false)
            }
        })
        .unwrap();
    }
}

#[cfg(test)]
mod tests {
    use alloc::collections::BTreeMap;

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
