use std::rc::Rc;

use super::{
    cuda::{CudaHal, CudaHash},
    eltwise::Eltwise,
    AnyBuffer, Hal,
};
use cust::prelude::*;
use risc0_core::field::{
    baby_bear::{BabyBear, BabyBearElem, BabyBearExtElem},
    ExtElem,
};

struct EltwiseImp<H: Hal> {
    hal: Rc<H>,
}

#[cfg(feature = "cuda")]
impl<CH: CudaHash> Eltwise<BabyBear> for EltwiseImp<CudaHal<CH>> {
    #[tracing::instrument(skip_all)]
    fn eltwise_add_elem(
        &self,
        output: &dyn AnyBuffer<BabyBearElem>,
        input1: &dyn AnyBuffer<BabyBearElem>,
        input2: &dyn AnyBuffer<BabyBearElem>,
    ) {
        let output = self.hal.get_buffer(output);
        let input1 = self.hal.get_buffer(input1);
        let input2 = self.hal.get_buffer(input2);

        assert_eq!(output.size(), input1.size());
        assert_eq!(output.size(), input2.size());
        let count = output.size();

        let kernel = self.hal.module.get_function("eltwise_add_fp").unwrap();
        let params = self.hal.compute_simple_params(count);
        unsafe {
            let stream = &self.hal.stream;
            launch!(kernel<<<params.0, params.1, 0, stream>>>(
                output.as_device_ptr(),
                input1.as_device_ptr(),
                input2.as_device_ptr(),
                count
            ))
            .unwrap();
        }
        self.hal.stream.synchronize().unwrap();
    }

    #[tracing::instrument(skip_all)]
    fn eltwise_sum_extelem(
        &self,
        output: &dyn AnyBuffer<BabyBearElem>,
        input: &dyn AnyBuffer<BabyBearExtElem>,
    ) {
        let output = self.hal.get_buffer(output);
        let input = self.hal.get_buffer(input);

        let count = output.size() / BabyBearExtElem::EXT_SIZE;
        let to_add = input.size() / count;
        assert_eq!(output.size(), count * BabyBearExtElem::EXT_SIZE);
        assert_eq!(input.size(), count * to_add);

        let kernel = self.hal.module.get_function("eltwise_sum_fpext").unwrap();
        let params = self.hal.compute_simple_params(output.size());
        unsafe {
            let stream = &self.hal.stream;
            launch!(kernel<<<params.0, params.1, 0, stream>>>(
                output.as_device_ptr(),
                input.as_device_ptr(),
                to_add,
                count
            ))
            .unwrap();
        }
        self.hal.stream.synchronize().unwrap();
    }
}

#[cfg(cuda)]
#[distributed_slice(super::REGISTERED_INTERFACES)]
static BABYBEAR_CUDA_SHA256: fn() -> Registration = || {
    Registration::new::<CudaHal<CudaHashSha256>, dyn Eltwise<BabyBear>>(|hal| {
        Box::new(EltwiseImp { hal })
    })
};
