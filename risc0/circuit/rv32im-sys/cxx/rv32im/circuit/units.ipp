// Copyright 2026 RISC Zero, Inc.
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

#define UNIT_BLOCK_INPUTS(ctx, arg)                                                                \
  PICUS_INPUT(ctx, arg.opts);                                                                      \
  PICUS_INPUT(ctx, arg.aLow);                                                                      \
  PICUS_INPUT(ctx, arg.aHigh);                                                                     \
  PICUS_INPUT(ctx, arg.bLow);                                                                      \
  PICUS_INPUT(ctx, arg.bHigh)

// Do we need do bound the value of arg.opts here? (< 18)
#define UNIT_ARGUMENT(ctx, arg)                                                                    \
  PICUS_ARGUMENT(ctx,                                                                              \
                 ({ctx.get(arg.opts),                                                              \
                   ctx.get(arg.aLow),                                                              \
                   ctx.get(arg.aHigh),                                                             \
                   ctx.get(arg.bLow),                                                              \
                   ctx.get(arg.bHigh)}),                                                           \
                 ({ctx.get(arg.out0Low),                                                           \
                   ctx.get(arg.out0High),                                                          \
                   ctx.get(arg.out1Low),                                                           \
                   ctx.get(arg.out1High)}))

template <typename C> FDEV void UnitAddSubBlock<C>::set(CTX, UnitAddSubWitness wit) DEV {
  count.set(ctx, wit.count);
  Option opts(wit.opts);
  opts.pop<UnitKind>();
  doSub.set(ctx, opts.val);
  a.set(ctx, wit.a);
  b.set(ctx, wit.b);
  out.set(ctx, wit.a, (opts.val ? ~wit.b : wit.b), opts.val);
}

template <typename C> FDEV void UnitAddSubBlock<C>::verify(CTX) DEV {}

template <typename C> FDEV void UnitAddSubBlock<C>::addArguments(CTX) DEV {
  UnitArgument<C> arg;
  arg.opts = doSub.get() * Val<C>(OptSize<UnitKind>::value) + Val<C>(uint32_t(UNIT_ADDSUB));
  arg.aLow = a.low.get();
  arg.aHigh = a.high.get();
  arg.bLow = b.low.get();
  arg.bHigh = b.high.get();
  ValU32<C> outVal = out.get();
  arg.out0Low = outVal.low;
  arg.out0High = outVal.high;
  arg.out1Low = 0;
  arg.out1High = 0;
  ctx.addArgument(count.get(), arg);
  PICUS_INPUT(ctx, count);
  UNIT_BLOCK_INPUTS(ctx, arg);
}

template <typename C> FDEV void UnitBitBlock<C>::set(CTX, UnitBitWitness wit) DEV {
  count.set(ctx, wit.count);
  Option opts(wit.opts);
  opts.pop<UnitKind>();
  op.set(ctx, opts.val);
  a.set(ctx, wit.a);
  b.set(ctx, wit.b);
  out.set(ctx, wit.out0);
  for (size_t i = 0; i < 32; i++) {
    aBits[i].set(ctx, (wit.a >> i) & 1);
    bBits[i].set(ctx, (wit.b >> i) & 1);
  }
}

template <typename C> FDEV void UnitBitBlock<C>::verify(CTX) DEV {
  // Assert that aBits and bBits are bit decompositions of a and b. Also compute
  // the "recomposition" of aBits, bBits, and their product into shorts for use
  // in a moment.
  Val<C> aParts[2], bParts[2], andParts[2];
  for (size_t p = 0; p < 2; p++) {
    for (size_t i = 0; i < 16; i++) {
      Val<C> po2 = (1 << i);
      Val<C> aVal = aBits[16 * p + i].get();
      Val<C> bVal = bBits[16 * p + i].get();
      aParts[p] += aVal * po2;
      bParts[p] += bVal * po2;
      andParts[p] += aVal * bVal * po2;
    }
  }

  // Assert that aBits and bBits recompose into a and b.
  EQ(aParts[0], a.low.get());
  EQ(aParts[1], a.high.get());
  EQ(bParts[0], b.low.get());
  EQ(bParts[1], b.high.get());

  // Now we want to assert that out is computed correctly from a and b, and bits
  // encodes whether we're computing XOR, OR, or AND. Noting that we've already
  // computed AND(a, b), we can relate XOR(a, b) and OR(a, b) with ordinary
  // addition (and therefore field addition without overflow) with some
  // manipulation of the equations of a ripple-carry adder:
  //
  // XOR(a, b) = a + b - 2 * AND(a, b)
  // OR(a, b) = a + b - AND(a, b)
  // AND(a, b) = AND(a, b)
  //
  // Since these equations have common structure, we can write the result of
  // each possible operation in the form c1 * (a + b) + c2 * AND(a, b).
  Val<C> c1 = op.bits[0].get() + op.bits[1].get();
  Val<C> c2 = op.bits[0].get() * (-Val<C>(2)) + op.bits[1].get() * (-Val<C>(1)) + op.bits[2].get();
  // LOG(0, "c1 = " << c1 << ", c2 = " << c2);
  // LOG(0, "a = " << std::hex << aParts[0] << ", b = " << bParts[0] << ", out =
  // " << out.low.get() << std::dec);
  EQ(c1 * (aParts[0] + bParts[0]) + c2 * andParts[0], out.low.get());
  EQ(c1 * (aParts[1] + bParts[1]) + c2 * andParts[1], out.high.get());
}

template <typename C> FDEV void UnitBitBlock<C>::addArguments(CTX) DEV {
  UnitArgument<C> arg;
  arg.opts = op.get() * Val<C>(OptSize<UnitKind>::value) + Val<C>(uint32_t(UNIT_BIT));
  arg.aLow = a.low.get();
  arg.aHigh = a.high.get();
  arg.bLow = b.low.get();
  arg.bHigh = b.high.get();
  arg.out0Low = out.low.get();
  arg.out0High = out.high.get();
  arg.out1Low = 0;
  arg.out1High = 0;
  ctx.addArgument(count.get(), arg);
  PICUS_INPUT(ctx, count);
  UNIT_BLOCK_INPUTS(ctx, arg);
}

template <typename C> FDEV void UnitMulBlock<C>::set(CTX, UnitMulWitness wit) DEV {
  Option opts(wit.opts);
  opts.pop<UnitKind>();
  uint32_t signA, signB;
  switch (opts.peek<MulKind>()) {
  case MUL_SS:
    signA = 1;
    signB = 1;
    break;
  case MUL_SU:
    signA = 1;
    signB = 0;
    break;
  case MUL_UU:
    signA = 0;
    signB = 0;
    break;
  }
  count.set(ctx, wit.count);
  mul.set(ctx, wit.a, wit.b, signA, signB);
}

template <typename C> FDEV void UnitMulBlock<C>::verify(CTX) DEV {
  // Disallow signA = 0, sign B = 1
  EQZ((Val<C>(1) - mul.signA.get()) * mul.signB.get());
}

template <typename C> FDEV void UnitMulBlock<C>::addArguments(CTX) DEV {
  UnitArgument<C> arg;
  Val<C> signOpt = Val<C>(2) - mul.signA.get() - mul.signB.get();
  arg.opts = signOpt * Val<C>(OptSize<UnitKind>::value) + Val<C>(uint32_t(UNIT_MUL));
  arg.aLow = mul.getA().low;
  arg.aHigh = mul.getA().high;
  arg.bLow = mul.getB().low;
  arg.bHigh = mul.getB().high;
  arg.out0Low = mul.getOutLow().low;
  arg.out0High = mul.getOutLow().high;
  arg.out1Low = mul.getOutHigh().low;
  arg.out1High = mul.getOutHigh().high;
  ctx.addArgument(count.get(), arg);
  PICUS_INPUT(ctx, count);
  UNIT_BLOCK_INPUTS(ctx, arg);
}

template <typename C> FDEV void UnitDivBlock<C>::set(CTX, UnitDivWitness wit) DEV {
  Option opts(wit.opts);
  opts.pop<UnitKind>();
  count.set(ctx, wit.count);
  isSigned.set(ctx, opts.val);
  numer.set(ctx, wit.a, opts.val);
  denom.set(ctx, wit.b, opts.val);
  bool negNumer = false;
  uint32_t absNumer = wit.a;
  bool negDenom = false;
  uint32_t absDenom = wit.b;
  if (opts.peek<DivKind>() == DIV_S) {
    if (absNumer & 0x80000000) {
      negNumer = true;
      absNumer = ~absNumer + 1;
    }
    if (absDenom & 0x80000000) {
      negDenom = true;
      absDenom = ~absDenom + 1;
    }
  }
  uint32_t absQuotU32 = (absDenom == 0 ? 0xffffffff : absNumer / absDenom);
  uint32_t absRemU32 = (absDenom == 0 ? absNumer : absNumer % absDenom);
  absQuot.set(ctx, absQuotU32);
  absRemLow.set(ctx, absRemU32 & 0xffff);
  absRemHigh.set(ctx, absRemU32 >> 16);
  uint32_t totalU32 = absQuotU32 * absDenom;
  total.set(ctx, totalU32);
  addTotRem.set(ctx, totalU32, absRemU32);
  denomZero.set(ctx, (wit.b & 0xffff) + (wit.b >> 16));
  verifyRem.set(ctx, absDenom, ~absRemU32);
  bool negQuotVal = negDenom ^ negNumer;
  if (absDenom == 0) {
    negQuotVal = false;
  }
  negQuot.set(ctx, negQuotVal);
  flipQuot.set(ctx, absQuotU32, negQuotVal);
  flipRem.set(ctx, absRemU32, negNumer);
}

template <typename C> FDEV void UnitDivBlock<C>::verify(CTX) DEV {
  /*
  LOG(0, std::hex);
  LOG(0, "isSigned = " << isSigned.get());
  LOG(0, "numer = " << numer.in.high.get() << ":" << numer.in.low.get());
  LOG(0, "denom = " << denom.in.high.get() << ":" << denom.in.low.get());
  LOG(0, "absNumer = " << numer.absHigh.get() << ":" << numer.absLow.get());
  LOG(0, "absDenom = " << denom.absHigh.get() << ":" << denom.absLow.get());
  LOG(0, "absQuot = " << absQuot.high.get() << ":" << absQuot.low.get());
  LOG(0, "absRem = " << absRemHigh.get() << ":" << absRemLow.get());
  LOG(0, "total = " << total.high.get() << ":" << total.low.get());
  LOG(0, "addTotRem = " << addTotRem.high.get() << ":" << addTotRem.low.get());
  LOG(0, "negQuot = " << negQuot.get());
  LOG(0, "negRem = " << numer.neg.get());
  LOG(0, "flipQuot = " << flipQuot.outHigh.get() << ":" <<
  flipQuot.outLow.get()); LOG(0, "flipRem = " << flipRem.outHigh.get() << ":" <<
  flipRem.outLow.get()); LOG(0, std::dec);
  */

  // Verify that negQuot is the sign of the quotient. It should be set if we're
  // doing signed division, the signs of the numerator and denominator differ,
  // and the denominator is nonzero.
  Val<C> negDenom = denom.neg.get();
  Val<C> negNumer = numer.neg.get();
  Val<C> negXor = negDenom * (Val<C>(1) - negNumer) + (Val<C>(1) - negDenom) * negNumer;
  Val<C> nz = Val<C>(1) - denomZero.isZero.get();
  EQ(negQuot.get(), nz * negXor);

  // Check that quotient * denom + remainder = numerator
  EQ(addTotRem.get().low, numer.absLow.get());
  EQ(addTotRem.get().high, numer.absHigh.get());

  // Prevent quotient * denom + remainder from overflowing.
  EQZ(addTotRem.carryHigh.get());
  EQZ(nz * (Val<C>(1) - verifyRem.carryHigh.get()));

  // If the denominator is zero, then we should have quotient = 0xffffffff.
  EQZ(denomZero.isZero.get() * (absQuot.high.get() - 0xffff));
  EQZ(denomZero.isZero.get() * (absQuot.low.get() - 0xffff));
}

template <typename C> FDEV void UnitDivBlock<C>::addArguments(CTX) DEV {
  // Produce division
  UnitArgument<C> arg;
  arg.opts = isSigned.get() * Val<C>(OptSize<UnitKind>::value) + Val<C>(uint32_t(UNIT_DIV));
  arg.aLow = numer.in.low.get();
  arg.aHigh = numer.in.high.get();
  arg.bLow = denom.in.low.get();
  arg.bHigh = denom.in.high.get();
  arg.out0Low = flipQuot.outLow.get();
  arg.out0High = flipQuot.outHigh.get();
  arg.out1Low = flipRem.outLow.get();
  arg.out1High = flipRem.outHigh.get();
  ctx.addArgument(count.get(), arg);
  // Require multiplication
  arg.opts = Val<C>(uint32_t(MUL_UU) * OptSize<UnitKind>::value + uint32_t(UNIT_MUL));
  arg.aLow = absQuot.low.get();
  arg.aHigh = absQuot.high.get();
  arg.bLow = denom.absLow.get();
  arg.bHigh = denom.absHigh.get();
  arg.out0Low = total.low.get();
  arg.out0High = total.high.get();
  arg.out1Low = 0;
  arg.out1High = 0;
  ctx.pull(arg);
}

template <typename C> FDEV Val<C> UnitLtBlock<C>::computeOverflow() DEV {
  Val<C> s1 = signA.get();
  Val<C> s2 = signB.get();
  Val<C> s3 = signDiff.get();
  return s1 * (Val<C>(1) - s2) * (Val<C>(1) - s3) + (Val<C>(1) - s1) * s2 * s3;
}

template <typename C> FDEV Val<C> UnitLtBlock<C>::computeLt() DEV {
  Val<C> s3 = signDiff.get();
  Val<C> overflowVal = overflow.get();
  return overflowVal + s3 - Val<C>(2) * overflowVal * s3;
}

template <typename C> FDEV void UnitLtBlock<C>::set(CTX, UnitLtWitness wit) DEV {
  count.set(ctx, wit.count);
  a.set(ctx, wit.a);
  b.set(ctx, wit.b);
  diff.set(ctx, wit.a, ~wit.b, 1);
  signA.set(ctx, wit.a);
  signB.set(ctx, wit.b);
  signDiff.set(ctx, wit.a - wit.b);
  overflow.set(ctx, computeOverflow());
  isLt.set(ctx, computeLt());
}

template <typename C> FDEV void UnitLtBlock<C>::verify(CTX) DEV {
  EQ(overflow.get(), computeOverflow());
  EQ(isLt.get(), computeLt());
}

template <typename C> FDEV void UnitLtBlock<C>::addArguments(CTX) DEV {
  UnitArgument<C> arg;
  arg.opts = Val<C>(uint32_t(UNIT_LT));
  arg.aLow = a.low.get();
  arg.aHigh = a.high.get();
  arg.bLow = b.low.get();
  arg.bHigh = b.high.get();
  arg.out0Low = isLt.get();
  arg.out0High = 0;
  arg.out1Low = Val<C>(1) - diff.carryHigh.get();
  arg.out1High = 0;
  ctx.addArgument(count.get(), arg);
  PICUS_INPUT(ctx, count);
  UNIT_BLOCK_INPUTS(ctx, arg);
}

template <typename C> FDEV void UnitShiftBlock<C>::set(CTX, UnitShiftWitness wit) DEV {
  count.set(ctx, wit.count);
  a.set(ctx, wit.a);
  b.set(ctx, wit.b);
  Option opts(wit.opts);
  opts.pop<UnitKind>();
  opt.set(ctx, opts.val);
  for (size_t i = 0; i < 8; i++) {
    bits[i].set(ctx, (wit.b >> i) & 1);
  }
  byte1.set(ctx, (wit.b >> 8) & 0xff);
  uint32_t po2_ = 1 << (wit.b & 31);
  bool negVal = opts.val == 2 && (wit.a >> 31);
  neg.set(ctx, negVal);
  uint32_t mna = negVal ? ~wit.a : wit.a;
  po2First3.set(ctx, 1 << (wit.b & 7));
  po2.set(ctx, po2_);
  signA.set(ctx, wit.a);
  maybeNegA.set(ctx, mna);
  if (opts.val == 0) {
    uint64_t mul = (uint64_t(mna) * uint64_t(po2_));
    maybeNegOut.set(ctx, mul & 0xffffffff);
    out.set(ctx, mul & 0xffffffff);
    out2.set(ctx, mul >> 32);
  } else {
    uint32_t quot = mna / po2_;
    maybeNegOut.set(ctx, quot);
    out.set(ctx, negVal ? ~quot : quot);
    out2.set(ctx, mna % po2_);
  }
}

template <typename C> FDEV void UnitShiftBlock<C>::verify(CTX) DEV {
  /*
  LOG(0, std::hex);
  LOG(0, "opt = " << opt.get());
  LOG(0, "a = " << a.high.get() << ":" << a.low.get());
  LOG(0, "b = " << b.high.get() << ":" << b.low.get());
  LOG(0, "signA = " << signA.get());
  LOG(0, std::dec);
  */
  Val<C> low = byte1.get() * 256;
  for (size_t i = 0; i < 8; i++) {
    low += bits[i].get() * (1 << i);
  }
  EQ(low, b.low.get());
  Val<C> po2_ = 1;
  po2_ *= cond<C>(bits[0].get(), 2, 1);
  po2_ *= cond<C>(bits[1].get(), 4, 1);
  po2_ *= cond<C>(bits[2].get(), 16, 1);
  EQ(po2_, po2First3.get());
  po2_ = po2First3.get();
  po2_ *= cond<C>(bits[3].get(), 256, 1);
  EQ(po2.low.get(), (Val<C>(1) - bits[4].get()) * po2_);
  EQ(po2.high.get(), bits[4].get() * po2_);
  EQ(neg.get(), opt.bits[2].get() * signA.get());
  EQ(maybeNegA.low.get(), cond<C>(neg.get(), Val<C>(0xffff) - a.low.get(), a.low.get()));
  EQ(maybeNegA.high.get(), cond<C>(neg.get(), Val<C>(0xffff) - a.high.get(), a.high.get()));
  EQ(maybeNegOut.low.get(), cond<C>(neg.get(), Val<C>(0xffff) - out.low.get(), out.low.get()));
  EQ(maybeNegOut.high.get(), cond<C>(neg.get(), Val<C>(0xffff) - out.high.get(), out.high.get()));
}

template <typename C> FDEV void UnitShiftBlock<C>::addArguments(CTX) DEV {
  // Produce division
  UnitArgument<C> arg;
  arg.opts = opt.get() * Val<C>(OptSize<UnitKind>::value) + Val<C>(uint32_t(UNIT_SHIFT));
  arg.aLow = a.low.get();
  arg.aHigh = a.high.get();
  arg.bLow = b.low.get();
  arg.bHigh = b.high.get();
  arg.out0Low = out.low.get();
  arg.out0High = out.high.get();
  arg.out1Low = 0;
  arg.out1High = 0;
  ctx.addArgument(count.get(), arg);
  PICUS_INPUT(ctx, count);
  UNIT_BLOCK_INPUTS(ctx, arg);

  // Require multiplication or division
  arg.opts =
      opt.bits[0].get() * Val<C>(uint32_t(MUL_UU) * OptSize<UnitKind>::value + uint32_t(UNIT_MUL)) +
      opt.bits[1].get() * Val<C>(uint32_t(DIV_U) * OptSize<UnitKind>::value + uint32_t(UNIT_DIV)) +
      opt.bits[2].get() * Val<C>(uint32_t(DIV_U) * OptSize<UnitKind>::value + uint32_t(UNIT_DIV));
  arg.aLow = maybeNegA.low.get();
  arg.aHigh = maybeNegA.high.get();
  arg.bLow = po2.low.get();
  arg.bHigh = po2.high.get();
  arg.out0Low = maybeNegOut.low.get();
  arg.out0High = maybeNegOut.high.get();
  arg.out1Low = out2.low.get();
  arg.out1High = out2.high.get();
  ctx.pull(arg);
  UNIT_ARGUMENT(ctx, arg);
}

#undef UNIT_BLOCK_INPUTS
#undef UNIT_ARGUMENT
