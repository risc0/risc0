#include "risc0/r0vm/cpp/device/risc0.h"

namespace risc0 {

static Digest zero = {0, 0, 0, 0, 0, 0, 0, 0};

PRNG::PRNG(KeyPtr key) {
  SHA256 setup(key);
  setup.tweak(1);
  capacity = setup.finalize();
  rate = shaCombine(capacity, &zero);
  used = 0;
}

uint32_t PRNG::generate() {
  if (used == 8) {
    capacity = shaCombine(capacity, capacity);
    rate = shaCombine(capacity, &zero);
    used = 0;
  }
  return rate->words[used++];
}

uint32_t PRNG::generate(uint32_t n) {
  REQUIRE(n > 0);
  uint32_t t = (-n) % n;
  uint32_t x;
  do {
    x = generate();
  } while (x < t);
  return x % n;
}

} // namespace risc0
