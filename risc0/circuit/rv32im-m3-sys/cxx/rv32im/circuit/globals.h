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

#include "rv32im/witness/globals.h"
#include "rv32im/circuit/poseidon2.h"

template<typename C>
struct GlobalsBlock {
  CONSTANT static char NAME[] = "GlobalsBlock";

  RegDigest<C> rootIn;
  RegDigest<C> rootOut;
  Reg<C> p2Count;
  Reg<C> finalCycle;
  Reg<C> finalCycleCeilDiv;
  RegU8<C> checkRoundedGT;
  RegU8<C> checkRoundedLT;

  template<typename T>
  FDEV void applyInner(CTX) DEV {
    T::apply(ctx, rootIn);
    T::apply(ctx, rootOut);
    T::apply(ctx, p2Count);
    T::apply(ctx, finalCycle);
    T::apply(ctx, finalCycleCeilDiv);
    T::apply(ctx, checkRoundedGT);
    T::apply(ctx, checkRoundedLT);
  }

  FDEV void set(CTX, GlobalsWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}

  FDEV void verify(CTX) DEV;
  FDEV void addArguments(CTX) DEV;
};
