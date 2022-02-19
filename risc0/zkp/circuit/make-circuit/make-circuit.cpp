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
