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

#include "risc0/zkp/core/sha256.h"

namespace risc0 {

// Character based entry point, CPU only
inline ShaDigest shaHash(const uint8_t* data, size_t size) {
  // Capture initial # of bits
  uint64_t bitSize = size * uint64_t(8);

  // Initialize state
  ShaDigest state = impl::initState();

  // Make room for a single chunk
  uint32_t words[16];

  // Process all the full chunks
  while (size >= 64) {
    impl::endianEncode(words, data);
    impl::compress(state, words);
    data += 64;
    size -= 64;
  }

  // Copy over the final bytes + pad (always safe, since size < 64)
  uint8_t final[64] = {0};
  memcpy(final, data, size);
  final[size] = 0x80;
  impl::endianEncode(words, final);

  // If we can't fit the size in the remaining room, compress + clear
  if (size + 1 > 56) {
    impl::compress(state, words);
    memset(words, 0, 64);
  }

  // Now add size + do final compession
  words[14] = bitSize >> 32;
  words[15] = bitSize & 0xffffffff;
  impl::compress(state, words);

  return state;
}

// Helper function for strings
inline ShaDigest shaHash(const std::string& str) {
  return shaHash(reinterpret_cast<const uint8_t*>(str.data()), str.size());
}

inline std::string hexDigest(const ShaDigest& digest) {
  const char* hexdigits = "0123456789abcdef";
  std::string r(64, 0);
  for (size_t i = 0; i < 8; i++) {
    uint32_t word = digest.words[i];
    for (size_t j = 0; j < 4; j++) {
      uint8_t byte = word >> 24;
      r[i * 8 + j * 2] = hexdigits[byte >> 4];
      r[i * 8 + j * 2 + 1] = hexdigits[byte & 0xf];
      word <<= 8;
    }
  }
  return r;
}

inline std::ostream& operator<<(std::ostream& os, const ShaDigest& x) {
  os << hexDigest(x);
  return os;
}

} // namespace risc0
