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

template <typename C> struct PhysMemReadBlock {
  CONSTANT static char NAME[] = "PhysMemReadBlock";

  Reg<C> wordAddr;
  Reg<C> prevCycle;
  RegU32<C> data;

  template <typename T> FDEV void applyInner(CTX, Val<C> cycle) DEV {
    T::apply(ctx, wordAddr);
    T::apply(ctx, prevCycle);
    T::apply(ctx, data);
  }

  FDEV void set(CTX, PhysMemReadWitness wit, uint32_t cycle) DEV;
  FDEV inline void finalize(CTX) DEV {}
  FDEV void verify(CTX, Val<C> cycle) DEV {}
  FDEV void addArguments(CTX, Val<C> cycle) DEV;
};

template <typename C> struct PhysMemWriteBlock {
  CONSTANT static char NAME[] = "PhysMemWriteBlock";

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

  FDEV void set(CTX, PhysMemWriteWitness wit, uint32_t cycle) DEV;
  FDEV inline void finalize(CTX) DEV {}
  FDEV void verify(CTX, Val<C> cycle) DEV {}
  FDEV void addArguments(CTX, Val<C> cycle) DEV;
};

template <typename C> struct VirtAddrBlock {
  CONSTANT static char NAME[] = "VirtAddrBlock";

  Reg<C> vpage;
  Reg<C> ppage;
  RegU8<C> lowByte;
  BitReg<C> bit8;
  BitReg<C> bit9;

  template <typename T> FDEV void applyInner(CTX, Val<C> cycle) DEV {
    T::apply(ctx, vpage);
    T::apply(ctx, ppage);
    T::apply(ctx, lowByte);
    T::apply(ctx, bit8);
    T::apply(ctx, bit9);
  }

  FDEV Val<C> getWordAddr() DEV {
    return ppage.get() * 0x400 + bit9.get() * 0x200 + bit8.get() * 0x100 + lowByte.get();
  }

  // TODO: Actual verification of address mapping
  FDEV void set(CTX, VirtAddrWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}
  FDEV void verify(CTX, Val<C> cycle) DEV {}
  FDEV void addArguments(CTX, Val<C> cycle) DEV {}
};

template <typename C> struct VirtMemReadBlock {
  CONSTANT static char NAME[] = "VirtMemReadBlock";

  VirtAddrBlock<C> addr;
  Reg<C> prevCycle;
  RegU32<C> data;

  template <typename T> FDEV void applyInner(CTX, Val<C> cycle) DEV {
    T::apply(ctx, addr, cycle);
    T::apply(ctx, prevCycle);
    T::apply(ctx, data);
  }

  FDEV Val<C> getWordAddr() DEV { return addr.getWordAddr(); }

  FDEV void set(CTX, VirtMemReadWitness wit, uint32_t cycle) DEV;
  FDEV inline void finalize(CTX) DEV {}
  FDEV void verify(CTX, Val<C> cycle) DEV {}
  FDEV void addArguments(CTX, Val<C> cycle) DEV;
};

template <typename C> struct VirtMemWriteBlock {
  CONSTANT static char NAME[] = "VirtMemWriteBlock";

  VirtAddrBlock<C> addr;
  Reg<C> prevCycle;
  RegU32<C> prevData;
  RegU32<C> data;

  template <typename T> FDEV void applyInner(CTX, Val<C> cycle) DEV {
    T::apply(ctx, addr, cycle);
    T::apply(ctx, prevCycle);
    T::apply(ctx, prevData);
    T::apply(ctx, data);
  }

  FDEV Val<C> getWordAddr() DEV { return addr.getWordAddr(); }

  FDEV void set(CTX, VirtMemWriteWitness wit, uint32_t cycle) DEV;
  FDEV inline void finalize(CTX) DEV {}
  FDEV void verify(CTX, Val<C> cycle) DEV {}
  FDEV void addArguments(CTX, Val<C> cycle) DEV;
};

template <typename C>
using RegMemReadBlock = PhysMemReadBlock<C>;

template <typename C>
using RegMemWriteBlock = PhysMemWriteBlock<C>;

