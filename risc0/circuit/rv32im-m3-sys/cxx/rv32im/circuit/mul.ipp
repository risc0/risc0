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

template <typename C> FDEV void ExpandU32<C>::set(CTX, uint32_t val) DEV {
  b0.set(ctx, val & 0xff);
  b1.set(ctx, (val >> 8) & 0xff);
  b2.set(ctx, (val >> 16) & 0xff);
  b3.set(ctx, (val >> 24) & 0xff);
  topBit.set(ctx, val >> 31);
  b3Low7times2.set(ctx, ((val >> 24) & 0x7f) << 1);
}

template <typename C> FDEV ValU32<C> ExpandU32<C>::get() DEV {
  return ValU32<C>(b0.get() + b1.get() * 256, b2.get() + b3.get() * 256);
}

template <typename C> FDEV void ExpandU32<C>::verify(CTX) DEV {
  EQ(b3.get(), topBit.get() * 128 + b3Low7times2.get() * inv(Fp(2)));
}

template <typename C> FDEV void SplitTotal<C>::set(CTX, uint32_t val) DEV {
  out.set(ctx, val & 0xffff);
  carryByte.set(ctx, (val >> 16) & 0xff);
  carryBit0.set(ctx, (val >> 24) & 1);
  carryBit1.set(ctx, (val >> 25) & 1);
}

template <typename C> FDEV Val<C> SplitTotal<C>::carry() DEV {
  return carryByte.get() + carryBit0.get() * 0x100 + carryBit1.get() * 0x200;
}

template <typename C> FDEV void SplitTotal<C>::verify(CTX, Val<C> val) DEV {
  EQ(val,
     out.get() + carryByte.get() * 0x10000 + carryBit0.get() * 0x1000000 +
         carryBit1.get() * 0x2000000);
}

template <typename C>
FDEV void Multiply<C>::set(CTX, uint32_t a, uint32_t b, uint32_t signA_, uint32_t signB_) DEV {
  ax.set(ctx, a);
  bx.set(ctx, b);
  signA.set(ctx, signA_);
  signB.set(ctx, signB_);
  Val<C> s0Val = valS0();
  s0.set(ctx, asUInt32(s0Val));
  Val<C> s1Val = valS1();
  s1.set(ctx, asUInt32(s1Val));
  Val<C> s2Val = valS2();
  s2.set(ctx, asUInt32(s2Val));
  Val<C> s3Val = valS3();
  s3Out.set(ctx, asUInt32(s3Val) & 0xffff);
  s3Carry.set(ctx, asUInt32(s3Val) >> 16);
}

template <typename C> FDEV ValU32<C> Multiply<C>::getA() DEV {
  return ax.get();
}

template <typename C> FDEV ValU32<C> Multiply<C>::getB() DEV {
  return bx.get();
}

template <typename C> FDEV ValU32<C> Multiply<C>::getOutLow() DEV {
  return ValU32<C>(s0.out.get(), s1.out.get());
}

template <typename C> FDEV ValU32<C> Multiply<C>::getOutHigh() DEV {
  return ValU32<C>(s2.out.get(), s3Out.get());
}

template <typename C> FDEV void Multiply<C>::verify(CTX) DEV {
  EQ(s3Out.get() + Val<C>(0x10000) * s3Carry.get(), valS3());
}

template <typename C> FDEV Val<C> Multiply<C>::valS0() DEV {
  return ax.b0.get() * bx.b0.get() +
         Val<C>(0x100) * (ax.b0.get() * bx.b1.get() + ax.b1.get() * bx.b0.get());
}

template <typename C> FDEV Val<C> Multiply<C>::valS1() DEV {
  return s0.carry() + ax.b0.get() * bx.b2.get() + ax.b1.get() * bx.b1.get() +
         ax.b2.get() * bx.b0.get() +
         Val<C>(0x100) * (ax.b0.get() * bx.b3.get() + ax.b1.get() * bx.b2.get() +
                          ax.b2.get() * bx.b1.get() + ax.b3.get() * bx.b0.get());
}

template <typename C> FDEV Val<C> Multiply<C>::valS2() DEV {
  Val<C> aNeg = signA.get() * ax.topBit.get();
  Val<C> bNeg = signB.get() * bx.topBit.get();
  return s1.carry() + Val<C>(0x20000) - (ax.b0.get() + ax.b1.get() * Val<C>(0x100)) * bNeg -
         (bx.b0.get() + bx.b1.get() * Val<C>(0x100)) * aNeg + ax.b1.get() * bx.b3.get() +
         ax.b2.get() * bx.b2.get() + ax.b3.get() * bx.b1.get() +
         Val<C>(0x100) * (ax.b2.get() * bx.b3.get() + ax.b3.get() * bx.b2.get());
}

template <typename C> FDEV Val<C> Multiply<C>::valS3() DEV {
  Val<C> aNeg = signA.get() * ax.topBit.get();
  Val<C> bNeg = signB.get() * bx.topBit.get();
  return s2.carry() + Val<C>(0x1fffe) - (ax.b2.get() + ax.b3.get() * Val<C>(0x100)) * bNeg -
         (bx.b2.get() + bx.b3.get() * Val<C>(0x100)) * aNeg + ax.b3.get() * bx.b3.get();
}
