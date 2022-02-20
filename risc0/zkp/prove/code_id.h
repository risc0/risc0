#pragma once

#include <array>

#include "risc0/core/util.h"
#include "risc0/zkp/circuit/constants.h"
#include "risc0/zkp/core/sha256.h"

namespace risc0 {

constexpr size_t kCodeDigestCount = log2Ceil(kMaxCycles / kMinCycles) + 1;

using CodeID = std::array<ShaDigest, kCodeDigestCount>;

CodeID makeCodeID(const std::string& elfFile);
void writeCodeID(const std::string& filename, const CodeID& id);
CodeID readCodeID(const std::string& filename);

} // namespace risc0


