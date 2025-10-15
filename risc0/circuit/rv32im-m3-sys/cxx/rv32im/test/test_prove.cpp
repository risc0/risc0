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
#include "prove/rv32im.h"
#include "verify/rv32im.h"

namespace risc0 {

void runTestBinary(const std::string& elf, rv32im::HostIO& io, size_t po2) {
  IHalPtr hal = getCpuHal();
  LOG(2, "Loading ELF: '" << elf << "'");
  auto image = rv32im::MemoryImage::fromRawElf(elf);
  LOG(0, "Running test on " << elf);
  Rv32imProver prover(hal, po2, true);
  bool complete = prover.preflight(image, io);
  if (!complete) {
    std::cerr << "FAILED TO COMPLETE\n";
    exit(1);
  }
  WriteIop wiop;
  prover.prove(wiop);
  ReadIop riop(wiop.getTranscript().data(), wiop.getTranscript().size());
  LOG(0, "Running verify");
  verifyRv32im(riop, po2);
  LOG(0, "Verify succeeded");
}

void runTestBinary(const std::string& kernel,
                   const std::string& guest,
                   rv32im::HostIO& io,
                   size_t po2) {
  IHalPtr hal = getCpuHal();
  LOG(2, "Loading ELFs");
  auto image = rv32im::MemoryImage::fromElfs(kernel, guest);
  LOG(0, "Running test");
  Rv32imProver prover(hal, po2, true);
  bool complete = prover.preflight(image, io);
  if (!complete) {
    std::cerr << "FAILED TO COMPLETE\n";
    exit(1);
  }
  WriteIop wiop;
  prover.prove(wiop);
  ReadIop riop(wiop.getTranscript().data(), wiop.getTranscript().size());
  LOG(0, "Running verify");
  verifyRv32im(riop, po2);
  LOG(0, "Verify succeeded");
}

} // namespace risc0
