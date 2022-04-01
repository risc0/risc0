// Copyright 2022 Risc0, Inc.
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

#include "risc0/zkvm/circuit/final_cycle.h"

#include "risc0/zkvm/circuit/step_state.h"

namespace risc0 {

void FinalCycle::set(StepState& state) {
  Value cycle = state.code.cycle.get();
  auto prevFinal = state.getPrev(3).asFinal();
  auto decode = state.getPrev(2).asDecode();
  auto compute = state.getPrev(1).asCompute();
  auto& resultInfo = compute.resultInfo;
  ValueU32 result = resultInfo.result.get();
  BYZ_IF(resultInfo.doStore.get()) {
    Value isWOM = compute.x1.get(kMemBits + 1);
    Value memAddr = compute.x1.getPart(2, kMemBits);
    equate(compute.x1.getPart(2 + kMemBits, 32 - kMemBits - 2), 0);
    state.data.memIO.doWrite(cycle, memAddr, result, isWOM);
  }
  BYZ_IF(1 - resultInfo.doStore.get()) { state.data.memIO.doRead(cycle); }
  // Set the registers
  rdLow.set(resultInfo.setReg.get() * decode.inst.getPart(7, 3));
  rdHigh.set(resultInfo.setReg.get() * decode.inst.getPart(10, 2));
  for (int i = 1; i < 32; i++) {
    Value sel = rdLow.is(i % 8) * rdHigh.is(i / 8);
    regs[i].set((1 - sel) * prevFinal.regs[i].get() + sel * result);
  }
  // Set the new PC
  carryLow.set(pc.setPart(resultInfo.pcRaw.low(), 0, 16));
  carryHigh.set(pc.setPart(resultInfo.pcRaw.high() + carryLow.get(), 16, 16));
  risc0Log("C%u: pc: %08x Final: 0x%04x%04x -> r%u, next: %08x",
           {cycle,
            prevFinal.pc.getPart(2, kMemBits) * 4,
            resultInfo.result.high(),
            resultInfo.result.low(),
            decode.inst.getPart(7, 5),
            pc.getPart(2, kMemBits) * 4});
}

} // namespace risc0
