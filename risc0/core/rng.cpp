#include "risc0/core/rng.h"

#include <cstdio>
#include <ctime>
#include <stdexcept>

#include "risc0/core/log.h"

extern "C" uint32_t rust_rand_random();

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
  return rust_rand_random();
}

CryptoRng& CryptoRng::shared() {
  static CryptoRng r;
  return r;
}

} // End namespace risc0
