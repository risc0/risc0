#include "risc0/r0vm/cpp/device/risc0.h"

using namespace risc0;

extern "C" void risc0_main(Env* env) {
  fail("Failure");
}
