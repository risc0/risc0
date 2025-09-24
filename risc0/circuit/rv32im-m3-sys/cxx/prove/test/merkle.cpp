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

#include <random>

#include "core/log.h"
#include "core/util.h"
#include "prove/merkle.h"
#include "verify/merkle.h"

using namespace risc0;

// A simple mock distribution that can be used to generate random integers
// consistently across different platforms and compilers. This should only be
// used for the sake of testing.
template <typename IntT>
struct PortableIntDistribution {
  IntT min;
  IntT max;

  PortableIntDistribution(IntT min, IntT max) : min(min), max(max) {}

  template <typename G>
  IntT operator()(G& g) const {
    return static_cast<IntT>(g() % (max + 1));
  }
};

struct MerkleTester {
  IHalPtr hal;
  size_t queries;
  std::mt19937 rng;
  PortableIntDistribution<uint32_t> fpDist;
  PortableIntDistribution<size_t> idxDist;
  HalMatrix<Fp> input;
  MerkleProver prover;
  WriteIop wiop;
  ReadIop* riop;
  MerkleVerifier* verifier;

  MerkleTester(IHalPtr hal, size_t rows, size_t cols, size_t queries)
    : hal(hal)
    , queries(queries)
    , rng(42)
    , fpDist(0, Fp::P - 1)
    , idxDist(0, rows)
    , input(hal->allocateMatrix<Fp>(rows, cols))
    , prover(hal, input, queries)
  {}

  void randomizeInput() {
    PinnedMatrixWO<Fp> pInput(hal, input);
    for (size_t i = 0; i < input.rows(); i++) {
      for (size_t j = 0; j < input.cols(); j++) {
        pInput(i, j) = fpDist(rng);
      }
    }
  }

  void verify(const Fp* data, size_t size) {
    ReadIop riop(data, size);
    MerkleVerifier verifier(riop, input.rows(), input.cols(), queries);
    LOG(1, "verifier root = " << verifier.getRoot());
    for (size_t i = 0; i < queries; i++) {
      size_t idx = riop.rngBits(log2Ceil(input.rows()));
      LOG(2, "Query @ " << idx);
      verifier.query(riop, idx);
    }
    riop.done();
  }

  void addQueries() {
    for (size_t i = 0; i < queries; i++) {
      size_t idx = wiop.rngBits(log2Ceil(input.rows()));
      LOG(2, "Query @ " << idx);
      prover.query(wiop, idx);
    }
  }

  void runNormalTest() {
    randomizeInput();
    prover.compute(wiop);
    addQueries();
    LOG(1, "prover root = " << prover.getRoot());
    LOG(1, "iop size = " << wiop.getTranscript().size());
    verify(wiop.getTranscript().data(), wiop.getTranscript().size());
  }
};

TEST(merkle, regression) {
  // Test an exact merkle tree transcript which is also tested in the Rust codebase.
  MerkleTester tester(getCpuHal(), 8, 1, 1);
  tester.runNormalTest();
  std::vector<Fp> transcript = tester.wiop.getTranscript();
  // for (auto x : transcript) {
  //   std::cout << x.asUInt32() << ", ";
  // }
  // std::cout << std::endl;
  std::vector<Fp> expected = {
    366955732, 1043300749, 74177033, 1788640914, 1454853479, 1696155387, 479780022,
    525523434, 1130624105, 1758925008, 876674128, 552514083, 1807923120, 1568665656,
    1926294261, 1263206558, 487460060, 1176879454, 599107438, 413211907, 177851327,
    519196378, 818209729, 1734225370, 399001480, 1701413422, 835961365, 922103091,
    1753516239, 1898152612, 1005614573, 268169686, 1431391262,
  };
  EXPECT_EQ(transcript, expected);
}

TEST(merkle, cpu) {
  MerkleTester tester(getCpuHal(), 4096, 103, 50);
  tester.runNormalTest();
}

TEST(merkle, gpu) {
  MerkleTester tester(getGpuHal(), 4096, 103, 50);
  tester.runNormalTest();
}

