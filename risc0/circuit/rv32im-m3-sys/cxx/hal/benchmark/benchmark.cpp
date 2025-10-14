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
#include "core/util.h"
#include "prove/rv32im.h"

using namespace risc0;
using namespace risc0::rv32im;

int main() {
  LOG(0, "Opening GPU");
  IHalPtr hal = getGpuHal();
  LOG(0, "Loading elf");
  auto image = MemoryImage::fromRawElf("rv32im/test/benchmark_kernel");
  size_t po2 = 20;
  NullHostIO io;
  Rv32imProver prover(hal, po2);
  for (size_t i = 0; i < 3; i++) {
    LOG(0, "Preflight");
    prover.preflight(image, io);
    LOG(0, "Proving");
    WriteIop writeIop;
    prover.prove(writeIop);
  }
  LOG(0, "Done");
}
