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

use clap::Parser;
use rlimit::{INFINITY, Resource, setrlimit};
use std::path::PathBuf;
use xshell::{Shell, cmd};

const CIRCOM_WITNESSCALC_URL: &str = "https://github.com/iden3/circom-witnesscalc.git";
const CIRCOM_WITNESSCALC_COMMIT: &str = "b7ff0ffd9c72c8f60896ce131ee98a35aba96009"; // 0.2.1

const RISC0_TO_BITVM2_URL: &str = "https://github.com/ec2/risc0-to-bitvm2-boundless.git";
const RISC0_TO_BITVM2_COMMIT: &str = "b47483ae7ff2bbfbf6d4448bac76aa26afc80e47";

const CIRCOMLIB_URL: &str = "https://github.com/iden3/circomlib.git";
const CIRCOMLIB_COMMIT: &str = "35e54ea21da3e8762557234298dbb553c175ea8d";

#[derive(Debug, Parser)]
pub struct SetupBlake3Groth16 {
    /// Directory to store Groth16 setup files
    dir: PathBuf,
}

const CIRCUIT_FILES: &[&str] = &[
    "blake3_common.circom",
    "blake3_compression.circom",
    "risc0.circom",
    "stark_verify.circom",
    "verify_for_guest.circom",
];

fn download_circuits(sh: &Shell) {
    if !sh.path_exists("risc0-to-bitvm2") {
        cmd!(sh, "git clone {RISC0_TO_BITVM2_URL} risc0-to-bitvm2")
            .run()
            .unwrap();
    }
    {
        let _cd = sh.push_dir("risc0-to-bitvm2");
        cmd!(sh, "git checkout {RISC0_TO_BITVM2_COMMIT}")
            .run()
            .unwrap();
        cmd!(sh, "git lfs pull").run().unwrap();
    }
    sh.create_dir("groth16_proof").unwrap();
    sh.create_dir("groth16_proof/circuits").unwrap();
    // Copy circuit files every time because we modify stark_verify.circom
    for file in CIRCUIT_FILES {
        let src = format!("risc0-to-bitvm2/groth16_proof/circuits/{file}");
        let dst = format!("groth16_proof/circuits/{file}");
        sh.copy_file(&src, &dst).unwrap();
    }
    // Delete the last line of stark_verify.circom so that we only use its template
    cmd!(
        sh,
        "sed -i '$d' ./groth16_proof/circuits/stark_verify.circom"
    )
    .run()
    .unwrap();
}

impl SetupBlake3Groth16 {
    pub fn run(&self) {
        tracing::info!("Setting up Groth16 in {}", self.dir.display());
        setrlimit(Resource::STACK, INFINITY, INFINITY).unwrap();
        let sh = Shell::new().unwrap();

        let setup_dir = sh.create_dir(&self.dir).unwrap();

        let srs_path = setup_dir.join("verify_for_guest_final.zkey");

        if !sh.path_exists(srs_path.as_path()) {
            let zkey_path = srs_path.as_path().to_path_buf();
            let url = "https://static.testnet.citrea.xyz/conf/verify_for_guest_final.zkey";
            cmd!(sh, "curl -o {zkey_path} {url}").run().unwrap();
        }

        sh.change_dir(&setup_dir);

        download_circuits(&sh);

        if !sh.path_exists("circom-witnesscalc") {
            cmd!(sh, "git clone {CIRCOM_WITNESSCALC_URL}")
                .run()
                .unwrap();
        }

        if !sh.path_exists("circomlib") {
            cmd!(sh, "git clone {CIRCOMLIB_URL}").run().unwrap();
        }
        {
            let _cd = sh.push_dir("circomlib");
            cmd!(sh, "git checkout {CIRCOMLIB_COMMIT}").run().unwrap();
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

        let stark_verify_circom = setup_dir.join("groth16_proof/circuits/verify_for_guest.circom");
        if !sh.path_exists(&stark_verify_circom) {
            panic!(
                "Run from top of workspace. Could not find: {}",
                stark_verify_circom.display()
            );
        }

        let graph_path = setup_dir.join("verify_for_guest_graph.bin");
        // verify_for_guest.circom -> verify_for_guest_graph.bin
        if !sh.path_exists(graph_path.as_path()) {
            cmd!(sh, "{build_circuit} {stark_verify_circom} {graph_path}")
                .run()
                .unwrap();
        }

        let verifier_sol_path = setup_dir.join("verifier.sol");
        if !sh.path_exists(verifier_sol_path.as_path()) {
            tracing::info!(
                "Exporting Solidity verifier to {}",
                verifier_sol_path.display()
            );
            // Export Solidity verifier
            cmd!(
                sh,
                "snarkjs zkey export solidityverifier {srs_path} {verifier_sol_path}"
            )
            .run()
            .unwrap();
        }

        #[cfg(feature = "cuda")]
        {
            use memmap2::{Mmap, MmapMut};
            use risc0_groth16_sys::SetupParams;
            tracing::info!("Setting up Groth16 with CUDA");
            let srs_file = std::fs::File::open(&srs_path).unwrap();
            // verify_for_guest_final.zkey -> (fuzzed_msm_results.bin, preprocessed_coeffs.bin)

            let fuzzed_results_file = std::fs::OpenOptions::new()
                .read(true)
                .write(true)
                .create(true)
                .truncate(true)
                .open(setup_dir.join("fuzzed_msm_results.bin"))
                .unwrap();
            fuzzed_results_file.set_len(1024).unwrap();

            let preprocessed_coeffs_file = std::fs::OpenOptions::new()
                .read(true)
                .write(true)
                .create(true)
                .truncate(true)
                .open(setup_dir.join("preprocessed_coeffs.bin"))
                .unwrap();
            preprocessed_coeffs_file
                .set_len(2 * 1024 * 1024 * 1024)
                .unwrap();

            let (fuzzed_results_size, preprocessed_coeffs_size) = {
                let srs = unsafe { Mmap::map(&srs_file).unwrap() };
                let mut fuzzed_results = unsafe { MmapMut::map_mut(&fuzzed_results_file).unwrap() };
                let mut preprocessed_coeffs =
                    unsafe { MmapMut::map_mut(&preprocessed_coeffs_file).unwrap() };
                let mut setup_params = SetupParams {
                    srs: &srs[..],
                    fuzzed_results_out: &mut fuzzed_results[..],
                    preprocessed_coeffs_out: &mut preprocessed_coeffs[..],
                };
                risc0_groth16_sys::setup(&mut setup_params).unwrap()
            };
            fuzzed_results_file
                .set_len(fuzzed_results_size as u64)
                .unwrap();
            preprocessed_coeffs_file
                .set_len(preprocessed_coeffs_size as u64)
                .unwrap();
        }
    }
}
