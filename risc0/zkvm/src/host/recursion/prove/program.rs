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

use risc0_zkp::{
    core::{digest::Digest, hash::HashSuite},
    field::baby_bear::{BabyBear, BabyBearElem},
    hal::{cpu::CpuHal, Hal},
    prove::poly_group::PolyGroup,
};

use super::RECURSION_PO2;

/// TODO
#[derive(Clone)]
pub struct Program {
    /// TODO
    pub code: Vec<BabyBearElem>,

    /// TODO
    pub code_size: usize,
}

impl Program {
    /// TODO
    pub fn code_rows(&self) -> usize {
        self.code.len() / self.code_size
    }

    /// TODO
    pub fn code_by_row(&self) -> impl Iterator<Item = &[BabyBearElem]> {
        self.code.as_slice().chunks(self.code_size)
    }

    /// TODO
    pub fn compute_control_id(&self, hash_suite: HashSuite<BabyBear>) -> Digest {
        let hal = CpuHal::new(hash_suite);
        let cycles = 1 << RECURSION_PO2;

        let mut code = vec![BabyBearElem::default(); cycles * self.code_size];

        for (cycle, row) in self.code_by_row().enumerate() {
            for (i, elem) in row.iter().enumerate() {
                code[cycles * i + cycle] = *elem;
            }
        }
        let coeffs = hal.copy_from_elem("coeffs", &code);
        // Do interpolate & shift
        hal.batch_interpolate_ntt(&coeffs, self.code_size);
        hal.zk_shift(&coeffs, self.code_size);
        // Make the poly-group & extract the root
        let code_group = PolyGroup::new(&hal, coeffs, self.code_size, cycles, "code");
        let root = *code_group.merkle.root();
        log::trace!("Computed recursion code: {root:?}");
        root
    }
}
