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

#include "risc0/zkvm/sdk/cpp/guest/risc0.h"

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
