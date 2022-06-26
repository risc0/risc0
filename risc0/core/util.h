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

/// \file
/// Small utility functions, mostly common math routines.

#include <cstddef>
#include <stdexcept>
#include <vector>

#define REQUIRE(x)                                                                                 \
  do {                                                                                             \
    if (!(x)) {                                                                                    \
      throw std::runtime_error(#x);                                                                \
    }                                                                                              \
  } while (0)

namespace risc0 {

/// Compute `ceil(a / b)` via truncated integer division.
inline size_t constexpr ceilDiv(size_t a, size_t b) {
  return (a + (b - 1)) / b;
}

/// Round `a` up to the nearest multipe of `b`.
inline size_t constexpr roundUp(size_t a, size_t b) {
  return ceilDiv(a, b) * b;
}

/// Compute the smalled power `p` of x such that `x^p >= in`
inline size_t constexpr nearestPoX(size_t in, size_t x) {
  size_t r = 1;
  while (r < in) {
    r *= x;
  }
  return r;
}

/// Compute the smalled power `2` of x such that `2^p >= in`
inline size_t constexpr nearestPo2(size_t in) {
  size_t r = 1;
  while (r < in) {
    r *= 2;
  }
  return r;
}

/// Compute `ceil(log_x(in))`, i.e. find the smallest value `out` such that `x^out >= in`.
inline size_t constexpr logXCeil(size_t in, size_t x) {
  size_t r = 0;
  size_t c = 1;
  while (c < in) {
    r++;
    c *= x;
  }
  return r;
}

/// Compute `ceil(log_2(in))`, i.e. find the smallest value `out` such that `2^out >= in`.
inline size_t constexpr log2Ceil(size_t in) {
  size_t r = 0;
  while ((size_t(1) << r) < in) {
    r++;
  }
  return r;
}

/// True if `in` is a power of 2
inline bool constexpr isPo2(size_t in) {
  return (size_t(1) << log2Ceil(in)) == in;
}

// Reads an entire file into a buffer.
std::vector<uint8_t> loadFile(const std::string& path);

} // namespace risc0
