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

#pragma once

#include "rv32im/witness/decode.h"
#include "rv32im/circuit/mem.h"
#include "rv32im/circuit/one_hot.h"
#include "rv32im/circuit/u32.h"

template<typename C>
struct FetchBlock {
  CONSTANT static char NAME[] = "FetchBlock";

  Reg<C> iCacheCycle;
  RegU32<C> pc;
  RegU32<C> nextPc;

  template<typename T>
  FDEV void applyInner(CTX) DEV {
    T::apply(ctx, iCacheCycle);
    T::apply(ctx, pc);
    T::apply(ctx, nextPc);
  }

  FDEV void set(CTX, FetchWitness witness) DEV;
  FDEV inline void finalize(CTX) DEV {}

  FDEV void verify(CTX) DEV {}
  FDEV void addArguments(CTX) DEV {}
};

template<typename C>
struct DecodeBlock {
  CONSTANT static char NAME[] = "DecodeBlock";

  ArgCountReg<C> count;
  FetchBlock<C> fetch;
  Reg<C> loadCycle;
  AddressDecompose<C> pcDecomp;
  MemReadBlock<C> load0;
  MemReadBlock<C> load1;
  AddressDecompose<C> low16Decomp;
  BitReg<C> isCompressed;
  AddU32<C> computeNext;
  BitReg<C> bits[32];
  Reg<C> opcode;
  OneHot<C, 7> idx1;
  OneHot<C, 7> idx2;
  RegU32<C> imm;
  Reg<C> options;

  // Return low 16 bits of what is read (may be full instruction is compressed)
  FDEV Val<C> low16() DEV {
    return cond<C>(pcDecomp.low1.get(), load0.data.high.get(), load0.data.low.get());
  }

  template<typename T>
  FDEV void applyInner(CTX) DEV {
    T::apply(ctx, count);
    T::apply(ctx, fetch);
    T::apply(ctx, loadCycle);
    T::apply(ctx, pcDecomp, fetch.pc.get());
    T::apply(ctx, load0, loadCycle.get());
    T::apply(ctx, load1, loadCycle.get());
    T::apply(ctx, low16Decomp, ValU32<C>{low16(), 0});
    T::apply(ctx, computeNext, fetch.pc.get(), ValU32<C>(Val<C>(4) - isCompressed.get() * 2, 0));
    T::apply(ctx, bits);
    T::apply(ctx, opcode);
    T::apply(ctx, idx1);
    T::apply(ctx, idx2);
    T::apply(ctx, imm);
    T::apply(ctx, options);
  }

  FDEV void set(CTX, DecodeWitness witness) DEV;
  FDEV inline void finalize(CTX) DEV {}

  FDEV void verify(CTX) DEV;
  FDEV void addArguments(CTX) DEV;

private:
  FDEV Val<C> recomposeRange(uint32_t start, uint32_t end) DEV;

  FDEV Val<C> getOpcode() DEV;
  FDEV Val<C> getRD() DEV;
  FDEV Val<C> getFunct3() DEV;
  FDEV Val<C> getRS1() DEV;
  FDEV Val<C> getRS2() DEV;
  FDEV Val<C> getFunct7Low() DEV;
  FDEV Val<C> getFunct7() DEV;

  // Immediate variant helpers
  FDEV Val<C> getImmSign() DEV;
  FDEV ValU32<C> getImmI() DEV;
  FDEV ValU32<C> getImmIL() DEV;
  FDEV ValU32<C> getImmS() DEV;
  FDEV ValU32<C> getImmB() DEV;
  FDEV ValU32<C> getImmJ() DEV;
  FDEV ValU32<C> getImmU() DEV;
};
