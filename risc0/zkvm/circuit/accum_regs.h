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

#include "risc0/zkvm/circuit/constants.h"
#include "risc0/zkvm/circuit/types.h"

namespace risc0 {

struct AccumRegs {
  Buffer prod1;
  Buffer prod2;
  BufAlloc alloc;
  Reg det;
  Reg invDet;

  AccumRegs(Buffer buf)
      : prod1(buf.slice(0, 4))
      , prod2(buf.slice(4, 4))
      , alloc(buf.slice(0, 0), buf.slice(8, 2))
      , det(alloc)
      , invDet(alloc) {}

  void set(StepState& state);
};

} // namespace risc0
