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

#include "rv32im/emu/blocks.h"

#include "rv32im/circuit/verify.h"

namespace risc0::rv32im {

namespace {

// Wrap FpExt to make sure we are doing only what we intend
struct PolyVal {
  FpExt val;

  PolyVal() {}
  PolyVal(uint32_t val) : val(val) {}
  PolyVal(Fp val) : val(val) {}
  explicit PolyVal(FpExt val) : val(val) {}

  PolyVal operator+(const PolyVal& rhs) const { return PolyVal(val + rhs.val); }
  PolyVal operator-(const PolyVal& rhs) const { return PolyVal(val - rhs.val); }
  PolyVal operator*(const PolyVal& rhs) const { return PolyVal(val * rhs.val); }
  PolyVal operator-() const { return PolyVal(-val); }
  PolyVal& operator+=(const PolyVal& rhs) {
    val += rhs.val;
    return *this;
  }
  PolyVal& operator*=(const PolyVal& rhs) {
    val *= rhs.val;
    return *this;
  }
};

struct PolyValExt {
  FpExt val;

  PolyValExt() {}
  explicit PolyValExt(FpExt val) : val(val) {}
  explicit PolyValExt(PolyVal val) : val(val.val) {}
  explicit PolyValExt(PolyVal e0, PolyVal e1, PolyVal e2, PolyVal e3)
      : val(e0.val * FpExt(1, 0, 0, 0) + e1.val * FpExt(0, 1, 0, 0) + e2.val * FpExt(0, 0, 1, 0) +
            e3.val * FpExt(0, 0, 0, 1)) {}
  explicit PolyValExt(uint32_t x) : val(x) {}

  PolyValExt operator+(const PolyValExt& rhs) const { return PolyValExt(val + rhs.val); }
  PolyValExt operator-(const PolyValExt& rhs) const { return PolyValExt(val - rhs.val); }
  PolyValExt operator*(const PolyVal& rhs) const { return PolyValExt(val * rhs.val); }
  PolyValExt operator*(const PolyValExt& rhs) const { return PolyValExt(val * rhs.val); }
  PolyValExt& operator+=(const PolyVal& rhs) {
    val += rhs.val;
    return *this;
  }
  PolyValExt& operator+=(const PolyValExt& rhs) {
    val += rhs.val;
    return *this;
  }
  PolyValExt operator*=(const PolyVal& rhs) {
    val *= rhs.val;
    return *this;
  }
  PolyValExt operator*=(const PolyValExt& rhs) {
    val *= rhs.val;
    return *this;
  }
};

struct PolyReg {
  PolyVal get() { return value; }
  template <typename T, typename C> void applyInner(C& ctx) {}
  template <typename C> void verify(C& ctx) {}
  template <typename C> void addArguments(C& ctx) {}

  PolyVal value;
};

} // namespace

FpExt computeConstraintPoly(
    const FpExt* eval, const Fp* globals, const FpExt* accMix, FpExt ecMix, FpExt z) {
  size_t dataCols = computeMaxDataPerRow();
  size_t accumCols = computeTotalAccum();
  size_t accumNormalCols = computeMaxAccumPerRow();
  FpExt* data = const_cast<FpExt*>(eval);
  const FpExt* accumBase = eval + dataCols;
  std::vector<FpExt> accum;
  std::vector<FpExt> prevAccum;
  size_t offset = 0;
  for (size_t i = 0; i < accumCols; i++) {
    accum.push_back(accumBase[offset++]);
    if (i < 4 || i >= accumNormalCols) {
      prevAccum.push_back(accumBase[offset++]);
    } else {
      prevAccum.push_back(FpExt(0));
    }
  }
  std::vector<PolyVal> gvals;
  for (size_t i = 0; i < NUM_GLOBALS; i++) {
    gvals.push_back(PolyVal(globals[i]));
  }
  PolyValExt val = verifyCircuit(reinterpret_cast<PolyReg*>(data),
                                 reinterpret_cast<PolyReg*>(accum.data()),
                                 reinterpret_cast<PolyReg*>(prevAccum.data()),
                                 gvals.data(),
                                 reinterpret_cast<PolyValExt*>(const_cast<FpExt*>(accMix)),
                                 PolyValExt(ecMix),
                                 PolyVal(Fp(3) * z));
  return val.val;
}

} // namespace risc0::rv32im
