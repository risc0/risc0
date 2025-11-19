// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use assert_cmd::cargo::cargo_bin;
use risc0_zkvm::{
    DefaultProver, Executor as _, ExecutorEnv, ExitCode, Prover as _, ProverOpts, VerifierContext,
};
use risc0_zkvm_methods::{FIB_ELF, FIB_ID};

#[cfg(feature = "rv32im-m3")]
const ITERATIONS: u32 = 800_000;

#[cfg(not(feature = "rv32im-m3"))]
const ITERATIONS: u32 = 300_000;

#[test_log::test]
#[cfg_attr(all(ci, not(ci_profile = "slow")), ignore = "slow test")]
#[gpu_guard::gpu_guard]
fn basic_proof() {
    let r0vm_path = cargo_bin("r0vm");
    let prover = DefaultProver::new(r0vm_path).unwrap();

    let env = ExecutorEnv::builder()
        .write(&ITERATIONS)
        .unwrap()
        .build()
        .unwrap();

    let ctx = VerifierContext::default();

    #[cfg(feature = "cuda")]
    let opts = ProverOpts::groth16();

    #[cfg(not(feature = "cuda"))]
    let opts = ProverOpts::default();

    let receipt = prover
        .prove_with_ctx(env, &ctx, FIB_ELF, &opts)
        .unwrap()
        .receipt;
    receipt.verify(FIB_ID).unwrap();
}

#[test_log::test]
fn basic_execute() {
    let r0vm_path = cargo_bin("r0vm");
    let prover = DefaultProver::new(r0vm_path).unwrap();

    let env = ExecutorEnv::builder()
        .write(&ITERATIONS)
        .unwrap()
        .build()
        .unwrap();

    let session_info = prover.execute(env, FIB_ELF).unwrap();
    assert_eq!(session_info.exit_code, ExitCode::Halted(0));
    assert!(session_info.segments.len() > 2);
    assert!(session_info.receipt_claim.is_some());
}
