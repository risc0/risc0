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

#include "rv32im/circuit/u32.h"
#include "rv32im/witness/mem.h"

template <typename C> struct MemReadBlock {
  CONSTANT static char NAME[] = "MemReadBlock";

  Reg<C> wordAddr;
  Reg<C> prevCycle;
  RegU32<C> data;

  template <typename T> FDEV void applyInner(CTX, Val<C> cycle) DEV {
    T::apply(ctx, wordAddr);
    T::apply(ctx, prevCycle);
    T::apply(ctx, data);
  }

  FDEV void set(CTX, MemReadWitness wit, uint32_t cycle) DEV;
  FDEV inline void finalize(CTX) DEV {}
  FDEV void verify(CTX, Val<C> cycle) DEV {}
  FDEV void addArguments(CTX, Val<C> cycle) DEV;
};

template <typename C> struct MemWriteBlock {
  CONSTANT static char NAME[] = "MemWriteBlock";

  Reg<C> wordAddr;
  Reg<C> prevCycle;
  RegU32<C> prevData;
  RegU32<C> data;

  template <typename T> FDEV void applyInner(CTX, Val<C> cycle) DEV {
    T::apply(ctx, wordAddr);
    T::apply(ctx, prevCycle);
    T::apply(ctx, prevData);
    T::apply(ctx, data);
  }

  FDEV void set(CTX, MemWriteWitness wit, uint32_t cycle) DEV;
  FDEV inline void finalize(CTX) DEV {}
  FDEV void verify(CTX, Val<C> cycle) DEV {}
  FDEV void addArguments(CTX, Val<C> cycle) DEV;
};
