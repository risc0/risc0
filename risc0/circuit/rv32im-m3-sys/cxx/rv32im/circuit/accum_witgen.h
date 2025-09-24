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

template<size_t po2>
struct AccumWitgenContext {
  using C = AccumWitgenContext<po2>;
  static CONSTANT size_t numRows = (1 << po2);

  using ValImpl = Fp;
  using ValExtImpl = FpExt;

  // During accum witgen, set + get work as expected, arguments are still null
  struct RegImpl {
    FDEV void set(CTX, Fp val) DEV {
      data[0] = val;
    }
    FDEV Fp get() DEV {
      return data[0];
    }
    template<typename T> FDEV void applyInner(MTHR C& ctx) DEV {}
    FDEV void addArguments(MTHR C& ctx) DEV {}
    Fp data[numRows];
  };
  using ArgCountRegImpl = RegImpl;

  const MDEV Fp* globals;
  const MDEV FpExt* accMix;
  MDEV Fp* accum;
  Fp isValid;
  Fp x;
  FpExt tot;
  FpExt cur;
  size_t col = 1;
  size_t inner = 0;

  template<typename T>
  FDEV inline void push(const MTHR T& argument) {
    addArgument(isValid, argument);
  }
  template<typename T>
  FDEV inline void pull(const MTHR T& argument) {
    addArgument(-isValid, argument);
  }
  template<typename T>
  FDEV inline void addArgument(Fp count, const MTHR T& argument) {
    FpExt flat = flattenArgument<T, C>(argument, accMix + 1);
    cur += inv(accMix[0] - flat) * count;
    inner++;
    if (inner == 2) {
      writeFpExt();
    }
  }
  FDEV void writeFpExt() {
    accum[(4*col + 0) * numRows] = elem(cur, 0);
    accum[(4*col + 1) * numRows] = elem(cur, 1);
    accum[(4*col + 2) * numRows] = elem(cur, 2);
    accum[(4*col + 3) * numRows] = elem(cur, 3);
    col++;
    inner = 0;
    tot += cur;
    cur = FpExt();
  }
  FDEV void done() {
    if (inner != 0) {
      writeFpExt();
    }
    accum[0 * numRows] = elem(tot, 0);
    accum[1 * numRows] = elem(tot, 1);
    accum[2 * numRows] = elem(tot, 2);
    accum[3 * numRows] = elem(tot, 3);
  }
  FDEV inline Fp globalGet(uint32_t offset) {
    return globals[offset];
  }
  FDEV inline Fp getX() { return x; }
};

struct AddArgumentsFwd {
  template<typename T, typename C, typename... Args>
  FDEV static void apply(MTHR C& ctx, MDEV T& obj, Args... args) {
    obj.template applyInner<AddArgumentsFwd>(ctx, args...);
    obj.addArguments(ctx, args...);
  }

  template <typename T, typename C, size_t N>
  FDEV static void apply(MTHR C& ctx, MDEV T (&t)[N]) {
    for (size_t i = 0; i < N; i++) {
      AddArgumentsFwd::apply(ctx, t[i]);
    }
  }
};

template<size_t po2>
FDEV void computeRowPhase1(MDEV Fp* accum,
                const MDEV Fp* dataConst,
                const MDEV Fp* globals,
                const MDEV FpExt* accMix,
                Fp rou,
                size_t row) {
  // TODO: Actually properly 'constify' get / verify / etc
  using C = AccumWitgenContext<po2>;
  constexpr size_t numRows = (1 << po2);
  MDEV Fp* data = const_cast<MDEV Fp*>(dataConst);
  MDEV Top<C>* top = reinterpret_cast<MDEV Top<C>*>(data + row);
  size_t idx = top->select.get().asUInt32();
  BlockType type = static_cast<BlockType>(idx);
  C ctx;
  ctx.globals = globals;
  ctx.accMix = accMix;
  ctx.accum = accum + row;
  ctx.isValid = 1;
  ctx.x = pow(rou, row);
  switch(type) {
#define BLOCK_TYPE(name, count) \
    case BlockType::name: { \
      for (size_t i = 0; i < count; i++) { \
        ctx.isValid = top->mux.name.isValid[i].get(); \
        AddArgumentsFwd::apply(ctx, top->mux.name.data[i]); \
      }} \
      break;
    BLOCK_TYPES
#undef BLOCK_TYPE
    case BlockType::Empty:
      break;
  }
  ctx.done();
  // Do Accum top
  MDEV AccumTop<C>* accumTop = reinterpret_cast<MDEV AccumTop<C>*>(
      accum + MAX_ACCUM_PER_ROW * numRows + row);
  accumTop->setPhase1(ctx, top, accMix[ACCUM_BIGINT_Z]);
}

template<size_t po2>
FDEV void computeRowPhase2(MDEV Fp* accum,
                const MDEV Fp* dataConst,
                const MDEV Fp* globals,
                const MDEV FpExt* accMix,
                Fp rou,
                size_t row) {
  // TODO: Actually properly 'constify' get / verify / etc
  using C = AccumWitgenContext<po2>;
  constexpr size_t numRows = (1 << po2);
  MDEV Fp* data = const_cast<MDEV Fp*>(dataConst);
  C ctx;  // Not actually used in phase2, but needs to be passed to keep API happy

  MDEV Top<C>* top = reinterpret_cast<MDEV Top<C>*>(data + row);
  MDEV AccumTop<C>* accumTop = reinterpret_cast<MDEV AccumTop<C>*>(
      accum + MAX_ACCUM_PER_ROW * numRows + row);
  // If simple (i.e. can be set by phase 1), return
  if (accumTop->isSimple()) { return; }
  FpExt z = accMix[ACCUM_BIGINT_Z];
  FpExt cur(1);
  FpExt neg;
  for (size_t i = 0; i < 16; i++) {
    neg += cur * Fp(128);
    cur *= z;
  }
  FpExt z16 = cur;
  size_t prevRow = (row + numRows - 1) % numRows;
  MDEV AccumTop<C>* accumTopPrev = reinterpret_cast<MDEV AccumTop<C>*>(
      accum + MAX_ACCUM_PER_ROW * numRows + prevRow);
  // If prev is not simple, let earlier node handle
  if (!accumTopPrev->isSimple()) { return; }
  // Otherwise loop until we get back to a simple node
  while(1) {
    accumTop->setPhase2(ctx, top, accumTopPrev, z16, neg);
    row++;
    row %= numRows;
    top = reinterpret_cast<MDEV Top<C>*>(data + row);
    accumTop = reinterpret_cast<MDEV AccumTop<C>*>(
      accum + MAX_ACCUM_PER_ROW * numRows + row);
    if (accumTop->isSimple()) { break; }
    prevRow = (row + numRows - 1) % numRows;
    accumTopPrev = reinterpret_cast<MDEV AccumTop<C>*>(
      accum + MAX_ACCUM_PER_ROW * numRows + prevRow);
  }
}

