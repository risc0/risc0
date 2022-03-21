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

#include "risc0/zkp/core/fp4.h"
#include "risc0/zkp/verify/verify.h"

namespace risc0 {

namespace {
struct MixState {
  Fp4 tot;
  Fp4 mul;
#ifdef CIRCUIT_DEBUG
  std::vector<std::pair<const char*, Fp4>> locs;
#endif

  MixState() : tot(Fp4(0)), mul(Fp4(1)) {}
  MixState(Fp4 tot, Fp4 mul) : tot(tot), mul(mul) {}
  MixState assert_zero(Fp4 val, Fp4 mix, const char* loc) const {
    MixState ret(tot + mul * val, mul * mix);
#ifdef CIRCUIT_DEBUG
    if (locs.empty()) {
      if (val != Fp4()) {
        ret.locs.emplace_back(loc, val);
      }
    } else {
      ret.locs = locs;
    }
#endif
    return ret;
  }
  MixState combine(Fp4 cond, const MixState& inner, const char* loc) const {
    MixState ret(tot + cond * mul * inner.tot, mul * inner.mul);
#ifdef CIRCUIT_DEBUG
    if (locs.empty()) {
      if (cond != Fp4() && !inner.locs.empty()) {
        ret.locs = inner.locs;
        ret.locs.emplace_back(loc, cond);
      }
    } else {
      ret.locs = locs;
    }
#endif
    return ret;
  }
};

} // namespace

TapSetRef getRiscVTaps() {
  static TapSet tapSet;
  static bool computed = false;
  if (!computed) {
    RegisterGroup accum = RegisterGroup::ACCUM;
    RegisterGroup code = RegisterGroup::CODE;
    RegisterGroup data = RegisterGroup::DATA;
#define tap(base, offset, back) tapSet.addTap(base, offset, back);
#define TAPS
#include "risc0/zkp/prove/step/step.cpp.inc"
    computed = true;
  }
  return tapSet.getRef();
}

static Fp4 RiscVPolynomial(const Fp4* evalU, const Fp* globals) {
  Fp4 polyMix = {globals[kPolyMixGlobalOffset],
                 globals[kPolyMixGlobalOffset + 1],
                 globals[kPolyMixGlobalOffset + 2],
                 globals[kPolyMixGlobalOffset + 3]};

  // Do the big polynomial eval
#define CHECK_EVAL
#define do_get(buf, reg, back, id) evalU[id];
#define do_get_global(reg) globals[reg]
#define do_begin() MixState()
#define do_assert_zero(in, val, loc) in.assert_zero(Fp4(val), polyMix, loc)
#define do_combine(prev, cond, inner, loc) prev.combine(Fp4(cond), inner, loc)
#define do_add(a, b) Fp4(a) + Fp4(b)
#define do_sub(a, b) Fp4(a) - Fp4(b)
#define do_mul(a, b) Fp4(a) * Fp4(b)
#include "risc0/zkp/prove/step/step.cpp.inc"

#ifdef CIRCUIT_DEBUG
  for (const auto& loc : result.locs) {
    LOG(1, "  ERR LOC: " << loc.second << " @ " << loc.first);
  }
#endif
  return result.tot;
}

VerifyCircuit getRiscVVerifyCircuit() {
  return VerifyCircuit(getRiscVTaps(), RiscVPolynomial);
}

} // namespace risc0
