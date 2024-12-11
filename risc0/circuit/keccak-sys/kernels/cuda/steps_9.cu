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

__device__ void step_Top_8(ExecContext& ctx, MutableBuf arg0) {
  // ControlState(zirgen/circuit/keccak2/top.zir:403)
  // ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:458)
  set(ctx, arg0, 12, Val(6));
  // ControlState(zirgen/circuit/keccak2/top.zir:404)
  set(ctx, arg0, 13, Val(0));
  // ControlState(zirgen/circuit/keccak2/top.zir:405)
  set(ctx, arg0, 14, Val(0));
  // ControlState(zirgen/circuit/keccak2/top.zir:406)
  set(ctx, arg0, 15, get(ctx, arg0, 15, 1));
  return;
}
__device__ void step_Top_24(ExecContext& ctx, MutableBuf arg0) {
  // ControlState(zirgen/circuit/keccak2/top.zir:405)
  Val x1 = get(ctx, arg0, 14, 1);
  // ControlState(zirgen/circuit/keccak2/top.zir:406)
  Val x2 = get(ctx, arg0, 15, 1);
  // ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:451)
  Val x3 = (Val(1) - get(ctx, arg0, 13, 1));
  if (to_size_t(get(ctx, arg0, 0, 1))) {
    // ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:448)
    step_Top_1(ctx, arg0);
  }
  if (to_size_t(get(ctx, arg0, 1, 1))) {
    step_Top_2(ctx, arg0);
  }
  if (to_size_t(get(ctx, arg0, 2, 1))) {
    step_Top_5(ctx, arg0);
  }
  if (to_size_t(get(ctx, arg0, 3, 1))) {
    step_Top_6(ctx, arg0);
  }
  if (to_size_t(get(ctx, arg0, 4, 1))) {
    step_Top_7(ctx, arg0);
  }
  if (to_size_t(get(ctx, arg0, 5, 1))) {
    step_Top_8(ctx, arg0);
  }
  if (to_size_t(get(ctx, arg0, 6, 1))) {
    step_Top_9(ctx, arg0);
  }
  if (to_size_t(get(ctx, arg0, 7, 1))) {
    step_Top_10(ctx, arg0);
  }
  if (to_size_t(get(ctx, arg0, 8, 1))) {
    step_Top_13(ctx, arg0);
  }
  if (to_size_t(get(ctx, arg0, 9, 1))) {
    step_Top_16(ctx, arg0);
  }
  if (to_size_t(get(ctx, arg0, 10, 1))) {
    step_Top_22(ctx, arg0);
  }
  if (to_size_t(get(ctx, arg0, 11, 1))) {
    step_Top_23(ctx, arg0);
  }
  return;
}

} // namespace risc0::circuit::keccak::cuda
