
#include "jit/trace.h"
#include "rv32im/emu/emu.h"

namespace risc0::jit {

bool doJit(JitTrace& trace, rv32im::MemoryImage& image, rv32im::HostIO& io, size_t quota, bool execOnly = false);

}  // namespace risc0::jit
