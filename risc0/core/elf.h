// Copyright 2022 RISC Zero, Inc.
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

#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace risc0 {

// Loads an ELF file and collects the memory that would be written on loading in memOut
// All writes are 32 bit wide and aligned (i.e. addr % 4 == 0).  Throws
// std::runtime_error on any errors (file, type, misalignment, addr >= maxMem, etc).  Returns
// the entry point address.

uint32_t loadElf(const std::vector<uint8_t>& elfBytes,
                 uint32_t maxMem,
                 std::map<uint32_t, uint32_t>& memOut);

} // namespace risc0
