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

#include <random>

#include "hal/dual/dual.h"
#include "prove/rv32im.h"
#include "verify/rv32im.h"

using namespace risc0;

void testProve(IHalPtr hal) {
  size_t po2 = 12;
  Rv32imProver prover(hal, po2);
  LOG(0, "Loading elf");
  std::map<uint32_t, uint32_t> words;
  rv32im::loadKernelV2(words, "rv32im/test/benchmark_kernel");
  auto image = rv32im::MemoryImage::fromWords(words);
  LOG(0, "Running first segment");
  rv32im::NullHostIO io;
  auto preflightData = preflight(po2, image, io);
  WriteIop writeIop;
  LOG(0, "Proving");
  prover.prove(writeIop, *preflightData);
  std::vector<Fp> transcript = writeIop.getTranscript();
  LOG(0, "Transcipt size = " << transcript.size());
  LOG(0, "Verifying");
  ReadIop readIop(transcript.data(), transcript.size());
  verifyRv32im(readIop, po2);
  readIop.done();
}

TEST(prove, cpu) {
  testProve(getCpuHal());
}

TEST(prove, gpu) {
  testProve(getGpuHal());
}

/*
TEST(prove, dual) {
  IHalPtr cpu = getCpuHal();
  IHalPtr gpu = getGpuHal();
  IHalPtr dual = getDualHal(cpu, gpu);
  testProve(dual);
}
*/
