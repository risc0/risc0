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
#include "risc0/zkvm/circuit/accum_regs.h"
#include "risc0/zkvm/circuit/gen_context.h"
#include "risc0/zkvm/circuit/poly_context.h"
#include "risc0/zkvm/circuit/step_state.h"

#include <fstream>

namespace risc0::circuit {

void make_circuit(const std::string& path) {
  std::ofstream fout(path);

  fout << "#ifdef STEP_INC\n";
  {
    GenContext genContext("dataStepExec");
    setGlobalContext(&genContext);
    Buffer code = genContext.addParam("code", kCodeSize, true);
    Buffer data = genContext.addParam("data", kDataSize, false);
    genContext.paramsDone();
    StepState step(code, data);
    step.setExec();
    setGlobalContext(nullptr);
    fout << genContext.funcDone();
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
    fout << genContext.funcDone();
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
    fout << genContext.funcDone();
  }
  fout << "#endif // STEP_INC\n";
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
    fout << polyContext.done();
  }
}

} // namespace risc0::circuit
