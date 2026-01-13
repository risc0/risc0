// Copyright 2026 RISC Zero, Inc.
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

#include "verify/fri.h"

#include "core/util.h"
#include "zkp/ntt.h"
#include "zkp/params.h"
#include "zkp/poly.h"
#include "zkp/rou.h"

namespace risc0 {

FriRoundVerifier::FriRoundVerifier(ReadIop& iop, size_t degreeIn)
    : degree(degreeIn / kFriFold)
    , merkle(iop, degree * kExpansionFactor, kFriFold * kExtSize, kQueries) {
  mix = iop.rngFpExt();
}

void FriRoundVerifier::query(ReadIop& iop, size_t& pos, FpExt& goal) {
  size_t domain = merkle.rows();
  size_t quot = pos / domain;
  size_t group = pos % domain;

  // Get the column data
  auto data = merkle.query(iop, group);
  // Reformat into ext fields
  std::vector<FpExt> dataExt(kFriFold);
  for (size_t i = 0; i < kFriFold; i++) {
    dataExt[i] = FpExt(data[0 * kFriFold + i],
                       data[1 * kFriFold + i],
                       data[2 * kFriFold + i],
                       data[3 * kFriFold + i]);
  }
  // Check the existing goal
  if (dataExt[quot] != goal) {
    throw std::runtime_error("Invalid fri state");
  }
  // Compute the new goal + pos
  Fp root = ROU_REV[log2Ceil(kFriFold * domain)];
  Fp invWk = pow(root, group);
  multiInterpolate(dataExt.data(), dataExt.size());
  multiBitReverse(dataExt.data(), dataExt.size());
  goal = polyEval(dataExt, mix * invWk);
  pos = group;
}

FriVerifier::FriVerifier(ReadIop& iop, size_t degree) : initDegree(degree) {
  while (degree > kFriMinDegree) {
    rounds.emplace_back(iop, degree);
    degree /= kFriFold;
  }
  finalDegree = degree;
  // Read the final coefficients + commit
  std::vector<Fp> coeffsFlat(finalDegree * kExtSize);
  iop.read(coeffsFlat.data(), coeffsFlat.size());
  Digest digest = poseidon2Hash(coeffsFlat.data(), coeffsFlat.size());
  iop.commit(digest);
  // Reformat into FpExt
  for (size_t i = 0; i < finalDegree; i++) {
    coeffs.push_back(FpExt(coeffsFlat[0 * finalDegree + i],
                           coeffsFlat[1 * finalDegree + i],
                           coeffsFlat[2 * finalDegree + i],
                           coeffsFlat[3 * finalDegree + i]));
  }
}

void FriVerifier::run(ReadIop& iop, VerifyPointFunction func) {
  size_t initDomain = initDegree * kExpansionFactor;
  size_t finalDomain = finalDegree * kExpansionFactor;
  Fp gen = ROU_FWD[log2Ceil(finalDomain)];
  // Do the queries
  for (size_t i = 0; i < kQueries; i++) {
    size_t pos = iop.rngBits(log2Ceil(initDomain));
    FpExt goal = func(iop, pos);
    for (size_t j = 0; j < rounds.size(); j++) {
      rounds[j].query(iop, pos, goal);
    }
    FpExt fx = polyEval(coeffs, pow(gen, pos));
    if (fx != goal) {
      throw std::runtime_error("Mismatch final goal in FRI query");
    }
  }
}

} // namespace risc0
