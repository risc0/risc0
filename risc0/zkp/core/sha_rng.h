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
