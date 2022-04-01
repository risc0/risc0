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

#include <map>

#include "risc0/zkvm/circuit/code_regs.h"
#include "risc0/zkvm/circuit/data_regs.h"

namespace risc0 {

struct StepState {
  Buffer codeBuf;
  Buffer dataBuf;
  CodeRegs code;
  DataRegs data;
  std::map<size_t, DataRegs> prev;

  StepState(Buffer codeBuf, Buffer dataBuf)
      : codeBuf(codeBuf)
      , dataBuf(dataBuf)
      , code(BufAlloc(codeBuf.slice(0, 0), codeBuf))
      , data(code, dataBuf) {}
  DataRegs& getPrev(size_t size);
  void setExec();
  void setMemCheck();
};

} // namespace risc0
