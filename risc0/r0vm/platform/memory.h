#pragma once

#include "risc0/zkp/core/devs.h"

namespace risc0 {

#define MEM_REGION(name, start, len)                                                               \
  CONSTSCALAR size_t kMem##name##Start = start;                                                    \
  CONSTSCALAR size_t kMem##name##End = start + len;                                                \
  CONSTSCALAR size_t kMem##name##Len = len;

CONSTSCALAR size_t kMemBits = 20;
CONSTSCALAR size_t kMemSize = (1 << kMemBits) * 4;

CONSTSCALAR size_t k256KB = 0x00040000;
CONSTSCALAR size_t k512KB = 0x00080000;
CONSTSCALAR size_t k1MB = 0x00100000;

// Must match riscv.ld
// clang-format off
MEM_REGION(Stack,  0x00000000, k256KB)
MEM_REGION(Data,   0x00040000, k256KB)
MEM_REGION(Heap,   0x00080000, k1MB + k256KB)
MEM_REGION(GPIO,   0x001C0000, k256KB)
MEM_REGION(Prog,   0x00200000, k1MB)
MEM_REGION(SHA,    0x00300000, k256KB)
MEM_REGION(WOM,    0x00340000, k512KB + k256KB)
// clang-format on

#define PTR_TO(type, name) reinterpret_cast<type*>(kMem##name##Start);

struct ShaDescriptor {
  uint32_t typeAndCount;
  uint32_t idx;
  uint32_t source;
  uint32_t digest;
};

} // namespace risc0
