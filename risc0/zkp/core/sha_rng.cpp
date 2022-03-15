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

#include "risc0/zkp/core/sha_rng.h"

namespace risc0 {

ShaRng::ShaRng() : poolUsed(0) {
  // TODO: Make this values more fun, after all they are arbitrary
  pool0 = shaHash("Hello");
  pool1 = shaHash("World");
}

// Mix the hash into the entropy pool
void ShaRng::mix(ShaDigest data) {
  for (size_t i = 0; i < 8; i++) {
    pool0.words[i] ^= data.words[i];
  }
  step();
}

uint32_t ShaRng::generate() {
  if (poolUsed == 8) {
    step();
  }
  return pool0.words[poolUsed++];
}

void ShaRng::step() {
  pool0 = shaHashPair(pool0, pool1);
  pool1 = shaHashPair(pool0, pool1);
  poolUsed = 0;
}

} // namespace risc0
