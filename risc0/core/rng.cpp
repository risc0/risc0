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

CryptoRng::CryptoRng() {
  rng_ = fopen("/dev/urandom", "rb");
  if (rng_ == nullptr) {
    throw std::runtime_error("Unable to open RNG device");
  }
}

CryptoRng::~CryptoRng() {
  if (rng_ != nullptr) {
    fclose(rng_);
  }
}

uint32_t CryptoRng::generate() {
  uint32_t val;
  size_t r = fread(&val, sizeof(uint32_t), 1, rng_);
  if (r != 1) {
    throw std::runtime_error("Unable to read from RNG device");
  }
  return val;
}

CryptoRng& CryptoRng::shared() {
  static CryptoRng r = CryptoRng();
  return r;
}

} // End namespace risc0
