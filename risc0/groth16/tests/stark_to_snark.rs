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

#[cfg(feature = "prove")]
#[test]
fn stark2snark() {
    use risc0_groth16::docker::stark_to_snark;
    use risc0_zkvm::{
        get_prover_server, recursion::identity_p254, CompactReceipt, ExecutorEnv, ExecutorImpl,
        InnerReceipt, ProverOpts, Receipt, VerifierContext,
    };
    use risc0_zkvm_methods::multi_test::MultiTestSpec;
    use risc0_zkvm_methods::{MULTI_TEST_ELF, MULTI_TEST_ID};

    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::BusyLoop { cycles: 0 })
        .unwrap()
        .build()
        .unwrap();

    tracing::info!("execute");

    let mut exec = ExecutorImpl::from_elf(env, MULTI_TEST_ELF).unwrap();
    let session = exec.run().unwrap();

    tracing::info!("prove");
    let opts = ProverOpts::default();
    let ctx = VerifierContext::default();
    let prover = get_prover_server(&opts).unwrap();
    let receipt = prover.prove_session(&ctx, &session).unwrap();
    let claim = receipt.get_claim().unwrap();
    let succinct_receipt = receipt.inner.succinct().unwrap();
    let journal = session.journal.unwrap().bytes;

    tracing::info!("identity_p254");
    let ident_receipt = identity_p254(&succinct_receipt).unwrap();
    let seal_bytes = ident_receipt.get_seal_bytes();

    tracing::info!("stark-to-snark");
    let seal = stark_to_snark(&seal_bytes).unwrap().to_vec();

    tracing::info!("Receipt");
    let receipt = Receipt::new(
        InnerReceipt::Compact(CompactReceipt { seal, claim }),
        journal,
    );

    receipt.verify(MULTI_TEST_ID).unwrap();
}
