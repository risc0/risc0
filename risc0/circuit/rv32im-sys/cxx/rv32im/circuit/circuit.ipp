// Copyright 2026 RISC Zero, Inc.
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

#include "rv32im/circuit/circuit.h"

#include "rv32im/argument/argument.h"
#include "rv32im/base/opt.h"

#ifdef IN_VERIFY
#define EQ(a, b)                                                                                   \
  do {                                                                                             \
    Fp aVal = (a);                                                                                 \
    Fp bVal = (b);                                                                                 \
    if (aVal != bVal) {                                                                            \
      LOG(0,                                                                                       \
          "INVALID EQ: " << __FILE__ << ": " << __LINE__ << ", " << #a << " [ actual = " << aVal   \
                         << "] != " << #b << " [ actual = " << bVal << "]");                       \
    }                                                                                              \
    ctx.eqz(aVal - bVal);                                                                          \
  } while (0)
#define EQZ(a)                                                                                     \
  do {                                                                                             \
    Fp aVal = (a);                                                                                 \
    if (aVal != 0) {                                                                               \
      LOG(0,                                                                                       \
          "INVALID EQZ: " << __FILE__ << ": " << __LINE__ << ", " << #a << " [ actual = " << aVal  \
                          << "]");                                                                 \
    }                                                                                              \
    ctx.eqz(aVal);                                                                                 \
  } while (0)
#else
#define EQ(a, b) ctx.eqz((a) - (b))
#define EQZ(a) ctx.eqz(a)
#endif

#define GET_ARR(out, in, n)                                                                        \
  for (size_t i = 0; i < n; i++) {                                                                 \
    out[i] = in[i].get();                                                                          \
  }

#define SET_ARR(out, in, n)                                                                        \
  for (size_t i = 0; i < n; i++) {                                                                 \
    out[i].set(ctx, in[i]);                                                                        \
  }

#define GLOBAL_OFFSET(member)                                                                      \
  (reinterpret_cast<MDEV Fp*>(&reinterpret_cast<MDEV Globals*>(0x10000)->member) -                 \
   reinterpret_cast<MDEV Fp*>(0x10000))
#define GLOBAL_GET(member) ctx.globalGet(GLOBAL_OFFSET(member))
#define GLOBAL_SET(member, val) ctx.globalSet(GLOBAL_OFFSET(member), (val))

template <typename T, typename U> struct if_not_char {
  using type = U;
};
template <typename U> struct if_not_char<char, U> {};
template <typename U> struct if_not_char<const char, U> {};

#include "rv32im/circuit/bigint.ipp"
#include "rv32im/circuit/bits.ipp"
#include "rv32im/circuit/decode.ipp"
#include "rv32im/circuit/ecall.ipp"
#include "rv32im/circuit/globals.ipp"
#include "rv32im/circuit/inst.ipp"
#include "rv32im/circuit/io.ipp"
#include "rv32im/circuit/is_zero.ipp"
#include "rv32im/circuit/lookups.ipp"
#include "rv32im/circuit/mem.ipp"
#include "rv32im/circuit/mul.ipp"
#include "rv32im/circuit/one_hot.ipp"
#include "rv32im/circuit/paging.ipp"
#include "rv32im/circuit/poseidon2.ipp"
#include "rv32im/circuit/top.ipp"
#include "rv32im/circuit/u32.ipp"
#include "rv32im/circuit/units.ipp"
