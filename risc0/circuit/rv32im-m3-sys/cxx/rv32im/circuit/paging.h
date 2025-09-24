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

#include "rv32im/base/constants.h"
#include "rv32im/witness/paging.h"
#include "rv32im/circuit/is_zero.h"
#include "rv32im/circuit/poseidon2.h"
#include "rv32im/circuit/u32.h"

CONSTANT uint32_t NUM_PARTS = PAGE_SIZE_WORDS / PAGE_PART_SIZE;

template<typename C>
struct PageInNodeBlock {
  CONSTANT static char NAME[] = "PageInNodeBlock";

  Reg<C> index;
  RegDigest<C> node;
  RegDigest<C> left;
  RegDigest<C> right;

  template<typename T>
  FDEV void applyInner(CTX) DEV {
    T::apply(ctx, index);
    T::apply(ctx, node);
    T::apply(ctx, left);
    T::apply(ctx, right);
  }

  FDEV void set(CTX, PageInNodeWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}

  FDEV void verify(CTX) DEV {}
  FDEV void addArguments(CTX) DEV;
};

template<typename C>
struct PageInPartBlock {
  CONSTANT static char NAME[] = "PageInPartBlock";

  Reg<C> addr;
  Reg<C> partNum;
  RegDigest<C> in;
  RegDigest<C> out;
  RegU32<C> data[PAGE_PART_SIZE];
  IsZero<C> lastPart;

  template<typename T>
  FDEV void applyInner(CTX) DEV {
    T::apply(ctx, addr);
    T::apply(ctx, partNum);
    T::apply(ctx, in);
    T::apply(ctx, out);
    T::apply(ctx, data);
    T::apply(ctx, lastPart,  Val<C>(NUM_PARTS - 1) - partNum.get());
  }

  FDEV void set(CTX, PageInPartWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}

  FDEV void verify(CTX) DEV {}
  FDEV void addArguments(CTX) DEV;
};

template<typename C>
struct PageInPageBlock {
  CONSTANT static char NAME[] = "PageInPageBlock";

  Reg<C> addr;
  RegDigest<C> node;

  template<typename T>
  FDEV void applyInner(CTX) DEV {
    T::apply(ctx, addr);
    T::apply(ctx, node);
  }

  FDEV void set(CTX, PageInPageWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}

  FDEV void verify(CTX) DEV {}
  FDEV void addArguments(CTX) DEV;
};

template<typename C>
struct PageOutNodeBlock {
  CONSTANT static char NAME[] = "PageOutNodeBlock";

  Reg<C> index;
  RegDigest<C> node;
  RegDigest<C> left;
  RegDigest<C> right;

  template<typename T>
  FDEV void applyInner(CTX) DEV {
    T::apply(ctx, index);
    T::apply(ctx, node);
    T::apply(ctx, left);
    T::apply(ctx, right);
  }

  FDEV void set(CTX, PageOutNodeWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}

  FDEV void verify(CTX) DEV {}
  FDEV void addArguments(CTX) DEV;
};

template<typename C>
struct PageOutPartBlock {
  CONSTANT static char NAME[] = "PageOutPartBlock";

  Reg<C> addr;
  Reg<C> partNum;
  RegDigest<C> in;
  RegDigest<C> out;
  RegU32<C> data[PAGE_PART_SIZE];
  Reg<C> cycle[PAGE_PART_SIZE];
  IsZero<C> lastPart;

  template<typename T>
  FDEV void applyInner(CTX) DEV {
    T::apply(ctx, addr);
    T::apply(ctx, partNum);
    T::apply(ctx, in);
    T::apply(ctx, out);
    T::apply(ctx, data);
    T::apply(ctx, cycle);
    T::apply(ctx, lastPart,  Val<C>(NUM_PARTS - 1) - partNum.get());
  }

  FDEV void set(CTX, PageOutPartWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}

  FDEV void verify(CTX) DEV {}
  FDEV void addArguments(CTX) DEV;
};

template<typename C>
struct PageOutPageBlock {
  CONSTANT static char NAME[] = "PageOutPageBlock";

  Reg<C> addr;
  RegDigest<C> node;

  template<typename T>
  FDEV void applyInner(CTX) DEV {
    T::apply(ctx, addr);
    T::apply(ctx, node);
  }

  FDEV void set(CTX, PageOutPageWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}

  FDEV void verify(CTX) DEV {}
  FDEV void addArguments(CTX) DEV;
};

template<typename C>
struct PageUncleBlock {
  CONSTANT static char NAME[] = "PageUncleBlock";

  Reg<C> index;
  RegDigest<C> node;

  template<typename T>
  FDEV void applyInner(CTX) DEV {
    T::apply(ctx, index);
    T::apply(ctx, node);
  }

  FDEV void set(CTX, PageUncleWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}

  FDEV void verify(CTX) DEV {}
  FDEV void addArguments(CTX) DEV;
};

