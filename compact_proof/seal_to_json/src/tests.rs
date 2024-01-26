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

use std::{fs::File, io::Cursor, path::Path, process::Command};

use risc0_zkvm_methods::{multi_test::MultiTestSpec, MULTI_TEST_ELF, MULTI_TEST_ID};
use tempfile::tempdir;
use test_log::test;

use risc0_zkvm::{
    get_prover_server,
    recursion::{identity_p254, lift},
    ExecutorEnv, ExecutorImpl, Groth16Receipt, Groth16Seal, InnerReceipt, ProverOpts, Receipt,
    VerifierContext,
};

#[test]
fn stark2snark() {
    let tmp_dir = tempdir().expect("Failed to create tmpdir");
    let work_dir = std::env::var("RISC0_WORK_DIR");
    let work_dir = work_dir
        .as_ref()
        .map(|x| Path::new(x))
        .unwrap_or(tmp_dir.path());

    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::BusyLoop { cycles: 0 })
        .unwrap()
        .build()
        .unwrap();

    tracing::info!("execute");
    let mut exec = ExecutorImpl::from_elf(env, MULTI_TEST_ELF).unwrap();
    let session = exec.run().unwrap();
    assert_eq!(session.segments.len(), 1);
    let segment = session.segments.first().unwrap().resolve().unwrap();

    tracing::info!("prove");
    let opts = ProverOpts::default();
    let ctx = VerifierContext::default();
    let prover = get_prover_server(&opts).unwrap();
    let segment_receipt = prover.prove_segment(&ctx, &segment).unwrap();

    tracing::info!("lift");
    let lift_receipt = lift(&segment_receipt).unwrap();
    lift_receipt.verify_integrity().unwrap();

    tracing::info!("identity_p254");
    let ident_receipt = identity_p254(&lift_receipt).unwrap();
    let seal_bytes = ident_receipt.get_seal_bytes();

    std::fs::write(work_dir.join("seal.r0"), &seal_bytes).unwrap();

    let journal = session.journal.unwrap().bytes;
    let succinct_receipt = Receipt::new(InnerReceipt::Succinct(ident_receipt), journal.clone());
    // NOTE: verifying an identity_p254 receipt in rust is not supported at the moment.
    // succinct_receipt.verify(MULTI_TEST_ID).unwrap();

    tracing::info!("seal-to-json");
    let seal_path = work_dir.join("input.json");
    let snark_path = work_dir.join("output.json");
    let seal_json = File::create(&seal_path).unwrap();
    let mut seal_reader = Cursor::new(&seal_bytes);
    super::to_json(&mut seal_reader, &seal_json).unwrap();

    tracing::info!("risc0-groth16-prover");
    let status = Command::new("docker")
        .arg("run")
        .arg("--rm")
        .arg("-v")
        .arg(&format!("{}:/mnt", work_dir.to_string_lossy()))
        .arg("risc0-groth16-prover")
        .status()
        .unwrap();
    if !status.success() {
        panic!("docker returned failure exit code: {:?}", status.code());
    }

    let snark_str = std::fs::read_to_string(snark_path).unwrap();
    tracing::info!("{snark_str}");
    let snark_str = format!("[{snark_str}]"); // make the output valid json
    let raw_proof: (Vec<String>, Vec<Vec<String>>, Vec<String>, Vec<String>) =
        serde_json::from_str(&snark_str).unwrap();

    tracing::info!("decode a");
    let a: Result<Vec<Vec<u8>>, hex::FromHexError> = raw_proof
        .0
        .into_iter()
        .map(|x| hex::decode(&x[2..]))
        .collect();
    let a = a.expect("Failed to decode snark 'a' values");

    tracing::info!("decode b");
    let b: Result<Vec<Vec<Vec<u8>>>, hex::FromHexError> = raw_proof
        .1
        .into_iter()
        .map(|inner| {
            inner
                .into_iter()
                .map(|x| hex::decode(&x[2..]))
                .collect::<Result<Vec<Vec<u8>>, hex::FromHexError>>()
        })
        .collect();
    let b = b.expect("Failed to decode snark 'b' values");

    tracing::info!("decode c");
    let c: Result<Vec<Vec<u8>>, hex::FromHexError> = raw_proof
        .2
        .into_iter()
        .map(|x| hex::decode(&x[2..]))
        .collect();
    let c = c.expect("Failed to decode snark 'c' values");

    tracing::info!("Groth16Seal");
    let groth16_seal = Groth16Seal { a, b, c };
    let receipt = Receipt::new(
        InnerReceipt::Groth16(Groth16Receipt {
            seal: groth16_seal.to_vec(),
            claim: succinct_receipt.get_claim().unwrap(),
        }),
        journal,
    );

    receipt.verify(MULTI_TEST_ID).unwrap();
}
