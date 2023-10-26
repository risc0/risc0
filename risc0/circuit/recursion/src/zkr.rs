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
use risc0_zkp::core::digest::Digest;

const ZKR_ZIP: &[u8] = include_bytes!(concat!(env!("OUT_DIR"), "/recursion_zkr.zip"));
const CONTROL_ID_SUFFIX: &str = ".control_id";

pub fn get_zkr(name: &str) -> Result<Vec<u32>> {
    let mut zip = zip::ZipArchive::new(std::io::Cursor::new(ZKR_ZIP)).unwrap();
    let mut f = zip
        .by_name(name)
        .with_context(|| format!("Failed to read {name}"))?;

    let mut u8vec: Vec<u8> = Vec::new();
    f.read_to_end(&mut u8vec)?;

    Ok(Vec::from(bytemuck::cast_slice(u8vec.as_slice())))
}

pub fn get_all_zkrs() -> Result<Vec<(String, Vec<u32>)>> {
    let mut zip = zip::ZipArchive::new(std::io::Cursor::new(ZKR_ZIP)).unwrap();
    let files: Result<Vec<Option<String>>> = (0..zip.len())
        .map(|idx| {
            let f = zip.by_index(idx)?;
            let name = f.name().to_string();

            if name.ends_with(CONTROL_ID_SUFFIX) {
                Ok(None)
            } else {
                Ok(Some(name))
            }
        })
        .collect();

    files?
        .into_iter()
        .flatten()
        .map(|name| {
            let mut f = zip.by_name(&name)?;

            let mut u8vec: Vec<u8> = Vec::new();
            f.read_to_end(&mut u8vec)?;

            Ok((name, Vec::from(bytemuck::cast_slice(u8vec.as_slice()))))
        })
        .collect()
}

pub fn get_control_id(name: &str) -> Result<Digest> {
    Ok(Digest::try_from(
        get_zkr(&format!("{name}{CONTROL_ID_SUFFIX}"))?.as_slice(),
    )?)
}
