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

extern crate alloc;

use alloc::vec::Vec;

use anyhow::{Error, Result, anyhow};
use ark_bn254::{Bn254, G1Projective};
use ark_ec::AffineRepr;
use ark_groth16::{Groth16, PreparedVerifyingKey, Proof};
use ark_serialize::{CanonicalDeserialize, CanonicalSerialize};
use risc0_binfmt::{Digestible, tagged_iter, tagged_struct};
use risc0_zkp::core::{digest::Digest, hash::sha::Sha256};
use serde::{Deserialize, Serialize};

use crate::{
    ProofJson, PublicInputsJson, Seal, VerifyingKeyJson, from_u256_hex, g1_from_bytes,
    g2_from_bytes,
};

pub(crate) mod risc0;

#[cfg(feature = "blake3")]
pub(crate) mod blake3;

/// Groth16 `Verifier` instance over the BN_254 curve encoded in little endian.
#[derive(Clone, Debug, Deserialize, Serialize)]
pub struct Verifier {
    /// prepared verifying key little endian encoded.
    encoded_pvk: Vec<u8>,

    /// proof little endian encoded.
    encoded_proof: Vec<u8>,

    /// prepared public inputs little endian encoded.
    encoded_prepared_inputs: Vec<u8>,
}

impl Verifier {
    /// Creates a new Groth16 `Verifier` instance.
    pub fn new(
        seal: &[u8],
        control_root: Digest,
        claim_digest: Digest,
        mut bn254_control_id: Digest,
        verifying_key: &VerifyingKey,
    ) -> Result<Self, Error> {
        let seal = Seal::decode(seal)?;

        let (a0, a1) = split_digest(control_root)?;
        let (c0, c1) = split_digest(claim_digest)?;
        bn254_control_id.as_mut_bytes().reverse();
        let id_bn254_fr = fr_from_hex_string(&hex::encode(bn254_control_id))?;

        Self::new_inner(&seal, &[a0, a1, c0, c1, id_bn254_fr], verifying_key)
    }

    pub(crate) fn new_inner(
        seal: &Seal,
        public_inputs: &[Fr],
        verifying_key: &VerifyingKey,
    ) -> Result<Self, Error> {
        let pvk = ark_groth16::prepare_verifying_key(&verifying_key.0);
        let mut encoded_pvk = Vec::new();
        pvk.serialize_uncompressed(&mut encoded_pvk)
            .map_err(|err| anyhow!(err))?;

        let mut encoded_proof = Vec::new();
        let proof = Proof::<Bn254> {
            a: g1_from_bytes(&seal.a)?,
            b: g2_from_bytes(&seal.b)?,
            c: g1_from_bytes(&seal.c)?,
        };
        proof
            .serialize_uncompressed(&mut encoded_proof)
            .map_err(|err| anyhow!(err))?;

        let mut encoded_prepared_inputs = Vec::new();
        let prepared_inputs = Groth16::<Bn254>::prepare_inputs(
            &pvk,
            &public_inputs.iter().map(|x| x.0).collect::<Vec<_>>(),
        )
        .map_err(|err| anyhow!(err))?;
        prepared_inputs
            .serialize_uncompressed(&mut encoded_prepared_inputs)
            .map_err(|err| anyhow!(err))?;

        Ok(Self {
            encoded_pvk,
            encoded_proof,
            encoded_prepared_inputs,
        })
    }

    /// Create a Verifier given the JSON representation of the proof, public inputs and verifier
    /// key.
    pub fn from_json(
        proof: ProofJson,
        public_inputs: PublicInputsJson,
        verifying_key: VerifyingKeyJson,
    ) -> Result<Self> {
        Verifier::new_inner(
            &proof.try_into()?,
            &public_inputs.to_scalar()?,
            &verifying_key.verifying_key()?,
        )
    }

    /// Verifies the Groth16 proof.
    pub fn verify(&self) -> Result<(), Error> {
        let pvk = &PreparedVerifyingKey::deserialize_uncompressed(&*self.encoded_pvk)
            .map_err(|err| anyhow!(err))?;
        let proof =
            &Proof::deserialize_uncompressed(&*self.encoded_proof).map_err(|err| anyhow!(err))?;
        let prepared_inputs =
            &G1Projective::deserialize_uncompressed(self.encoded_prepared_inputs.as_slice())
                .map_err(|err| anyhow!(err))?;
        match Groth16::<Bn254>::verify_proof_with_prepared_inputs(pvk, proof, prepared_inputs)
            .map_err(|err| anyhow!(err))?
        {
            true => Ok(()),
            false => Err(anyhow!("Invalid proof")),
        }
    }
}

/// Scalar field element over BN254 used for public inputs and hashing.
#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct Fr(#[serde(with = "serde_ark")] pub(crate) ark_bn254::Fr);

impl Digestible for Fr {
    /// Compute a tagged hash of the [Fr] value.
    fn digest<S: Sha256>(&self) -> Digest {
        let mut buffer = Vec::<u8>::with_capacity(32);
        // Serialization into a pre-allocated buffer should never fail.
        self.0.serialize_uncompressed(&mut buffer).unwrap();
        // Convert to big-endian representation.
        buffer.reverse();
        tagged_struct::<S>(
            "risc0_groth16.Fr",
            &[bytemuck::pod_read_unaligned::<Digest>(&buffer)],
            &[],
        )
    }
}

/// Verifying key for Groth16 proofs.
#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct VerifyingKey(#[serde(with = "serde_ark")] pub(crate) ark_groth16::VerifyingKey<Bn254>);

/// Hash a point on G1 or G2 by hashing the concatenated big-endian representation of (x, y).
fn hash_point<S: Sha256>(p: impl AffineRepr) -> Digest {
    let mut buffer = Vec::<u8>::new();
    // If p is the point at infinity, the verifying key is invalid. Panic.
    let (x, y) = p.xy().unwrap();
    y.serialize_uncompressed(&mut buffer).unwrap();
    x.serialize_uncompressed(&mut buffer).unwrap();
    buffer.reverse();
    *S::hash_bytes(&buffer)
}

impl Digestible for VerifyingKey {
    /// Hash the [VerifyingKey] to get a struct digest.
    fn digest<S: Sha256>(&self) -> Digest {
        tagged_struct::<S>(
            "risc0_groth16.VerifyingKey",
            &[
                hash_point::<S>(self.0.alpha_g1),
                hash_point::<S>(self.0.beta_g2),
                hash_point::<S>(self.0.gamma_g2),
                hash_point::<S>(self.0.delta_g2),
                tagged_iter::<S>(
                    "risc0_groth16.VerifyingKey.IC",
                    self.0.gamma_abc_g1.iter().map(|p| hash_point::<S>(*p)),
                ),
            ],
            &[],
        )
    }
}

/// Compatibility module providing simple serde interop
mod serde_ark {
    use alloc::vec::Vec;

    use ark_serialize::{CanonicalDeserialize, CanonicalSerialize};
    use serde::{
        Deserialize, Deserializer, Serialize, Serializer, de::Error as _, ser::Error as _,
    };

    pub fn serialize<S>(key: &impl CanonicalSerialize, serializer: S) -> Result<S::Ok, S::Error>
    where
        S: Serializer,
    {
        let mut buffer = Vec::<u8>::new();
        key.serialize_uncompressed(&mut buffer)
            .map_err(S::Error::custom)?;
        buffer.serialize(serializer)
    }

    pub fn deserialize<'de, D, T>(deserializer: D) -> Result<T, D::Error>
    where
        D: Deserializer<'de>,
        T: CanonicalDeserialize,
    {
        let buffer = Vec::<u8>::deserialize(deserializer)?;
        T::deserialize_uncompressed(buffer.as_slice()).map_err(D::Error::custom)
    }
}

/// Splits the digest in half returning a scalar for each halve.
fn split_digest(d: Digest) -> Result<(Fr, Fr), Error> {
    let big_endian: Vec<u8> = d.as_bytes().to_vec().iter().rev().cloned().collect();
    let middle = big_endian.len() / 2;
    let (b, a) = big_endian.split_at(middle);
    Ok((
        fr_from_bytes(&from_u256_hex(&hex::encode(a))?)?,
        fr_from_bytes(&from_u256_hex(&hex::encode(b))?)?,
    ))
}

/// Creates an [Fr] from a hex string
fn fr_from_hex_string(val: &str) -> Result<Fr, Error> {
    fr_from_bytes(&from_u256_hex(val)?)
}

// Deserialize a scalar field from bytes in big-endian format
fn fr_from_bytes(scalar: &[u8]) -> Result<Fr, Error> {
    let scalar: Vec<u8> = scalar.iter().rev().cloned().collect();
    ark_bn254::Fr::deserialize_uncompressed(&*scalar)
        .map(Fr)
        .map_err(|err| anyhow!(err))
}
