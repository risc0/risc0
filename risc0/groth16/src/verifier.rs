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

extern crate alloc;

use alloc::{vec, vec::Vec};

use anyhow::{anyhow, Error, Result};
use ark_bn254::{Bn254, G1Projective};
use ark_ec::AffineRepr;
use ark_groth16::{Groth16, PreparedVerifyingKey, Proof};
use ark_serialize::{CanonicalDeserialize, CanonicalSerialize};
use risc0_binfmt::{tagged_iter, tagged_struct, Digestible};
use risc0_zkp::core::{digest::Digest, hash::sha::Sha256};
use serde::{Deserialize, Serialize};

use crate::{
    from_u256, from_u256_hex, g1_from_bytes, g2_from_bytes, ProofJson, PublicInputsJson, Seal,
    VerifyingKeyJson,
};

// Constants from: risc0-ethereum/contracts/src/groth16/Groth16Verifier.sol
// When running a new ceremony, update them by running cargo xtask bootstrap-groth16
// after updating the new Groth16Verifier.sol on the risc0-ethereum repo.
const ALPHA_X: &str =
    "16428432848801857252194528405604668803277877773566238944394625302971855135431";
const ALPHA_Y: &str =
    "16846502678714586896801519656441059708016666274385668027902869494772365009666";
const BETA_X1: &str =
    "3182164110458002340215786955198810119980427837186618912744689678939861918171";
const BETA_X2: &str =
    "16348171800823588416173124589066524623406261996681292662100840445103873053252";
const BETA_Y1: &str =
    "4920802715848186258981584729175884379674325733638798907835771393452862684714";
const BETA_Y2: &str =
    "19687132236965066906216944365591810874384658708175106803089633851114028275753";
const GAMMA_X1: &str =
    "11559732032986387107991004021392285783925812861821192530917403151452391805634";
const GAMMA_X2: &str =
    "10857046999023057135944570762232829481370756359578518086990519993285655852781";
const GAMMA_Y1: &str =
    "4082367875863433681332203403145435568316851327593401208105741076214120093531";
const GAMMA_Y2: &str =
    "8495653923123431417604973247489272438418190587263600148770280649306958101930";
const DELTA_X1: &str =
    "13685059722572430118879685427946391979901136567998183708779569511490189317001";
const DELTA_X2: &str =
    "885466262627004802590867456739578300677915885086603763598705832963512086505";
const DELTA_Y1: &str =
    "8933121941496894014853887359369032186410688475735000080433413130611683087240";
const DELTA_Y2: &str =
    "10807343278331592741981940444887734276273932203693990777507350667309517636319";

const IC0_X: &str = "6821737526841934241272766898616788768501455291896697498051714590367778942840";
const IC0_Y: &str = "4698850673305122375961716162174983535198844999933178163759288415424083470587";
const IC1_X: &str = "16228843417386597614819478366286421997949075406332603279696832781620859664082";
const IC1_Y: &str = "17664127035017167525612282755946999798260932200793445674879102286542605097098";
const IC2_X: &str = "14324205345033861380043442611976565168611172366095343547065887177170176653323";
const IC2_Y: &str = "5406762165323503454505992867123895235515984438494446094150097263332194389438";
const IC3_X: &str = "321894424338075502915267091467125347576281575097392421739606708442584022200";
const IC3_Y: &str = "7463411692929197697144511611813579535812927110717862827111739583446994788026";
const IC4_X: &str = "17102793626148543892721316443277712948753865223157395620053241691940994746878";
const IC4_Y: &str = "21287072888423362820334250698073807712055690599308394352313545747547734584776";
const IC5_X: &str = "11136065033585885873464917479258656136369388570108290410378993085304721761858";
const IC5_Y: &str = "7984772638125791248037780093288646636176119708747433579442394619155523753874";

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

/// Verifying key for Groth16 proofs.
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
        de::Error as _, ser::Error as _, Deserialize, Deserializer, Serialize, Serializer,
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

/// Default verifying key for RISC Zero recursive verification.
pub fn verifying_key() -> VerifyingKey {
    try_verifying_key().unwrap()
}

// try_verifying_key executes entirely over const data and so should never error.
fn try_verifying_key() -> Result<VerifyingKey, Error> {
    let alpha_g1 = g1_from_bytes(&[from_u256(ALPHA_X)?, from_u256(ALPHA_Y)?])?;
    let beta_g2 = g2_from_bytes(&[
        vec![from_u256(BETA_X1)?, from_u256(BETA_X2)?],
        vec![from_u256(BETA_Y1)?, from_u256(BETA_Y2)?],
    ])?;
    let gamma_g2 = g2_from_bytes(&[
        vec![from_u256(GAMMA_X1)?, from_u256(GAMMA_X2)?],
        vec![from_u256(GAMMA_Y1)?, from_u256(GAMMA_Y2)?],
    ])?;
    let delta_g2 = g2_from_bytes(&[
        vec![from_u256(DELTA_X1)?, from_u256(DELTA_X2)?],
        vec![from_u256(DELTA_Y1)?, from_u256(DELTA_Y2)?],
    ])?;

    let ic0 = g1_from_bytes(&[from_u256(IC0_X)?, from_u256(IC0_Y)?])?;
    let ic1 = g1_from_bytes(&[from_u256(IC1_X)?, from_u256(IC1_Y)?])?;
    let ic2 = g1_from_bytes(&[from_u256(IC2_X)?, from_u256(IC2_Y)?])?;
    let ic3 = g1_from_bytes(&[from_u256(IC3_X)?, from_u256(IC3_Y)?])?;
    let ic4 = g1_from_bytes(&[from_u256(IC4_X)?, from_u256(IC4_Y)?])?;
    let ic5 = g1_from_bytes(&[from_u256(IC5_X)?, from_u256(IC5_Y)?])?;
    let gamma_abc_g1 = vec![ic0, ic1, ic2, ic3, ic4, ic5];

    Ok(VerifyingKey(ark_groth16::VerifyingKey::<Bn254> {
        alpha_g1,
        beta_g2,
        gamma_g2,
        delta_g2,
        gamma_abc_g1,
    }))
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
