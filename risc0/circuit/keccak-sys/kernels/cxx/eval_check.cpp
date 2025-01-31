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

#include "buffers.h"
#include "fp.h"
#include "fpext.h"

#include <array>
#include <cassert>
#include <cstdint>
#include <cstdio>
#include <exception>
#include <mutex>
#include <string.h>

using namespace risc0;

namespace {

constexpr bool kDebug = false;
using BCPtr = const uint8_t*;

constexpr size_t kInvRate = 4;

struct EncodedProg {
  const uint32_t* curPos = nullptr;

  uint32_t decode() { return *curPos++; }
};

template <typename T> T tempLoad(Fp* buf, size_t offset);

template <> Fp tempLoad<Fp>(Fp* buf, size_t offset) {
  return buf[offset];
}

template <> FpExt tempLoad<FpExt>(Fp* buf, size_t offset) {
  return FpExt(buf[offset], buf[offset + 1], buf[offset + 2], buf[offset + 3]);
}

template <typename T> void tempStore(Fp* buf, size_t offset, T val);

template <> void tempStore<Fp>(Fp* buf, size_t offset, Fp val) {
  buf[offset] = val;
}
template <> void tempStore<FpExt>(Fp* buf, size_t offset, FpExt val) {
  buf[offset] = val.elems[0];
  buf[offset + 1] = val.elems[1];
  buf[offset + 2] = val.elems[2];
  buf[offset + 3] = val.elems[3];
}

template <typename ConcreteType> struct EncodedProgBase : public EncodedProg {
};

void printDebug(const char* label, Fp fpVal) {
  printf(" %3s:  %u\n", label, fpVal.asUInt32());
}

void printDebug(const char* label, FpExt extVal) {
  uint32_t a = extVal.elems[0].asUInt32();
  uint32_t b = extVal.elems[1].asUInt32();
  uint32_t c = extVal.elems[2].asUInt32();
  uint32_t d = extVal.elems[3].asUInt32();
  printf(" %3s:  [%u, %u, %u, %u]\n", label, a, b, c, d);
}

template <typename T> T debugIn(T val) {
  if (kDebug) {
    printDebug("in", val);
  }
  return val;
}
template <typename T> void debugOut(T val) {
  printDebug("out", val);
}

namespace impl {

using MutableBuf = Fp*;
using GlobalBuf = Fp*;
using GlobalExtBuf = FpExt*;
using ExtVal = FpExt;
using Val = Fp;
using Index = size_t;
using MixState = FpExt;

inline constexpr size_t getBackOrZero() { return 0; }
inline constexpr size_t getBackOrZero(size_t back) { return back; }

#define zllGet(BUF, OFFSET, BACK...) ((BUF)[(OFFSET) * steps + ((cycle - kInvRate * (getBackOrZero(BACK))) & mask)]);
#define zllGetGlobal(BUF, OFFSET) ((BUF)[(OFFSET)])
#define zllAndEqz(IN, VAL, MIX_POW) zllAndEqzImpl(IN, VAL, MIX_POW, polyMix)
#define zllAndCond(IN, COND, INNER, MIX_POW) zllAndCondImpl(IN, COND, INNER, MIX_POW, polyMix)

Fp zllConst(size_t a) {
  return Fp(a);
}

FpExt zllConst(size_t a, size_t b, size_t c, size_t d) {
  return FpExt(a, b, c, d);
}

FpExt trivialConstraint() {
  return FpExt(0, 0, 0, 0);
}

FpExt zllAndEqzImpl(FpExt inMix, Fp val, size_t mixPowIndex, const FpExt* polyMix) {
  return inMix + val * polyMix[mixPowIndex];
}

FpExt zllAndEqzImpl(FpExt inMix, FpExt val, size_t mixPowIndex, const FpExt* polyMix) {
  return inMix + val * polyMix[mixPowIndex];
}

FpExt zllAndCondImpl(
    FpExt inMix, Fp cond, FpExt innerMix, size_t mixPowIndex, const FpExt* polyMix) {
  return inMix + cond * innerMix * polyMix[mixPowIndex];
}

FpExt zllAndCondImpl(
    FpExt inMix, FpExt cond, FpExt innerMix, size_t mixPowIndex, const FpExt* polyMix) {
  return inMix + cond * innerMix * polyMix[mixPowIndex];
}

#include "poly_fp_bc.cpp.inc"

} // namespace impl

} // namespace

extern "C" const char* risc0_circuit_keccak_cpu_poly_fp(
    size_t cycle, size_t steps, FpExt* poly_mix, Fp** args, FpExt* result) {
  try {
    Fp* data = args[0];
    Fp* out = args[1];
    *result = impl::execByteCode<impl::Keccak>(cycle, steps, data, out, poly_mix);
  } catch (const std::exception& err) {
    return strdup(err.what());
  }
  return nullptr;
}
