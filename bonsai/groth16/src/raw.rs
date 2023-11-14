// Copyright 2023 RISC Zero, Inc.
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

use anyhow::{anyhow, Error};
use ark_bn254::{Bn254, Fr};
use ark_groth16::{prepare_verifying_key, PreparedVerifyingKey, VerifyingKey};
use serde::{Deserialize, Serialize};

use crate::{convert_g1, convert_g2, from_u256};

#[derive(Serialize, Deserialize, Debug)]
pub struct RawProof {
    pub pi_a: Vec<String>,
    pub pi_b: Vec<Vec<String>>,
    pub pi_c: Vec<String>,
    pub protocol: String,
    pub curve: String,
}

#[derive(Serialize, Deserialize, Debug)]
pub struct RawVKey {
    pub protocol: String,
    pub curve: String,
    #[serde(rename = "nPublic")]
    pub n_public: u32,
    pub vk_alpha_1: Vec<String>,
    pub vk_beta_2: Vec<Vec<String>>,
    pub vk_gamma_2: Vec<Vec<String>>,
    pub vk_delta_2: Vec<Vec<String>>,
    pub vk_alphabeta_12: Vec<Vec<Vec<String>>>,
    #[serde(rename = "IC")]
    pub ic: Vec<Vec<String>>,
}

impl RawVKey {
    pub fn pvk(&self) -> Result<PreparedVerifyingKey<Bn254>, Error> {
        let alpha_g1 = convert_g1(&vec![
            from_u256(&self.vk_alpha_1[0])?,
            from_u256(&self.vk_alpha_1[1])?,
        ])?;

        let beta_g2 = convert_g2(&vec![
            vec![
                from_u256(&self.vk_beta_2[0][1])?,
                from_u256(&self.vk_beta_2[0][0])?,
            ],
            vec![
                from_u256(&self.vk_beta_2[1][1])?,
                from_u256(&self.vk_beta_2[1][0])?,
            ],
        ])?;
        let gamma_g2 = convert_g2(&vec![
            vec![
                from_u256(&self.vk_gamma_2[0][1])?,
                from_u256(&self.vk_gamma_2[0][0])?,
            ],
            vec![
                from_u256(&self.vk_gamma_2[1][1])?,
                from_u256(&self.vk_gamma_2[1][0])?,
            ],
        ])?;
        let delta_g2 = convert_g2(&vec![
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
            .map(|ic| convert_g1(&[from_u256(&ic[0])?, from_u256(&ic[1])?]))
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

#[derive(Serialize, Deserialize, Debug)]
pub struct RawPublic {
    pub values: Vec<String>,
}

impl RawPublic {
    pub fn public_inputs(&self) -> Result<Vec<Fr>, Error> {
        let mut parsed_inputs: Vec<Fr> = Vec::with_capacity(self.values.len());
        for input in self.values.clone() {
            match input.parse::<u64>() {
                Ok(n) => parsed_inputs.push(Fr::from(n)),
                Err(_) => return Err(anyhow!("Failed to decode snark 'public inputs' values")),
            }
        }
        Ok(parsed_inputs)
    }
}

#[cfg(test)]
mod tests {
    use crate::fixtures::{CIRCOM_PROOF, CIRCOM_VERIFICATION_KEY};

    use super::*;

    #[test]
    fn test_proof_deserialization() {
        let proof: RawProof =
            serde_json::from_str(CIRCOM_PROOF).expect("JSON was not well-formatted");
        assert_eq!(proof.protocol, "groth16");
        assert_eq!(proof.curve, "bn128");
    }

    #[test]
    fn test_vkey_deserialization() {
        let vk: RawVKey =
            serde_json::from_str(CIRCOM_VERIFICATION_KEY).expect("JSON was not well-formatted");
        assert_eq!(vk.protocol, "groth16");
        assert_eq!(vk.curve, "bn128");
        assert_eq!(vk.n_public, 1);
        vk.pvk().unwrap();
    }
}
