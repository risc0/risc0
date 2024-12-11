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
void step_Top_7(ExecContext& ctx,MutableBuf arg0)   {
// Reg(<preamble>:4)
// ControlState(zirgen/circuit/keccak2/top.zir:403)
// ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:457)
set(ctx,arg0, 12, Val(5));
// ControlState(zirgen/circuit/keccak2/top.zir:404)
set(ctx,arg0, 13, Val(0));
// ControlState(zirgen/circuit/keccak2/top.zir:405)
set(ctx,arg0, 14, Val(0));
// ControlState(zirgen/circuit/keccak2/top.zir:406)
set(ctx,arg0, 15, get(ctx,arg0, 15, 1));
return ;
}
void step_Top_23(ExecContext& ctx,MutableBuf arg0)   {
// ControlState(zirgen/circuit/keccak2/top.zir:403)
// ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:464)
set(ctx,arg0, 12, Val(1));
// ControlState(zirgen/circuit/keccak2/top.zir:404)
set(ctx,arg0, 13, Val(0));
// ControlState(zirgen/circuit/keccak2/top.zir:405)
set(ctx,arg0, 14, Val(0));
// ControlState(zirgen/circuit/keccak2/top.zir:406)
set(ctx,arg0, 15, Val(0));
return ;
}

} // namespace risc0::circuit::keccak::cpu
