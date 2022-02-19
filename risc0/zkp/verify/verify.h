#pragma once

#include <cstddef>
#include <cstdint>

namespace risc0 {

// Throws on failure
void verify(const uint32_t* proofData, size_t proofSize);

} // namespace risc0
