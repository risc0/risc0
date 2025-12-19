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

#include "rv32im/base/constants.h"
#include "rv32im/circuit/is_zero.h"
#include "rv32im/circuit/poseidon2.h"
#include "rv32im/circuit/u32.h"
#include "rv32im/witness/paging.h"

CONSTANT uint32_t NUM_PARTS = MPAGE_SIZE_WORDS / MPAGE_PART_SIZE;

template <typename C> struct PageInNodeBlock {
  CONSTANT static char NAME[] = "PageInNodeBlock";

  Reg<C> index;
  RegDigest<C> node;
  RegDigest<C> left;
  RegDigest<C> right;

  template <typename T> FDEV void applyInner(CTX) DEV {
    T::apply(ctx, "index", index);
    T::apply(ctx, "node", node);
    T::apply(ctx, "left", left);
    T::apply(ctx, "right", right);
  }

  FDEV void set(CTX, PageInNodeWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}

  FDEV void verify(CTX) DEV {}
  FDEV void addArguments(CTX) DEV;
};

template <typename C> struct PageInPartBlock {
  CONSTANT static char NAME[] = "PageInPartBlock";

  Reg<C> addr;
  Reg<C> partNum;
  RegDigest<C> in;
  RegDigest<C> out;
  RegU32<C> data[MPAGE_PART_SIZE];
  IsZero<C> lastPart;

  template <typename T> FDEV void applyInner(CTX) DEV {
    T::apply(ctx, "addr", addr);
    T::apply(ctx, "partNum", partNum);
    T::apply(ctx, "in", in);
    T::apply(ctx, "out", out);
    T::apply(ctx, "data", data);
    T::apply(ctx, "lastPart", lastPart, Val<C>(NUM_PARTS - 1) - partNum.get());
  }

  FDEV void set(CTX, PageInPartWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}

  FDEV void verify(CTX) DEV {}
  FDEV void addArguments(CTX) DEV;
};

template <typename C> struct PageInPageBlock {
  CONSTANT static char NAME[] = "PageInPageBlock";

  Reg<C> addr;
  RegDigest<C> node;

  template <typename T> FDEV void applyInner(CTX) DEV {
    T::apply(ctx, "addr", addr);
    T::apply(ctx, "node", node);
  }

  FDEV void set(CTX, PageInPageWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}

  FDEV void verify(CTX) DEV {}
  FDEV void addArguments(CTX) DEV;
};

template <typename C> struct PageOutNodeBlock {
  CONSTANT static char NAME[] = "PageOutNodeBlock";

  Reg<C> index;
  RegDigest<C> node;
  RegDigest<C> left;
  RegDigest<C> right;

  template <typename T> FDEV void applyInner(CTX) DEV {
    T::apply(ctx, "index", index);
    T::apply(ctx, "node", node);
    T::apply(ctx, "left", left);
    T::apply(ctx, "right", right);
  }

  FDEV void set(CTX, PageOutNodeWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}

  FDEV void verify(CTX) DEV {}
  FDEV void addArguments(CTX) DEV;
};

template <typename C> struct PageOutPartBlock {
  CONSTANT static char NAME[] = "PageOutPartBlock";

  Reg<C> addr;
  Reg<C> partNum;
  RegDigest<C> in;
  RegDigest<C> out;
  RegU32<C> data[MPAGE_PART_SIZE];
  Reg<C> cycle[MPAGE_PART_SIZE];
  IsZero<C> lastPart;

  template <typename T> FDEV void applyInner(CTX) DEV {
    T::apply(ctx, "addr", addr);
    T::apply(ctx, "partNum", partNum);
    T::apply(ctx, "in", in);
    T::apply(ctx, "out", out);
    T::apply(ctx, "data", data);
    T::apply(ctx, "cycle", cycle);
    T::apply(ctx, "lastPart", lastPart, Val<C>(NUM_PARTS - 1) - partNum.get());
  }

  FDEV void set(CTX, PageOutPartWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}

  FDEV void verify(CTX) DEV {}
  FDEV void addArguments(CTX) DEV;
};

template <typename C> struct PageOutPageBlock {
  CONSTANT static char NAME[] = "PageOutPageBlock";

  Reg<C> addr;
  RegDigest<C> node;

  template <typename T> FDEV void applyInner(CTX) DEV {
    T::apply(ctx, "addr", addr);
    T::apply(ctx, "node", node);
  }

  FDEV void set(CTX, PageOutPageWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}

  FDEV void verify(CTX) DEV {}
  FDEV void addArguments(CTX) DEV;
};

template <typename C> struct PageUncleBlock {
  CONSTANT static char NAME[] = "PageUncleBlock";

  Reg<C> index;
  RegDigest<C> node;

  template <typename T> FDEV void applyInner(CTX) DEV {
    T::apply(ctx, "index", index);
    T::apply(ctx, "node", node);
  }

  FDEV void set(CTX, PageUncleWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}

  FDEV void verify(CTX) DEV {}
  FDEV void addArguments(CTX) DEV;
};
