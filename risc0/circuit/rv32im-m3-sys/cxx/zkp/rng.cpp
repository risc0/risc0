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

#include "zkp/rng.h"

namespace risc0 {

Rng::Rng() : poolUsed(0) {
  state.fill(0);
}

void Rng::mix(const Digest& digest) {
  // if switching from squeezing, do a mix
  if (poolUsed != 0) {
    p2impl::poseidonSponge(state);
    poolUsed = 0;
  }
  // Add in CELLS_OUT elements (also # of digest words)
  for (size_t i = 0; i < 8; i++) {
    state[i] += Fp::fromRaw(digest.words[i]);
  }
  // Mix
  p2impl::poseidonSponge(state);
}

Fp Rng::rngFp() {
  if (poolUsed == p2impl::CELLS_RATE) {
    p2impl::poseidonSponge(state);
    poolUsed = 0;
  }
  return state[poolUsed++];
}

FpExt Rng::rngFpExt() {
  Fp a = rngFp();
  Fp b = rngFp();
  Fp c = rngFp();
  Fp d = rngFp();
  return FpExt(a, b, c, d);
}

size_t Rng::rngBits(size_t bits) {
  if (bits < 1 || bits > 27) {
    throw std::runtime_error("Invalid # of bits");
  }
  uint32_t val = rngFp().asUInt32();
  for (size_t i = 0; i < 3; i++) {
    uint32_t newVal = rngFp().asUInt32();
    if (val == 0) {
      val = newVal;
    }
  }
  return ((1 << bits) - 1) & val;
}

} // namespace risc0

