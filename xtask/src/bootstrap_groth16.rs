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

use std::{fs, process::Command};

use clap::Parser;
use regex::Regex;

#[derive(Parser)]
pub struct BootstrapGroth16;

const SOLIDITY_GROTH16_VERIFIER_PATH: &str =
    "bonsai/ethereum/contracts/groth16/Groth16Verifier.sol";
const RUST_GROTH16_VERIFIER_PATH: &str = "risc0/zkvm/src/host/groth16.rs";

impl BootstrapGroth16 {
    pub fn run(&self) {
        let solidity_code = fs::read_to_string(SOLIDITY_GROTH16_VERIFIER_PATH).expect(
            format!(
                "failed to read the Solidity verifier from {}",
                SOLIDITY_GROTH16_VERIFIER_PATH
            )
            .as_str(),
        );
        let mut rust_code = fs::read_to_string(RUST_GROTH16_VERIFIER_PATH).expect(
            format!(
                "failed to read groth16.rs from {}",
                RUST_GROTH16_VERIFIER_PATH
            )
            .as_str(),
        );

        let solidity_constants = [
            "alphax", "alphay", "betax1", "betax2", "betay1", "betay2", "gammax1", "gammax2",
            "gammay1", "gammay2", "deltax1", "deltax2", "deltay1", "deltay2", "IC0x", "IC0y",
            "IC1x", "IC1y", "IC2x", "IC2y", "IC3x", "IC3y", "IC4x", "IC4y",
        ];

        let rust_constants = [
            "ALPHA_X", "ALPHA_Y", "BETA_X1", "BETA_X2", "BETA_Y1", "BETA_Y2", "GAMMA_X1",
            "GAMMA_X2", "GAMMA_Y1", "GAMMA_Y2", "DELTA_X1", "DELTA_X2", "DELTA_Y1", "DELTA_Y2",
            "IC0_X", "IC0_Y", "IC1_X", "IC1_Y", "IC2_X", "IC2_Y", "IC3_X", "IC3_Y", "IC4_X",
            "IC4_Y",
        ];

        for (i, constant) in solidity_constants.into_iter().enumerate() {
            let re = Regex::new(&format!(r"uint256 constant\s+{}\s*=\s*(\d+);", constant)).unwrap();
            if let Some(caps) = re.captures(&solidity_code) {
                let rust_re = Regex::new(&format!(
                    "const {}: &str =[\\r\\n\\s]*\"\\d+\";",
                    rust_constants[i]
                ))
                .unwrap();
                rust_code = rust_re
                    .replace(
                        &rust_code,
                        &format!("const {}: &str = \"{}\";", rust_constants[i], &caps[1]),
                    )
                    .to_string();
            } else {
                println!("{} not found", constant);
            }
        }

        fs::write(RUST_GROTH16_VERIFIER_PATH, rust_code)
            .expect(format!("failed to save changes to {}", RUST_GROTH16_VERIFIER_PATH).as_str());

        // Use rustfmt to format the file.
        Command::new("rustfmt")
            .arg(RUST_GROTH16_VERIFIER_PATH)
            .status()
            .expect("failed to format {RUST_GROTH16_VERIFIER_PATH}");
    }
}
