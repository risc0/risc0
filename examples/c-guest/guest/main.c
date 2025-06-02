// Copyright 2024 RISC Zero, Inc.
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

#include "out/platform/platform.h"
#include <assert.h>
#include <stdint.h>

union u32_cast {
  uint32_t value;
  uint8_t buffer[4];
};

int main() {
  init_allocator();
  // TODO introduce entropy into memory image (for zk)
  sha256_state* hasher = init_sha256();

  // Read two u32 values from the host, assuming LE byte order.
  union u32_cast a;
  union u32_cast b;
  assert(env_read(a.buffer, 4) == 4);
  assert(env_read(b.buffer, 4) == 4);

  a.value *= b.value;

  env_commit(hasher, a.buffer, sizeof(a.buffer));
  env_exit(hasher, 0);

  return 0;
}
