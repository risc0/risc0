// Copyright 2022 Risc0, Inc.
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

#include "risc0/zkp/core/ntt.h"

#include "risc0/core/util.h"
#include "risc0/zkp/core/rou.h"

namespace risc0 {

namespace {

// Basically we use a radix-2 Cooley–Tukey algorithm.  We have some special casing for when the
// input size is bigger than the output size for the evaluation case (basically for Reed-Solomon).
// We do a bit-reversal/butterfly for the simple case.
//
// Annoyningly, since we want to do interpolation followed by evaluation without doing any bit
// reversals, we need to support both decimation in time and decimation in freqency based the
// direction.
//
// Thsese are the primary recurvsive implementations.  Here T is the datatype (presumed to support
// add, sub and mul), (1 << N) is the size of the buffer, (1 << L) is the expansion size.
// Basically, L just causes an early termination, since we 'precompute' the constant evaluations.

template <typename T, size_t N, size_t L> struct FwdNTTButterfly {
  static void run(T* io) {
    if (N == L) {
      return;
    }
    constexpr size_t half = 1 << (N - 1);
    FwdNTTButterfly<T, N - 1, L>::run(io);
    FwdNTTButterfly<T, N - 1, L>::run(io + half);
    Fp step = kRouFwd[N];
    Fp cur = 1;
    for (size_t i = 0; i < half; i++) {
      T a = io[i];
      T b = io[i + half] * cur;
      io[i] = a + b;
      io[i + half] = a - b;
      cur *= step;
    }
  }
};

// Termination case is a NOP
template <typename T, size_t L> struct FwdNTTButterfly<T, 0, L> {
  static void run(T* io) {}
};

template <typename T, size_t N> struct RevNTTButterfly {
  static void run(T* io) {
    constexpr size_t half = 1 << (N - 1);
    Fp step = kRouRev[N];
    Fp cur = 1;
    for (size_t i = 0; i < half; i++) {
      T a = io[i];
      T b = io[i + half];
      io[i] = a + b;
      io[i + half] = (a - b) * cur;
      cur *= step;
    }
    RevNTTButterfly<T, N - 1>::run(io);
    RevNTTButterfly<T, N - 1>::run(io + half);
  }
};

// Termination case is a NOP
template <typename T> struct RevNTTButterfly<T, 0> {
  static void run(T* io) {}
};

// Wrap all the steps
template <typename T, size_t N, size_t L, bool Rev> void wrapNTT(T* io) {
  size_t size = 1 << N;
  if (Rev) {
    RevNTTButterfly<T, N>::run(io);
    Fp norm = inv(Fp(size));
    for (size_t i = 0; i < size; i++) {
      io[i] *= norm;
    }
  } else {
    FwdNTTButterfly<T, N, L>::run(io);
  }
}

// Now handle the two levels of runtime switches
template <typename T, size_t N, bool Rev> void runtimeL(T* io, size_t L) {
  REQUIRE(L <= 2);
  if (Rev) {
    REQUIRE(L == 0);
  }
#define DO_CASE(x)                                                                                 \
  case x:                                                                                          \
    wrapNTT<T, N, x, Rev>(io);                                                                     \
    break;
  switch (L) {
    DO_CASE(0)
    DO_CASE(1)
    DO_CASE(2)
  }
#undef DO_CASE
}

template <typename T, bool Rev> void runtimeN(T* io, size_t N, size_t L) {
  REQUIRE(N <= 27);
#define DO_CASE(x)                                                                                 \
  case x:                                                                                          \
    runtimeL<T, x, Rev>(io, L);                                                                    \
    break;
  switch (N) {
    DO_CASE(0)
    DO_CASE(1)
    DO_CASE(2)
    DO_CASE(3)
    DO_CASE(4)
    DO_CASE(5)
    DO_CASE(6)
    DO_CASE(7)
    DO_CASE(8)
    DO_CASE(9)
    DO_CASE(10)
    DO_CASE(11)
    DO_CASE(12)
    DO_CASE(13)
    DO_CASE(14)
    DO_CASE(15)
    DO_CASE(16)
    DO_CASE(17)
    DO_CASE(18)
    DO_CASE(19)
    DO_CASE(20)
    DO_CASE(21)
    DO_CASE(22)
    DO_CASE(23)
    DO_CASE(24)
    DO_CASE(25)
    DO_CASE(26)
    DO_CASE(27)
  }
#undef DO_CASE
}

template <typename T, bool Rev> void doNTT(T* io, size_t size, size_t bitExpand) {
  size_t N = log2Ceil(size);
  REQUIRE((size_t(1) << N) == size);
  runtimeN<T, Rev>(io, N, bitExpand);
}

// An in place bit reversal routine
template <typename T> void bitRevImpl(T* io, size_t size) {
  size_t N = log2Ceil(size);
  REQUIRE((size_t(1) << N) == size);
  for (size_t i = 0; i < size; i++) {
    size_t revIdx = bitReverse(i) >> (32 - N);
    if (i < revIdx) {
      std::swap(io[i], io[revIdx]);
    }
  }
}

template <typename T> void doExpand(T* out, const T* in, size_t sizeIn, size_t expandBits) {
  size_t sizeOut = sizeIn * (1 << expandBits);
  for (size_t i = 0; i < sizeOut; i++) {
    out[i] = in[i >> expandBits];
  }
}

} // namespace

void interpolateNTT(Fp* io, size_t size) {
  doNTT<Fp, true>(io, size, 0);
}

void interpolateNTT(Fp4* io, size_t size) {
  doNTT<Fp4, true>(io, size, 0);
}

void evaluateNTT(Fp* io, size_t size, size_t expandBits) {
  doNTT<Fp, false>(io, size, expandBits);
}

void evaluateNTT(Fp4* io, size_t size, size_t expandBits) {
  doNTT<Fp4, false>(io, size, expandBits);
}

void bitReverse(Fp* io, size_t size) {
  return bitRevImpl<Fp>(io, size);
}

void bitReverse(Fp4* io, size_t size) {
  return bitRevImpl<Fp4>(io, size);
}

void expand(Fp* out, const Fp* in, size_t sizeIn, size_t expandBits) {
  doExpand(out, in, sizeIn, expandBits);
}

void expand(Fp4* out, const Fp4* in, size_t sizeIn, size_t expandBits) {
  doExpand(out, in, sizeIn, expandBits);
}

} // namespace risc0
