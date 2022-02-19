#include "risc0/r0vm/cpp/device/risc0.h"
#include "risc0/r0vm/platform/memory.h"

using namespace risc0;

extern "C" void risc0_main(Env* env) {
  volatile auto* womAddr = PTR_TO(uint32_t, WOM);
  *womAddr = 5;
  *womAddr = 7;
}
