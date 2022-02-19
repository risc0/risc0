#include "risc0/r0vm/cpp/device/risc0.h"

using namespace risc0;

extern "C" void risc0_main(Env* env) {
  uint32_t size = env->read<uint32_t>();
  const void* data = env->read(size);
  env->commit(shaDigest(data, size));
}
