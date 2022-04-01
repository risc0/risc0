// Copyright 2022 Risc0, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "risc0/zkvm/prove/exec.h"

#include "risc0/core/elf.h"
#include "risc0/core/log.h"
#include "risc0/core/util.h"
#include "risc0/zkvm/circuit/constants.h"

namespace risc0 {

ExecState::ExecState(const std::string& elfFile) {
  startAddr = loadElf(elfFile, kMemSize, image);
}

void ExecState::run(size_t maxSteps, MemoryHandler& io) {
  context.io = &io;
  context.curStep = 0;
  context.mem.data[0] = 0;
  context.numSteps = nearestPo2(image.size() + 3 + kZkCycles);
  if (context.numSteps > maxSteps) {
    throw std::runtime_error("Elf too large to fix in maxSteps");
  }

  LOG(1, "image.size() = " << image.size());
  LOG(1, "numSteps = " << context.numSteps);
  io.onInit(context.mem);

  code.resize(kCodeSize * context.numSteps);
#ifdef CIRCUIT_DEBUG
  data.resize(kDataSize * context.numSteps, Fp::invalid());
#else
  data.resize(kDataSize * context.numSteps);
#endif
  setupCode(code.data(), context.numSteps, startAddr, image);
  while (context.numSteps <= maxSteps) {
    while (context.curStep < (context.numSteps - 1 - kZkCycles)) {
      if (context.curStep == image.size() + 1) {
        io.onLoaded(context.mem);
      }
      dataStepExec(context, code.data(), data.data());
      context.curStep++;
    }
    MemoryState save = context.mem;
    try {
      // Try to execute fini, if it works, we are done
      dataStepExec(context, code.data(), data.data());
      // TODO: Call onHalt
      return;
    } catch (const std::runtime_error& err) {
      // Unwind the effects on memory (if any)
      // TODO: Make this less expensive
      context.mem = save;
    }
    // We weren't done (and fini failed), expand and keep going
    LOG(1, "EXPANDING!");
    {
      std::vector<Fp> newCode(code.size() * 2);
#ifdef CIRCUIT_DEBUG
      std::vector<Fp> newData(data.size() * 2, Fp::invalid());
#else
      std::vector<Fp> newData(data.size() * 2);
#endif
      setupCode(newCode.data(), context.numSteps * 2, startAddr, image);
      for (int j = 0; j < kDataSize; j++) {
        std::copy(data.begin() + j * context.numSteps,
                  data.begin() + j * context.numSteps + context.curStep,
                  newData.begin() + j * context.numSteps * 2);
      }
      code.swap(newCode);
      data.swap(newData);
    }
    context.numSteps *= 2;
  }
}

} // namespace risc0
