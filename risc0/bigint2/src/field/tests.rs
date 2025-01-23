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

#[cfg(feature = "num-bigint-dig")]
extern crate num_bigint_dig as num_bigint;

use num_bigint::BigUint;

use risc0_bigint2_methods::{
    EXTFIELDADD_ELF, EXTFIELDMUL_ELF, EXTFIELDSUB_ELF, EXTFIELD_DEG4_MUL_ELF,
    EXTFIELD_XXONE_MUL_ELF, MODADD_ELF, MODINV_ELF, MODMUL_ELF, MODSUB_ELF,
};
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

#[test]
fn extfieldadd() {
    const LHS0: &[u8] = b"04";
    const LHS1: &[u8] = b"06";
    const RHS0: &[u8] = b"03";
    const RHS1: &[u8] = b"04";
    const PRIME: &[u8] = b"07";
    const EXPECTED0: &[u8] = b"00";
    const EXPECTED1: &[u8] = b"03";

    let lhs0 = BigUint::parse_bytes(LHS0, 16).unwrap();
    let lhs1 = BigUint::parse_bytes(LHS1, 16).unwrap();
    let rhs0 = BigUint::parse_bytes(RHS0, 16).unwrap();
    let rhs1 = BigUint::parse_bytes(RHS1, 16).unwrap();
    let prime = BigUint::parse_bytes(PRIME, 16).unwrap();
    let expected0 = BigUint::parse_bytes(EXPECTED0, 16).unwrap();
    let expected1 = BigUint::parse_bytes(EXPECTED1, 16).unwrap();
    let expected = (expected0, expected1);

    let env = ExecutorEnv::builder()
        .write(&(lhs0, lhs1, rhs0, rhs1, prime))
        .unwrap()
        .build()
        .unwrap();
    let now = Instant::now();
    let session = ExecutorImpl::from_elf(env, EXTFIELDADD_ELF)
        .unwrap()
        .run()
        .unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));
    let result: (BigUint, BigUint) = session.journal.as_ref().unwrap().decode().unwrap();
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
fn extfieldsub() {
    const LHS0: &[u8] = b"02";
    const LHS1: &[u8] = b"06";
    const RHS0: &[u8] = b"03";
    const RHS1: &[u8] = b"02";
    const PRIME: &[u8] = b"07";
    const EXPECTED0: &[u8] = b"06";
    const EXPECTED1: &[u8] = b"04";

    let lhs0 = BigUint::parse_bytes(LHS0, 16).unwrap();
    let lhs1 = BigUint::parse_bytes(LHS1, 16).unwrap();
    let rhs0 = BigUint::parse_bytes(RHS0, 16).unwrap();
    let rhs1 = BigUint::parse_bytes(RHS1, 16).unwrap();
    let prime = BigUint::parse_bytes(PRIME, 16).unwrap();
    let expected0 = BigUint::parse_bytes(EXPECTED0, 16).unwrap();
    let expected1 = BigUint::parse_bytes(EXPECTED1, 16).unwrap();
    let expected = (expected0, expected1);

    let env = ExecutorEnv::builder()
        .write(&(lhs0, lhs1, rhs0, rhs1, prime))
        .unwrap()
        .build()
        .unwrap();
    let now = Instant::now();
    let session = ExecutorImpl::from_elf(env, EXTFIELDSUB_ELF)
        .unwrap()
        .run()
        .unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));
    let result: (BigUint, BigUint) = session.journal.as_ref().unwrap().decode().unwrap();
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
fn extfieldmul() {
    // (2x+5)(3x+2) mod (xx+1) =
    //   6xx+4x+15x+10 = 6xx+5x+3 = 6(xx+0x+1)-0x-6 + 5x+3 = 5x+4
    const LHS0: &[u8] = b"05";
    const LHS1: &[u8] = b"02";
    const RHS0: &[u8] = b"02";
    const RHS1: &[u8] = b"03";
    const MONICIRR0: &[u8] = b"06";
    const MONICIRR1: &[u8] = b"00";
    const PRIME: &[u8] = b"07";
    const EXPECTED0: &[u8] = b"04";
    const EXPECTED1: &[u8] = b"05";

    let lhs0 = BigUint::parse_bytes(LHS0, 16).unwrap();
    let lhs1 = BigUint::parse_bytes(LHS1, 16).unwrap();
    let rhs0 = BigUint::parse_bytes(RHS0, 16).unwrap();
    let rhs1 = BigUint::parse_bytes(RHS1, 16).unwrap();
    let monicirr0 = BigUint::parse_bytes(MONICIRR0, 16).unwrap();
    let monicirr1 = BigUint::parse_bytes(MONICIRR1, 16).unwrap();
    let prime = BigUint::parse_bytes(PRIME, 16).unwrap();
    let expected0 = BigUint::parse_bytes(EXPECTED0, 16).unwrap();
    let expected1 = BigUint::parse_bytes(EXPECTED1, 16).unwrap();
    let expected = (expected0, expected1);

    let env = ExecutorEnv::builder()
        .write(&(lhs0, lhs1, rhs0, rhs1, monicirr0, monicirr1, prime))
        .unwrap()
        .build()
        .unwrap();
    let now = Instant::now();
    let session = ExecutorImpl::from_elf(env, EXTFIELDMUL_ELF)
        .unwrap()
        .run()
        .unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));
    let result: (BigUint, BigUint) = session.journal.as_ref().unwrap().decode().unwrap();
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
fn extfield_xxone_mul() {
    // (5x+5)(2x+2) mod (xx+1) =
    //   10xx+10x+10x+10 = 10xx+20x+10 = 10(xx+1)-10 + 6x+3 = 6x+0
    const LHS0: &[u8] = b"05";
    const LHS1: &[u8] = b"05";
    const RHS0: &[u8] = b"02";
    const RHS1: &[u8] = b"02";
    const PRIME: &[u8] = b"07";
    const PRIMESQR: &[u8] = b"31";
    const EXPECTED0: &[u8] = b"00";
    const EXPECTED1: &[u8] = b"06";

    let lhs0 = BigUint::parse_bytes(LHS0, 16).unwrap();
    let lhs1 = BigUint::parse_bytes(LHS1, 16).unwrap();
    let rhs0 = BigUint::parse_bytes(RHS0, 16).unwrap();
    let rhs1 = BigUint::parse_bytes(RHS1, 16).unwrap();
    let prime = BigUint::parse_bytes(PRIME, 16).unwrap();
    let primesqr = BigUint::parse_bytes(PRIMESQR, 16).unwrap();
    let expected0 = BigUint::parse_bytes(EXPECTED0, 16).unwrap();
    let expected1 = BigUint::parse_bytes(EXPECTED1, 16).unwrap();
    let expected = (expected0, expected1);

    let env = ExecutorEnv::builder()
        .write(&(lhs0, lhs1, rhs0, rhs1, prime, primesqr))
        .unwrap()
        .build()
        .unwrap();
    let now = Instant::now();
    let session = ExecutorImpl::from_elf(env, EXTFIELD_XXONE_MUL_ELF)
        .unwrap()
        .run()
        .unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));
    let result: (BigUint, BigUint) = session.journal.as_ref().unwrap().decode().unwrap();
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
fn extfield_deg4_mul() {
    // (4xxx + 2xx + 5x +4)(2xxx + 6xx + 6x + 3) mod (x^4 + 1) =
    //   8x^6 + 24x^5 + 24x^4 + 12xxx +
    //   4x^5 + 12x^4 + 12xxx + 6xx +
    //   10x^4 + 30xxx + 30xx + 15x +
    //   8xxx + 24xx + 24x + 12 ==
    //   1x^6 + 0x^5 + 3x^4 + 6xxx + 4xx + 4x + 5 ==
    //   xx(x^4+1)-xx + 3(x^4+1)-3 + 6xxx + 4xx + 4x + 5 ==
    //   -xx - 3 + 6xxx + 4xx + 4x + 4 == 6xxx + 3xx + 4x + 1
    const LHS0: &[u8] = b"04";
    const LHS1: &[u8] = b"05";
    const LHS2: &[u8] = b"02";
    const LHS3: &[u8] = b"04";
    const RHS0: &[u8] = b"03";
    const RHS1: &[u8] = b"06";
    const RHS2: &[u8] = b"06";
    const RHS3: &[u8] = b"02";
    const MONICIRR0: &[u8] = b"06";
    const MONICIRR1: &[u8] = b"00";
    const MONICIRR2: &[u8] = b"00";
    const MONICIRR3: &[u8] = b"00";
    const PRIME: &[u8] = b"07";
    const EXPECTED0: &[u8] = b"01";
    const EXPECTED1: &[u8] = b"04";
    const EXPECTED2: &[u8] = b"03";
    const EXPECTED3: &[u8] = b"06";

    let lhs0 = BigUint::parse_bytes(LHS0, 16).unwrap();
    let lhs1 = BigUint::parse_bytes(LHS1, 16).unwrap();
    let lhs2 = BigUint::parse_bytes(LHS2, 16).unwrap();
    let lhs3 = BigUint::parse_bytes(LHS3, 16).unwrap();
    let rhs0 = BigUint::parse_bytes(RHS0, 16).unwrap();
    let rhs1 = BigUint::parse_bytes(RHS1, 16).unwrap();
    let rhs2 = BigUint::parse_bytes(RHS2, 16).unwrap();
    let rhs3 = BigUint::parse_bytes(RHS3, 16).unwrap();
    let monicirr0 = BigUint::parse_bytes(MONICIRR0, 16).unwrap();
    let monicirr1 = BigUint::parse_bytes(MONICIRR1, 16).unwrap();
    let monicirr2 = BigUint::parse_bytes(MONICIRR2, 16).unwrap();
    let monicirr3 = BigUint::parse_bytes(MONICIRR3, 16).unwrap();
    let prime = BigUint::parse_bytes(PRIME, 16).unwrap();
    let expected0 = BigUint::parse_bytes(EXPECTED0, 16).unwrap();
    let expected1 = BigUint::parse_bytes(EXPECTED1, 16).unwrap();
    let expected2 = BigUint::parse_bytes(EXPECTED2, 16).unwrap();
    let expected3 = BigUint::parse_bytes(EXPECTED3, 16).unwrap();
    let expected = (expected0, expected1, expected2, expected3);

    let env = ExecutorEnv::builder()
        .write(&(
            lhs0, lhs1, lhs2, lhs3, rhs0, rhs1, rhs2, rhs3, monicirr0, monicirr1, monicirr2,
            monicirr3, prime,
        ))
        .unwrap()
        .build()
        .unwrap();
    let now = Instant::now();
    let session = ExecutorImpl::from_elf(env, EXTFIELD_DEG4_MUL_ELF)
        .unwrap()
        .run()
        .unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));
    let result: (BigUint, BigUint, BigUint, BigUint) =
        session.journal.as_ref().unwrap().decode().unwrap();
    assert_eq!(result, expected);

    let prover = get_prover_server(&ProverOpts::fast()).unwrap();
    let prove_info = prover
        .prove_session(&VerifierContext::default(), &session)
        .unwrap();
    let elapsed = now.elapsed();
    tracing::info!("Runtime: {}", elapsed.as_millis());
    tracing::info!("User cycles: {}", prove_info.stats.user_cycles);
}
