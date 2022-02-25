#include <stdlib.h>

#include "risc0/r0vm/cpp/device/align.h"
#include "risc0/r0vm/cpp/device/risc0.h"
#include "risc0/r0vm/platform/memory.h"

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
  heap = align(heap + size, sizeof(uint32_t));
  if (heap >= risc0::kMemHeapEnd) {
    std::__throw_bad_alloc();
  }
  return ret;
}

void free(void*) {
  // no-op
}

} // extern "C"
