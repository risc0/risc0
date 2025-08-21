// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use std::io::{Cursor, Read as _};

use anyhow::{Context as _, Result, bail};

use super::Program;

const ZKR_ZIP: &[u8] = include_bytes!(concat!(env!("OUT_DIR"), "/recursion_zkr.zip"));

pub fn get_zkr(name: &str, po2: usize) -> Result<Program> {
    let mut zip = zip::ZipArchive::new(Cursor::new(ZKR_ZIP))?;
    let encoded = extract_zkr(&mut zip, name)?;
    Ok(Program::from_encoded(&encoded, po2))
}

/// Iterate over all provided zkr programs.
///
/// ```rust
/// let listing = risc0_circuit_recursion::prove::zkr::get_all_zkrs().unwrap();
/// println!("{}", listing.into_iter().map(|(name, _)| name).collect::<Vec<_>>().join("\n"));
/// ```
pub fn get_all_zkrs() -> Result<Vec<(String, Vec<u32>)>> {
    let mut zip = zip::ZipArchive::new(Cursor::new(ZKR_ZIP))?;
    let files: Vec<_> = zip.file_names().map(|name| name.to_string()).collect();
    files
        .into_iter()
        .map(|name| {
            let encoded = extract_zkr(&mut zip, &name)?;
            Ok((name, encoded))
        })
        .collect()
}

fn extract_zkr(zip: &mut zip::ZipArchive<Cursor<&[u8]>>, name: &str) -> Result<Vec<u32>> {
    let mut f = zip
        .by_name(name)
        .with_context(|| format!("Failed to read {name}"))?;
    let uncompressed_size = f.size() as usize;

    if uncompressed_size % std::mem::size_of::<u32>() != 0 {
        bail!(".zkr is incorrect size");
    }

    let mut u32s = vec![0u32; uncompressed_size / std::mem::size_of::<u32>()];
    f.read_exact(bytemuck::cast_slice_mut(&mut u32s[..]))?;

    Ok(u32s)
}
