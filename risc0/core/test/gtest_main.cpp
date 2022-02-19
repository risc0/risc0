#include "risc0/core/log.h"

#include <cstdlib>
#include <gtest/gtest.h>

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  if (const char* level = std::getenv("RISC0_LOG")) {
    risc0::setLogLevel(std::atoi(level));
  }
  return RUN_ALL_TESTS();
}
