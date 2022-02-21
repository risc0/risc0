#pragma once

#include "risc0/zkp/verify/code_id.h"

namespace risc0 {

CodeID makeCodeID(const std::string& elfFile);
void writeCodeID(const std::string& filename, const CodeID& id);

} // namespace risc0
