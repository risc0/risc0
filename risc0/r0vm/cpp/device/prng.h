/// @file prng.h
/// @brief Psuedo-random number generator

#pragma once

#include "risc0/r0vm/cpp/device/key.h"
#include "risc0/r0vm/cpp/device/sha.h"

namespace risc0 {

/// @brief Psuedo-random number generator seeded by a Key.
/// @headerfile "risc0/r0vm/cpp/device/prng.h"
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
