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

#include "risc0/zkvm/circuit/multiply_cycle.h"

#include "risc0/zkvm/circuit/step_state.h"

namespace risc0 {

void MultiplyCycle::set(StepState& state) {
  Value cycle = state.code.cycle.get();
  risc0Log("C%u: Multiply", {cycle});
  state.data.memIO.doRead(state.code.cycle.get());
  auto decode = state.getPrev(1).asDecode();
  auto final = state.getPrev(2).asFinal();
  ValueU32 R1 = decode.rs1.get();
  ValueU32 R2 = decode.rs2.get();
  ValueU32 V2 = decode.val2OH.asU32();
  auto doMultiply = [&](bool i0Signed, bool i1Signed) {
    Value curCarry = 0;
    Value sub0;
    Value sub1;
    if (i1Signed) {
      in1High.setPartExact(in1.getPart(30, 2), 0, 2);
      sub0 = in1High.get(1);
    } else {
      sub0 = 0;
    }
    if (i0Signed) {
      in0High.setPartExact(in0.getPart(30, 2), 0, 2);
      sub1 = in0High.get(1);
    } else {
      sub1 = 0;
    }
    for (int muli = 0; muli < 5; muli++) {
      Value tot = curCarry;
      for (int i0Off = 0; i0Off <= muli; i0Off++) {
        int i1Off = muli - i0Off;
        if (i0Off > 2 || i1Off > 2) {
          continue;
        }
        int i0Len = (i0Off == 2 ? 8 : 12);
        int i1Len = (i1Off == 2 ? 8 : 12);
        tot = tot + in0.getPart(i0Off * 12, i0Len) * in1.getPart(i1Off * 12, i1Len);
      }
      if (muli == 2) {
        tot = tot + 0x2000 - (sub0 * in0.getPart(0, 4) + sub1 * in1.getPart(0, 4)) * (1 << 8);
      }
      if (muli == 3) {
        tot = tot + 0x1ffe - (sub0 * in0.getPart(4, 12) + sub1 * in1.getPart(4, 12));
      }
      if (muli == 4) {
        tot = tot + 0x1fffe - (sub0 * in0.getPart(16, 16) + sub1 * in1.getPart(16, 16));
      }
      risc0Log("  tot[%d] = %08x", {muli, tot});
      Value topCarry = mul[muli].setPart(tot, 0, 24);
      carry[muli].setPartExact(topCarry, 0, 2);
      if (muli != 4) {
        curCarry = mul[muli].getPart(12, 12) + (1 << 12) * topCarry;
      }
    }
  };
  // Since we are only doing multiply ops, we can ignore the high bits of the ID
#define OPC(...) /**/
#define OPM(id, mnem, opc, f3, f7, immFmt, i0Expr, i1Expr, i0Signed, i1Signed, resultHigh)         \
  BYZ_IF(decode.opID1.is((id)&7)) {                                                                \
    in0.set(i0Expr);                                                                               \
    in1.set(i1Expr);                                                                               \
    doMultiply(i0Signed, i1Signed);                                                                \
    if (resultHigh) {                                                                              \
      resultInfo.result.set(                                                                       \
          {mul[2].getPart(8, 4) + mul[3].getPart(0, 12) * (1 << 4), mul[4].getPart(0, 16)});       \
    } else {                                                                                       \
      resultInfo.result.set({mul[0].getPart(0, 12) + mul[1].getPart(0, 4) * (1 << 12),             \
                             mul[1].getPart(4, 8) + mul[2].getPart(0, 8) * (1 << 8)});             \
    }                                                                                              \
    risc0Log("  i0 = 0x%04x%04x", {in0.getPart(16, 16), in0.getPart(0, 16)});                      \
    risc0Log("  i1 = 0x%04x%04x", {in1.getPart(16, 16), in1.getPart(0, 16)});                      \
    risc0Log("  result = 0x%04x%04x", {resultInfo.result.high(), resultInfo.result.low()});        \
  }
#define OPD(...) /**/
#include "risc0/zkvm/circuit/riscv32im.inl"
#undef OPC
#undef OPM
#undef OPD

  resultInfo.setReg.set(1);
  resultInfo.doStore.set(0);
  resultInfo.pcRaw.set(final.pc + 4);
}

} // namespace risc0
