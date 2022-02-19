#include "risc0/core/elf.h"
#include "risc0/core/log.h"
#include "risc0/core/util.h"
#include "risc0/zkp/circuit/constants.h"
#include "risc0/zkp/prove/step/exec.h"

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
