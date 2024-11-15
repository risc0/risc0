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

use risc0_bigint2_methods::{EC_ADD_ELF, EC_DOUBLE_ELF, NEGTEST_ELF};
use risc0_zkvm::{
    get_prover_server, ExecutorEnv, ExecutorImpl, ExitCode, ProverOpts, VerifierContext,
};
use test_log::test;

#[test]
fn ec_add() {
    let env = ExecutorEnv::builder().build().unwrap();
    let session = ExecutorImpl::from_elf(env, EC_ADD_ELF)
        .unwrap()
        .run()
        .unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));

    let prover = get_prover_server(&ProverOpts::fast()).unwrap();
    prover
        .prove_session(&VerifierContext::default(), &session)
        .unwrap();
}

#[test]
fn ec_double() {
    let env = ExecutorEnv::builder().build().unwrap();
    let session = ExecutorImpl::from_elf(env, EC_DOUBLE_ELF)
        .unwrap()
        .run()
        .unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));

    let prover = get_prover_server(&ProverOpts::fast()).unwrap();
    prover
        .prove_session(&VerifierContext::default(), &session)
        .unwrap();
}

#[test]
fn negtest() {
    let env = ExecutorEnv::builder().build().unwrap();
    let session = ExecutorImpl::from_elf(env, NEGTEST_ELF)
        .unwrap()
        .run()
        .unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));

    let prover = get_prover_server(&ProverOpts::fast()).unwrap();
    prover
        .prove_session(&VerifierContext::default(), &session)
        .unwrap();
}
