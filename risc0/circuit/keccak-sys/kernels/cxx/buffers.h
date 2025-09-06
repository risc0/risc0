// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT
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

#include "fp.h"

#include <cstdio>
#include <stdexcept>

namespace risc0 {

struct Buffer {
  Fp* buf;
  size_t rows;
  size_t cols;
  bool checkedReads;

  void set(size_t row, size_t col, Fp val) {
    Fp& elem = buf[col * rows + row];
    if (elem != Fp::invalid() && elem != val) {
      printf("set(row: %zu, col: %zu, val: 0x%08x) cur: 0x%08x\n",
             row,
             col,
             val.asUInt32(),
             elem.asUInt32());
      throw std::runtime_error("Inconsistent set");
    }
    // printf("set(row: %zu, col: %zu, val: 0x%08x)\n", row, col, val.asUInt32());
    elem = val;
  }

  Fp get(size_t row, size_t col) {
    Fp ret = buf[col * rows + row];
    if (ret == Fp::invalid() && checkedReads) {
      printf("get(row: %zu, col: %zu) -> 0x%08x\n", row, col, ret.asRaw());
      throw std::runtime_error("Read of unset value");
    }
    // printf("get(row: %zu, col: %zu) -> 0x%08x\n", row, col, ret.asUInt32());
    return ret;
  }
};

} // namespace risc0
