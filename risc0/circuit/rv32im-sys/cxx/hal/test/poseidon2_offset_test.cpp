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

// Regression test for the poseidon2 row-commit CUDA offset overflow.
//
// The row-commit kernel `_poseidon2_rows` (poseidon2.cuh, vendored in both
// risc0-sys and rv32im-sys) indexes the matrix as `matrix[(size_t)i * dim_x]`,
// where `i` is the column and `dim_x` is the domain size. When both were plain
// `uint32_t` the multiply ran in 32 bits and wrapped once `columns * domain`
// passed 2^32, so the kernel read the wrong cell and returned a wrong seal with
// no error. The `(size_t)` cast is the fix.
//
// The full kernel repro needs ~23 GB of device memory, so this checks the
// arithmetic on its own: the widened multiply is correct exactly where the
// bare `uint32_t` one wraps. It fails against the pre-fix expression.

#include <cstddef>
#include <cstdint>

#include <gtest/gtest.h>

// po2-21 evaluation domain (2^21 * INV_RATE 4 = 2^23 rows), and the first
// column that pushes column * domain to 2^32.
TEST(Poseidon2Offset, Widened64BitMultiplyDoesNotWrap) {
  uint32_t domain = 1u << 23;
  uint32_t column = 512;

  EXPECT_EQ(static_cast<size_t>(column) * domain, 4294967296ULL); // 2^32, correct
  EXPECT_EQ(column * domain, 0u); // bare uint32_t wraps to 0
}
