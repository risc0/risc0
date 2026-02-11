// Copyright 2026 RISC Zero, Inc.
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

#include "rv32im/base/base.h"
#include "rv32im/base/constants.h"
#include "rv32im/circuit/is_zero.h"
#include "rv32im/circuit/mem.h"
#include "rv32im/circuit/one_hot.h"
#include "rv32im/circuit/u32.h"
#include "rv32im/witness/bigint.h"

// TODO: handling of user / machine mode doesn't really work unless isUM is set
template <typename C> struct BigIntBlock {
  CONSTANT static char NAME[] = "BigInt";

  Reg<C> cycle;
  BitReg<C> mm;
  PhysMemReadBlock<C> readInst;
  PhysMemReadBlock<C> readBaseReg;
  OneHot<C, 3> memOp;
  OneHot<C, POLY_OP_SIZE> polyOp;
  BitReg<C> coeffBits[3];
  BitReg<C> regBits[5];
  Reg<C> offset;
  RegU8<C> offset16High;
  RegU16<C> offset16Low;
  AddU32<C> computeAddr;
  IsZero<C> isLastPage;
  AddressDecompose<C> wordBase;
  AddressVerify<C> checkBase;
  RegU8<C> bytes[16];
  Reg<C> prevCycle[4];
  RegU32<C> prevValue[4];

  template <typename T> FDEV void applyInner(CTX) DEV {
    T::apply(ctx, "cycle", cycle);
    T::apply(ctx, "mm", mm);
    T::apply(ctx, "readInst", readInst, cycle.get());
    T::apply(ctx, "readBaseReg", readBaseReg, cycle.get());
    T::apply(ctx, "memOp", memOp);
    T::apply(ctx, "polyOp", polyOp);
    T::apply(ctx, "coeffBits", coeffBits);
    T::apply(ctx, "regBits", regBits);
    T::apply(ctx, "offset", offset);
    T::apply(ctx, "offset16High", offset16High);
    T::apply(ctx, "offset16Low", offset16Low);
    T::apply(ctx,
             "computeAddr",
             computeAddr,
             readBaseReg.data.get(),
             ValU32<C>(offset16Low.get(), offset16High.get()));
    T::apply(ctx, "isLastPage", isLastPage, computeAddr.get().high - Val<C>(0xbfff));
    T::apply(ctx, "wordBase", wordBase, computeAddr.get());
    T::apply(ctx, "checkBase", checkBase, computeAddr.get(), mm.get() * Val<C>(MODE_MACHINE));
    T::apply(ctx, "bytes", bytes);
    T::apply(ctx, "prevCycle", prevCycle);
    T::apply(ctx, "prevValue", prevValue);
  }

  FDEV Val<C> getCoeff() DEV {
    Val<C> out = 0;
    for (size_t i = 0; i < 3; i++) {
      out += coeffBits[i].get() * (1 << i);
    }
    return out;
  }

  FDEV Val<C> getReg() DEV {
    Val<C> out = 0;
    for (size_t i = 0; i < 5; i++) {
      out += regBits[i].get() * (1 << i);
    }
    return out;
  }

  FDEV void set(CTX, BigIntWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}
  FDEV void verify(CTX) DEV;
  FDEV void addArguments(CTX) DEV;
};
