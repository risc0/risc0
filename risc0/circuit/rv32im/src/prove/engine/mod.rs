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

use std::sync::Mutex;

use anyhow::Result;
use rand::thread_rng;
use rayon::prelude::*;
use risc0_zkp::{
    adapter::{
        CircuitInfo as _, CircuitStep as _, CircuitStepContext, CircuitStepHandler as _,
        TapsProvider,
    },
    field::{
        baby_bear::{BabyBear, BabyBearElem, BabyBearExtElem},
        Elem as _,
    },
    hal::{cpu::CpuBuffer, CircuitHal, Hal},
    layout::Buffer as _,
    prove::{
        accum::{Accum, Handler},
        write_iop::WriteIOP,
        Prover,
    },
    ZK_CYCLES,
};

use self::{loader::Loader, machine::MachineContext};

use super::emu::{
    preflight::{preflight_segment, PreflightTrace},
    Segment,
};
use crate::{
    layout::{OutBuffer, LAYOUT},
    CircuitImpl, CIRCUIT, REGISTER_GROUP_ACCUM, REGISTER_GROUP_CODE, REGISTER_GROUP_DATA,
};

struct WitnessGenerator {
    steps: usize,
    code: CpuBuffer<BabyBearElem>,
    data: CpuBuffer<BabyBearElem>,
    io: CpuBuffer<BabyBearElem>,
}

impl WitnessGenerator {
    pub fn new(po2: usize, io: &[BabyBearElem]) -> Self {
        let steps = 1 << po2;
        Self {
            steps,
            code: CpuBuffer::from_fn(steps * CIRCUIT.code_size(), |_| BabyBearElem::ZERO),
            data: CpuBuffer::from_fn(steps * CIRCUIT.data_size(), |_| BabyBearElem::INVALID),
            io: CpuBuffer::from(Vec::from(io)),
        }
    }

    fn execute(&mut self, trace: PreflightTrace) {
        let mut machine = MachineContext::new(trace);
        self.compute_execute(&mut machine);
        self.compute_verify(&mut machine);

        // Zero out 'invalid' entries in data and output.
        self.data
            .as_slice_mut()
            .par_iter_mut()
            .chain(self.io.as_slice_mut().par_iter_mut())
            .for_each(|value| *value = value.valid_or_zero());
    }

    fn compute_execute(&mut self, machine: &mut MachineContext) {
        tracing::debug!("load");
        let mut loader = Loader::new(self.steps);
        loader.load();

        tracing::debug!("execute");
        for cycle in 0..loader.cycle {
            let args = &[
                loader.ctrl.as_slice_sync(),
                self.io.as_slice_sync(),
                self.data.as_slice_sync(),
            ];

            let ctx = CircuitStepContext {
                size: self.steps,
                cycle,
            };
            CIRCUIT.step_exec(&ctx, machine, args).unwrap();
        }
    }

    fn compute_verify(&mut self, machine: &mut MachineContext) {
        tracing::debug!("compute_verify");
        let mut rng = thread_rng();
        let code = self.code.as_slice_sync();
        let io = self.io.as_slice_sync();
        let data = self.data.as_slice_sync();

        for i in 0..ZK_CYCLES {
            let cycle = self.steps - ZK_CYCLES + i;
            // Set code to all zeros for the ZK_CYCLES
            for j in 0..CIRCUIT.code_size() {
                code.set(j * self.steps + cycle, BabyBearElem::ZERO);
            }
            // Set data to random for the ZK_CYCLES
            for j in 0..CIRCUIT.data_size() {
                data.set(j * self.steps + cycle, BabyBearElem::random(&mut rng));
            }
        }

        // Do the verify cycles
        let args = &[code, io, data];

        machine.sort("ram");
        let last_cycle = self.steps - ZK_CYCLES;
        tracing::info_span!("step_verify_mem").in_scope(|| {
            for i in 0..last_cycle {
                let ctx = CircuitStepContext {
                    cycle: i,
                    size: self.steps,
                };
                CIRCUIT.step_verify_mem(&ctx, machine, args).unwrap();
            }
        });

        machine.sort("bytes");
        tracing::info_span!("step_verify_bytes").in_scope(|| {
            for i in 0..last_cycle {
                let ctx = CircuitStepContext {
                    cycle: i,
                    size: self.steps,
                };
                CIRCUIT.step_verify_bytes(&ctx, machine, args).unwrap();
            }
        });
    }

    fn accumulate(
        &mut self,
        iop: &mut WriteIOP<BabyBear>,
    ) -> (CpuBuffer<BabyBearElem>, CpuBuffer<BabyBearElem>) {
        tracing::debug!("accumulate");

        // Make the mixing values
        let mix = CpuBuffer::from_fn(CircuitImpl::MIX_SIZE, |_| iop.random_elem());

        // Make and compute accum data
        let accum_size = CIRCUIT.accum_size();
        let accum = CpuBuffer::from_fn(self.steps * accum_size, |_| BabyBearElem::INVALID);
        self.compute_accum(&mix, &accum);

        {
            // Zero out 'invalid' entries in accum and io
            let mut accum_slice = accum.as_slice_mut();
            let mut io = self.io.as_slice_mut();
            for value in accum_slice.iter_mut().chain(io.iter_mut()) {
                *value = value.valid_or_zero();
            }

            // Add random noise to end of accum and change invalid element to zero
            let mut rng = thread_rng();
            for i in self.steps - ZK_CYCLES..self.steps {
                for j in 0..accum_size {
                    accum_slice[j * self.steps + i] = BabyBearElem::random(&mut rng);
                }
            }
        }

        (mix, accum)
    }

    fn compute_accum(&mut self, mix: &CpuBuffer<BabyBearElem>, accum: &CpuBuffer<BabyBearElem>) {
        let args = &[
            self.code.as_slice_sync(),
            self.io.as_slice_sync(),
            self.data.as_slice_sync(),
            mix.as_slice_sync(),
            accum.as_slice_sync(),
        ];
        let accum: Mutex<Accum<BabyBearExtElem>> = Mutex::new(Accum::new(self.steps));
        tracing::info_span!("step_compute_accum").in_scope(|| {
            // TODO: Add an way to be able to run this on cuda, metal, etc.
            (0..self.steps - ZK_CYCLES).into_par_iter().for_each_init(
                || Handler::<BabyBear>::new(&accum),
                |handler, cycle| {
                    CIRCUIT
                        .step_compute_accum(
                            &CircuitStepContext {
                                size: self.steps,
                                cycle,
                            },
                            handler,
                            args,
                        )
                        .unwrap();
                },
            );
        });
        tracing::info_span!("calc_prefix_products").in_scope(|| {
            accum.lock().unwrap().calc_prefix_products();
        });
        tracing::info_span!("step_verify_accum").in_scope(|| {
            (0..self.steps - ZK_CYCLES).into_par_iter().for_each_init(
                || Handler::<BabyBear>::new(&accum),
                |handler, cycle| {
                    CIRCUIT
                        .step_verify_accum(
                            &CircuitStepContext {
                                size: self.steps,
                                cycle,
                            },
                            handler,
                            args,
                        )
                        .unwrap();
                },
            );
        });
    }
}

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

    let code = hal.copy_from_elem("code", &witgen.code.as_slice());
    prover.commit_group(REGISTER_GROUP_CODE, code);

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

        let check_code = |_, _: &_| -> Result<(), VerificationError> { Ok(()) };
        risc0_zkp::verify::verify(&CIRCUIT, &suite, &seal, check_code).unwrap();
    }
}
