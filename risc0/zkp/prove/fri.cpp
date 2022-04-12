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

#include "risc0/zkp/prove/fri.h"

#include <memory>

#include "risc0/core/log.h"
#include "risc0/core/util.h"
#include "risc0/zkp/core/constants.h"
#include "risc0/zkp/prove/merkle.h"

namespace risc0 {

namespace {

struct ProveRoundInfo {
  size_t size;
  size_t domain;
  AccelSlice<Fp> evaluated;
  AccelSlice<Fp> outCoeffs;
  std::unique_ptr<MerkleTreeProver> merkle;

  ProveRoundInfo(WriteIOP& iop, AccelConstSlice<Fp> coeffs)
      : size(coeffs.size() / 4) // Coeffs are really Fp4s, but we treat as FP to use NTT/Merkle
      , domain(size * kInvRate)
      , evaluated(AccelSlice<Fp>::allocate(domain * 4))
      , outCoeffs(AccelSlice<Fp>::allocate(size / kFriFold * 4)) {
    LOG(1, "Doing FRI folding");
    batchExpand(evaluated, coeffs, 4);
    batchEvaluateNTT(evaluated, 4, log2Ceil(kInvRate));
    merkle =
        std::make_unique<MerkleTreeProver>(evaluated, domain / kFriFold, kFriFold * 4, kQueries);
    merkle->commit(iop);
    Fp4 foldMix = Fp4::random(iop);
    friFoldAccel(outCoeffs, coeffs, AccelSlice<Fp4>::copy(&foldMix, 1));
  }

  void proveQuery(WriteIOP& iop, size_t* pos) const {
    // Compute which group we are in
    size_t group = *pos % (domain / kFriFold);
    // Generate the proof
    merkle->prove(iop, group);
    // Update pos
    *pos = group;
  }
};

} // namespace

void friProve(WriteIOP& iop, AccelConstSlice<Fp> coeffs, InnerProve inner) {
  size_t origDomain = coeffs.size() / 4 * kInvRate;
  std::vector<ProveRoundInfo> rounds;
  while (coeffs.size() / 4 > kFriMinDegree) {
    rounds.emplace_back(iop, coeffs);
    coeffs = rounds.back().outCoeffs;
  }
  // Put the final coefficients into natural order
  auto final = AccelSlice<Fp>::allocate(coeffs.size());
  eltwiseCopyFpAccel(final, coeffs);
  batchBitReverse(final, 4);
  // Dump final polynomial + commit
  {
    AccelReadLock<Fp> finalCpu(final);
    iop.write(finalCpu.data(), finalCpu.size());
    auto digest = shaHash(finalCpu.data(), finalCpu.size(), 1, false);
    iop.commit(digest);
  }
  // Do queries
  LOG(1, "Doing Queries");
  for (size_t q = 0; q < kQueries; q++) {
    // Get a 'random' index.
    uint32_t rng = iop.generate();
    size_t pos = rng % origDomain;
    // Do the 'inner' proof for this index
    inner(iop, pos);
    // Write the per-round proofs
    for (auto& round : rounds) {
      round.proveQuery(iop, &pos);
    }
  }
}

} // namespace risc0
