// This code is automatically generated

use risc0_zkp::{
    adapter::{MixState, PolyExt, PolyExtContext, PolyExtStep, PolyExtStepDef},
    core::{fp::Fp, fp4::Fp4},
};

use super::CircuitImpl;

#[rustfmt::skip]
const DEF: PolyExtStepDef = PolyExtStepDef {
    block: &[PolyExtStep::Const(1, "circuits/fib/gen_fib.cpp:16"),
PolyExtStep::True("circuits/fib/gen_fib.cpp:9"),
PolyExtStep::Get(1, "circuits/fib/gen_fib.cpp:15"),
PolyExtStep::Get(4, "circuits/fib/gen_fib.cpp:16"),
PolyExtStep::Sub(2, 0, "circuits/fib/gen_fib.cpp:16"),
PolyExtStep::AndEqz(0, 3, "circuits/fib/gen_fib.cpp:16"),
PolyExtStep::AndCond(0, 1, 1, "circuits/fib/gen_fib.cpp:15"),
PolyExtStep::Get(2, "circuits/fib/gen_fib.cpp:18"),
PolyExtStep::Get(5, "circuits/fib/gen_fib.cpp:19"),
PolyExtStep::Get(6, "circuits/fib/gen_fib.cpp:19"),
PolyExtStep::Add(5, 6, "circuits/fib/gen_fib.cpp:19"),
PolyExtStep::Sub(2, 7, "circuits/fib/gen_fib.cpp:19"),
PolyExtStep::AndEqz(0, 8, "circuits/fib/gen_fib.cpp:19"),
PolyExtStep::AndCond(2, 4, 3, "circuits/fib/gen_fib.cpp:18"),
PolyExtStep::Get(3, "circuits/fib/gen_fib.cpp:21"),
PolyExtStep::GetGlobal(0, 0, "circuits/fib/gen_fib.cpp:23"),
PolyExtStep::Sub(10, 2, "circuits/fib/gen_fib.cpp:23"),
PolyExtStep::AndEqz(0, 11, "circuits/fib/gen_fib.cpp:23"),
PolyExtStep::AndCond(4, 9, 5, "circuits/fib/gen_fib.cpp:21"),
PolyExtStep::Add(1, 4, "circuits/fib/gen_fib.cpp:27"),
PolyExtStep::Add(12, 9, "circuits/fib/gen_fib.cpp:27"),
PolyExtStep::Get(0, "circuits/fib/gen_fib.cpp:28"),
PolyExtStep::Sub(14, 0, "circuits/fib/gen_fib.cpp:28"),
PolyExtStep::AndEqz(0, 15, "circuits/fib/gen_fib.cpp:28"),
PolyExtStep::AndCond(6, 13, 7, "circuits/fib/gen_fib.cpp:27"),
],
    ret: 8,
};

impl PolyExt for CircuitImpl {
    fn poly_ext(&self, ctx: &PolyExtContext, u: &[Fp4], args: &[&[Fp]]) -> MixState {
        DEF.step(ctx, u, args)
    }
}
