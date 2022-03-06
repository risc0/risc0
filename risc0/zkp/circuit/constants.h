#pragma once

#include "risc0/r0vm/platform/memory.h"
#include "risc0/zkp/core/devs.h"

namespace risc0 {

namespace CodeCycleType {
enum {
  NORMAL,
  FINAL,
  INIT,
  MEM_WRITE,
  RESET,
  FINI,
  NUM_TYPES,
};
} // namespace CodeCycleType

namespace ShaCycleType {
enum {
  CONTROL,
  LOAD,
  MIX,
  NUM_TYPES,
};
} // namespace ShaCycleType

CONSTSCALAR size_t kCodeSize = 16;
CONSTSCALAR size_t kDataSize = 160;
CONSTSCALAR size_t kAccumSize = 16;
CONSTSCALAR size_t kCheckSize = 16;

CONSTSCALAR size_t kOutputRegs = 9;
CONSTSCALAR size_t kMinCycles = 512;
CONSTSCALAR size_t kMaxCycles = 1024 * 1024;
CONSTSCALAR size_t kQueries = 50; // ~100 bits of conjectured security
CONSTSCALAR size_t kZkCycles = kQueries;

CONSTSCALAR size_t kRegistersGlobalOffset = 0;
CONSTSCALAR size_t kRegistersGlobalSize = kOutputRegs * 2;
CONSTSCALAR size_t kAccumMixGlobalOffset = kRegistersGlobalSize;
CONSTSCALAR size_t kAccumMixGlobalSize = 20;
CONSTSCALAR size_t kPolyMixGlobalOffset = kAccumMixGlobalOffset + kAccumMixGlobalSize;
CONSTSCALAR size_t kPolyMixGlobalSize = 4;
CONSTSCALAR size_t kMixMixGlobalOffset = kPolyMixGlobalOffset + kPolyMixGlobalSize;
CONSTSCALAR size_t kMixMixGlobalSize = 4;
CONSTSCALAR size_t kGlobalSize = kMixMixGlobalOffset + kMixMixGlobalSize;

CONSTSCALAR size_t kComboCount = 5;

CONSTSCALAR size_t kInvRate = 4;
CONSTSCALAR size_t kMaxDegree = kInvRate + 1;

CONSTSCALAR size_t kFriFold = 16;
CONSTSCALAR size_t kFriMinDegree = 256;

} // namespace risc0
