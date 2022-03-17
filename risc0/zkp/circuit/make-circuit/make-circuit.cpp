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

#include "risc0/core/log.h"
#include "risc0/zkp/circuit/accum_regs.h"
#include "risc0/zkp/circuit/gen_context.h"
#include "risc0/zkp/circuit/poly_context.h"
#include "risc0/zkp/circuit/step_state.h"

int main() {
  using namespace risc0;
  setLogLevel(1);
  std::cout << "#ifdef STEP_INC\n";
  {
    GenContext genContext("dataStepExec");
    setGlobalContext(&genContext);
    Buffer code = genContext.addParam("code", kCodeSize, true);
    Buffer data = genContext.addParam("data", kDataSize, false);
    genContext.paramsDone();
    StepState step(code, data);
    step.setExec();
    setGlobalContext(nullptr);
    std::cout << genContext.funcDone();
  }
  {
    GenContext genContext("dataStepCheck");
    setGlobalContext(&genContext);
    Buffer code = genContext.addParam("code", kCodeSize, true);
    Buffer data = genContext.addParam("data", kDataSize, false);
    genContext.paramsDone();
    StepState step(code, data);
    step.setMemCheck();
    setGlobalContext(nullptr);
    std::cout << genContext.funcDone();
  }
  {
    GenContext genContext("accumStep");
    setGlobalContext(&genContext);
    Buffer code = genContext.addParam("code", kCodeSize, true);
    Buffer data = genContext.addParam("data", kDataSize, true);
    Buffer accum = genContext.addParam("accum", kAccumSize, false);
    genContext.paramsDone();
    StepState step(code, data);
    AccumRegs accumRegs(accum);
    accumRegs.set(step);
    setGlobalContext(nullptr);
    std::cout << genContext.funcDone();
  }
  std::cout << "#endif // STEP_INC\n";
  {
    PolyContext polyContext;
    setGlobalContext(&polyContext);
    Buffer code = polyContext.addParam("code", kCodeSize);
    Buffer data = polyContext.addParam("data", kDataSize);
    Buffer accum = polyContext.addParam("accum", kAccumSize);
    StepState step(code, data);
    // equate(step.code.cycleType[CodeCycleType::MEM_WRITE], 1);
    step.setExec();
    step.setMemCheck();
    AccumRegs accumRegs(accum);
    accumRegs.set(step);
    setGlobalContext(nullptr);
    std::cout << polyContext.done();
  }
}
