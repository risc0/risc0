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

use anyhow::{Context as _, Result};
use risc0_circuit_recursion_sys::{RawPreflightTrace, StepMode};
use risc0_core::scope;
use risc0_zkp::{
    adapter::{CircuitInfo as _, TapsProvider as _},
    field::{
        baby_bear::{BabyBear, BabyBearElem, BabyBearExtElem},
        Elem as _,
    },
    hal::Hal,
};

use crate::{CircuitImpl, CIRCUIT};

use super::{preflight::Preflight, CircuitAccumulator, CircuitWitnessGenerator, Program};

pub(crate) struct WitnessGenerator<H: Hal> {
    work_cycles: u32,
    total_cycles: u32,
    pub global: H::Buffer<H::Elem>,
    pub ctrl: H::Buffer<H::Elem>,
    pub data: H::Buffer<H::Elem>,
    pub accum: H::Buffer<H::Elem>,
}

impl<H> WitnessGenerator<H>
where
    H: Hal<Field = BabyBear, Elem = BabyBearElem, ExtElem = BabyBearExtElem>,
{
    pub fn new<C: CircuitWitnessGenerator<H>>(
        hal: &H,
        circuit_hal: &C,
        zkr: &Program,
        preflight: &Preflight,
    ) -> Result<Self> {
        scope!("witgen");

        let total_cycles = 1 << zkr.po2;

        let global = vec![BabyBearElem::INVALID; CircuitImpl::OUTPUT_SIZE];
        let global = hal.copy_from_elem("global", &global);

        let mut ctrl = vec![BabyBearElem::ZERO; total_cycles * CIRCUIT.ctrl_size()];

        // populate the ctrl buffer
        let ctrl_size = CIRCUIT.ctrl_size();
        assert_eq!(ctrl_size, zkr.code_size);
        for i in 0..zkr.code_rows() {
            for j in 0..ctrl_size {
                ctrl[j * total_cycles + i] = zkr.code[i * ctrl_size + j];
            }
        }
        let ctrl = hal.copy_from_elem("ctrl", &ctrl);

        let data = hal.alloc_elem_init(
            "data",
            total_cycles * CIRCUIT.data_size(),
            BabyBearElem::INVALID,
        );
        let accum = hal.alloc_elem_init(
            "accum",
            total_cycles * CIRCUIT.accum_size(),
            BabyBearElem::INVALID,
        );

        let work_cycles = zkr.code_rows() as u32;
        let raw_trace = RawPreflightTrace {
            wom: preflight.trace.wom.as_ptr(),
            cycles: preflight.trace.cycles.as_ptr(),
            iops: preflight.trace.iops.as_ptr(),
            num_woms: preflight.trace.wom.len() as u32,
            num_cycles: work_cycles,
            num_iops: preflight.trace.iops.len() as u32,
        };

        circuit_hal
            .generate_witness(
                StepMode::Parallel,
                total_cycles as u32,
                &raw_trace,
                &ctrl,
                &data,
                &global,
            )
            .context("witness generation failure")?;

        // Add random noise to end of the data columns
        scope!("noise", {
            use risc0_zkp::ZK_CYCLES;
            let mut rng = rand::rng();
            let noise = vec![BabyBearElem::random(&mut rng); ZK_CYCLES * CIRCUIT.data_size()];
            hal.eltwise_copy_elem_slice(
                &data,
                &noise,
                CIRCUIT.data_size(),      // from_rows
                ZK_CYCLES,                // from_cols
                0,                        // from_offset
                ZK_CYCLES,                // from_stride
                total_cycles - ZK_CYCLES, // into_offset
                total_cycles,             // into_stride
            );
        });

        // Zero out 'invalid' entries in data and output.
        scope!("zeroize", {
            hal.eltwise_zeroize_elem(&data);
            hal.eltwise_zeroize_elem(&global);
        });

        Ok(Self {
            work_cycles,
            total_cycles: total_cycles as u32,
            global,
            ctrl,
            data,
            accum,
        })
    }

    pub fn accum<C: CircuitAccumulator<H>>(
        &self,
        hal: &H,
        circuit_hal: &C,
        mix: &[BabyBearElem],
    ) -> Result<H::Buffer<H::Elem>> {
        scope!("accum");

        let mix = hal.copy_from_elem("mix", mix);

        // Add random noise to end of accum
        scope!("noise", {
            use risc0_zkp::ZK_CYCLES;
            let mut rng = rand::rng();
            let total_cycles = self.total_cycles as usize;
            let noise = vec![BabyBearElem::random(&mut rng); ZK_CYCLES * CIRCUIT.accum_size()];
            hal.eltwise_copy_elem_slice(
                &self.accum,
                &noise,
                CIRCUIT.accum_size(),     // from_rows
                ZK_CYCLES,                // from_cols
                0,                        // from_offset
                ZK_CYCLES,                // from_stride
                total_cycles - ZK_CYCLES, // into_offset
                total_cycles,             // into_stride
            );
        });

        circuit_hal.accumulate(
            self.work_cycles,
            self.total_cycles,
            &self.ctrl,
            &self.global,
            &self.data,
            &mix,
            &self.accum,
        )?;

        scope!("zeroize", {
            hal.eltwise_zeroize_elem(&self.accum);
            hal.eltwise_zeroize_elem(&self.global);
        });

        Ok(mix)
    }
}
