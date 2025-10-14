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

#include "rv32im/circuit/verify.h"

template <size_t po2> struct EvalCheckReg {
  static CONSTANT size_t numRows = (1 << (po2 + 2));

  FDEV Fp get() DEV { return data[0]; }
  template <typename T, typename C> FDEV void applyInner(MTHR C& ctx) DEV {}
  template <typename C> FDEV void verify(MTHR C& ctx) DEV {}
  template <typename C> FDEV void addArguments(MTHR C& ctx) DEV {}
  Fp data[numRows];
};

template <size_t po2>
FDEV void computeRow(MDEV Fp* check,
                     const MDEV Fp* dataConst,
                     const MDEV Fp* accumConst,
                     const MDEV Fp* globals,
                     const MDEV FpExt* accMix,
                     FpExt ecMix,
                     Fp rou,
                     uint row) {
  using RegT = EvalCheckReg<po2>;
  constexpr size_t numRows = (1 << (po2 + 2));
  size_t back1 = (row + numRows - 4) % numRows;
  Fp x = Fp(3) * pow(rou, row);
  FpExt ret = verifyCircuit<RegT, Fp, FpExt>(
      reinterpret_cast<MDEV RegT*>(const_cast<MDEV Fp*>(dataConst) + row),
      reinterpret_cast<MDEV RegT*>(const_cast<MDEV Fp*>(accumConst) + row),
      reinterpret_cast<MDEV RegT*>(const_cast<MDEV Fp*>(accumConst) + back1),
      const_cast<MDEV Fp*>(globals),
      const_cast<MDEV FpExt*>(accMix),
      ecMix,
      x);
  // Divide by 3x^n - 1: In reality this simplifies for each po2 to
  // multiplication by 4 constants, one at each row % 4, but it's annoying to
  // precompute + pass them, and impact of this code relative to the entire
  // validity polynomial is small
  Fp y = pow(x, 1 << po2);
  Fp quot = inv(y - 1);
  check += row;
  for (size_t i = 0; i < 4; i++) {
    check[i * numRows] = elem(ret, i) * quot;
  }
}
