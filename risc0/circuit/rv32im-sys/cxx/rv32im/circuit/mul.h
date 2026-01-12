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

#include "rv32im/circuit/u32.h"

// Split a 32 bit value into 4 bytes, and also extract it's top bit
// Used in the multiplier
template <typename C> struct ExpandU32 {
  CONSTANT static char NAME[] = "ExpandU32";

  RegU8<C> b0;
  RegU8<C> b1;
  RegU8<C> b2;
  RegU8<C> b3;
  BitReg<C> topBit;
  RegU8<C> b3Low7times2;

  template <typename T> FDEV void applyInner(CTX) DEV {
    T::apply(ctx, "b0", b0);
    T::apply(ctx, "b1", b1);
    T::apply(ctx, "b2", b2);
    T::apply(ctx, "b3", b3);
    T::apply(ctx, "topBit", topBit);
    T::apply(ctx, "b3Low7times2", b3Low7times2);
  }

  FDEV void set(CTX, uint32_t val) DEV;
  FDEV inline void finalize(CTX) DEV {}
  FDEV ValU32<C> get() DEV;

  FDEV void verify(CTX) DEV;
  FDEV void addArguments(CTX) DEV {}
};

// Split a total that is < 26 bits into:
// out - bits 0-15
// carryByte - bits 16-23
// carryBit0 - bit 24
// carryBit1 - bit 25
template <typename C> struct SplitTotal {
  CONSTANT static char NAME[] = "SplitTotal";

  RegU16<C> out;
  RegU8<C> carryByte;
  BitReg<C> carryBit0;
  BitReg<C> carryBit1;

  template <typename T> FDEV void applyInner(CTX, Val<C> val) DEV {
    T::apply(ctx, "out", out);
    T::apply(ctx, "carryByte", carryByte);
    T::apply(ctx, "carryBit0", carryBit0);
    T::apply(ctx, "carryBit1", carryBit1);
  }

  FDEV void set(CTX, uint32_t val) DEV;
  FDEV inline void finalize(CTX) DEV {}
  // Get 10 bit carry value
  FDEV Val<C> carry() DEV;
  FDEV void verify(CTX, Val<C> val) DEV;
  FDEV void addArguments(CTX, Val<C> val) DEV {}
};

// Multiply 2 32-bit values, compute low / high of output
// Supports
template <typename C> struct Multiply {
  CONSTANT static char NAME[] = "Multiply";

  BitReg<C> signA;
  BitReg<C> signB;
  // We expand a + b
  ExpandU32<C> ax;
  ExpandU32<C> bx;
  // We sum terms effecting each of 4 words + then carry
  // Special case final word because carry is limited
  SplitTotal<C> s0;
  SplitTotal<C> s1;
  SplitTotal<C> s2;
  RegU16<C> s3Out;
  RegU8<C> s3Carry;

  template <typename T> FDEV void applyInner(CTX) DEV {
    T::apply(ctx, "signA", signA);
    T::apply(ctx, "signB", signB);
    T::apply(ctx, "ax", ax);
    T::apply(ctx, "bx", bx);
    T::apply(ctx, "s0", s0, valS0());
    T::apply(ctx, "s1", s1, valS1());
    T::apply(ctx, "s2", s2, valS2());
    T::apply(ctx, "s3Out", s3Out);
    T::apply(ctx, "s3Carry", s3Carry);
  }

  FDEV void set(CTX, uint32_t a, uint32_t b, uint32_t signA, uint32_t signB) DEV;
  FDEV inline void finalize(CTX) DEV {}
  FDEV ValU32<C> getA() DEV;
  FDEV ValU32<C> getB() DEV;
  FDEV ValU32<C> getOutLow() DEV;
  FDEV ValU32<C> getOutHigh() DEV;

  FDEV void verify(CTX) DEV;
  FDEV void addArguments(CTX) DEV {}

  // Helpers to compute each word's partial sum
  FDEV Val<C> valS0() DEV;
  FDEV Val<C> valS1() DEV;
  FDEV Val<C> valS2() DEV;
  FDEV Val<C> valS3() DEV;
};
