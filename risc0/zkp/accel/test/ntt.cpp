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
#include "risc0/zkp/accel/accel.h"

#include <gtest/gtest.h>

namespace risc0 {

template <typename AccelFunc, typename... Args>
void testNTT(const char* name,
             AccelFunc accelFunc,
             void (*cpuFunc)(Fp*, size_t, Args...),
             size_t size,
             size_t count,
             Args... args) {
  auto a = AccelSlice<Fp>::allocate(size * count);
  std::vector<Fp> b(size * count);
  LOG(1, "Testing " << name);
  {
    PseudoRng rng(2);
    LOG(1, "Randomizing");
    AccelReadWriteLock cpuA(a);
    for (size_t i = 0; i < size * count; i++) {
      b[i] = cpuA[i] = Fp::random(rng);
    }
    LOG(1, "Running accel");
  }
  accelFunc(a, count, args...);
  {
    // SYNC for timing
    AccelReadLock cpuA(a);
  }
  LOG(1, "Running CPU");
  for (size_t i = 0; i < count; i++) {
    cpuFunc(b.data() + i * size, size, args...);
  }
  {
    AccelReadLock cpuA(a);
    LOG(1, "Verifying");
    for (size_t i = 0; i < size * count; i++) {
      if (cpuA[i] != b[i]) {
        LOG(1, "i = " << i);
      }
      ASSERT_EQ(cpuA[i], b[i]);
    }
  }
  LOG(1, "Done");
}

TEST(Accel, NTT) {
  LOG(1, "Doing startup");
  accelStartup();
  size_t size = 1 << 21;
  size_t count = 50;
  accelBeginProfile();
  testNTT("evaluateNTT(0)", batchEvaluateNTT, evaluateNTT, size, count, size_t(0));
  testNTT("evaluateNTT(2)", batchEvaluateNTT, evaluateNTT, size, count, size_t(2));
  testNTT("interpolateNTT", batchInterpolateNTT, interpolateNTT, size, count);
}

} // namespace risc0
