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

#include <stdlib.h>

#include "risc0/core/align.h"
#include "risc0/zkvm/platform/memory.h"
#include "risc0/zkvm/sdk/cpp/guest/risc0.h"

extern "C" {

// We implement only a trivial bump allocator since memory is cheap, CPU is expensive, and
// processes are short running.
void* malloc(size_t size) {
  // Initialize heap to the value defined in Memory.h
  static uint32_t heap = risc0::kMemHeapStart;
  // Fail if alloc is too big
  if (size >= risc0::kMemHeapLen) {
    std::__throw_bad_alloc();
  }
  // For each call to malloc, get current head pointer as our return value
  void* ret = reinterpret_cast<void*>(heap);
  // Increment heap pointer by size and then word align
  heap = risc0::align(heap + size, sizeof(uint32_t));
  if (heap >= risc0::kMemHeapEnd) {
    std::__throw_bad_alloc();
  }
  return ret;
}

void free(void*) {
  // no-op
}

} // extern "C"
