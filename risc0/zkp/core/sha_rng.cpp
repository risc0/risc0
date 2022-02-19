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
