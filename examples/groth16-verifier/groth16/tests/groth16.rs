#[cfg(test)]
mod tests {
    use hex::FromHex;
    use risc0_groth16::{
        circom::{CircomProof, CircomPublic, CircomVKey},
        Groth16,
    };

    const CIRCOM_VERIFICATION_KEY: &str = include_str!("data/circom/verification_key.json");
    const CIRCOM_PROOF: &str = include_str!("data/circom/proof.json");
    const CIRCOM_PUBLIC: &str = include_str!("data/circom/public.json");

    #[test]
    fn test_from_circom() {
        let circom_vkey: CircomVKey = serde_json::from_str(CIRCOM_VERIFICATION_KEY).unwrap();
        let circom_proof: CircomProof = serde_json::from_str(CIRCOM_PROOF).unwrap();
        let circom_public = CircomPublic {
            values: serde_json::from_str(CIRCOM_PUBLIC).unwrap(),
        };

        let groth16 = Groth16::from_circom(circom_vkey, circom_proof, circom_public).unwrap();
        groth16.verify().unwrap();
    }
}
