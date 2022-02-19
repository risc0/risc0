#pragma once

#include <cstddef>
#include <cstdint>

namespace risc0 {

[[noreturn]] void fail(const char* msg);

#define REQUIRE(x)                                                                                 \
  if (!(x)) {                                                                                      \
    ::risc0::fail(#x);                                                                             \
  }

} // namespace risc0
