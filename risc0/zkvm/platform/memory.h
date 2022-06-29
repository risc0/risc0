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

namespace risc0 {

#define MEM_REGION(name, start, len)                                                               \
  constexpr size_t kMem##name##Start = start;                                                      \
  constexpr size_t kMem##name##End = start + len;                                                  \
  constexpr size_t kMem##name##Len = len;

constexpr size_t kMemBits = 24;
constexpr size_t kMemSize = (1 << kMemBits) * 4;

constexpr size_t k1MB = 0x00100000;

// Must match risc0.ld and zkvm/sdk/rust/platform/src/memory.rs.
//
// The circuit treats sections where the high bit (1 << (kMemBits -
// 1)) is set as write-once memory, so read-write sections must not be
// in the upper half of the memory space.
//
// clang-format off
MEM_REGION(Stack,  0x00000000, 9 * k1MB)
MEM_REGION(Data,   0x00900000, k1MB)
MEM_REGION(Heap,   0x00A00000, 20 * k1MB)
MEM_REGION(Input,  0x01E00000, k1MB)
MEM_REGION(GPIO,   0x01F00000, k1MB)
MEM_REGION(Prog,   0x02000000, 10 * k1MB)
MEM_REGION(SHA,    0x02A00000, k1MB)
MEM_REGION(WOM,    0x02B00000, 21 * k1MB)
MEM_REGION(Output, 0x02B00000, 20 * k1MB)
MEM_REGION(Commit, 0x03F00000, k1MB)
// clang-format on

#define PTR_TO(type, name) reinterpret_cast<type*>(kMem##name##Start);

inline uint32_t* GPIO_InputBase() {
  return reinterpret_cast<uint32_t*>(kMemInputStart);
}

inline uint32_t* GPIO_OutputBase() {
  return reinterpret_cast<uint32_t*>(kMemOutputStart);
}

inline uint32_t* GPIO_CommitBase() {
  return reinterpret_cast<uint32_t*>(kMemCommitStart);
}

} // namespace risc0
