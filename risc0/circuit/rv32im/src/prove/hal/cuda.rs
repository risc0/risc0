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

use std::rc::Rc;

use anyhow::Result;
use risc0_circuit_rv32im_sys::{
    RawAccumBuffers, RawBuffer, RawExecBuffers, RawPreflightTrace, risc0_circuit_rv32im_cuda_accum,
    risc0_circuit_rv32im_cuda_eval_check, risc0_circuit_rv32im_cuda_reset,
    risc0_circuit_rv32im_cuda_witgen,
};
use risc0_core::{
    field::{Elem, ExtElem as _, RootsOfUnity, map_pow},
    scope,
};
use risc0_sys::ffi_wrap;
use risc0_zkp::{
    INV_RATE,
    core::log2_ceil,
    hal::{
        AccumPreflight, Buffer, CircuitHal,
        cuda::{BufferImpl as CudaBuffer, CudaHal, CudaHalPoseidon2, CudaHash, CudaHashPoseidon2},
    },
};

use crate::{
    prove::{GLOBAL_MIX, GLOBAL_OUT, SegmentProver},
    zirgen::{
        circuit::{ExtVal, REGISTER_GROUP_ACCUM, REGISTER_GROUP_CODE, REGISTER_GROUP_DATA, Val},
        info::{NUM_POLY_MIX_POWERS, POLY_MIX_POWERS},
    },
};

use super::{
    CircuitAccumulator, CircuitWitnessGenerator, MetaBuffer, PreflightTrace, SegmentProverImpl,
    StepMode,
};

pub struct CudaCircuitHal<CH: CudaHash> {
    hal: Rc<CudaHal<CH>>,
}

impl<CH: CudaHash> CudaCircuitHal<CH> {
    pub fn new(hal: Rc<CudaHal<CH>>) -> Self {
        #[cfg(test)]
        gpu_guard::assert_gpu_semaphore_held();

        Self { hal }
    }
}

impl<CH: CudaHash> Drop for CudaCircuitHal<CH> {
    fn drop(&mut self) {
        cuda_reset();
    }
}

fn cuda_reset() {
    ffi_wrap(|| unsafe { risc0_circuit_rv32im_cuda_reset() }).unwrap();
}

impl<CH: CudaHash> CircuitWitnessGenerator<CudaHal<CH>> for CudaCircuitHal<CH> {
    fn generate_witness(
        &self,
        mode: StepMode,
        preflight: &PreflightTrace,
        global: &MetaBuffer<CudaHal<CH>>,
        data: &MetaBuffer<CudaHal<CH>>,
    ) -> Result<()> {
        scope!("witgen");

        let cycles = preflight.cycles.len();
        assert_eq!(cycles, data.rows);
        tracing::debug!("witgen: {cycles}");

        let global_ptr = global.buf.as_device_ptr();
        let data_ptr = data.buf.as_device_ptr();
        let buffers = RawExecBuffers {
            global: RawBuffer {
                buf: global_ptr.as_ptr() as *const Val,
                rows: global.rows,
                cols: global.cols,
                checked: global.checked,
            },
            data: RawBuffer {
                buf: data_ptr.as_ptr() as *const Val,
                rows: data.rows,
                cols: data.cols,
                checked: data.checked,
            },
        };

        let preflight = RawPreflightTrace {
            cycles: preflight.cycles.as_ptr(),
            txns: preflight.txns.as_ptr(),
            bigint_bytes: preflight.bigint_bytes.as_ptr(),
            txns_len: preflight.txns.len() as u32,
            bigint_bytes_len: preflight.bigint_bytes.len() as u32,
            table_split_cycle: preflight.table_split_cycle,
        };
        ffi_wrap(|| unsafe {
            risc0_circuit_rv32im_cuda_witgen(
                self.hal.stream.as_inner(),
                mode as u32,
                &buffers,
                &preflight,
                cycles as u32,
            )
        })
    }
}

impl<CH: CudaHash> CircuitAccumulator<CudaHal<CH>> for CudaCircuitHal<CH> {
    fn step_accum(
        &self,
        preflight: &PreflightTrace,
        data: &MetaBuffer<CudaHal<CH>>,
        accum: &MetaBuffer<CudaHal<CH>>,
        global: &MetaBuffer<CudaHal<CH>>,
        mix: &MetaBuffer<CudaHal<CH>>,
    ) -> Result<()> {
        scope!("accumulate");

        let cycles = preflight.cycles.len();
        tracing::debug!("accumulate: {cycles}");

        let buffers = RawAccumBuffers {
            data: RawBuffer {
                buf: data.buf.as_device_ptr().as_ptr() as *const Val,
                rows: data.rows,
                cols: data.cols,
                checked: data.checked,
            },
            accum: RawBuffer {
                buf: accum.buf.as_device_ptr().as_ptr() as *const Val,
                rows: accum.rows,
                cols: accum.cols,
                // Disable checked reads/writes for CUDA so that in-place
                // changes can be made during phase2 and phase3 of accumulation.
                checked: false,
            },
            global: RawBuffer {
                buf: global.buf.as_device_ptr().as_ptr() as *const Val,
                rows: global.rows,
                cols: global.cols,
                checked: global.checked,
            },
            mix: RawBuffer {
                buf: mix.buf.as_device_ptr().as_ptr() as *const Val,
                rows: mix.rows,
                cols: mix.cols,
                checked: mix.checked,
            },
        };
        let preflight = RawPreflightTrace {
            cycles: preflight.cycles.as_ptr(),
            txns: preflight.txns.as_ptr(),
            bigint_bytes: preflight.bigint_bytes.as_ptr(),
            txns_len: preflight.txns.len() as u32,
            bigint_bytes_len: preflight.bigint_bytes.len() as u32,
            table_split_cycle: preflight.table_split_cycle,
        };
        ffi_wrap(|| unsafe {
            risc0_circuit_rv32im_cuda_accum(
                self.hal.stream.as_inner(),
                &buffers,
                &preflight,
                cycles as u32,
            )
        })
    }
}

impl<CH: CudaHash> CircuitHal<CudaHal<CH>> for CudaCircuitHal<CH> {
    fn accumulate(
        &self,
        _preflight: &AccumPreflight,
        _ctrl: &CudaBuffer<Val>,
        _io: &CudaBuffer<Val>,
        _data: &CudaBuffer<Val>,
        _mix: &CudaBuffer<Val>,
        _accum: &CudaBuffer<Val>,
        _steps: usize,
    ) {
    }

    fn eval_check(
        &self,
        check: &CudaBuffer<Val>,
        groups: &[&CudaBuffer<Val>],
        globals: &[&CudaBuffer<Val>],
        poly_mix: ExtVal,
        po2: usize,
        steps: usize,
    ) {
        scope!("eval_check");

        let accum = groups[REGISTER_GROUP_ACCUM];
        let ctrl = groups[REGISTER_GROUP_CODE];
        let data = groups[REGISTER_GROUP_DATA];
        let mix = globals[GLOBAL_MIX];
        let out = globals[GLOBAL_OUT];
        tracing::debug!(
            "check: {}, ctrl: {}, data: {}, accum: {}, mix: {} out: {}",
            check.size(),
            ctrl.size(),
            data.size(),
            accum.size(),
            mix.size(),
            out.size()
        );
        tracing::debug!(
            "total: {}",
            (check.size() + ctrl.size() + data.size() + accum.size() + mix.size() + out.size()) * 4
        );

        const EXP_PO2: usize = log2_ceil(INV_RATE);
        let domain = steps * INV_RATE;
        let rou = Val::ROU_FWD[po2 + EXP_PO2];

        tracing::debug!("steps: {steps}, domain: {domain}, po2: {po2}, rou: {rou:?}");
        let poly_mix_pows = map_pow(poly_mix, POLY_MIX_POWERS);
        let poly_mix_pows: &[u32; ExtVal::EXT_SIZE * NUM_POLY_MIX_POWERS] =
            ExtVal::as_u32_slice(poly_mix_pows.as_slice())
                .try_into()
                .unwrap();

        ffi_wrap(|| unsafe {
            risc0_circuit_rv32im_cuda_eval_check(
                self.hal.stream.as_inner(),
                check.as_device_ptr(),
                ctrl.as_device_ptr(),
                data.as_device_ptr(),
                accum.as_device_ptr(),
                mix.as_device_ptr(),
                out.as_device_ptr(),
                &rou as *const Val,
                po2 as u32,
                domain as u32,
                poly_mix_pows.as_ptr(),
            )
        })
        .unwrap();
    }
}

pub type CudaCircuitHalPoseidon2 = CudaCircuitHal<CudaHashPoseidon2>;

pub fn segment_prover() -> Result<Box<dyn SegmentProver>> {
    let hal_factory = || {
        let hal = Rc::new(CudaHalPoseidon2::new());
        let circuit_hal = Rc::new(CudaCircuitHalPoseidon2::new(hal.clone()));
        (hal, circuit_hal)
    };
    Ok(Box::new(SegmentProverImpl::new(hal_factory)))
}

#[cfg(test)]
mod tests {
    use std::rc::Rc;

    use rand::Rng;
    use risc0_core::field::baby_bear::BabyBear;
    use risc0_zkp::{
        adapter::CircuitInfo as _,
        core::hash::sha::Sha256HashSuite,
        hal::{Hal, cpu::CpuHal, cuda::CudaHalSha256},
    };
    use test_log::test;

    use super::*;
    use crate::{
        prove::hal::cpu::CpuCircuitHal,
        zirgen::{CircuitImpl, taps::TAPSET},
    };

    pub struct EvalCheckParams {
        pub po2: usize,
        pub steps: usize,
        pub domain: usize,
        pub code: Vec<Val>,
        pub data: Vec<Val>,
        pub accum: Vec<Val>,
        pub mix: Vec<Val>,
        pub out: Vec<Val>,
        pub poly_mix: ExtVal,
    }

    impl EvalCheckParams {
        pub fn new(po2: usize) -> Self {
            let mut rng = rand::rng();
            let steps = 1 << po2;
            let domain = steps * INV_RATE;
            let code_size = TAPSET.group_size(REGISTER_GROUP_CODE);
            let data_size = TAPSET.group_size(REGISTER_GROUP_DATA);
            let accum_size = TAPSET.group_size(REGISTER_GROUP_ACCUM);
            let code = random_fps(&mut rng, code_size * domain);
            let data = random_fps(&mut rng, data_size * domain);
            let accum = random_fps(&mut rng, accum_size * domain);
            let mix = random_fps(&mut rng, CircuitImpl::MIX_SIZE);
            let out = random_fps(&mut rng, CircuitImpl::OUTPUT_SIZE);
            let poly_mix = ExtVal::random(&mut rng);
            tracing::debug!("code: {} bytes", code.len() * 4);
            tracing::debug!("data: {} bytes", data.len() * 4);
            tracing::debug!("accum: {} bytes", accum.len() * 4);
            tracing::debug!("mix: {} bytes", mix.len() * 4);
            tracing::debug!("out: {} bytes", out.len() * 4);
            Self {
                po2,
                steps,
                domain,
                code,
                data,
                accum,
                mix,
                out,
                poly_mix,
            }
        }
    }

    fn random_fps<E: Elem>(rng: &mut impl Rng, size: usize) -> Vec<E> {
        let mut ret = Vec::new();
        for _ in 0..size {
            ret.push(E::random(rng));
        }
        ret
    }

    #[test]
    #[gpu_guard::gpu_guard]
    fn eval_check() {
        const PO2: usize = 4;
        let cpu_hal: CpuHal<BabyBear> = CpuHal::new(Sha256HashSuite::new_suite());
        let cpu_eval = CpuCircuitHal;
        let gpu_hal = Rc::new(CudaHalSha256::new());
        let gpu_eval = super::CudaCircuitHal::new(gpu_hal.clone());
        let params = EvalCheckParams::new(PO2);
        let check1 = eval_check_impl(&params, &cpu_hal, &cpu_eval);
        let check2 = eval_check_impl(&params, gpu_hal.as_ref(), &gpu_eval);
        assert_eq!(check1, check2);
    }

    fn eval_check_impl<H, C>(params: &EvalCheckParams, hal: &H, circuit_hal: &C) -> Vec<H::Elem>
    where
        H: Hal<Elem = Val, ExtElem = ExtVal>,
        C: CircuitHal<H>,
    {
        let check = hal.alloc_elem("check", ExtVal::EXT_SIZE * params.domain);
        let code = hal.copy_from_elem("code", &params.code);
        let data = hal.copy_from_elem("data", &params.data);
        let accum = hal.copy_from_elem("accum", &params.accum);
        let mix = hal.copy_from_elem("mix", &params.mix);
        let out = hal.copy_from_elem("out", &params.out);
        circuit_hal.eval_check(
            &check,
            &[&accum, &code, &data],
            &[&mix, &out],
            params.poly_mix,
            params.po2,
            params.steps,
        );
        let mut ret = vec![H::Elem::ZERO; check.size()];
        check.view(|view| {
            ret.clone_from_slice(view);
        });
        ret
    }
}
