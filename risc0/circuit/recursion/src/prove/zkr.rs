// Copyright 2026 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use std::io::{Cursor, Read as _};

use anyhow::{Context as _, Result, anyhow, bail};

use super::Program;

const ZKR_ZIP: &[u8] = include_bytes!(concat!(env!("OUT_DIR"), "/recursion_zkr.zip"));

pub fn get_zkr(name: &str, po2: usize) -> Result<Program> {
    let mut zip = zip::ZipArchive::new(Cursor::new(ZKR_ZIP))?;
    let encoded = extract_zkr(&mut zip, name)?;
    Ok(Program::from_encoded(&encoded, po2))
}

pub fn get_zkr_m3(name: &str, po2: usize, recursion_po2: usize) -> Result<Program> {
    let encoded = if name.contains("rv32im_m3") {
        let section = if name.contains("povw") {
            ZkrSection::LiftPovw
        } else {
            ZkrSection::Lift
        };
        extract_zkr_m3(section, po2, name)?
    } else {
        let mut zip = zip::ZipArchive::new(Cursor::new(ZKR_ZIP))?;
        extract_zkr(&mut zip, name)?
    };
    Ok(Program::from_encoded(&encoded, recursion_po2))
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
        .chain(crate::LIFT_PO2_RANGE.map(|po2| {
            let name = format!("lift_rv32im_m3_{po2}.zkr");
            let encoded = extract_zkr_m3(ZkrSection::Lift, po2, &name)?;
            Ok((name, encoded))
        }))
        .chain(crate::LIFT_PO2_RANGE.map(|po2| {
            let name = format!("lift_rv32im_m3_povw_{po2}.zkr");
            let encoded = extract_zkr_m3(ZkrSection::LiftPovw, po2, &name)?;
            Ok((name, encoded))
        }))
        .collect()
}

enum ZkrSection {
    Lift,
    LiftPovw,
}

impl ZkrSection {
    fn table(&self) -> &phf::Map<&'static str, (&'static [u8], usize)> {
        use risc0_circuit_recursion_povw_zkrs::ZKRS as POVW_ZKRS;
        use risc0_circuit_recursion_zkrs::ZKRS;

        match self {
            Self::Lift => &ZKRS,
            Self::LiftPovw => &POVW_ZKRS,
        }
    }
}

fn extract_zkr_m3(section: ZkrSection, _po2: usize, name: &str) -> Result<Vec<u32>> {
    let &(xz_data, uncompressed_size) = section
        .table()
        .get(name)
        .ok_or_else(|| anyhow!("given zkr not found: {name}"))?;

    let mut decoder = liblzma::read::XzDecoder::new_parallel(xz_data);
    let mut u32s = vec![0u32; uncompressed_size / std::mem::size_of::<u32>()];
    decoder.read_exact(bytemuck::cast_slice_mut(&mut u32s))?;
    return Ok(u32s);
}

fn extract_zkr(zip: &mut zip::ZipArchive<Cursor<&[u8]>>, name: &str) -> Result<Vec<u32>> {
    let mut f = zip
        .by_name(name)
        .with_context(|| format!("Failed to read {name}"))?;
    let uncompressed_size = f.size() as usize;

    if !uncompressed_size.is_multiple_of(std::mem::size_of::<u32>()) {
        bail!(".zkr is incorrect size");
    }

    let mut u32s = vec![0u32; uncompressed_size / std::mem::size_of::<u32>()];
    f.read_exact(bytemuck::cast_slice_mut(&mut u32s[..]))?;

    Ok(u32s)
}
