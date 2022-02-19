#include "risc0/zkp/core/fp.h"
#include "risc0/core/rng.h"

#include <gtest/gtest.h>

namespace risc0 {

// Compare core operations against simple % P implementations
TEST(Fp, FpCompareNative) {
  PsuedoRng rng(2);
  for (size_t i = 0; i < 100000; i++) {
    Fp fa = Fp::random(rng);
    Fp fb = Fp::random(rng);
    uint64_t a = fa.asUInt32();
    uint64_t b = fb.asUInt32();
    EXPECT_EQ(fa + fb, Fp((a + b) % Fp::P));
    EXPECT_EQ(fa - fb, Fp((a + (Fp::P - b)) % Fp::P));
    EXPECT_EQ(fa * fb, Fp((a * b) % Fp::P));
  }
}

// Smoke tests for pow
TEST(Fp, FpTestPow) {
  EXPECT_EQ(pow(Fp(5), 0), 1);
  EXPECT_EQ(pow(Fp(5), 1), 5);
  EXPECT_EQ(pow(Fp(5), 2), 25);
  // Mathematica says PowerMod[5, 1000, 15*2^27 + 1] == 589699054
  EXPECT_EQ(pow(Fp(5), 1000), 589699054);
  EXPECT_EQ(pow(Fp(5), Fp::P - 2) * Fp(5), 1);
  EXPECT_EQ(pow(Fp(5), Fp::P - 1), 1);
}

// Smoke test for inv
TEST(Fp, FpTestInv) {
  EXPECT_EQ(inv(Fp(5)) * Fp(5), 1);
}

} // End namespace risc0
