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

#include "rv32im/circuit/circuit.ipp"

template<typename RegT, typename ValT, typename ValExtT>
struct VerifyContext {
  using RegImpl = RegT;
  using ArgCountRegImpl = RegT;
  using ValImpl = ValT;
  using ValExtImpl = ValExtT;
  using C = VerifyContext;

  struct VerifyFwd {
    template<typename T, typename... Args>
    FDEV static void apply(MTHR VerifyContext& ctx, MDEV T& obj, Args... args) {
      obj.template applyInner<VerifyFwd>(ctx, args...);
      obj.verify(ctx, args...);
      obj.addArguments(ctx, args...);
    }

    template <typename T, size_t N>
    FDEV static void apply(MTHR VerifyContext& ctx, MDEV T (&t)[N]) {
      for (size_t i = 0; i < N; i++) {
        VerifyFwd::apply(ctx, t[i]);
      }
    }
  };
  MDEV Top<C>* top;
  MDEV RegExt<C>* accum;
  MDEV RegExt<C>* prevAccum;
  MDEV Val<C>* globals;
  MDEV ValExt<C>* accMix;
  ValExt<C> ecMix;
  Val<C> x;

  ValExt<C> curEcMix = ValExtT(1);
  ValExt<C> ecTot = ValExtT(0);

  Val<C> isValid = true;

  uint32_t accCol = 0;
  uint32_t accSubstep = 0;
  ValExt<C> accTot = ValExtT(0);
  Val<C> numers[2];
  ValExt<C> denoms[2];

  FDEV VerifyContext(MDEV RegT* data, MDEV RegT* accum, MDEV RegT* prevAccum, MDEV ValT* globals, MDEV ValExtT* accMix, ValExtT ecMix, ValT x)
    : top(reinterpret_cast<MDEV Top<C>*>(data))
    , accum(reinterpret_cast<MDEV RegExt<C>*>(accum))
    , prevAccum(reinterpret_cast<MDEV RegExt<C>*>(prevAccum))
    , globals(globals)
    , accMix(accMix)
    , ecMix(ecMix)
    , x(x) 
  {}

  // Main entry point
  FDEV ValExtT verify() {
    // Verify the selector
    VerifyFwd::apply(*this, top->select);
    ValExtT ret = ecTot;
    // Verify inner data
    #define BLOCK_TYPE(name, count) \
    { \
      reset(); \
      for (size_t i = 0; i < count; i++) { \
        isValid = top->mux.name.isValid[i].get(); \
        VerifyFwd::apply(*this, top->mux.name.data[i]); \
      } \
      finalize(); \
      ecTot *= top->select.at(uint32_t(BlockType::name)); \
      ret += ecTot; \
    }
    BLOCK_TYPES
    #undef BLOCK_TYPE
    // Verify accumTop
    // TODO: this is very ugly
    auto accumTop = reinterpret_cast<MDEV AccumTop<C>*>(reinterpret_cast<MDEV RegT*>(accum) + MAX_ACCUM_PER_ROW);
    auto prevAccumTop = reinterpret_cast<MDEV AccumTop<C>*>(reinterpret_cast<MDEV RegT*>(prevAccum) + MAX_ACCUM_PER_ROW);
    ecTot = ValExtT(0);
    VerifyFwd::apply(*this, *accumTop, top, prevAccumTop, accMix[ACCUM_BIGINT_Z]);
    ret += ecTot;
    return ret;
  }

  FDEV void reset() {
    ecTot = ValExtT(0);
    accCol = 1;
    accSubstep = 0;
    accTot = ValExtT(0);
  }
  FDEV void eqz(ValT val) {
    ecTot += curEcMix * val;
    curEcMix *= ecMix;
  }
  FDEV void eqz(ValExtT val) {
    ecTot += curEcMix * val;
    curEcMix *= ecMix;
  }
  template<typename T> FDEV void push(const MTHR T& argument) {
    addArgument(isValid, argument);
  }
  template<typename T> FDEV void pull(const MTHR T& argument) {
    addArgument(-isValid, argument);
  }
  template<typename T> FDEV void addArgument(ValT count, const MTHR T& argument) {
    ValExtT flat = flattenArgument<T, VerifyContext>(argument, accMix + 1);
    denoms[accSubstep] = accMix[0] - flat;
    numers[accSubstep] = count;
    accSubstep++;
    if (accSubstep == 2) {
      finishFpExt();
    }
  }
  FDEV void finishFpExt() {
    if (accSubstep == 1) {
      denoms[1] = ValExtT(1);
      numers[1] = 0;
    }
    ValExtT cur = ValExtT(accum[accCol].get());
    // We want to show that at
    // cur = n0/d0 + n1/d1 ==> cur * d0 * d1 = n0 * d1 + n1 * d0
    ValExtT lhs = cur * denoms[0] * denoms[1];
    ValExtT rhs = denoms[0] * numers[1] + denoms[1] * numers[0];
    eqz(lhs - rhs);
    // Bump forward
    accCol++;
    accSubstep = 0;
    accTot += cur;
  }
  FDEV void finalize() {
    if (accSubstep != 0) {
      finishFpExt();
    }
    eqz(accum[0].get() - (prevAccum[0].get() + accTot));
  }
  FDEV inline ValT globalGet(size_t idx) { return globals[idx]; }
  FDEV inline ValT getX() { return x; }
};

template<typename RegT, typename ValT, typename ValExtT>
FDEV ValExtT verifyCircuit(MDEV RegT* data, MDEV RegT* accum, MDEV RegT* prevAccum, MDEV ValT* globals, MDEV ValExtT* accMix, ValExtT ecMix, ValT x) {
  VerifyContext<RegT, ValT, ValExtT> verifier(data, accum, prevAccum, globals, accMix, ecMix, x);
  return verifier.verify();
}

