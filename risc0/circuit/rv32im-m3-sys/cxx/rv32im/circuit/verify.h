// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

#pragma once

#include "rv32im/circuit/circuit.ipp"

template <typename ValExtT> struct DefaultMixState {
  FDEV DefaultMixState(ValExtT tot, ValExtT mul) : tot(tot), mul(mul) {}
  ValExtT tot;
  ValExtT mul;
};

template <typename ValT, typename ValExtT> struct DefaultEqzHandler {
  using MixStateT = DefaultMixState<ValExtT>;
  ValExtT ecMix;

  FDEV DefaultEqzHandler(ValExtT ecMix) : ecMix(ecMix) {}

  FDEV MixStateT getTrue() { return MixStateT(ValExtT(ValT(0)), ValExtT(ValT(1))); }
  FDEV MixStateT andEqz(MixStateT chain, ValT expr) {
    return MixStateT(chain.tot + chain.mul * expr, chain.mul * ecMix);
  }
  FDEV MixStateT andEqz(MixStateT chain, ValExtT expr) {
    return MixStateT(chain.tot + chain.mul * expr, chain.mul * ecMix);
  }
  FDEV MixStateT andCond(MixStateT chain, ValT cond, MixStateT inner) {
    return MixStateT(chain.tot + chain.mul * inner.tot * cond, chain.mul * inner.mul);
  }
};

template <typename ValT> struct SameTypeEqzHandler {
  using MixStateT = DefaultMixState<ValT>;
  ValT ecMix;

  FDEV SameTypeEqzHandler(ValT ecMix) : ecMix(ecMix) {}

  FDEV MixStateT getTrue() { return MixStateT(ValT(0), ValT(1)); }
  FDEV MixStateT andEqz(MixStateT chain, ValT expr) {
    return MixStateT(chain.tot + chain.mul * expr, chain.mul * ecMix);
  }
  FDEV MixStateT andCond(MixStateT chain, ValT cond, MixStateT inner) {
    return MixStateT(chain.tot + chain.mul * inner.tot * cond, chain.mul * inner.mul);
  }
};

template <typename ValT, typename ValExtT> struct DebugEqzHandler {
  using MixStateT = DefaultMixState<ValExtT>;
  ValExtT ecMix;

  DebugEqzHandler(ValExtT ecMix) : ecMix(ecMix) {}

  MixStateT getTrue() { return MixStateT(ValExtT(ValT(0)), ValExtT(ValT(1))); }
  MixStateT andEqz(MixStateT chain, ValT expr) {
    LOG(0, "EQZ: " << expr);
    return MixStateT(chain.tot + chain.mul * expr, chain.mul * ecMix);
  }
  MixStateT andEqz(MixStateT chain, ValExtT expr) {
    LOG(0, "EQZ: " << expr);
    return MixStateT(chain.tot + chain.mul * expr, chain.mul * ecMix);
  }
  MixStateT andCond(MixStateT chain, ValT cond, MixStateT inner) {
    auto ret = MixStateT(chain.tot + chain.mul * inner.tot * cond, chain.mul * inner.mul);
    LOG(0, "AND COND: " << ret.tot);
    return ret;
  }
};

template <typename RegT, typename ValT, typename ValExtT, typename EqzCtx> struct VerifyContext {
  using RegImpl = RegT;
  using ArgCountRegImpl = RegT;
  using ValImpl = ValT;
  using ValExtImpl = ValExtT;
  using C = VerifyContext;

  struct VerifyFwd {
    template <typename T, typename... Args>
    static void apply(MTHR VerifyContext& ctx, CONSTARG const char*, MDEV T& obj, Args... args) {
      VerifyFwd::apply(ctx, obj, args...);
    }

    template <typename T, typename... Args>
    FDEV static typename if_not_char<T, void>::type
    apply(MTHR VerifyContext& ctx, MDEV T& obj, Args... args) {
      obj.template applyInner<VerifyFwd>(ctx, args...);
      obj.verify(ctx, args...);
      obj.addArguments(ctx, args...);
    }

    template <typename T, size_t N, typename... Args>
    FDEV static typename if_not_char<T, void>::type
    apply(MTHR VerifyContext& ctx, MDEV T (&t)[N], Args... args) {
      for (size_t i = 0; i < N; i++) {
        VerifyFwd::apply(ctx, t[i], args...);
      }
    }
  };
  MTHR EqzCtx& eqzCtx;
  MDEV Top<C>* top;
  MDEV RegExt<C>* accum;
  MDEV RegExt<C>* prevAccum;
  MDEV Val<C>* globals;
  MDEV ValExt<C>* accMix;
  Val<C> x;

  typename EqzCtx::MixStateT outerMix;
  typename EqzCtx::MixStateT innerMix;

  Val<C> isValid = true;

  uint32_t accCol = 0;
  uint32_t accSubstep = 0;
  ValExt<C> accTot = ValExtT(0);
  Val<C> numers[2];
  ValExt<C> denoms[2];

  FDEV VerifyContext(MTHR EqzCtx& eqzCtx,
                     MDEV RegT* data,
                     MDEV RegT* accum,
                     MDEV RegT* prevAccum,
                     MDEV ValT* globals,
                     MDEV ValExtT* accMix,
                     ValT x)
      : eqzCtx(eqzCtx)
      , top(reinterpret_cast<MDEV Top<C>*>(data))
      , accum(reinterpret_cast<MDEV RegExt<C>*>(accum))
      , prevAccum(reinterpret_cast<MDEV RegExt<C>*>(prevAccum))
      , globals(globals)
      , accMix(accMix)
      , x(x)
      , outerMix(eqzCtx.getTrue())
      , innerMix(eqzCtx.getTrue()) {}

  // Main entry point
  FDEV typename EqzCtx::MixStateT verify() {
    // Verify the selector
    VerifyFwd::apply(*this, top->select);
    outerMix = innerMix;
// Verify inner data
#define BLOCK_TYPE(name, count)                                                                    \
  {                                                                                                \
    reset();                                                                                       \
    for (size_t i = 0; i < count; i++) {                                                           \
      isValid = top->mux.name.isValid[i].get();                                                    \
      VerifyFwd::apply(*this, top->mux.name.data[i]);                                              \
    }                                                                                              \
    finalize();                                                                                    \
    ValT cond = top->select.at(uint32_t(BlockType::name));                                         \
    outerMix = eqzCtx.andCond(outerMix, cond, innerMix);                                           \
  }
    BLOCK_TYPES
#undef BLOCK_TYPE
    // Verify accumTop
    // TODO: this is very ugly
    auto accumTop = reinterpret_cast<MDEV AccumTop<C>*>(reinterpret_cast<MDEV RegT*>(accum) +
                                                        MAX_ACCUM_PER_ROW);
    auto prevAccumTop = reinterpret_cast<MDEV AccumTop<C>*>(
        reinterpret_cast<MDEV RegT*>(prevAccum) + MAX_ACCUM_PER_ROW);
    innerMix = eqzCtx.getTrue();
    VerifyFwd::apply(*this, *accumTop, top, prevAccumTop, accMix[ACCUM_BIGINT_Z]);
    outerMix = eqzCtx.andCond(outerMix, ValT(1), innerMix);
    return outerMix;
  }

  FDEV void reset() {
    innerMix = eqzCtx.getTrue();
    accCol = 1;
    accSubstep = 0;
    accTot = ValExtT(0);
  }

  template <typename T> FDEV void eqz(T val) { innerMix = eqzCtx.andEqz(innerMix, val); }

  template <typename T> FDEV void push(const MTHR T& argument) { addArgument(isValid, argument); }

  template <typename T> FDEV void pull(const MTHR T& argument) { addArgument(-isValid, argument); }

  template <typename T> FDEV void addArgument(ValT count, const MTHR T& argument) {
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

template <typename RegT, typename ValT, typename ValExtT, typename EqzCtx>
FDEV typename EqzCtx::MixStateT verifyCircuitCtx(MTHR EqzCtx& eqzCtx,
                                                 MDEV RegT* data,
                                                 MDEV RegT* accum,
                                                 MDEV RegT* prevAccum,
                                                 MDEV ValT* globals,
                                                 MDEV ValExtT* accMix,
                                                 ValT x) {
  VerifyContext<RegT, ValT, ValExtT, EqzCtx> verifier(
      eqzCtx, data, accum, prevAccum, globals, accMix, x);
  return verifier.verify();
}

template <typename RegT,
          typename ValT,
          typename ValExtT,
          typename EqzCtx = DefaultEqzHandler<ValT, ValExtT>>
FDEV ValExtT verifyCircuit(MDEV RegT* data,
                           MDEV RegT* accum,
                           MDEV RegT* prevAccum,
                           MDEV ValT* globals,
                           MDEV ValExtT* accMix,
                           ValExtT ecMix,
                           ValT x) {
  EqzCtx eqzCtx(ecMix);
  VerifyContext<RegT, ValT, ValExtT, EqzCtx> verifier(
      eqzCtx, data, accum, prevAccum, globals, accMix, x);
  return verifier.verify().tot;
}
