// Copyright 2026 RISC Zero, Inc.
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

#include "fp.h"

#include <cassert>
#include <cstdio>

namespace risc0::circuit::keccak::cuda {

struct Buffer {
  Fp* buf;
  size_t rows;
  size_t cols;
  bool checkedReads;

  __device__ void set(size_t row, size_t col, Fp val) {
    Fp& elem = buf[col * rows + row];
    if (elem != Fp::invalid() && elem != val) {
      printf("set(row: %lu, col: %lu, val: 0x%08x) cur: 0x%08x\n",
             row,
             col,
             val.asUInt32(),
             elem.asUInt32());
      assert(false && "Inconsistent set");
    }
    // printf("set(row: %lu, col: %lu, val: 0x%08x)\n", row, col, val.asUInt32());
    elem = val;
  }

  __device__ Fp get(size_t row, size_t col) {
    Fp ret = buf[col * rows + row];
    if (ret == Fp::invalid() && checkedReads) {
      printf("get(row: %lu, col: %lu) -> 0x%08x\n", row, col, ret.asRaw());
      assert(false && "Read of unset value");
    }
    // printf("get(row: %lu, col: %lu) -> 0x%08x\n", row, col, ret.asUInt32());
    return ret;
  }
};

} // namespace risc0::circuit::keccak::cuda
