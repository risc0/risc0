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

/// @file rng.h
/// Support for random numbers, including both PRNG and strong cryptographic random numbers.
/// RNGs are a concept which basically just requires a `generate` method.
/// This file is really CPU only, but the RNG concept is general.

#include <random>
#include <string>
#include <vector>

namespace risc0 {

/// A Psuedorandom number generator.
/// Uses `std::mt19937_64` under the hood.
/// Basically, only really used for tests.
/// For this reason, when default constructed, it pick and log a per-process seed.
class PseudoRng {
public:
  /// Seed with a process specific seed, log on first construction.
  PseudoRng();

  /// Construct a reproducable PRNG with a specific seed.
  explicit PseudoRng(uint64_t seed) : state_(seed) {}

  /// Generate a random 32-bit value uniformly selected over all values.
  uint32_t generate() { return static_cast<uint32_t>(state_()); }

private:
  std::mt19937_64 state_;
};

/// A cryptographic RNG using the system entropy pool.
class CryptoRng {
public:
  /// Generate a random 32-bit value uniformly selected over all values.
  uint32_t generate();

  /// Get the system-wide cryptographically secure RNG.
  static CryptoRng& shared();
};

} // namespace risc0
