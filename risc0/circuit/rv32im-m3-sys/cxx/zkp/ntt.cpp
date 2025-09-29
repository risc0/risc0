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

#include "zkp/ntt.h"
#include "zkp/rou.h"
#include "core/util.h"

#include <assert.h>

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
    Fp step = ROU_FWD[N];
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

template <typename T, size_t N, size_t L> struct RevNTTButterfly {
  static void run(T* io) {
    if (N == L) {
      return;
    }
    constexpr size_t half = 1 << (N - 1);
    Fp step = ROU_REV[N];
    Fp cur = 1;
    for (size_t i = 0; i < half; i++) {
      T a = io[i];
      T b = io[i + half];
      io[i] = a + b;
      io[i + half] = (a - b) * cur;
      cur *= step;
    }
    RevNTTButterfly<T, N - 1, L>::run(io);
    RevNTTButterfly<T, N - 1, L>::run(io + half);
  }
};

// Termination case is a NOP
template <typename T, size_t L> struct RevNTTButterfly<T, 0, L> {
  static void run(T* io) {}
};

// An in place bit reversal routine
template <typename T, size_t N> void bitRevImpl(T* io) {
  if (N == 0) {
    return;
  }
  size_t size = 1 << N;
  for (size_t i = 0; i < size; i++) {
    size_t shift = (N >= 32) ? 0 : (32 - N);
    size_t revIdx = bitReverse(i) >> shift;
    if (i < revIdx) {
      std::swap(io[i], io[revIdx]);
    }
  }
}

// Wrap all the steps
template <typename T, size_t N, size_t L, bool Rev> void wrapNTT(T* io, bool doBitRev) {
  size_t size = 1 << N;
  if (Rev) {
    RevNTTButterfly<T, N, L>::run(io);
    if (doBitRev) {
      bitRevImpl<T, N>(io);
    }
    Fp norm = inv(Fp(size));
    for (size_t i = 0; i < size; i++) {
      io[i] *= norm;
    }
  } else {
    if (doBitRev) {
      bitRevImpl<T, N>(io);
    }
    FwdNTTButterfly<T, N, L>::run(io);
  }
}

// Now handle the two levels of runtime switches
template <typename T, size_t N, bool Rev> void runtimeL(T* io, size_t L, bool doBitRev) {
  assert(L <= 2);
#define DO_CASE(x)                                                                                 \
  case x:                                                                                          \
    wrapNTT<T, N, x, Rev>(io, doBitRev);                                                           \
    break;
  switch (L) {
    DO_CASE(0)
    DO_CASE(1)
    DO_CASE(2)
  }
#undef DO_CASE
}

template <typename T, bool Rev> void runtimeN(T* io, size_t N, size_t L, bool doBitRev) {
  assert(N <= 27);
#define DO_CASE(x)                                                                                 \
  case x:                                                                                          \
    runtimeL<T, x, Rev>(io, L, doBitRev);                                                          \
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

template <typename T, bool Rev> void parallelNTT(T* io, size_t size, size_t count, bool doBitRev=true) {
  size_t N = log2Ceil(size);
  assert((size_t(1) << N) == size);
  // TODO: parallel
  for (size_t i = 0; i < count; i++) {
    runtimeN<T, Rev>(io + size * i, N, 0, doBitRev);
  }
}

template <typename T> void parallelExpand(T* io, size_t sizeIn, size_t sizeOut, size_t count) {
  size_t N = log2Ceil(sizeOut);
  assert((size_t(1) << N) == sizeOut);
  size_t L = log2Ceil(sizeOut / sizeIn);
  assert((size_t(1) << (N - L)) == sizeIn);
  // TODO: parallel
  for (size_t i = 0; i < count; i++) {
    runtimeN<T, true>(io + sizeOut * i, N - L, 0, false);
    for (size_t j = sizeIn; j-- > 0;) {
      for (size_t k = 0; k < (size_t(1) << L); k++) {
        io[i * sizeOut + j * (size_t(1) << L) + k] = io[i * sizeOut + j];
      }
    }
    runtimeN<T, false>(io + sizeOut * i, N, L, false);
  }
}

} // namespace

void multiBitReverse(Fp* io, size_t size, size_t count) {
  size_t N = log2Ceil(size);
  if (size_t(1) << N != size) {
    throw std::runtime_error("Invalid bit reversal");
  }
  // TODO: parallel
  for(size_t i = 0; i < count; i++) {
    for (size_t j = 0; j < size; j++) {
      size_t revIdx = bitReverse(j) >> (32 - N);
      if (j < revIdx) {
        std::swap(io[i*size + j], io[i*size + revIdx]);
      }
    }
  }
}

void multiBitReverse(FpExt* io, size_t size, size_t count) {
  size_t N = log2Ceil(size);
  if (size_t(1) << N != size) {
    throw std::runtime_error("Invalid bit reversal");
  }
  // This is only used for FRI, so count == 16
  for(size_t i = 0; i < count; i++) {
    for (size_t j = 0; j < size; j++) {
      size_t revIdx = bitReverse(j) >> (32 - N);
      if (j < revIdx) {
        std::swap(io[i*size + j], io[i*size + revIdx]);
      }
    }
  }
}

void multiEvaluate(Fp* io, size_t size, size_t count) {
  parallelNTT<Fp, false>(io, size, count, false);
}
void multiEvaluate(FpExt* io, size_t size, size_t count) {
  parallelNTT<FpExt, false>(io, size, count, false);
}
void multiInterpolate(Fp* io, size_t size, size_t count) {
  parallelNTT<Fp, true>(io, size, count, false);
}
void multiInterpolate(FpExt* io, size_t size, size_t count) {
  parallelNTT<FpExt, true>(io, size, count, false);
}
void multiExpand(Fp* io, size_t sizeIn, size_t sizeOut, size_t count) {
  parallelExpand<Fp>(io, sizeIn, sizeOut, count);
}
void multiShift(Fp* io, size_t size, size_t count) {
  size_t N = log2Ceil(size);
  if (size_t(1) << N != size) {
    throw std::runtime_error("Invalid shift");
  }
  for (size_t j = 0; j < size; j++) {
    size_t revIdx = bitReverse(j) >> (32 - N);
    Fp mul = pow(Fp(3), revIdx);
    for (size_t i = 0; i < count; i++) {
      io[i*size + j] *= mul;
    }
  }
}

} // namespace byz
