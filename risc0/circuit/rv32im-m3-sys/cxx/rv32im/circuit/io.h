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

#include "rv32im/witness/io.h"
#include "rv32im/circuit/mem.h"

template<typename C>
struct ReadByteBlock {
  CONSTANT static char NAME[] = "ReadByte";

  Reg<C> cycle;
  BitReg<C> lowBit0;
  BitReg<C> lowBit1;
  MemWriteBlock<C> io;
  RegU8<C> lowByte;
  RegU8<C> highByte;
  RegU8<C> newByte;
  Reg<C> is3;
  RegU16<C> sizeMinus1;

  template<typename T>
  FDEV void applyInner(CTX) DEV {
    T::apply(ctx, cycle);
    T::apply(ctx, lowBit0);
    T::apply(ctx, lowBit1);
    T::apply(ctx, io, cycle.get());
    T::apply(ctx, lowByte);
    T::apply(ctx, highByte);
    T::apply(ctx, newByte);
    T::apply(ctx, is3);
    T::apply(ctx, sizeMinus1);
  }

  FDEV void set(CTX, ReadByteWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}
  FDEV void verify(CTX) DEV;
  FDEV void addArguments(CTX) DEV;
};

template<typename C>
struct ReadWordBlock {
  CONSTANT static char NAME[] = "ReadWord";

  Reg<C> cycle;
  RegU16<C> sizeMinus4;
  MemWriteBlock<C> io;

  template<typename T>
  FDEV void applyInner(CTX) DEV {
    T::apply(ctx, cycle);
    T::apply(ctx, sizeMinus4);
    T::apply(ctx, io, cycle.get());
  }

  FDEV void set(CTX, ReadWordWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}
  FDEV void verify(CTX) DEV;
  FDEV void addArguments(CTX) DEV;
};

