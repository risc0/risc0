#include "risc0/r0vm/cpp/device/risc0.h"

#include "risc0/r0vm/platform/memory.h"

extern "C" {

void* memmove(void* dest, const void* src, size_t count) {
  char* destPtr = static_cast<char*>(dest);
  const char* srcPtr = static_cast<const char*>(src);
  size_t dstAddr = reinterpret_cast<size_t>(dest);
  size_t srcAddr = reinterpret_cast<size_t>(src);
  // If we can copy forward, use memcpy (which is in fact forward copying)
  if (dstAddr - srcAddr >= count) {
    return memcpy(dest, src, count);
  }
  // Otherwise, we use a naive bytewise backword copy as a fallback
  for (size_t i = count; i-- > 0;) {
    destPtr[i] = srcPtr[i];
  }
  return dest;
}

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
  heap = (heap + size + 3) & 0xfffffffc;
  if (heap >= risc0::kMemHeapEnd) {
    std::__throw_bad_alloc();
  }
  return ret;
}

void free(void*) {
  // Do nothing
}

} // extern "C"
