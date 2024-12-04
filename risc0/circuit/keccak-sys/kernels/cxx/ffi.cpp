// Copyright 2024 RISC Zero, Inc.
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

#include "vendor/poolstl.hpp"

#include <array>
#include <cassert>
#include <cstdint>
#include <cstdio>
#include <functional>
#include <iomanip>
#include <iostream>
#include <string.h>
#include <vector>

namespace risc0 {

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

namespace keccak::cpu {

#if defined(__clang__)
#pragma clang diagnostic ignored "-Wunused-parameter"
#pragma clang diagnostic ignored "-Wunused-variable"
#elif defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif

using Val = risc0::Fp;
using ExtVal = risc0::FpExt;

size_t to_size_t(Val v) {
  return v.asUInt32();
}

ExtVal operator+(const Val& lhs, const ExtVal& rhs) {
  return FpExt(lhs) + rhs;
}

ExtVal operator-(const ExtVal& lhs, const Val& rhs) {
  return lhs - FpExt(rhs);
}

Val mod(Val a, Val b) {
  return Val(a.asUInt32() % b.asUInt32());
}

struct ExecContext {
public:
  ExecContext(PreflightTrace& preflight, size_t cycle) : preflight(preflight), cycle(cycle) {}

  PreflightTrace& preflight;
  size_t cycle;
};

// Setup the basic field stuff
#define SET_FIELD(x) /**/

constexpr size_t EXT_SIZE = 4;

// Built in field operations
Val isz(Val x) {
  return Val(x == Val(0));
}

Val neg_0(Val x) {
  return -x;
}

Val inv_0(Val x) {
  return inv(x);
}

ExtVal inv_0(ExtVal x) {
  return inv(x);
}

Val bitAnd(Val a, Val b) {
  return Val(a.asUInt32() & b.asUInt32());
}

Val inRange(Val low, Val mid, Val high) {
  assert(low <= high);
  return Val(low <= mid && mid < high);
}

void eqz(Val a, const char* loc) {
  if (a.asUInt32()) {
    printf("eqz failure at: %s\n", loc);
    throw std::runtime_error("eqz failure");
  }
}

void eqz(ExtVal a, const char* loc) {
  for (size_t i = 0; i < EXT_SIZE; i++) {
    eqz(a.elems[i], loc);
  }
}

// Define index type (used in back)
using Index = size_t;

struct Reg {
  constexpr Reg(size_t col) : col(col) {}
  size_t col;
};

struct BufferObj {
  virtual Val load(size_t col, size_t back) = 0;
  virtual void store(size_t col, Val val) = 0;
};

struct MutableBufObj : public BufferObj {
  MutableBufObj(ExecContext& ctx, Buffer& buf) : ctx(ctx), buf(buf) {}

  Val load(size_t col, size_t back) override {
    if (back > ctx.cycle) {
      return 0;
    }
    return buf.get(ctx.cycle - back, col);
  }

  void store(size_t col, Val val) override { return buf.set(ctx.cycle, col, val); }

  ExecContext& ctx;
  Buffer& buf;
};

using MutableBuf = MutableBufObj*;

struct GlobalBufObj : public BufferObj {
  GlobalBufObj(ExecContext& ctx, Buffer& buf) : ctx(ctx), buf(buf) {}

  Val load(size_t col, size_t back) override {
    assert(back == 0);
    return buf.get(0, col);
  }

  void store(size_t col, Val val) override { return buf.set(0, col, val); }

  ExecContext& ctx;
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

void store(ExecContext& ctx, BoundLayout<Reg> reg, Val val) {
  reg.buf->store(reg.layout.col, val);
}

void storeExt(ExecContext& ctx, BoundLayout<Reg> reg, ExtVal val) {
  for (size_t i = 0; i < EXT_SIZE; i++) {
    reg.buf->store(reg.layout.col + i, val.elems[i]);
  }
}

Val load(ExecContext& ctx, BoundLayout<Reg> reg, size_t back) {
  return reg.buf->load(reg.layout.col, back);
}

ExtVal loadExt(ExecContext& ctx, BoundLayout<Reg> reg, size_t back) {
  std::array<Fp, EXT_SIZE> elems;
  for (size_t i = 0; i < EXT_SIZE; i++) {
    elems[i] = reg.buf->load(reg.layout.col + i, back);
  }
  return FpExt(elems[0], elems[1], elems[2], elems[3]);
}

#define LOAD(reg, back) load(ctx, reg, back)
#define LOAD_EXT(reg, back) loadExt(ctx, reg, back)
#define STORE(reg, val) store(ctx, reg, val)
#define STORE_EXT(reg, val) storeExt(ctx, reg, val)

// Map + reduce support
template <typename T1, typename F, size_t N> auto map(std::array<T1, N> a, F f) {
  std::array<decltype(f(a[0])), N> out;
  for (size_t i = 0; i < N; i++) {
    out[i] = f(a[i]);
  }
  return out;
}

template <typename T1, typename T2, typename F, size_t N>
auto map(std::array<T1, N> a, std::array<T2, N> b, F f) {
  std::array<decltype(f(a[0], b[0])), N> out;
  for (size_t i = 0; i < N; i++) {
    out[i] = f(a[i], b[i]);
  }
  return out;
}

template <typename T1, typename T2, typename F, size_t N>
auto map(std::array<T1, N> a, const BoundLayout<T2>& b, F f) {
  std::array<decltype(f(a[0], BoundLayout(b.layout[0], b.buf))), N> out;
  for (size_t i = 0; i < N; i++) {
    out[i] = f(a[i], BoundLayout(b.layout[i], b.buf));
  }
  return out;
}

template <typename T1, typename T2, typename F, size_t N>
auto reduce(std::array<T1, N> elems, T2 start, F f) {
  T2 cur = start;
  for (size_t i = 0; i < N; i++) {
    cur = f(cur, elems[i]);
  }
  return cur;
}

template <typename T1, typename T2, typename T3, typename F, size_t N>
auto reduce(std::array<T1, N> elems, T2 start, const BoundLayout<T3>& b, F f) {
  T2 cur = start;
  for (size_t i = 0; i < N; i++) {
    cur = f(cur, elems[i], BoundLayout(b.layout[i], b.buf));
  }
  return cur;
}

// All the extern handling
#define INVOKE_EXTERN(ctx, name, ...) extern_##name(ctx, ##__VA_ARGS__)

Val extern_isFirstCycle(ExecContext& ctx) {
  return ctx.cycle == 0;
}

Val extern_getCycle(ExecContext& ctx) {
  return ctx.cycle;
}

// std::ostream& hex_word(std::ostream& os, uint32_t word) {
//   std::cout << "0x"                                          //
//             << std::hex << std::setw(8) << std::setfill('0') //
//             << word                                          //
//             << std::dec << std::setw(0);
//   return os;
// }

void extern_log(ExecContext& ctx, const std::string& message, std::vector<Val> vals) {
  // std::cout << "LOG[" << ctx.cycle << "]: '" << message << "': ";
  // for (size_t i = 0; i < vals.size(); i++) {
  //   if (i != 0) {
  //     std::cout << ", ";
  //   }
  //   hex_word(std::cout, vals[i].asUInt32());
  // }
  // std::cout << "\n";
}

Val extern_getPreimage(ExecContext& ctx, Val idx) {
  uint32_t idxLow = idx.asUInt32() % 4;
  uint32_t idxHigh = idx.asUInt32() / 4;
  uint32_t preimageIdx = ctx.preflight.curPreimage[ctx.cycle];
  const KeccakState& preimages = ctx.preflight.preimages[preimageIdx];
  return (preimages[idxHigh] >> (16 * idxLow)) & 0xffff;
}

Val extern_nextPreimage(ExecContext& ctx) {
  return ctx.preflight.curPreimage[ctx.cycle] != ctx.preflight.preimagesSize;
}

#include "defs.cpp.inc"

#include "types.h.inc"

#include "layout.cpp.inc"

#include "steps.cpp.inc"

} // namespace keccak::cpu

void stepExec(ExecBuffers& buffers, PreflightTrace& preflight, size_t cycle) {
  keccak::cpu::ExecContext ctx(preflight, cycle);
  keccak::cpu::MutableBufObj data(ctx, buffers.data);
  keccak::cpu::GlobalBufObj global(ctx, buffers.global);
  step_Top(ctx, &data, &global);
}

} // namespace risc0

constexpr size_t kStepModeParallel = 0;
constexpr size_t kStepModeSeqForward = 1;
constexpr size_t kStepModeSeqReverse = 2;

extern "C" {

using namespace risc0;

const char* risc0_circuit_keccak_cpu_witgen(uint32_t mode,
                                            ExecBuffers* buffers,
                                            PreflightTrace* preflight,
                                            uint32_t lastCycle) {
  try {
    switch (mode) {
    case kStepModeParallel: {
      auto begin = poolstl::iota_iter<uint32_t>(0);
      auto end = poolstl::iota_iter<uint32_t>(lastCycle);
      std::for_each(
          poolstl::par, begin, end, [&](uint32_t cycle) { stepExec(*buffers, *preflight, cycle); });
    } break;
    case kStepModeSeqForward:
      for (size_t cycle = 0; cycle < lastCycle; cycle++) {
        stepExec(*buffers, *preflight, cycle);
      }
      break;
    case kStepModeSeqReverse: {
      for (size_t i = lastCycle; i-- > 0;) {
        // printf("stepExec: %zu\n", i);
        stepExec(*buffers, *preflight, i);
      }
    } break;
    }
  } catch (const std::exception& err) {
    return strdup(err.what());
  }
  return nullptr;
}

} // extern "C"
