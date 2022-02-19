#pragma once

#include <map>

#include "risc0/zkp/circuit/code_regs.h"
#include "risc0/zkp/circuit/data_regs.h"

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
