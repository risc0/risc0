use crate::{from_u256, g1_from_bytes, g2_from_bytes, Seal, Verifier, VerifyingKey};
use anyhow::{Error, Result};
use ark_bn254::Bn254;
use ark_ff::PrimeField;
use risc0_zkp::core::digest::Digest;

// Constants from: risc0-ethereum/contracts/src/blake3/Groth16Verifier.sol
// When running a new ceremony, update them by running cargo xtask bootstrap-blake3-groth16
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
    "19916519943909223643323234301580053157586699704876134064841182937085943926141";
const DELTA_X2: &str =
    "19928663713463533589216209779412278386769407450988172849262535478593422929698";
const DELTA_Y1: &str =
    "903010326261527050999816348900764705196723158942686053018929539519969664840";
const DELTA_Y2: &str =
    "4584600978911428195337731119171761277167808711062125916470525050324985708782";

const IC0_X: &str = "6698887085900109660417671413804888867145870700073340970189635830129386206569";
const IC0_Y: &str = "10431087902009508261375793061696708147989126018612269070732549055898651692604";
const IC1_X: &str = "20225609417084538563062516991929114218412992453664808591983416996515711931386";
const IC1_Y: &str = "3236310410959095762960658876334609343091075204896196791007975095263664214628";

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
