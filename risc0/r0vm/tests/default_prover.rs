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

use assert_cmd::cargo::cargo_bin;
use risc0_zkvm::{DefaultProver, ExecutorEnv, Prover as _};
use risc0_zkvm_methods::{FIB_ELF, FIB_ID};

#[test_log::test]
fn basic_proof() {
    let r0vm_path = cargo_bin("r0vm");
    let prover = DefaultProver::new(r0vm_path).unwrap();

    const ITERATIONS: u32 = 300_000;
    let env = ExecutorEnv::builder()
        .write(&ITERATIONS)
        .unwrap()
        .build()
        .unwrap();

    let receipt = prover.prove(env, FIB_ELF).unwrap().receipt;
    receipt.verify(FIB_ID).unwrap();
}
