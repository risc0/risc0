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

#include <cassert>
#include <iostream>
#include <string>

using namespace risc0;

uint32_t readU32(OutU32 val) {
  return val.low.asUInt32() | (val.high.asUInt32() << 16);
}

int main() {
  IHalPtr hal = getCpuHal();
  size_t po2 = 12;
  std::map<uint32_t, uint32_t> words;
  rv32im::loadKernelV2(words, "rv32im/test/seal_test_kernel");
  auto image = rv32im::MemoryImage::fromWords(words);
  Digest initialDigest = image.getDigest(1);
  Rv32imProver prover(hal, po2, true);
  rv32im::NullHostIO io;
  auto preflightData = preflight(po2, image, io);
  if (!preflightData.isFinal) {
    throw std::runtime_error("Failed to complete");
  }
  Digest finalDigest = image.getDigest(1);
  WriteIop wiop;
  prover.prove(wiop, preflightData);
  auto transcript = wiop.getTranscript();
  ReadIop riop(wiop.getTranscript().data(), wiop.getTranscript().size());
  LOG(0, "Running verify");
  verifyRv32im(riop, po2);

  const Globals* globals = reinterpret_cast<const Globals*>(transcript.data());
  Digest sealIn = *reinterpret_cast<const Digest*>(globals->rootIn);
  Digest sealOut = *reinterpret_cast<const Digest*>(globals->rootOut);
  if (sealIn != initialDigest) {
    throw std::runtime_error("In digest mismatch");
  }
  if (sealOut != finalDigest) {
    throw std::runtime_error("Out digest mismatch");
  }
  LOG(0, "isTerminate = " << globals->isTerminate);
  LOG(0, "termA0 = " << readU32(globals->termA0));
  LOG(0, "termA1 = " << readU32(globals->termA1));
  for (size_t i = 0; i < 8; i++) {
    LOG(0, "Output[" << i << "] = " << readU32(globals->out[i]));
  }
  assert(globals->isTerminate == 1);
  assert(readU32(globals->termA0) == 0);
  assert(readU32(globals->termA0) == 17);
  for (size_t i = 0; i < 8; i++) {
    assert(readU32(globals->out[i]) == i);
  }
  return 0;
}
