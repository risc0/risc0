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

#pragma once

#include "risc0/zkp/core/sha256_cpu.h"

namespace risc0 {

// The ShaRng basically provides a cryptographically strong PRNG and is used in the IOP protocol.
// Thus we need an initially empty entropy pool and a way to mix new data in, as well as a way to
// draw as many random bits as we require.  We basically use a construction similar to a sponge,
// with a capacity of 256 bits, a rate of 256 bits, and Sha256 as the mixing function.

class ShaRng {
public:
  // Makes an RNG with an initial 'default' entropy pool (thus it's not very random until you use
  // mix to mix somthing in!).
  ShaRng();
  // Mix the hash into the entropy pool
  void mix(ShaDigest data);
  // Generate a value from the entropy pool
  uint32_t generate();

private:
  void step();
  ShaDigest pool0;
  ShaDigest pool1;
  size_t poolUsed;
};

} // namespace risc0
