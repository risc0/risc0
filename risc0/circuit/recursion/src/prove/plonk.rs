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

use std::collections::VecDeque;

use risc0_zkp::field::{self, ExtElem};

// Write once RAM
#[derive(Ord, PartialOrd, Eq, PartialEq)]
struct WomPlonkRow {
    addr: u32,
    val: [u32; 4],
}

pub struct WomPlonk {
    wom_ram: Vec<WomPlonkRow>,
}

impl WomPlonk {
    pub fn new() -> Self {
        WomPlonk {
            wom_ram: Vec::new(),
        }
    }

    pub fn write<E: field::Elem>(&mut self, elems: &[E; 5])
    where
        u32: From<E>,
    {
        self.wom_ram.push(WomPlonkRow {
            addr: u32::from(elems[0]),
            val: core::array::from_fn(|i| u32::from(elems[1 + i])),
        });
    }

    pub fn sort(&mut self) {
        // Reverse sort all plonk rows so we can pop them off the back in order.
        self.wom_ram.sort_unstable_by(|a, b| b.cmp(a));
    }

    pub fn read<E: field::Elem>(&mut self, elems: &mut [E; 5])
    where
        u32: From<E>,
    {
        let row = self.wom_ram.pop().unwrap();
        let mut set_elem = |idx, val: u32| {
            elems[idx] = E::from_u64(val as u64);
        };
        set_elem(0, row.addr);
        set_elem(1, row.val[0]);
        set_elem(2, row.val[1]);
        set_elem(3, row.val[2]);
        set_elem(4, row.val[3]);
    }
}

/// Plonk accumulations.  Saves factors to compute prefix products.
pub struct PlonkAccum<F: field::Field> {
    elems: VecDeque<F::ExtElem>,
}

impl<F: field::Field> PlonkAccum<F> {
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

impl<F: field::Field> Default for PlonkAccum<F> {
    fn default() -> Self {
        Self::new()
    }
}
