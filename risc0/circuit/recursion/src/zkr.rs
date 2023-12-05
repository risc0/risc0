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

// Control trees for various recursion programs

use std::io::Read;

use anyhow::{Context, Result};

const ZKR_ZIP: &[u8] = include_bytes!(concat!(env!("OUT_DIR"), "/recursion_zkr.zip"));

/// Lookup and return the zkr recursion program as a vector of words.
///
/// ```rust
/// let encoded_program = risc0_circuit_recursion::zkr::get_zkr("lift_20.zkr").unwrap();
/// ```
pub fn get_zkr(name: &str) -> Result<Vec<u32>> {
    let mut zip = zip::ZipArchive::new(std::io::Cursor::new(ZKR_ZIP)).unwrap();
    let mut f = zip
        .by_name(name)
        .with_context(|| format!("Failed to read {name}"))?;

    let mut u8vec: Vec<u8> = Vec::new();
    f.read_to_end(&mut u8vec)?;

    Ok(Vec::from(bytemuck::cast_slice(u8vec.as_slice())))
}

/// Iterate over all provided zkr programs.
///
/// ```rust
/// let listing = risc0_circuit_recursion::zkr::get_all_zkrs().unwrap();
/// println!("{}", listing.into_iter().map(|(name, _)| name).collect::<Vec<_>>().join("\n"));
/// ```
pub fn get_all_zkrs() -> Result<Vec<(String, Vec<u32>)>> {
    let mut zip = zip::ZipArchive::new(std::io::Cursor::new(ZKR_ZIP)).unwrap();
    let files: Vec<String> = (0..zip.len())
        .map(|idx| Ok(zip.by_index(idx)?.name().to_string()))
        .collect::<Result<_>>()?;

    files
        .into_iter()
        .map(|name| {
            let mut f = zip.by_name(&name)?;

            let mut u8vec: Vec<u8> = Vec::new();
            f.read_to_end(&mut u8vec)?;

            Ok((name, Vec::from(bytemuck::cast_slice(u8vec.as_slice()))))
        })
        .collect()
}
