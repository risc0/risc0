// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

#pragma once

/// \file
/// Small utility functions, mostly common math routines.

#include <array>
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <vector>

namespace risc0 {

/// Compute `ceil(a / b)` via truncated integer division.
inline size_t constexpr ceilDiv(size_t a, size_t b) {
  return (a + (b - 1)) / b;
}

/// Round `a` up to the nearest multipe of `b`.
inline size_t constexpr roundUp(size_t a, size_t b) {
  return ceilDiv(a, b) * b;
}

/// Compute the greatest power of 2 less than or equal to `in`
/// For example, `greatestLePo2(50) == 32`
inline size_t constexpr greatestLePo2(size_t in) {
  size_t r = 1;
  while (r * 2 <= in) {
    r *= 2;
  }
  return r;
}

/// Compute the smallest power of 2 greater than or equal to `in`
/// For example, `leastGePo2(50) == 64`
inline size_t constexpr leastGePo2(size_t in) {
  size_t r = 1;
  while (r < in) {
    r *= 2;
  }
  return r;
}

/// Compute `ceil(log_2(in))`, i.e. find the smallest value `out` such that
/// `2^out >= in`.
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
