// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use std::path::PathBuf;

use clap::Parser;
use memmap2::{Mmap, MmapMut};
use risc0_groth16_sys::SetupParams;
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

        let srs_path = setup_dir.join("stark_verify_final.zkey");
        if !sh.path_exists(srs_path.as_path()) {
            let mut zkey_gz_path = srs_path.as_path().to_path_buf();
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
        let graph_path = setup_dir.join("stark_verify_graph.bin");
        if !sh.path_exists(&graph_path) {
            cmd!(sh, "{build_circuit} {stark_verify_circom} {graph_path}")
                .run()
                .unwrap();
        }

        // stark_verify_final.zkey -> (fuzzed_msm_results.bin, preprocessed_coeffs.bin)
        let srs_file = std::fs::File::open(&srs_path).unwrap();

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
