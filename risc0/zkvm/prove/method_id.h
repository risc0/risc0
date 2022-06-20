// Copyright 2022 Risc0, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <cstddef>
#include <cstdint>
#include <string>

#include "risc0/core/archive.h"
#include "risc0/zkvm/circuit/constants.h"
#include "risc0/zkvm/verify/riscv.h"

namespace risc0 {

// Computes a method ID based on an ELF file.  The ELF file can either be
// supplied by a file or by an in-memory buffer.
MethodId computeMethodId(const std::string& elfPath, size_t limit = kDefaultCodeDigestCount);
MethodId computeMethodId(const std::vector<uint8_t>& elfBytes,
                         size_t limit = kDefaultCodeDigestCount);

// Loads an already-computed method ID from an in-memory buffer or a file.
MethodId loadMethodId(const std::string& path);
MethodId loadMethodId(const uint8_t* bytes, size_t len);

} // namespace risc0
