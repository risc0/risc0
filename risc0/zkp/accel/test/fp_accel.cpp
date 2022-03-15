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

#include "risc0/core/log.h"
#include "risc0/core/rng.h"
#include "risc0/zkp/accel/accel.h"

#include <gtest/gtest.h>

#include "test_accel.h"

namespace risc0 {

TEST(Accel, CheckReq) {
  auto a = AccelSlice<Fp>::allocate(10);
  auto b = AccelSlice<Fp>::allocate(20);
  ASSERT_THROW(eltwiseAddFpAccel(a, b, b), std::runtime_error);
}

TEST(Accel, AccelFp) {
  LOG(1, "Doing startup");
  accelStartup();
  size_t count = 20 * 1024 * 1024;
  accelBeginProfile();
  DO_BINARY_TEST(Fp, eltwiseAddFpAccel, a + b, count);
  DO_BINARY_TEST(Fp, eltwiseSubFpAccel, a - b, count);
  DO_BINARY_TEST(Fp, eltwiseMulFpAccel, a * b, count);
  DO_UNARY_TEST(Fp, eltwiseNegFpAccel, -a, count);
  DO_UNARY_TEST(Fp, eltwiseInvFpAccel, inv(a), count);
  accelEndProfile();
}

} // namespace risc0
