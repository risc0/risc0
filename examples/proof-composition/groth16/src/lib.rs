use anyhow::{anyhow, Context, Error};
use ark_bn254::{Bn254, Fr, G1Affine, G1Projective, G2Affine};
use ark_groth16::{Groth16 as ark_Groth16, PreparedVerifyingKey, Proof};
use ark_serialize::{CanonicalDeserialize, CanonicalSerialize};
use ethereum_types::U256;
use pvk::pvk;
use raw::{RawProof, RawPublic, RawVKey};
use risc0_zkvm::sha::Digest;
use serde::{Deserialize, Serialize};
use sha2::Digest as _;

pub mod pvk;
pub mod raw;

#[derive(Debug, Deserialize, Serialize, PartialEq)]
pub struct Groth16Seal {
    /// Proof 'a' value
    pub a: Vec<Vec<u8>>,
    /// Proof 'b' value
    pub b: Vec<Vec<Vec<u8>>>,
    /// Proof 'c' value
    pub c: Vec<Vec<u8>>,
    /// Proof public outputs
    pub public: Vec<Vec<u8>>,
}

impl TryFrom<RawProof> for Groth16Seal {
    type Error = Error;
    fn try_from(raw_proof: RawProof) -> Result<Self, Error> {
        let a = vec![
            from_u256(&raw_proof.pi_a[0])?,
            from_u256(&raw_proof.pi_a[1])?,
        ];

        let b = vec![
            vec![
                from_u256(&raw_proof.pi_b[0][1])?,
                from_u256(&raw_proof.pi_b[0][0])?,
            ],
            vec![
                from_u256(&raw_proof.pi_b[1][1])?,
                from_u256(&raw_proof.pi_b[1][0])?,
            ],
        ];

        let c = vec![
            from_u256(&raw_proof.pi_c[0])?,
            from_u256(&raw_proof.pi_c[1])?,
        ];

        Ok(Groth16Seal {
            a,
            b,
            c,
            public: vec![],
        })
    }
}

#[derive(Debug, Deserialize, Serialize)]
pub struct Groth16 {
    pvk: Vec<u8>,
    proof: Vec<u8>,
    prepared_inputs: Vec<u8>,
}

impl Groth16 {
    pub fn from_seal(
        groth16_seal: Groth16Seal,
        allowed_ids_root: Digest,
        receipt_meta: Digest,
    ) -> Result<Self, anyhow::Error> {
        let mut pvk_bytes = Vec::new();
        let public_key_verification = pvk()?;
        public_key_verification.serialize_uncompressed(&mut pvk_bytes)?;

        let mut proof_bytes = Vec::new();
        let proof = Proof::<Bn254> {
            a: convert_g1(&groth16_seal.a)?,
            b: convert_g2(&groth16_seal.b)?,
            c: convert_g1(&groth16_seal.c)?,
        };
        proof.serialize_uncompressed(&mut proof_bytes)?;

        let mut prepared_inputs_bytes = Vec::new();
        let (c1, c2) = split_digest(allowed_ids_root)?;
        let (m1, m2) = split_digest(receipt_meta)?;
        let public_inputs = vec![c2, c1, m2, m1];
        let prepared_inputs =
            ark_Groth16::<Bn254>::prepare_inputs(&public_key_verification, &public_inputs)?;
        prepared_inputs.serialize_uncompressed(&mut prepared_inputs_bytes)?;

        Ok(Self {
            pvk: pvk_bytes,
            proof: proof_bytes,
            prepared_inputs: prepared_inputs_bytes,
        })
    }

    pub fn from_raw(
        raw_vk: RawVKey,
        raw_proof: RawProof,
        raw_public: RawPublic,
    ) -> Result<Self, anyhow::Error> {
        let mut pvk_bytes = Vec::new();
        let public_key_verification = raw_vk.pvk()?;
        public_key_verification.serialize_uncompressed(&mut pvk_bytes)?;

        let groth16_seal: Groth16Seal = raw_proof.try_into()?;
        let proof = Proof::<Bn254> {
            a: convert_g1(&groth16_seal.a)?,
            b: convert_g2(&groth16_seal.b)?,
            c: convert_g1(&groth16_seal.c)?,
        };
        let mut proof_bytes = Vec::new();
        proof.serialize_uncompressed(&mut proof_bytes)?;

        let public_inputs = raw_public.public_inputs()?;
        let mut prepared_inputs_bytes = Vec::new();
        let prepared_inputs =
            ark_Groth16::<Bn254>::prepare_inputs(&public_key_verification, &public_inputs)?;
        prepared_inputs.serialize_uncompressed(&mut prepared_inputs_bytes)?;

        Ok(Self {
            pvk: pvk_bytes,
            proof: proof_bytes,
            prepared_inputs: prepared_inputs_bytes,
        })
    }

    pub fn verify(&self) -> Result<(), Error> {
        let pvk = &PreparedVerifyingKey::deserialize_uncompressed(&*self.pvk)?;
        let proof = &Proof::deserialize_uncompressed(&*self.proof)?;
        let prepared_inputs = &G1Projective::deserialize_uncompressed(&*self.prepared_inputs)?;
        match ark_Groth16::<Bn254>::verify_proof_with_prepared_inputs(pvk, proof, prepared_inputs)?
        {
            true => Ok(()),
            false => Err(anyhow!("Invalid proof")),
        }
    }

    pub fn digest(&self) -> [u8; 32] {
        let mut hasher = sha2::Sha256::new();
        hasher.update(&self.pvk);
        hasher.update(&self.proof);
        hasher.update(&self.prepared_inputs);
        hasher.finalize().into()
    }
}

fn convert_fr(scalar: &Vec<u8>) -> Result<Fr, Error> {
    let scalar: Vec<u8> = scalar.iter().rev().cloned().collect();
    Ok(Fr::deserialize_uncompressed(&*scalar)?)
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

fn split_digest(d: Digest) -> Result<(Fr, Fr), Error> {
    let big_endian: Vec<u8> = d.as_bytes().to_vec().iter().rev().cloned().collect();
    let middle = big_endian.len() / 2;
    let (a, b) = big_endian.split_at(middle);
    Ok((
        convert_fr(&from_u256(&format!("0x{}", hex::encode(a)))?)?,
        convert_fr(&from_u256(&format!("0x{}", hex::encode(b)))?)?,
    ))
}
