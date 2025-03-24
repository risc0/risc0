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

#include "platform.h"
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

union u32_cast {
  uint32_t value;
  uint8_t buffer[4];
};

// Simple bit mixing function for increased entropy
uint32_t mix_bits(uint32_t value) {
  value = value ^ (value << 13);
  value = value ^ (value >> 17);
  value = value ^ (value << 5);
  return value;
}

int main() {
  // Introducing entropy into memory image for zk proofs
  // Create and use a value that will affect the overall memory state
  // without changing the program logic
  volatile uint32_t entropy_seed = 0;
  uint8_t entropy_bytes[16];
  
  // Get additional random data from the host
  assert(env_read(entropy_bytes, sizeof(entropy_bytes)) == sizeof(entropy_bytes));
  
  // Mix entropy into memory
  for (size_t i = 0; i + 3 < sizeof(entropy_bytes); i += 4) {
    uint32_t entropy_chunk = 
      ((uint32_t)entropy_bytes[i]) | 
      ((uint32_t)entropy_bytes[i+1] << 8) | 
      ((uint32_t)entropy_bytes[i+2] << 16) | 
      ((uint32_t)entropy_bytes[i+3] << 24);
    
    entropy_seed ^= mix_bits(entropy_chunk);
  }
  
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
