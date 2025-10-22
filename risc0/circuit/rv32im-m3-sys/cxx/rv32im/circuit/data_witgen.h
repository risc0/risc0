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

// During data witgen, we ignore eqz, and all arguments
template <size_t po2> struct DataWitgenContext {
  using C = DataWitgenContext<po2>;
  static CONSTANT size_t numRows = (1 << po2);

  using ValImpl = Fp;
  using ValExtImpl = FpExt;
  struct RegImpl {
    FDEV void set(MTHR C& ctx, Fp val) DEV { data[0] = val; }
    FDEV void finalize(MTHR C& ctx) DEV {}
    FDEV Fp get() DEV { return data[0]; }
    template <typename T> FDEV void applyInner(MTHR C& ctx) DEV {}
    Fp data[numRows];
  };
  struct ArgCountRegImpl {
    FDEV void set(MTHR C& ctx, Fp val) DEV {
      if (ctx.valid) {
        this->data[0] = val;
      } else {
        this->data[0] = 0;
      }
    }
    FDEV void finalize(MTHR C& ctx) DEV {}
    FDEV Fp get() DEV { return data[0]; }
    template <typename T> FDEV void applyInner(MTHR C& ctx) DEV {}
    Fp data[numRows];
  };

  bool valid = true;
  FDEV inline void tableAdd(uint32_t offset, uint32_t val) {
    if (valid) {
      ATOMIC_ADD(tables[offset], val);
    }
  }
  FDEV inline uint32_t tableGet(uint32_t offset) { return ATOMIC_GET(tables[offset]); }
  FDEV inline void globalSet(uint32_t offset, Fp val) { globals[offset] = val; }
  FDEV inline Fp globalGet(uint32_t offset) { return globals[offset]; }
  FDEV inline Fp getX() { return x; }
  Fp x;
  MDEV ATOMIC_U32* tables;
  MDEV Fp* globals;
};

template <size_t po2>
FDEV void computeRowSet(MDEV Fp* data,
                        MDEV Fp* globals,
                        const MDEV RowInfo* info,
                        const MDEV uint32_t* aux,
                        MDEV uint32_t* tables,
                        Fp rou,
                        size_t row) {
  using C = DataWitgenContext<po2>;
  C ctx;
  ctx.tables = reinterpret_cast<MDEV ATOMIC_U32*>(tables);
  ctx.globals = globals;
  ctx.x = pow(rou, row);
  BlockType type = static_cast<BlockType>(info[row].rowType);
  MDEV Top<C>* top = reinterpret_cast<MDEV Top<C>*>(data + row);
  switch (type) {
#define BLOCK_TYPE(name, count)                                                                    \
  case BlockType::name: {                                                                          \
    const MDEV name##Witness* typedWitness =                                                       \
        reinterpret_cast<const MDEV name##Witness*>(aux + info[row].auxOffset);                    \
    top->select.set(ctx, static_cast<size_t>(type));                                               \
    for (size_t i = 0; i < count; i++) {                                                           \
      if (i < info[row].blockCount) {                                                              \
        ctx.valid = true;                                                                          \
        top->mux.name.isValid[i].set(ctx, 1);                                                      \
        top->mux.name.data[i].set(ctx, typedWitness[i]);                                           \
      } else {                                                                                     \
        ctx.valid = false;                                                                         \
        top->mux.name.isValid[i].set(ctx, 0);                                                      \
        top->mux.name.data[i].set(ctx, typedWitness[0]);                                           \
      }                                                                                            \
    }                                                                                              \
  } break;
    BLOCK_TYPES
#undef BLOCK_TYPE
  case BlockType::Empty:
    top->select.set(ctx, static_cast<size_t>(BlockType::Empty));
    break;
  }
}

struct FinalizeFwd {
  template <typename T, typename C, typename... Args>
  FDEV static void apply(MTHR C& ctx, MDEV T& obj, Args... args) {
    obj.template applyInner<FinalizeFwd>(ctx, args...);
    obj.finalize(ctx);
  }

  template <typename T, typename C, size_t N, typename... Args>
  FDEV static void apply(MTHR C& ctx, MDEV T (&t)[N], Args... args) {
    for (size_t i = 0; i < N; i++) {
      FinalizeFwd::apply(ctx, t[i], args...);
    }
  }
};

template <size_t po2>
FDEV void computeRowFinalize(MDEV Fp* io,
                             MDEV Fp* globals,
                             const MDEV RowInfo* info,
                             const MDEV uint32_t* aux,
                             MDEV uint32_t* tables,
                             Fp rou,
                             size_t row) {
  using C = DataWitgenContext<po2>;
  C ctx;
  ctx.tables = reinterpret_cast<MDEV ATOMIC_U32*>(tables);
  ctx.globals = globals;
  ctx.x = pow(rou, row);
  BlockType type = static_cast<BlockType>(info[row].rowType);
  MDEV Top<C>* top = reinterpret_cast<MDEV Top<C>*>(io + row);
  switch (type) {
#define BLOCK_TYPE(name, count)                                                                    \
  case BlockType::name: {                                                                          \
    for (size_t i = 0; i < count; i++) {                                                           \
      ctx.valid = i < info[row].blockCount;                                                        \
      FinalizeFwd::apply(ctx, top->mux.name.data[i]);                                              \
    }                                                                                              \
  } break;
    BLOCK_TYPES
#undef BLOCK_TYPE
  case BlockType::Empty:
    break;
  }
}
