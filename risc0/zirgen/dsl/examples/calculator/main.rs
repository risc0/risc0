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

//! Performs a simple test of 123 + 456 using the generated code for the calculator circuit.
mod cpu;
mod info;
mod poly_ext;
mod taps;

use anyhow::Result;
use clap::Parser;
use risc0_zkp::{
    adapter::{CircuitCoreDef, CircuitInfo, TapsProvider, PROOF_SYSTEM_INFO},
    core::{
        digest::Digest,
        hash::{poseidon2::Poseidon2HashSuite, HashSuite},
    },
    field::Elem,
    hal::{cpu::CpuHal, Buffer, Hal},
    taps::TapSet,
};
use std::path::PathBuf;
use std::rc::Rc;

pub const CALC_PO2: usize = 5;

risc0_zirgen_dsl::zirgen_inhibit_warnings! {
mod calc_circuit {
    risc0_zirgen_dsl::zirgen_preamble!{}

    type ExecContext = super::cpu::CpuExecContext;
    type ValidityCtx = super::cpu::ValidityCtx;

    fn and_eqz(ctx: &ValidityCtx, x: MixState, val: Val) -> Result<MixState> {
        and_eqz_generic::<CircuitField, Val>(ctx.poly_mix, x, val)
    }
    fn and_eqz_ext(ctx: &ValidityCtx, x: MixState, val: ExtVal) -> Result<MixState> {
        and_eqz_generic::<CircuitField, ExtVal>(ctx.poly_mix, x, val)
    }

    include!{"types.rs.inc"}
    include!{"defs.rs.inc"}
    include!{"layout.rs.inc"}
    include!{"steps.rs.inc"}

    // TODO: modularize validity stuff
    pub mod validity {
        use super::*;
        include!{"validity.rs.inc"}
    }
}
}
use calc_circuit::{CircuitField, CircuitHal, ExtVal, Val};

pub struct CircuitImpl;

pub const CIRCUIT: CircuitImpl = CircuitImpl;
impl TapsProvider for CircuitImpl {
    fn get_taps(&self) -> &'static TapSet<'static> {
        self::taps::TAPSET
    }
}

pub const OP_ADD: usize = 0;
pub const OP_SUB: usize = 1;

fn clear_invalid<B: Buffer<impl Elem>>(buf: &B) {
    // Zero out 'invalid' entries
    buf.view_mut(|slice| {
        slice
            .iter_mut()
            .for_each(|value| *value = value.valid_or_zero())
    });
}

fn prove<
    'a,
    H: Hal<Field = CircuitField, Elem = Val, ExtElem = ExtVal>,
    CH: CircuitHal<'a, H> + risc0_zkp::hal::CircuitHal<H>,
>(
    hal: &H,
    circuit_hal: &CH,
) -> Result<Vec<u32>> {
    // TODO: Make it so we can use a smaller PO2 for testing without
    // having everything break in mysterious ways.  We should at least
    // have a more informative error message than "seal fails
    // verifaciton".
    const TOT_CYCLES: usize = 1 << CALC_PO2;

    let alloc_elem = |name, size| {
        if cfg!(debug_assertions) {
            hal.copy_from_elem(name, vec![H::Elem::INVALID; size].as_slice())
        } else {
            hal.alloc_elem(name, size)
        }
    };
    let data = alloc_elem("data", calc_circuit::REGCOUNT_DATA * TOT_CYCLES);
    let code = alloc_elem("code", calc_circuit::REGCOUNT_CODE * TOT_CYCLES);
    let global = alloc_elem("global", calc_circuit::REGCOUNT_GLOBAL);
    let accum = alloc_elem("accum", calc_circuit::REGCOUNT_ACCUM * TOT_CYCLES);

    circuit_hal.step_exec(TOT_CYCLES, &data, &global)?;

    clear_invalid(&data);
    clear_invalid(&global);
    clear_invalid(&code);

    let hashfn = Rc::clone(&hal.get_hash_suite().hashfn);
    let mut prover = risc0_zkp::prove::Prover::new(hal, &*crate::taps::TAPSET);
    // At the start of the protocol, seed the Fiat-Shamir transcript with context information
    // about the proof system and circuit.
    prover
        .iop()
        .commit(&hashfn.hash_elem_slice(&PROOF_SYSTEM_INFO.encode()));
    prover
        .iop()
        .commit(&hashfn.hash_elem_slice(&CircuitImpl::CIRCUIT_INFO.encode()));

    // Concat io (i.e. globals) and po2 into a vector.
    let mut vec: Vec<Val> = Vec::new();
    global.view(|out_slice| {
        vec.extend(out_slice);
    });
    vec.extend(Val::from_u32_slice(&[CALC_PO2 as u32]));

    prover
        .iop()
        .commit(&hal.get_hash_suite().hashfn.hash_elem_slice(&vec));
    prover.iop().write_field_elem_slice(vec.as_slice());

    prover.set_po2(CALC_PO2);

    // ZKP library's verification requires that we have 3 hardcoded
    // buffers, numbered 0, 1, and 2, all of which are nonempty, have
    // a size of a multiple of the cycle count, and are committed in a
    // specific order.
    //
    // TODO: Remove this restriction and make buffer orders and such per-circuit.
    prover.commit_group(calc_circuit::REGISTER_GROUP_CODE, &code);
    prover.commit_group(calc_circuit::REGISTER_GROUP_DATA, &data);
    let mix: [Val; calc_circuit::REGCOUNT_MIX] =
        std::array::from_fn(|_| prover.iop().random_elem());
    let mix = hal.copy_from_elem("mix", mix.as_slice());
    circuit_hal.step_accum(TOT_CYCLES, &accum, &data, &global)?;
    clear_invalid(&accum);
    prover.commit_group(calc_circuit::REGISTER_GROUP_ACCUM, &accum);
    let seal = prover.finalize(&[&global, &mix], circuit_hal);

    Ok(seal)
}

pub fn verify(seal: &[u32], hash_suite: &HashSuite<CircuitField>) -> Result<()> {
    // We don't have a `code' buffer to verify.
    let check_code_fn = |_: u32, _: &Digest| Ok(());

    Ok(risc0_zkp::verify::verify(
        &CircuitImpl,
        hash_suite,
        seal,
        check_code_fn,
    )?)
}

impl CircuitCoreDef<risc0_zkp::field::baby_bear::BabyBear> for CircuitImpl {}

#[derive(Parser)]
struct Args {
    /// Filename in which to write an output seal.
    #[clap(long)]
    seal: PathBuf,
}

pub fn main() {
    tracing_subscriber::fmt()
        .with_env_filter(tracing_subscriber::filter::EnvFilter::from_default_env())
        .init();

    let args = Args::parse();
    let hash_suite = Poseidon2HashSuite::new_suite();
    let hal = CpuHal::new(hash_suite.clone());

    let mut elems = Vec::new();
    // operation, argument, expected
    while elems.len() < (1 << CALC_PO2) * 4 {
        elems.extend([OP_ADD, 1, 2, 3]);
        elems.extend([OP_SUB, 10, 1, 9]);
    }

    let circuit_hal = cpu::CpuCircuitHal::new(&elems);
    let seal = prove(&hal, &circuit_hal).unwrap();
    std::fs::write(args.seal, bytemuck::cast_slice(seal.as_slice())).expect("Writing seal failed");

    verify(seal.as_slice(), &hash_suite).expect("Verification failed");
}

#[cfg(test)]
mod tests {
    /*
    use super::*;
    use risc0_zkp::field::Elem;
    use test_log::test;

    // TODO: fix this test
    fn run_test(op: usize) {
        let hash_suite = Poseidon2HashSuite::new_suite();
        let hal = CpuHal::new(hash_suite.clone());
        let circuit_hal = cpu::CpuCircuitHal::new(op, 456, 123);
        let seal = prove(&hal, &circuit_hal).unwrap();

        verify(seal.as_slice(), &hash_suite).expect("Verification failed");

        let expected_result = match op {
            OP_ADD => Val::new(456 + 123),
            OP_SUB => Val::new(456 - 123),
            _ => panic!("Unexpected op"),
        };

        let seal_vals = Val::from_u32_slice(&seal[..calc_circuit::REGCOUNT_GLOBAL]);
        assert_eq!(
            seal_vals[calc_circuit::LAYOUT_GLOBAL.result._super.offset],
            expected_result
        );
    }

    #[test]
    fn test_cpu_add() {
        run_test(OP_ADD);
    }

    #[test]
    fn test_cpu_sub() {
        run_test(OP_SUB);
    }*/
}
