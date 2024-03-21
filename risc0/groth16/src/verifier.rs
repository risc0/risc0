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

use anyhow::{anyhow, Error, Result};
use ark_bn254::{Bn254, Fr, G1Projective};
use ark_groth16::{prepare_verifying_key, Groth16, PreparedVerifyingKey, Proof, VerifyingKey};
use ark_serialize::{CanonicalDeserialize, CanonicalSerialize};
use serde::{Deserialize, Serialize};

use crate::{
    from_u256, g1_from_bytes, g2_from_bytes, ProofJson, PublicInputsJson, Seal, VerifyingKeyJson,
};

// Constants from: risc0-ethereum/contracts/src/groth16/Groth16Verifier.sol
// When running a new ceremony, update them by running cargo xtask bootstrap-groth16
// after udpating the new Groth16Verifier.sol on the risc0-ethereum repo.
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
    "15812970097961370153674199617774981716040734315258649745290401636407380406912";
const DELTA_X2: &str =
    "15272907684154633044509543400226731318818418052841756853813885452870310184616";
const DELTA_Y1: &str =
    "17615325087184137087962095547508842687619248542240677521719991620946359765556";
const DELTA_Y2: &str =
    "20648240692136268378418423236571415246868768896669777929780643427309530963184";

const IC0_X: &str = "3493191013609582086479185699231962539321697357623463793463992857745531777381";
const IC0_Y: &str = "16181448008586693940906739179135819777560403605989488561390517361491131931950";
const IC1_X: &str = "11936905984999022183412847785498644142185378561697141688442207694436807935920";
const IC1_Y: &str = "11686533372229744443154300202082468163410958089472870786803623145513267068573";
const IC2_X: &str = "17682812385468410232642290005758664702166900922163386855513442644600346939455";
const IC2_Y: &str = "17146787898844892575864657670828581364923927000042081018806719640965782443948";
const IC3_X: &str = "20457045958098673349648536986654637998627860761194610688186494785887928186418";
const IC3_Y: &str = "20016645794309877455213278100232898860301762821112066365123784115381277628768";
const IC4_X: &str = "21239879785520219456396454940027328701856640130991351667643741030239553576430";
const IC4_Y: &str = "20792082454563427423578028870779800202936035067991988946784302720095342614530";
const IC5_X: &str = "5593923098692524530660316905672717559365410553851682305615606996949212514665";
const IC5_Y: &str = "11658944420229172238682484071783135005767555025673223959566076634298941625504";

/// Groth16 `Verifier` instance over the BN_254 curve encoded in little endian.
#[derive(Clone, Debug, Deserialize, Serialize)]
pub struct Verifier {
    /// prepared verifying key little endian encoded.
    pub encoded_pvk: Vec<u8>,
    /// proof little endian encoded.
    pub encoded_proof: Vec<u8>,
    /// prepared public inputs little endian encoded.
    pub encoded_prepared_inputs: Vec<u8>,
}

impl Verifier {
    /// Creates a new Groth16 `Verifier` instance.
    pub fn new(
        seal: &Seal,
        public_inputs: Vec<Fr>,
        prepared_verifying_key: PreparedVerifyingKey<Bn254>,
    ) -> Result<Self, Error> {
        let mut encoded_pvk = Vec::new();
        prepared_verifying_key
            .serialize_uncompressed(&mut encoded_pvk)
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
        let prepared_inputs =
            Groth16::<Bn254>::prepare_inputs(&prepared_verifying_key, &public_inputs)
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

    pub fn from_json(
        proof: ProofJson,
        public_inputs: PublicInputsJson,
        verifying_key: VerifyingKeyJson,
    ) -> Result<Self> {
        Verifier::new(
            &proof.try_into()?,
            public_inputs.to_scalar()?,
            verifying_key.prepared_verifying_key()?,
        )
    }

    /// Verifies the Groth16 proof.
    pub fn verify(&self) -> Result<(), Error> {
        let pvk = &PreparedVerifyingKey::deserialize_uncompressed(&*self.encoded_pvk)
            .map_err(|err| anyhow!(err))?;
        let proof =
            &Proof::deserialize_uncompressed(&*self.encoded_proof).map_err(|err| anyhow!(err))?;
        let prepared_inputs =
            &G1Projective::deserialize_uncompressed(&*self.encoded_prepared_inputs)
                .map_err(|err| anyhow!(err))?;
        match Groth16::<Bn254>::verify_proof_with_prepared_inputs(pvk, proof, prepared_inputs)
            .map_err(|err| anyhow!(err))?
        {
            true => Ok(()),
            false => Err(anyhow!("Invalid proof")),
        }
    }
}

/// Computes the default prepared verifying key, used by Bonsai.
pub fn prepared_verifying_key() -> Result<PreparedVerifyingKey<Bn254>, Error> {
    let alpha_g1 = g1_from_bytes(&[from_u256(ALPHA_X)?, from_u256(ALPHA_Y)?])?;
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

    let ic0 = g1_from_bytes(&[from_u256(IC0_X)?, from_u256(IC0_Y)?])?;
    let ic1 = g1_from_bytes(&[from_u256(IC1_X)?, from_u256(IC1_Y)?])?;
    let ic2 = g1_from_bytes(&[from_u256(IC2_X)?, from_u256(IC2_Y)?])?;
    let ic3 = g1_from_bytes(&[from_u256(IC3_X)?, from_u256(IC3_Y)?])?;
    let ic4 = g1_from_bytes(&[from_u256(IC4_X)?, from_u256(IC4_Y)?])?;
    let ic5 = g1_from_bytes(&[from_u256(IC5_X)?, from_u256(IC5_Y)?])?;
    let gamma_abc_g1 = vec![ic0, ic1, ic2, ic3, ic4, ic5];

    let vk = VerifyingKey::<Bn254> {
        alpha_g1,
        beta_g2,
        gamma_g2,
        delta_g2,
        gamma_abc_g1,
    };

    Ok(prepare_verifying_key(&vk))
}
