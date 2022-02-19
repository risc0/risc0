#pragma once

#include "risc0/zkp/circuit/constants.h"
#include "risc0/zkp/circuit/types.h"

namespace risc0 {

namespace DataCycleType {
enum {
  DECODE,
  COMPUTE_0,
  COMPUTE_1,
  COMPUTE_2,
  COMPUTE_3,
  MULTIPLY,
  DIVIDE,
  FINAL,
  SHA_SYNC,
  SHA_CONTROL,
  SHA_DATA,
  HALT,
  NUM_CYCLE_TYPES,
};
} // namespace DataCycleType

struct CodeRegs {
  Reg cycle;
  Buffer codeCycleType;
  Buffer shaCycleType;
  Reg p1;
  Reg p2;
  RegU32 data;
  RegU32 data2;

  CodeRegs(BufAlloc alloc)
      : cycle(alloc)
      , codeCycleType(alloc.allocGeneric(CodeCycleType::NUM_TYPES))
      , shaCycleType(alloc.allocGeneric(ShaCycleType::NUM_TYPES))
      , p1(alloc)
      , p2(alloc)
      , data(alloc)
      , data2(alloc) {}
};

} // namespace risc0
