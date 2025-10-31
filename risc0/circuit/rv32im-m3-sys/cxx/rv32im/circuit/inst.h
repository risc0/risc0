// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

#pragma once

#include "rv32im/circuit/decode.h"
#include "rv32im/circuit/is_zero.h"
#include "rv32im/witness/inst.h"

// A 'resume' instruction reads the PC and the machine mode
// and initiates normal executions, always occurs on cycle 1
template <typename C> struct InstResumeBlock {
  CONSTANT static char NAME[] = "InstResumeBlock";

  PhysMemReadBlock<C> readV2Compat;
  PhysMemReadBlock<C> readPc;
  PhysMemReadBlock<C> readMode;
  PhysMemWriteBlock<C> writeVersion;

  template <typename T> FDEV void applyInner(CTX) DEV {
    T::apply(ctx, "readV2Compat", readV2Compat, 1);
    T::apply(ctx, "readPc", readPc, 1);
    T::apply(ctx, "readMode", readMode, 1);
    T::apply(ctx, "writeVersion", writeVersion, 1);
  }

  FDEV void set(CTX, InstResumeWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}

  FDEV void verify(CTX) DEV;
  FDEV void addArguments(CTX) DEV;
};

// A 'suspend' instruction writes the PC and machine mode and
// terminates execution.
template <typename C> struct InstSuspendBlock {
  CONSTANT static char NAME[] = "InstSuspendBlock";

  Reg<C> cycle;
  Reg<C> iCacheCycle;
  PhysMemWriteBlock<C> writePc;
  PhysMemWriteBlock<C> writeMode;

  template <typename T> FDEV void applyInner(CTX) DEV {
    T::apply(ctx, "cycle", cycle);
    T::apply(ctx, "writePc", writePc, cycle.get());
    T::apply(ctx, "writeMode", writeMode, cycle.get());
  }

  FDEV void set(CTX, InstSuspendWitness) DEV;
  FDEV inline void finalize(CTX) DEV {}

  FDEV void verify(CTX) DEV;
  FDEV void addArguments(CTX) DEV;
};

// A helper to extract + verify a source register given a word address
template <typename C> struct SourceReg {
  CONSTANT static char NAME[] = "SourceReg";

  Reg<C> idx;

  template <typename T> FDEV void applyInner(CTX, Val<C> wordAddr, Val<C> mode) DEV {
    T::apply(ctx, "idx", idx);
  }

  FDEV void set(CTX, Val<C> wordAddr) DEV;
  FDEV inline void finalize(CTX) DEV {}

  FDEV void verify(CTX, Val<C> wordAddr, Val<C> mode) DEV;
  FDEV void addArguments(CTX, Val<C> wordAddr, Val<C> mode) DEV {}
};

// A helper to extract + verify the destination register given a word address
template <typename C> struct DestReg {
  CONSTANT static char NAME[] = "DestReg";

  Reg<C> idx;
  IsZero<C> isZero;

  template <typename T> FDEV void applyInner(CTX, Val<C> wordAddr, Val<C> mode) DEV {
    T::apply(ctx, "idx", idx);
    T::apply(ctx, "isZero", isZero, idx.get());
  }

  FDEV void set(CTX, Val<C> wordAddr) DEV;
  FDEV inline void finalize(CTX) DEV {}

  FDEV void verify(CTX, Val<C> wordAddr, Val<C> mode) DEV;
  FDEV void addArguments(CTX, Val<C> wordAddr, Val<C> mode) DEV {}
};

// Handle reading from both rs1 + rs2, and make sure we only make
// one real memory transaction if rs1 == rs2
template <typename C> struct DualReg {
  CONSTANT static char NAME[] = "DestReg";

  BitReg<C> sameReg;
  RegMemReadBlock<C> readRs1;
  RegMemReadBlock<C> readRs2;
  Reg<C> rs1Idx;
  Reg<C> rs2Idx;
  RegU32<C> rs2Data;

  template <typename T> FDEV void applyInner(CTX, Val<C> cycle, Val<C> mm) DEV {
    T::apply(ctx, "sameReg", sameReg);
    T::apply(ctx, "readRs1", readRs1, cycle);
    T::apply(ctx, "readRs2", readRs2, cycle);
    T::apply(ctx, "rs1Idx", rs1Idx);
    T::apply(ctx, "rs2Idx", rs2Idx);
  }

  FDEV ValU32<C> getRS1() DEV;
  FDEV ValU32<C> getRS2() DEV;

  FDEV void set(CTX, RegMemReadWitness rs1Wit, RegMemReadWitness rs2Wit, uint32_t cycle) DEV;
  FDEV inline void finalize(CTX) DEV {}

  FDEV void verify(CTX, Val<C> cycle, Val<C> mode) DEV;
  FDEV void addArguments(CTX, Val<C> cycle, Val<C> mode) DEV {}
};

// Handle 3 register style instructions
template <typename C> struct InstRegBlock {
  CONSTANT static char NAME[] = "InstRegBlock";

  Reg<C> cycle;
  FetchBlock<C> fetch;
  DualReg<C> dr;
  RegMemWriteBlock<C> writeRd;
  DestReg<C> rd;
  Reg<C> optOut;
  BitReg<C> outIdx;
  RegU32<C> out0;
  RegU32<C> out1;

  template <typename T> FDEV void applyInner(CTX) DEV {
    T::apply(ctx, "cycle", cycle);
    T::apply(ctx, "fetch", fetch, cycle.get());
    T::apply(ctx, "dr", dr, cycle.get(), fetch.isMM());
    T::apply(ctx, "writeRd", writeRd, cycle.get());
    T::apply(ctx, "rd", rd, writeRd.wordAddr.get(), fetch.isMM());
    T::apply(ctx, "optOut", optOut);
    T::apply(ctx, "outIdx", outIdx);
    T::apply(ctx, "out0", out0);
    T::apply(ctx, "out1", out1);
  }

  FDEV void set(CTX, InstRegWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}

  FDEV void verify(CTX) DEV;
  FDEV void addArguments(CTX) DEV;
};

template <typename C> struct InstImmBlock {
  CONSTANT static char NAME[] = "InstImmBlock";

  Reg<C> cycle;
  FetchBlock<C> fetch;
  RegMemReadBlock<C> readRs1;
  RegMemWriteBlock<C> writeRd;
  SourceReg<C> rs1;
  Reg<C> rs2;
  DestReg<C> rd;
  RegU32<C> imm;
  Reg<C> optOut;
  BitReg<C> outIdx;
  RegU32<C> out0;
  RegU32<C> out1;

  template <typename T> FDEV void applyInner(CTX) DEV {
    T::apply(ctx, "cycle", cycle);
    T::apply(ctx, "fetch", fetch, cycle.get());
    T::apply(ctx, "readRs1", readRs1, cycle.get());
    T::apply(ctx, "writeRd", writeRd, cycle.get());
    T::apply(ctx, "rs1", rs1, readRs1.wordAddr.get(), fetch.isMM());
    T::apply(ctx, "rs2", rs2);
    T::apply(ctx, "rd", rd, writeRd.wordAddr.get(), fetch.isMM());
    T::apply(ctx, "imm", imm);
    T::apply(ctx, "optOut", optOut);
    T::apply(ctx, "outIdx", outIdx);
    T::apply(ctx, "out0", out0);
    T::apply(ctx, "out1", out1);
  }

  FDEV void set(CTX, InstImmWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}

  FDEV void verify(CTX) DEV;
  FDEV void addArguments(CTX) DEV;
};

template <typename C> struct InstLoadBlock {
  CONSTANT static char NAME[] = "InstLoadBlock";

  Reg<C> cycle;
  OneHot<C, 5> opt;
  FetchBlock<C> fetch;
  RegMemReadBlock<C> readRs1;
  RegMemWriteBlock<C> writeRd;
  SourceReg<C> rs1;
  Reg<C> rs2;
  DestReg<C> rd;
  RegU32<C> imm;
  AddU32<C> computeAddr;
  AddressDecompose<C> readAddr;
  AddressVerify<C> checkAddr;
  VirtMemReadBlock<C> readMem;
  Reg<C> pickShort;
  RegU8<C> b0;
  RegU8<C> b1;
  Reg<C> pickByte;
  GetSign<C> signBit;

  template <typename T> FDEV void applyInner(CTX) DEV {
    T::apply(ctx, "cycle", cycle);
    T::apply(ctx, "opt", opt);
    T::apply(ctx, "fetch", fetch, cycle.get());
    T::apply(ctx, "readRs1", readRs1, cycle.get());
    T::apply(ctx, "writeRd", writeRd, cycle.get());
    T::apply(ctx, "rs1", rs1, readRs1.wordAddr.get(), fetch.isMM());
    T::apply(ctx, "rs2", rs2);
    T::apply(ctx, "rd", rd, writeRd.wordAddr.get(), fetch.isMM());
    T::apply(ctx, "imm", imm);
    T::apply(ctx, "computeAddr", computeAddr, readRs1.data.get(), imm.get());
    T::apply(ctx, "readAddr", readAddr, computeAddr.get());
    T::apply(ctx, "checkAddr", checkAddr, computeAddr.get(), fetch.isMM());
    T::apply(ctx, "readMem", readMem, cycle.get());
    T::apply(ctx, "pickShort", pickShort);
    T::apply(ctx, "b0", b0);
    T::apply(ctx, "b1", b1);
    T::apply(ctx, "pickByte", pickByte);
    T::apply(ctx, "signBit", signBit, getSignBitInput());
  }
  FDEV void set(CTX, InstLoadWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}
  FDEV Val<C> getSignBitInput() DEV;
  FDEV void verify(CTX) DEV;
  FDEV void addArguments(CTX) DEV;
};

template <typename C> struct InstStoreBlock {
  CONSTANT static char NAME[] = "InstStoreBlock";

  Reg<C> cycle;
  OneHot<C, 3> opt;
  FetchBlock<C> fetch;
  DualReg<C> dr;
  Reg<C> rd;
  RegU32<C> imm;
  AddU32<C> computeAddr;
  AddressDecompose<C> writeAddr;
  AddressVerify<C> checkAddr;
  VirtMemWriteBlock<C> writeMem;
  // Pick a short based on address
  Reg<C> pickShort;
  // Decompose
  RegU8<C> psB0;
  RegU8<C> psB1;
  // Pick the byte base on address
  Reg<C> pickByte;
  // Get the low bytes of RS2
  RegU8<C> lowB0;
  RegU8<C> lowB1;
  // Reconstruct short
  Reg<C> newShort;

  template <typename T> FDEV void applyInner(CTX) DEV {
    T::apply(ctx, "cycle", cycle);
    T::apply(ctx, "opt", opt);
    T::apply(ctx, "fetch", fetch, cycle.get());
    T::apply(ctx, "dr", dr, cycle.get(), fetch.isMM());
    T::apply(ctx, "rd", rd);
    T::apply(ctx, "imm", imm);
    T::apply(ctx, "computeAddr", computeAddr, dr.getRS1(), imm.get());
    T::apply(ctx, "writeAddr", writeAddr, computeAddr.get());
    T::apply(ctx, "checkAddr", checkAddr, computeAddr.get(), fetch.isMM());
    T::apply(ctx, "writeMem", writeMem, cycle.get());
    T::apply(ctx, "pickShort", pickShort);
    T::apply(ctx, "psB0", psB0);
    T::apply(ctx, "psB1", psB1);
    T::apply(ctx, "pickByte", pickByte);
    T::apply(ctx, "lowB0", lowB0);
    T::apply(ctx, "lowB1", lowB1);
    T::apply(ctx, "newShort", newShort);
  }
  FDEV void set(CTX, InstStoreWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}
  FDEV void verify(CTX) DEV;
  FDEV void addArguments(CTX) DEV;
};

template <typename C> struct InstBranchBlock {
  CONSTANT static char NAME[] = "InstBranchBlock";

  Reg<C> cycle;
  FetchBlock<C> fetch;
  DualReg<C> dr;
  Reg<C> rd;
  RegU32<C> imm;
  Reg<C> optOut;
  BitReg<C> brnz;
  BitReg<C> outIdx;
  IsZero<C> isOutZero;
  RegU32<C> out0;
  RegU32<C> out1;
  AddU32<C> sumPc;
  RegU32<C> newPc;

  template <typename T> FDEV void applyInner(CTX) DEV {
    T::apply(ctx, "cycle", cycle);
    T::apply(ctx, "fetch", fetch, cycle.get());
    T::apply(ctx, "dr", dr, cycle.get(), fetch.isMM());
    T::apply(ctx, "rd", rd);
    T::apply(ctx, "imm", imm);
    T::apply(ctx, "optOut", optOut);
    T::apply(ctx, "brnz", brnz);
    T::apply(ctx, "outIdx", outIdx);
    ValU32<C> out = cond<C>(outIdx.get(), out1.get(), out0.get());
    Val<C> outSum = out.low + out.high;
    T::apply(ctx, "isOutZero", isOutZero, outSum);
    T::apply(ctx, "out0", out0);
    T::apply(ctx, "out1", out1);
    T::apply(ctx, "sumPc", sumPc, fetch.pc.get(), imm.get());
    T::apply(ctx, "newPc", newPc);
  }

  FDEV void set(CTX, InstBranchWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}

  FDEV void verify(CTX) DEV;
  FDEV void addArguments(CTX) DEV;
};

template <typename C> struct InstJalBlock {
  CONSTANT static char NAME[] = "InstJalBlock";

  Reg<C> cycle;
  FetchBlock<C> fetch;
  Reg<C> rs1;
  Reg<C> rs2;
  RegMemWriteBlock<C> writeRd;
  DestReg<C> rd;
  RegU32<C> imm;
  AddU32<C> sumPc;

  template <typename T> FDEV void applyInner(CTX) DEV {
    T::apply(ctx, "cycle", cycle);
    T::apply(ctx, "fetch", fetch, cycle.get());
    T::apply(ctx, "writeRd", writeRd, cycle.get());
    T::apply(ctx, "rs1", rs1);
    T::apply(ctx, "rs2", rs2);
    T::apply(ctx, "rd", rd, writeRd.wordAddr.get(), fetch.isMM());
    T::apply(ctx, "imm", imm);
    T::apply(ctx, "sumPc", sumPc, fetch.pc.get(), imm.get());
  }

  FDEV void set(CTX, InstJalWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}

  FDEV void verify(CTX) DEV;
  FDEV void addArguments(CTX) DEV;
};

template <typename C> struct InstJalrBlock {
  CONSTANT static char NAME[] = "InstJalrBlock";

  Reg<C> cycle;
  FetchBlock<C> fetch;
  RegMemReadBlock<C> readRs1;
  SourceReg<C> rs1;
  Reg<C> rs2;
  RegMemWriteBlock<C> writeRd;
  DestReg<C> rd;
  RegU32<C> imm;
  AddU32<C> sumPc;

  template <typename T> FDEV void applyInner(CTX) DEV {
    T::apply(ctx, "cycle", cycle);
    T::apply(ctx, "fetch", fetch, cycle.get());
    T::apply(ctx, "readRs1", readRs1, cycle.get());
    T::apply(ctx, "rs1", rs1, readRs1.wordAddr.get(), fetch.isMM());
    T::apply(ctx, "rs2", rs2);
    T::apply(ctx, "writeRd", writeRd, cycle.get());
    T::apply(ctx, "rd", rd, writeRd.wordAddr.get(), fetch.isMM());
    T::apply(ctx, "imm", imm);
    T::apply(ctx, "sumPc", sumPc, readRs1.data.get(), imm.get());
  }

  FDEV void set(CTX, InstJalrWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}

  FDEV void verify(CTX) DEV;
  FDEV void addArguments(CTX) DEV;
};

template <typename C> struct InstLuiBlock {
  CONSTANT static char NAME[] = "InstLuiBlock";

  Reg<C> cycle;
  FetchBlock<C> fetch;
  Reg<C> rs1;
  Reg<C> rs2;
  RegMemWriteBlock<C> writeRd;
  DestReg<C> rd;

  template <typename T> FDEV void applyInner(CTX) DEV {
    T::apply(ctx, "cycle", cycle);
    T::apply(ctx, "fetch", fetch, cycle.get());
    T::apply(ctx, "rs1", rs1);
    T::apply(ctx, "rs2", rs2);
    T::apply(ctx, "writeRd", writeRd, cycle.get());
    T::apply(ctx, "rd", rd, writeRd.wordAddr.get(), fetch.isMM());
  }

  FDEV void set(CTX, InstLuiWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}

  FDEV void verify(CTX) DEV {}
  FDEV void addArguments(CTX) DEV;
};

template <typename C> struct InstAuipcBlock {
  CONSTANT static char NAME[] = "InstAuipcBlock";

  Reg<C> cycle;
  FetchBlock<C> fetch;
  Reg<C> rs1;
  Reg<C> rs2;
  RegMemWriteBlock<C> writeRd;
  DestReg<C> rd;
  RegU32<C> imm;
  AddU32<C> sumPc;

  template <typename T> FDEV void applyInner(CTX) DEV {
    T::apply(ctx, "cycle", cycle);
    T::apply(ctx, "fetch", fetch, cycle.get());
    T::apply(ctx, "rs1", rs1);
    T::apply(ctx, "rs2", rs2);
    T::apply(ctx, "writeRd", writeRd, cycle.get());
    T::apply(ctx, "rd", rd, writeRd.wordAddr.get(), fetch.isMM());
    T::apply(ctx, "imm", imm);
    T::apply(ctx, "sumPc", sumPc, fetch.pc.get(), imm.get());
  }

  FDEV void set(CTX, InstAuipcWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}

  FDEV void verify(CTX) DEV;
  FDEV void addArguments(CTX) DEV;
};

template <typename C> struct InstEcallBlock {
  CONSTANT static char NAME[] = "InstEcallBlock";

  Reg<C> cycle;
  FetchBlock<C> fetch;
  PhysMemWriteBlock<C> writeSavePc;
  PhysMemReadBlock<C> readDispatch;

  template <typename T> FDEV void applyInner(CTX) DEV {
    T::apply(ctx, "cycle", cycle);
    T::apply(ctx, "fetch", fetch, cycle.get());
    T::apply(ctx, "writeSavePc", writeSavePc, cycle.get());
    T::apply(ctx, "readDispatch", readDispatch, cycle.get());
  }

  FDEV void set(CTX, InstEcallWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}

  FDEV void verify(CTX) DEV;
  FDEV void addArguments(CTX) DEV;
};

template <typename C> struct InstMretBlock {
  CONSTANT static char NAME[] = "InstMretBlock";

  Reg<C> cycle;
  FetchBlock<C> fetch;
  PhysMemReadBlock<C> readPc;
  AddU32<C> sumPc;

  template <typename T> FDEV void applyInner(CTX) DEV {
    T::apply(ctx, "cycle", cycle);
    T::apply(ctx, "fetch", fetch, cycle.get());
    T::apply(ctx, "readPc", readPc, cycle.get());
    T::apply(ctx, "sumPc", sumPc, readPc.data.get(), ValU32<C>(4, 0));
  }

  FDEV void set(CTX, InstMretWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}

  FDEV void verify(CTX) DEV;
  FDEV void addArguments(CTX) DEV;
};
