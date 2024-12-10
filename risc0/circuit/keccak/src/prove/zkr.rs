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

use std::io::Read as _;

use anyhow::Result;
use risc0_circuit_recursion::prove::Program;
use xz2::read::XzDecoder;

use crate::{KECCAK_PO2_RANGE, RECURSION_PO2};

const ZKRS: &[&[u8]] = &[
    include_bytes!("keccak_lift_14.zkr.xz"),
    include_bytes!("keccak_lift_15.zkr.xz"),
    include_bytes!("keccak_lift_16.zkr.xz"),
    include_bytes!("keccak_lift_17.zkr.xz"),
    include_bytes!("keccak_lift_18.zkr.xz"),
];

pub fn get_keccak_zkr(po2: usize) -> Result<Program> {
    let idx = po2 - KECCAK_PO2_RANGE.min().unwrap();
    let mut decoder = XzDecoder::new(ZKRS[idx]);
    let mut bytes = vec![];
    decoder.read_to_end(&mut bytes)?;
    let u32s = bytemuck::cast_slice(&bytes);
    Ok(Program::from_encoded(u32s, RECURSION_PO2))
}
