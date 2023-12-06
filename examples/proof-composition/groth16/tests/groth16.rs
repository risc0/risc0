#[cfg(test)]
mod tests {
    use hex::FromHex;
    use risc0_groth16::{
        raw::{RawProof, RawPublic, RawVKey},
        Groth16, Groth16Seal,
    };
    use risc0_zkvm::{sha::Digest, ALLOWED_IDS_ROOT};

    const RISC0_RECEIPT_META_DIGEST: &str =
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
            [23,250,144,90,188,98,158,62,214,76,108,236,158,31,125,183,20,200,101,254,212,15,32,174,120,230,219,15,71,206,189,55]],
        "public":[[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,104,228,45,139,61,220,73,159,78,23,153,167,103,5,42,179],
            [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,56,2,104,79,22,69,224,160,40,88,91,4,69,211,146,49],
            [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,207,29,214,20,178,62,196,218,167,244,197,95,239,64,43,255],
            [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,86,246,102,224,24,131,128,68,162,253,108,219,190,247,101,102]]
    }
    "#;

    const CIRCOM_VERIFICATION_KEY: &str = include_str!("data/circom/verification_key.json");
    const CIRCOM_PROOF: &str = include_str!("data/circom/proof.json");
    const CIRCOM_PUBLIC: &str = include_str!("data/circom/public.json");

    #[test]
    fn test_from_groth16_seal() {
        let seal: Groth16Seal = serde_json::from_str(RISC0_GROTH16_SEAL).unwrap();
        let groth16 = Groth16::from_seal(
            seal,
            Digest::from_hex(ALLOWED_IDS_ROOT).unwrap(),
            Digest::from_hex(RISC0_RECEIPT_META_DIGEST).unwrap(),
        )
        .unwrap();
        groth16.verify().unwrap();
    }

    #[test]
    fn test_from_raw() {
        let raw_vkey: RawVKey = serde_json::from_str(CIRCOM_VERIFICATION_KEY).unwrap();
        let raw_proof: RawProof = serde_json::from_str(CIRCOM_PROOF).unwrap();
        let raw_public = RawPublic {
            values: serde_json::from_str(CIRCOM_PUBLIC).unwrap(),
        };

        let groth16 = Groth16::from_raw(raw_vkey, raw_proof, raw_public).unwrap();
        groth16.verify().unwrap();
    }
}
