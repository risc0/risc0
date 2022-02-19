#include "risc0/r0vm/cpp/device/risc0.h"

void* operator new(std::size_t count) {
  return malloc(count);
}

void* operator new[](std::size_t count) {
  return malloc(count);
}

void operator delete(void*, unsigned int) {}

void operator delete[](void*, unsigned int) {}

namespace std {

void __throw_length_error(char const* msg) {
  risc0::fail(msg);
}

void __throw_bad_alloc() {
  risc0::fail("bad_alloc");
}

} // namespace std
