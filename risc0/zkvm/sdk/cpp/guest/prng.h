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

/// @file prng.h
/// @brief Psuedo-random number generator

#pragma once

#include "risc0/zkvm/sdk/cpp/guest/key.h"
#include "risc0/zkvm/sdk/cpp/guest/sha.h"

namespace risc0 {

/// @brief Psuedo-random number generator seeded by a Key.
/// @headerfile "risc0/zkvm/sdk/cpp/guest/prng.h"
///
/// A mechanism similar to the sponge construction is used to avoid leaking the full mixer state in
/// the RNG output.
class PRNG {
public:
  /// Construct a PRNG seeded with the provided Key.
  PRNG(KeyPtr key);

  /// Generate a number in the range [0, MAX_U32).
  uint32_t generate();

  /// Generate a number in the range [0, n).
  ///
  /// @param n The upper bound for the range [0, n).
  uint32_t generate(uint32_t n);

private:
  DigestPtr rate;
  DigestPtr capacity;
  uint32_t used;
};

} // namespace risc0
