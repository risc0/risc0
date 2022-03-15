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

#include <string>

namespace risc0 {

std::string allKernelNames() {
  std::string out;
#define GPU_KERNEL(name, args, launch, impl) out += #name "\n";
#define PARALLEL_KERNEL(name, args, impl) out += #name "\n";
#include "risc0/zkp/accel/kernels/all.h"
  return out;
}

} // namespace risc0
