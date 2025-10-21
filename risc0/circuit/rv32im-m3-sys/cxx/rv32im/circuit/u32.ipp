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
// WITHOUT WARRANTIES OR condITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

template <typename C> FDEV void RegU32<C>::set(CTX, uint32_t val) DEV {
  low.set(ctx, val & 0xffff);
  high.set(ctx, val >> 16);
}

template <typename C> FDEV ValU32<C> RegU32<C>::get() DEV {
  return ValU32<C>(low.get(), high.get());
}

template <typename C> FDEV void AddU32<C>::set(CTX, uint32_t a, uint32_t b, bool carryIn) DEV {
  uint32_t low17 = (a & 0xffff) + (b & 0xffff) + carryIn;
  low.set(ctx, low17 & 0xffff);
  carryLow.set(ctx, low17 >> 16);
  uint32_t high17 = (a >> 16) + (b >> 16) + (low17 >> 16);
  high.set(ctx, high17 & 0xffff);
  carryHigh.set(ctx, high17 >> 16);
}

template <typename C> FDEV ValU32<C> AddU32<C>::get() DEV {
  return ValU32<C>(low.get(), high.get());
}

template <typename C> FDEV void AddU32<C>::verify(CTX, ValU32<C> a, ValU32<C> b) DEV {
  EQ(low.get() + carryLow.get() * 0x10000, a.low + b.low);
  EQ(high.get() + carryHigh.get() * 0x10000, a.high + b.high + carryLow.get());
}

template <typename C> FDEV void AddressDecompose<C>::set(CTX, uint32_t val) DEV {
  mid14.set(ctx, (val & 0xffff) >> 2);
  low0.set(ctx, val & 1);
  low1.set(ctx, (val >> 1) & 1);
}

template <typename C> FDEV Val<C> AddressDecompose<C>::wordAddr(ValU32<C> val) DEV {
  return val.high * 0x4000 + mid14.get();
}

template <typename C> FDEV void AddressDecompose<C>::verify(CTX, ValU32<C> val) DEV {
  EQ(mid14.get() * 4 + low1.get() * 2 + low0.get(), val.low);
}

template <typename C> FDEV void AddressVerify<C>::set(CTX, uint32_t val, uint32_t mode) DEV {
  isMM.set(ctx, mode == MODE_MACHINE);
  uint32_t max = (mode == MODE_MACHINE ? 0xffff : (GLOBAL_GET(v2Compat) != 0 ? 0xbfff : 0xefff));
  highSub.set(ctx, max - (val >> 16));
}

template <typename C> FDEV void AddressVerify<C>::verify(CTX, ValU32<C> val, Val<C> mode) DEV {
  Val<C> topAddr = cond<C>(isMM.get(), 0xffff,
                   cond<C>(GLOBAL_GET(v2Compat), Val<C>(0xbfff), Val<C>(0xefff)));
  EQZ(isMM.get() * (mode - Val<C>(MODE_MACHINE)));
  EQ(topAddr - val.high, highSub.get());
}

template <typename C> FDEV void GetSign<C>::set(CTX, uint32_t val) DEV {
  sign.set(ctx, val >> 31);
  signVerify.set(ctx, (val & 0x7fff0000) >> 15);
}

template <typename C> FDEV void GetSign<C>::verify(CTX, Val<C> inHigh) DEV {
  EQ(inHigh, signVerify.get() * inv(Fp(2)) + sign.get() * 0x8000);
}

template <typename C> FDEV void NegU32<C>::set(CTX, uint32_t val, uint32_t neg) DEV {
  if (neg) {
    uint32_t lowSum = 0xffff - (val & 0xffff) + 1;
    outLow.set(ctx, lowSum & 0xffff);
    carryLow.set(ctx, lowSum >> 16);
    uint32_t highSum = 0xffff - (val >> 16) + (lowSum >> 16);
    outHigh.set(ctx, highSum & 0xffff);
    carryHigh.set(ctx, highSum >> 16);
  } else {
    outLow.set(ctx, val & 0xffff);
    carryLow.set(ctx, 0);
    outHigh.set(ctx, val >> 16);
    carryHigh.set(ctx, 0);
  }
}

template <typename C> FDEV ValU32<C> NegU32<C>::get() DEV {
  return ValU32<C>(outLow.get(), outHigh.get());
}

template <typename C> FDEV void NegU32<C>::verify(CTX, ValU32<C> in, Val<C> neg) DEV {
  EQZ(neg * (Val<C>(0xffff) - in.low + 1 - Val<C>(0x10000) * carryLow.get() - outLow.get()) +
      (Val<C>(1) - neg) * (outLow.get() - in.low));
  EQZ(neg * (Val<C>(0xffff) - in.high + carryLow.get() - Val<C>(0x10000) * carryHigh.get() -
             outHigh.get()) +
      (Val<C>(1) - neg) * (outHigh.get() - in.high));
}

template <typename C> FDEV void AbsU32<C>::set(CTX, uint32_t val, uint32_t isSigned) DEV {
  bool negVal = ((val & 0x80000000) && isSigned);
  in.set(ctx, val);
  neg.set(ctx, uint32_t(negVal));
  sign.set(ctx, (val >> 31));
  signVerify.set(ctx, ((val >> 16) & 0x7fff) << 1);
  if (negVal) {
    uint32_t lowSum = 0xffff - (val & 0xffff) + 1;
    absLow.set(ctx, lowSum & 0xffff);
    carryLow.set(ctx, lowSum >> 16);
    uint32_t highSum = 0xffff - (val >> 16) + (lowSum >> 16);
    absHigh.set(ctx, highSum & 0xffff);
    carryHigh.set(ctx, highSum >> 16);
  } else {
    absLow.set(ctx, val & 0xffff);
    carryLow.set(ctx, 0);
    absHigh.set(ctx, val >> 16);
    carryHigh.set(ctx, 0);
  }
}

template <typename C> FDEV ValU32<C> AbsU32<C>::getIn() DEV {
  return in.get();
}

template <typename C> FDEV ValU32<C> AbsU32<C>::getAbs() DEV {
  return ValU32<C>(absLow.get(), absHigh.get());
}

template <typename C> FDEV void AbsU32<C>::verify(CTX, Val<C> isSigned) DEV {
  EQ(signVerify.get() * inv(Fp(2)) + sign.get() * Val<C>(0x8000), in.high.get());
  EQ(neg.get(), sign.get() * isSigned);
  EQZ(neg.get() *
          (Val<C>(0xffff) - in.low.get() + 1 - Val<C>(0x10000) * carryLow.get() - absLow.get()) +
      (Val<C>(1) - neg.get()) * (absLow.get() - in.low.get()));
  EQZ(neg.get() * (Val<C>(0xffff) - in.high.get() + carryLow.get() -
                   Val<C>(0x10000) * carryHigh.get() - absHigh.get()) +
      (Val<C>(1) - neg.get()) * (absHigh.get() - in.high.get()));
}
