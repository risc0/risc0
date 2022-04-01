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

#include "risc0/zkvm/circuit/accum_regs.h"

#include "risc0/zkvm/circuit/step_state.h"

namespace risc0 {

void AccumRegs::set(StepState& state) {
  // Only verify when code is active
  auto& codeType = state.code.codeCycleType;
  Value isActive = 0;
  for (size_t i = 0; i < CodeCycleType::NUM_TYPES; i++) {
    isActive = isActive + codeType[i];
  }
  BYZ_IF(isActive) {
    Value isInit = codeType[CodeCycleType::INIT];
    Value isFini = codeType[CodeCycleType::FINI];

    std::vector<Value> cmp1;
    std::vector<Value> cmp2;

    // Push the 'cycle' number onto both sides
    cmp1.push_back(state.code.cycle.get());
    cmp2.push_back(state.data.memCheckBuf[4]);
    // Push the main memory IO data onto both sides
    for (size_t i = 0; i < 4; i++) {
      cmp1.push_back(state.data.buf[DataRegs::kCycleRegs + i]);
      cmp2.push_back(state.data.memCheckBuf[i]);
    }

    // Now build Fp4 values via mixing the inputs
    auto computeTot = [&](std::vector<Value> in) {
      std::array<Value, 4> tot = {1, 0, 0, 0};
      for (size_t i = 0; i < in.size(); i++) {
        for (size_t j = 0; j < 4; j++) {
          tot[j] = tot[j] + in[i] * getGlobal(kAccumMixGlobalOffset + i * 4 + j);
        }
      }
      return tot;
    };
    std::array<Value, 4> tot1 = computeTot(cmp1);
    std::array<Value, 4> tot2 = computeTot(cmp2);

    // Get the previous values
    auto getPrev = [&](Buffer in) {
      std::array<Value, 4> out;
      for (size_t i = 0; i < 4; i++) {
        out[i] = isInit * 1 + (1 - isInit) * in[i];
      }
      return out;
    };
    std::array<Value, 4> prev1 = getPrev(prod1.back(1));
    std::array<Value, 4> prev2 = getPrev(prod2.back(1));
    // Do the actual Fp4 multiply + set
    auto mulFp4 = [&](Buffer out, std::array<Value, 4> a, std::array<Value, 4> b) {
      Fp nBeta = Fp::P - 11;
      out[0] = a[0] * b[0] + nBeta * (a[1] * b[3] + a[2] * b[2] + a[3] * b[1]);
      out[1] = a[0] * b[1] + a[1] * b[0] + nBeta * (a[2] * b[3] + a[3] * b[2]);
      out[2] = a[0] * b[2] + a[1] * b[1] + a[2] * b[0] + nBeta * (a[3] * b[3]);
      out[3] = a[0] * b[3] + a[1] * b[2] + a[2] * b[1] + a[3] * b[0];
    };
    mulFp4(prod1, prev1, tot1);
    mulFp4(prod2, prev2, tot2);

    // Compute the determinant of prod 1 (to be used in the isFini case)
    {
      std::array<Value, 4> a = {prod1[0], prod1[1], prod1[2], prod1[3]};
      Value b0 = a[0] * a[0] + 11 * (2 * a[1] * a[3] - a[2] * a[2]);
      Value b2 = 2 * a[0] * a[2] - a[1] * a[1] + 11 * (a[3] * a[3]);
      Value c = b0 * b0 + 11 * b2 * b2;
      det.set(c);
    }

    // Check that the products match and are invertable for FINI
    BYZ_IF(isFini) {
      BYZ_NONDET { invDet.set(inv(det.get())); }
      for (size_t i = 0; i < 4; i++) {
        equate(prod1[i], prod2[i]);
      }
      equate(invDet.get() * det.get(), 1);
    }
  } // End if (isAcive)
}

} // namespace risc0
