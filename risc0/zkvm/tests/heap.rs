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

#![cfg(feature = "prove")]

use risc0_zkvm::{get_prover_server, ExecutorEnv, ProverOpts};
use risc0_zkvm_methods::HEAP_LIMITS_ELF;

fn test_it(name: &str) -> anyhow::Error {
    let env = ExecutorEnv::builder()
        .write(&name)
        .unwrap()
        .build()
        .unwrap();

    let prover = get_prover_server(&ProverOpts::fast()).unwrap();

    prover.prove(env, HEAP_LIMITS_ELF).map(|_| ()).unwrap_err()
}

#[test]
fn heap_overflow_via_alloc() {
    let error = test_it("heap_overflow_via_alloc");
    assert!(
        error.to_string().contains("Guest panicked: Out of memory!"),
        "{error}"
    );
}

#[test]
fn heap_overflow_via_sys_alloc_aligned() {
    let error = test_it("heap_overflow_via_sys_alloc_aligned");
    assert!(
        error.to_string().contains("Guest panicked: Out of memory!"),
        "{error}"
    );
}
