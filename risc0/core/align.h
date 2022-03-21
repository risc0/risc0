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
