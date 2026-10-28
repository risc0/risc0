// Copyright 2026 RISC Zero, Inc.
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

use anyhow::{anyhow, bail, Result};

use super::Program;

pub fn get_zkr(name: &str, po2: usize) -> Result<Program> {
    let encoded = extract_zkr(ZkrSection::for_name(name), name)?;
    Ok(Program::from_encoded(&encoded, po2))
}

/// Iterate over all provided zkr programs, sorted by name.
///
/// ```rust
/// let listing = risc0_circuit_recursion::prove::zkr::get_all_zkrs().unwrap();
/// println!("{}", listing.into_iter().map(|(name, _)| name).collect::<Vec<_>>().join("\n"));
/// ```
pub fn get_all_zkrs() -> Result<Vec<(String, Vec<u32>)>> {
    sorted_names()
        .into_iter()
        .map(|(section, name)| Ok((name.into(), extract_zkr(section, name)?)))
        .collect()
}

/// The order matters: `cargo xtask bootstrap` builds the allowed control root
/// from [get_all_zkrs]. Sort to match the zip these zkrs used to ship in.
fn sorted_names() -> Vec<(ZkrSection, &'static str)> {
    let mut names: Vec<_> = [ZkrSection::Lift, ZkrSection::Control]
        .into_iter()
        .flat_map(|section| section.table().keys().map(move |&name| (section, name)))
        .collect();
    names.sort_by_key(|&(_, name)| name);
    names
}

/// The zkrs are split across two crates to stay under the crates.io size
/// limit: the lifts in one, everything else (join, resolve, etc.) in the other.
#[derive(Clone, Copy, Debug, PartialEq)]
enum ZkrSection {
    Lift,
    Control,
}

impl ZkrSection {
    fn for_name(name: &str) -> Self {
        if name.starts_with("lift_") {
            Self::Lift
        } else {
            Self::Control
        }
    }

    fn table(&self) -> &'static phf::Map<&'static str, (&'static [u8], usize)> {
        match self {
            Self::Lift => &risc0_circuit_recursion_zkrs::ZKRS,
            Self::Control => &risc0_circuit_recursion_control_zkrs::ZKRS,
        }
    }
}

fn extract_zkr(section: ZkrSection, name: &str) -> Result<Vec<u32>> {
    let &(xz_data, uncompressed_size) = section
        .table()
        .get(name)
        .ok_or_else(|| anyhow!("given zkr not found: {name}"))?;

    if !uncompressed_size.is_multiple_of(std::mem::size_of::<u32>()) {
        bail!(".zkr is incorrect size");
    }

    let mut decoder = liblzma::read::XzDecoder::new_parallel(xz_data);
    let mut u32s = vec![0u32; uncompressed_size / std::mem::size_of::<u32>()];
    decoder.read_exact(bytemuck::cast_slice_mut(&mut u32s))?;
    Ok(u32s)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn names_sorted_and_in_right_section() {
        let names = sorted_names();
        assert_eq!(names.len(), 32);
        assert!(names.is_sorted_by_key(|&(_, name)| name));
        for (section, name) in names {
            assert_eq!(section, ZkrSection::for_name(name), "{name}");
        }
    }

    #[test]
    fn get_zkr_from_each_section() {
        get_zkr("lift_rv32im_v2_14.zkr", 18).unwrap();
        get_zkr("test_recursion_circuit.zkr", 18).unwrap();
        assert!(get_zkr("missing.zkr", 18).is_err());
    }
}
