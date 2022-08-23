// This code is automatically generated

use risc0_zkp::{
    adapter::{MixState, PolyFp, PolyFpContext, PolyFpStep, PolyFpStepDef},
    core::fp::Fp,
};

use super::CircuitImpl;

#[rustfmt::skip]
const DEF: PolyFpStepDef = PolyFpStepDef {
    block: &[PolyFpStep::Const(1, "circuits/fib/gen_fib.cpp:16"),
PolyFpStep::True("circuits/fib/gen_fib.cpp:9"),
PolyFpStep::Get(0, 0, 0, "circuits/fib/gen_fib.cpp:15"),
PolyFpStep::Get(2, 0, 0, "circuits/fib/gen_fib.cpp:16"),
PolyFpStep::Sub(2, 0, "circuits/fib/gen_fib.cpp:16"),
PolyFpStep::AndEqz(0, 3, "circuits/fib/gen_fib.cpp:16"),
PolyFpStep::AndCond(0, 1, 1, "circuits/fib/gen_fib.cpp:15"),
PolyFpStep::Get(0, 1, 0, "circuits/fib/gen_fib.cpp:18"),
PolyFpStep::Get(2, 0, 1, "circuits/fib/gen_fib.cpp:19"),
PolyFpStep::Get(2, 0, 2, "circuits/fib/gen_fib.cpp:19"),
PolyFpStep::Add(5, 6, "circuits/fib/gen_fib.cpp:19"),
PolyFpStep::Sub(2, 7, "circuits/fib/gen_fib.cpp:19"),
PolyFpStep::AndEqz(0, 8, "circuits/fib/gen_fib.cpp:19"),
PolyFpStep::AndCond(2, 4, 3, "circuits/fib/gen_fib.cpp:18"),
PolyFpStep::Get(0, 2, 0, "circuits/fib/gen_fib.cpp:21"),
PolyFpStep::GetGlobal(1, 0, "circuits/fib/gen_fib.cpp:23"),
PolyFpStep::Sub(10, 2, "circuits/fib/gen_fib.cpp:23"),
PolyFpStep::AndEqz(0, 11, "circuits/fib/gen_fib.cpp:23"),
PolyFpStep::AndCond(4, 9, 5, "circuits/fib/gen_fib.cpp:21"),
PolyFpStep::Add(1, 4, "circuits/fib/gen_fib.cpp:27"),
PolyFpStep::Add(12, 9, "circuits/fib/gen_fib.cpp:27"),
PolyFpStep::Get(4, 0, 0, "circuits/fib/gen_fib.cpp:28"),
PolyFpStep::Sub(14, 0, "circuits/fib/gen_fib.cpp:28"),
PolyFpStep::AndEqz(0, 15, "circuits/fib/gen_fib.cpp:28"),
PolyFpStep::AndCond(6, 13, 7, "circuits/fib/gen_fib.cpp:27"),
],
    ret: 8,
};

impl PolyFp for CircuitImpl {
    fn poly_fp(&self, ctx: &PolyFpContext, args: &[&[Fp]]) -> MixState {
        DEF.step(ctx, args)
    }
}
