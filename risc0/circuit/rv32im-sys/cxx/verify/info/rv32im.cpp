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

#include "verify/info/info.h"

#include "rv32im/base/constants.h"
#include "rv32im/emu/blocks.h"
#include "zkp/params.h"
#include "zkp/rou.h"

namespace risc0 {

using namespace rv32im;

void setupVerifyInfo(VerifyCircuitInfo& ci) {
  ci.groups.resize(2);
  size_t dataCols = computeMaxDataPerRow();
  VerifyGroupInfo& dataInfo = ci.groups[0];
  dataInfo.globalCount = NUM_GLOBALS;
  dataInfo.mixCount = 0;
  for (size_t i = 0; i < dataCols; i++) {
    ci.taps.addTap(0, i, 0);
  }
  size_t accumCols = computeTotalAccum();
  size_t accumNormalCols = computeMaxAccumPerRow();
  VerifyGroupInfo& accumInfo = ci.groups[1];
  accumInfo.globalCount = 0;
  accumInfo.mixCount = ACCUM_MIX_SIZE;
  for (size_t i = 0; i < accumCols; i++) {
    ci.taps.addTap(1, i, 0);
    if (i < 4 || i >= accumNormalCols) {
      ci.taps.addTap(1, i, 1);
    }
  }
  ci.taps.done();
  ci.evalCheck = [](FpExt* evals, Fp* globals, FpExt* mix, FpExt ecMix, FpExt z) {
    return computeConstraintPoly(evals, globals, mix, ecMix, z);
  };
}

} // namespace risc0
