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

#include "risc0/zkvm/sdk/cpp/guest/risc0.h"

namespace risc0 {

static Digest zero = {0, 0, 0, 0, 0, 0, 0, 0};

PRNG::PRNG(KeyPtr key) {
  SHA256 setup(key);
  setup.tweak(1);
  capacity = setup.finalize();
  rate = shaCombine(capacity, &zero);
  used = 0;
}

uint32_t PRNG::generate() {
  if (used == 8) {
    capacity = shaCombine(capacity, capacity);
    rate = shaCombine(capacity, &zero);
    used = 0;
  }
  return rate->words[used++];
}

uint32_t PRNG::generate(uint32_t n) {
  REQUIRE(n > 0);
  uint32_t t = (-n) % n;
  uint32_t x;
  do {
    x = generate();
  } while (x < t);
  return x % n;
}

} // namespace risc0
