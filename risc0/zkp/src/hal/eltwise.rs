use super::{cpu::CpuHal, Buffer, Hal, Registration};
use linkme::distributed_slice;
use ndarray::{ArrayView, ArrayViewMut, Axis};
use rayon::prelude::*;
use risc0_core::field::{baby_bear::BabyBear, Elem, ExtElem, Field};
use std::rc::Rc;

pub trait Eltwise<F: Field> {
    fn eltwise_add_elem(
        &self,
        out: &dyn Buffer<F::Elem>,
        a: &dyn Buffer<F::Elem>,
        b: &dyn Buffer<F::Elem>,
    );
    fn eltwise_sum_extelem(&self, output: &dyn Buffer<F::Elem>, input: &dyn Buffer<F::ExtElem>);
}

struct EltwiseImp<H: Hal> {
    _hal: Rc<H>,
}

impl<F: Field> Eltwise<F> for EltwiseImp<CpuHal<F>> {
    #[tracing::instrument(skip_all)]
    fn eltwise_add_elem(
        &self,
        output: &dyn Buffer<F::Elem>,
        input1: &dyn Buffer<F::Elem>,
        input2: &dyn Buffer<F::Elem>,
    ) {
        assert_eq!(output.size(), input1.size());
        assert_eq!(output.size(), input2.size());
        let mut output = output.as_sync_slice();
        let input1 = input1.as_sync_slice();
        let input2 = input2.as_sync_slice();
        (&mut output[..], &input1[..], &input2[..])
            .into_par_iter()
            .for_each(|(o, a, b)| {
                *o = *a + *b;
            });
        output.flush();
    }

    #[tracing::instrument(skip_all)]
    fn eltwise_sum_extelem(&self, output: &dyn Buffer<F::Elem>, input: &dyn Buffer<F::ExtElem>) {
        let mut output_slice = output.as_sync_slice();
        let input = input.as_sync_slice();

        let count = output_slice.size() / F::ExtElem::EXT_SIZE;
        let to_add = input.size() / count;
        assert_eq!(output_slice.size(), count * F::ExtElem::EXT_SIZE);
        assert_eq!(input.size(), count * to_add);
        let mut output =
            ArrayViewMut::from_shape((F::ExtElem::EXT_SIZE, count), &mut output_slice[..]).unwrap();
        let output = output.axis_iter_mut(Axis(1)).into_par_iter();
        let input = ArrayView::from_shape((to_add, count), &input[..]).unwrap();
        let input = input.axis_iter(Axis(1)).into_par_iter();
        output.zip(input).for_each(|(mut output, input)| {
            let mut sum = F::ExtElem::ZERO;
            for i in input {
                sum += *i;
            }
            for i in 0..F::ExtElem::EXT_SIZE {
                output[i] = sum.subelems()[i]
            }
        });
        output_slice.flush();
    }
}

#[distributed_slice(super::REGISTERED_INTERFACES)]
static BABYBEAR_CPU: fn() -> Registration = || {
    Registration::new::<CpuHal<BabyBear>, dyn Eltwise<BabyBear>>(|_hal| {
        Box::new(EltwiseImp { _hal })
    })
};
