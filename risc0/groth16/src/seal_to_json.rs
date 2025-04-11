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

use std::io::{Read, Write};

use anyhow::{Context, Result};
use num_bigint::BigUint;
use num_traits::Num;
use risc0_core::field::baby_bear::BabyBearElem;
use risc0_zkp::core::{
    digest::{Digest, DIGEST_WORDS},
    hash::poseidon_254::digest_to_fr,
};

use crate::seal_format::{IopType, K_SEAL_ELEMS, K_SEAL_TYPES, K_SEAL_WORDS};

/// Convert a recursion VM seal (i.e. succinct receipt) into a JSON format compatible with the
/// `stark_verify` witness generator.
pub fn to_json<R: Read, W: Write>(mut reader: R, mut writer: W) -> Result<()> {
    let mut iop = vec![0u32; K_SEAL_WORDS];
    reader.read_exact(bytemuck::cast_slice_mut(&mut iop))?;

    writeln!(writer, "{{\n  \"iop\" : [")?;

    let mut pos = 0;
    for seal_type in K_SEAL_TYPES.iter().take(K_SEAL_ELEMS) {
        if pos != 0 {
            writeln!(writer, ",")?;
        }
        match seal_type {
            IopType::Fp => {
                let value = BabyBearElem::new_raw(iop[pos]).as_u32();
                pos += 1;
                writeln!(writer, "    \"{value}\"")?;
            }
            _ => {
                let digest = Digest::try_from(&iop[pos..pos + DIGEST_WORDS])?;
                let value = digest_to_decimal(&digest)?;
                pos += 8;
                writeln!(writer, "    \"{value}\"")?;
            }
        }
    }
    write!(writer, "  ]\n}}")?;

    Ok(())
}

fn digest_to_decimal(digest: &Digest) -> Result<String> {
    to_decimal(&format!("{:?}", digest_to_fr(digest))).context("digest_to_decimal failed")
}

fn to_decimal(s: &str) -> Result<String> {
    s.strip_prefix("Fr(0x")
        .and_then(|s| s.strip_suffix(')'))
        .ok_or_else(|| anyhow::anyhow!("Invalid string format"))?
        .parse::<BigUint>()
        .map(|n| n.to_str_radix(10))
        .map_err(|e| anyhow::anyhow!("Failed to convert BigUint: {}", e))
}
