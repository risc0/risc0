// Copyright 2022 Risc0, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "risc0/zkvm/sdk/cpp/guest/fail.h"

#include "risc0/zkvm/platform/io.h"

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
