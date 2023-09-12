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

use std::collections::VecDeque;

use risc0_core::field::{Elem, ExtElem, Field};
use risc0_zkp::MAX_CYCLES;

// Main RAM plonk rows have the following 7 plonk elements:
// addr, cycle, isWrite, byte0, byte1, byte2, byte3
#[derive(Ord, PartialOrd, Eq, PartialEq)]
struct MainRamPlonkRow {
    addr: u32,
    // (cycle << 2) | mem_op
    cycle_and_write_flag: u32,
    val: u32,
}

pub struct RamPlonk {
    main_ram: Vec<MainRamPlonkRow>,
}

impl RamPlonk {
    pub fn new() -> Self {
        // Make sure cycle_and_write_flag won't overflow
        assert!(MAX_CYCLES < ((u32::MAX as usize) << 2));

        RamPlonk {
            main_ram: Vec::new(),
        }
    }

    pub fn write<E: Elem>(&mut self, elems: &[E; 7])
    where
        u32: From<E>,
    {
        let addr = u32::from(elems[0]);
        let cycle = u32::from(elems[1]);
        let mem_op = u32::from(elems[2]);
        debug_assert!(mem_op < 4);
        let cycle_and_write_flag = (cycle << 2) + mem_op;

        for elem in &elems[3..] {
            debug_assert!(u32::from(*elem) < 256);
        }
        self.main_ram.push(MainRamPlonkRow {
            addr,
            cycle_and_write_flag,
            val: u32::from(elems[3])
                + (u32::from(elems[4]) << 8)
                + (u32::from(elems[5]) << 16)
                + (u32::from(elems[6]) << 24),
        });
    }

    pub fn sort(&mut self) {
        // Reverse sort all plonk rows so we can pop them off the back in order.
        self.main_ram.sort_unstable_by(|a, b| b.cmp(a));
    }

    pub fn read<E: Elem>(&mut self, elems: &mut [E; 7])
    where
        u32: From<E>,
    {
        let mut set_elem = |idx, val: u32| {
            elems[idx] = E::from_u64(val as u64);
        };
        let row = self.main_ram.pop().unwrap();
        set_elem(0, row.addr);
        set_elem(1, row.cycle_and_write_flag >> 2);
        set_elem(2, row.cycle_and_write_flag & 3);
        set_elem(3, row.val & 0xFF);
        set_elem(4, (row.val >> 8) & 0xFF);
        set_elem(5, (row.val >> 16) & 0xFF);
        set_elem(6, (row.val >> 24) & 0xFF);
    }
}

// Plonk for bytes.  Rows each have 2 byte elements, each of which is
// in [0, 256).  We construct these into a short, [0, 256*256), and
// count how many of each row occurs.
pub struct BytesPlonk {
    counts: Box<[u32; 256 * 256]>,

    read_pos: usize,
}

impl BytesPlonk {
    pub fn new() -> Self {
        BytesPlonk {
            counts: Box::new([0; 256 * 256]),
            read_pos: 0,
        }
    }

    pub fn write<E: Elem>(&mut self, elems: &[E; 2])
    where
        u32: From<E>,
    {
        for elem in elems {
            debug_assert!(u32::from(*elem) < 256);
        }
        let index = ((u32::from(elems[0]) << 8) + u32::from(elems[1])) as usize;
        self.counts[index] += 1;
    }

    pub fn sort(&mut self) {
        // BytesPlonk is already sorted.
    }

    pub fn read<E: Elem>(&mut self, outs: &mut [E; 2]) {
        while self.counts[self.read_pos] == 0 {
            self.read_pos += 1;
        }

        let b1 = (self.read_pos >> 8) & 0xFF;
        let b2 = self.read_pos & 0xFF;

        self.counts[self.read_pos] -= 1;

        *outs = [E::from_u64(b1 as u64), E::from_u64(b2 as u64)];
    }
}

/// Plonk accumulations.  Saves factors to compute prefix products.
pub struct PlonkAccum<F: Field> {
    elems: VecDeque<F::ExtElem>,
}

impl<F: Field> PlonkAccum<F> {
    pub fn new() -> Self {
        PlonkAccum {
            elems: VecDeque::new(),
        }
    }

    // TODO: When the circuit supports ExtElem natively we should operate on those
    // directly instead of converting from E::Elem.
    pub fn write(&mut self, elems: &[F::Elem]) {
        self.elems.extend(
            elems
                .chunks_exact(F::ExtElem::EXT_SIZE)
                .map(|v| F::ExtElem::from_subelems(v.iter().cloned())),
        );
    }

    pub fn read(&mut self, outs: &mut [F::Elem]) {
        for out in outs.chunks_exact_mut(F::ExtElem::EXT_SIZE) {
            out.clone_from_slice(self.elems.pop_front().unwrap().subelems());
        }
    }
}

impl<F: Field> Default for PlonkAccum<F> {
    fn default() -> Self {
        Self::new()
    }
}
