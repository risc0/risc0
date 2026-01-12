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

use anyhow::{Result, bail};
use liblzma::read::XzDecoder;
use risc0_circuit_recursion::prove::Program;

use crate::{KECCAK_PO2_RANGE, RECURSION_PO2};

include!(concat!(env!("OUT_DIR"), "/zkr_table.rs"));

pub fn get_keccak_zkr(po2: usize) -> Result<Program> {
    let idx = po2 - KECCAK_PO2_RANGE.min().unwrap();
    let (xz_bytes, uncompressed_size) = ZKRS[idx];

    if uncompressed_size % std::mem::size_of::<u32>() != 0 {
        bail!(".zkr is incorrect size");
    }

    let mut decoder = XzDecoder::new(xz_bytes);
    let mut u32s = vec![0u32; uncompressed_size / std::mem::size_of::<u32>()];
    decoder.read_exact(bytemuck::cast_slice_mut(&mut u32s))?;
    Ok(Program::from_encoded(&u32s, RECURSION_PO2))
}
