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

#include "steps.cuh"
#include "witgen.h"

namespace risc0::circuit::keccak::cuda {

__device__ void step_Top_6(ExecContext& ctx, MutableBuf arg0) {
  // Reg(<preamble>:4)
  // ControlState(zirgen/circuit/keccak2/top.zir:403)
  // ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:456)
  set(ctx, arg0, 12, Val(9));
  // ControlState(zirgen/circuit/keccak2/top.zir:404)
  set(ctx, arg0, 13, Val(1));
  // ControlState(zirgen/circuit/keccak2/top.zir:405)
  set(ctx, arg0, 14, Val(0));
  // ControlState(zirgen/circuit/keccak2/top.zir:406)
  set(ctx, arg0, 15, Val(0));
  return;
}
__device__ void step_Top_22(ExecContext& ctx, MutableBuf arg0) {
  // ShaNextBlock(zirgen/circuit/keccak2/top.zir:428)
  // ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:463)
  Val x1 = (get(ctx, arg0, 14, 1) - Val(3));
  // IsZero(zirgen/circuit/keccak2/is_zero.zir:8)
  set(ctx, arg0, 934, isz(x1));
  Val x2 = get(ctx, arg0, 934, 0);
  // IsZero(zirgen/circuit/keccak2/is_zero.zir:11)
  set(ctx, arg0, 935, inv_0(x1));
  // ShaNextBlock(zirgen/circuit/keccak2/top.zir:429)
  Val x3 = (Val(1) - x2);
  // Reg(<preamble>:4)
  // ShaNextBlock(zirgen/circuit/keccak2/top.zir:430)
  set(ctx, arg0, 936, (x2 * (Val(1) - get(ctx, arg0, 13, 1))));
  Val x4 = get(ctx, arg0, 936, 0);
  // ShaNextBlock(zirgen/circuit/keccak2/top.zir:431)
  Val x5 = ((Val(1) - x3) - x4);
  if (to_size_t(x3)) {
    // ShaNextBlock(zirgen/circuit/keccak2/top.zir:432)
    step_Top_17(ctx, arg0);
  }
  if (to_size_t(x4)) {
    step_Top_18(ctx, arg0);
  }
  if (to_size_t(x5)) {
    step_Top_21(ctx, arg0);
  }
  return;
}

} // namespace risc0::circuit::keccak::cuda
