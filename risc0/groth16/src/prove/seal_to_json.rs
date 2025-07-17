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

use std::fmt::Write;

use anyhow::{Context, Result};
use num_bigint::BigUint;
use num_traits::Num;
use risc0_core::field::baby_bear::BabyBearElem;
use risc0_zkp::core::{
    digest::{Digest, DIGEST_WORDS},
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
