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

#include "rv32im/base/base.h"
#include "rv32im/witness/lookups.h"

// A register that is constrained to be [0, 255]
template<typename C>
struct RegU8 {
  CONSTANT static char NAME[] = "RegU8";

  Reg<C> inner;

  template<typename T>
  FDEV void applyInner(CTX) DEV {
    T::apply(ctx, inner);
  }

  FDEV void set(CTX, Val<C> in) DEV;
  FDEV inline void finalize(CTX) DEV {}
  FDEV Val<C> get() DEV;
  FDEV void verify(CTX) DEV {}
  FDEV void addArguments(CTX) DEV;
};

// A register that is constrained to be [0, 65535]
template<typename C>
struct RegU16 {
  CONSTANT static char NAME[] = "RegU16";

  Reg<C> inner;

  template<typename T>
  FDEV void applyInner(CTX) DEV {
    T::apply(ctx, inner);
  }

  FDEV void set(CTX, Val<C> in) DEV;
  FDEV inline void finalize(CTX) DEV {}
  FDEV Val<C> get() DEV;
  FDEV void verify(CTX) DEV {}
  FDEV void addArguments(CTX) DEV;
};

// A thing that generates table entries
template<typename C>
struct MakeTableBlock {
  CONSTANT static char NAME[] = "MakeTableBlock";

  Reg<C> table;
  Reg<C> start;
  ArgCountReg<C> useCount[16];

  template<typename T>
  FDEV void applyInner(CTX) DEV {
    T::apply(ctx, table);
    T::apply(ctx, start);
    T::apply(ctx, useCount);
  }

  FDEV void set(CTX, MakeTableWitness wit) DEV;
  FDEV void finalize(CTX) DEV;
  FDEV void verify(CTX) DEV;
  FDEV void addArguments(CTX) DEV;
};

