// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

#include "prove/prove.h"

#include "core/log.h"
#include "zkp/params.h"
#include "zkp/poly.h"
#include "zkp/rou.h"

namespace risc0 {

std::vector<Tap> makeCheckTaps(size_t group, size_t comboId) {
  std::vector<Tap> taps;
  for (size_t i = 0; i < kExtSize * kExpansionFactor; i++) {
    taps.emplace_back(group, i, 0);
    taps.back().comboId = comboId;
  }
  return taps;
}

Prover::Prover(IHalPtr hal, const CircuitInfo& _circuitInfo, size_t po2)
  : hal(hal)
  , circuitInfo(_circuitInfo)
  , po2(po2)
  , rows(1 << po2)
  , domain(rows * kExpansionFactor)
  , checkSize(kExtSize * kExpansionFactor)
  , evalSize(circuitInfo.taps.getTaps().size() + checkSize)
  , checkComboId(circuitInfo.taps.getCombos().size())
  , totCombos(checkComboId + 1)
  , checkTaps(makeCheckTaps(circuitInfo.groups.size(), checkComboId))
  , checkRaw(hal->allocateMatrix<Fp>(domain, kExtSize))
  , check(hal,
      checkRaw.reshape(rows, kExtSize * kExpansionFactor),
      checkTaps,
      kExtSize * kExpansionFactor)
  , combos(hal->allocateMatrix<FpExt>(rows, totCombos))
  , evalCoeffs(hal->allocateArray<FpExt>(evalSize))
  , evalInfo(hal->allocateArray<EvalInfo>(evalSize))
  , divideInfo(hal->allocateArray<DivideInfo>(circuitInfo.taps.comboSizeTot() + 1))
  , friCoeffs(hal->allocateMatrix<Fp>(rows, kExtSize))
  , fri(hal, friCoeffs)
{
  LOG(0, "circuitInfo.groups.size() = " << circuitInfo.groups.size());
  groups.resize(circuitInfo.groups.size());
  for (size_t i = 0; i < circuitInfo.groups.size(); i++) {
    GroupState& gs = groups[i];
    const Group& gt = circuitInfo.taps.getGroups()[i];
    size_t cols = gt.getColumns().size();
    if (circuitInfo.groups[i].globalCount > 0) {
      gs.global = hal->allocateArray<Fp>(circuitInfo.groups[i].globalCount);
    }
    if (circuitInfo.groups[i].mixCount > 0) {
      gs.mix = hal->allocateArray<FpExt>(circuitInfo.groups[i].mixCount);
    }
    gs.table = hal->allocateMatrix<Fp>(rows, cols);
    auto coeffs = hal->allocateMatrix<Fp>(rows, cols);
    polys.emplace_back(hal, coeffs, gt.getTaps(), gt.getColumns().size());
    gs.expTable = polys[i].expanded;
  }
  PinnedArrayWO<EvalInfo> pEvalInfo(hal, evalInfo);
  size_t pos = 0;
  for (const Column& col : circuitInfo.taps.getColumns()) {
    for (size_t j = 0; j < col.getTaps().size(); j++) {
      pEvalInfo[pos].group = col.group;
      pEvalInfo[pos].column = col.column;
      pEvalInfo[pos].comboId = col.comboId;
      pEvalInfo[pos].coeffIndex = j;
      pos++;
    }
  }
  for (size_t i = 0; i < checkSize; i++) {
    pEvalInfo[pos].group = circuitInfo.groups.size();
    pEvalInfo[pos].column = i;
    pEvalInfo[pos].comboId = checkComboId;
    pEvalInfo[pos].coeffIndex = 0;
    pos++;
  }
}

void Prover::prove(WriteIop& iop) {
  Fp rou = ROU_REV[po2];
  for (size_t i = 0; i < circuitInfo.groups.size(); i++) {
    if (circuitInfo.groups[i].mixCount) {
      LOG(0, "Generate mix");
      PinnedArrayWO<FpExt> pMix(hal, groups[i].mix);
      for (size_t j = 0; j < pMix.size(); j++) {
        pMix[j] = iop.rngFpExt();
      }
    }
    LOG(0, "Witgen");
    hal->zero(groups[i].table);
    circuitInfo.groups[i].witgen(groups);
    hal->sync();
    if (circuitInfo.groups[i].globalCount) {
      LOG(0, "Write globals");
      PinnedArrayRO<Fp> pGlobals(hal, groups[i].global);
      iop.write(pGlobals.data(), pGlobals.size());
      Digest globalsDigest = poseidon2Hash(pGlobals.data(), pGlobals.size());
      iop.commit(globalsDigest);
    }
    LOG(0, "Copy");
    hal->copy<Fp>(polys[i].coeffs, groups[i].table);
    LOG(0, "Interpolate + Shift");
    hal->batchInterpolate(polys[i].coeffs);
    hal->batchShift(polys[i].coeffs);
    LOG(0, "Eval + commit");
    polys[i].commit(iop);
    LOG(0, "root = " << polys[i].merkle.getRoot());
  }
  FpExt evalCheckMix = iop.rngFpExt();
  hal->sync();
  LOG(0, "Doing eval check, mix = " << evalCheckMix);
  circuitInfo.evalCheck(checkRaw, groups, evalCheckMix);
  hal->sync();
  LOG(0, "Interopate in place");
  hal->batchInterpolate(checkRaw);
  // {
  //   PinnedMatrixRO<Fp> checkRawPinned(hal, checkRaw);
  //   for (size_t i = 0; i < checkRaw.rows(); i++) {
  //     if (checkRawPinned(i, 0) != 0) {
  //       LOG(0, "checkRaw coefficients: " << i << "; " << checkRawPinned(i, 0));
  //     }
  //   }
  // }
  LOG(0, "Eval + commit check group");
  check.commit(iop);
  LOG(0, "Check root = " << check.merkle.getRoot());
  FpExt z = iop.rngFpExt();
  // FpExt z = FpExt(3);
  LOG(0, "Selected z = " << z);
  std::vector<FpExt> eval(evalSize);
  size_t offset = 0;
  for (size_t i = 0; i < circuitInfo.groups.size(); i++) {
    LOG(0, "Compute eval, offset = " << offset);
    polys[i].evaluate(eval.data() + offset, z);
    offset += circuitInfo.taps.getGroups()[i].getTaps().size();
  }
  LOG(0, "Compute check eval, offset = " << offset);
  check.evaluate(eval.data() + offset, pow(z, kExpansionFactor));
  LOG(0, "Translate to coefficients");
  std::vector<FpExt> coeffs(evalSize);
  offset = 0;
  // Compute tap coeffs via interpolation
  for (const Column& col : circuitInfo.taps.getColumns()) {
    std::vector<FpExt> xs;
    std::vector<FpExt> fxs;
    for (size_t i = 0; i < col.getTaps().size(); i++) {
      xs.push_back(z * pow(rou, col.getTaps()[i].back));
      fxs.push_back(eval[offset + i]);
    }
    std::vector<FpExt> colCoeffs = polyInterpolate(xs, fxs);
    for (size_t i = 0; i < col.getTaps().size(); i++) {
      coeffs[offset + i] = colCoeffs[i];
    }
    offset += col.getTaps().size();
  }
  // Check coeffs can just copy across
  for (size_t i = offset; i < evalSize; i++) {
    coeffs[i] = eval[i];
  }
  LOG(0, "Commit to data");
  iop.write(coeffs.data(), coeffs.size());
  Digest coeffsDigest = poseidon2Hash(coeffs.data(), coeffs.size());
  LOG(0, "Coeffs digest = " << coeffsDigest);
  iop.commit(coeffsDigest);

  FpExt curMix(1);
  FpExt comboMix = iop.rngFpExt();
  LOG(0, "Combo mix = " << comboMix);
  LOG(0, "# combos = " << combos.cols());
  hal->zero(combos);
  for (auto& poly : polys) {
    LOG(0, "Mixing in polynomial");
    poly.mix(combos, curMix, comboMix);
  }
  LOG(0, "Mixing in check");
  check.mix(combos, curMix, comboMix);
  LOG(0, "Prepare combos (i.e. subtract coeffs)");
  evalCoeffs.copyFromCpu(hal, coeffs.data());
  hal->combosPrep(combos, evalCoeffs, evalInfo, comboMix);
  LOG(0, "Divide combos");
  {
    // Compute what to divide by
    PinnedArrayWO<DivideInfo> pDivideInfo(hal, divideInfo);
    size_t pos = 0;
    for (const Combo& combo : circuitInfo.taps.getCombos()) {
      for (size_t back : combo.backs) {
        // LOG(0, "Divide combo " << combo.comboId << " by (x - " << pow(rou, back) * z << ")");
        pDivideInfo[pos].comboId = combo.comboId;
        pDivideInfo[pos].z = pow(rou, back) * z;
        pos++;
      }
    }
    pDivideInfo[divideInfo.size() - 1].comboId = checkComboId;
    pDivideInfo[divideInfo.size() - 1].z = pow(z, kExpansionFactor);
    // LOG(0, "Divide combo " << checkComboId << " by (x - " << pow(z, kExpansionFactor) << ")");
  }
  hal->combosDivide(combos, divideInfo);
  LOG(0, "Prepare final polynomial");
  hal->combosFinalize(friCoeffs, combos);
  hal->batchBitReverse(friCoeffs);
  LOG(0, "Do FRI");
  fri.compute(iop, [&](WriteIop& iiop, size_t pos) {
    for (auto& poly : polys) {
      poly.merkle.query(iiop, pos);
    }
    check.merkle.query(iiop, pos);
  });
}

}  // namespace risc0
