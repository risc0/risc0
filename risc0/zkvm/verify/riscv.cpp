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

#define SIZES
#include "risc0/zkvm/circuit/step.cpp.inc"
#undef SIZES

enum class OpType {
  CONST,
  GET,
  GET_GLOBAL,
  BEGIN,
  ASSERT_ZERO,
  COMBINE,
  ADD,
  SUB,
  MUL,
};

struct Op {
  OpType type;
  size_t out;
  size_t a;
  size_t b;
  size_t c;
  Fp val;
  const char* loc;
};

static constexpr size_t kNumSteps = kNumStepFp4s + kNumStepCons;

static const Op g_steps[kNumSteps] = {
#define CHECK_EVAL
#define do_const(out, cval) {OpType::CONST, out, 0, 0, 0, cval},
#define do_get(out, buf, reg, back, id) {OpType::GET, out, id, 0, 0, 0},
#define do_get_global(out, reg) {OpType::GET_GLOBAL, out, reg, 0, 0, 0},
#define do_begin(out) {OpType::BEGIN, out, 0, 0, 0, 0},
#define do_assert_zero(out, in, zval, loc) {OpType::ASSERT_ZERO, out, in, zval, 0, 0, loc},
#define do_combine(out, prev, cond, inner, loc) {OpType::COMBINE, out, prev, cond, inner, 0, loc},
#define do_add(out, a, b) {OpType::ADD, out, a, b, 0, 0},
#define do_sub(out, a, b) {OpType::SUB, out, a, b, 0, 0},
#define do_mul(out, a, b) {OpType::MUL, out, a, b, 0, 0},
#define do_result(out)                                                                             \
  }                                                                                                \
  ;                                                                                                \
  size_t kResultID = out;
#include "risc0/zkvm/circuit/step.cpp.inc"
#undef CHECK_EVAL

    struct MixState{Fp4 tot;
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
}; // namespace

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

} // namespace risc0

static TapSet buildTapSet() {
  All all;
  RegisterGroup accum = RegisterGroup::ACCUM;
  RegisterGroup code = RegisterGroup::CODE;
  RegisterGroup data = RegisterGroup::DATA;
#define tap(base, offset, back) all[base][offset].insert(back);
#define TAPS
#include "risc0/zkvm/circuit/step.cpp.inc"
  return TapSet(all);
}

TapSetRef getRiscVTaps() {
  static TapSet taps = buildTapSet();
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
  LOG(1, "whichCode: " << whichCode);
  return codeID_[whichCode] == top;
}

Fp4 RiscVVerifyCircuit::computePolynomial(const Fp4* evalU, Fp4 polyMix) const {
  // Do the big polynomial eval
  std::vector<Fp4> fp4s(kNumStepFp4s);
  std::vector<MixState> cons(kNumStepCons);
  for (size_t i = 0; i < kNumSteps; i++) {
    const auto& step = g_steps[i];
    switch (step.type) {
    case OpType::CONST:
      fp4s[step.out] = Fp4(step.val);
      break;
    case OpType::GET:
      fp4s[step.out] = evalU[step.a];
      break;
    case OpType::GET_GLOBAL:
      fp4s[step.out] = Fp4(globals_[step.a]);
      break;
    case OpType::BEGIN:
      break;
    case OpType::ASSERT_ZERO:
      cons[step.out] = cons[step.a].assert_zero(fp4s[step.b], polyMix, step.loc);
      break;
    case OpType::COMBINE:
      cons[step.out] = cons[step.a].combine(fp4s[step.b], cons[step.c], step.loc);
      break;
    case OpType::ADD:
      fp4s[step.out] = fp4s[step.a] + fp4s[step.b];
      break;
    case OpType::SUB:
      fp4s[step.out] = fp4s[step.a] - fp4s[step.b];
      break;
    case OpType::MUL:
      fp4s[step.out] = fp4s[step.a] * fp4s[step.b];
      break;
    }
  }
  MixState result = cons[kResultID];

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
