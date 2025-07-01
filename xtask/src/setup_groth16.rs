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
use risc0_groth16_sys::SetupParams;
use xshell::{cmd, Shell};

#[derive(Debug, Parser)]
pub struct SetupGroth16 {
    #[arg(env)]
    dir: PathBuf,
}

impl SetupGroth16 {
    pub fn run(&self) {
        let sh = Shell::new().unwrap();
        sh.change_dir(sh.create_dir(&self.dir).unwrap());

        let setup_dir = self.dir.join("v0.1.0-risc0-groth16");
        sh.create_dir(&setup_dir).unwrap();

        let params = SetupParams::new(&setup_dir).unwrap();
        if !sh.path_exists(params.srs_path.as_path()) {
            let mut zkey_gz_path = params.srs_path.as_path().to_path_buf();
            zkey_gz_path.set_extension("zkey.gz");
            let url = "https://risc0-artifacts.s3.us-west-2.amazonaws.com/zkey/2024-05-17.1/stark_verify_final.zkey.gz";
            cmd!(sh, "curl -o {zkey_gz_path} {url}").run().unwrap();
            cmd!(sh, "gunzip {zkey_gz_path}").run().unwrap();
        }

        let build_circuit = "circom-witnesscalc/target/release/build-circuit";
        let calc_parallel_graph_bn254 =
            "circom-witnesscalc/target/release/calc-parallel-graph-bn254";

        if !sh.path_exists("circom-witnesscalc") {
            cmd!(
                sh,
                "git clone https://github.com/supranational/circom-witnesscalc.git"
            )
            .run()
            .unwrap();
        }

        if !sh.path_exists(build_circuit) {
            let _cd = sh.push_dir("circom-witnesscalc");
            cmd!(sh, "cargo build --release").run().unwrap();
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

        let stark_verify_bin = self.dir.join("stark_verify_graph.bin");
        if !sh.path_exists(&stark_verify_bin) {
            // stark_verify.circom -> stark_verify_graph.bin
            cmd!(
                sh,
                "{build_circuit} {stark_verify_circom} {stark_verify_bin}"
            )
            .run()
            .unwrap();
        }

        let graph_path = params.graph_path.as_path();
        // stark_verify_graph.bin -> parallel-graph (directory)
        cmd!(
            sh,
            "{calc_parallel_graph_bn254} {stark_verify_bin} {graph_path} 32"
        )
        .run()
        .unwrap();

        // stark_verify_final.zkey -> (fuzzed_msm_results.bin, preprocessed_coeffs.bin)
        risc0_groth16_sys::setup(&params).unwrap();
    }
}
