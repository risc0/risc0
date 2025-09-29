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

#include <gtest/gtest.h>

#include <set>
#include <random>

#include "prove/write_iop.h"

using namespace risc0;

TEST(write_iop, matches_rust) {
  // Do a few IOP operations and check that they match the Rust implementation
  WriteIop iop;
  iop.commit(Digest::zero());
  Fp x = iop.rngFp();
  assert(x.asUInt32() == 972705262);
  Digest d = {x.asUInt32(), 2, 3, 4, 5, 6, 7, 8};
  iop.commit(d);
  x = iop.rngFp();
  assert(x.asUInt32() == 1771240996);
}
