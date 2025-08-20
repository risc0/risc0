// Copyright 2025 RISC Zero, Inc.
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
//! ## Shrink Wrap (aka STARK to SNARK)
//!
//! It also provides the [shrink_wrap][prove::shrink_wrap] function to run a prover Groth16
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
//!
//! # Publishing the rzup Component
//! The groth16 proving on GPU requires a special rzup component be installed. Publishing this
//! component can be done with the following commands:
//!
//! ```bash
//! export VERSION=0.1.0
//! cargo xtask-groth16 -- ~/groth16-tmp
//! cargo run --bin rzup -- \
//!     publish create-artifact \
//!     --input ~/groth16-tmp/v$VERSION-risc0-groth16 \
//!     --output ~/groth16-component.tar.xz
//! aws-vault exec ci -- \
//! cargo run --bin rzup -- \
//!     publish upload \
//!     --target-agnostic \
//!     risc0-groth16 $VERSION \
//!     ~/groth16-component.tar.xz
//! ```

#![cfg_attr(not(feature = "std"), no_std)]
#![deny(missing_docs)]
#![deny(rustdoc::broken_intra_doc_links)]
#![cfg_attr(docsrs, feature(doc_cfg, doc_auto_cfg))]

extern crate alloc;

#[cfg(feature = "prove")]
pub mod prove;
mod types;
mod verifier;

use alloc::vec::Vec;
use core::str::FromStr;

use anyhow::{anyhow, Error, Result};
use ark_bn254::{G1Affine, G2Affine};
use ark_serialize::CanonicalDeserialize;
use num_bigint::BigInt;

pub use types::{ProofJson, PublicInputsJson, Seal, VerifyingKeyJson};
pub use verifier::{verifying_key, Fr, Verifier, VerifyingKey};

/// Deserialize an element over the G1 group from bytes in big-endian format
pub(crate) fn g1_from_bytes(elem: &[Vec<u8>]) -> Result<G1Affine, Error> {
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
pub(crate) fn g2_from_bytes(elem: &[Vec<Vec<u8>>]) -> Result<G2Affine, Error> {
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
pub(crate) fn from_u256_hex(value: &str) -> Result<Vec<u8>, Error> {
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
