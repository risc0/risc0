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

use risc0_zkvm::{default_executor, get_prover_server, ExecutorEnv, ExitCode, ProverOpts, Receipt};
use risc0_zkvm_methods::{multi_test::MultiTestSpec, MULTI_TEST_ELF, MULTI_TEST_ID, VERIFY_ELF};

#[cfg_attr(test, test)]
fn main() {
    tracing_subscriber::fmt()
        .with_env_filter(tracing_subscriber::EnvFilter::from_default_env())
        .init();

    let receipt = generate_receipt(&ProverOpts::default());
    exec_verify(&receipt);
}

fn generate_receipt(opts: &ProverOpts) -> Receipt {
    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::DoNothing)
        .unwrap()
        .build()
        .unwrap();
    let prover = get_prover_server(opts).unwrap();
    prover.prove(env, MULTI_TEST_ELF).unwrap().receipt
}

fn exec_verify(receipt: &Receipt) {
    let input = (receipt.clone(), MULTI_TEST_ID);
    let env = ExecutorEnv::builder()
        .write(&input)
        .unwrap()
        .build()
        .unwrap();
    let session = default_executor().execute(env, VERIFY_ELF).unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));
}
