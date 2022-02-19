#include "risc0/core/log.h"
#include "risc0/core/rng.h"
#include "risc0/zkp/accel/accel.h"

#include <gtest/gtest.h>

namespace risc0 {

template <typename T, typename AccelFunc, typename CpuFunc>
void testAccelUnary(const char* name, AccelFunc accelFunc, CpuFunc cpuFunc, size_t count) {
  auto a = AccelSlice<T>::allocate(count);
  auto o = AccelSlice<T>::allocate(count);
  LOG(1, "Testing " << name);
  std::vector<T> goldenOut(count);
  {
    PsuedoRng rng(2);
    LOG(1, "Randomizing");
    AccelReadWriteLock cpuA(a);
    for (size_t i = 0; i < count; i++) {
      cpuA[i] = T::random(rng);
    }
    LOG(1, "Doing CPU calculation");
    for (size_t i = 0; i < count; i++) {
      goldenOut[i] = cpuFunc(cpuA[i]);
    }
    // Note we put the log start here to so transfer to GPU via lock destuction are counted.
    LOG(1, "Doing Accel calculation");
  }
  accelFunc(o, a, count);
  {
    AccelReadLock cpuO(o);
    LOG(1, "Verifying");
    for (size_t i = 0; i < count; i++) {
      ASSERT_EQ(cpuO[i], goldenOut[i]);
    }
  }
  LOG(1, "Done");
}

#define DO_UNARY_TEST(T, binOp, expr, count)                                                       \
  testAccelUnary<T>(                                                                               \
      #binOp, binOp, [](T a) { return (expr); }, count);

template <typename T, typename AccelFunc, typename CpuFunc>
void testAccelBinary(const char* name, AccelFunc accelFunc, CpuFunc cpuFunc, size_t count) {
  auto a = AccelSlice<T>::allocate(count);
  auto b = AccelSlice<T>::allocate(count);
  auto o = AccelSlice<T>::allocate(count);
  LOG(1, "Testing " << name);
  std::vector<T> goldenOut(count);
  {
    PsuedoRng rng(2);
    LOG(1, "Randomizing");
    AccelReadWriteLock cpuA(a);
    AccelReadWriteLock cpuB(b);
    for (size_t i = 0; i < count; i++) {
      cpuA[i] = T::random(rng);
      cpuB[i] = T::random(rng);
    }
    LOG(1, "Doing CPU calculation");
    for (size_t i = 0; i < count; i++) {
      goldenOut[i] = cpuFunc(cpuA[i], cpuB[i]);
    }
    // Note we put the log start here to so transfer to GPU via lock destuction are counted.
    LOG(1, "Doing Accel calculation");
  }
  accelFunc(o, a, b, count);
  {
    AccelReadLock cpuO(o);
    LOG(1, "Verifying");
    for (size_t i = 0; i < count; i++) {
      ASSERT_EQ(cpuO[i], goldenOut[i]);
    }
  }
  LOG(1, "Done");
}

#define DO_BINARY_TEST(T, binOp, expr, count)                                                      \
  testAccelBinary<T>(                                                                              \
      #binOp, binOp, [](T a, T b) { return (expr); }, count);

} // namespace risc0
