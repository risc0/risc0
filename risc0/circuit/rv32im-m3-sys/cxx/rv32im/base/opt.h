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

template <typename T> struct OptSize {};

#define IMPL_SIZE(T, L)                                                                            \
  template <> struct OptSize<T> {                                                                  \
    static CONSTANT int32_t value = uint32_t(L) + 1;                                               \
  }

enum InstKind {
  INST_REG,
  INST_IMM,
  INST_LOAD,
  INST_STORE,
  INST_BRANCH,
  INST_JAL,
  INST_JALR,
  INST_LUI,
  INST_AUIPC,
  INST_ECALL,
};

IMPL_SIZE(InstKind, INST_ECALL);

enum UnitKind {
  UNIT_ADDSUB,
  UNIT_BIT,
  UNIT_LT,
  UNIT_MUL,
  UNIT_DIV,
  UNIT_SHIFT,
};

IMPL_SIZE(UnitKind, UNIT_SHIFT);

enum OutKind {
  OUT_0,
  OUT_1,
};

IMPL_SIZE(OutKind, OUT_1);

enum AsKind {
  AS_ADD,
  AS_SUB,
};

IMPL_SIZE(AsKind, AS_SUB);

enum BrKind {
  BR_Z,
  BR_NZ,
};

IMPL_SIZE(BrKind, BR_NZ);

enum LoadKind {
  LOAD_LB,
  LOAD_LH,
  LOAD_LW,
  LOAD_LBU,
  LOAD_LHU,
};

IMPL_SIZE(LoadKind, LOAD_LHU);

enum StoreKind {
  STORE_SB,
  STORE_SH,
  STORE_SW,
};

IMPL_SIZE(StoreKind, STORE_SW);

enum BitKind {
  BIT_XOR,
  BIT_OR,
  BIT_AND,
};

IMPL_SIZE(BitKind, BIT_AND);

enum MulKind {
  MUL_SS,
  MUL_SU,
  MUL_UU,
};

IMPL_SIZE(MulKind, MUL_UU);

enum DivKind {
  DIV_U,
  DIV_S,
};

IMPL_SIZE(DivKind, DIV_S);

enum ShiftKind {
  SHIFT_LL,
  SHIFT_RL,
  SHIFT_RA,
};

IMPL_SIZE(ShiftKind, SHIFT_RA);

struct Option {
  uint32_t val;

  FDEV constexpr Option() : val(0) {}
  FDEV constexpr Option(uint32_t val) : val(val) {}

  template <typename T> FDEV constexpr bool is(T cmp) const {
    return (val % OptSize<T>::value) == uint32_t(cmp);
  }

  template <typename T> FDEV constexpr T peek() const { return T(val % OptSize<T>::value); }

  template <typename T> FDEV constexpr T pop() {
    T ret = peek<T>();
    val /= OptSize<T>::value;
    return ret;
  }

  template <typename T> FDEV constexpr Option popRet() const {
    return Option(val / OptSize<T>::value);
  }

  template <typename T> FDEV constexpr void push(T t) {
    val *= OptSize<T>::value;
    val += uint32_t(t);
  }
};

FDEV constexpr inline Option EncodeOptions() {
  return Option();
}

template <typename T, typename... Rest>
FDEV constexpr inline Option EncodeOptions(T a, Rest... args) {
  Option r = EncodeOptions(args...);
  r.push(a);
  return r;
}
