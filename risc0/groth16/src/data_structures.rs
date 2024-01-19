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

extern crate alloc;

use alloc::{vec, vec::Vec};

use anyhow::{bail, Error, Result};
use ark_bn254::{Bn254, Fr};
use ark_groth16::{prepare_verifying_key, PreparedVerifyingKey, VerifyingKey};
use serde::{Deserialize, Serialize};

use crate::{from_u256, g1_from_bytes, g2_from_bytes};

/// Groth16 seal object encoded in big endian.
#[derive(Clone, Debug, Deserialize, Serialize, PartialEq)]
pub struct Seal {
    /// Proof 'a' value
    pub a: Vec<Vec<u8>>,
    /// Proof 'b' value
    pub b: Vec<Vec<Vec<u8>>>,
    /// Proof 'c' value
    pub c: Vec<Vec<u8>>,
}

impl Seal {
    const ELEMENT_SIZE: usize = 32;
    const G1_GROUP_SIZE: usize = Self::ELEMENT_SIZE * 2;
    const G2_GROUP_SIZE: usize = Self::ELEMENT_SIZE * 4;
    const SIZE: usize = Self::G1_GROUP_SIZE * 2 + Self::G2_GROUP_SIZE;

    /// Serialize the Groth16 `Seal` into a `Vec<u8>`
    pub fn to_vec(&self) -> Vec<u8> {
        let mut result = Vec::with_capacity(Self::SIZE);

        // Serialize 'a'
        for item in &self.a {
            result.extend(item);
        }

        // Serialize 'b'
        for sub_vec in &self.b {
            for item in sub_vec {
                result.extend(item);
            }
        }

        // Serialize 'c'
        for item in &self.c {
            result.extend(item);
        }

        result
    }

    /// Method to convert back from a `Vec<u8>`
    pub fn from_vec(data: &[u8]) -> Result<Seal, Error> {
        if data.len() != Self::SIZE {
            bail!("Data length mismatch");
        }

        let mut offset = 0;
        let mut a = Vec::with_capacity(2);
        let mut b = Vec::with_capacity(2);
        let mut c = Vec::with_capacity(2);

        // Deserialize 'a'
        for _ in 0..2 {
            a.push(data[offset..offset + Self::ELEMENT_SIZE].to_vec());
            offset += Self::ELEMENT_SIZE;
        }

        // Deserialize 'b'
        for _ in 0..2 {
            let mut sub_vec = Vec::with_capacity(2);
            for _ in 0..2 {
                sub_vec.push(data[offset..offset + Self::ELEMENT_SIZE].to_vec());
                offset += Self::ELEMENT_SIZE;
            }
            b.push(sub_vec);
        }

        // Deserialize 'c'
        for _ in 0..2 {
            c.push(data[offset..offset + Self::ELEMENT_SIZE].to_vec());
            offset += Self::ELEMENT_SIZE;
        }

        Ok(Seal { a, b, c })
    }
}

impl TryFrom<ProofJson> for Seal {
    type Error = Error;
    fn try_from(proof: ProofJson) -> Result<Self, Error> {
        if proof.pi_a.len() < 2 {
            bail!("Malformed G1 element field");
        }
        let a = vec![from_u256(&proof.pi_a[0])?, from_u256(&proof.pi_a[1])?];

        if proof.pi_b.len() < 2 || proof.pi_b[0].len() < 2 || proof.pi_b[1].len() < 2 {
            bail!("Malformed G2 element field");
        }
        let b = vec![
            vec![from_u256(&proof.pi_b[0][1])?, from_u256(&proof.pi_b[0][0])?],
            vec![from_u256(&proof.pi_b[1][1])?, from_u256(&proof.pi_b[1][0])?],
        ];

        if proof.pi_c.len() < 2 {
            bail!("Malformed G1 element field");
        }
        let c = vec![from_u256(&proof.pi_c[0])?, from_u256(&proof.pi_c[1])?];

        Ok(Seal { a, b, c })
    }
}

/// Groth16 Proof encoded as JSON.
#[derive(Serialize, Deserialize, Debug)]
pub struct ProofJson {
    pi_a: Vec<String>,
    pi_b: Vec<Vec<String>>,
    pi_c: Vec<String>,
    protocol: String,
    curve: String,
}

/// Groth16 VErifying Key encoded as JSON.
#[derive(Serialize, Deserialize, Debug)]
pub struct VerifyingKeyJson {
    protocol: String,
    curve: String,
    #[serde(rename = "nPublic")]
    n_public: u32,
    vk_alpha_1: Vec<String>,
    vk_beta_2: Vec<Vec<String>>,
    vk_gamma_2: Vec<Vec<String>>,
    vk_delta_2: Vec<Vec<String>>,
    vk_alphabeta_12: Vec<Vec<Vec<String>>>,
    #[serde(rename = "IC")]
    ic: Vec<Vec<String>>,
}

impl VerifyingKeyJson {
    /// Computes the prepared verifying key
    pub fn prepared_verifying_key(&self) -> Result<PreparedVerifyingKey<Bn254>, Error> {
        if self.vk_alpha_1.len() < 2 {
            bail!("Malformed G1 element field: vk_alpha_1");
        }
        let alpha_g1 = g1_from_bytes(&vec![
            from_u256(&self.vk_alpha_1[0])?,
            from_u256(&self.vk_alpha_1[1])?,
        ])?;

        if self.vk_beta_2.len() < 2 || self.vk_beta_2[0].len() < 2 || self.vk_beta_2[1].len() < 2 {
            bail!("Malformed G2 element field: vk_beta_2");
        }
        let beta_g2 = g2_from_bytes(&vec![
            vec![
                from_u256(&self.vk_beta_2[0][1])?,
                from_u256(&self.vk_beta_2[0][0])?,
            ],
            vec![
                from_u256(&self.vk_beta_2[1][1])?,
                from_u256(&self.vk_beta_2[1][0])?,
            ],
        ])?;

        if self.vk_gamma_2.len() < 2 || self.vk_gamma_2[0].len() < 2 || self.vk_gamma_2[1].len() < 2
        {
            bail!("Malformed G2 element field: vk_gamma_2");
        }
        let gamma_g2 = g2_from_bytes(&vec![
            vec![
                from_u256(&self.vk_gamma_2[0][1])?,
                from_u256(&self.vk_gamma_2[0][0])?,
            ],
            vec![
                from_u256(&self.vk_gamma_2[1][1])?,
                from_u256(&self.vk_gamma_2[1][0])?,
            ],
        ])?;

        if self.vk_delta_2.len() < 2 || self.vk_delta_2[0].len() < 2 || self.vk_delta_2[1].len() < 2
        {
            bail!("Malformed G2 element field: vk_delta_2");
        }
        let delta_g2 = g2_from_bytes(&vec![
            vec![
                from_u256(&self.vk_delta_2[0][1])?,
                from_u256(&self.vk_delta_2[0][0])?,
            ],
            vec![
                from_u256(&self.vk_delta_2[1][1])?,
                from_u256(&self.vk_delta_2[1][0])?,
            ],
        ])?;

        let gamma_abc_g1 = self
            .ic
            .iter()
            .enumerate()
            .map(|(i, ic)| {
                if ic.len() < 2 {
                    bail!("Malformed G1 element field: IC_{i}");
                }
                g1_from_bytes(&[from_u256(&ic[0])?, from_u256(&ic[1])?])
            })
            .collect::<Result<Vec<_>, _>>()?;

        let vk = VerifyingKey::<Bn254> {
            alpha_g1,
            beta_g2,
            gamma_g2,
            delta_g2,
            gamma_abc_g1,
        };

        Ok(prepare_verifying_key(&vk))
    }
}

/// Groth16 Public witness encoded as JSON.
#[derive(Serialize, Deserialize, Debug)]
pub struct PublicWitnessJson {
    /// values of the public witness
    pub values: Vec<String>,
}

impl PublicWitnessJson {
    /// Converts public inputs to scalars over the field of the G1/G2 groups.
    pub fn to_scalar(&self) -> Result<Vec<Fr>, Error> {
        let mut parsed_inputs: Vec<Fr> = Vec::with_capacity(self.values.len());
        for input in self.values.clone() {
            match input.parse::<u64>() {
                Ok(n) => parsed_inputs.push(Fr::from(n)),
                Err(_) => bail!("Failed to decode snark 'public inputs' values"),
            }
        }
        Ok(parsed_inputs)
    }
}
