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

#include "rv32im/witness/units.h"
#include "rv32im/circuit/is_zero.h"
#include "rv32im/circuit/mul.h"
#include "rv32im/circuit/one_hot.h"
#include "rv32im/circuit/u32.h"

template<typename C>
struct UnitAddSubBlock {
  CONSTANT static char NAME[] = "UnitAddSubBlock";

  ArgCountReg<C> count;
  BitReg<C> doSub;
  RegU32<C> a;
  RegU32<C> b;
  AddU32<C> out;

  template<typename T>
  FDEV void applyInner(CTX) DEV {
    T::apply(ctx, count);
    T::apply(ctx, doSub);
    T::apply(ctx, a);
    T::apply(ctx, b);
    ValU32<C> v = cond<C>(doSub.get(), negate(b.get()), b.get());
    T::apply(ctx, out, a.get(), v);
  }

  FDEV void set(CTX, UnitAddSubWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}

  FDEV void verify(CTX) DEV {}
  FDEV void addArguments(CTX) DEV;
};

template<typename C>
struct UnitBitBlock {
  CONSTANT static char NAME[] = "UnitBitBlock";

  ArgCountReg<C> count;
  OneHot<C, 3> op;
  RegU32<C> a;
  RegU32<C> b;
  RegU32<C> out;
  BitReg<C> aBits[32];
  BitReg<C> bBits[32];

  template<typename T>
  FDEV void applyInner(CTX) DEV {
    T::apply(ctx, count);
    T::apply(ctx, op);
    T::apply(ctx, a);
    T::apply(ctx, b);
    T::apply(ctx, out);
    T::apply(ctx, aBits);
    T::apply(ctx, bBits);
  }

  FDEV void set(CTX, UnitBitWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}

  FDEV void verify(CTX) DEV;
  FDEV void addArguments(CTX) DEV;
};

template<typename C>
struct UnitMulBlock {
  CONSTANT static char NAME[] = "UnitMulBlock";

  ArgCountReg<C> count;
  Multiply<C> mul;

  template<typename T>
  FDEV void applyInner(CTX) DEV {
    T::apply(ctx, count);
    T::apply(ctx, mul);
  }

  FDEV void set(CTX, UnitMulWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}

  FDEV void verify(CTX) DEV;
  FDEV void addArguments(CTX) DEV;
};

template<typename C>
struct UnitDivBlock {
  CONSTANT static char NAME[] = "UnitDivBlock";

  ArgCountReg<C> count;
  BitReg<C> isSigned;
  AbsU32<C> numer;
  AbsU32<C> denom;
  RegU32<C> absQuot;
  RegU32<C> total;
  RegU16<C> absRemLow;
  RegU16<C> absRemHigh;
  AddU32<C> addTotRem;
  IsZero<C> denomZero;
  // For denom != 0, We should have (denom - 1) - rem >= 0
  // denom -1 + (-rem)
  // denom -1 + (~rem + 1) (two's complement)
  // denom + ~rem
  AddU32<C> verifyRem;
  BitReg<C> negQuot;
  NegU32<C> flipQuot;
  NegU32<C> flipRem;

  template<typename T>
  FDEV void applyInner(CTX) DEV {
    ValU32<C> absRem = ValU32<C>(absRemLow.get(), absRemHigh.get());
    T::apply(ctx, count);
    T::apply(ctx, isSigned);
    T::apply(ctx, numer, isSigned.get());
    T::apply(ctx, denom, isSigned.get());
    T::apply(ctx, absQuot);
    T::apply(ctx, total);
    T::apply(ctx, absRemLow);
    T::apply(ctx, absRemHigh);
    T::apply(ctx, addTotRem, total.get(), absRem);
    T::apply(ctx, denomZero, denom.in.low.get() + denom.in.high.get());
    T::apply(ctx, verifyRem, ValU32<C>(denom.absLow.get(), denom.absHigh.get()),
        ValU32<C>(Val<C>(0xffff) - absRemLow.get(), Val<C>(0xffff) - absRemHigh.get()));
    T::apply(ctx, negQuot);
    T::apply(ctx, flipQuot, absQuot.get(), negQuot.get());
    T::apply(ctx, flipRem, absRem, numer.neg.get());
  }

  FDEV void set(CTX, UnitDivWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}
  FDEV void verify(CTX) DEV;
  FDEV void addArguments(CTX) DEV;
};

template<typename C>
struct UnitLtBlock {
  CONSTANT static char NAME[] = "UnitLtBlock";

  ArgCountReg<C> count;
  RegU32<C> a;
  RegU32<C> b;
  AddU32<C> diff;
  GetSign<C> signA;
  GetSign<C> signB;
  GetSign<C> signDiff;
  BitReg<C> overflow;
  BitReg<C> isLt;

  template<typename T>
  FDEV void applyInner(CTX) DEV {
    T::apply(ctx, count);
    T::apply(ctx, a);
    T::apply(ctx, b);
    T::apply(ctx, diff, a.get(), negate(b.get()));
    T::apply(ctx, signA, a.get().high);
    T::apply(ctx, signB, b.get().high);
    T::apply(ctx, signDiff, diff.get().high);
    T::apply(ctx, overflow);
    T::apply(ctx, isLt);
  }

  FDEV void set(CTX, UnitLtWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}

  FDEV Val<C> computeOverflow() DEV;
  FDEV Val<C> computeLt() DEV;
  FDEV void verify(CTX) DEV;
  FDEV void addArguments(CTX) DEV;
};

template<typename C>
struct UnitShiftBlock {
  CONSTANT static char NAME[] = "UnitShiftBlock";

  ArgCountReg<C> count;
  RegU32<C> a;
  RegU32<C> b;
  OneHot<C, 3> opt;
  BitReg<C> bits[8];
  RegU8<C> byte1;
  Reg<C> po2First3;
  RegU32<C> po2;
  GetSign<C> signA;
  BitReg<C> neg;
  RegU32<C> maybeNegA;
  RegU32<C> maybeNegOut;
  RegU32<C> out;
  RegU32<C> out2;

  template<typename T>
  FDEV void applyInner(CTX) DEV {
    T::apply(ctx, count);
    T::apply(ctx, a);
    T::apply(ctx, b);
    T::apply(ctx, opt);
    T::apply(ctx, bits);
    T::apply(ctx, byte1);
    T::apply(ctx, po2First3);
    T::apply(ctx, po2);
    T::apply(ctx, signA, a.get().high);
    T::apply(ctx, maybeNegA);
    T::apply(ctx, maybeNegOut);
    T::apply(ctx, out);
    T::apply(ctx, out2);
  }

  FDEV void set(CTX, UnitShiftWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}

  FDEV void verify(CTX) DEV;
  FDEV void addArguments(CTX) DEV;
};
