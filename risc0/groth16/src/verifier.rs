// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

extern crate alloc;

use alloc::{vec, vec::Vec};

use anyhow::{Error, Result, anyhow};
use ark_bn254::{Bn254, G1Projective};
use ark_ec::AffineRepr;
use ark_groth16::{Groth16, PreparedVerifyingKey, Proof};
use ark_serialize::{CanonicalDeserialize, CanonicalSerialize};
use risc0_binfmt::{Digestible, tagged_iter, tagged_struct};
use risc0_zkp::core::{digest::Digest, hash::sha::Sha256};
use serde::{Deserialize, Serialize};

use crate::{
    ProofJson, PublicInputsJson, Seal, VerifyingKeyJson, from_u256, from_u256_hex, g1_from_bytes,
    g2_from_bytes,
};

// Constants from: risc0-ethereum/contracts/src/groth16/Groth16Verifier.sol
// When running a new ceremony, update them by running cargo xtask bootstrap-groth16
// after updating the new Groth16Verifier.sol on the risc0-ethereum repo.
const ALPHA_X: &str =
    "20491192805390485299153009773594534940189261866228447918068658471970481763042";
const ALPHA_Y: &str =
    "9383485363053290200918347156157836566562967994039712273449902621266178545958";
const BETA_X1: &str =
    "4252822878758300859123897981450591353533073413197771768651442665752259397132";
const BETA_X2: &str =
    "6375614351688725206403948262868962793625744043794305715222011528459656738731";
const BETA_Y1: &str =
    "21847035105528745403288232691147584728191162732299865338377159692350059136679";
const BETA_Y2: &str =
    "10505242626370262277552901082094356697409835680220590971873171140371331206856";
const GAMMA_X1: &str =
    "11559732032986387107991004021392285783925812861821192530917403151452391805634";
const GAMMA_X2: &str =
    "10857046999023057135944570762232829481370756359578518086990519993285655852781";
const GAMMA_Y1: &str =
    "4082367875863433681332203403145435568316851327593401208105741076214120093531";
const GAMMA_Y2: &str =
    "8495653923123431417604973247489272438418190587263600148770280649306958101930";
const DELTA_X1: &str =
    "1668323501672964604911431804142266013250380587483576094566949227275849579036";
const DELTA_X2: &str =
    "12043754404802191763554326994664886008979042643626290185762540825416902247219";
const DELTA_Y1: &str =
    "7710631539206257456743780535472368339139328733484942210876916214502466455394";
const DELTA_Y2: &str =
    "13740680757317479711909903993315946540841369848973133181051452051592786724563";

const IC0_X: &str = "8446592859352799428420270221449902464741693648963397251242447530457567083492";
const IC0_Y: &str = "1064796367193003797175961162477173481551615790032213185848276823815288302804";
const IC1_X: &str = "3179835575189816632597428042194253779818690147323192973511715175294048485951";
const IC1_Y: &str = "20895841676865356752879376687052266198216014795822152491318012491767775979074";
const IC2_X: &str = "5332723250224941161709478398807683311971555792614491788690328996478511465287";
const IC2_Y: &str = "21199491073419440416471372042641226693637837098357067793586556692319371762571";
const IC3_X: &str = "12457994489566736295787256452575216703923664299075106359829199968023158780583";
const IC3_Y: &str = "19706766271952591897761291684837117091856807401404423804318744964752784280790";
const IC4_X: &str = "19617808913178163826953378459323299110911217259216006187355745713323154132237";
const IC4_Y: &str = "21663537384585072695701846972542344484111393047775983928357046779215877070466";
const IC5_X: &str = "6834578911681792552110317589222010969491336870276623105249474534788043166867";
const IC5_Y: &str = "15060583660288623605191393599883223885678013570733629274538391874953353488393";

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
