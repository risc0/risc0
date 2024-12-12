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

#include "steps.h"
#include "witgen.h"

namespace risc0::circuit::keccak::cpu {
void step_Top_5(ExecContext& ctx,MutableBuf arg0)   {
// ControlState(zirgen/circuit/keccak2/top.zir:404)
// Top(zirgen/circuit/keccak2/top.zir:483)
Val x1 = get(ctx,arg0, 13, 1);
if (to_size_t(x1)) {
// ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:451)
step_Top_3(ctx,arg0);
}
if (to_size_t((Val(1) - x1))) {
step_Top_4(ctx,arg0);
}
return ;
}
void step_Top_21(ExecContext& ctx,MutableBuf arg0)   {
// NextPreimage(zirgen/circuit/keccak2/top.zir:280)
// ShaNextBlock(zirgen/circuit/keccak2/top.zir:436)
// ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:463)
Val x1 = INVOKE_EXTERN(ctx,nextPreimage);
set(ctx,arg0, 933, x1);
Val x2 = get(ctx,arg0, 933, 0);
if (to_size_t(x2)) {
// ShaNextBlock(zirgen/circuit/keccak2/top.zir:438)
step_Top_19(ctx,arg0);
}
if (to_size_t((Val(1) - x2))) {
step_Top_20(ctx,arg0);
}
return ;
}

} // namespace risc0::circuit::keccak::cpu
