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

#include <gtest/gtest.h>

#include <set>
#include <random>

#include "core/log.h"
#include "core/util.h"
#include "zkp/poly.h"
#include "zkp/rou.h"
#include "prove/fri.h"
#include "verify/fri.h"

using namespace risc0;

// TODO: Maybe move this somewhere common
HalMatrix<Fp> generateRandomMatrix(IHalPtr hal, size_t rows, size_t cols, size_t seed=42) {
  std::default_random_engine rng(seed);
  std::uniform_int_distribution<uint32_t> fpDist(0, Fp::P - 1);
  HalMatrix<Fp> out = hal->allocateMatrix<Fp>(rows, cols);
  PinnedMatrixWO<Fp> pOut(hal, out);
  for (size_t i = 0; i < out.rows(); i++) {
    for (size_t j = 0; j < out.cols(); j++) {
      pOut(i, j) = fpDist(rng);
    }
  }
  return out;
}

std::vector<FpExt> getCoeffs(IHalPtr hal, HalMatrix<Fp> coeffs) {
  std::vector<FpExt> coeffsOut;
  PinnedMatrixRO<Fp> pCoeffs(hal, coeffs);
  for (size_t i = 0; i < coeffs.rows(); i++) {
    coeffsOut.push_back(FpExt(
          pCoeffs(i, 0),
          pCoeffs(i, 1),
          pCoeffs(i, 2),
          pCoeffs(i, 3)
    ));
  }
  hal->batchBitReverse(coeffs);
  return coeffsOut;
}

void runFriTest(IHalPtr hal) {
  size_t kExampleSize = 8192;  // Gives us 2 folds
  auto polyCoeffsMat = generateRandomMatrix(hal, kExampleSize, kExtSize);
  auto polyCoeffs = getCoeffs(hal, polyCoeffsMat);
  FriProver prover(hal, polyCoeffsMat);
  WriteIop writeIop;
  Fp gen = ROU_FWD[log2Ceil(kExampleSize * kExpansionFactor)];
  prover.compute(writeIop, [&](WriteIop& iop, size_t pos) {
    FpExt val = polyEval(polyCoeffs, pow(gen, pos));
    iop.write(val.elems, kExtSize);
  });
  std::vector<Fp> transcript = writeIop.getTranscript();
  LOG(0, "Size of transcript = " << transcript.size());
  ReadIop readIop(transcript.data(), transcript.size());
  FriVerifier verifier(readIop, kExampleSize);
  verifier.run(readIop, [&](ReadIop& iop, size_t pos) {
    FpExt val;
    iop.read(val.elems, kExtSize);
    return val;
  });
  readIop.done();
  /* TEST ALL LOCATIONS FOR ERRORS
  std::set<std::string> whats;
  for (size_t i = 0; i < transcript.size(); i++) {
    std::vector<Fp> transcript2 = transcript;
    transcript2[i]++;
    ReadIop readIop(transcript2.data(), transcript2.size());
    bool good = true;
    try {
      FriVerifier verifier(readIop, kExampleSize);
      verifier.run(readIop, [&](ReadIop& iop, size_t pos) {
        FpExt val;
        iop.read(val.elems, kExtSize);
        return val;
      });
      readIop.done();
    } catch (const std::runtime_error& err) {
      whats.insert(err.what());
      good = false;
    }
    if (good) {
      throw std::runtime_error("SHOULD HAVE FAILED");
    }
  }
  for (const std::string& what : whats) {
    LOG(0, "Verified error: " << what);
  }
  */
}

TEST(fri, cpu) {
  runFriTest(getCpuHal());
}

TEST(fri, gpu) {
  runFriTest(getGpuHal());
}

