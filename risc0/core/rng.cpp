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

#include "risc0/core/rng.h"

#include <cstdio>
#include <ctime>
#include <stdexcept>

#include "risc0/core/log.h"

extern "C" uint32_t rust_rand_u32();

namespace risc0 {

PsuedoRng::PsuedoRng() {
  static uint64_t seed = CryptoRng::shared().generate();
  static bool logged = false;
  if (!logged) {
    LOG(1, "RNG seed = " << seed);
    logged = true;
  }
  state_ = std::mt19937_64(seed);
}

uint32_t CryptoRng::generate() {
  return rust_rand_u32();
}

CryptoRng& CryptoRng::shared() {
  static CryptoRng r;
  return r;
}

} // namespace risc0
