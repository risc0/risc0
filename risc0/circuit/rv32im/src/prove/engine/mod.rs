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

pub mod argument;
pub mod loader;
pub mod machine;
pub mod witgen;

use anyhow::Result;
use risc0_zkp::{
    adapter::TapsProvider,
    field::baby_bear::{BabyBear, BabyBearElem, BabyBearExtElem},
    hal::{CircuitHal, Hal},
    layout::Buffer as _,
    prove::Prover,
};

use self::witgen::WitnessGenerator;
use super::emu::{preflight::preflight_segment, Segment};
use crate::{
    layout::{OutBuffer, LAYOUT},
    CIRCUIT, REGISTER_GROUP_ACCUM, REGISTER_GROUP_CTRL, REGISTER_GROUP_DATA,
};

pub fn prove_segment<H, C>(
    hal: &H,
    circuit_hal: &C,
    segment: &Segment,
    po2: usize,
) -> Result<Vec<u32>>
where
    H: Hal<Field = BabyBear, Elem = BabyBearElem, ExtElem = BabyBearExtElem>,
    C: CircuitHal<H>,
{
    let io = segment.prepare_globals();
    let mut witgen = WitnessGenerator::new(po2, &io);

    let trace = preflight_segment(segment)?;
    witgen.execute(trace);

    let mut prover = Prover::new(hal, CIRCUIT.get_taps());
    prover.iop().write_field_elem_slice(&witgen.io.as_slice());
    prover.iop().write_u32_slice(&[po2 as u32]);
    prover.set_po2(po2);

    let ctrl = hal.copy_from_elem("ctrl", &witgen.ctrl.as_slice());
    prover.commit_group(REGISTER_GROUP_CTRL, ctrl);

    let data = hal.copy_from_elem("data", &witgen.data.as_slice());
    prover.commit_group(REGISTER_GROUP_DATA, data);

    let (mix, accum) = witgen.accumulate(prover.iop());

    let accum = hal.copy_from_elem("accum", &accum.as_slice());
    prover.commit_group(REGISTER_GROUP_ACCUM, accum);

    let io = &witgen.io.as_slice();
    tracing::debug!("Globals: {:?}", OutBuffer(io).tree(LAYOUT));
    let io = hal.copy_from_elem("io", io);
    let mix = hal.copy_from_elem("mix", &mix.as_slice());

    let seal = prover.finalize(&[&mix, &io], circuit_hal);
    Ok(seal)
}

#[cfg(test)]
#[allow(unused)]
mod tests {
    use std::collections::BTreeMap;

    use anyhow::Result;
    use risc0_binfmt::{MemoryImage, Program};
    use risc0_zkp::{
        adapter::{
            CircuitProveDef, CircuitStep as _, CircuitStepContext, CircuitStepHandler,
            TapsProvider as _,
        },
        core::hash::sha::Sha256HashSuite,
        field::{baby_bear::BabyBearElem, Elem as _},
        hal::{
            cpu::{CpuBuffer, CpuHal, SyncSlice},
            Hal,
        },
        prove::executor::Executor,
        verify::VerificationError,
    };
    use risc0_zkvm_platform::PAGE_SIZE;
    use test_log::test;

    use crate::{
        prove::{
            emu::{
                exec::{self, execute, Syscall, SyscallContext},
                preflight::preflight_segment,
            },
            hal::cpu::CpuCircuitHal,
        },
        CIRCUIT,
    };

    use super::{loader::Loader, machine::MachineContext};

    #[derive(Default)]
    struct NullSyscall;

    impl Syscall for NullSyscall {
        fn syscall(
            &self,
            _syscall: &str,
            _ctx: &mut dyn SyscallContext,
            _guest_buf: &mut [u32],
        ) -> Result<(u32, u32)> {
            todo!()
        }
    }

    #[test]
    fn basic() {
        let raw_image = BTreeMap::from([
            (0x4000, 0x1234b137), // lui x2, 0x1234b000
            (0x4004, 0xf387e1b7), // lui x3, 0xf387e000
            (0x4008, 0x003100b3), // add x1, x2, x3
            (0x400c, 0x000055b7), // lui a1, 0x00005000
            (0x4010, 0x00000073), // ecall(halt)
        ]);
        let program = Program {
            entry: 0x4000,
            image: raw_image.clone(),
        };
        let image = MemoryImage::new(&program, PAGE_SIZE as u32).unwrap();

        let segments = execute(image, 1 << 20, 1 << 4, &NullSyscall::default()).unwrap();
        let segment = segments.first().unwrap();

        let suite = Sha256HashSuite::new_suite();
        let hal = CpuHal::new(suite.clone());
        let circuit_hal = CpuCircuitHal::new();
        let po2 = 15;

        let seal = super::prove_segment(&hal, &circuit_hal, segment, po2).unwrap();

        let check_ctrl = |_, _: &_| -> Result<(), VerificationError> { Ok(()) };
        risc0_zkp::verify::verify(&CIRCUIT, &suite, &seal, check_ctrl).unwrap();
    }
}
