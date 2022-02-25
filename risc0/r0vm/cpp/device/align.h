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
