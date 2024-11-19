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

use risc0_bigint2_methods::{EC_ADD_ELF, EC_DOUBLE_ELF, EC_MUL_ELF};
use risc0_zkvm::{
    get_prover_server, ExecutorEnv, ExecutorImpl, ExitCode, ProverOpts, VerifierContext,
};
use std::time::Instant;
use test_log::test;

#[test]
fn ec_add() {
    let env = ExecutorEnv::builder().build().unwrap();
    let now = Instant::now();
    let session = ExecutorImpl::from_elf(env, EC_ADD_ELF)
        .unwrap()
        .run()
        .unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));

    let prover = get_prover_server(&ProverOpts::fast()).unwrap();
    let prove_info = prover
        .prove_session(&VerifierContext::default(), &session)
        .unwrap();
    let elapsed = now.elapsed();
    println!("Runtime: {}", elapsed.as_millis());
    println!("User cycles: {}", prove_info.stats.user_cycles);
}

#[test]
fn ec_double() {
    let env = ExecutorEnv::builder().build().unwrap();
    let now = Instant::now();
    let session = ExecutorImpl::from_elf(env, EC_DOUBLE_ELF)
        .unwrap()
        .run()
        .unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));

    let prover = get_prover_server(&ProverOpts::fast()).unwrap();
    let prove_info = prover
        .prove_session(&VerifierContext::default(), &session)
        .unwrap();
    let elapsed = now.elapsed();
    println!("Runtime: {}", elapsed.as_millis());
    println!("User cycles: {}", prove_info.stats.user_cycles);
}

#[test]
fn ec_mul() {
    let env = ExecutorEnv::builder().build().unwrap();
    let now = Instant::now();
    let session = ExecutorImpl::from_elf(env, EC_MUL_ELF)
        .unwrap()
        .run()
        .unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));

    let prover = get_prover_server(&ProverOpts::fast()).unwrap();
    let prove_info = prover
        .prove_session(&VerifierContext::default(), &session)
        .unwrap();
    let elapsed = now.elapsed();
    println!("Runtime: {}", elapsed.as_millis());
    println!("User cycles: {}", prove_info.stats.user_cycles);
}
