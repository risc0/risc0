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

#include "core/log.h"
#include "zkp/poly.h"

namespace risc0 {

FpExt polyEval(const std::vector<FpExt>& coeffs, Fp x) {
  FpExt tot;
  Fp pow(1);
  for (size_t i = 0; i < coeffs.size(); i++) {
    tot += coeffs[i] * pow;
    pow *= x;
  }
  return tot;
}

FpExt polyEval(const std::vector<FpExt>& coeffs, FpExt x) {
  FpExt tot;
  FpExt pow(Fp(1));
  for (size_t i = 0; i < coeffs.size(); i++) {
    tot += coeffs[i] * pow;
    pow *= x;
  }
  return tot;
}

std::vector<FpExt> polyInterpolate(const std::vector<FpExt>& xs, const std::vector<FpExt>& fxs) {
  if (xs.size() == 1) {
    return fxs;
  }
  if (xs.size() != 2) {
    throw std::runtime_error("Unimplemented");
  }
  FpExt c1 = (fxs[0] - fxs[1]) * inv(xs[0] - xs[1]);
  FpExt c0 = fxs[0] - c1 * xs[0];
  return { c0, c1 };
}

FpExt polyDivide(FpExt* coeffs, size_t deg, FpExt z) {
  FpExt cur;
  for (size_t i = deg; i-->0; ) {
    FpExt next = z * cur + coeffs[i];
    coeffs[i] = cur;
    cur = next;
  }
  return cur;
}

} // namespace risc0

