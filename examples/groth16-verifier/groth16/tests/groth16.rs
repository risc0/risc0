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
