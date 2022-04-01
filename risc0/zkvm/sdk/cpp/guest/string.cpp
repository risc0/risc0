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

#include <string.h>

#include "risc0/core/align.h"
#include "risc0/zkvm/platform/memory.h"

extern "C" {

void* memmove(void* dest, const void* src, size_t count) {
  char* destPtr = static_cast<char*>(dest);
  const char* srcPtr = static_cast<const char*>(src);
  size_t dstAddr = reinterpret_cast<size_t>(dest);
  size_t srcAddr = reinterpret_cast<size_t>(src);
  // If we can copy forward, use memcpy (which is in fact forward copying)
  if (dstAddr - srcAddr >= count) {
    return memcpy(dest, src, count);
  }
  // Otherwise, we use a naive bytewise backword copy as a fallback
  for (size_t i = count; i-- > 0;) {
    destPtr[i] = srcPtr[i];
  }
  return dest;
}

#ifdef PORTABLE_IMPL

void* memcpy(void* dest, const void* src, size_t count) {
  const uint8_t* from_u8 = static_cast<const uint8_t*>(src);
  uint8_t* into_u8 = static_cast<uint8_t*>(dest);
  uint8_t* aligned = align(into_u8, 4);
  while (into_u8 < aligned && count) {
    *into_u8++ = *from_u8++;
    count--;
  }

  if (is_aligned(from_u8, sizeof(uint32_t))) {
    const uint32_t* from_u32 = reinterpret_cast<const uint32_t*>(from_u8);
    uint32_t* into_u32 = reinterpret_cast<uint32_t*>(into_u8);
    while (count >= 4) {
      *into_u32++ = *from_u32++;
      count -= 4;
    }
    from_u8 = reinterpret_cast<const uint8_t*>(from_u32);
    into_u8 = reinterpret_cast<uint8_t*>(into_u32);
  }

  while (count) {
    *into_u8++ = *from_u8++;
    count--;
  }

  return dest;
}

void* memset(void* dest, int ch, size_t count) {
  uint8_t* into_u8 = static_cast<uint8_t*>(dest);
  uint8_t* aligned = align(into_u8, 4);
  while (into_u8 < aligned && count) {
    *into_u8++ = ch;
    count--;
  }

  uint32_t word = ((ch & 0xff) << 24) | ((ch & 0xff) << 16) | ((ch & 0xff) << 8) | (ch & 0xff);
  uint32_t* into_u32 = reinterpret_cast<uint32_t*>(into_u8);
  while (count >= 4) {
    *into_u32++ = word;
    count -= 4;
  }

  into_u8 = reinterpret_cast<uint8_t*>(into_u32);
  while (count) {
    *into_u8++ = ch;
    count--;
  }

  return dest;
}

#endif // #ifdef PORTABLE_IMPL

} // extern "C"
