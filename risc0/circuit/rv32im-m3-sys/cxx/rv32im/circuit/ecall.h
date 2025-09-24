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

#include "rv32im/witness/ecall.h"
#include "rv32im/circuit/decode.h"

template<typename C>
struct EcallTerminateBlock {
  CONSTANT static char NAME[] = "EcallTerminate";

  // TODO: pass A0/A1 on?  Clear suspend data?
  Reg<C> cycle;
  FetchBlock<C> fetch;
  MemReadBlock<C> readA7;

  template<typename T>
  FDEV void applyInner(CTX) DEV {
    T::apply(ctx, cycle);
    T::apply(ctx, fetch);
    T::apply(ctx, readA7, cycle.get());
  }

  FDEV void set(CTX, EcallTerminateWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}
  FDEV void verify(CTX) DEV;
  FDEV void addArguments(CTX) DEV;
};

template<typename C>
struct EcallReadBlock {
  CONSTANT static char NAME[] = "EcallRead";

  Reg<C> cycle;
  Reg<C> finalCycle;
  FetchBlock<C> fetch;
  MemReadBlock<C> readA7;
  MemReadBlock<C> readA1;
  MemReadBlock<C> readA2;
  MemWriteBlock<C> writeA0;
  AddressDecompose<C> decomp;
  RegU16<C> verifyRet;
  Reg<C> finalAddrWord;
  Reg<C> finalAddrBits;

  template<typename T>
  FDEV void applyInner(CTX) DEV {
    T::apply(ctx, cycle);
    T::apply(ctx, finalCycle);
    T::apply(ctx, fetch);
    T::apply(ctx, readA7, cycle.get());
    T::apply(ctx, readA1, cycle.get());
    T::apply(ctx, readA2, cycle.get());
    T::apply(ctx, writeA0, cycle.get());
    T::apply(ctx, decomp, readA1.data.get());
    T::apply(ctx, verifyRet);
    T::apply(ctx, finalAddrWord);
    T::apply(ctx, finalAddrBits);
  }

  FDEV void set(CTX, EcallReadWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}
  FDEV void verify(CTX) DEV;
  FDEV void addArguments(CTX) DEV;
};

template<typename C>
struct EcallWriteBlock {
  CONSTANT static char NAME[] = "EcallWrite";

  Reg<C> cycle;
  FetchBlock<C> fetch;
  MemReadBlock<C> readA7;
  MemReadBlock<C> readA2;
  MemWriteBlock<C> writeA0;
  RegU16<C> verifyRet;

  template<typename T>
  FDEV void applyInner(CTX) DEV {
    T::apply(ctx, cycle);
    T::apply(ctx, fetch);
    T::apply(ctx, readA7, cycle.get());
    T::apply(ctx, readA2, cycle.get());
    T::apply(ctx, writeA0, cycle.get());
    T::apply(ctx, verifyRet);
  }

  FDEV void set(CTX, EcallWriteWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}
  FDEV void verify(CTX) DEV;
  FDEV void addArguments(CTX) DEV;
};

template<typename C>
struct EcallBigIntBlock {
  CONSTANT static char NAME[] = "EcallBigInt";

  Reg<C> cycle;
  FetchBlock<C> fetch;
  MemReadBlock<C> readA7;
  MemReadBlock<C> readT0;
  MemReadBlock<C> readT2;
  Reg<C> cycleCount;
  BitReg<C> mm;
  AddressDecompose<C> pcDecomp;
  AddressVerify<C> pcVerify;

  template<typename T>
  FDEV void applyInner(CTX) DEV {
    T::apply(ctx, cycle);
    T::apply(ctx, fetch);
    T::apply(ctx, readA7, cycle.get());
    T::apply(ctx, readT0, cycle.get());
    T::apply(ctx, readT2, cycle.get());
    T::apply(ctx, cycleCount);
    T::apply(ctx, pcDecomp, readT2.data.get());
    T::apply(ctx, pcVerify, readT2.data.get(), mm.get());
  }

  FDEV void set(CTX, EcallBigIntWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}
  FDEV void verify(CTX) DEV;
  FDEV void addArguments(CTX) DEV;
};

