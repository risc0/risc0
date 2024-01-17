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

use anyhow::{anyhow, Context, Error};
use ark_bn254::{Bn254, G1Affine, G1Projective, G2Affine};
use ark_groth16::{Groth16 as ark_Groth16, PreparedVerifyingKey, Proof};
use ark_serialize::{CanonicalDeserialize, CanonicalSerialize};
use ethereum_types::U256;
use serde::{Deserialize, Serialize};
use sha2::Digest as _;

use crate::circom::{CircomProof, CircomPublic, CircomVKey};

pub mod circom;

#[derive(Debug, Deserialize, Serialize, PartialEq)]
pub struct Groth16Seal {
    /// Proof 'a' value
    pub a: Vec<Vec<u8>>,
    /// Proof 'b' value
    pub b: Vec<Vec<Vec<u8>>>,
    /// Proof 'c' value
    pub c: Vec<Vec<u8>>,
}

impl TryFrom<CircomProof> for Groth16Seal {
    type Error = Error;
    fn try_from(circom_proof: CircomProof) -> Result<Self, Error> {
        let a = vec![
            from_u256(&circom_proof.pi_a[0])?,
            from_u256(&circom_proof.pi_a[1])?,
        ];

        let b = vec![
            vec![
                from_u256(&circom_proof.pi_b[0][1])?,
                from_u256(&circom_proof.pi_b[0][0])?,
            ],
            vec![
                from_u256(&circom_proof.pi_b[1][1])?,
                from_u256(&circom_proof.pi_b[1][0])?,
            ],
        ];

        let c = vec![
            from_u256(&circom_proof.pi_c[0])?,
            from_u256(&circom_proof.pi_c[1])?,
        ];

        Ok(Groth16Seal { a, b, c })
    }
}

#[derive(Debug, Deserialize, Serialize)]
pub struct Groth16 {
    prepared_verifying_key: Vec<u8>,
    proof: Vec<u8>,
    prepared_inputs: Vec<u8>,
}

impl Groth16 {
    pub fn from_circom(
        circom_vk: CircomVKey,
        circom_proof: CircomProof,
        circom_public: CircomPublic,
    ) -> Result<Self, anyhow::Error> {
        let mut prepared_verifying_key_bytes = Vec::new();
        let public_key_verification = circom_vk.prepare_verifying_key()?;
        public_key_verification.serialize_uncompressed(&mut prepared_verifying_key_bytes)?;

        let groth16_seal: Groth16Seal = circom_proof.try_into()?;
        let proof = Proof::<Bn254> {
            a: convert_g1(&groth16_seal.a)?,
            b: convert_g2(&groth16_seal.b)?,
            c: convert_g1(&groth16_seal.c)?,
        };
        let mut proof_bytes = Vec::new();
        proof.serialize_uncompressed(&mut proof_bytes)?;

        let public_inputs = circom_public.public_inputs()?;
        let mut prepared_inputs_bytes = Vec::new();
        let prepared_inputs =
            ark_Groth16::<Bn254>::prepare_inputs(&public_key_verification, &public_inputs)?;
        prepared_inputs.serialize_uncompressed(&mut prepared_inputs_bytes)?;

        Ok(Self {
            prepared_verifying_key: prepared_verifying_key_bytes,
            proof: proof_bytes,
            prepared_inputs: prepared_inputs_bytes,
        })
    }

    pub fn verify(&self) -> Result<(), Error> {
        let prepared_verifying_key =
            &PreparedVerifyingKey::deserialize_uncompressed(&*self.prepared_verifying_key)?;
        let proof = &Proof::deserialize_uncompressed(&*self.proof)?;
        let prepared_inputs = &G1Projective::deserialize_uncompressed(&*self.prepared_inputs)?;
        match ark_Groth16::<Bn254>::verify_proof_with_prepared_inputs(
            prepared_verifying_key,
            proof,
            prepared_inputs,
        )? {
            true => Ok(()),
            false => Err(anyhow!("Invalid proof")),
        }
    }

    pub fn digest(&self) -> [u8; 32] {
        let mut hasher = sha2::Sha256::new();
        hasher.update(&self.prepared_verifying_key);
        hasher.update(&self.proof);
        hasher.update(&self.prepared_inputs);
        hasher.finalize().into()
    }
}

fn convert_g1(elem: &[Vec<u8>]) -> Result<G1Affine, Error> {
    if elem.len() != 2 {
        return Err(anyhow!("Malformed G1 element field"));
    }
    let g1_affine: Vec<u8> = elem[0]
        .iter()
        .rev()
        .chain(elem[1].iter().rev())
        .cloned()
        .collect();

    Ok(G1Affine::deserialize_uncompressed(&*g1_affine)?)
}

fn convert_g2(elem: &Vec<Vec<Vec<u8>>>) -> Result<G2Affine, Error> {
    if elem.len() != 2 || elem[0].len() != 2 || elem[1].len() != 2 {
        return Err(anyhow!("Malformed G2 element field"));
    }
    let g2_affine: Vec<u8> = elem[0][1]
        .iter()
        .rev()
        .chain(elem[0][0].iter().rev())
        .chain(elem[1][1].iter().rev())
        .chain(elem[1][0].iter().rev())
        .cloned()
        .collect();

    Ok(G2Affine::deserialize_uncompressed(&*g2_affine)?)
}

// Convert the U256 value to a byte array in big-endian format
fn from_u256(value: &str) -> Result<Vec<u8>, Error> {
    let mut bytes = [0u8; 32];
    let value = if value.starts_with("0x") {
        U256::from_str_radix(value, 16).context("Invalid number")?
    } else {
        U256::from_dec_str(value).context("Invalid number")?
    };
    value.to_big_endian(&mut bytes);
    Ok(bytes.to_vec())
}
