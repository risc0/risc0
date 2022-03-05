#include "risc0/core/rng.h"

#include "risc0/core/log.h"
#include <cstdio>
#include <ctime>
#include <stdexcept>

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

CryptoRng::CryptoRng() = default;

CryptoRng::~CryptoRng() = default;

uint32_t CryptoRng::generate() {
  return rng();
}

CryptoRng& CryptoRng::shared() {
  static CryptoRng r;
  return r;
}

} // End namespace risc0
