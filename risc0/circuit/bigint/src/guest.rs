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

use anyhow::Result;
use risc0_zkvm::{guest::env, guest::sha::Impl as Sha256};
use risc0_zkvm_platform::syscall;

use crate::{claim_list_digest, generate_proof_input, BigIntClaim, BigIntProgram};

pub fn prove(prog: &BigIntProgram, claims: &[BigIntClaim]) -> Result<()> {
    let claim_digest = claim_list_digest::<Sha256>(prog, claims)?;

    env::run_unconstrained(|| {
        let input = generate_proof_input(claims, prog).unwrap();
        unsafe {
            syscall::sys_prove_zkr(
                claim_digest.as_ref(),
                prog.control_id.as_ref(),
                prog.control_root.as_ref(),
                input.as_ptr(),
                input.len(),
            );
        }
    });

    env::verify_assumption(claim_digest, prog.control_root)?;

    Ok(())
}
