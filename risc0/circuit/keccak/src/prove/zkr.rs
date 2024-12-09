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

use std::io::{Cursor, Read as _};

use anyhow::{Context as _, Result};
use risc0_circuit_recursion::prove::Program;
use zip::ZipArchive;

use crate::RECURSION_PO2;

const ZKR_ZIP: &[u8] = include_bytes!("keccak_zkr.zip");

pub fn get_keccak_zkr(po2: usize) -> Result<Program> {
    let name = format!("keccak_lift_{po2}.zkr");

    let mut zip = ZipArchive::new(Cursor::new(ZKR_ZIP))?;
    let mut entry = zip
        .by_name(&name)
        .with_context(|| format!("Failed to read {name}"))?;

    let mut bytes = Vec::new();
    entry.read_to_end(&mut bytes)?;
    let u32s = bytemuck::cast_slice(&bytes);

    Ok(Program::from_encoded(u32s, RECURSION_PO2))
}
