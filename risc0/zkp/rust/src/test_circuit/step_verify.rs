// This code is automatically generated

use anyhow::Result;
use crate::{
    adapter::{CircuitStep, CircuitStepContext, CircuitStepDef, CircuitStepVerify, CustomStep},
    core::fp::Fp,
};

use super::CircuitImpl;

#[rustfmt::skip]
const DEF: CircuitStepDef = CircuitStepDef {
    block: &[CircuitStep::Const(1, "circuits/fib/gen_fib.cpp:16"),
],
    ret: 0,
};

impl<S: CustomStep> CircuitStepVerify<S> for CircuitImpl {
    #[allow(unused)]
    fn step_verify(
        &self,
        ctx: &CircuitStepContext,
        custom: &mut S,
        args: &mut [&mut [Fp]],
    ) -> Result<Fp> {
        DEF.step(ctx, custom, args)
    }
}
