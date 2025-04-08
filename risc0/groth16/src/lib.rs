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

// TODO: Redo intro docs

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
use std::ops::Neg;

use anyhow::{anyhow, Error, Result};
use ark_serialize::CanonicalDeserialize;
use num_bigint::BigInt;
use risc0_zkp::core::digest::Digest;
use substrate_bn::Group;

mod data_structures;
#[cfg(feature = "prove")]
pub mod docker;
#[cfg(feature = "prove")]
mod seal_format;
#[cfg(feature = "prove")]
mod seal_to_json;
mod verifier;

pub use data_structures::{ProofJson, PublicInputsJson, Pvk, Seal, VerifyingKeyJson, Vk};
#[cfg(feature = "prove")]
pub use seal_to_json::to_json;
pub use verifier::{verifying_key, Fr, Verifier, VerifyingKey};

/// Splits the digest in half returning a scalar for each halve.
pub fn split_digest(d: Digest) -> Result<(substrate_bn::Fr, substrate_bn::Fr), Error> {
    let big_endian: Vec<u8> = d.as_bytes().to_vec().iter().rev().cloned().collect();
    let middle = big_endian.len() / 2;
    let (b, a) = big_endian.split_at(middle);
    Ok((
        substrate_bn::Fr::from_slice(&from_u256_hex(&hex::encode(a))?).map_err(|_|anyhow!("TODO"))?,
        substrate_bn::Fr::from_slice(&from_u256_hex(&hex::encode(b))?).map_err(|_|anyhow!("TODO"))?,
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

// TODO: Clean up or use something else directly
#[stability::unstable]
#[derive(Clone)]
struct LocalG1(Option<substrate_bn::AffineG1>);

impl LocalG1 {
    /// Deserialize an element over the G1 group from bytes in big-endian format
    #[stability::unstable]
    pub fn from_be_bytes(elem: &[Vec<u8>]) -> Result<Self, Error> {
        if elem.len() != 2 {
            return Err(anyhow!("Malformed G1 field element"));
        }
        // TODO: Better error forwarding
        let x = substrate_bn::Fq::from_slice(&elem[0]).map_err(|_|{anyhow!("TODO")})?;
        let y = substrate_bn::Fq::from_slice(&elem[1]).map_err(|_|{anyhow!("TODO")})?;
        // Note that AffineG1::new checks that the point is on the curve
        Ok(LocalG1(Some(substrate_bn::AffineG1::new(x, y).map_err(|_|{anyhow!("TODO")})?)))
    }
}

impl Neg for LocalG1 {
    type Output = Self;

    fn neg(self) -> Self::Output {
        LocalG1(match self.0 {
            None => None,
            // TODO: `new` re-does the "check point on curve" logic, which isn't actually needed here and can't fail
            Some(val) => Some(substrate_bn::AffineG1::new(val.x(), -val.y()).unwrap()),
        })
    }
}

// TODO: I'm a bit suspicious that these should just be `G1` the whole way through
impl From<LocalG1> for substrate_bn::G1 {
    fn from(item: LocalG1) -> Self {
        match item.0 {
            None => substrate_bn::G1::zero(),
            Some(val) => substrate_bn::G1::from(val),
        }
    }
}

// TODO: Clean up or use something else directly
#[derive(Clone)]
struct LocalG2(Option<substrate_bn::AffineG2>);

impl LocalG2 {
    /// Deserialize an element over the G2 group from bytes in big-endian format
    #[stability::unstable]
    pub fn from_be_bytes(elem: &[Vec<Vec<u8>>]) -> Result<Self, Error> {
        if elem.len() != 2 || elem[0].len() != 2 || elem[1].len() != 2 {
            return Err(anyhow!("Malformed G2 field element"));
        }
        // TODO: Am I right about which is real and which is imaginary?
        // TODO: Better error forwarding
        let x_re = substrate_bn::Fq::from_slice(&elem[0][1]).map_err(|_|{anyhow!("TODO")})?;
        let x_im = substrate_bn::Fq::from_slice(&elem[0][0]).map_err(|_|{anyhow!("TODO")})?;
        let x = substrate_bn::Fq2::new(x_re, x_im);
        let y_re = substrate_bn::Fq::from_slice(&elem[1][1]).map_err(|_|{anyhow!("TODO")})?;
        let y_im = substrate_bn::Fq::from_slice(&elem[1][0]).map_err(|_|{anyhow!("TODO")})?;
        let y = substrate_bn::Fq2::new(y_re, y_im);
        // Note that AffineG1::new checks that the point is on the curve and in the subgroup
        Ok(LocalG2(Some(substrate_bn::AffineG2::new(x, y).map_err(|_|{anyhow!("TODO")})?)))
    }
}

impl Neg for LocalG2 {
    type Output = Self;

    fn neg(self) -> Self::Output {
        LocalG2(match self.0 {
            None => None,
            // TODO: `new` re-does the "check point on curve & in subgroup" logic, which isn't actually needed here and can't fail
            Some(val) => Some(substrate_bn::AffineG2::new(val.x(), -val.y()).unwrap()),
        })
    }
}

// TODO: I'm a bit suspicious that these should just be `G2` the whole way through
impl From<LocalG2> for substrate_bn::G2 {
    fn from(item: LocalG2) -> Self {
        match item.0 {
            None => substrate_bn::G2::zero(),
            Some(val) => substrate_bn::G2::from(val),
        }
    }
}

/// Deserialize an element over the G1 group from bytes in big-endian format
#[stability::unstable]
pub fn g1_from_bytes(elem: &[Vec<u8>]) -> Result<LocalG1, Error> {
    LocalG1::from_be_bytes(elem)
}

/// Deserialize an element over the G2 group from bytes in big-endian format
#[stability::unstable]
pub fn g2_from_bytes(elem: &[Vec<Vec<u8>>]) -> Result<LocalG2, Error> {
    LocalG2::from_be_bytes(elem)
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
