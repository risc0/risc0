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

use std::{ffi::CString, rc::Rc};

use fil_rustacuda as rustacuda;
use risc0_core::field::{
    baby_bear::{BabyBearElem, BabyBearExtElem},
    RootsOfUnity,
};
use risc0_zkp::{
    core::log2_ceil,
    hal::{
        cuda::{BufferImpl as CudaBuffer, CudaHal},
        Buffer, EvalCheck,
    },
    INV_RATE,
};
use rustacuda::{launch, prelude::*};

use crate::{
    GLOBAL_MIX, GLOBAL_OUT, REGISTER_GROUP_ACCUM, REGISTER_GROUP_CODE, REGISTER_GROUP_DATA,
};

const KERNELS_FATBIN: &[u8] = include_bytes!(env!("RV32IM_CUDA_PATH"));

pub struct CudaEvalCheck {
    hal: Rc<CudaHal>, // retain a reference to ensure the context remains valid
    module: Module,
}

impl CudaEvalCheck {
    #[tracing::instrument(name = "CudaEvalCheck::new", skip_all)]
    pub fn new(hal: Rc<CudaHal>) -> Self {
        let module = Module::load_from_bytes(KERNELS_FATBIN).unwrap();
        Self { hal, module }
    }
}

impl<'a> EvalCheck<CudaHal> for CudaEvalCheck {
    #[tracing::instrument(skip_all)]
    fn eval_check(
        &self,
        check: &CudaBuffer<BabyBearElem>,
        groups: &[&CudaBuffer<BabyBearElem>],
        globals: &[&CudaBuffer<BabyBearElem>],
        poly_mix: BabyBearExtElem,
        po2: usize,
        steps: usize,
    ) {
        let code = groups[REGISTER_GROUP_CODE];
        let data = groups[REGISTER_GROUP_DATA];
        let accum = groups[REGISTER_GROUP_ACCUM];
        let mix = globals[GLOBAL_MIX];
        let out = globals[GLOBAL_OUT];
        log::debug!(
            "check: {}, code: {}, data: {}, accum: {}, mix: {} out: {}",
            check.size(),
            code.size(),
            data.size(),
            accum.size(),
            mix.size(),
            out.size()
        );
        log::debug!(
            "total: {}",
            (check.size() + code.size() + data.size() + accum.size() + mix.size() + out.size()) * 4
        );

        const EXP_PO2: usize = log2_ceil(INV_RATE);
        let domain = steps * INV_RATE;
        let rou = BabyBearElem::ROU_FWD[po2 + EXP_PO2];

        let poly_mix = CudaBuffer::copy_from("poly_mix", &[poly_mix]);
        let rou = CudaBuffer::copy_from("rou", &[rou]);
        let po2 = CudaBuffer::copy_from("po2", &[po2 as u32]);
        let size = CudaBuffer::copy_from("size", &[domain as u32]);

        let stream = Stream::new(StreamFlags::DEFAULT, None).unwrap();

        let kernel_name = CString::new("eval_check").unwrap();
        let kernel = self.module.get_function(&kernel_name).unwrap();
        let params = self.hal.compute_simple_params(domain);
        unsafe {
            launch!(kernel<<<params.0, params.1, 0, stream>>>(
                check.as_device_ptr(),
                code.as_device_ptr(),
                data.as_device_ptr(),
                accum.as_device_ptr(),
                mix.as_device_ptr(),
                out.as_device_ptr(),
                poly_mix.as_device_ptr(),
                rou.as_device_ptr(),
                po2.as_device_ptr(),
                size.as_device_ptr()
            ))
            .unwrap();
        }
        stream.synchronize().unwrap();
    }
}

#[cfg(test)]
mod tests {
    use std::rc::Rc;

    use risc0_zkp::hal::{cpu::BabyBearSha256CpuHal, cuda::CudaHal};
    use test_log::test;

    use crate::cpu::CpuEvalCheck;

    #[test]
    fn eval_check() {
        const PO2: usize = 4;
        let circuit = crate::CircuitImpl::new();
        let cpu_hal = BabyBearSha256CpuHal::new();
        let cpu_eval = CpuEvalCheck::new(&circuit);
        let gpu_hal = Rc::new(CudaHal::new());
        let gpu_eval = super::CudaEvalCheck::new(gpu_hal.clone());
        crate::testutil::eval_check(&cpu_hal, cpu_eval, gpu_hal.as_ref(), gpu_eval, PO2);
    }
}
