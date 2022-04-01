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

#pragma once

#include "risc0/zkvm/prove/step.h"

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
