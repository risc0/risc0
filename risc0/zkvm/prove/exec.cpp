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

ExecState::ExecState(const std::vector<uint8_t>& elfBytes) {
  startAddr = loadElf(elfBytes, kMemSize, image);
}

void ExecState::run(size_t maxSteps, MemoryHandler& io) {
  init(maxSteps, io);
  while (step())
    ;
  fini();
}

void ExecState::init(size_t maxSteps, MemoryHandler& io) {
  context.io = &io;
  context.curStep = 0;
  context.mem.data[0] = 0;
  context.numSteps = nearestPo2(image.size() + 3 + kZkCycles);
  if (context.numSteps > maxSteps) {
    throw std::runtime_error("Elf too large to fix in maxSteps");
  }
  this->maxSteps = maxSteps;
  done = false;

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

  // Run until the image is loaded
  for (size_t i = 0; i < 1 + image.size(); i++) {
    dataStepExec(context, code.data(), data.data());
    context.curStep++;
  }
  // Call onLoaded
  io.onLoaded(context.mem);
  // Step over what should be the 'reset' cycle
  // At this point, we should be ready to do normal
  // code execution
  dataStepExec(context, code.data(), data.data());
  context.curStep++;
}

bool ExecState::step() {
  // If we hit the last cycle already, return false
  if (done) {
    return false;
  }
  // If we are about to hit the end, expand
  if (context.curStep + 3 >= (context.numSteps - 1 - kZkCycles)) {
    expand();
  }
  // Run three steps
  for (size_t i = 0; i < 3; i++) {
    dataStepExec(context, code.data(), data.data());
    context.curStep++;
  }
  // Check if last cycle type == Final
  size_t finalOff = 128 /* kCycleRegs */ + 4 /* size of MemIORegs */ + DataCycleType::FINAL;
  bool isFinal = (data.data()[finalOff * context.numSteps + context.curStep - 1] != Fp(0));
  // If it's not, normal execution is complete
  if (!isFinal) {
    done = true;
  }
  return !done;
}

void ExecState::fini() {
  while (true) {
    bool finiCycle = (context.curStep == context.numSteps - 1 - kZkCycles);
    if (finiCycle) {
      size_t haltOff = 128 /* kCycleRegs */ + 4 /* size of MemIORegs */ + DataCycleType::HALT;
      bool isHalted = (data.data()[haltOff * context.numSteps + context.curStep - 1] != Fp(0));
      if (isHalted)
        break;
      expand();
    }
    dataStepExec(context, code.data(), data.data());
    context.curStep++;
  }
  // Do fini cycle
  dataStepExec(context, code.data(), data.data());
}

uint32_t ExecState::getPC() {
  // PC is two-bit decomposed into the final cycle (last cycle executed) at the first 32 elements of
  // the data
  uint32_t pc = 0;
  uint32_t twoBitMul = 1;
  for (size_t i = 0; i < 16; i++) {
    uint32_t twoBit = data.data()[i * context.numSteps + context.curStep - 1].asUInt32();
    REQUIRE(twoBit < 4);
    pc += twoBit * twoBitMul;
    twoBitMul *= 4;
  }
  return pc;
}

std::vector<uint32_t> ExecState::getRegisters() {
  std::vector<uint32_t> out;
  size_t offset = 30;
  for (size_t i = 0; i < 32; i++) {
    uint32_t low =
        data.data()[(i * 2 + offset) * context.numSteps + context.curStep - 1].asUInt32();
    uint32_t high =
        data.data()[(i * 2 + offset + 1) * context.numSteps + context.curStep - 1].asUInt32();
    REQUIRE(low < 65536 && high < 65536);
    out.push_back(low | (high << 16));
  }
  return out;
}

void ExecState::expand() {
  if (context.numSteps == maxSteps) {
    throw std::runtime_error("Expand failed: at max steps");
  }
  LOG(1, "EXPANDING!");
  {
    std::vector<Fp> newCode(code.size() * 2);
#ifdef CIRCUIT_DEBUG
    std::vector<Fp> newData(data.size() * 2, Fp::invalid());
#else
    std::vector<Fp> newData(data.size() * 2);
#endif
    setupCode(newCode.data(), context.numSteps * 2, startAddr, image);
    for (unsigned j = 0; j < kDataSize; j++) {
      std::copy(data.begin() + j * context.numSteps,
                data.begin() + j * context.numSteps + context.curStep,
                newData.begin() + j * context.numSteps * 2);
    }
    code.swap(newCode);
    data.swap(newData);
  }
  context.numSteps *= 2;
}

} // namespace risc0
