#pragma once

#include <cstddef>
#include <cstdint>

#include "risc0/zkp/verify/code_id.h"

namespace risc0 {

// Throws on failure
void verify(const CodeID& code, const uint32_t* proofData, size_t proofSize);

} // namespace risc0
