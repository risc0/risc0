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

use std::{path::PathBuf, str::FromStr};

use anyhow::{Context, Result};
use risc0_binfmt::ProgramBinary;
use risc0_zkvm::{
    ApiClient, Asset, AssetRequest, Digest, ExecutorEnv, Groth16ReceiptVerifierParameters,
    ProverOpts, SuccinctReceiptVerifierParameters, VerifierContext, digest,
};
use risc0_zkvm_methods::{MULTI_TEST_ELF, multi_test::MultiTestSpec};
use rstest::rstest;

const OUT_DIR: &str = env!("OUT_DIR");

// https://github.com/risc0/risc0/blob/release-1.1/risc0/circuit/recursion/src/control_id.rs
mod control_ids_1_1_3 {
    use super::{Digest, digest};

    pub const ALLOWED_CONTROL_ROOT: Digest =
        digest!("8b6dcf11d463ac455361b41fb3ed053febb817491bdea00fdb340e45013b852e");

    pub const BN254_IDENTITY_CONTROL_ID: Digest =
        digest!("4e160df1e119ac0e3d658755a9edf38c8feb307b34bc10b57f4538dbe122a005");
}

// https://github.com/risc0/risc0/blob/release-1.2/risc0/circuit/recursion/src/control_id.rs
mod control_ids_1_2_2 {
    use super::{Digest, digest};

    pub const ALLOWED_CONTROL_ROOT: Digest =
        digest!("8cdad9242664be3112aba377c5425a4df735eb1c6966472b561d2855932c0469");

    pub const BN254_IDENTITY_CONTROL_ID: Digest =
        digest!("c07a65145c3cb48b6101962ea607a4dd93c753bb26975cb47feb00d3666e4404");
}

fn into_version(version: &str) -> Result<semver::Version> {
    if version == "main" {
        Ok(risc0_zkvm::get_version()?)
    } else {
        Ok(semver::Version::parse(version)?)
    }
}

fn verifier_context(version: semver::Version) -> Result<VerifierContext> {
    let cur_version = risc0_zkvm::get_version().context("Failed to get current version")?;
    if version.major == cur_version.major && version.minor == cur_version.minor {
        return Ok(VerifierContext::default());
    }

    let verifying_key = Groth16ReceiptVerifierParameters::default().verifying_key;

    // 1.0
    match version.minor {
        1 => Ok(VerifierContext::default()
            .with_succinct_verifier_parameters(SuccinctReceiptVerifierParameters {
                control_root: control_ids_1_1_3::ALLOWED_CONTROL_ROOT,
                inner_control_root: None,
                proof_system_info: risc0_zkp::adapter::PROOF_SYSTEM_INFO,
                // https://github.com/risc0/risc0/blob/release-1.1/risc0/circuit/recursion/src/info.rs#L23
                circuit_info: risc0_zkp::adapter::ProtocolInfo(*b"RECURSION:rev1v1"),
            })
            .with_groth16_verifier_parameters(Groth16ReceiptVerifierParameters {
                control_root: control_ids_1_1_3::ALLOWED_CONTROL_ROOT,
                bn254_control_id: control_ids_1_1_3::BN254_IDENTITY_CONTROL_ID,
                verifying_key,
            })),
        2 => {
            Ok(VerifierContext::default()
                .with_succinct_verifier_parameters(SuccinctReceiptVerifierParameters {
                    control_root: control_ids_1_2_2::ALLOWED_CONTROL_ROOT,
                    inner_control_root: None,
                    proof_system_info: risc0_zkp::adapter::PROOF_SYSTEM_INFO,
                    // https://github.com/risc0/risc0/blob/release-1.1/risc0/circuit/recursion/src/info.rs#L23
                    circuit_info: risc0_zkp::adapter::ProtocolInfo(*b"RECURSION:rev1v1"),
                })
                .with_groth16_verifier_parameters(Groth16ReceiptVerifierParameters {
                    control_root: control_ids_1_2_2::ALLOWED_CONTROL_ROOT,
                    bn254_control_id: control_ids_1_2_2::BN254_IDENTITY_CONTROL_ID,
                    verifying_key,
                }))
        }
        _ => anyhow::bail!("Unsupported risc0 minor version: {version:?}"),
    }
}

// Adapted from
// https://github.com/rust-lang/cargo/blob/485670b3983b52289a2f353d589c57fae2f60f82/tests/testsuite/support/mod.rs#L507
fn target_dir() -> PathBuf {
    std::env::current_exe()
        .ok()
        .map(|mut path| {
            path.pop();
            if path.ends_with("deps") {
                path.pop();
            }
            path
        })
        .expect("this should only be used where a `current_exe` can be set")
}

fn cargo_bin_str(name: &str) -> PathBuf {
    let env_var = format!("CARGO_BIN_EXE_{name}");
    std::env::var_os(env_var)
        .map(|p| p.into())
        .unwrap_or_else(|| target_dir().join(format!("{}{}", name, std::env::consts::EXE_SUFFIX)))
}

fn new_client(version: &str) -> ApiClient {
    let server_path = if version == "main" {
        cargo_bin_str("local-r0vm")
    } else {
        PathBuf::from_str(OUT_DIR)
            .unwrap()
            .join("install")
            .join(version)
            .join("bin/r0vm")
    };
    println!("path: {}", server_path.display());
    let semver = into_version(version).unwrap();
    ApiClient::new_sub_process_compat(server_path, semver).unwrap()
}

#[rstest]
#[case("1.1.3")]
#[case("1.2.2")]
#[case("main")]
#[test_log::test]
fn prove_lift(#[case] version: &str) {
    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::DoNothing)
        .unwrap()
        .build()
        .unwrap();

    let semver = into_version(version).unwrap();
    let binary = if semver.major == 1 {
        let binary = ProgramBinary::decode(MULTI_TEST_ELF).unwrap();
        Asset::Inline(binary.user_elf.into())
    } else {
        Asset::Inline(MULTI_TEST_ELF.into())
    };

    let client = new_client(version);

    let mut segments = vec![];
    let session = client
        .execute(&env, binary, AssetRequest::Inline, |_info, segment| {
            segments.push(segment);
            Ok(())
        })
        .unwrap();
    assert_eq!(session.segments.len(), 1);
    assert_eq!(segments.len(), 1);

    for segment in segments {
        let opts = ProverOpts::default();
        let segment_receipt = client
            .prove_segment(&opts, segment, AssetRequest::Inline)
            .unwrap();

        let succinct_receipt = client
            .lift(
                &opts,
                segment_receipt.try_into().unwrap(),
                AssetRequest::Inline,
            )
            .unwrap();

        let ctx = verifier_context(semver.clone()).unwrap();
        succinct_receipt
            .verify_integrity_with_context(&ctx)
            .unwrap();
    }
}
