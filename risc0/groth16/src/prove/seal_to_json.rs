// Copyright 2025 RISC Zero, Inc.
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

use std::fmt::Write;

use anyhow::{Context, Result};
use num_bigint::BigUint;
use num_traits::Num;
use risc0_core::field::baby_bear::BabyBearElem;
use risc0_zkp::core::{
    digest::{DIGEST_WORDS, Digest},
    hash::poseidon_254::digest_to_fr,
};

use super::seal_format::{IopType, K_SEAL_ELEMS, K_SEAL_TYPES, K_SEAL_WORDS};

/// Convert a recursion VM seal (i.e. succinct receipt) into a JSON format compatible with the
/// `stark_verify` witness generator.
pub fn to_json(seal_bytes: &[u8]) -> Result<String> {
    let mut json = String::new();

    let mut iop = vec![0u32; K_SEAL_WORDS];
    iop.copy_from_slice(bytemuck::cast_slice(seal_bytes));

    writeln!(json, "{{\n  \"iop\" : [")?;

    let mut pos = 0;
    for seal_type in K_SEAL_TYPES.iter().take(K_SEAL_ELEMS) {
        if pos != 0 {
            writeln!(json, ",")?;
        }
        match seal_type {
            IopType::Fp => {
                let value = BabyBearElem::new_raw(iop[pos]).as_u32();
                pos += 1;
                writeln!(json, "    \"{value}\"")?;
            }
            _ => {
                let digest = Digest::try_from(&iop[pos..pos + DIGEST_WORDS])?;
                let value = digest_to_decimal(&digest)?;
                pos += 8;
                writeln!(json, "    \"{value}\"")?;
            }
        }
    }
    write!(json, "  ]\n}}")?;

    Ok(json)
}

fn digest_to_decimal(digest: &Digest) -> Result<String> {
    to_decimal(&format!("{:?}", digest_to_fr(digest))).context("digest_to_decimal failed")
}

fn to_decimal(s: &str) -> Option<String> {
    s.strip_prefix("Fr(0x")
        .and_then(|s| s.strip_suffix(')'))
        .and_then(|stripped| BigUint::from_str_radix(stripped, 16).ok())
        .map(|n| n.to_str_radix(10))
}

#[cfg(feature = "blake3")]
/// TODO(ec2): comments
pub fn identity_seal_json_blake3(
    seal_bytes: impl AsRef<[u8]>,
    pre: impl Into<Digest>,
    post: impl Into<Digest>,
    control_id: impl Into<Digest>,
    control_root: impl Into<Digest>,
    journal_bytes: [u8; 32],
) -> Result<serde_json::Value> {
    let seal_json = to_json(seal_bytes.as_ref())?;
    let mut seal_json: serde_json::Value = serde_json::from_str(&seal_json)?;

    let mut journal_bits = Vec::new();
    for byte in journal_bytes {
        for i in 0..8 {
            journal_bits.push((byte >> (7 - i)) & 1);
        }
    }
    let pre_state_digest_bits: Vec<_> = pre
        .into()
        .as_bytes()
        .iter()
        .flat_map(|&byte| (0..8).rev().map(move |i| ((byte >> i) & 1).to_string()))
        .collect();

    let post_state_digest_bits: Vec<_> = post
        .into()
        .as_bytes()
        .iter()
        .flat_map(|&byte| (0..8).rev().map(move |i| ((byte >> i) & 1).to_string()))
        .collect();

    let mut id_bn254_fr_bits: Vec<String> = control_id
        .into()
        .as_bytes()
        .iter()
        .flat_map(|&byte| (0..8).rev().map(move |i| ((byte >> i) & 1).to_string()))
        .collect();
    // remove 248th and 249th bits
    id_bn254_fr_bits.remove(248);
    id_bn254_fr_bits.remove(248);

    // let mut succinct_control_root_bytes: [u8; 32] =
    //     risc0_zkvm::SuccinctReceiptVerifierParameters::default()
    //         .control_root
    //         .as_bytes()
    //         .try_into()?;
    let mut succinct_control_root_bytes: [u8; 32] = control_root
        .into()
        .as_bytes()
        .try_into()
        .context("control_root conversion failed")?;

    succinct_control_root_bytes.reverse();
    let succinct_control_root_hex = hex::encode(succinct_control_root_bytes);

    let a1_str = succinct_control_root_hex[0..32].to_string();
    let a0_str = succinct_control_root_hex[32..64].to_string();
    let a0_dec = BigUint::from_str_radix(&a0_str, 16)
        .ok()
        .context("a0_str returned None")
        .map(|n| n.to_str_radix(10))?;
    let a1_dec = BigUint::from_str_radix(&a1_str, 16)
        .ok()
        .context("a1_str returned None")
        .map(|n| n.to_str_radix(10))?;

    let control_root = vec![a0_dec, a1_dec];

    seal_json["journal_digest_bits"] = journal_bits.into();
    seal_json["pre_state_digest_bits"] = pre_state_digest_bits.into();
    seal_json["post_state_digest_bits"] = post_state_digest_bits.into();
    seal_json["id_bn254_fr_bits"] = id_bn254_fr_bits.into();
    seal_json["control_root"] = control_root.into();

    Ok(seal_json)
}
