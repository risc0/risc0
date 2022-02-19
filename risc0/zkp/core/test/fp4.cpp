#include "risc0/zkp/core/fp4.h"
#include "risc0/core/rng.h"

#include <gtest/gtest.h>

namespace risc0 {

TEST(Fp4, IsaField) {
  PsuedoRng rng(2);
  // Pick random sets of 3 elements of Fp4, and verify they meet the requirements of a field.
  for (size_t i = 0; i < 1000000; i++) {
    Fp4 a = Fp4::random(rng);
    Fp4 b = Fp4::random(rng);
    Fp4 c = Fp4::random(rng);
    // Addition + multiplication commute
    ASSERT_EQ(a + b, b + a);
    ASSERT_EQ(a * b, b * a);
    // Addition + multiplication are associative
    ASSERT_EQ(a + (b + c), (a + b) + c);
    ASSERT_EQ(a * (b * c), (a * b) * c);
    // Distributive propertly
    ASSERT_EQ(a * (b + c), a * b + a * c);
    // Inverses
    if (a != Fp4(0)) {
      ASSERT_EQ(inv(a) * a, Fp4(1));
    }
    ASSERT_EQ(Fp4(0) - a, -a);
    ASSERT_EQ(a + (-a), Fp4(0));
  }
}

} // namespace risc0
