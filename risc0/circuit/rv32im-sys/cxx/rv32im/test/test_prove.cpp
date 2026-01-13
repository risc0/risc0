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
#include "prove/rv32im.h"
#include "verify/rv32im.h"

namespace risc0 {

void runTest(rv32im::MemoryImage& image, rv32im::HostIO& io, size_t po2) {
  IHalPtr hal = getCpuHal();
  // IHalPtr hal = getGpuHal();
  Rv32imProver prover(hal, po2, true);
  auto preflightData = preflight(po2, image, io);
  if (!preflightData->isFinal) {
    std::cerr << "FAILED TO COMPLETE\n";
    exit(1);
  }
  WriteIop wiop;
  prover.prove(wiop, *preflightData);
  ReadIop riop(wiop.getTranscript().data(), wiop.getTranscript().size());
  verifyRv32im(riop, po2);
}

} // namespace risc0
