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

extern crate alloc;

use alloc::vec::Vec;

use risc0_zkp::field::baby_bear::BabyBearElem;

// TODO: Automatically generate this from the circuit somehow without
// messing up bootstrap dependencies.
/// Number of columns used in the recursion circuit's code section.
pub const RECURSION_CODE_SIZE: usize = 21;

/// Number of rows in the recursion circuit witness as a power of 2.
pub const RECURSION_PO2: usize = 18;

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
}
