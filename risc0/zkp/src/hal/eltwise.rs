use super::{cpu::CpuHal, AnyBuffer, Hal, Registration};
use linkme::distributed_slice;
use ndarray::{ArrayView, ArrayViewMut, Axis};
use rayon::prelude::*;
use risc0_core::field::{baby_bear::BabyBear, Elem, ExtElem, Field};
use std::marker::PhantomData;

pub trait Eltwise<F: Field> {
    fn eltwise_add_elem(
        &self,
        out: &dyn AnyBuffer<F::Elem>,
        a: &dyn AnyBuffer<F::Elem>,
        b: &dyn AnyBuffer<F::Elem>,
    );
    fn eltwise_sum_extelem(
        &self,
        output: &dyn AnyBuffer<F::Elem>,
        input: &dyn AnyBuffer<F::ExtElem>,
    );
}

struct EltwiseImp<H: Hal> {
    phantom: PhantomData<H>,
}

impl<F: Field> Eltwise<F> for EltwiseImp<CpuHal<F>> {
    #[tracing::instrument(skip_all)]
    fn eltwise_add_elem(
        &self,
        output: &dyn AnyBuffer<F::Elem>,
        input1: &dyn AnyBuffer<F::Elem>,
        input2: &dyn AnyBuffer<F::Elem>,
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
    }

    #[tracing::instrument(skip_all)]
    fn eltwise_sum_extelem(
        &self,
        output: &dyn AnyBuffer<F::Elem>,
        input: &dyn AnyBuffer<F::ExtElem>,
    ) {
        let mut output = output.as_sync_slice();
        let input = input.as_sync_slice();

        let count = output.size() / F::ExtElem::EXT_SIZE;
        let to_add = input.size() / count;
        assert_eq!(output.size(), count * F::ExtElem::EXT_SIZE);
        assert_eq!(input.size(), count * to_add);
        let mut output =
            ArrayViewMut::from_shape((F::ExtElem::EXT_SIZE, count), &mut output[..]).unwrap();
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
    }
}

#[distributed_slice(super::REGISTERED_INTERFACES)]
static BABYBEAR_CPU: fn() -> Registration = || {
    Registration::new::<CpuHal<BabyBear>, dyn Eltwise<BabyBear>>(|_hal| {
        Box::new(EltwiseImp {
            phantom: PhantomData::default(),
        })
    })
};
