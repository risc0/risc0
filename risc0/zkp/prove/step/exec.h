#pragma once

#include "risc0/zkp/prove/step/step.h"

#include <string>
#include <vector>

namespace risc0 {

struct ExecState {
  ExecState(const std::string& elfFile);
  void run(size_t maxSteps, MemoryHandler& io);

  uint32_t startAddr;
  std::map<uint32_t, uint32_t> image;
  StepContext context;
  std::vector<Fp> code;
  std::vector<Fp> data;
};

} // namespace risc0
