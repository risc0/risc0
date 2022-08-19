// This code is automatically generated

use crate::{
    adapter::{CircuitStep, CircuitStepAccum, CircuitStepContext, CircuitStepDef, CustomStep},
    core::fp::Fp,
};
use anyhow::Result;

use super::CircuitImpl;

#[rustfmt::skip]
const DEF: CircuitStepDef = CircuitStepDef {
    block: &[CircuitStep::Const(1, "circuits/fib/gen_fib.cpp:16"),
CircuitStep::Get(0, 0, 0, "circuits/fib/gen_fib.cpp:15"),
CircuitStep::Get(0, 1, 0, "circuits/fib/gen_fib.cpp:18"),
CircuitStep::Get(0, 2, 0, "circuits/fib/gen_fib.cpp:21"),
CircuitStep::Add(1, 2, "circuits/fib/gen_fib.cpp:27"),
CircuitStep::Add(4, 3, "circuits/fib/gen_fib.cpp:27"),
CircuitStep::If(5, &[CircuitStep::Set(4, 0, 0, "circuits/fib/gen_fib.cpp:28"),
], "circuits/fib/gen_fib.cpp:27"),
],
    ret: 0,
};

impl<S: CustomStep> CircuitStepAccum<S> for CircuitImpl {
    #[allow(unused)]
    fn step_accum(
        &self,
        ctx: &CircuitStepContext,
        custom: &mut S,
        args: &mut [&mut [Fp]],
    ) -> Result<Fp> {
        DEF.step(ctx, custom, args)
    }
}
