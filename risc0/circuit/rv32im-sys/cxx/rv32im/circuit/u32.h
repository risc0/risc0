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

#include "rv32im/circuit/bits.h"
#include "rv32im/circuit/lookups.h"

template <typename C> inline FDEV ValU32<C> cond(Val<C> c, ValU32<C> a, ValU32<C> b) {
  return ValU32<C>(c * a.low + (Val<C>(1) - c) * b.low, c * a.high + (Val<C>(1) - c) * b.high);
}

// A 32 bit value stored in two parts
// Note: RegU32 does *not* validate that low + high are each U16s
template <typename C> struct RegU32 {
  CONSTANT static char NAME[] = "RegU32<C>";

  Reg<C> low;
  Reg<C> high;

  template <typename T> FDEV void applyInner(CTX) DEV {
    T::apply(ctx, "low", low);
    T::apply(ctx, "high", high);
  }

  FDEV void set(CTX, uint32_t val) DEV;
  FDEV inline void finalize(CTX) DEV {}
  FDEV ValU32<C> get() DEV;
  FDEV Val<C> flat() DEV;
  FDEV void verify(CTX) DEV {}
  FDEV void addArguments(CTX) DEV {}
};

// An adder that takes two (presumably valid) ValU32<C>'s and add them
// Propagates carrys + range checks the output (i.e. if the inputs)
// are valid, the output will be.
template <typename C> struct AddU32 {
  CONSTANT static char NAME[] = "AddU32";

  RegU16<C> low;
  BitReg<C> carryLow;
  RegU16<C> high;
  BitReg<C> carryHigh;

  template <typename T> FDEV void applyInner(CTX, ValU32<C> a, ValU32<C> b) DEV {
    T::apply(ctx, "low", low);
    T::apply(ctx, "carryLow", carryLow);
    T::apply(ctx, "high", high);
    T::apply(ctx, "carryHigh", carryHigh);
  }

  // Set based on the 32 bit inputs
  FDEV void set(CTX, uint32_t a, uint32_t b, bool carryIn = false) DEV;
  FDEV inline void finalize(CTX) DEV {}
  // Gets the output
  FDEV ValU32<C> get() DEV;
  // The verification also requires the inputs
  FDEV void verify(CTX, ValU32<C> a, ValU32<C> b) DEV;
  FDEV void addArguments(CTX, ValU32<C> a, ValU32<C> b) DEV {}
};

// Two's complement negation, returns an 'denormalized' value, but
// still small enough to be passed safely to an adder.
template <typename C> inline FDEV ValU32<C> negate(ValU32<C> val) {
  return ValU32<C>(Val<C>(0xffff) - val.low + 1, Val<C>(0xffff) - val.high);
}

// Given a 32 bit address and a mode get the 'wordAddr' and the low 2 bits
template <typename C> struct AddressDecompose {
  CONSTANT static char NAME[] = "AddressDecompose";

  // Hold the 14 low bits of the wordAddr
  RegU16<C> mid14;
  // Low 2 bits
  BitReg<C> low0;
  BitReg<C> low1;

  template <typename T> FDEV void applyInner(CTX, ValU32<C> val) DEV {
    T::apply(ctx, "mid14", mid14);
    T::apply(ctx, "low0", low0);
    T::apply(ctx, "low1", low1);
  }

  FDEV void set(CTX, uint32_t val) DEV;
  FDEV inline void finalize(CTX) DEV {}
  // Compute the actual answer, by not recording, we save a register
  FDEV Val<C> wordAddr(ValU32<C> val) DEV;
  FDEV void verify(CTX, ValU32<C> val) DEV;
  FDEV void addArguments(CTX, ValU32<C> val) DEV {}
};

// Verify an addresses legality in a given machine mode
template <typename C> struct AddressVerify {
  CONSTANT static char NAME[] = "AddressVerify";

  // Holds the 'maxHigh16 - high16', verifies the mode legality
  RegU16<C> highSub;

  template <typename T> FDEV void applyInner(CTX, ValU32<C> val, Val<C> mode) DEV {
    T::apply(ctx, "highSub", highSub);
  }

  FDEV void set(CTX, uint32_t val, uint32_t mode) DEV;
  FDEV inline void finalize(CTX) DEV {}
  FDEV void verify(CTX, ValU32<C> val, Val<C> mode) DEV;
  FDEV void addArguments(CTX, ValU32<C> val, Val<C> mode) DEV {}
};

template <typename C> struct GetSign {
  CONSTANT static char NAME[] = "GetSign";

  BitReg<C> sign;
  RegU16<C> signVerify;

  template <typename T> FDEV void applyInner(CTX, Val<C> inHigh) DEV {
    T::apply(ctx, "sign", sign);
    T::apply(ctx, "signVerify", signVerify);
  }

  FDEV void set(CTX, uint32_t val) DEV;
  FDEV inline void finalize(CTX) DEV {}
  FDEV Val<C> get() DEV { return sign.get(); }

  FDEV void verify(CTX, Val<C> inHigh) DEV;
  FDEV void addArguments(CTX, Val<C> inHigh) DEV {}
};

template <typename C> struct NegU32 {
  CONSTANT static char NAME[] = "NegU32";

  BitReg<C> carryLow;
  BitReg<C> carryHigh;
  RegU16<C> outLow;
  RegU16<C> outHigh;

  template <typename T> FDEV void applyInner(CTX, ValU32<C> in, Val<C> neg) DEV {
    T::apply(ctx, "carryLow", carryLow);
    T::apply(ctx, "carryHigh", carryHigh);
    T::apply(ctx, "outLow", outLow);
    T::apply(ctx, "outHigh", outHigh);
  }

  FDEV void set(CTX, uint32_t in, uint32_t neg) DEV;
  FDEV inline void finalize(CTX) DEV {}
  FDEV ValU32<C> get() DEV;
  FDEV void verify(CTX, ValU32<C> in, Val<C> neg) DEV;
  FDEV void addArguments(CTX, ValU32<C> in, Val<C> neg) DEV {}
};

template <typename C> struct AbsU32 {
  CONSTANT static char NAME[] = "AbsU32";

  RegU32<C> in; // Must be constrained elsewhere to be normalized
  BitReg<C> neg;
  BitReg<C> sign;
  RegU16<C> signVerify;
  BitReg<C> carryLow;
  BitReg<C> carryHigh;
  RegU16<C> absLow;
  RegU16<C> absHigh;

  template <typename T> FDEV void applyInner(CTX, Val<C> isSigned) DEV {
    T::apply(ctx, "in", in);
    T::apply(ctx, "neg", neg);
    T::apply(ctx, "sign", sign);
    T::apply(ctx, "signVerify", signVerify);
    T::apply(ctx, "carryLow", carryLow);
    T::apply(ctx, "carryHigh", carryHigh);
    T::apply(ctx, "absLow", absLow);
    T::apply(ctx, "absHigh", absHigh);
  }

  FDEV void set(CTX, uint32_t in, uint32_t isSigned) DEV;
  FDEV inline void finalize(CTX) DEV {}
  FDEV ValU32<C> getIn() DEV;
  FDEV ValU32<C> getAbs() DEV;
  FDEV void verify(CTX, Val<C> isSigned) DEV;
  FDEV void addArguments(CTX, Val<C> isSigned) DEV {}
};
