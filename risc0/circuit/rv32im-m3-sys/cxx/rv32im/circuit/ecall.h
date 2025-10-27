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

#include "rv32im/base/poseidon2.h"
#include "rv32im/circuit/decode.h"
#include "rv32im/witness/ecall.h"

template <typename C> struct EcallTerminateBlock {
  CONSTANT static char NAME[] = "EcallTerminate";

  Reg<C> cycle;
  FetchBlock<C> fetch;
  RegMemReadBlock<C> readA7;
  RegMemReadBlock<C> readA0;
  RegMemReadBlock<C> readA1;
  PhysMemReadBlock<C> readOutput[8];

  template <typename T> FDEV void applyInner(CTX) DEV {
    T::apply(ctx, cycle);
    T::apply(ctx, fetch, cycle.get());
    T::apply(ctx, readA7, cycle.get());
    T::apply(ctx, readA0, cycle.get());
    T::apply(ctx, readA1, cycle.get());
    T::apply(ctx, readOutput, cycle.get());
  }

  FDEV void set(CTX, EcallTerminateWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}
  FDEV void verify(CTX) DEV;
  FDEV void addArguments(CTX) DEV;
};

template <typename C> struct EcallReadBlock {
  CONSTANT static char NAME[] = "EcallRead";

  Reg<C> cycle;
  Reg<C> finalCycle;
  FetchBlock<C> fetch;
  RegMemReadBlock<C> readA7;
  RegMemReadBlock<C> readA1;
  RegMemReadBlock<C> readA2;
  RegMemWriteBlock<C> writeA0;
  AddressDecompose<C> decomp;
  RegU16<C> verifyRet;
  Reg<C> finalAddrWord;
  Reg<C> finalAddrBits;

  template <typename T> FDEV void applyInner(CTX) DEV {
    T::apply(ctx, cycle);
    T::apply(ctx, finalCycle);
    T::apply(ctx, fetch, cycle.get());
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

template <typename C> struct EcallWriteBlock {
  CONSTANT static char NAME[] = "EcallWrite";

  Reg<C> cycle;
  FetchBlock<C> fetch;
  RegMemReadBlock<C> readA7;
  RegMemReadBlock<C> readA2;
  RegMemWriteBlock<C> writeA0;
  RegU16<C> verifyRet;

  template <typename T> FDEV void applyInner(CTX) DEV {
    T::apply(ctx, cycle);
    T::apply(ctx, fetch, cycle.get());
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

template <typename C> struct P2StepBlock {
  CONSTANT static char NAME[] = "P2Step";

  Reg<C> cycle;
  BitReg<C> isElem;
  BitReg<C> isCheck;
  Reg<C> count;
  IsZero<C> countOne;
  Reg<C> inWordAddr;
  Reg<C> outWordAddr;
  PhysMemReadBlock<C> dataIn[CELLS_RATE];
  PhysMemWriteBlock<C> dataOut[CELLS_DIGEST];
  Reg<C> stateIn[CELLS_DIGEST];
  Reg<C> inValues[CELLS_RATE];
  Reg<C> stateOut[CELLS_DIGEST];

  template <typename T> FDEV void applyInner(CTX) DEV {
    T::apply(ctx, cycle);
    T::apply(ctx, isElem);
    T::apply(ctx, isCheck);
    T::apply(ctx, count);
    T::apply(ctx, countOne, count.get() - 1);
    T::apply(ctx, inWordAddr);
    T::apply(ctx, outWordAddr);
    T::apply(ctx, dataIn, cycle.get());
    T::apply(ctx, dataOut, cycle.get());
    T::apply(ctx, stateIn);
    T::apply(ctx, inValues);
    T::apply(ctx, stateOut);
  }

  FDEV void set(CTX, P2StepWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}
  FDEV void verify(CTX) DEV;
  FDEV void addArguments(CTX) DEV;
};

template <typename C> struct EcallP2Block {
  CONSTANT static char NAME[] = "EcallP2";

  Reg<C> cycle;
  FetchBlock<C> fetch;
  RegMemReadBlock<C> readA0;
  RegMemReadBlock<C> readA1;
  RegMemReadBlock<C> readA2;
  RegMemReadBlock<C> readA3;
  RegMemReadBlock<C> readA7;
  BitReg<C> isElem;
  BitReg<C> isCheck;
  AddressDecompose<C> decompState;
  AddressDecompose<C> decompIn;
  AddressDecompose<C> decompOut;
  IsZero<C> iszState;
  Reg<C> stateInWordAddr; 
  Reg<C> stateOutWordAddr; 
  Reg<C> inWordAddrFinal; 
  PhysMemReadBlock<C> stateIn[CELLS_DIGEST];
  PhysMemWriteBlock<C> stateOut[CELLS_DIGEST];

  template <typename T> FDEV void applyInner(CTX) DEV {
    T::apply(ctx, cycle);
    T::apply(ctx, fetch, cycle.get());
    T::apply(ctx, readA0, cycle.get());
    T::apply(ctx, readA1, cycle.get());
    T::apply(ctx, readA2, cycle.get());
    T::apply(ctx, readA3, cycle.get());
    T::apply(ctx, readA7, cycle.get());
    T::apply(ctx, decompState, readA0.data.get());
    T::apply(ctx, decompIn, readA1.data.get());
    T::apply(ctx, decompOut, readA2.data.get());
    T::apply(ctx, iszState, decompState.wordAddr(readA0.data.get()));
    T::apply(ctx, stateInWordAddr);
    T::apply(ctx, stateOutWordAddr);
    T::apply(ctx, inWordAddrFinal);
    T::apply(ctx, stateIn, cycle.get());
    T::apply(ctx, stateOut, cycle.get() + 1 + readA3.data.low.get());
  }

  FDEV void set(CTX, EcallP2Witness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}
  FDEV void verify(CTX) DEV;
  FDEV void addArguments(CTX) DEV;
};

template <typename C> struct EcallBigIntBlock {
  CONSTANT static char NAME[] = "EcallBigInt";

  Reg<C> cycle;
  FetchBlock<C> fetch;
  RegMemReadBlock<C> readA7;
  RegMemReadBlock<C> readT0;
  RegMemReadBlock<C> readT2;
  Reg<C> cycleCount;
  BitReg<C> mm;
  AddressDecompose<C> pcDecomp;
  AddressVerify<C> pcVerify;

  template <typename T> FDEV void applyInner(CTX) DEV {
    T::apply(ctx, cycle);
    T::apply(ctx, fetch, cycle.get());
    T::apply(ctx, readA7, cycle.get());
    T::apply(ctx, readT0, cycle.get());
    T::apply(ctx, readT2, cycle.get());
    T::apply(ctx, cycleCount);
    T::apply(ctx, pcDecomp, readT2.data.get());
    T::apply(ctx, pcVerify, readT2.data.get(), mm.get() * Val<C>(MODE_MACHINE));
  }

  FDEV void set(CTX, EcallBigIntWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}
  FDEV void verify(CTX) DEV;
  FDEV void addArguments(CTX) DEV;
};
