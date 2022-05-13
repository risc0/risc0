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

uint32_t num_iter;
Digest initial_digest;

extern "C" void risc0_main(Env* env) {
  num_iter = env->read<uint32_t>();

  DigestPtr cur = &initial_digest;

  while (num_iter > 0) {
    // Prevent loop from being optimized out
    asm volatile("" : : : "memory");

    --num_iter;
    cur = shaDigest(reinterpret_cast<const void*>(cur), sizeof(Digest));
  }
}
