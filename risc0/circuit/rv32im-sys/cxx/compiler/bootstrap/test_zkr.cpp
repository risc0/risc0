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

#include "compiler/bootstrap/extract_zkr.h"
#include "prove/rv32im.h"
#include "verify/rv32im.h"
#include "zirgen/circuit/recursion/code.h"

using namespace risc0;

struct MyExternHandler : public zirgen::Zll::ExternHandler {
  std::optional<std::vector<uint64_t>> doExtern(llvm::StringRef name,
                                                llvm::StringRef extra,
                                                llvm::ArrayRef<const zirgen::Zll::InterpVal*> args,
                                                size_t outCount) override {
    std::vector<uint64_t> results;
    if (name == "write") {
      return results;
    }
    return ExternHandler::doExtern(name, extra, args, outCount);
  }
};

int main() {
  zirgen::registerEdslCLOptions();
  uint32_t po2 = 12;

  // Do a prove
  IHalPtr hal = getGpuHal();
  std::map<uint32_t, uint32_t> words;
  rv32im::loadKernelV2(words, "rv32im/test/benchmark_kernel");
  auto image = rv32im::MemoryImage::fromWords(words);
  Rv32imProver prover(hal, po2);
  rv32im::NullHostIO io;
  auto preflightData = preflight(po2, image, io);
  WriteIop wiop;
  prover.prove(wiop, *preflightData);
  const std::vector<Fp>& transcript = wiop.getTranscript();

  // Do a plain verify as a sanity check
  LOG(0, "Test verify");
  ReadIop riop(transcript.data(), transcript.size());
  verifyRv32im(riop, po2);

  // Build verifier as a module
  LOG(0, "Make + optimize module");
  zirgen::Module module;
  addLift(module, 12);
  module.optimize();

  LOG(0, "Emulate");
  auto func =
      module.getModule().lookupSymbol<mlir::func::FuncOp>("lift_rv32im_m3_" + std::to_string(po2));
  MyExternHandler externHandler;
  zirgen::Zll::Interpreter interp(module.getCtx(), zirgen::poseidon2HashSuite());
  interp.setExternHandler(&externHandler);
  Digest whatever;
  size_t outSize = zirgen::recursion::kOutSize;
  for (size_t i = 0; i < 8; i++) {
    whatever.words[i] = i;
  }
  zirgen::ReadIop root(
      interp.getHashSuite().makeRng(), reinterpret_cast<const uint32_t*>(&whatever), 8);
  zirgen::ReadIop seal(interp.getHashSuite().makeRng(),
                       reinterpret_cast<const uint32_t*>(transcript.data()),
                       transcript.size());
  auto outBuf = interp.makeBuf(func.getArgument(0), outSize, zirgen::Zll::BufferKind::Global);
  interp.setIop(func.getArgument(1), &root);
  interp.setIop(func.getArgument(2), &seal);
  if (failed(interp.runBlock(func.front()))) {
    LOG(0, "Failed to evaluate");
    throw std::runtime_error("BAD");
  }
  LOG(0, "DONE!");
  // Print outputs
  for (size_t i = 0; i < outSize; i++) {
    LOG(0, "out[" << i << "] = " << outBuf[i][0]);
  }
  // module.dump(true);
}
