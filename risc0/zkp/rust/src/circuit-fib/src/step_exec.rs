// This code is automatically generated

use risc0_zkp::{
    adapter::{CircuitStep, CircuitStepContext, CircuitStepDef, CircuitStepExec, CustomStep},
    core::fp::Fp,
};
use anyhow::Result;

use super::CircuitImpl;

#[rustfmt::skip]
const DEF: CircuitStepDef = CircuitStepDef {
    block: &[CircuitStep::Const(1, "circuits/fib/gen_fib.cpp:16"),
CircuitStep::Get(0, 0, 0, "circuits/fib/gen_fib.cpp:15"),
CircuitStep::If(1, &[CircuitStep::Set(2, 0, 0, "circuits/fib/gen_fib.cpp:16"),
], "circuits/fib/gen_fib.cpp:15"),
CircuitStep::Get(0, 1, 0, "circuits/fib/gen_fib.cpp:18"),
CircuitStep::If(2, &[CircuitStep::Get(2, 0, 1, "circuits/fib/gen_fib.cpp:19"),
CircuitStep::Get(2, 0, 2, "circuits/fib/gen_fib.cpp:19"),
CircuitStep::Add(3, 4, "circuits/fib/gen_fib.cpp:19"),
CircuitStep::Set(2, 5, 0, "circuits/fib/gen_fib.cpp:19"),
], "circuits/fib/gen_fib.cpp:18"),
CircuitStep::Get(0, 2, 0, "circuits/fib/gen_fib.cpp:21"),
CircuitStep::If(3, &[CircuitStep::Get(2, 0, 0, "circuits/fib/gen_fib.cpp:23"),
CircuitStep::SetGlobal(1, 4, 0, "circuits/fib/gen_fib.cpp:23"),
], "circuits/fib/gen_fib.cpp:21"),
CircuitStep::Sub(0, 3, "circuits/fib/gen_fib.cpp:25"),
],
    ret: 4,
};

impl<S: CustomStep> CircuitStepExec<S> for CircuitImpl {
    #[allow(unused)]
    fn step_exec(
        &self,
        ctx: &CircuitStepContext,
        custom: &mut S,
        args: &mut [&mut [Fp]],
    ) -> Result<Fp> {
        DEF.step(ctx, custom, args)
    }
}
