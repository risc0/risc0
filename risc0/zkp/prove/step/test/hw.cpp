#include "risc0/core/log.h"
#include "risc0/zkp/prove/step/exec.h"

#include <gtest/gtest.h>

namespace risc0 {

static std::vector<uint32_t> run(const std::string& name) {
  std::vector<uint32_t> regs;
  MemoryHandler io;
  ExecState exec(("risc0/zkp/prove/step/test/" + name).c_str());
  exec.run(1 << 20, io);
  size_t size = exec.context.numSteps;
  // Extract registers
  for (size_t i = 0; i < 8; i++) {
    const Fp* globals = exec.context.globals;
    regs.push_back(globals[2 * i].asUInt32() | (globals[2 * i + 1].asUInt32() << 16));
  }
  // Now, do memory verification
  for (size_t i = 0; i < size - kZkCycles; i++) {
    LOG(2, "Verify cycle " << i);
    exec.context.curStep = i;
    dataStepCheck(exec.context, exec.code.data(), exec.data.data());
  }
  return regs;
}

TEST(Step, HW) {
  // Verify writes to WOM with the same value work
  run("test_wom_same");
  // Verify writes to WOM with different values fail
  ASSERT_THROW(run("test_wom_diff"), std::runtime_error);
}

} // namespace risc0
