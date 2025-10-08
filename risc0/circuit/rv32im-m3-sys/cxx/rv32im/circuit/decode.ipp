// Copyright 2025 RISC Zero, Inc.
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

template <typename C> FDEV void FetchBlock<C>::set(CTX, FetchWitness witness) DEV {
  iCacheCycle.set(ctx, witness.iCacheCycle);
  pc.set(ctx, witness.pc);
  nextPc.set(ctx, witness.nextPc);
}

template <typename C> FDEV Val<C> DecodeBlock<C>::recomposeRange(uint32_t start, uint32_t end) DEV {
  Val<C> value(0);
  for (uint32_t i = start; i < end; i++) {
    uint32_t multiplier = 1 << (i - start);
    value += bits[i].get() * multiplier;
  }
  return value;
}

template <typename C> FDEV Val<C> DecodeBlock<C>::getOpcode() DEV {
  return recomposeRange(0, 7);
}

template <typename C> FDEV Val<C> DecodeBlock<C>::getRD() DEV {
  return recomposeRange(7, 12);
}

template <typename C> FDEV Val<C> DecodeBlock<C>::getFunct3() DEV {
  return recomposeRange(12, 15);
}

template <typename C> FDEV Val<C> DecodeBlock<C>::getRS1() DEV {
  return recomposeRange(15, 20);
}

template <typename C> FDEV Val<C> DecodeBlock<C>::getRS2() DEV {
  return recomposeRange(20, 25);
}

template <typename C> FDEV Val<C> DecodeBlock<C>::getFunct7Low() DEV {
  return recomposeRange(25, 31);
}

template <typename C> FDEV Val<C> DecodeBlock<C>::getFunct7() DEV {
  return recomposeRange(25, 32);
}

// Immediate variant helpers
template <typename C> FDEV Val<C> DecodeBlock<C>::getImmSign() DEV {
  return bits[31].get();
}

template <typename C> FDEV ValU32<C> DecodeBlock<C>::getImmI() DEV {
  Val<C> immSign = getImmSign();
  Val<C> funct7 = getFunct7();
  Val<C> rs2 = getRS2();
  return ValU32<C>(immSign * 0xf000 + funct7 * 32 + rs2, immSign * 0xffff);
}

template <typename C> FDEV ValU32<C> DecodeBlock<C>::getImmIL() DEV {
  return ValU32<C>(getRS2(), 0);
}

template <typename C> FDEV ValU32<C> DecodeBlock<C>::getImmS() DEV {
  Val<C> immSign = getImmSign();
  Val<C> funct7 = getFunct7();
  Val<C> rd = getRD();
  return ValU32<C>(immSign * 0xf000 + funct7 * 32 + rd, immSign * 0xffff);
}

template <typename C> FDEV ValU32<C> DecodeBlock<C>::getImmB() DEV {
  Val<C> immSign = getImmSign();
  Val<C> funct7Low = getFunct7Low();
  Val<C> rdHigh = recomposeRange(8, 12);
  return ValU32<C>(immSign * 0xf000 + bits[7].get() * 0x800 + funct7Low * 32 + rdHigh * 2,
                   immSign * 0xffff);
}

template <typename C> FDEV ValU32<C> DecodeBlock<C>::getImmJ() DEV {
  Val<C> immSign = getImmSign();
  Val<C> bits_1_10 = recomposeRange(21, 31);
  Val<C> bit_11 = bits[20].get();
  Val<C> bits_12_16 = recomposeRange(12, 16);
  Val<C> bits_17_19 = recomposeRange(16, 20);
  return ValU32<C>(bits_12_16 * 0x1000 + bit_11 * 0x800 + bits_1_10 * 0x2,
                   immSign * 0xfff0 + bits_17_19);
}

template <typename C> FDEV ValU32<C> DecodeBlock<C>::getImmU() DEV {
  Val<C> instHigh = recomposeRange(16, 32);
  return ValU32<C>(bits[15].get() * 0x8000 + getFunct3() * 0x1000, instHigh);
}

template <typename C> FDEV void DecodeBlock<C>::set(CTX, DecodeWitness witness) DEV {
  count.set(ctx, witness.count);
  fetch.set(ctx, witness.fetch);
  loadCycle.set(ctx, witness.loadCycle);
  uint32_t cycleDiff = witness.loadCycle - witness.fetch.iCacheCycle;
  ctx.tableAdd(256 + 65536 + cycleDiff * 2, 1);
  pcDecomp.set(ctx, witness.fetch.pc);
  load0.set(ctx, witness.load0, witness.loadCycle);
  load1.set(ctx, witness.load1, witness.loadCycle);
  uint32_t baseInst = witness.load0.value;
  uint32_t low16 = witness.fetch.pc % 4 == 2 ? baseInst >> 16 : baseInst & 0xffff;
  low16Decomp.set(ctx, low16);
  bool compressed = (low16 & 3) != 3;
  isCompressed.set(ctx, compressed);
  computeNext.set(ctx, witness.fetch.pc, compressed ? 2 : 4);
  uint32_t inst;
  if (compressed) {
    inst = witness.load1.value;
  } else {
    if (witness.fetch.pc % 4 == 2) {
      inst = witness.load0.value >> 16 | witness.load1.value << 16;
    } else {
      inst = witness.load0.value;
    }
  }
  for (unsigned i = 0; i < 32; i++) {
    bits[i].set(ctx, (inst >> i) & 1);
  }

  opcode.set(ctx, inst & 0x7f);
  uint32_t opcode = inst & 0x7f;
  uint32_t f7 = (inst >> 25) & 0x7f;
  uint32_t f3 = (inst >> 12) & 0x7;
  uint32_t topBit = inst >> 31;
  uint32_t rd = (inst >> 7) & 0x1f;
  uint32_t rs1 = (inst >> 15) & 0x1f;
  uint32_t rs2 = (inst >> 20) & 0x1f;
  uint32_t immR = 0;
  uint32_t immB = (topBit * 0xfffff000) | ((rd & 1) << 11) | ((f7 & 0x3f) << 5) | (rd & 0x1e);
  uint32_t immI = (topBit * 0xfffff000) | (f7 << 5) | rs2;
  uint32_t immIL = rs2;
  uint32_t immS = (topBit * 0xfffff000) | (f7 << 5) | rd;
  uint32_t immJ = (topBit * 0xfff00000) | (rs1 << 15) | (f3 << 12) | ((rs2 & 1) << 11) |
                  ((f7 & 0x3f) << 5) | (rs2 & 0x1e);
  uint32_t immU = inst & 0xfffff000;
  uint32_t idx = 48; // Will fail to verify if we don't find a match
#define XF3 f3
#define XF7 f7
#define ENTRY(name, gidx, gopcode, gimmType, gf3, gf7, ...)                                        \
  if (gopcode == opcode && gf3 == f3 && gf7 == f7) {                                               \
    idx = gidx;                                                                                    \
    imm.set(ctx, imm##gimmType);                                                                   \
    options.set(ctx, EncodeOptions(__VA_ARGS__).val);                                              \
  }
#include "rv32im/base/rv32im.inc"
#undef ENTRY
#undef XF7
#undef XF3
  idx1.set(ctx, idx / 7);
  idx2.set(ctx, idx % 7);
}

template <typename C> FDEV void DecodeBlock<C>::verify(CTX) DEV {
  Val<C> instWordAddr = pcDecomp.wordAddr(fetch.pc.get());
  // Always load from the decomposed word initially
  EQ(instWordAddr, load0.wordAddr.get());
  // Verify low 2 bits relate to isCompressed
  EQ(isCompressed.get(), Val<C>(1) - low16Decomp.low0.get() * low16Decomp.low1.get());
  // Compute address of second read + verify
  Val<C> load1Addr =
      cond<C>(isCompressed.get(), Val<C>(COMPRESSED_INST_LOOKUP_WORD) + low16(), instWordAddr + 1);
  EQ(load1Addr, load1.wordAddr.get());
  // Verify next instruction is right
  EQ(computeNext.low.get(), fetch.nextPc.low.get());
  EQ(computeNext.high.get(), fetch.nextPc.high.get());
  // Get actual instruction data
  Val<C> instLow = cond<C>(isCompressed.get(), load1.data.low.get(), low16());
  Val<C> instHigh =
      cond<C>(isCompressed.get(),
              load1.data.high.get(),
              cond<C>(pcDecomp.low1.get(), load1.data.low.get(), load0.data.high.get()));
  // Make sure the instruction matches the bits
  EQ(instLow, recomposeRange(0, 16));
  EQ(instHigh, recomposeRange(16, 32));

  // Make the various parts
  Val<C> f7 = getFunct7();
  Val<C> f3 = getFunct3();

  // Compute the multiple verisons of the immediate
  ValU32<C> immR(0, 0);
  ValU32<C> immI = getImmI();
  ValU32<C> immIL = getImmIL();
  ValU32<C> immS = getImmS();
  ValU32<C> immB = getImmB();
  ValU32<C> immJ = getImmJ();
  ValU32<C> immU = getImmU();

  // Zero the 'instruction specific' bits
  ValU32<C> reqImm;
  Val<C> reqOptions = 0;
  Val<C> reqOpcode = 0;

  // 'Add' into the above, modified by idx, also, verify f3 / f7 match
  Val<C> reqF3 = 0;
  Val<C> reqF7 = 0;
  Val<C> validCount = 0;
#define XF3 f3
#define XF7 f7
#define ENTRY(name, gidx, gopcode, gt, gf3, gf7, ...)                                              \
  {                                                                                                \
    Val<C> isValid = idx1.bits[gidx / 7].get() * idx2.bits[gidx % 7].get();                        \
    reqOpcode += isValid * gopcode;                                                                \
    reqF3 += isValid * gf3;                                                                        \
    reqF7 += isValid * gf7;                                                                        \
    reqImm.low += isValid * imm##gt.low;                                                           \
    reqImm.high += isValid * imm##gt.high;                                                         \
    reqOptions += isValid * EncodeOptions(__VA_ARGS__).val;                                        \
    validCount += isValid;                                                                         \
  }
#include "rv32im/base/rv32im.inc"
#undef ENTRY
#undef XF7
#undef XF3
  // Do final validation
  EQ(validCount, 1);
  EQ(reqF3, f3);
  EQ(reqF7, f7);
  EQ(reqOptions, options.get());
  EQ(reqOpcode, opcode.get());
  EQ(reqImm.low, imm.low.get());
  EQ(reqImm.high, imm.high.get());
}

template <typename C> FDEV void DecodeBlock<C>::addArguments(CTX) DEV {
  ctx.pull(LookupArgument<C>(2, (loadCycle.get() - fetch.iCacheCycle.get()) * 2));
  DecodeArgument<C> arg;
  arg.iCacheCycle = fetch.iCacheCycle.get();
  arg.pcLow = fetch.pc.low.get();
  arg.pcLow = fetch.pc.high.get();
  arg.newPcLow = fetch.nextPc.low.get();
  arg.newPcLow = fetch.nextPc.high.get();
  arg.rs1 = getRS1();
  arg.rs2 = getRS2();
  arg.rd = getRD();
  arg.immLow = imm.low.get();
  arg.immHigh = imm.high.get();
  arg.options = options.get();
  ctx.addArgument(count.get(), arg);
}
