#include "risc0/zkp/circuit/step_state.h"

namespace risc0 {

DataRegs& StepState::getPrev(size_t size) {
  auto it = prev.find(size);
  if (it == prev.end()) {
    it = prev.emplace(size, DataRegs(code, dataBuf.back(size))).first;
  }
  return it->second;
}

void StepState::setExec() {
  data.setExec(*this);
}

void StepState::setMemCheck() {
  data.setMemCheck(*this);
}

} // namespace risc0
