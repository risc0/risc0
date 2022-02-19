#include "risc0/r0vm/cpp/device/risc0.h"

using namespace risc0;

extern "C" void risc0_main(Env* env) {
  uint8_t* src = static_cast<uint8_t*>(env->read(1024));
  uint8_t* dest = static_cast<uint8_t*>(env->read(1024));
  uint32_t srcOffset = env->read<uint32_t>();
  uint32_t destOffset = env->read<uint32_t>();
  uint32_t size = env->read<uint32_t>();
  if (srcOffset == 1024) {
    memset(dest + destOffset, 0xff, size);
  } else {
    memcpy(dest + destOffset, src + srcOffset, size);
  }
  env->write(dest, 1024);
}
