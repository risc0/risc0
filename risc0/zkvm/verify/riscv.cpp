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

#include "risc0/zkvm/verify/riscv.h"

#include "risc0/core/log.h"
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

class RiscVVerifyCircuit : public VerifyCircuit {
public:
  RiscVVerifyCircuit(const MethodID& codeID) : codeID_(codeID) {}
  TapSetRef getTapSet() const override { return getRiscVTaps(); }
  void execute(ReadIOP& iop) override;
  void accumulate(ReadIOP& iop) override;
  Fp4 computePolynomial(const Fp4* evalU, Fp4 polyMix) const override;
  uint32_t getPo2() const override { return po2_; }
  bool validCode(const ShaDigest& top) const override;

private:
  MethodID codeID_;
  uint32_t po2_;
  Fp globals_[kGlobalSize];
};

} // namespace

TapSetRef getRiscVTaps() {
  static TapSet taps;
  if (!taps.finalized()) {
    RegisterGroup accum = RegisterGroup::ACCUM;
    RegisterGroup code = RegisterGroup::CODE;
    RegisterGroup data = RegisterGroup::DATA;
#define tap(base, offset, back) taps.addTap(base, offset, back);
#define TAPS
#include "risc0/zkvm/circuit/step.cpp.inc"
    taps.finalize();
  }
  return taps.getRef();
}

void RiscVVerifyCircuit::execute(ReadIOP& iop) {
  // Read the low registers + write to globals
  for (size_t i = 0; i < kOutputRegs; i++) {
    uint32_t reg;
    iop.read(&reg, 1);
    globals_[2 * i] = reg & 0xffff;
    globals_[2 * i + 1] = reg >> 16;
  }
  // Read the po2 size
  iop.read(&po2_, 1);
}

void RiscVVerifyCircuit::accumulate(ReadIOP& iop) {
  // Fill in accum mix
  for (size_t i = 0; i < kAccumMixGlobalSize; i++) {
    globals_[kAccumMixGlobalOffset + i] = Fp::random(iop);
  }
}

bool RiscVVerifyCircuit::validCode(const ShaDigest& top) const {
  size_t whichCode = po2_ - log2Ceil(kMinCycles);
  return codeID_[whichCode] == top;
}

Fp4 RiscVVerifyCircuit::computePolynomial(const Fp4* evalU, Fp4 polyMix) const {
  // Do the big polynomial eval
#define CHECK_EVAL
#define do_get(buf, reg, back, id) evalU[id];
#define do_get_global(reg) globals_[reg]
#define do_begin() MixState()
#define do_assert_zero(in, val, loc) in.assert_zero(Fp4(val), polyMix, loc)
#define do_combine(prev, cond, inner, loc) prev.combine(Fp4(cond), inner, loc)
#define do_add(a, b) Fp4(a) + Fp4(b)
#define do_sub(a, b) Fp4(a) - Fp4(b)
#define do_mul(a, b) Fp4(a) * Fp4(b)
#include "risc0/zkvm/circuit/step.cpp.inc"

#ifdef CIRCUIT_DEBUG
  for (const auto& loc : result.locs) {
    LOG(1, "  ERR LOC: " << loc.second << " @ " << loc.first);
  }
#endif
  return result.tot;
}

std::unique_ptr<VerifyCircuit> getRiscVVerifyCircuit(const MethodID& id) {
  return std::make_unique<RiscVVerifyCircuit>(id);
}

} // namespace risc0
