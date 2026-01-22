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

use std::io::Read as _;

use anyhow::{Result, anyhow};

use super::Program;

pub fn get_zkr(name: &str, recursion_po2: usize) -> Result<Program> {
    let section = if name.contains("povw") {
        ZkrSection::LiftPovw
    } else {
        ZkrSection::Lift
    };
    let encoded = extract_zkr(section, name)?;
    Ok(Program::from_encoded(&encoded, recursion_po2))
}

/// Iterate over all provided zkr programs.
///
/// ```rust
/// let listing = risc0_circuit_recursion::prove::zkr::get_all_zkrs().unwrap();
/// println!("{}", listing.into_iter().map(|(name, _)| name).collect::<Vec<_>>().join("\n"));
/// ```
pub fn get_all_zkrs() -> Result<Vec<(String, Vec<u32>)>> {
    let regular_zrs = ZkrSection::Lift.table().keys().map(|&name| {
        let encoded = extract_zkr(ZkrSection::Lift, name)?;
        Ok((name.into(), encoded))
    });
    let povw_zkrs = ZkrSection::LiftPovw.table().keys().map(|&name| {
        let encoded = extract_zkr(ZkrSection::LiftPovw, name)?;
        Ok((name.into(), encoded))
    });
    regular_zrs.chain(povw_zkrs).collect()
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

fn extract_zkr(section: ZkrSection, name: &str) -> Result<Vec<u32>> {
    let &(xz_data, uncompressed_size) = section
        .table()
        .get(name)
        .ok_or_else(|| anyhow!("given zkr not found: {name}"))?;

    let mut decoder = liblzma::read::XzDecoder::new_parallel(xz_data);
    let mut u32s = vec![0u32; uncompressed_size / std::mem::size_of::<u32>()];
    decoder.read_exact(bytemuck::cast_slice_mut(&mut u32s))?;
    Ok(u32s)
}
