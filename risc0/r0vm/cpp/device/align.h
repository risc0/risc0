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

#include <cstdint>

inline uint32_t align(uint32_t value, uint32_t alignment) {
  return ((value - 1u) & ~(alignment - 1u)) + alignment;
}

inline uint8_t* align(uint8_t* ptr, uint32_t alignment) {
  uint32_t value = reinterpret_cast<uint32_t>(ptr);
  return reinterpret_cast<uint8_t*>(align(value, alignment));
}

inline bool is_aligned(const void* ptr, uint32_t alignment) {
  return (reinterpret_cast<uint32_t>(ptr) & (alignment - 1)) == 0;
}
