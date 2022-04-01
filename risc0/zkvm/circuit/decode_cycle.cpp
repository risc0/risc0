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

#include "risc0/zkvm/circuit/decode_cycle.h"

#include "risc0/zkvm/circuit/step_state.h"

namespace risc0 {

// Helper for matching in nondet sections
static Value match(int pat, Value x) {
  if (pat == -1) {
    return 1;
  }
  return 1 - nonzero(pat - x);
}

// Do the decode cycle.  Turn off max function size since macro inclusion make it too big.
// NOLINTNEXTLINE(readability-function-size)
void DecodeCycle::set(StepState& state) {
  // Get previous instruction (either reset or final)
  DataRegs& prev = state.getPrev(1);
  FinalCycle prevFinal = prev.asFinal();

  // Make sure PC is an aligned access
  equate(prevFinal.pc.getPart(0, 2), 0);
  // Get PC to read from
  Value pc = prevFinal.pc.getPart(2, kMemBits);

  // Do the memory read of the instruction
  MemIORegs& memIO = state.data.memIO;
  Value cycle = state.code.cycle.get();
  memIO.doRead(cycle, pc);
  ValueU32 instVal = memIO.value.get();
  // Extract bits from the instruction
  inst.set(instVal);

  // Require low 2 bits of opcode to be 1 (normal compressed instruction0
  equate(inst.get(0), 1);
  equate(inst.get(1), 1);

  // Now we generate the various intermediate formats, which will later by selected during decode.
  // Basically this is an encoding of figure 2.4 from the RiscV spec, with the additional
  // complication that we need to split the low and high 16 bits.  We initially extract and shift
  // each of the common fields.  Then we put them together into various instruction types, and
  // finally pick the right one.

  // Extract + shift
  auto instField = [&](size_t low, size_t high) { return inst.getPart(low, high - low + 1); };
  Value imm3025 = instField(25, 30) * (1 << 5);
  Value imm2421 = instField(21, 24) * (1 << 1);
  Value imm1108 = instField(8, 11) * (1 << 1);
  Value imm1512 = instField(12, 15) * (1 << 12);
  Value imm1916 = instField(16, 19);
  Value imm3020 = instField(20, 30) * (1 << 4);
  Value imm07 = inst.get(07);
  Value imm20 = inst.get(20);
  Value imm31 = inst.get(31);

  // Combine by type
  ValueU32 immR = {0, 0};
  ValueU32 immI = {imm3025 + imm2421 + imm20 + imm31 * int(uint16_t(-(1 << 11))), imm31 * 0xffff};
  ValueU32 immS = {imm3025 + imm1108 + imm07 + imm31 * int(uint16_t(-(1 << 11))), imm31 * 0xffff};
  ValueU32 immB = {imm3025 + imm1108 + imm07 * (1 << 11) + imm31 * int(uint16_t(-(1 << 12))),
                   imm31 * 0xffff};
  ValueU32 immU = {imm1512, imm3020 + imm1916 + imm31 * 0x8000};
  ValueU32 immJ = {imm1512 + imm20 * (1 << 11) + imm3025 + imm2421,
                   imm1916 + imm31 * int(uint16_t(-(1 << 4)))};

  // Extract rs1 + rs2 and get 1-hot versions
  Value rs1Id = inst.getPart(15, 5);
  Value rs2Id = inst.getPart(20, 5);
  rs1Low.set(inst.getPart(15, 3));
  rs2Low.set(inst.getPart(20, 3));
  rs1High.set(inst.getPart(18, 2));
  rs2High.set(inst.getPart(23, 2));

  // Demux rs1 + rs2.  Missing case of 0 handles the zero register load
  ValueU32 rs1Val = {0, 0};
  ValueU32 rs2Val = {0, 0};
  for (int i = 1; i < 32; i++) {
    Value r1Sel = rs1Low.is(i & 0b111) * rs1High.is(i >> 3);
    Value r2Sel = rs2Low.is(i & 0b111) * rs2High.is(i >> 3);
    rs1Val = rs1Val + r1Sel * prevFinal.regs[i].get();
    rs2Val = rs2Val + r2Sel * prevFinal.regs[i].get();
  }
  rs1.set(rs1Val);
  rs2.set(rs2Val);

  // Extract the various fields useful to instruction decoding
  Value opcode = inst.getPart(2, 5);
  Value func3 = inst.getPart(12, 3);
  Value func7 = inst.getPart(25, 7);

  // Decode the instruction.  We do this in two parts: First we set the opID nondeterministicly, and
  // then we verify we got it right.  For the purposed of decoding, we treat OP<X> instructions the
  // same, so we redefine them all to ANYOP
#define OPC(...) ANYOP(COMPUTE_0, __VA_ARGS__)
#define OPM(...) ANYOP(MULTIPLY, __VA_ARGS__)
#define OPD(...) ANYOP(DIVIDE, __VA_ARGS__)

  // Pick out the op id
  BYZ_NONDET {
#define ANYOP(ct, id, mnem, oc, f3, f7, ...)                                                       \
  BYZ_IF(match(oc, opcode) * match(f3, func3) * match(f7, func7)) {                                \
    opID1.set(id & 7);                                                                             \
    opID2.set(id >> 3);                                                                            \
  }
#include "risc0/zkvm/circuit/riscv32im.inl"
    // Special case for halt, basically to avoid OPH
    ANYOP(SHA_SYNC, 63, HALT, 0b11100, 0, 0, R, 0)
#undef ANYOP
  }

  // Now verify we got it right + set the immediate value + next step
#define ANYOP(ct, id, mnem, oc, f3, f7, immFmt, ...)                                               \
  BYZ_IF(opID1.is(id & 7) * opID2.is(id >> 3)) {                                                   \
    equate(opcode, oc);                                                                            \
    if (f3 >= 0) {                                                                                 \
      equate(func3, f3);                                                                           \
    }                                                                                              \
    if (f7 >= 0) {                                                                                 \
      equate(func7, f7);                                                                           \
    }                                                                                              \
    BYZ_GROUP {                                                                                    \
      imm.set(imm##immFmt);                                                                        \
      Value val2Low16 = (#immFmt[0] == 'R') ? rs2.low() : imm.low();                               \
      val2Low.setPartExact(val2Low16, 0, 16);                                                      \
      val2Split.setPartExact(val2Low.getPart(4, 2), 0, 2);                                         \
      val2OH.set(val2Low.getPart(0, 4) + 16 * val2Split.get(0));                                   \
    }                                                                                              \
    nextCycleType.set(DataCycleType::ct + (id < 32 ? id >> 3 : 0));                                \
    risc0Log("C%u: pc: %08x Decode: " #mnem " r%u=0x%04x%04x, r%u=0x%04x%04x, imm=0x%04x%04x",     \
             {cycle,                                                                               \
              pc * 4,                                                                              \
              rs1Id,                                                                               \
              rs1.high(),                                                                          \
              rs1.low(),                                                                           \
              rs2Id,                                                                               \
              rs2.high(),                                                                          \
              rs2.low(),                                                                           \
              imm.high(),                                                                          \
              imm.low()});                                                                         \
  }
#include "risc0/zkvm/circuit/riscv32im.inl"
  ANYOP(SHA_SYNC, 63, HALT, 0b11100, 0, 0, R, 0)
#undef ANYOP

  // Done with decode
#undef OPC
#undef OPM
#undef OPD
}

} // namespace risc0
