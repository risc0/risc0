use crate::{from_u256, g1_from_bytes, g2_from_bytes, Seal, Verifier, VerifyingKey};
use anyhow::{Error, Result};
use ark_bn254::Bn254;
use ark_ff::PrimeField;
use risc0_zkp::core::digest::Digest;

// Constants from: risc0-ethereum/contracts/src/blake3/Groth16Verifier.sol
// When running a new ceremony, update them by running cargo xtask bootstrap-blake3-groth16
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
    "18786665442134809547367793008388252094276956707083189371748822844215202271178";
const DELTA_X2: &str =
    "17296777349791701671871010047490559682924748762983962242018229225890177681165";
const DELTA_Y1: &str =
    "21546884238630900902634517213362010321565339505810557359182294051078510536811";
const DELTA_Y2: &str =
    "7214627676570978956115414107903354102221009447018809863680303520130992055423";

const IC0_X: &str = "1396989810128049774239906514097458055670219613079348950494410066757721605523";
const IC0_Y: &str = "20069629286434534534516684991063672335613842540347999544849171590987775766961";
const IC1_X: &str = "19282603452922066135228857769519044667044696173320493211119861249451600114594";
const IC1_Y: &str = "11966256187809052800087108088094647243345273965264062329687482664981607072161";

/// Default verifying key for RISC Zero recursive verification.
pub fn verifying_key() -> VerifyingKey {
    // VerifyingKey(get_ark_verifying_key())
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

    let gamma_abc_g1 = vec![ic0, ic1];

    Ok(VerifyingKey(ark_groth16::VerifyingKey::<Bn254> {
        alpha_g1,
        beta_g2,
        gamma_g2,
        delta_g2,
        gamma_abc_g1,
    }))
}

impl Verifier {
    /// Creates a new Groth16 Blake3`Verifier` instance.
    pub fn new_blake3(
        seal: &[u8],
        claim_digest: Digest,
        verifying_key: &VerifyingKey,
    ) -> Result<Self, Error> {
        let seal = Seal::decode(seal)?;
        let public_input_scalar = crate::Fr(ark_bn254::Fr::from_be_bytes_mod_order(
            claim_digest.as_ref(),
        ));
        Self::new_inner(&seal, &[public_input_scalar], verifying_key)
    }
}
