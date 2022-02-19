#pragma once

#include <string>
#include <vector>

#include "risc0/zkp/prove/step/step.h"

namespace risc0 {

BufferU32 prove(const std::string& elfFile, MemoryHandler& io);

} // namespace risc0
