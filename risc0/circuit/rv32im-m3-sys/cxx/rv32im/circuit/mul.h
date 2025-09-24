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

#include "rv32im/circuit/u32.h"

// Split a 32 bit value into 4 bytes, and also extract it's top bit
// Used in the multiplier
template<typename C>
struct ExpandU32 {
  CONSTANT static char NAME[] = "ExpandU32";

  RegU8<C> b0;
  RegU8<C> b1;
  RegU8<C> b2;
  RegU8<C> b3;
  BitReg<C> topBit;
  RegU8<C> b3Low7times2;

  template<typename T>
  FDEV void applyInner(CTX) DEV {
    T::apply(ctx, b0);
    T::apply(ctx, b1);
    T::apply(ctx, b2);
    T::apply(ctx, b3);
    T::apply(ctx, topBit);
    T::apply(ctx, b3Low7times2);
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
template<typename C>
struct SplitTotal {
  CONSTANT static char NAME[] = "SplitTotal";

  RegU16<C> out;
  RegU8<C> carryByte;
  BitReg<C> carryBit0;
  BitReg<C> carryBit1;

  template<typename T>
  FDEV void applyInner(CTX, Val<C> val) DEV {
    T::apply(ctx, out);
    T::apply(ctx, carryByte);
    T::apply(ctx, carryBit0);
    T::apply(ctx, carryBit1);
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
template<typename C>
struct Multiply {
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

  template<typename T>
  FDEV void applyInner(CTX) DEV {
    T::apply(ctx, signA);
    T::apply(ctx, signB);
    T::apply(ctx, ax);
    T::apply(ctx, bx);
    T::apply(ctx, s0, valS0());
    T::apply(ctx, s1, valS1());
    T::apply(ctx, s2, valS2());
    T::apply(ctx, s3Out);
    T::apply(ctx, s3Carry);
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
