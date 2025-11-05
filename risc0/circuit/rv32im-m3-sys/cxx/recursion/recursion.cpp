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

#include <iostream>
#include <string>

using namespace risc0;

class TestIO : public rv32im::HostIO {
public:
  std::vector<uint8_t> data;
  uint32_t offset = 0;
  uint32_t onRead(uint32_t fd, uint8_t* buf, uint32_t len) override {
    LOG(0, "data.size() = " << data.size() << ", offset = " << offset << ", len = " << len);
    if (offset + len > data.size()) {
      throw std::runtime_error("Overread");
    }
    memcpy(buf, data.data() + offset, len);
    offset += len;
    return len;
  }
  uint32_t onWrite(uint32_t fd, const uint8_t* buf, uint32_t len) override {
    LOG(fd, std::string(reinterpret_cast<const char*>(buf), len));
    return len;
  }
};

std::vector<Fp> doProof() {
  LOG(0, "Making proof to pass to recursion");
  uint32_t po2 = 12;
  IHalPtr hal = getCpuHal();
  rv32im::NullHostIO io;
  std::map<uint32_t, uint32_t> words;
  rv32im::loadKernelV2(words, "rv32im/test/smoke_kernel");
  auto image = rv32im::MemoryImage::fromWords(words);
  Rv32imProver prover(hal, po2, false);
  prover.preflight(image, io);
  WriteIop wiop;
  prover.prove(wiop);
  return wiop.getTranscript();
}

int main() {
  TestIO io;
  auto transcript = doProof();
  io.data.resize(sizeof(uint32_t) + transcript.size() * sizeof(Fp));
  *reinterpret_cast<uint32_t*>(io.data.data()) = transcript.size();
  LOG(0, "Transcript size = " << transcript.size());
  memcpy(io.data.data() + sizeof(uint32_t), transcript.data(), transcript.size() * sizeof(Fp));
  LOG(0, "Running recursion");
  uint32_t po2 = 20;
  IHalPtr hal = getCpuHal();
  std::map<uint32_t, uint32_t> words;
  rv32im::loadUserMachineV2(words, "recursion/recursion_kernel", "recursion/recursion_guest");
  auto image = rv32im::MemoryImage::fromWords(words);
  Rv32imProver prover(hal, po2, true);
  uint32_t segments = 0;
  uint32_t cycles = 0;
  while (true) {
    uint32_t curCycles;
    bool complete = prover.preflight(image, io, &curCycles);
    segments++;
    LOG(0, "Another segment");
    cycles += curCycles;
    if (complete) {
      break;
    }
  }
  LOG(0, "Total segments = " << segments);
  LOG(0, "Total cycles = " << cycles);
  return 0;
}
