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

#include "core/log.h"
#include "core/util.h"
#include "hal/hal.h"
#include "hal/po2s.h"
#include "zkp/fp.h"
#include "zkp/rou.h"

namespace risc0 {

#define PO2(x)                                                                                     \
  void accum_witgen_cpu_##x(                                                                       \
      Fp* accum, const Fp* data, const Fp* globals, const FpExt* accMix, Fp rou);
PO2S
#undef PO2

    void
    computeAccumWitnessCpu(
        Fp* accum, const Fp* data, const Fp* globals, const FpExt* accMix, size_t numRows) {
  size_t po2 = log2Ceil(numRows);
  if (po2 < MIN_PO2 || po2 > MAX_PO2) {
    LOG(0, "PO2 = " << po2);
    throw std::runtime_error("Invalid po2");
  }
  if (numRows != (size_t(1) << po2)) {
    throw std::runtime_error("numRows is not a power of 2");
  }

  switch (po2) {
#define PO2(x)                                                                                     \
  case x:                                                                                          \
    accum_witgen_cpu_##x(accum, data, globals, accMix, ROU_FWD[po2]);                              \
    break;
    PO2S
#undef PO2
        default : throw std::runtime_error("Unreachable");
  }
}

} // namespace risc0
