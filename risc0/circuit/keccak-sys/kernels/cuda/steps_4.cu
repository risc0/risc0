// Copyright 2025 RISC Zero, Inc.
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

#include "steps.cuh"
#include "witgen.h"

namespace risc0::circuit::keccak::cuda {

__device__ void step_Top_3(ExecContext& ctx,MutableBuf arg0)   {
// builtin NondetReg
// Reg(<preamble>:5)
// ControlState(zirgen/circuit/keccak/top.zir:296)
// ComputeCurrentStep(zirgen/circuit/keccak/top.zir:338)
set(ctx,arg0, 11, Val(4));
// ControlState(zirgen/circuit/keccak/top.zir:297)
set(ctx,arg0, 12, Val(0));
// ControlState(zirgen/circuit/keccak/top.zir:298)
set(ctx,arg0, 13, Val(0));
return ;
}
__device__ void step_Top_19(ExecContext& ctx,MutableBuf arg0)   {
// builtin Sub
// Poseidon2NextRound(zirgen/circuit/keccak/top.zir:311)
// ComputeCurrentStep(zirgen/circuit/keccak/top.zir:348)
Val x1 = (get(ctx,arg0, 13, 1) - Val(6));
// builtin NondetReg
// IsZero(zirgen/circuit/keccak/is_zero.zir:8)
set(ctx,arg0, 942, isz(x1));
Val x2 = get(ctx,arg0, 942, 0);
// IsZero(zirgen/circuit/keccak/is_zero.zir:11)
set(ctx,arg0, 943, inv_0(x1));
// Reg(<preamble>:5)
// ControlState(zirgen/circuit/keccak/top.zir:297)
Val x3 = get(ctx,arg0, 12, 1);
// Poseidon2NextRound(zirgen/circuit/keccak/top.zir:312)
// ComputeCurrentStep(zirgen/circuit/keccak/top.zir:348)
set(ctx,arg0, 944, (x2 * (Val(1) - x3)));
// Poseidon2NextRound(zirgen/circuit/keccak/top.zir:313)
set(ctx,arg0, 945, (x2 * x3));
if (to_size_t((Val(1) - x2))) {
// Poseidon2NextRound(zirgen/circuit/keccak/top.zir:314)
step_Top_14(ctx,arg0);
}
if (to_size_t(get(ctx,arg0, 944, 0))) {
step_Top_15(ctx,arg0);
}
if (to_size_t(get(ctx,arg0, 945, 0))) {
step_Top_18(ctx,arg0);
}
return ;
}

} // namespace risc0::circuit::keccak::cuda
