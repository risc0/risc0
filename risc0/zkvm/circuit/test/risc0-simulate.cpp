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

#include "risc0/core/elf.h"
#include "risc0/core/log.h"
#include "risc0/core/util.h"
#include "risc0/zkvm/circuit/constants.h"
#include "risc0/zkvm/prove/exec.h"

#include <vector>

using namespace risc0;

int main(int argc, char* argv[]) {
  setLogLevel(2);
  if (argc < 2) {
    LOG(1, "usage: risc0-simulate <elf>");
    exit(1);
  }
  LOG(1, "File = " << argv[1]);
  try {
    ExecState state(argv[1]);
    MemoryHandler io;
    state.run(1 << 20, io);
  } catch (const std::runtime_error& err) {
    LOG(1, "Failed: " << err.what());
    exit(1);
  }
}
