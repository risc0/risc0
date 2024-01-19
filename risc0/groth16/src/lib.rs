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

//! Core module used to implement Groth16.

use core::str::FromStr;

use anyhow::{anyhow, bail, Error, Result};
use ark_bn254::{Fr, G1Affine, G2Affine};
use ark_serialize::CanonicalDeserialize;
use num_bigint::BigInt;
use risc0_zkp::core::digest::Digest;

pub mod data_structures;
#[cfg(feature = "prove")]
mod seal_format;
#[cfg(feature = "prove")]
mod seal_to_json;
pub mod verifier;

pub use data_structures::{ProofJson, PublicInputsJson, Seal, VerifyingKeyJson};
#[cfg(feature = "prove")]
pub use seal_to_json::to_json;
pub use verifier::Verifier;

// Deserialize a scalar field from bytes in big-endian format
pub(crate) fn fr_from_bytes(scalar: &Vec<u8>) -> Result<Fr, Error> {
    let scalar: Vec<u8> = scalar.iter().rev().cloned().collect();
    Ok(Fr::deserialize_uncompressed(&*scalar).map_err(|err| anyhow!(err))?)
}

// Deserialize an element over the G1 group from bytes in big-endian format
pub(crate) fn g1_from_bytes(elem: &[Vec<u8>]) -> Result<G1Affine, Error> {
    if elem.len() != 2 {
        bail!("Malformed G1 field element");
    }
    let g1_affine: Vec<u8> = elem[0]
        .iter()
        .rev()
        .chain(elem[1].iter().rev())
        .cloned()
        .collect();

    Ok(G1Affine::deserialize_uncompressed(&*g1_affine).map_err(|err| anyhow!(err))?)
}

// Deserialize an element over the G2 group from bytes in big-endian format
pub(crate) fn g2_from_bytes(elem: &Vec<Vec<Vec<u8>>>) -> Result<G2Affine, Error> {
    if elem.len() != 2 || elem[0].len() != 2 || elem[1].len() != 2 {
        bail!("Malformed G2 field element");
    }
    let g2_affine: Vec<u8> = elem[0][1]
        .iter()
        .rev()
        .chain(elem[0][0].iter().rev())
        .chain(elem[1][1].iter().rev())
        .chain(elem[1][0].iter().rev())
        .cloned()
        .collect();

    Ok(G2Affine::deserialize_uncompressed(&*g2_affine).map_err(|err| anyhow!(err))?)
}

// Convert the U256 value to a byte array in big-endian format
pub(crate) fn from_u256(value: &str) -> Result<Vec<u8>, Error> {
    let value = if value.starts_with("0x") {
        to_fixed_array(
            hex::decode(&value[2..]).map_err(|_| anyhow!("conversion from u256 failed"))?,
        )
        .to_vec()
    } else {
        to_fixed_array(
            BigInt::from_str(value)
                .map_err(|_| anyhow!("conversion from u256 failed"))?
                .to_bytes_be()
                .1,
        )
        .to_vec()
    };
    Ok(value)
}

fn to_fixed_array(input: Vec<u8>) -> [u8; 32] {
    let mut fixed_array = [0u8; 32];
    let start = core::cmp::max(32, input.len()) - core::cmp::min(32, input.len());
    fixed_array[start..].copy_from_slice(&input[input.len().saturating_sub(32)..]);
    fixed_array
}

/// Splits the digest in half returning a scalar for each halve.
pub fn split_digest(d: Digest) -> Result<(Fr, Fr), Error> {
    let big_endian: Vec<u8> = d.as_bytes().to_vec().iter().rev().cloned().collect();
    let middle = big_endian.len() / 2;
    let (b, a) = big_endian.split_at(middle);
    Ok((
        fr_from_bytes(&from_u256(&format!("0x{}", hex::encode(a)))?)?,
        fr_from_bytes(&from_u256(&format!("0x{}", hex::encode(b)))?)?,
    ))
}
