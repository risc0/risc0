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

#[cfg(test)]
mod test {

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

    struct HelloCircuit {}
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

    #[test]
    fn verify_v3_stark_proof() {
        let transcript: Vec<u32> = include_bytes!("proof.bin")
            .chunks_exact(4)
            .map(|chunk| u32::from_le_bytes(chunk.try_into().unwrap()))
            // .map(|x| BabyBearElem::new(x).as_u32_montgomery())
            .collect();

        let circuit = HelloCircuit {};
        let suite = Poseidon2HashSuite::new_suite();
        let x = verify_v3(&circuit, &suite, &transcript, 12);
        match x {
            Ok(_) => {}
            Err(e) => panic!("Failed to verify: {e}"),
        }
    }

    fn get_hello_zkr() -> Result<Program> {
        let words: Vec<u32> = include_bytes!("hello_lift_12.zkr")
            .chunks_exact(4)
            .map(|chunk| u32::from_le_bytes(chunk.try_into().unwrap()))
            .collect();

        // Use recursion PO2 = 17 because of the size of the hello ZKR
        Ok(Program::from_encoded(&words, 17))
    }

    #[test]
    fn verify_with_zkr() -> Result<()> {
        // Compute the control ID for our ZKR, as well as the corresponding control root
        let hash_suite = Poseidon2HashSuite::new_suite();
        let program = get_hello_zkr()?;
        let control_id = program.compute_control_id(hash_suite.clone())?;
        let control_ids = vec![control_id];
        let group = MerkleGroup::new(vec![control_id])?;
        let control_root = group.calc_root(hash_suite.hashfn.as_ref());

        // Compute the input, which should be the control ID followed by the seal
        let mut input: Vec<u32> = vec![];
        input.extend(control_root.as_words());
        let seal = include_bytes!("proof.bin")
            .chunks_exact(4)
            .map(|chunk| u32::from_le_bytes(chunk.try_into().unwrap()));
        input.extend(seal);

        // Prove
        let receipt = prove_zkr(
            program,
            &control_id,
            control_ids,
            bytemuck::cast_slice(&input),
        )?;

        // Verify, swapping out the default control root for one that includes our ZKR
        let ctx = VerifierContext::default().with_succinct_verifier_parameters(
            SuccinctReceiptVerifierParameters {
                control_root,
                inner_control_root: None,
                proof_system_info: PROOF_SYSTEM_INFO,
                circuit_info: CircuitImpl::CIRCUIT_INFO,
            },
        );

        receipt.verify_integrity_with_context(&ctx)?;
        Ok(())
    }
}
