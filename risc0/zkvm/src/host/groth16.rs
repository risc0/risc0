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

use alloc::{format, vec, vec::Vec};
use core::str::FromStr;

use anyhow::{anyhow, bail, Error, Result};
use ark_bn254::{Bn254, Fr, G1Affine, G1Projective, G2Affine};
use ark_groth16::{
    prepare_verifying_key, Groth16 as ark_Groth16, PreparedVerifyingKey, Proof, VerifyingKey,
};
use ark_serialize::{CanonicalDeserialize, CanonicalSerialize};
use hex::FromHex;
use num_bigint::BigInt;
use serde::{Deserialize, Serialize};

use crate::{sha::Digest, ALLOWED_IDS_ROOT};

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
    "7693487429026351977103582346623702458502994930724273067160489676068253241122";
const DELTA_X2: &str =
    "18083587067730303898088465773541035809657139089748028791075809901844080381583";
const DELTA_Y1: &str =
    "7359384703862385660061748803901931167856917172356103761995576336394013820206";
const DELTA_Y2: &str =
    "19155327851717349610711498610928624259731705665803906701543914342469719520424";

const IC0_X: &str = "3946965800586156692981925338368207536736705930062938727478976206429630223321";
const IC0_Y: &str = "9960693350301697546955796394716396930467039081099556382890913872882520616640";
const IC1_X: &str = "12558970553567495705160565934359147265891951005223735094684712986779479012425";
const IC1_Y: &str = "6199258869647841500919704073457246710601253972070160340767955790036898000135";
const IC2_X: &str = "16706808935575787802711250967470306094414582323642394044367277865965614549578";
const IC2_Y: &str = "4311171349764489922968166376528109775195413405587105360819319395803197119429";
const IC3_X: &str = "18597303695576860451572687600097059285572952378680993135977532372976749998241";
const IC3_Y: &str = "21723251549997210319914312194189948104957781222830842952199420842095495134729";
const IC4_X: &str = "12164939688015960624286304530289921602116255917351297336606146584068755512927";
const IC4_Y: &str = "17036398532634379807038707418819848170237695473144751623976431755966389161373";

/// Groth16 proof object encoded in big endian
#[derive(Clone, Debug, Deserialize, Serialize, PartialEq)]
pub struct Groth16Seal {
    /// Proof 'a' value
    pub a: Vec<Vec<u8>>,
    /// Proof 'b' value
    pub b: Vec<Vec<Vec<u8>>>,
    /// Proof 'c' value
    pub c: Vec<Vec<u8>>,
}

impl Groth16Seal {
    const ELEMENT_SIZE: usize = 32;
    const G1_GROUP_SIZE: usize = Self::ELEMENT_SIZE * 2;
    const G2_GROUP_SIZE: usize = Self::ELEMENT_SIZE * 4;
    const SIZE: usize = Self::G1_GROUP_SIZE * 2 + Self::G2_GROUP_SIZE;

    /// Serialize the Groth16 seal into `Vec<u8>`
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

    /// Method to convert back from `Vec<u8>`
    pub fn from_vec(data: &[u8]) -> Result<Groth16Seal, Error> {
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

        Ok(Groth16Seal { a, b, c })
    }
}

/// Groth16 instance over the BN_254 curve encoded in little endian
#[derive(Clone, Debug, Deserialize, Serialize)]
pub struct Groth16Proof {
    pvk: Vec<u8>,
    proof: Vec<u8>,
    prepared_inputs: Vec<u8>,
}

impl Groth16Proof {
    /// Creates a Groth16 instance from a `Groth16Seal` and the claim digest
    /// of the original RISC Zero receipt
    pub fn from_seal(groth16_seal: &Groth16Seal, receipt_claim: Digest) -> Result<Self, Error> {
        let mut pvk_bytes = Vec::new();
        let public_key_verification = Self::pvk()?;
        public_key_verification
            .serialize_uncompressed(&mut pvk_bytes)
            .map_err(|err| anyhow!(err))?;

        let mut proof_bytes = Vec::new();
        let proof = Proof::<Bn254> {
            a: g1_from_bytes(&groth16_seal.a)?,
            b: g2_from_bytes(&groth16_seal.b)?,
            c: g1_from_bytes(&groth16_seal.c)?,
        };
        proof
            .serialize_uncompressed(&mut proof_bytes)
            .map_err(|err| anyhow!(err))?;

        let mut prepared_inputs_bytes = Vec::new();
        let (c1, c2) =
            split_digest(Digest::from_hex(ALLOWED_IDS_ROOT).map_err(|err| anyhow!(err))?)?;
        let (m1, m2) = split_digest(receipt_claim)?;
        let public_inputs = vec![c2, c1, m2, m1];
        let prepared_inputs =
            ark_Groth16::<Bn254>::prepare_inputs(&public_key_verification, &public_inputs)
                .map_err(|err| anyhow!(err))?;
        prepared_inputs
            .serialize_uncompressed(&mut prepared_inputs_bytes)
            .map_err(|err| anyhow!(err))?;

        Ok(Self {
            pvk: pvk_bytes,
            proof: proof_bytes,
            prepared_inputs: prepared_inputs_bytes,
        })
    }

    /// Computes the prepared verifying key used by Bonsai
    fn pvk() -> Result<PreparedVerifyingKey<Bn254>, Error> {
        let alpha_g1 = g1_from_bytes(&vec![from_u256(ALPHA_X)?, from_u256(ALPHA_Y)?])?;
        let beta_g2 = g2_from_bytes(&vec![
            vec![from_u256(BETA_X1)?, from_u256(BETA_X2)?],
            vec![from_u256(BETA_Y1)?, from_u256(BETA_Y2)?],
        ])?;
        let gamma_g2 = g2_from_bytes(&vec![
            vec![from_u256(GAMMA_X1)?, from_u256(GAMMA_X2)?],
            vec![from_u256(GAMMA_Y1)?, from_u256(GAMMA_Y2)?],
        ])?;
        let delta_g2 = g2_from_bytes(&vec![
            vec![from_u256(DELTA_X1)?, from_u256(DELTA_X2)?],
            vec![from_u256(DELTA_Y1)?, from_u256(DELTA_Y2)?],
        ])?;

        let ic0 = g1_from_bytes(&vec![from_u256(IC0_X)?, from_u256(IC0_Y)?])?;
        let ic1 = g1_from_bytes(&vec![from_u256(IC1_X)?, from_u256(IC1_Y)?])?;
        let ic2 = g1_from_bytes(&vec![from_u256(IC2_X)?, from_u256(IC2_Y)?])?;
        let ic3 = g1_from_bytes(&vec![from_u256(IC3_X)?, from_u256(IC3_Y)?])?;
        let ic4 = g1_from_bytes(&vec![from_u256(IC4_X)?, from_u256(IC4_Y)?])?;
        let gamma_abc_g1 = vec![ic0, ic1, ic2, ic3, ic4];

        let vk = VerifyingKey::<Bn254> {
            alpha_g1,
            beta_g2,
            gamma_g2,
            delta_g2,
            gamma_abc_g1,
        };

        Ok(prepare_verifying_key(&vk))
    }

    /// Verifies the Groth16 instance
    pub fn verify(&self) -> Result<(), Error> {
        let pvk = &PreparedVerifyingKey::deserialize_uncompressed(&*self.pvk)
            .map_err(|err| anyhow!(err))?;
        let proof = &Proof::deserialize_uncompressed(&*self.proof).map_err(|err| anyhow!(err))?;
        let prepared_inputs = &G1Projective::deserialize_uncompressed(&*self.prepared_inputs)
            .map_err(|err| anyhow!(err))?;
        match ark_Groth16::<Bn254>::verify_proof_with_prepared_inputs(pvk, proof, prepared_inputs)
            .map_err(|err| anyhow!(err))?
        {
            true => Ok(()),
            false => bail!("Invalid proof"),
        }
    }
}

// Deserialize a scalar field from bytes in big-endian format
fn fr_from_bytes(scalar: &Vec<u8>) -> Result<Fr, Error> {
    let scalar: Vec<u8> = scalar.iter().rev().cloned().collect();
    Ok(Fr::deserialize_uncompressed(&*scalar).map_err(|err| anyhow!(err))?)
}

// Deserialize an element over the G1 group from bytes in big-endian format
fn g1_from_bytes(elem: &[Vec<u8>]) -> Result<G1Affine, Error> {
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
fn g2_from_bytes(elem: &Vec<Vec<Vec<u8>>>) -> Result<G2Affine, Error> {
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
fn from_u256(value: &str) -> Result<Vec<u8>, Error> {
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

// Splits the digest in half returning a scalar field for each
fn split_digest(d: Digest) -> Result<(Fr, Fr), Error> {
    let big_endian: Vec<u8> = d.as_bytes().to_vec().iter().rev().cloned().collect();
    let middle = big_endian.len() / 2;
    let (a, b) = big_endian.split_at(middle);
    Ok((
        fr_from_bytes(&from_u256(&format!("0x{}", hex::encode(a)))?)?,
        fr_from_bytes(&from_u256(&format!("0x{}", hex::encode(b)))?)?,
    ))
}

#[cfg(test)]
mod tests {
    const RISC0_RECEIPT_CLAIM_DIGEST: &str =
        "ff2b40ef5fc5f4a7dac43eb214d61dcf6665f7bedb6cfda244808318e066f656";

    const RISC0_GROTH16_SEAL: &str = r#"
    {
        "a":[[26,63,155,211,133,192,185,234,51,172,152,49,113,248,13,45,155,140,75,98,171,225,72,44,133,246,88,199,37,103,28,56],
            [22,46,102,79,175,35,89,153,55,78,200,143,26,196,209,62,247,200,136,247,101,65,101,157,59,33,20,91,191,43,246,84]],
        "b":[[[20,0,192,47,211,1,254,55,118,229,52,232,89,161,51,100,224,242,246,5,106,190,188,113,187,230,100,7,255,70,192,153],
            [9,206,194,232,36,249,103,125,57,1,189,209,245,133,230,79,219,98,176,253,221,160,20,78,189,142,46,52,171,1,162,203]],
            [[32,70,252,38,183,118,240,156,230,16,28,10,122,111,184,65,239,158,193,102,94,156,5,56,24,236,174,103,160,172,89,109],
            [4,151,70,37,225,160,65,7,230,206,172,247,41,192,58,149,244,201,31,171,7,137,232,107,29,143,227,49,96,29,198,35]]],
        "c":[[20,112,216,216,113,186,224,139,117,16,31,102,238,29,76,150,58,216,254,75,147,172,89,147,216,138,41,130,172,106,148,8],
            [23,250,144,90,188,98,158,62,214,76,108,236,158,31,125,183,20,200,101,254,212,15,32,174,120,230,219,15,71,206,189,55]]
    }
    "#;

    use super::*;

    #[ignore]
    #[test]
    fn test_from_seal() {
        let seal: Groth16Seal = serde_json::from_str(RISC0_GROTH16_SEAL).unwrap();
        let groth16 =
            Groth16Proof::from_seal(&seal, Digest::from_hex(RISC0_RECEIPT_CLAIM_DIGEST).unwrap())
                .unwrap();
        groth16.verify().unwrap();
    }
}
