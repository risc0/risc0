// Copyright 2024 RISC Zero, Inc.
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

// This code is automatically generated

use risc0_zkp::{
    adapter::{MixState, PolyExt, PolyExtStep, PolyExtStepDef},
    field::baby_bear::{BabyBear, BabyBearElem, BabyBearExtElem},
};

use super::CircuitImpl;

#[allow(missing_docs)]
#[rustfmt::skip]
pub const DEF: PolyExtStepDef = PolyExtStepDef {
    block: &[PolyExtStep::Const(5), // loc(unknown)
PolyExtStep::Const(1), // loc(unknown)
PolyExtStep::True, // loc(unknown)
PolyExtStep::Get(2), // loc(callsite(unknown at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :29:19) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :28:2) at unknown))))
PolyExtStep::Get(3), // loc(callsite(unknown at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :30:21) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :28:2) at unknown))))
PolyExtStep::Get(4), // loc(callsite(unknown at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :31:21) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :28:2) at unknown))))
PolyExtStep::Get(5), // loc(callsite(unknown at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :32:25) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :28:2) at unknown))))
PolyExtStep::Get(6), // loc(callsite(unknown at callsite( OneHot ( zirgen/dsl/examples/calculator/calculator.zir :13:36) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :33:20) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :28:2) at unknown)))))
PolyExtStep::Get(7), // loc(callsite(unknown at callsite( OneHot ( zirgen/dsl/examples/calculator/calculator.zir :13:36) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :33:20) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :28:2) at unknown)))))
PolyExtStep::Sub(1, 6), // loc(callsite(unknown at callsite( OneHot ( zirgen/dsl/examples/calculator/calculator.zir :15:28) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :33:20) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :28:2) at unknown)))))
PolyExtStep::Mul(6, 8), // loc(callsite(unknown at callsite( OneHot ( zirgen/dsl/examples/calculator/calculator.zir :15:21) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :33:20) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :28:2) at unknown)))))
PolyExtStep::AndEqz(0, 9), // loc(callsite( OneHot ( zirgen/dsl/examples/calculator/calculator.zir :15:37) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :33:20) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :28:2) at unknown))))
PolyExtStep::Sub(1, 7), // loc(callsite(unknown at callsite( OneHot ( zirgen/dsl/examples/calculator/calculator.zir :15:28) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :33:20) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :28:2) at unknown)))))
PolyExtStep::Mul(7, 10), // loc(callsite(unknown at callsite( OneHot ( zirgen/dsl/examples/calculator/calculator.zir :15:21) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :33:20) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :28:2) at unknown)))))
PolyExtStep::AndEqz(1, 11), // loc(callsite( OneHot ( zirgen/dsl/examples/calculator/calculator.zir :15:37) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :33:20) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :28:2) at unknown))))
PolyExtStep::Add(6, 7), // loc(callsite(unknown at callsite( OneHot ( zirgen/dsl/examples/calculator/calculator.zir :17:4) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :33:20) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :28:2) at unknown)))))
PolyExtStep::Sub(12, 1), // loc(callsite( OneHot ( zirgen/dsl/examples/calculator/calculator.zir :17:32) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :33:20) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :28:2) at unknown))))
PolyExtStep::AndEqz(2, 13), // loc(callsite( OneHot ( zirgen/dsl/examples/calculator/calculator.zir :17:32) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :33:20) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :28:2) at unknown))))
PolyExtStep::Sub(7, 2), // loc(callsite( OneHot ( zirgen/dsl/examples/calculator/calculator.zir :19:56) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :33:20) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :28:2) at unknown))))
PolyExtStep::AndEqz(3, 14), // loc(callsite( OneHot ( zirgen/dsl/examples/calculator/calculator.zir :19:56) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :33:20) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :28:2) at unknown))))
PolyExtStep::Add(3, 4), // loc(callsite(unknown at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :35:10) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :28:2) at unknown))))
PolyExtStep::Get(8), // loc(callsite(unknown at callsite( Reg ( <preamble> :4:21) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :35:9) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :28:2) at unknown)))))
PolyExtStep::Sub(15, 16), // loc(callsite( Reg ( <preamble> :5:7) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :35:9) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :28:2) at unknown))))
PolyExtStep::AndEqz(0, 17), // loc(callsite( Reg ( <preamble> :5:7) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :35:9) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :28:2) at unknown))))
PolyExtStep::AndCond(4, 6, 5), // loc(callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :33:25) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :28:2) at unknown)))
PolyExtStep::Sub(3, 4), // loc(callsite(unknown at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :37:10) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :28:2) at unknown))))
PolyExtStep::Sub(18, 16), // loc(callsite( Reg ( <preamble> :5:7) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :37:9) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :28:2) at unknown))))
PolyExtStep::AndEqz(0, 19), // loc(callsite( Reg ( <preamble> :5:7) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :37:9) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :28:2) at unknown))))
PolyExtStep::AndCond(6, 7, 7), // loc(callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :33:25) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :28:2) at unknown)))
PolyExtStep::Sub(16, 5), // loc(callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :40:11) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :28:2) at unknown)))
PolyExtStep::AndEqz(8, 20), // loc(callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :40:11) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :28:2) at unknown)))
PolyExtStep::GetGlobal(0, 0), // loc(callsite(unknown at callsite( Reg ( <preamble> :4:21) at callsite( SetGlobalResult ( zirgen/dsl/examples/calculator/calculator.zir :24:18) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :41:19) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :28:2) at unknown))))))
PolyExtStep::Sub(0, 21), // loc(callsite( Reg ( <preamble> :5:7) at callsite( SetGlobalResult ( zirgen/dsl/examples/calculator/calculator.zir :24:18) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :41:19) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :28:2) at unknown)))))
PolyExtStep::AndEqz(9, 22), // loc(callsite( Reg ( <preamble> :5:7) at callsite( SetGlobalResult ( zirgen/dsl/examples/calculator/calculator.zir :24:18) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :41:19) at callsite( Top ( zirgen/dsl/examples/calculator/calculator.zir :28:2) at unknown)))))
],
    ret: 10,
};

impl PolyExt<BabyBear> for CircuitImpl {
    fn poly_ext(
        &self,
        mix: &BabyBearExtElem,
        u: &[BabyBearExtElem],
        args: &[&[BabyBearElem]],
    ) -> MixState<BabyBearExtElem> {
        DEF.step::<BabyBear>(mix, u, args)
    }
}
