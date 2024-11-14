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

use std::io::{Cursor, Read};

use anyhow::{Context, Result};
use zip::ZipArchive;

const ZKR_ZIP: &[u8] = include_bytes!("prove/keccak_zkr.zip");

pub fn get_zkr_u32s(name: &str) -> Result<Vec<u32>> {
    let mut zip = ZipArchive::new(Cursor::new(ZKR_ZIP))?;
    let mut entry = zip
        .by_name(name)
        .with_context(|| format!("Failed to read {name}"))?;

    let mut bytes = Vec::new();
    entry.read_to_end(&mut bytes)?;

    Ok(Vec::from(bytemuck::cast_slice(bytes.as_slice())))
}
