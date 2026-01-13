// Copyright 2026 RISC Zero, Inc.
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

#[cfg(test)]
mod test {
    use std::mem::size_of;

    use anyhow::Result;
    use risc0_circuit_recursion::{CircuitImpl, prove::Program};
    use risc0_core::field::baby_bear::{BabyBear, BabyBearElem, BabyBearExtElem};
    use risc0_zkp::{
        adapter::{
            CircuitCoreDefV3, CircuitInfo, CircuitInfoV3, GroupInfo, MixState, PROOF_SYSTEM_INFO,
            PolyExt, PolyExtStep, PolyExtStepDef, TapsProvider,
        },
        core::hash::poseidon2::Poseidon2HashSuite,
        taps::{TapData, TapSet},
        verify::verify_v3,
    };
    use risc0_zkvm::{
        SuccinctReceiptVerifierParameters, VerifierContext, prove_zkr, recursion::MerkleGroup,
    };

    const PROOF_BIN: &[u8] = include_bytes!("testdata/proof.bin");
    const HELLO_LIFT_12_ZKR: &[u8] = include_bytes!("testdata/hello_lift_12.zkr");
    const HELLO_LIFT_PO2: usize = 12;
    const WORD_SIZE: usize = size_of::<u32>();

    pub const TAPSET: &TapSet = &TapSet::<'static> {
        taps: &[
            TapData {
                offset: 0,
                back: 0,
                group: 0,
                combo: 0,
                skip: 1,
            },
            TapData {
                offset: 0,
                back: 0,
                group: 1,
                combo: 0,
                skip: 1,
            },
            TapData {
                offset: 0,
                back: 0,
                group: 2,
                combo: 0,
                skip: 1,
            },
        ],
        combo_taps: &[0],
        combo_begin: &[0, 1],
        group_begin: &[0, 1, 2, 3],
        combos_count: 1,
        reg_count: 3,
        tot_combo_backs: 1,
        group_names: &["accum", "code", "data"],
    };

    struct HelloCircuit;

    impl CircuitInfoV3 for HelloCircuit {
        fn get_groups(&self) -> &'static [GroupInfo] {
            &[
                GroupInfo {
                    global_count: 0,
                    mix_count: 0,
                },
                GroupInfo {
                    global_count: 0,
                    mix_count: 0,
                },
                GroupInfo {
                    global_count: 0,
                    mix_count: 0,
                },
            ]
        }
    }

    const DEF: PolyExtStepDef = PolyExtStepDef {
        block: &[
            PolyExtStep::True,         // mix_vars 0
            PolyExtStep::Get(0),       // fp_vars 0
            PolyExtStep::Get(1),       // fp_vars 1
            PolyExtStep::Get(2),       // fp_vars 2
            PolyExtStep::Const(0),     // fp_vars 3
            PolyExtStep::Const(1),     // fp_vars 4
            PolyExtStep::AndEqz(0, 0), // mix_vars 1
            PolyExtStep::AndEqz(1, 1), // mix_vars 2
            PolyExtStep::Sub(2, 4),    // fp_vars 5
            PolyExtStep::Mul(2, 5),    // fp_vars 6
            PolyExtStep::AndEqz(2, 6), // mix_vars 3
        ],
        ret: 3,
    };

    impl PolyExt<BabyBear> for HelloCircuit {
        fn poly_ext(
            &self,
            mix: &BabyBearExtElem,
            u: &[BabyBearExtElem],
            args: &[&[BabyBearElem]],
        ) -> MixState<BabyBearExtElem> {
            DEF.step::<BabyBear>(mix, u, args)
        }
    }

    impl TapsProvider for HelloCircuit {
        fn get_taps(&self) -> &'static TapSet<'static> {
            TAPSET
        }
    }

    impl CircuitCoreDefV3<BabyBear> for HelloCircuit {}

    fn bytes_as_words(bytes: &[u8]) -> Vec<u32> {
        bytes
            .chunks_exact(WORD_SIZE)
            .map(|chunk| u32::from_le_bytes(chunk.try_into().unwrap()))
            .collect()
    }

    fn get_hello_zkr() -> Result<Program> {
        let words = bytes_as_words(HELLO_LIFT_12_ZKR);

        // Use recursion PO2 = 17 because of the size of the hello ZKR
        const RECURSION_PO2: usize = 17;
        Ok(Program::from_encoded(&words, RECURSION_PO2))
    }

    #[test_log::test]
    fn verify_v3_stark_proof() {
        let transcript = bytes_as_words(PROOF_BIN);
        let circuit = HelloCircuit;
        let suite = Poseidon2HashSuite::new_suite();
        verify_v3(&circuit, &suite, &transcript, HELLO_LIFT_PO2).unwrap();
    }

    #[test_log::test]
    fn verify_with_zkr() {
        // Compute the control ID for our ZKR, as well as the corresponding control root
        let hash_suite = Poseidon2HashSuite::new_suite();
        let program = get_hello_zkr().unwrap();
        let control_id = program.compute_control_id(hash_suite.clone()).unwrap();
        let group = MerkleGroup::new(vec![control_id]).unwrap();
        let control_root = group.calc_root(hash_suite.hashfn.as_ref());

        // Compute the input, which should be the control ID followed by the seal
        let mut input: Vec<u32> = vec![];
        input.extend(control_root.as_words());
        let seal = bytes_as_words(PROOF_BIN);
        input.extend(seal);

        // Prove
        let receipt = prove_zkr(
            program,
            &control_id,
            group.leaves,
            bytemuck::cast_slice(&input),
        )
        .unwrap();

        // Verify, swapping out the default control root for one that includes our ZKR
        let ctx = VerifierContext::default().with_succinct_verifier_parameters(
            SuccinctReceiptVerifierParameters {
                control_root,
                inner_control_root: None,
                proof_system_info: PROOF_SYSTEM_INFO,
                circuit_info: CircuitImpl::CIRCUIT_INFO,
            },
        );

        receipt.verify_integrity_with_context(&ctx).unwrap();
    }
}
