// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT
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
#include <array>
#include <cassert>
#include <cstdint>
#include <cstdio>
#include <functional>
#include <iomanip>
#include <iostream>
#include <string.h>
#include <vector>

namespace risc0::circuit::keccak::cpu {

struct ExecBuffers {
  Buffer global;
  Buffer data;
};

using KeccakState = std::array<uint64_t, 25>;

struct PreflightTrace {
  // All the preimages
  KeccakState* preimages;

  // Number of preimages
  uint32_t preimagesSize;

  // Which 'preimage' each cycle is working on (to answer extern calls)
  uint32_t* curPreimage;
};

#if defined(__clang__)
#pragma clang diagnostic ignored "-Wunused-parameter"
#pragma clang diagnostic ignored "-Wunused-variable"
#elif defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

using Val = risc0::Fp;
using ExtVal = risc0::FpExt;

inline size_t to_size_t(Val v) {
  return v.asUInt32();
}

inline ExtVal operator+(const Val& lhs, const ExtVal& rhs) {
  return FpExt(lhs) + rhs;
}

inline ExtVal operator-(const ExtVal& lhs, const Val& rhs) {
  return lhs - FpExt(rhs);
}

inline Val mod(Val a, Val b) {
  return Val(a.asUInt32() % b.asUInt32());
}

constexpr size_t EXT_SIZE = 4;

// Built in field operations
inline Val isz(Val x) {
  return Val(x == Val(0));
}

inline Val neg_0(Val x) {
  return -x;
}

inline Val inv_0(Val x) {
  return inv(x);
}

inline ExtVal inv_0(ExtVal x) {
  return inv(x);
}

inline Val bitAnd(Val a, Val b) {
  return Val(a.asUInt32() & b.asUInt32());
}

inline Val inRange(Val low, Val mid, Val high) {
  assert(low <= high);
  return Val(low <= mid && mid < high);
}

inline void eqz(Val a, const char* loc) {
  if (a.asUInt32()) {
    printf("eqz failure at: %s\n", loc);
    throw std::runtime_error("eqz failure");
  }
}

inline void eqz(ExtVal a, const char* loc) {
  for (size_t i = 0; i < EXT_SIZE; i++) {
    eqz(a.elems[i], loc);
  }
}

struct ExecContext {
public:
  ExecContext(PreflightTrace& preflight, size_t cycle) : preflight(preflight), cycle(cycle) {}

  PreflightTrace& preflight;
  size_t cycle;
};

// Define index type (used in back)
using Index = size_t;

struct Reg {
  constexpr Reg(size_t col) : col(col) {}
  size_t col;
};

struct BufferObj {
  virtual Val load(ExecContext& ctx, size_t col, size_t back) = 0;
  virtual void store(ExecContext& ctx, size_t col, Val val) = 0;
};

struct MutableBufObj : public BufferObj {
  MutableBufObj(Buffer& buf) : buf(buf) {}

  Val load(ExecContext& ctx, size_t col, size_t back) override {
    if (back > ctx.cycle) {
      return 0;
    }
    return buf.get(ctx.cycle - back, col);
  }

  void store(ExecContext& ctx, size_t col, Val val) override {
    return buf.set(ctx.cycle, col, val);
  }

  Buffer& buf;
};

using MutableBuf = MutableBufObj*;

struct GlobalBufObj : public BufferObj {
  GlobalBufObj(Buffer& buf) : buf(buf) {}

  Val load(ExecContext& ctx, size_t col, size_t back) override {
    assert(back == 0);
    return buf.get(0, col);
  }

  void store(ExecContext& ctx, size_t col, Val val) override { return buf.set(0, col, val); }

  Buffer& buf;
};

using GlobalBuf = GlobalBufObj*;

template <typename T> struct BoundLayout {
  BoundLayout(const T& layout, BufferObj* buf) : layout(layout), buf(buf) {}
  BoundLayout() = default;
  BoundLayout(const BoundLayout&) = default;

  const T& layout;
  BufferObj* buf = nullptr;
};

#define BIND_LAYOUT(orig, buf) BoundLayout(orig, buf)
#define LAYOUT_LOOKUP(orig, elem) BoundLayout(orig.layout.elem, orig.buf)
#define LAYOUT_SUBSCRIPT(orig, index) BoundLayout(orig.layout[index], orig.buf)
#define EQZ(val, loc) eqz(val, loc)

inline void store(ExecContext& ctx, BoundLayout<Reg> reg, Val val) {
  reg.buf->store(ctx, reg.layout.col, val);
}

inline void set(ExecContext& ctx, BufferObj* buf, size_t offset, Val val) {
  static_cast<MutableBufObj*>(buf)->store(ctx, offset, val);
}

inline void setGlobal(ExecContext& ctx, BufferObj* buf, size_t offset, Val val) {
  static_cast<GlobalBufObj*>(buf)->store(ctx, offset, val);
}

inline void storeExt(ExecContext& ctx, BoundLayout<Reg> reg, ExtVal val) {
  for (size_t i = 0; i < EXT_SIZE; i++) {
    reg.buf->store(ctx, reg.layout.col + i, val.elems[i]);
  }
}

inline Val load(ExecContext& ctx, BoundLayout<Reg> reg, size_t back) {
  return reg.buf->load(ctx, reg.layout.col, back);
}

inline ExtVal loadExt(ExecContext& ctx, BoundLayout<Reg> reg, size_t back) {
  std::array<Fp, EXT_SIZE> elems;
  for (size_t i = 0; i < EXT_SIZE; i++) {
    elems[i] = reg.buf->load(ctx, reg.layout.col + i, back);
  }
  return FpExt(elems[0], elems[1], elems[2], elems[3]);
}

inline Val get(ExecContext& ctx, BufferObj* buf, size_t offset, size_t back) {
  return static_cast<MutableBufObj*>(buf)->load(ctx, offset, back);
}

inline Val getGlobal(ExecContext& ctx, BufferObj* buf, size_t offset) {
  return static_cast<GlobalBufObj*>(buf)->load(ctx, offset, 0);
}

#define LOAD(reg, back) load(ctx, reg, back)
#define LOAD_EXT(reg, back) loadExt(ctx, reg, back)
#define STORE(reg, val) store(ctx, reg, val)
#define STORE_EXT(reg, val) storeExt(ctx, reg, val)

// Map + reduce support
template <typename T1, typename F, size_t N> inline auto map(std::array<T1, N> a, F f) {
  std::array<decltype(f(a[0])), N> out;
  for (size_t i = 0; i < N; i++) {
    out[i] = f(a[i]);
  }
  return out;
}

template <typename T1, typename T2, typename F, size_t N>
inline auto map(std::array<T1, N> a, std::array<T2, N> b, F f) {
  std::array<decltype(f(a[0], b[0])), N> out;
  for (size_t i = 0; i < N; i++) {
    out[i] = f(a[i], b[i]);
  }
  return out;
}

template <typename T1, typename T2, typename F, size_t N>
inline auto map(std::array<T1, N> a, const BoundLayout<T2>& b, F f) {
  std::array<decltype(f(a[0], BoundLayout(b.layout[0], b.buf))), N> out;
  for (size_t i = 0; i < N; i++) {
    out[i] = f(a[i], BoundLayout(b.layout[i], b.buf));
  }
  return out;
}

template <typename T1, typename T2, typename F, size_t N>
inline auto reduce(std::array<T1, N> elems, T2 start, F f) {
  T2 cur = start;
  for (size_t i = 0; i < N; i++) {
    cur = f(cur, elems[i]);
  }
  return cur;
}

template <typename T1, typename T2, typename T3, typename F, size_t N>
inline auto reduce(std::array<T1, N> elems, T2 start, const BoundLayout<T3>& b, F f) {
  T2 cur = start;
  for (size_t i = 0; i < N; i++) {
    cur = f(cur, elems[i], BoundLayout(b.layout[i], b.buf));
  }
  return cur;
}

// All the extern handling
#define INVOKE_EXTERN(ctx, name, ...) extern_##name(ctx, ##__VA_ARGS__)

Val extern_isFirstCycle(ExecContext& ctx);
Val extern_getCycle(ExecContext& ctx);
void extern_log(ExecContext& ctx, const std::string& message, std::vector<Val> vals);
Val extern_getPreimage(ExecContext& ctx, Val idx);
Val extern_nextPreimage(ExecContext& ctx);

// Setup the basic field stuff
#define SET_FIELD(x) /**/

#include "defs.cpp.inc"

#include "types.h.inc"

#include "layout.cpp.inc"

} // namespace risc0::circuit::keccak::cpu
