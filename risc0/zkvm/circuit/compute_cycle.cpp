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

#include "risc0/zkvm/circuit/compute_cycle.h"

#include "risc0/zkvm/circuit/step_state.h"

namespace risc0 {

// Do the compute cycle.  Turn off max function size since macro inclusion make it too big.
// NOLINTNEXTLINE(readability-function-size)
void ComputeCycle::set(StepState& state, int highID) {
  Value cycle = state.code.cycle.get();

  // Cache some commonly used values
  auto decode = state.getPrev(1).asDecode();
  auto final = state.getPrev(2).asFinal();

  // Setup values used by the instruction macros
  auto R1 = decode.rs1.get();
#define R2 decode.rs2.get()
  auto IM = decode.imm.get();
#define MM state.data.memIO.value.get()
  auto memoryStore = [&]() {
    // Load the low 16 with the low 16 of rs2, and also the bit of the memory IO we will
    // be overwriting (so we can mix the bytes if needed).
    return ValueU32({decode.rs2.low(),
                     (1 - x1.get(1)) * state.data.memIO.value.low() +
                         x1.get(1) * state.data.memIO.value.high()});
  };
  auto& X1 = x1;
  auto& X2 = x2;
  auto& X3 = x3;
  auto PC = final.pc.get();
  // Do a memory read
  auto GET = [&](bool signExt, int bits) {
    if (bits == 32) {
      equate(x1.getPart(0, 2), 0);
      return x2.get();
    }
    ValueU32 out;
    Value highBit = 0;
    if (bits == 8) {
      Value tot = 0;
      for (int i = 0; i < 4; i++) {
        tot = tot + x1Low.is(i) * x2.getPart(i * 8, 8);
        if (signExt) {
          highBit = highBit + x1Low.is(i) * x2.get(i * 8 + 7);
        }
      }
      out.low = 0xff00 * highBit + tot;
    } else {
      equate(x1.get(0), 0);
      out.low = (1 - x1.get(1)) * x2.getPart(0, 16) + x1.get(1) * x2.getPart(16, 16);
      if (signExt) {
        highBit = highBit + (1 - x1.get(1)) * x2.get(15) + x1.get(1) * x2.get(31);
      }
    }
    out.high = 0xffff * highBit;
    return out;
  };
  // Do a memory write
  auto PUT = [&](int bits) {
    if (bits == 32) {
      equate(x1.getPart(0, 2), 0);
      return R2;
    }
    ValueU32 out;
    Value halfUpdate;
    if (bits == 8) {
      Value lowByte = (1 - x1.get(0)) * x2.getPart(0, 8) + x1.get(0) * x2.getPart(16, 8);
      Value highByte = x1.get(0) * x2.getPart(0, 8) + (1 - x1.get(0)) * x2.getPart(24, 8);
      tmp.set(lowByte + 256 * highByte);
      halfUpdate = tmp.get();
    } else {
      equate(x1.get(0), 0);
      halfUpdate = x2.getPart(0, 16);
    }
    out.low = (1 - x1.get(1)) * halfUpdate + x1.get(1) * state.data.memIO.value.low();
    out.high = x1.get(1) * halfUpdate + (1 - x1.get(1)) * state.data.memIO.value.high();
    return out;
  };
  auto maybeBranch = [](ValueU32 pc, Value doBranch, ValueU32 imm) {
    return pc + doBranch * imm + (1 - doBranch) * ValueU32({4, 0});
  };
#define MS memoryStore()
#define EQ ValueU32({1 - nz.get(), 0})
#define LT ValueU32({lt.get(), 0})
#define LTU ValueU32({1 - x3CarryHigh.get(), 0})
#define BR_TRUE maybeBranch(PC, resultInfo.result.low(), IM)
#define BR_FALSE maybeBranch(PC, (1 - resultInfo.result.low()), IM)

  // We call this once *inside* the risc0-if in a purely nondet way to compute the values without a
  // high degree, and then once outside to verify.
  auto setStatusFlags = [&]() {
    nzLow.set(x3.getPart(0, 16));
    nzHigh.set(x3.getPart(16, 16));
    nz.set(1 - (1 - nzLow.get()) * (1 - nzHigh.get()));
    Value s1 = x1.get(31);
    Value s2 = x2.get(31);
    Value s3 = x3.get(31);
    overflow.set(s1 * (1 - s2) * (1 - s3) + (1 - s1) * s2 * s3);
    lt.set(overflow.get() + s3 - 2 * overflow.get() * s3);
  };
#define OPC(                                                                                       \
    id, mnem, opc, f3, f7, immFmt, x1Expr, doLoad, x2Expr, x3Expr, resExpr, sreg, dstore, pcExpr)  \
  if ((id) >> 3 == highID) {                                                                       \
    BYZ_IF(decode.opID1.is((id)&7)) {                                                              \
      x1.setCarry(x1Expr, x1CarryLow, x1CarryHigh);                                                \
      Value cycle = state.code.cycle.get();                                                        \
      if (doLoad) {                                                                                \
        state.data.memIO.doRead(cycle, x1.getPart(2, kMemBits));                                   \
        equate(x1.getPart(2 + kMemBits, 32 - kMemBits - 2), 0);                                    \
      } else {                                                                                     \
        state.data.memIO.doRead(cycle, 0);                                                         \
      }                                                                                            \
      x2.set(x2Expr);                                                                              \
      x1Low.set(x1.getPart(0, 2));                                                                 \
      x3.setCarry(x3Expr, x3CarryLow, x3CarryHigh);                                                \
      BYZ_NONDET { setStatusFlags(); }                                                             \
      resultInfo.result.set(resExpr);                                                              \
      resultInfo.setReg.set(sreg);                                                                 \
      resultInfo.doStore.set(dstore);                                                              \
      resultInfo.pcRaw.set(pcExpr);                                                                \
      risc0Log(                                                                                    \
          "C%u: pc: %04x%04x Compute: x1 = 0x%04x%04x, x2 = 0x%04x%04x, x3 = 0x%04x%04x, nz = "    \
          "%d, carry = %d, "                                                                       \
          "overflow = %d, lt = %d, result = 0x%04x%04x",                                           \
          {cycle,                                                                                  \
           PC.high,                                                                                \
           PC.low,                                                                                 \
           x1.getPart(16, 16),                                                                     \
           x1.getPart(0, 16),                                                                      \
           x2.getPart(16, 16),                                                                     \
           x2.getPart(0, 16),                                                                      \
           x3.getPart(16, 16),                                                                     \
           x3.getPart(0, 16),                                                                      \
           nz.get(),                                                                               \
           x3CarryHigh.get(),                                                                      \
           overflow.get(),                                                                         \
           lt.get(),                                                                               \
           resultInfo.result.high(),                                                               \
           resultInfo.result.low()});                                                              \
    }                                                                                              \
  }
#define OPM(...) /**/
#define OPD(...) /**/
#include "risc0/zkvm/circuit/riscv32im.inl"
#undef MS
#undef EQ
#undef LT
#undef LTU
#undef BR_TRUE
#undef BR_FALSE
#undef OPC
#undef OPM
#undef OPD
  setStatusFlags();
}

} // namespace risc0
