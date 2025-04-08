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

use anyhow::{anyhow, Error, Result};
use ark_serialize::CanonicalSerialize;
use risc0_binfmt::{tagged_iter, tagged_struct, Digestible};
use risc0_zkp::core::{digest::Digest, hash::sha::Sha256};
use serde::{Deserialize, Serialize};

use crate::{
    from_u256, ProofJson, PublicInputsJson, Pvk, Seal, VerifyingKeyJson, Vk,
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
// #[derive(Clone, Debug, Deserialize, Serialize)]
// TODO: Goal ... depending on exact needs may want to still hold onto things as Vec<u8> or Vec<Vec<u8>>
#[derive(Clone)]
pub struct Verifier {
    // /// prepared verifying key little endian encoded.
    // encoded_pvk: Vec<u8>,
    // /// proof little endian encoded.
    // encoded_proof: Vec<u8>,
    // /// prepared public inputs little endian encoded.
    // encoded_prepared_inputs: Vec<u8>,
    pvk: Pvk,
    proof: Seal,
    prepared_inputs: substrate_bn::G1,
}

impl Verifier {
    /// Creates a new Groth16 `Verifier` instance.
    pub fn new(
        seal: &Seal,
        public_inputs: &[substrate_bn::Fr],
        verifying_key: &Vk,
    ) -> Result<Self, Error> {
        // let pvk = ark_groth16::prepare_verifying_key(&verifying_key.0);
        let pvk = Pvk::from(verifying_key.clone());  // TODO: Is clone the right approach here? Or don't borrow the parameter?

        // let mut encoded_pvk = Vec::new();
        // pvk.serialize_uncompressed(&mut encoded_pvk)
        //     .map_err(|err| anyhow!(err))?;

        // let mut encoded_proof = Vec::new();
        // let proof = Proof::<Bn254> {
        //     a: g1_from_bytes(&seal.a)?,
        //     b: g2_from_bytes(&seal.b)?,
        //     c: g1_from_bytes(&seal.c)?,
        // };
        // proof
        //     .serialize_uncompressed(&mut encoded_proof)
        //     .map_err(|err| anyhow!(err))?;

        // let mut encoded_prepared_inputs = Vec::new();
        // let prepared_inputs = Groth16::<Bn254>::prepare_inputs(
        //     &pvk,
        //     &public_inputs.iter().map(|x| x.0).collect::<Vec<_>>(),
        // )
        // .map_err(|err| anyhow!(err))?;
        // prepared_inputs
        //     .serialize_uncompressed(&mut encoded_prepared_inputs)
        //     .map_err(|err| anyhow!(err))?;

        // TODO: Use this error handling approach elsewhere?
        let prepared_inputs = prepare_inputs(&pvk, public_inputs).map_err(|err| anyhow!(err))?;

        Ok(Self {
            pvk,
            proof: seal.clone(),
            prepared_inputs,
        })
    }

    /// Create a Verifier given the JSON representation of the proof, public inputs and verifier
    /// key.
    pub fn from_json(
        proof: ProofJson,
        public_inputs: PublicInputsJson,
        verifying_key: VerifyingKeyJson,
    ) -> Result<Self> {
        Verifier::new(
            &proof.try_into()?,
            &public_inputs.to_scalar()?,
            &verifying_key.verifying_key()?,
        )
    }

    /// Verifies the Groth16 proof.
    pub fn verify(&self) -> Result<(), Error> {
        // let pvk = &PreparedVerifyingKey::deserialize_uncompressed(&*self.encoded_pvk)
        //     .map_err(|err| anyhow!(err))?;
        // let proof =
        //     &Proof::deserialize_uncompressed(&*self.encoded_proof).map_err(|err| anyhow!(err))?;
        // let prepared_inputs =
        //     &G1Projective::deserialize_uncompressed(self.encoded_prepared_inputs.as_slice())
        //         .map_err(|err| anyhow!(err))?;
        // TODO: May need deserialization? Depends on approach we take


        let plain_result = substrate_bn::miller_loop_batch(
            // TODO: more clones that are probably unnecessary...
            // TODO: Use this one
            &[
                (crate::LocalG2::from_be_bytes(&self.proof.b)?.into(), crate::LocalG1::from_be_bytes(&self.proof.a)?.into()),
                (self.pvk.gamma_g2_neg_pc.clone().into(), self.prepared_inputs),
                (self.pvk.delta_g2_neg_pc.clone().into(), crate::LocalG1::from_be_bytes(&self.proof.c)?.into()),
            ]

            // TODO: This is deliberately broken! Just testing!
            // &[
            //     (crate::LocalG2::from_be_bytes(&self.proof.b)?.into(), crate::LocalG1::from_be_bytes(&self.proof.c)?.into()),
            //     (self.pvk.gamma_g2_neg_pc.clone().into(), self.prepared_inputs),
            //     (self.pvk.delta_g2_neg_pc.clone().into(), crate::LocalG1::from_be_bytes(&self.proof.a)?.into()),
            // ]
            // /TODO end of deliberate break
        ).expect("TODO better error handling");
        let exponentiated = plain_result.final_exponentiation().ok_or_else(||anyhow!("Unexpected identity in final exponentiation step of verify"))?;
        if exponentiated == self.pvk.alpha_g1_beta_g2 {
            Ok(())
        } else {
            Err(anyhow!("Groth16 proof failed verification"))
        }



        // match Groth16::<Bn254>::verify_proof_with_prepared_inputs(pvk, proof, prepared_inputs)
        //     .map_err(|err| anyhow!(err))?
        // {
        //     true => Ok(()),
        //     false => Err(anyhow!("Invalid proof")),
        // }
    }
}

/// Verifying key for Groth16 proofs.
#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct Fr(#[serde(with = "serde_ark")] pub(crate) ark_bn254::Fr);

impl Fr {
    #[stability::unstable]
    pub fn ark_fr(&self) -> ark_bn254::Fr {
        self.0
    }
}

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
// TODO: Can we get away with fewer derives?
// #[derive(Clone, Debug, Serialize, Deserialize)]
#[derive(Clone)]
pub struct VerifyingKey(pub(crate) Vk);

// /// Hash a point on G1 or G2 by hashing the concatenated big-endian representation of (x, y).
// fn hash_point<S: Sha256>(p: impl AffineRepr) -> Digest {
//     let mut buffer = Vec::<u8>::new();
//     // If p is the point at infinity, the verifying key is invalid. Panic.
//     let (x, y) = p.xy().unwrap();
//     y.serialize_uncompressed(&mut buffer).unwrap();
//     x.serialize_uncompressed(&mut buffer).unwrap();
//     buffer.reverse();
//     *S::hash_bytes(&buffer)
// }

// TODO: As with other uses of LocalG1/LocalG2, we should probably deprecate those and clean this up
fn hash_g1_point<S: Sha256>(p: &crate::LocalG1) -> Digest {
    let mut buffer = [0u8; 64];
    let pt = p.0.expect("Verifying key contains point at infinity and hence is invalid");
    pt.y().to_big_endian(&mut buffer[0..32]).expect("output slice length is 32");
    pt.x().to_big_endian(&mut buffer[32..64]).expect("output slice length is 32");
    buffer.reverse();
    // TODO: This _might_ preserve how these hash relative to the arkworks version, but it's not tested
    //    > If this matters, test it, and fix any bugs!
    //    > If this doesn't matter, drop the `buffer.reverse()`!
    *S::hash_bytes(&buffer)
}

fn hash_g2_point<S: Sha256>(p: &crate::LocalG2) -> Digest {
    let mut buffer = [0u8; 128];
    let pt = p.0.expect("Verifying key contains point at infinity and hence is invalid");
    pt.y().real().to_big_endian(&mut buffer[0..32]).expect("output slice length is 32");
    pt.y().imaginary().to_big_endian(&mut buffer[32..64]).expect("output slice length is 32");
    pt.x().real().to_big_endian(&mut buffer[64..96]).expect("output slice length is 32");
    pt.x().imaginary().to_big_endian(&mut buffer[96..128]).expect("output slice length is 32");
    buffer.reverse();
    // TODO: This _might_ preserve how these hash relative to the arkworks version, but it's not tested
    //    > If this matters, test it, and fix any bugs!
    //    > If this doesn't matter, drop the `buffer.reverse()`!
    *S::hash_bytes(&buffer)
}

// TODO: Presumably we need this somewhere?
impl Digestible for VerifyingKey {
    /// Hash the [VerifyingKey] to get a struct digest.
    fn digest<S: Sha256>(&self) -> Digest {
        tagged_struct::<S>(
            "risc0_groth16.VerifyingKey",
            &[
                hash_g1_point::<S>(&self.0.alpha_g1),
                hash_g2_point::<S>(&self.0.beta_g2),
                hash_g2_point::<S>(&self.0.gamma_g2),
                hash_g2_point::<S>(&self.0.delta_g2),
                tagged_iter::<S>(
                    "risc0_groth16.VerifyingKey.IC",
                    self.0.gamma_abc_g1.iter().map(|p| hash_g1_point::<S>(p)),
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

// /// Default verifying key for RISC Zero recursive verification.
// pub fn verifying_key() -> VerifyingKey {
//     try_verifying_key().unwrap()
// }

// TODO: Ok that the type changed?
// TODO: I don't think the allow(dead_code) should be needed...
/// Default verifying key for RISC Zero recursive verification.
#[allow(dead_code)]
pub fn verifying_key() -> Vk {
    // TODO: We should probably be wrapping this as a VerifyingKey for compatability
    try_vk().unwrap()
}

// // try_verifying_key executes entirely over const data and so should never error.
// fn try_verifying_key() -> Result<VerifyingKey, Error> {
//     let alpha_g1 = g1_from_bytes(&[from_u256(ALPHA_X)?, from_u256(ALPHA_Y)?])?;
//     let beta_g2 = g2_from_bytes(&[
//         vec![from_u256(BETA_X1)?, from_u256(BETA_X2)?],
//         vec![from_u256(BETA_Y1)?, from_u256(BETA_Y2)?],
//     ])?;
//     let gamma_g2 = g2_from_bytes(&[
//         vec![from_u256(GAMMA_X1)?, from_u256(GAMMA_X2)?],
//         vec![from_u256(GAMMA_Y1)?, from_u256(GAMMA_Y2)?],
//     ])?;
//     let delta_g2 = g2_from_bytes(&[
//         vec![from_u256(DELTA_X1)?, from_u256(DELTA_X2)?],
//         vec![from_u256(DELTA_Y1)?, from_u256(DELTA_Y2)?],
//     ])?;

//     let ic0 = g1_from_bytes(&[from_u256(IC0_X)?, from_u256(IC0_Y)?])?;
//     let ic1 = g1_from_bytes(&[from_u256(IC1_X)?, from_u256(IC1_Y)?])?;
//     let ic2 = g1_from_bytes(&[from_u256(IC2_X)?, from_u256(IC2_Y)?])?;
//     let ic3 = g1_from_bytes(&[from_u256(IC3_X)?, from_u256(IC3_Y)?])?;
//     let ic4 = g1_from_bytes(&[from_u256(IC4_X)?, from_u256(IC4_Y)?])?;
//     let ic5 = g1_from_bytes(&[from_u256(IC5_X)?, from_u256(IC5_Y)?])?;
//     let gamma_abc_g1 = vec![ic0, ic1, ic2, ic3, ic4, ic5];

//     Ok(VerifyingKey(ark_groth16::VerifyingKey::<Bn254> {
//         alpha_g1,
//         beta_g2,
//         gamma_g2,
//         delta_g2,
//         gamma_abc_g1,
//     }))
// }

// TODO: Naming
fn try_vk() -> Result<Vk, Error> {
    let alpha_g1 = crate::LocalG1::from_be_bytes(&[from_u256(ALPHA_X)?, from_u256(ALPHA_Y)?])?;
    let beta_g2 = crate::LocalG2::from_be_bytes(&[
        vec![from_u256(BETA_X1)?, from_u256(BETA_X2)?],
        vec![from_u256(BETA_Y1)?, from_u256(BETA_Y2)?],
    ])?;
    let gamma_g2 = crate::LocalG2::from_be_bytes(&[
        vec![from_u256(GAMMA_X1)?, from_u256(GAMMA_X2)?],
        vec![from_u256(GAMMA_Y1)?, from_u256(GAMMA_Y2)?],
    ])?;
    let delta_g2 = crate::LocalG2::from_be_bytes(&[
        vec![from_u256(DELTA_X1)?, from_u256(DELTA_X2)?],
        vec![from_u256(DELTA_Y1)?, from_u256(DELTA_Y2)?],
    ])?;

    let ic0 = crate::LocalG1::from_be_bytes(&[from_u256(IC0_X)?, from_u256(IC0_Y)?])?;
    let ic1 = crate::LocalG1::from_be_bytes(&[from_u256(IC1_X)?, from_u256(IC1_Y)?])?;
    let ic2 = crate::LocalG1::from_be_bytes(&[from_u256(IC2_X)?, from_u256(IC2_Y)?])?;
    let ic3 = crate::LocalG1::from_be_bytes(&[from_u256(IC3_X)?, from_u256(IC3_Y)?])?;
    let ic4 = crate::LocalG1::from_be_bytes(&[from_u256(IC4_X)?, from_u256(IC4_Y)?])?;
    let ic5 = crate::LocalG1::from_be_bytes(&[from_u256(IC5_X)?, from_u256(IC5_Y)?])?;
    let gamma_abc_g1 = vec![ic0, ic1, ic2, ic3, ic4, ic5];

    Ok(Vk {
        alpha_g1,
        beta_g2,
        gamma_g2,
        delta_g2,
        gamma_abc_g1,
    })
}

// TODO
pub fn prepare_inputs(pvk: &Pvk, public_inputs: &[substrate_bn::Fr]) -> Result<substrate_bn::G1> {
    if (public_inputs.len() + 1) != pvk.vk.gamma_abc_g1.len() {
        return Err(anyhow!("Cannot prepare inputs, verifying key length should be 1 more than number of inputs (instead: {}, {})", pvk.vk.gamma_abc_g1.len(), public_inputs.len()));
    }

    // TODO: A whole bunch of cloning that I may be able to avoid with proper types initially
    let mut res: substrate_bn::G1 = pvk.vk.gamma_abc_g1[0].clone().into();
    for (inp, ic) in public_inputs.iter().zip(pvk.vk.gamma_abc_g1.iter().skip(1)) {
        res = res + substrate_bn::G1::from(ic.clone()) * *inp;
    }

    Ok(res)
}
