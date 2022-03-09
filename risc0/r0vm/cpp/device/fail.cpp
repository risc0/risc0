#include "risc0/r0vm/cpp/device/fail.h"

#include "risc0/r0vm/platform/io.h"

namespace risc0 {

[[noreturn]] void fail(const char* msg) {
  volatile FaultDescriptor desc{reinterpret_cast<uint32_t>(msg)};
  // A compliant host should fault when it receives this descriptor.
  *GPIO_Fault() = &desc;
  // As a fallback for uncompliant hosts, force an unaligned write, which causes a fault within the
  // Risc0 VM.
  asm("sw x0, 1(x0)");
  // Add a while(1) to apease the compiler which of course doesn't realize the above line faults
  while (1)
    ;
}

} // namespace risc0

extern "C" {

void abort() {
  risc0::fail("abort");
}

} // extern "C"
