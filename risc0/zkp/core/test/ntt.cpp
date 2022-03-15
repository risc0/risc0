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

#include "risc0/zkp/core/ntt.h"
#include "risc0/core/log.h"
#include "risc0/core/rng.h"
#include "risc0/zkp/core/rou.h"

#include <gtest/gtest.h>

namespace risc0 {

// Compare the complex version to the naive version
TEST(NTT, CmpEvaluate) {
  size_t N = 6;
  size_t size = (1 << N);
  std::vector<Fp> in(size);
  // Randomly fill input
  PsuedoRng rng(2);
  for (size_t i = 0; i < size; i++) {
    in[i] = Fp::random(rng);
  }
  // Compute the hard way
  std::vector<Fp> goal(size);
  // Compute polynomial at each ROU power (starting at 0, i.e. x = 1)
  Fp x = 1;
  for (size_t i = 0; i < size; i++) {
    // Compute the polynomial
    Fp tot = 0;
    Fp xn = 1;
    for (size_t j = 0; j < size; j++) {
      tot += in[j] * xn;
      xn *= x;
    }
    goal[i] = tot;
    x *= kRouFwd[N];
  }
  // Now compute multiEvaluate in place
  bitReverse(in.data(), size);
  evaluateNTT(in.data(), size);
  // Compare
  ASSERT_EQ(goal, in);
}

// Make sure fwd + rev is identity
TEST(NTT, Roundtrip) {
  size_t N = 10;
  size_t size = (1 << N);
  std::vector<Fp> buf(size);
  // Randomly fill buffer
  PsuedoRng rng(2);
  for (size_t i = 0; i < size; i++) {
    buf[i] = Fp::random(rng);
  }
  // Copy it
  auto orig = buf;
  // Now go backwords
  interpolateNTT(buf.data(), size);
  // Make sure something changed
  ASSERT_NE(orig, buf);
  // Now go forward
  evaluateNTT(buf.data(), size);
  // It should be back to identical
  ASSERT_EQ(orig, buf);
}

TEST(NTT, Expand) {
  size_t N = 6;
  size_t L = 2;
  size_t sizeIn = (1 << (N - L));
  size_t sizeOut = (1 << N);
  std::vector<Fp> cmp(sizeIn);
  std::vector<Fp> buf(sizeOut);
  PsuedoRng rng(2);
  for (size_t i = 0; i < sizeIn; i++) {
    cmp[i] = Fp::random(rng);
  }
  // Do plain interpolate on cmp
  interpolateNTT(cmp.data(), sizeIn);
  // Expand to buf
  expand(buf.data(), cmp.data(), sizeIn, L);
  // Evaluate over the larger space
  evaluateNTT(buf.data(), sizeOut, L);
  // Order cmp nicely for the check
  bitReverse(cmp.data(), sizeIn);
  // Now verify by comparing with the slow way
  std::vector<Fp> goal(sizeOut);
  // Compute polynomial at each ROU power (starting at 0, i.e. x = 1)
  Fp x = 1;
  for (size_t i = 0; i < sizeOut; i++) {
    // Compute the polynomial
    Fp tot = 0;
    Fp xn = 1;
    for (size_t j = 0; j < sizeIn; j++) {
      tot += cmp[j] * xn;
      xn *= x;
    }
    goal[i] = tot;
    x *= kRouFwd[N];
  }
  ASSERT_EQ(goal, buf);
}

} // End namespace risc0
