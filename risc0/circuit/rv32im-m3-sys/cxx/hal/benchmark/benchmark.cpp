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

#include <chrono>

#include "core/log.h"
#include "core/util.h"
#include "prove/rv32im.h"

using namespace risc0;
using namespace risc0::rv32im;

int main() {
  LOG(0, "Opening GPU");
  IHalPtr hal = getGpuHal();
  LOG(0, "Loading elf");
  std::map<uint32_t, uint32_t> words;
  rv32im::loadKernelV2(words, "rv32im/test/benchmark_kernel");
  auto image = MemoryImage::fromWords(words);
  size_t po2 = 20;
  NullHostIO io;
  Rv32imProver prover(hal, po2);
  for (size_t i = 0; i < 3; i++) {
    LOG(0, "Preflight");
    auto preflightData = preflight(po2, image, io);
    using time_point = std::chrono::time_point<std::chrono::high_resolution_clock>;
    LOG(0, "Proving " << preflightData.cycles << " cycles");
    static time_point pre = std::chrono::high_resolution_clock::now();
    WriteIop writeIop;
    prover.prove(writeIop, preflightData);
    static time_point post = std::chrono::high_resolution_clock::now();
    auto diff = std::chrono::duration<double>(post - pre).count();
    LOG(0, "MCycles/second = " << double(preflightData.cycles) / 1000000.0 / diff);
  }
  LOG(0, "Done");
}
