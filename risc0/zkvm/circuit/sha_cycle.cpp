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

#include "risc0/zkvm/circuit/sha_cycle.h"

#include "risc0/zkvm/circuit/step_state.h"

#include <array>

namespace risc0 {

static std::array<Value, 32> get(const RegDigits<1, 32>& reg) {
  std::array<Value, 32> ret;
  for (size_t i = 0; i < 32; i++) {
    ret[i] = reg.get(i);
  }
  return ret;
}

static std::array<Value, 32> rightRotate(std::array<Value, 32> in, size_t n) {
  std::array<Value, 32> ret;
  for (size_t i = 0; i < 32; i++) {
    size_t from = (i + n) % 32;
    ret[i] = in[from];
  }
  return ret;
}

static std::array<Value, 32> rightShift(std::array<Value, 32> in, size_t n) {
  std::array<Value, 32> ret;
  for (size_t i = 0; i < 32; i++) {
    size_t from = i + n;
    if (from >= 32) {
      ret[i] = 0;
    } else {
      ret[i] = in[from];
    }
  }
  return ret;
}

static std::array<Value, 32> xor_(std::array<Value, 32> a, std::array<Value, 32> b) {
  std::array<Value, 32> ret;
  for (size_t i = 0; i < 32; i++) {
    ret[i] = a[i] + b[i] - 2 * a[i] * b[i];
  }
  return ret;
}

static std::array<Value, 32>
maj(std::array<Value, 32> a, std::array<Value, 32> b, std::array<Value, 32> c) {
  std::array<Value, 32> ret;
  for (size_t i = 0; i < 32; i++) {
    ret[i] = a[i] * b[i] * (1 - c[i]) + a[i] * (1 - b[i]) * c[i] + (1 - a[i]) * b[i] * c[i] +
             a[i] * b[i] * c[i];
  }
  return ret;
}

static std::array<Value, 32>
ch(std::array<Value, 32> a, std::array<Value, 32> b, std::array<Value, 32> c) {
  std::array<Value, 32> ret;
  for (size_t i = 0; i < 32; i++) {
    ret[i] = a[i] * b[i] + (1 - a[i]) * c[i];
  }
  return ret;
}

static ValueU32 flat(std::array<Value, 32> a) {
  std::array<Value, 2> ret;
  for (size_t i = 0; i < 2; i++) {
    ret[i] = 0;
    for (size_t j = 0; j < 16; j++) {
      ret[i] = ret[i] + a[i * 16 + j] * (1 << j);
    }
  }
  return {ret[0], ret[1]};
}

#define CTYPE(x) cycleType.is(ShaCycleType::x)

void ShaCycle::sync(StepState& state) {
  Value cycle = state.code.cycle.get();
  risc0Log("C%u: Sha Sync", {cycle});
  state.data.memIO.doRead(cycle);
  descriptor.set(kMemSHAStart / 4);
  count.set(0);
  index.set(0);
  source.set(0);
  digest.set(0);
}

void ShaCycle::doInitRegs(StepState& state) {
  BufAlloc ealloc(extra.slice(0, 0), extra.slice(12, 4));
  RegBin aCarryLow(ealloc);
  RegBin aCarryHigh(ealloc);
  RegBin eCarryLow(ealloc);
  RegBin eCarryHigh(ealloc);
  BYZ_IF(contHash.get()) {
    auto back4 = state.getPrev(4).asSha();
    a.set(back4.a.get());
    e.set(back4.e.get());
    risc0Log("  InitRegs, a = 0x%04x%04x, e =  0x%0x04x%04x",
             {a.get().high, a.get().low, e.get().high, e.get().low});
  }
  BYZ_IF(1 - contHash.get()) {
    a.set(state.code.data.get());
    e.set(state.code.data2.get());
    risc0Log("  InitRegs, a = 0x%04x%04x, e =  0x%04x%04x",
             {a.get().high, a.get().low, e.get().high, e.get().low});
  }
}

void ShaCycle::doInit0(StepState& state) {
  Value cycle = state.code.cycle.get();
  auto prev = state.getPrev(1).asSha();
  auto& memIO = state.data.memIO;
  BufAlloc ealloc(extra.slice(0, 0), extra.slice(8, 4));
  // Check if we are still working on an old SHA
  MakeBoolRegs isOldCountNonzero(ealloc);
  isOldCountNonzero.set(prev.count.get());
  BYZ_IF(isOldCountNonzero.get()) {
    // Yup, keep the registers all in their original state
    descriptor.set(prev.descriptor.get());
    isMerkle.set(prev.isMerkle.get());
    count.set(prev.count.get() - 1);
    risc0Log("  INIT0, cont", {});
    contOp.set(1);
  }
  BYZ_IF(1 - isOldCountNonzero.get()) {
    // Nope, load up new type + count, kick descriptor forward
    risc0Log("  INIT0, load, addr = %x, val = 0x%04x%04x",
             {memIO.address.get() * 4, memIO.value.high(), memIO.value.low()});
    descriptor.set(prev.descriptor.get() + 1);
    isMerkle.set(memIO.value.high());
    count.set(memIO.value.low());
    contOp.set(0);
  }
  index.set(prev.index.get());
  source.set(prev.source.get());
  digest.set(prev.digest.get());
  // Next question: Is the newly loaded descriptor count=0?  This signals the end of the list,
  // otherwise keep going
  MakeBoolRegs isCountNonzero(ealloc);
  isCountNonzero.set(count.get());
  BYZ_IF(isCountNonzero.get()) { nextCycleType.set(DataCycleType::SHA_CONTROL); }
  BYZ_IF(1 - isCountNonzero.get()) { nextCycleType.set(DataCycleType::HALT); }
  // Check if we should continue old values or clear to new ones
  contHash.set((1 - isMerkle.get()) * isOldCountNonzero.get());
}

namespace {
enum ControlType {
  CT_INIT_0,
  CT_INIT_1,
  CT_INIT_2,
  CT_INIT_3,
  CT_FINI_0,
  CT_FINI_1,
  CT_FINI_2,
  CT_FINI_3,
  NUM_CONTROL_TYPES,
};
}

void ShaCycle::setControl(StepState& state) {
  Value cycle = state.code.cycle.get();
  auto prev = state.getPrev(1).asSha();
  auto& memIO = state.data.memIO;
  BufAlloc ealloc(extra.slice(0, 0), extra.slice(0, 8));
  RegMux<NUM_CONTROL_TYPES> subtype(ealloc);
  subtype.set(state.code.p1.get());
  risc0Log("C%u: Sha Control", {cycle});
  BYZ_IF(subtype.is(CT_INIT_0)) {
    memIO.doRead(cycle, prev.descriptor.get());
    doInit0(state);
    doInitRegs(state);
  }
  BYZ_IF(subtype.is(CT_INIT_1)) {
    memIO.doRead(cycle, prev.descriptor.get());
    contOp.set(prev.contOp.get());
    contHash.set(prev.contHash.get());
    isMerkle.set(prev.isMerkle.get());
    count.set(prev.count.get());
    source.set(prev.source.get());
    digest.set(prev.digest.get());
    BYZ_IF(contOp.get()) {
      risc0Log("  INIT2, cont", {});
      index.set(prev.index.get());
      descriptor.set(prev.descriptor.get());
    }
    BYZ_IF(1 - contOp.get()) {
      risc0Log("  INIT1, load, addr = %x, val = 0x%04x%04x",
               {memIO.address.get() * 4, memIO.value.high(), memIO.value.low()});
      Value memVal = 0x10000 * memIO.value.high() + memIO.value.low();
      index.set(memVal);
      descriptor.set(prev.descriptor.get() + 1);
    }
    doInitRegs(state);
    nextCycleType.set(DataCycleType::SHA_CONTROL);
  }
  BYZ_IF(subtype.is(CT_INIT_2)) {
    memIO.doRead(cycle, prev.descriptor.get());
    contOp.set(prev.contOp.get());
    contHash.set(prev.contHash.get());
    isMerkle.set(prev.isMerkle.get());
    count.set(prev.count.get());
    index.set(prev.index.get());
    digest.set(prev.digest.get());
    BYZ_IF(contOp.get()) {
      risc0Log("  INIT2, cont", {});
      source.set(prev.source.get());
      descriptor.set(prev.descriptor.get());
    }
    BYZ_IF(1 - contOp.get()) {
      risc0Log("  INIT2, load, addr = %x, val = 0x%04x%04x",
               {memIO.address.get() * 4, memIO.value.high(), memIO.value.low()});
      Value memVal = (0x10000 * memIO.value.high() + memIO.value.low()) * inv(Fp(4));
      source.set(memVal);
      descriptor.set(prev.descriptor.get() + 1);
    }
    doInitRegs(state);
    nextCycleType.set(DataCycleType::SHA_CONTROL);
  }
  BYZ_IF(subtype.is(CT_INIT_3)) {
    memIO.doRead(cycle, prev.descriptor.get());
    contOp.set(prev.contOp.get());
    contHash.set(prev.contHash.get());
    isMerkle.set(prev.isMerkle.get());
    count.set(prev.count.get());
    index.set(prev.index.get());
    source.set(prev.source.get());
    BYZ_IF(contOp.get()) {
      risc0Log("  INIT3, cont", {});
      digest.set(prev.digest.get());
      descriptor.set(prev.descriptor.get());
    }
    BYZ_IF(1 - contOp.get()) {
      Value memVal = (0x10000 * memIO.value.high() + memIO.value.low()) * inv(Fp(4));
      digest.set(memVal + 7);
      descriptor.set(prev.descriptor.get() + 1);
    }
    doInitRegs(state);
    nextCycleType.set(DataCycleType::SHA_DATA);
  }
  BYZ_IF(subtype.is(CT_FINI_0) + subtype.is(CT_FINI_1) + subtype.is(CT_FINI_2) +
         subtype.is(CT_FINI_3)) {
    memIO.doRead(cycle, prev.digest.get());
    descriptor.set(prev.descriptor.get());
    isMerkle.set(prev.isMerkle.get());
    index.set(prev.index.get());
    source.set(prev.source.get());
    count.set(prev.count.get());
    auto a_4 = get(state.getPrev(4).asSha().a);
    auto a_68 = get(state.getPrev(68).asSha().a);
    auto e_4 = get(state.getPrev(4).asSha().e);
    auto e_68 = get(state.getPrev(68).asSha().e);
    aOut.set(flat(a_4) + flat(a_68));
    eOut.set(flat(e_4) + flat(e_68));
    BufAlloc ealloc2(extra.slice(0, 0), extra.slice(8, 6));
    RegBin aCarryLow(ealloc2);
    RegBin aCarryHigh(ealloc2);
    RegBin eCarryLow(ealloc2);
    RegBin eCarryHigh(ealloc2);
    MakeBoolRegs prevCountNot1(ealloc2);
    prevCountNot1.set(prev.count.get() - 1);
    a.setCarry(aOut.get(), aCarryLow, aCarryHigh);
    e.setCarry(eOut.get(), eCarryLow, eCarryHigh);
    risc0Log("  FINI, load, addr = %x, val = 0x%04x%04x",
             {memIO.address.get() * 4, memIO.value.high(), memIO.value.low()});
    nextCycleType.set(DataCycleType::SHA_CONTROL);
    BYZ_IF(prevCountNot1.get()) {
      // If this is not the final step, the prev 4 cycles tried to load, and thus bumped digest
      // We bump it back...
      digest.set(prev.digest.get() + 1);
    }
    BYZ_IF(1 - prevCountNot1.get()) {
      risc0Log("  VERIFY, 0x%04x%04x == 0x%04x%04x, 0x%04x%04x == 0x%04x%04x",
               {a.get().high,
                a.get().low,
                memIO.value.high(),
                memIO.value.low(),
                e.get().high,
                e.get().low,
                state.getPrev(4).memIO.value.high(),
                state.getPrev(4).memIO.value.low()});

      digest.set(prev.digest.get() - 1);
      equate(a.get().high, memIO.value.high());
      equate(a.get().low, memIO.value.low());
      equate(e.get().high, state.getPrev(4).memIO.value.high());
      equate(e.get().low, state.getPrev(4).memIO.value.low());
    }
  }
  risc0Log("  descriptor=%x, isMerkle=%d, count=%d, index=%x, source=%x, digest=%x, contOp=%d, "
           "contHash=%d",
           {descriptor.get(),
            isMerkle.get(),
            count.get(),
            index.get(),
            source.get(),
            digest.get(),
            contOp.get(),
            contHash.get()});
  risc0Log("  a=%04x%04x, e=%04x%04x",
           {a.getPart(16, 16), a.getPart(0, 16), e.getPart(16, 16), e.getPart(0, 16)});
}

void ShaCycle::computeW(StepState& state) {
  auto w_2 = get(state.getPrev(2).asSha().w);
  auto w_7 = get(state.getPrev(7).asSha().w);
  auto w_15 = get(state.getPrev(15).asSha().w);
  auto w_16 = get(state.getPrev(16).asSha().w);
  auto s0 = xor_(rightRotate(w_15, 7), xor_(rightRotate(w_15, 18), rightShift(w_15, 3)));
  auto s1 = xor_(rightRotate(w_2, 17), xor_(rightRotate(w_2, 19), rightShift(w_2, 10)));
  auto w_0 = flat(w_16) + flat(s0) + flat(w_7) + flat(s1);
  wOut.set(w_0);
}

void ShaCycle::computeAE(StepState& state) {
  auto a_ = get(state.getPrev(1).asSha().a);
  auto b_ = get(state.getPrev(2).asSha().a);
  auto c_ = get(state.getPrev(3).asSha().a);
  auto d_ = get(state.getPrev(4).asSha().a);
  auto e_ = get(state.getPrev(1).asSha().e);
  auto f_ = get(state.getPrev(2).asSha().e);
  auto g_ = get(state.getPrev(3).asSha().e);
  auto h_ = get(state.getPrev(4).asSha().e);
  auto k = state.code.data.get();
  /*
  risc0Log("  a_=%04x%04x", {flat(a_).high, flat(a_).low});
  risc0Log("  b_=%04x%04x", {flat(b_).high, flat(b_).low});
  risc0Log("  c_=%04x%04x", {flat(c_).high, flat(c_).low});
  risc0Log("  d_=%04x%04x", {flat(d_).high, flat(d_).low});
  risc0Log("  e_=%04x%04x", {flat(e_).high, flat(e_).low});
  risc0Log("  f_=%04x%04x", {flat(f_).high, flat(f_).low});
  risc0Log("  g_=%04x%04x", {flat(g_).high, flat(g_).low});
  risc0Log("  h_=%04x%04x", {flat(h_).high, flat(h_).low});
  risc0Log("  k_=%04x%04x", {k.high, k.low});
  risc0Log("  w_=%04x%04x", {w.get().high, w.get().low});
  */
  auto s0 = xor_(rightRotate(a_, 2), xor_(rightRotate(a_, 13), rightRotate(a_, 22)));
  auto s1 = xor_(rightRotate(e_, 6), xor_(rightRotate(e_, 11), rightRotate(e_, 25)));
  auto stage1 = w.get() + k + flat(h_) + flat(ch(e_, f_, g_)) + flat(s1);
  aOut.set(stage1 + flat(maj(a_, b_, c_)) + flat(s0));
  eOut.set(stage1 + flat(d_));
}

void ShaCycle::setData(StepState& state) {
  Value cycle = state.code.cycle.get();
  auto prev = state.getPrev(1).asSha();
  auto& memIO = state.data.memIO;
  BufAlloc ealloc(extra.slice(0, 0), extra.slice(0, 16));
  computeW(state);
  descriptor.set(prev.descriptor.get());
  isMerkle.set(prev.isMerkle.get());
  count.set(prev.count.get());
  index.set(prev.index.get());
  RegDigits<1, 3> aCarryLow(ealloc);
  RegDigits<1, 3> aCarryHigh(ealloc);
  RegDigits<1, 3> eCarryLow(ealloc);
  RegDigits<1, 3> eCarryHigh(ealloc);
  RegDigits<1, 2> wCarryLow(ealloc);
  RegDigits<1, 2> wCarryHigh(ealloc);
  BYZ_IF(state.code.shaCycleType[ShaCycleType::LOAD]) {
    memIO.doRead(cycle, prev.source.get());
    risc0Log("C%u: Sha Load: M[%x] = %04x%04x",
             {cycle, memIO.address.get() * 4, memIO.value.high(), memIO.value.low()});
    w.setBE(memIO.value.get());
    source.set(prev.source.get() + 1);
    digest.set(prev.digest.get());
  }
  BYZ_IF(state.code.shaCycleType[ShaCycleType::MIX]) {
    risc0Log("C%u: Sha Mix", {cycle});
    BYZ_IF(state.code.p1.get()) {
      memIO.doRead(cycle, prev.digest.get());
      risc0Log("  Load digest: M[%x] = %04x%04x",
               {memIO.address.get() * 4, memIO.value.high(), memIO.value.low()});
      digest.set(prev.digest.get() - 1);
    }
    BYZ_IF(1 - state.code.p1.get()) {
      memIO.doRead(cycle, 0);
      digest.set(prev.digest.get());
    }
    w.setCarry(wOut.get(), wCarryLow, wCarryHigh);
    source.set(prev.source.get());
  }
  computeAE(state);
  a.setCarry(aOut.get(), aCarryLow, aCarryHigh);
  e.setCarry(eOut.get(), eCarryLow, eCarryHigh);
  risc0Log("  a=%04x%04x, e=%04x%04x, w=%04x%04x",
           {a.getPart(16, 16),
            a.getPart(0, 16),
            e.getPart(16, 16),
            e.getPart(0, 16),
            w.getPart(16, 16),
            w.getPart(0, 16)});
  BYZ_IF(1 - state.code.p2.get()) { nextCycleType.set(DataCycleType::SHA_DATA); }
  BYZ_IF(state.code.p2.get()) { nextCycleType.set(DataCycleType::SHA_CONTROL); }
}

} // namespace risc0
