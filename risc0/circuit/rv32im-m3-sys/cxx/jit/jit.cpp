#include "jit/jit.h"

#include "core/log.h"
#include "jit/block_cache.h"
#include "jit/memory.h"

using namespace risc0::rv32im;

namespace risc0::jit {

bool doJit(JitTrace& trace, MemoryImage& image, HostIO& io, size_t quota, bool execOnly) {
  JitContext ctx(quota);
  Memory memory(image, trace);
  BlockCache machine(ctx, trace, memory, MODE_MACHINE, execOnly);
  // Do 'restore' cycle
  MemTxn txn;
  machine.fetchWord(txn, V2_COMPAT_SPC);
  uint32_t pc = txn.value;
  ctx.incCycle();
  // Do main loop
  while(true) {
    auto ec = machine.run(pc);
    if (ec == ExitCause::QUOTA_OUT) {
      return false;
    }
    if (ec == ExitCause::ECALL) {
      LOG(0, "ECALL HIT");
      break;
    }
    throw std::runtime_error("Unhandled case");
  }
  return true;
}

}  // namespace risc0::jit
