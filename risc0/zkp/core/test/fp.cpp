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

#include "risc0/zkp/core/fp.h"
#include "risc0/core/rng.h"

#include <gtest/gtest.h>

namespace risc0 {

// Compare core operations against simple % P implementations
TEST(Fp, FpCompareNative) {
  PsuedoRng rng(2);
  for (size_t i = 0; i < 100000; i++) {
    Fp fa = Fp::random(rng);
    Fp fb = Fp::random(rng);
    uint64_t a = fa.asUInt32();
    uint64_t b = fb.asUInt32();
    EXPECT_EQ(fa + fb, Fp((a + b) % Fp::P));
    EXPECT_EQ(fa - fb, Fp((a + (Fp::P - b)) % Fp::P));
    EXPECT_EQ(fa * fb, Fp((a * b) % Fp::P));
  }
}

// Smoke tests for pow
TEST(Fp, FpTestPow) {
  EXPECT_EQ(pow(Fp(5), 0), 1);
  EXPECT_EQ(pow(Fp(5), 1), 5);
  EXPECT_EQ(pow(Fp(5), 2), 25);
  // Mathematica says PowerMod[5, 1000, 15*2^27 + 1] == 589699054
  EXPECT_EQ(pow(Fp(5), 1000), 589699054);
  EXPECT_EQ(pow(Fp(5), Fp::P - 2) * Fp(5), 1);
  EXPECT_EQ(pow(Fp(5), Fp::P - 1), 1);
}

// Smoke test for inv
TEST(Fp, FpTestInv) {
  EXPECT_EQ(inv(Fp(5)) * Fp(5), 1);
}

} // End namespace risc0
