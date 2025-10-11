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

__device__ void step_Top_2(ExecContext& ctx,MutableBuf arg0)   {
// ControlState(zirgen/circuit/keccak/top.zir:296)
// ComputeCurrentStep(zirgen/circuit/keccak/top.zir:336)
set(ctx,arg0, 11, Val(9));
// ControlState(zirgen/circuit/keccak/top.zir:297)
set(ctx,arg0, 12, Val(0));
// ControlState(zirgen/circuit/keccak/top.zir:298)
set(ctx,arg0, 13, Val(0));
return ;
}
__device__ void step_Top_18(ExecContext& ctx,MutableBuf arg0)   {
// NextPreimage(zirgen/circuit/keccak/top.zir:184)
// CheckNextPreimage(zirgen/circuit/keccak/top.zir:322)
// Poseidon2NextRound(zirgen/circuit/keccak/top.zir:317)
// ComputeCurrentStep(zirgen/circuit/keccak/top.zir:348)
Val x1 = INVOKE_EXTERN(ctx,nextPreimage);
// builtin NondetReg
set(ctx,arg0, 941, x1);
Val x2 = get(ctx,arg0, 941, 0);
if (to_size_t(x2)) {
// CheckNextPreimage(zirgen/circuit/keccak/top.zir:325)
step_Top_16(ctx,arg0);
}
if (to_size_t((Val(1) - x2))) {
step_Top_17(ctx,arg0);
}
return ;
}

} // namespace risc0::circuit::keccak::cuda
