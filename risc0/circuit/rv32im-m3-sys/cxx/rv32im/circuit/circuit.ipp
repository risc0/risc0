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

#include "rv32im/circuit/circuit.h"

#define EQ(a, b) ctx.eqz((a) - (b))
#define EQZ(a) ctx.eqz(a)

#define GET_ARR(out, in, n)                                                                        \
  for (size_t i = 0; i < n; i++) {                                                                 \
    out[i] = in[i].get();                                                                          \
  }

#define SET_ARR(out, in, n)                                                                        \
  for (size_t i = 0; i < n; i++) {                                                                 \
    out[i].set(ctx, in[i]);                                                                        \
  }

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
