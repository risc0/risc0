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

#include "prove/fri.h"

#include "core/util.h"

namespace risc0 {

FriProverRound::FriProverRound(IHalPtr hal, HalMatrix<Fp> coeffsIn)
    : hal(hal)
    , coeffsIn(coeffsIn)
    , evaluated(hal->allocateMatrix<Fp>(coeffsIn.rows() * kExpansionFactor, coeffsIn.cols()))
    , merkle(hal,
             evaluated.reshape(evaluated.rows() / kFriFold, evaluated.cols() * kFriFold),
             kQueries)
    , coeffsOut(hal->allocateMatrix<Fp>(coeffsIn.rows() / kFriFold, coeffsIn.cols())) {}

void FriProverRound::compute(WriteIop& iop) {
  hal->batchExpandAndEvaluate(evaluated, coeffsIn);
  merkle.compute(iop);
  FpExt mix = iop.rngFpExt();
  hal->friFold(coeffsOut, coeffsIn, mix);
}

void FriProverRound::query(WriteIop& iop, size_t& pos) {
  // Compute which group we are in
  size_t group = pos % merkle.rows();
  // Generate the proof
  merkle.query(iop, group);
  // Update pos
  pos = group;
}

FriProver::FriProver(IHalPtr hal, HalMatrix<Fp> coeffs)
    : hal(hal), degree(coeffs.rows()), domain(degree * kExpansionFactor) {
  while (coeffs.rows() > kFriMinDegree) {
    rounds.emplace_back(hal, coeffs);
    coeffs = rounds.back().coeffsOut;
  }
  last = coeffs;
  finalCoeffs = hal->allocateMatrix<Fp>(coeffs.rows(), coeffs.cols());
}

void FriProver::compute(WriteIop& iop, ProvePointFunction func) {
  for (size_t i = 0; i < rounds.size(); i++) {
    rounds[i].compute(iop);
  }
  // Copy + put final coefficients into normal order
  hal->copy<Fp>(finalCoeffs, last);
  hal->batchBitReverse(finalCoeffs);
  // Write coeffients + commit
  {
    PinnedMatrixRO<Fp> pFinal(hal, finalCoeffs);
    iop.write(pFinal.data(), pFinal.size());
    Digest digest = poseidon2Hash(pFinal.data(), pFinal.size());
    iop.commit(digest);
  }
  // Do the queries
  for (size_t i = 0; i < kQueries; i++) {
    size_t pos = iop.rngBits(log2Ceil(domain));
    func(iop, pos);
    for (size_t j = 0; j < rounds.size(); j++) {
      rounds[j].query(iop, pos);
    }
  }
}

} // namespace risc0
