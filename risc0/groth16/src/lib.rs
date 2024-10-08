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

//! # Groth16
//!
//! This library implements a verifier for the Groth16 protocol over the BN_254 elliptic curve.
//!
//! ## Example
//!
//! ```rust
//! use risc0_groth16::{ProofJson, PublicInputsJson, Verifier, VerifyingKeyJson};
//!
//! # macro_rules! test_data {
//! #    ($s:expr) => {
//! #        include_str!(concat!("../tests/data/", $s))
//! #    };
//! # }
//! #
//! const TEST_VERIFICATION_KEY: &str = test_data!("verification_key.json");
//! const TEST_PROOF: &str = test_data!("proof.json");
//! const TEST_PUBLIC_INPUTS: &str = test_data!("public.json");
//!
//! fn verify() {
//!     let verifying_key: VerifyingKeyJson = serde_json::from_str(TEST_VERIFICATION_KEY).unwrap();
//!     let proof: ProofJson = serde_json::from_str(TEST_PROOF).unwrap();
//!     let public_inputs = PublicInputsJson {
//!         values: serde_json::from_str(TEST_PUBLIC_INPUTS).unwrap(),
//!     };
//!     let verifier = Verifier::from_json(proof, public_inputs, verifying_key).unwrap();
//!     verifier.verify().unwrap();
//! }
//! ```
//!
//! ## STARK to SNARK
//!
//! It also provides the [stark_to_snark][docker::stark_to_snark] function to run a prover Groth16
//! recursion prover via Docker. After generating a RISC Zero STARK proof, this function can be
//! used to transform it into a Groth16 proof. This function becomes available when the `prove`
//! feature flag is enabled.
//!
//! > IMPORTANT: This feature requires an x86 architecture and Docker installed.
//! > Additionally, specific [installation steps](https://github.com/risc0/risc0/tree/main/groth16_proof) must be followed to use this functionality.
//!
//! The recommended way to get a Groth16 proof is to use the `Prover` trait in the [risc0-zkvm]
//! crate. With `ProverOpts::groth16()` it will produce a Groth16 proof.
//!
//! [risc0-zkvm]: https://docs.rs/risc0-zkvm/latest/risc0_zkvm/

#![cfg_attr(not(feature = "std"), no_std)]
#![deny(missing_docs)]
#![deny(rustdoc::broken_intra_doc_links)]
#![cfg_attr(docsrs, feature(doc_cfg, doc_auto_cfg))]

extern crate alloc;

use alloc::vec::Vec;
use core::str::FromStr;

use anyhow::{anyhow, Error, Result};
use ark_bn254::{G1Affine, G2Affine};
use ark_serialize::CanonicalDeserialize;
use num_bigint::BigInt;
use risc0_zkp::core::digest::Digest;

mod data_structures;
#[cfg(feature = "prove")]
pub mod docker;
#[cfg(feature = "prove")]
mod seal_format;
#[cfg(feature = "prove")]
mod seal_to_json;
mod verifier;

pub use data_structures::{ProofJson, PublicInputsJson, Seal, VerifyingKeyJson};
#[cfg(feature = "prove")]
pub use seal_to_json::to_json;
pub use verifier::{verifying_key, Fr, Verifier, VerifyingKey};

/// Splits the digest in half returning a scalar for each halve.
pub fn split_digest(d: Digest) -> Result<(Fr, Fr), Error> {
    let big_endian: Vec<u8> = d.as_bytes().to_vec().iter().rev().cloned().collect();
    let middle = big_endian.len() / 2;
    let (b, a) = big_endian.split_at(middle);
    Ok((
        fr_from_bytes(&from_u256_hex(&hex::encode(a))?)?,
        fr_from_bytes(&from_u256_hex(&hex::encode(b))?)?,
    ))
}

/// Creates an [Fr] from a hex string
pub fn fr_from_hex_string(val: &str) -> Result<Fr, Error> {
    fr_from_bytes(&from_u256_hex(val)?)
}

// Deserialize a scalar field from bytes in big-endian format
pub(crate) fn fr_from_bytes(scalar: &[u8]) -> Result<Fr, Error> {
    let scalar: Vec<u8> = scalar.iter().rev().cloned().collect();
    ark_bn254::Fr::deserialize_uncompressed(&*scalar)
        .map(Fr)
        .map_err(|err| anyhow!(err))
}

/// Deserialize an element over the G1 group from bytes in big-endian format
#[stability::unstable]
pub fn g1_from_bytes(elem: &[Vec<u8>]) -> Result<G1Affine, Error> {
    if elem.len() != 2 {
        return Err(anyhow!("Malformed G1 field element"));
    }
    let g1_affine: Vec<u8> = elem[0]
        .iter()
        .rev()
        .chain(elem[1].iter().rev())
        .cloned()
        .collect();

    G1Affine::deserialize_uncompressed(&*g1_affine).map_err(|err| anyhow!(err))
}

/// Deserialize an element over the G2 group from bytes in big-endian format
#[stability::unstable]
pub fn g2_from_bytes(elem: &[Vec<Vec<u8>>]) -> Result<G2Affine, Error> {
    if elem.len() != 2 || elem[0].len() != 2 || elem[1].len() != 2 {
        return Err(anyhow!("Malformed G2 field element"));
    }
    let g2_affine: Vec<u8> = elem[0][1]
        .iter()
        .rev()
        .chain(elem[0][0].iter().rev())
        .chain(elem[1][1].iter().rev())
        .chain(elem[1][0].iter().rev())
        .cloned()
        .collect();

    G2Affine::deserialize_uncompressed(&*g2_affine).map_err(|err| anyhow!(err))
}

// Convert the U256 value to a byte array in big-endian format
pub(crate) fn from_u256(value: &str) -> Result<Vec<u8>, Error> {
    if let Some(stripped) = value.strip_prefix("0x") {
        from_u256_hex(stripped)
    } else {
        Ok(to_fixed_array(
            BigInt::from_str(value)
                .map_err(|_| anyhow!("conversion from u256 failed"))?
                .to_bytes_be()
                .1,
        )
        .to_vec())
    }
}

// Convert the U256 value to a byte array in big-endian format
fn from_u256_hex(value: &str) -> Result<Vec<u8>, Error> {
    Ok(
        to_fixed_array(hex::decode(value).map_err(|_| anyhow!("conversion from u256 failed"))?)
            .to_vec(),
    )
}

fn to_fixed_array(input: Vec<u8>) -> [u8; 32] {
    let mut fixed_array = [0u8; 32];
    let start = core::cmp::max(32, input.len()) - core::cmp::min(32, input.len());
    fixed_array[start..].copy_from_slice(&input[input.len().saturating_sub(32)..]);
    fixed_array
}
