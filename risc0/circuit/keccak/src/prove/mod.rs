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

use crate::taps;
use anyhow::Result;
use rayon::prelude::*;
use risc0_core::field::Elem;
use risc0_zkp::hal::{Buffer, Hal};
use risc0_zkp::{
    adapter::{CircuitCoreDef, CircuitInfo, TapsProvider, PROOF_SYSTEM_INFO},
    core::{digest::Digest, hash::HashSuite},
    field::baby_bear::BabyBear,
    taps::TapSet,
};
use std::rc::Rc;

use super::CircuitImpl;

mod cpp;
pub mod cpu;
pub mod zkr;

risc0_zirgen_dsl::zirgen_inhibit_warnings! {

mod keccak_circuit {
    risc0_zirgen_dsl::zirgen_preamble!{}

    type ExecContext<'a> = super::cpu::CpuExecContext<'a>;

    include!{"../types.rs.inc"}
    include!{"../defs.rs.inc"}
    include!{"../layout.rs.inc"}
    include!{"../steps.rs.inc"}
}
}

pub use keccak_circuit::REGCOUNT_GLOBAL;
use keccak_circuit::{CircuitField, CircuitHal, ExtVal, Val};

fn clear_invalid<B: Buffer<impl Elem>>(buf: &B) {
    // Zero out 'invalid' entries
    buf.view_mut(|slice| {
        slice
            .par_iter_mut()
            .for_each(|value| *value = value.valid_or_zero())
    });
}

pub fn prove<
    'a,
    H: Hal<Field = CircuitField, Elem = Val, ExtElem = ExtVal>,
    CH: CircuitHal<'a, H> + risc0_zkp::hal::CircuitHal<H>,
>(
    hal: &H,
    circuit_hal: &CH,
    po2: usize,
) -> Result<Vec<u32>> {
    let tot_cycles: usize = 1 << po2;

    let alloc_elem = |name, size| {
        if cfg!(debug_assertions) {
            hal.copy_from_elem(name, vec![H::Elem::INVALID; size].as_slice())
        } else {
            hal.alloc_elem(name, size)
        }
    };
    let data = alloc_elem("data", keccak_circuit::REGCOUNT_DATA * tot_cycles);
    let code = alloc_elem("code", keccak_circuit::REGCOUNT_CODE * tot_cycles);
    let global = alloc_elem("global", keccak_circuit::REGCOUNT_GLOBAL);
    let accum = alloc_elem("accum", keccak_circuit::REGCOUNT_ACCUM * tot_cycles);

    circuit_hal.step_exec(tot_cycles, &data, &global)?;

    clear_invalid(&data);
    clear_invalid(&global);
    clear_invalid(&code);

    let mut prover = risc0_zkp::prove::Prover::new(hal, &*crate::taps::TAPSET);
    // At the start of the protocol, seed the Fiat-Shamir transcript with context information
    // about the proof system and circuit.
    let hashfn = Rc::clone(&hal.get_hash_suite().hashfn);
    prover
        .iop()
        .commit(&hashfn.hash_elem_slice(&PROOF_SYSTEM_INFO.encode()));
    prover
        .iop()
        .commit(&hashfn.hash_elem_slice(&CircuitImpl::CIRCUIT_INFO.encode()));
    prover.set_po2(po2);

    // Concat io (i.e. globals) and po2 into a vector.
    global.view(|out_slice| {
        let vec: Vec<_> = out_slice
            .iter()
            .chain(Elem::from_u32_slice(&[po2 as u32]))
            .copied()
            .collect();

        prover
            .iop()
            .commit(&hal.get_hash_suite().hashfn.hash_elem_slice(&vec));
        prover.iop().write_field_elem_slice(vec.as_slice());
    });

    prover.commit_group(keccak_circuit::REGISTER_GROUP_CODE, &code);
    prover.commit_group(keccak_circuit::REGISTER_GROUP_DATA, &data);

    let mix: [Val; keccak_circuit::REGCOUNT_MIX] =
        std::array::from_fn(|_| prover.iop().random_elem());
    let mix = hal.copy_from_elem("mix", mix.as_slice());
    circuit_hal.step_accum(tot_cycles, &accum, &data, &mix)?;
    clear_invalid(&accum);
    prover.commit_group(keccak_circuit::REGISTER_GROUP_ACCUM, &accum);
    let seal = prover.finalize(&[&mix, &global], circuit_hal);

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

impl CircuitCoreDef<BabyBear> for CircuitImpl {}

impl TapsProvider for CircuitImpl {
    fn get_taps(&self) -> &'static TapSet<'static> {
        self::taps::TAPSET
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use risc0_zkp::core::hash::poseidon2::Poseidon2HashSuite;
    use risc0_zkp::field::Elem;
    use risc0_zkp::hal::cpu::CpuHal;
    use test_log::test;
    fn run_test(input: Vec<u32>, po2: usize) {
        let hash_suite = Poseidon2HashSuite::new_suite();
        let hal = CpuHal::new(hash_suite.clone());
        let circuit_hal = cpu::CpuCircuitHal::new(input.into());
        let seal = prove(&hal, &circuit_hal, po2).unwrap();

        verify(seal.as_slice(), &hash_suite).expect("Verification failed");

        //        let expected_result = match op {
        //            OP_ADD => Val::new(456 + 123),
        //            OP_SUB => Val::new(456 - 123),
        //            _ => panic!("Unexpected op"),
        //        };

        let _seal_vals = Val::from_u32_slice(&seal[..keccak_circuit::REGCOUNT_GLOBAL]);
        //        assert_eq!(
        //            seal_vals[keccak_circuit::LAYOUT_GLOBAL.result._super.offset],
        //            expected_result
        //        );
    }

    fn from_hex(input: &str) -> Vec<u32> {
        let u8s: Vec<u8> = (0..input.len())
            .step_by(2)
            .map(|idx| u8::from_str_radix(&input[idx..idx + 2], 16).unwrap())
            .collect();
        assert!(u8s.len() % 4 == 0);
        u8s.chunks(4)
            .map(|slice| u32::from_le_bytes(slice.try_into().unwrap()))
            .collect()
    }

    #[test]
    fn test_keccak1() {
        run_test(from_hex("010000000000000054686520717569636B2062726F776E20666F78206A756D7073206F76657220746865206C617A7920646F672E0100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000080578951e24efd62a3d63a86f7cd19aaa53c898fe287d2552133220370240b572d0000000000000000"), /*po2=*/12);
    }

    #[test]
    fn test_keccak2() {
        run_test(from_hex("0600000000000000436F6D6D616E64657220526F64657269636B20426C61696E65206C6F6F6B6564206672616E746963616C6C792061726F756E6420746865206272696467652E20776865726520686973206F66666963657273207765726520646972656374696E6720726570616972732077697468206C6F7720616E6420757267656E7420766F696365732C2073757267656F6E7320617373697374696E67206174206120646966666963756C74206F7065726174696F6E2E20546865206772617920737465656C20636F6D706172746D656E7420776173206120636F6E667573696F6E206F6620616374697669746965732C2065616368206F726465726C7920627920697473656C662062757420746865206F766572616C6C20696D7072657373696F6E20776173206F66206368616F732E2053637265656E732061626F7665206F6E652068656C6D736D616E27732073746174696F6E2073686F7765642074686520706C616E65742062656C6F7720616E6420746865206F746865722C20736869707320696E206F72626974206E656172204D61634172746875722C20627574206576657279776865726520656C7365207468652070616E656C20636F7665727320686164206265656E2072656D6F7665642066726F6D20636F6E736F6C65732C207465737420696E737472756D656E7473207765726520636C697070656420696E746F20746865697220696E73696465732C20616E6420746563686E696369616E732073746F6F64206279207769746820636F6C6F722D636F64656420656C656374726F6E696320617373656D626C69657320746F207265706C6163652065766572797468696E672074686174207365656D656420646F75627466756C2E205468756D707320616E64207768696E657320736F756E646564207468726F75676820746865207368697020383920736F6D657768657265206166742074686520656E67696E656572696E67206372657720776F726B6564206F6E207468652068756C6C2E01000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000008028c3f5c69c21be780e5508d355ebf7d5e060f203ca8717447b71cb44544df5c70200000000000000546865736520776F7264732077657265207574746572656420696E204A756C79203138303520627920416E6E61205061766C6F766E6120536368657265722C20612064697374696E67756973686564206C616479206F662074686520636F7572742C20616E6420636F6E666964656E7469616C206D6169642D6F662D686F6E6F757220746F2074686520456D7072657373204D617279612046796F646F726F766E612E2049742077617320686572206772656574696E6720746F205072696E63652056617373696C792C2061206D616E206869676820696E2072616E6B20616E64206F66666963652C2077686F207761732074686520666972737420746F2061727269766520617401000000000000804bdc1874a3125f1f911fe8c76ac8443a6ec623ef91bc58eabf54c5762097894d0000000000000000") ,/*po2=*/15);
    }
}
