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

#include "buffers.h"
#include "fp.h"
#include "fpext.h"
#include "preflight.h"
#include "tables.h"

#include <cassert>
#include <cuda/std/array>

namespace risc0::circuit::rv32im_v2::cuda {

#if defined(__clang__)
#pragma clang diagnostic ignored "-Wunused-parameter"
#pragma clang diagnostic ignored "-Wunused-variable"
#elif defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

using Val = Fp;
using ExtVal = FpExt;

struct ExecContext {
  __device__ ExecContext(PreflightTrace& preflight, LookupTables& tables, size_t cycle)
      : preflight(preflight), tables(tables), cycle(cycle) {}
  PreflightTrace& preflight;
  LookupTables& tables;
  size_t cycle;
};

struct BufferObj {
  __device__ virtual Val load(ExecContext& ctx, size_t col, size_t back) = 0;
  __device__ virtual void store(ExecContext& ctx, size_t col, Val val) = 0;
};

struct MutableBufObj : public BufferObj {
  __device__ MutableBufObj(Buffer& buf, size_t zeroBack = 0) : buf(buf), zeroBack(zeroBack) {}

  __device__ Val load(ExecContext& ctx, size_t col, size_t back) override {
    if (zeroBack && col > zeroBack && back > 0) {
      return 0;
    }
    size_t backRow = (buf.rows + ctx.cycle - back) % buf.rows;
    return buf.get(backRow, col);
  }

  __device__ void store(ExecContext& ctx, size_t col, Val val) override {
    return buf.set(ctx.cycle, col, val);
  }

  Buffer& buf;
  size_t zeroBack;
};

using MutableBuf = MutableBufObj*;

struct GlobalBufObj : public BufferObj {
  __device__ GlobalBufObj(Buffer& buf) : buf(buf) {}

  __device__ Val load(ExecContext& ctx, size_t col, size_t back) override {
    assert(back == 0);
    return buf.get(0, col);
  }

  __device__ void store(ExecContext& ctx, size_t col, Val val) override {
    return buf.set(0, col, val);
  }

  Buffer& buf;
};

using GlobalBuf = GlobalBufObj*;

template <typename T> struct BoundLayout {
  __device__ BoundLayout(const T& layout, BufferObj* buf) : layout(layout), buf(buf) {}

  const T& layout;
  BufferObj* buf = nullptr;
};

__device__ inline size_t to_size_t(Val v) {
  return v.asUInt32();
}

__device__ inline Val mod(Val a, Val b) {
  return Val(a.asUInt32() % b.asUInt32());
}

constexpr size_t EXT_SIZE = 4;

// Built in field operations
__device__ inline Val isz(Val x) {
  return Val(x == Val(0));
}

__device__ inline Val neg_0(Val x) {
  return -x;
}

__device__ inline Val inv_0(Val x) {
  return inv(x);
}

__device__ inline ExtVal inv_0(ExtVal x) {
  return inv(x);
}

__device__ inline Val bitAnd(Val a, Val b) {
  return Val(a.asUInt32() & b.asUInt32());
}

__device__ inline Val inRange(Val low, Val mid, Val high) {
  assert(low <= high);
  return Val(low <= mid && mid < high);
}

__device__ inline void eqz(ExecContext& ctx, Val a, const char* loc) {
  if (a.asUInt32()) {
    printf("[%zu] eqz failure at: %s\n", ctx.cycle, loc);
    assert(false && "eqz failure");
  }
}

__device__ inline void eqz(ExecContext& ctx, ExtVal a, const char* loc) {
  for (size_t i = 0; i < EXT_SIZE; i++) {
    eqz(ctx, a.elems[i], loc);
  }
}

// Define index type (used in back)
using Index = size_t;

struct Reg {
  __device__ constexpr Reg(size_t col) : col(col) {}
  size_t col;
};

#define BIND_LAYOUT(orig, buf) BoundLayout(orig, buf)
#define LAYOUT_LOOKUP(orig, elem) BoundLayout(orig.layout.elem, orig.buf)
#define LAYOUT_SUBSCRIPT(orig, index) BoundLayout(orig.layout[index], orig.buf)
#define EQZ(val, loc) eqz(ctx, val, loc)

__device__ inline void store(ExecContext& ctx, BoundLayout<Reg> reg, Val val) {
  reg.buf->store(ctx, reg.layout.col, val);
}

__device__ inline void set(ExecContext& ctx, BufferObj* buf, size_t offset, Val val) {
  static_cast<MutableBufObj*>(buf)->store(ctx, offset, val);
}

__device__ inline void setGlobal(ExecContext& ctx, BufferObj* buf, size_t offset, Val val) {
  static_cast<GlobalBufObj*>(buf)->store(ctx, offset, val);
}

__device__ inline void storeExt(ExecContext& ctx, BoundLayout<Reg> reg, ExtVal val) {
  for (size_t i = 0; i < EXT_SIZE; i++) {
    reg.buf->store(ctx, reg.layout.col + i, val.elems[i]);
  }
}

__device__ inline Val load(ExecContext& ctx, BoundLayout<Reg> reg, size_t back) {
  return reg.buf->load(ctx, reg.layout.col, back);
}

__device__ inline ExtVal loadExt(ExecContext& ctx, BoundLayout<Reg> reg, size_t back) {
  ::cuda::std::array<Fp, EXT_SIZE> elems;
  for (size_t i = 0; i < EXT_SIZE; i++) {
    elems[i] = reg.buf->load(ctx, reg.layout.col + i, back);
  }
  return FpExt(elems[0], elems[1], elems[2], elems[3]);
}

__device__ inline Val get(ExecContext& ctx, BufferObj* buf, size_t offset, size_t back) {
  return static_cast<MutableBufObj*>(buf)->load(ctx, offset, back);
}

__device__ inline Val getGlobal(ExecContext& ctx, BufferObj* buf, size_t offset) {
  return static_cast<GlobalBufObj*>(buf)->load(ctx, offset, 0);
}

#define LOAD(reg, back) load(ctx, reg, back)
#define LOAD_EXT(reg, back) loadExt(ctx, reg, back)
#define STORE(reg, val) store(ctx, reg, val)
#define STORE_EXT(reg, val) storeExt(ctx, reg, val)

// Map + reduce support
template <typename T1, typename F, size_t N>
__device__ inline auto map(::cuda::std::array<T1, N> a, F f) {
  ::cuda::std::array<decltype(f(a[0])), N> out;
  for (size_t i = 0; i < N; i++) {
    out[i] = f(a[i]);
  }
  return out;
}

template <typename T1, typename T2, typename F, size_t N>
__device__ inline auto map(::cuda::std::array<T1, N> a, ::cuda::std::array<T2, N> b, F f) {
  ::cuda::std::array<decltype(f(a[0], b[0])), N> out;
  for (size_t i = 0; i < N; i++) {
    out[i] = f(a[i], b[i]);
  }
  return out;
}

template <typename T1, typename T2, typename F, size_t N>
__device__ inline auto map(::cuda::std::array<T1, N> a, const BoundLayout<T2>& b, F f) {
  ::cuda::std::array<decltype(f(a[0], BoundLayout(b.layout[0], b.buf))), N> out;
  for (size_t i = 0; i < N; i++) {
    out[i] = f(a[i], BoundLayout(b.layout[i], b.buf));
  }
  return out;
}

template <typename T1, typename T2, typename F, size_t N>
__device__ inline auto reduce(::cuda::std::array<T1, N> elems, T2 start, F f) {
  T2 cur = start;
  for (size_t i = 0; i < N; i++) {
    cur = f(cur, elems[i]);
  }
  return cur;
}

template <typename T1, typename T2, typename T3, typename F, size_t N>
__device__ inline auto
reduce(::cuda::std::array<T1, N> elems, T2 start, const BoundLayout<T3>& b, F f) {
  T2 cur = start;
  for (size_t i = 0; i < N; i++) {
    cur = f(cur, elems[i], BoundLayout(b.layout[i], b.buf));
  }
  return cur;
}

// All the extern handling
#define INVOKE_EXTERN(ctx, name, ...) extern_##name(ctx, ##__VA_ARGS__)

__device__ ::cuda::std::array<Val, 5> extern_getMemoryTxn(ExecContext& ctx, Val addrElem);
__device__ void extern_lookupDelta(ExecContext& ctx, Val table, Val index, Val count);
__device__ Val extern_lookupCurrent(ExecContext& ctx, Val table, Val index);
__device__ void
extern_memoryDelta(ExecContext& ctx, Val addr, Val cycle, Val dataLow, Val dataHigh, Val count);
__device__ uint32_t extern_getDiffCount(ExecContext& ctx, Val cycle);
__device__ Val extern_isFirstCycle_0(ExecContext& ctx);
__device__ ::cuda::std::array<Val, 4> extern_divide(
    ExecContext& ctx, Val numerLow, Val numerHigh, Val denomLow, Val denomHigh, Val signType);
__device__ void extern_print(ExecContext& ctx, Val v);
__device__ ::cuda::std::array<Val, 2> extern_getMajorMinor(ExecContext& ctx);
__device__ Val extern_hostReadPrepare(ExecContext& ctx, Val fp, Val len);
__device__ Val extern_hostWrite(ExecContext& ctx, Val fdVal, Val addrLow, Val addrHigh, Val lenVal);
__device__ ::cuda::std::array<Val, 2> extern_nextPagingIdx(ExecContext& ctx);
__device__ ::cuda::std::array<Val, 16> extern_bigIntExtern(ExecContext& ctx);

template <typename T> __device__ void extern_log(ExecContext& ctx, const char* message, T vals) {
  // printf("%s\n", message);
}

__device__ inline void extern_assert(ExecContext& ctx, Val cond, const char* message) {
  // if (cond != 0) {
  //   printf("assertion failed: %s\n", message);
  //   assert(0);
  // }
}

// Setup the basic field stuff
#define SET_FIELD(x) /**/

#include "defs.cu.inc"

#include "types.cuh.inc"

#include "layout.cu.inc"

} // namespace risc0::circuit::rv32im_v2::cuda
