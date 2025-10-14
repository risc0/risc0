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

#include "verify/verify.h"

#include "rv32im/emu/blocks.h"
#include "verify/fri.h"
#include "verify/merkle.h"
#include "zkp/params.h"
#include "zkp/poly.h"
#include "zkp/rou.h"

namespace risc0 {

using namespace rv32im;

void verify(VerifyCircuitInfo& ci, ReadIop& iop, size_t po2) {
  size_t rows = 1 << po2;
  size_t domain = rows * kExpansionFactor;

  size_t totalTaps = 0;
  std::vector<Fp> globals;
  std::vector<FpExt> mix;
  std::vector<MerkleVerifier> merkles;
  Fp backOne = ROU_REV[po2];

  for (size_t i = 0; i < ci.groups.size(); i++) {
    size_t numTaps = ci.taps.getGroups()[i].getTaps().size();
    size_t numCols = ci.taps.getGroups()[i].getColumns().size();
    totalTaps += numTaps;
    for (size_t j = 0; j < ci.groups[i].mixCount; j++) {
      mix.push_back(iop.rngFpExt());
    }
    size_t prevGlobals = globals.size();
    size_t newGlobals = ci.groups[i].globalCount;
    globals.resize(prevGlobals + newGlobals);
    iop.read(globals.data() + prevGlobals, newGlobals);
    if (newGlobals) {
      Digest globalsDigest = poseidon2Hash(globals.data() + prevGlobals, newGlobals);
      iop.commit(globalsDigest);
    }
    merkles.emplace_back(iop, domain, numCols, kQueries);
    LOG(0, "Merkle root = " << merkles.back().getRoot());
  }

  FpExt evalCheckMix = iop.rngFpExt();
  LOG(0, "evalCheckMix = " << evalCheckMix);

  MerkleVerifier checkMerkle(iop, domain, kExtSize * kExpansionFactor, kQueries);
  totalTaps += kExtSize * kExpansionFactor;
  LOG(0, "Check root = " << checkMerkle.getRoot());

  FpExt z = iop.rngFpExt();
  LOG(0, "Selected z = " << z);

  std::vector<FpExt> coeffs(totalTaps);
  iop.read(coeffs.data(), coeffs.size());
  Digest coeffsDigest = poseidon2Hash(coeffs.data(), coeffs.size());
  LOG(0, "Coeffs digest = " << coeffsDigest);
  iop.commit(coeffsDigest);
  FpExt comboMix = iop.rngFpExt();
  LOG(0, "Combo mix = " << comboMix);

  // Convert coeffs into evaluations
  std::vector<FpExt> eval(totalTaps);
  Fp rou = ROU_REV[po2];
  size_t offset = 0;
  for (const Column& col : ci.taps.getColumns()) {
    std::vector<FpExt> colCoeffs;
    for (size_t i = 0; i < col.getTaps().size(); i++) {
      colCoeffs.push_back(coeffs[offset + i]);
    }
    for (size_t i = 0; i < col.getTaps().size(); i++) {
      eval[offset + i] = polyEval(colCoeffs, z * pow(rou, col.getTaps()[i].back));
    }
    offset += col.getTaps().size();
  }
  // Check coeffs can just copy across
  for (size_t i = offset; i < eval.size(); i++) {
    eval[i] = coeffs[i];
  }

  FpExt constraintPoly = ci.evalCheck(eval.data(), globals.data(), mix.data(), evalCheckMix, z);
  LOG(0, "constraintPoly = " << constraintPoly);
  const FpExt* checkData = eval.data() + offset;
  FpExt check;
  size_t remap[] = {0, 2, 1, 3};
  for (size_t i = 0; i < kExpansionFactor; i++) {
    size_t rmi = remap[i];
    check += checkData[rmi + 0] * pow(z, i) * FpExt(1, 0, 0, 0);
    check += checkData[rmi + 4] * pow(z, i) * FpExt(0, 1, 0, 0);
    check += checkData[rmi + 8] * pow(z, i) * FpExt(0, 0, 1, 0);
    check += checkData[rmi + 12] * pow(z, i) * FpExt(0, 0, 0, 1);
  }
  check *= pow(Fp(3) * z, rows) - FpExt(1);
  LOG(0, "check = " << check);
  if (constraintPoly != check) {
    throw std::runtime_error("Poly check failed");
  }

  // Compute comboU
  std::vector<FpExt> comboU(ci.taps.comboSizeTot());
  FpExt curMix(1);
  size_t curPos = 0;
  // Normal columns
  for (const Column& col : ci.taps.getColumns()) {
    for (size_t i = 0; i < col.getTaps().size(); i++) {
      comboU[ci.taps.getCombos()[col.comboId].offset + i] += curMix * coeffs[curPos + i];
    }
    curPos += col.getTaps().size();
    curMix *= comboMix;
  }
  // Check columns
  FpExt checkComboU;
  for (size_t i = 0; i < 16; i++) {
    checkComboU += curMix * coeffs[curPos + i];
    curMix *= comboMix;
  }

  FriVerifier fri(iop, rows);
  fri.run(iop, [&](ReadIop& iiop, size_t pos) {
    FpExt x = FpExt(pow(ROU_FWD[po2 + 2], pos));
    std::vector<FpExt> tot(ci.taps.getCombos().size());
    curMix = FpExt(1);
    for (size_t i = 0; i < merkles.size(); i++) {
      const Group& group = ci.taps.getGroups()[i];
      auto vec = merkles[i].query(iiop, pos);
      for (size_t j = 0; j < vec.size(); j++) {
        size_t comboId = group.getColumns()[j].comboId;
        tot[comboId] += curMix * vec[j];
        curMix *= comboMix;
      }
    }
    FpExt checkTot;
    auto checkVec = checkMerkle.query(iiop, pos);
    for (Fp val : checkVec) {
      checkTot += curMix * val;
      curMix *= comboMix;
    }
    FpExt allTotal;
    for (size_t i = 0; i < ci.taps.getCombos().size(); i++) {
      size_t offset = ci.taps.getCombos()[i].offset;
      size_t size = ci.taps.getCombos()[i].backs.size();
      std::vector<FpExt> comboCoeffs(comboU.begin() + offset, comboU.begin() + offset + size);
      FpExt num = tot[i] - polyEval(comboCoeffs, x);
      FpExt divisor(1);
      for (uint32_t back : ci.taps.getCombos()[i].backs) {
        divisor *= (x - z * pow(backOne, back));
      }
      allTotal += num * inv(divisor);
    }
    allTotal += (checkTot - checkComboU) * inv(x - pow(z, kExpansionFactor));
    return allTotal;
  });
};

} // namespace risc0
