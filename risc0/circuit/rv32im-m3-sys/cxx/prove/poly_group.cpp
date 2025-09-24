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

#include "prove/poly_group.h"

#include "core/util.h"
#include "zkp/rou.h"
#include "zkp/params.h"

namespace risc0 {

PolyGroup::PolyGroup(IHalPtr hal, HalMatrix<Fp> coeffs, PtrRange<Tap> taps, size_t numCols)
  : hal(hal)
  , coeffs(coeffs)
  , taps(taps)
  , numCols(numCols)
  , expanded(hal->allocateMatrix<Fp>(coeffs.rows() * kExpansionFactor, coeffs.cols()))
  , merkle(hal, expanded, kQueries)
  , out(hal->allocateArray<FpExt>(taps.size()))
  , cols(hal->allocateArray<uint32_t>(taps.size()))
  , xs(hal->allocateArray<FpExt>(taps.size()))
  , whichCombo(hal->allocateArray<uint32_t>(numCols))
{
  PinnedArrayWO<uint32_t> pCols(hal, cols);
  PinnedArrayWO<uint32_t> pWhichCombo(hal, whichCombo);
  for (size_t i = 0; i < taps.size(); i++) {
    pCols[i] = taps[i].column;
    pWhichCombo[taps[i].column] = taps[i].comboId;
  }
  size_t po2 = log2Ceil(coeffs.rows());
  if (coeffs.rows() != size_t(1) << po2) {
    throw std::runtime_error("Size of input in EvalAtProver must be po2");
  }
  rou = ROU_REV[po2];
}

void PolyGroup::commit(WriteIop& iop) {
  hal->batchExpandAndEvaluate(expanded, coeffs);
  merkle.compute(iop);
  hal->batchBitReverse(coeffs);
}

void PolyGroup::evaluate(FpExt* userOut, FpExt z) {
  {
    PinnedArrayWO<FpExt> pXs(hal, xs);
    for (size_t i = 0; i < taps.size(); i++) {
      pXs[i] = z * pow(rou, taps[i].back);
    }
  }
  hal->batchPolyEval(out, coeffs, cols, xs);
  PinnedArrayRO<FpExt> pOut(hal, out);
  for (size_t i = 0; i < taps.size(); i++) {
    userOut[i] = pOut[i];
  }
}

void PolyGroup::mix(HalMatrix<FpExt> combos, FpExt& curMix, FpExt comboMix) {
  hal->combosMix(combos, coeffs, whichCombo, curMix, comboMix);
  curMix *= pow(comboMix, numCols);
}

}  // namespace risc0
