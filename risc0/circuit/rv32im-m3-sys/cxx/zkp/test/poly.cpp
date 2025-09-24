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

#include "zkp/rng.h"
#include "zkp/poly.h"
#include <gtest/gtest.h>

namespace risc0 {

TEST(zkp, polyDiv) {
  size_t size = 16;
  Rng rng;
  std::vector<FpExt> poly(size);
  for (size_t i = 0; i < size; i++) {
    poly[i] = rng.rngFpExt();
  }
  FpExt z = rng.rngFpExt();
  FpExt fz = polyEval(poly, z);
  poly[0] -= fz;
  FpExt rem = polyDivide(poly.data(), size, z);
  ASSERT_EQ(rem, FpExt(0));
}

} // namespace risc0
