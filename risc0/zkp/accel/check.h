#pragma once

#include "risc0/zkp/circuit/constants.h"

namespace risc0 {

struct MixState {
  Fp4 tot;
  Fp4 mul;
};

DEVSPEC Fp4 computePoly(      //
    const DEVADDR Fp* code,   //
    const DEVADDR Fp* data,   //
    const DEVADDR Fp* accum,  //
    const DEVADDR Fp* global, //
    uint32_t idx,             //
    uint32_t size) {
  uint32_t mask = size - 1;
  Fp4 mix = {global[kPolyMixGlobalOffset],
             global[kPolyMixGlobalOffset + 1],
             global[kPolyMixGlobalOffset + 2],
             global[kPolyMixGlobalOffset + 3]};
#define CHECK_EVAL
#define do_get(buf, reg, back) buf[reg * size + ((idx - kInvRate * back) & mask)]
#define do_get_global(reg) global[reg]
#define do_begin()                                                                                 \
  MixState { Fp4(0), Fp4(1) }
#define do_assert_zero(in, val, loc)                                                               \
  MixState { in.tot + in.mul *val, in.mul *mix }
#define do_combine(prev, cond, inner, loc)                                                         \
  MixState { prev.tot + cond *prev.mul *inner.tot, prev.mul *inner.mul }
#define do_add(a, b) a + b
#define do_sub(a, b) a - b
#define do_mul(a, b) a* b
#include "risc0/zkp/prove/step/step.cpp.inc"
#undef CHECK_EVAL
#undef do_get
#undef do_get_global
#undef do_begin
#undef do_add
#undef do_sub
#undef do_mul
  return result.tot;
}

} // namespace risc0
