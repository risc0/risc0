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

#include "risc0/zkp/prove/merkle.h"

#include "risc0/core/log.h"
#include "risc0/core/rng.h"

#include <gtest/gtest.h>

namespace risc0 {

void doTest(PseudoRng& rng, size_t rowSize, size_t colSize, size_t queries) {
  LOG(1, "Testing rowSize = " << rowSize << ", colSize = " << colSize << ", queries = " << queries);
  // Make some leaves
  auto leavesAccel = AccelSlice<Fp>::allocate(rowSize * colSize);
  {
    AccelWriteOnlyLock lock(leavesAccel);
    for (size_t i = 0; i < rowSize * colSize; i++) {
      lock[i] = static_cast<int>(i);
    }
  }
  // Make prover
  MerkleTreeProver prover(leavesAccel, rowSize, colSize, queries);
  // Make sure out of bounds accesses fail
  {
    WriteIOP proof;
    ASSERT_THROW(prover.prove(proof, rowSize), std::runtime_error);
  }
  // Make a proof of all the queries, make sure they return the row
  WriteIOP proof;
  prover.commit(proof);
  for (size_t i = 0; i < queries; i++) {
    size_t idx = proof.generate() % rowSize;
    LOG(2, "Prove: " << idx);
    auto col = prover.prove(proof, idx);
    for (size_t i = 0; i < colSize; i++) {
      ASSERT_EQ(col[i], idx + i * rowSize);
    }
  }
  auto proofRaw = proof.getProof();
  auto checkOnce = [&](size_t wrongQuery) {
    ReadIOP proof2(proofRaw.data(), proofRaw.size());
    MerkleTreeVerifier verifier(proof2, rowSize, colSize, queries);
    REQUIRE(verifier.getRoot() == prover.getRoot());
    bool err = false;
    for (size_t i = 0; i < queries; i++) {
      size_t idx = proof2.generate() % rowSize;
      LOG(2, "Query: " << idx);
      if (i == wrongQuery) {
        idx = (idx + 1) % rowSize;
        ASSERT_THROW(verifier.verify(proof2, idx), std::runtime_error);
        err = true;
        break;
      }
      auto col = verifier.verify(proof2, idx);
      for (size_t i = 0; i < colSize; i++) {
        ASSERT_EQ(col[i], idx + i * rowSize);
      }
    }
    if (!err) {
      proof2.verifyComplete();
    }
  };
  // Do normal verification, make sure it works by setting wrongQuery out of bounds
  checkOnce(queries + 1);
  // Pick a single query to get wrong, and verify it breaks things
  if (rowSize != 1) {
    size_t wrongQuery = rng.generate() % queries;
    checkOnce(wrongQuery);
  }
  // Verify each possible change to the proof breaks something
  for (size_t i = 0; i < proofRaw.size(); i++) {
    proofRaw[i] ^= 1;
    LOG(2, "Mucking with " << i << ", newVal = " << proofRaw[i]);
    ASSERT_THROW(checkOnce(queries + 1), std::runtime_error);
    proofRaw[i] ^= 1;
  }
}

TEST(Crypto, Merkle) {
  PseudoRng rng(2);
  doTest(rng, 1, 1, 1);
  doTest(rng, 4, 4, 2);
  auto logish = [&]() {
    size_t shift = rng.generate() % 6;
    return rng.generate() % (1 << shift) + 1;
  };
  auto po2 = [&]() { return (1 << (rng.generate() % 10)); };
  for (size_t i = 0; i < 100; i++) {
    // for (size_t i = 0; i < 10000; i++) {
    doTest(rng, po2(), logish(), logish());
  }
}

} // namespace risc0
