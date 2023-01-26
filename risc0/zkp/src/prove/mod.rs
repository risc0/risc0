// Copyright 2023 RISC Zero, Inc.
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

//! Cryptographic algorithms for producing a ZK proof of compute
//!
//! This module is not typically used directly. Instead, we recommend the
//! higher-level tools offered in [`risc0_zkvm::prove`].
//!
//! [`risc0_zkvm::prove`]: https://docs.rs/risc0-zkvm/latest/risc0_zkvm/prove/index.html

mod accum;
pub mod adapter;
pub mod executor;
mod fri;
mod merkle;
pub mod poly_group;
pub mod prover;
pub mod write_iop;

use alloc::vec::Vec;

use log::debug;
pub use prover::Prover;

use self::adapter::ProveAdapter;
use crate::{
    adapter::{CircuitDef, CircuitStepHandler},
    core::sha::Sha,
    field::Field,
    hal::{EvalCheck, Hal},
    prove::write_iop::WriteIOP,
    taps::{REGISTER_GROUP_ACCUM, REGISTER_GROUP_CODE, REGISTER_GROUP_DATA},
    MAX_CYCLES_PO2,
};

/// INSECURELY execute a circuit without producing a seal that proves execution
pub fn prove_without_seal<'a, F, S, C, CS>(sha: &S, circuit: &mut ProveAdapter<'a, F, C, CS>)
where
    F: Field,
    S: Sha,
    C: CircuitDef<F>,
    CS: CircuitStepHandler<F::Elem>,
{
    let mut iop = WriteIOP::new(sha);
    circuit.execute(&mut iop);
}

/// Construct a seal proving execution

// TODO: Deprecate this in favor of having each layer on top of zkp
// (like zkvm) figure out which buffers they needs and which order to
// use them in.  They can then depend on the "Prover" object directly.
#[tracing::instrument(skip_all)]
pub fn prove<'a, F, H, S, E, C, CS>(
    hal: &H,
    sha: &S,
    circuit: &mut ProveAdapter<'a, F, C, CS>,
    eval: &E,
) -> Vec<u32>
where
    F: Field,
    H: Hal<Elem = F::Elem, ExtElem = F::ExtElem>,
    S: Sha,
    E: EvalCheck<H>,
    C: CircuitDef<F>,
    CS: CircuitStepHandler<F::Elem>,
{
    // The taps are the entries of the trace used in evaluating the constraints.
    let taps = circuit.get_taps();

    // The number of columns used for encoding zkvm control instructions.
    let code_size = taps.group_size(REGISTER_GROUP_CODE);
    // The number of columns used for encoding the execution trace.
    let data_size = taps.group_size(REGISTER_GROUP_DATA);
    // The number of columns used for the PLOOKUP argument.
    let accum_size = taps.group_size(REGISTER_GROUP_ACCUM);
    debug!(
        "code: {code_size}/{}, data: {data_size}/{}, accum: {accum_size}/{}",
        circuit.get_code().len(),
        circuit.get_data().len(),
        circuit.get_accum().len()
    );

    let mut prover = Prover::new(hal, sha, taps);

    circuit.execute(prover.iop());

    // The log of the number of steps in the execution trace.
    let po2 = circuit.po2();
    assert!(po2 as usize <= MAX_CYCLES_PO2);
    let size = 1 << po2;
    prover.set_po2(po2 as usize);

    // Make code + data PolyGroups + commit them
    prover.commit_group(
        REGISTER_GROUP_CODE,
        hal.copy_from_elem("code", circuit.get_code()),
    );
    prover.commit_group(
        REGISTER_GROUP_DATA,
        hal.copy_from_elem("data", circuit.get_data()),
    );

    // Generates grand product accumulations for PLONK-style permutation arguments
    circuit.accumulate(prover.iop());

    // Make the accum group + commit
    debug!("size = {size}, accumSize = {accum_size}");
    debug!("getAccum.size() = {}", circuit.get_accum().len());
    prover.commit_group(
        REGISTER_GROUP_ACCUM,
        hal.copy_from_elem("accum", circuit.get_accum()),
    );

    let mix = hal.copy_from_elem("mix", circuit.get_mix());
    let out = hal.copy_from_elem("out", circuit.get_io());

    debug!("Steps: {}", circuit.get_steps());

    prover.finalize(&[&mix, &out], eval)
}
