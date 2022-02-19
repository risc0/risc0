#include "risc0/r0vm/cpp/device/risc0.h"

using namespace risc0;

extern "C" void risc0_main(Env* env) {
  uint32_t count = env->read<uint32_t>();
  for (size_t i = 0; i < count; i++) {
    uint32_t addr = env->read<uint32_t>();
    uint32_t value = env->read<uint32_t>();
    uint32_t* addrPtr = reinterpret_cast<uint32_t*>(addr);
    if (value) {
      *addrPtr = value;
    } else {
      value = *addrPtr;
      env->write(value);
    }
  }
}
