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

#define CPU

#include "risc0/core/log.h"
#include "risc0/zkp/accel/accel.h"
#include "risc0/zkp/accel/pp.h"
#include "risc0/zkp/core/constants.h"
#include "risc0/zkp/core/fp4.h"
#include "risc0/zkp/core/ntt.h"
#include "risc0/zkp/core/sha256.h"

#ifdef USE_TBB

#include "oneapi/tbb/parallel_for.h"

#define PARALLEL_FOR(start_, count_, body_) oneapi::tbb::parallel_for<size_t>(start_, count_, body_)

#else

#define PARALLEL_FOR(start_, count_, body_)                                                        \
  for (size_t i = start_; i < count_; i++)                                                         \
  body_(i)

#endif

namespace risc0 {

void cpuInit() {
  static bool done = false;
  if (!done) {
    LOG(1, "Opening CPU");
    done = true;
  }
}

void accelStartup() {
  cpuInit();
}

struct AccelBufImpl {
  uint8_t* buf;
};

AccelBufImpl* accelAllocBuf(size_t size) {
  cpuInit();
  AccelBufImpl* impl = new AccelBufImpl();
  impl->buf = new uint8_t[size];
  return impl;
}

void accelFreeBuf(AccelBufImpl* impl) {
  delete[] impl->buf;
  delete impl;
}

void* accelGetContents(AccelBufImpl* impl, size_t offset, size_t size, bool sync) {
  return impl->buf + offset;
}

void* accelDevicePtr(AccelBufImpl* impl, size_t offset) {
  return impl->buf + offset;
}

void accelIsDirty(AccelBufImpl* impl, size_t offset, size_t size) {
  // Do nothing
}

void accelBeginProfile() {
  // TODO
}

void accelEndProfile() {
  // TODO
}

void batchEvaluateNTT(AccelSlice<Fp> io, size_t count, size_t expandBits) {
  size_t rowSize = io.size() / count;
  REQUIRE(rowSize * count == io.size());
  Fp* ioPtr = reinterpret_cast<Fp*>(io.buf()->buf);
  PARALLEL_FOR(0, count, [&](size_t i) { evaluateNTT(ioPtr + i * rowSize, rowSize, expandBits); });
}

void batchInterpolateNTT(AccelSlice<Fp> io, size_t count) {
  size_t rowSize = io.size() / count;
  REQUIRE(rowSize * count == io.size());
  Fp* ioPtr = reinterpret_cast<Fp*>(io.buf()->buf);
  PARALLEL_FOR(0, count, [&](size_t i) { interpolateNTT(ioPtr + i * rowSize, rowSize); });
}

void batchExpand(AccelSlice<Fp> out, AccelConstSlice<Fp> in, size_t count) {
  size_t outSize = out.size() / count;
  size_t inSize = in.size() / count;
  size_t expandBits = log2Ceil(outSize / inSize);
  REQUIRE(outSize == inSize * (1 << expandBits));
  REQUIRE(outSize * count == out.size());
  REQUIRE(inSize * count == in.size());
  Fp* outPtr = reinterpret_cast<Fp*>(out.buf()->buf);
  Fp* inPtr = reinterpret_cast<Fp*>(in.buf()->buf);
  PARALLEL_FOR(0, count, [&](size_t i) {
    expand(outPtr + i * outSize, inPtr + i * inSize, inSize, expandBits);
  });
}

void batchBitReverse(AccelSlice<Fp> io, size_t count) {
  size_t rowSize = io.size() / count;
  REQUIRE(rowSize * count == io.size());
  Fp* ioPtr = reinterpret_cast<Fp*>(io.buf()->buf);
  PARALLEL_FOR(0, count, [&](size_t i) { bitReverse(ioPtr + i * rowSize, rowSize); });
}

void batchEvaluateAny(AccelConstSlice<Fp> coeffs,
                      size_t polyCount,
                      AccelConstSlice<uint32_t> which,
                      AccelConstSlice<Fp4> xs,
                      AccelSlice<Fp4> out) {
  size_t po2 = log2Ceil(coeffs.size() / polyCount);
  REQUIRE(polyCount * (1 << po2) == coeffs.size());
  size_t evalCount = which.size();
  REQUIRE(xs.size() == evalCount);
  REQUIRE(out.size() == evalCount);
  const Fp* coeffsPtr = reinterpret_cast<const Fp*>(coeffs.buf()->buf);
  Fp4* outPtr = reinterpret_cast<Fp4*>(out.buf()->buf);
  PARALLEL_FOR(0, evalCount, [&](size_t i) {
    Fp4 tot;
    Fp4 cur(1, 0, 0, 0);
    size_t id = reinterpret_cast<const uint32_t*>(which.buf()->buf)[i];
    Fp4 x = reinterpret_cast<const Fp4*>(xs.buf()->buf)[i];
    const Fp* coeffLocal = coeffsPtr + (1 << po2) * id;
    for (size_t i = 0; i < (static_cast<size_t>(1) << po2); i++) {
      tot += cur * coeffLocal[i];
      cur *= x;
    }
    outPtr[i] = tot;
  });
}

#define DECL_PTR(type, name) AccelSlice<type> name,
#define DECL_CPTR(type, name) AccelConstSlice<type> name,
#define DECL_SIZE(name) size_t name,
#define DECL_CALC(name, expr) /**/
#define DECL_REQ(expr)        /**/
#define PRE_PTR(a, b)         /**/
#define PRE_CPTR(a, b)        /**/
#define PRE_SIZE(name)        /**/
#define PRE_CALC(name, expr) size_t name = (expr);
#define PRE_REQ(expr)                                                                              \
  if (!(expr)) {                                                                                   \
    throw std::runtime_error(#expr);                                                               \
  }
#define POST_PTR(a, b)                                                                             \
  a* b##Tmp = reinterpret_cast<a*>(b.buf()->buf + b.offset() * sizeof(a));                         \
  a* b = b##Tmp;
#define POST_CPTR(a, b)                                                                            \
  const a* b##Tmp = reinterpret_cast<const a*>(b.buf()->buf + b.offset() * sizeof(a));             \
  const a* b = b##Tmp;
#define POST_SIZE(name)       /**/
#define POST_CALC(name, expr) /**/
#define POST_REQ(expr)        /**/
#define DECL_MAP(arg) PP_PASTE(DECL, PP_PASTE(_, arg))
#define PRE_MAP(arg) PP_PASTE(PRE, PP_PASTE(_, arg))
#define POST_MAP(arg) PP_PASTE(POST, PP_PASTE(_, arg))

#define PARALLEL_KERNEL(name, lst, impl)                                                           \
  void name##Accel(PP_APPLY_LST(DECL_MAP, lst) bool ignore) {                                      \
    cpuInit();                                                                                     \
    PP_APPLY_LST(PRE_MAP, lst) {                                                                   \
      PP_APPLY_LST(POST_MAP, lst)                                                                  \
      PARALLEL_FOR(0, count, [&](size_t idx) impl);                                                \
    }                                                                                              \
  }

static inline uint32_t accel_rev32(uint32_t x) {
  return bitReverse(x);
}

#include "risc0/zkp/accel/kernels/all.h"

} // namespace risc0
