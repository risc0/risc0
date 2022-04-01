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

#include "risc0/zkvm/circuit/divide_cycle.h"

#include "risc0/zkvm/circuit/step_state.h"

namespace risc0 {

void DivideCycle::set(StepState& state) {
  Value cycle = state.code.cycle.get();
  risc0Log("C%u: Divide", {cycle});
  state.data.memIO.doRead(state.code.cycle.get());
  auto decode = state.getPrev(1).asDecode();
  auto final = state.getPrev(2).asFinal();
  ValueU32 R1 = decode.rs1.get();
  ValueU32 R2 = decode.rs2.get();
  ValueU32 V2 = decode.val2OH.asU32();
  auto doDivide = [&](ValueU32 numerExpr, ValueU32 denomExpr, int signType, bool resultRem) {
    // Check if the denominator is zero
    denomNonzero.set(denomExpr.low + denomExpr.high);
    // Implement the sign flips of the inputs, by cases
    if (signType == 0) {
      // Sign type 0, do nothing
      numer32.set(numerExpr);
      denom.set(denomExpr);
      negNumer.set(0);
      negDenom.set(0);
    } else if (signType == 1) {
      // Sign type 1, do full complicated negation
      BYZ_NONDET {
        negNumer.set((numerExpr.high & 0x8000) / 0x8000);
        negDenom.set((denomExpr.high & 0x8000) / 0x8000);
      }
      auto negNumerVal = negNumerImpl.set(numerExpr);
      auto negDenomVal = negDenomImpl.set(denomExpr);
      numer32.set(negNumer.get() * negNumerVal + (1 - negNumer.get()) * numerExpr);
      denom.set(negDenom.get() * negDenomVal + (1 - negDenom.get()) * denomExpr);
    } else if (signType == 2) {
      // Sign type 2, 'not' the numerator
      BYZ_NONDET { negNumer.set((numerExpr.high & 0x8000) / 0x8000); }
      negDenom.set(0);
      numer32.set(
          {negNumer.get() * (0xffff - numerExpr.low) + (1 - negNumer.get()) * numerExpr.low,
           negNumer.get() * (0xffff - numerExpr.high) + (1 - negNumer.get()) * numerExpr.high});
      denom.set(denomExpr);
    }
    auto denomVal = denom.get();
    // Now guess the quotient + remainder
    risc0Log("numer32 = %04x%04x, denom = %04x%04x, negNumer = %d, negDenom = %d",
             {numer32.high(),
              numer32.low(),
              denomVal.high,
              denomVal.low,
              negNumer.get(),
              negDenom.get()});
    BYZ_NONDET {
      auto [quotLow, quotHigh, remLow, remHigh] =
          divide(numer32.low(), numer32.high(), denomVal.low, denomVal.high);
      quot32.setLow(quotLow);
      quot32.setHigh(quotHigh);
      rem32.setLow(remLow);
      rem32.setHigh(remHigh);
    }
    risc0Log("quot32 = %04x%04x, rem32 = %04x%04x",
             {quot32.high(), quot32.low(), rem32.high(), rem32.low()});
    // Set them into actual 2-bit values
    quot.set(quot32.get());
    rem.set(rem32.get());
    // Verify the remainder is < the denominator (if not divide by zero)
    BYZ_IF(denomNonzero.isNonzero.get()) {
      carryDMR.set(
          denomMinusRem.setPart(0x10000 + denom.getPart(0, 16) - rem.getPart(0, 16) - 1, 0, 16));
      Value final = denomMinusRem.setPart(
          denom.getPart(16, 16) - rem.getPart(16, 16) - 1 + carryDMR.get(), 16, 16);
      equate(final, 0);
    }
    // Compute quot * denom + rem -> numer, do this 12 bits at a time
    numer0.setPartExact(quot.getPart(0, 12) * denom.getPart(0, 12) + rem.getPart(0, 12), 0, 24);
    numer1.setPartExact(quot.getPart(0, 12) * denom.getPart(12, 12) +
                            quot.getPart(12, 12) * denom.getPart(0, 12) + rem.getPart(12, 12) +
                            numer0.getPart(12, 12),
                        0,
                        20);
    numer2.setPartExact(
        quot.getPart(0, 12) * denom.getPart(24, 8) + quot.getPart(12, 12) * denom.getPart(12, 12) +
            quot.getPart(24, 8) * denom.getPart(0, 12) + rem.getPart(24, 8) + numer1.getPart(12, 8),
        0,
        8);
    risc0Log("numer0=0x%06x, numer1=0x%05x, numer2=0x%02x",
             {numer0.getPart(0, 24), numer1.getPart(0, 20), numer2.getPart(0, 8)});
    // Verify result, this even works for div-by-zero
    equate(numer0.getPart(0, 12) + 0x1000 * numer1.getPart(0, 4), numer32.low());
    equate(numer1.getPart(4, 8) + 0x100 * numer2.getPart(0, 8), numer32.high());
    // Switch on result, and pass on negation flag
    ValueU32 out;
    Value negOut;
    if (resultRem) {
      out = rem32.get();
      if (signType) {
        negOut = negNumer.get();
      } else {
        negOut = 0;
      }
    } else {
      out = quot32.get();
      if (signType) {
        negOut =
            // Normally, we xor to get negOut
            (negNumer.get() + negDenom.get() - 2 * negNumer.get() * negDenom.get())
            // But if things are zero, we want negOut to be zero.  Since denom was 0, the xor in
            // this case will be just the numerator, so we can subtract that.  All of this is to
            // lower the degree by one vs just multiplying by isNonzero
            - (negNumer.get() * (1 - denomNonzero.isNonzero.get()));
      } else {
        negOut = 0;
      }
    }
    // Set final resultInfo
    negResult.set(negOut);
    if (signType == 1) {
      auto negResultVal = negResultImpl.set(out);
      resultInfo.result.set(negResult.get() * negResultVal + (1 - negResult.get()) * out);
    } else if (signType == 2) {
      resultInfo.result.set(
          {negResult.get() * (0xffff - out.low) + (1 - negResult.get()) * out.low,
           negResult.get() * (0xffff - out.high) + (1 - negResult.get()) * out.high});
    } else {
      resultInfo.result.set(out);
    }
  };
  // Since we are only doing divide ops, we can ignore the high bits of the ID
#define OPC(...) /**/
#define OPM(...) /**/
#define OPD(id, mnem, opc, f3, f7, immFmt, numerExpr, denomExpr, signType, resultRem)              \
  BYZ_IF(decode.opID1.is((id)&7)) { doDivide(numerExpr, denomExpr, signType, resultRem); }
#include "risc0/zkvm/circuit/riscv32im.inl"
#undef OPC
#undef OPM
#undef OPD
  resultInfo.setReg.set(1);
  resultInfo.doStore.set(0);
  resultInfo.pcRaw.set(final.pc + 4);
}

} // namespace risc0
