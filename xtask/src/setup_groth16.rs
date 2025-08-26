// Copyright 2025 RISC Zero, Inc.
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

use std::path::PathBuf;

use clap::Parser;
use risc0_groth16_sys::{SetupParams, WitnessParams};
use rlimit::{INFINITY, Resource, setrlimit};
use xshell::{Shell, cmd};

#[derive(Debug, Parser)]
pub struct SetupGroth16 {
    #[arg(env)]
    dir: PathBuf,
}

const CIRCOM_WITNESSCALC_URL: &str = "https://github.com/iden3/circom-witnesscalc.git";
const CIRCOM_WITNESSCALC_COMMIT: &str = "b7ff0ffd9c72c8f60896ce131ee98a35aba96009"; // 0.2.1

impl SetupGroth16 {
    pub fn run(&self) {
        setrlimit(Resource::STACK, INFINITY, INFINITY).unwrap();

        let sh = Shell::new().unwrap();
        let work_dir = self.dir.canonicalize().unwrap();
        sh.change_dir(sh.create_dir(&work_dir).unwrap());

        let setup_dir = work_dir.join("v0.1.0-risc0-groth16");
        sh.create_dir(&setup_dir).unwrap();

        let setup_params = SetupParams::new(&setup_dir).unwrap();
        let witness_params = WitnessParams::new(&setup_dir);
        if !sh.path_exists(setup_params.srs_path.as_path()) {
            let mut zkey_gz_path = setup_params.srs_path.as_path().to_path_buf();
            zkey_gz_path.set_extension("zkey.gz");
            let url = "https://risc0-artifacts.s3.us-west-2.amazonaws.com/zkey/2024-05-17.1/stark_verify_final.zkey.gz";
            cmd!(sh, "curl -o {zkey_gz_path} {url}").run().unwrap();
            cmd!(sh, "gunzip {zkey_gz_path}").run().unwrap();
        }

        if !sh.path_exists("circom-witnesscalc") {
            cmd!(sh, "git clone {CIRCOM_WITNESSCALC_URL}")
                .run()
                .unwrap();
        }

        let build_circuit = "circom-witnesscalc/target/release/build-circuit";
        if !sh.path_exists(build_circuit) {
            let _cd = sh.push_dir("circom-witnesscalc");
            cmd!(sh, "git checkout {CIRCOM_WITNESSCALC_COMMIT}")
                .run()
                .unwrap();
            cmd!(sh, "cargo build --release -p build-circuit")
                .run()
                .unwrap();
        }

        let stark_verify_circom = std::env::current_dir()
            .unwrap()
            .join("groth16_proof/groth16/stark_verify.circom");
        if !sh.path_exists(&stark_verify_circom) {
            panic!(
                "Run from top of workspace. Could not find: {}",
                stark_verify_circom.display()
            );
        }

        // stark_verify.circom -> stark_verify_graph.bin
        let graph_path = &witness_params.graph_path;
        if !sh.path_exists(graph_path) {
            cmd!(sh, "{build_circuit} {stark_verify_circom} {graph_path}")
                .run()
                .unwrap();
        }

        // stark_verify_final.zkey -> (fuzzed_msm_results.bin, preprocessed_coeffs.bin)
        risc0_groth16_sys::setup(&setup_params).unwrap();
    }
}
