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

#include <cstddef>
#include <cstdint>

namespace risc0 {

inline size_t align(size_t value, size_t alignment = sizeof(uint32_t)) {
  return ((value - 1) & ~(alignment - 1)) + alignment;
}

template <typename T> inline T* align(T* ptr, size_t alignment = sizeof(uint32_t)) {
  size_t value = reinterpret_cast<size_t>(ptr);
  return reinterpret_cast<T*>(align(value, alignment));
}

inline bool is_aligned(const void* ptr, size_t alignment = sizeof(uint32_t)) {
  return (reinterpret_cast<size_t>(ptr) & (alignment - 1)) == 0;
}

} // namespace risc0
