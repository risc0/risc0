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

#[cfg(feature = "num-bigint-dig")]
extern crate num_bigint_dig as num_bigint;

use num_bigint::BigUint;

use risc0_bigint2_methods::{MODADD_ELF, MODINV_ELF, MODMUL_ELF, MODSUB_ELF};
use risc0_zkvm::{
    get_prover_server, ExecutorEnv, ExecutorImpl, ExitCode, ProverOpts, VerifierContext,
};
use std::time::Instant;
use test_log::test;

#[test]
fn modadd() {
    const LHS: &[u8] = b"04";
    const RHS: &[u8] = b"07";
    const MODULUS: &[u8] = b"03";
    const EXPECTED: &[u8] = b"02";

    let lhs = BigUint::parse_bytes(LHS, 16).unwrap();
    let rhs = BigUint::parse_bytes(RHS, 16).unwrap();
    let modulus = BigUint::parse_bytes(MODULUS, 16).unwrap();
    let expected = BigUint::parse_bytes(EXPECTED, 16).unwrap();

    let env = ExecutorEnv::builder()
            .write(&(lhs, rhs, modulus))
            .unwrap()
            .build()
            .unwrap();
    let now = Instant::now();
    let session = ExecutorImpl::from_elf(env, MODADD_ELF)
        .unwrap()
        .run()
        .unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));
    let result: BigUint = session.journal.as_ref().unwrap().decode().unwrap();
    assert_eq!(result, expected);

    let prover = get_prover_server(&ProverOpts::fast()).unwrap();
    let prove_info = prover
        .prove_session(&VerifierContext::default(), &session)
        .unwrap();
    let elapsed = now.elapsed();
    tracing::info!("Runtime: {}", elapsed.as_millis());
    tracing::info!("User cycles: {}", prove_info.stats.user_cycles);
}

#[test]
fn modinv() {
    const INP: &[u8] = b"02";
    const MODULUS: &[u8] = b"05";
    const EXPECTED: &[u8] = b"03";

    let inp = BigUint::parse_bytes(INP, 16).unwrap();
    let modulus = BigUint::parse_bytes(MODULUS, 16).unwrap();
    let expected = BigUint::parse_bytes(EXPECTED, 16).unwrap();

    let env = ExecutorEnv::builder()
            .write(&(inp, modulus))
            .unwrap()
            .build()
            .unwrap();
    let now = Instant::now();
    let session = ExecutorImpl::from_elf(env, MODINV_ELF)
        .unwrap()
        .run()
        .unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));
    let result: BigUint = session.journal.as_ref().unwrap().decode().unwrap();
    assert_eq!(result, expected);

    let prover = get_prover_server(&ProverOpts::fast()).unwrap();
    let prove_info = prover
        .prove_session(&VerifierContext::default(), &session)
        .unwrap();
    let elapsed = now.elapsed();
    tracing::info!("Runtime: {}", elapsed.as_millis());
    tracing::info!("User cycles: {}", prove_info.stats.user_cycles);
}

#[test]
fn modmul() {
    // TODO: I think we have problems if modulus isn't the full bitwidth
    const LHS: &[u8] = b"04";
    const RHS: &[u8] = b"07";
    const MODULUS: &[u8] = b"05";
    const EXPECTED: &[u8] = b"03";

    let lhs = BigUint::parse_bytes(LHS, 16).unwrap();
    let rhs = BigUint::parse_bytes(RHS, 16).unwrap();
    let modulus = BigUint::parse_bytes(MODULUS, 16).unwrap();
    let expected = BigUint::parse_bytes(EXPECTED, 16).unwrap();

    let env = ExecutorEnv::builder()
            .write(&(lhs, rhs, modulus))
            .unwrap()
            .build()
            .unwrap();
    let now = Instant::now();
    let session = ExecutorImpl::from_elf(env, MODMUL_ELF)
        .unwrap()
        .run()
        .unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));
    let result: BigUint = session.journal.as_ref().unwrap().decode().unwrap();
    assert_eq!(result, expected);

    let prover = get_prover_server(&ProverOpts::fast()).unwrap();
    let prove_info = prover
        .prove_session(&VerifierContext::default(), &session)
        .unwrap();
    let elapsed = now.elapsed();
    tracing::info!("Runtime: {}", elapsed.as_millis());
    tracing::info!("User cycles: {}", prove_info.stats.user_cycles);
}

#[test]
fn modsub() {
    const LHS: &[u8] = b"04";
    const RHS: &[u8] = b"07";
    const MODULUS: &[u8] = b"05";
    const EXPECTED: &[u8] = b"02";

    let lhs = BigUint::parse_bytes(LHS, 16).unwrap();
    let rhs = BigUint::parse_bytes(RHS, 16).unwrap();
    let modulus = BigUint::parse_bytes(MODULUS, 16).unwrap();
    let expected = BigUint::parse_bytes(EXPECTED, 16).unwrap();

    let env = ExecutorEnv::builder()
            .write(&(lhs, rhs, modulus))
            .unwrap()
            .build()
            .unwrap();
    let now = Instant::now();
    let session = ExecutorImpl::from_elf(env, MODSUB_ELF)
        .unwrap()
        .run()
        .unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));
    let result: BigUint = session.journal.as_ref().unwrap().decode().unwrap();
    assert_eq!(result, expected);

    let prover = get_prover_server(&ProverOpts::fast()).unwrap();
    let prove_info = prover
        .prove_session(&VerifierContext::default(), &session)
        .unwrap();
    let elapsed = now.elapsed();
    tracing::info!("Runtime: {}", elapsed.as_millis());
    tracing::info!("User cycles: {}", prove_info.stats.user_cycles);
}
