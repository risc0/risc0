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

use crate::REGISTER_GROUP_CODE;
use anyhow::Result;
use risc0_zkp::{adapter::TapsProvider, field::baby_bear::BabyBearElem};

use super::{Program, CIRCUIT, RECURSION_CODE_SIZE};

pub fn get_zkr(name: &str, po2: usize) -> Result<Program> {
    let code_size = CIRCUIT.get_taps().group_size(REGISTER_GROUP_CODE);
    assert_eq!(code_size, RECURSION_CODE_SIZE);

    let u32s = crate::zkr::get_zkr(name)?;
    Ok(Program {
        code: u32s.iter().cloned().map(BabyBearElem::from).collect(),
        code_size,
        po2,
    })
}
