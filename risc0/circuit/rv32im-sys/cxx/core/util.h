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
#include <functional>
#include <stdexcept>
#include <thread>
#include <vector>

namespace risc0 {

/// Compute `ceil(a / b)` via truncated integer division.
inline size_t constexpr ceilDiv(size_t a, size_t b) {
  return (a + (b - 1)) / b;
}

/// Round `a` up to the nearest multiple of `b`.
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

// Runs function on different threads passing i = 0..count
inline void parallel_map(size_t count, std::function<void(size_t)> body) {
  size_t num_logical_processors =
      std::max(static_cast<size_t>(std::thread::hardware_concurrency()), 1UL);
  size_t num_threads = std::min(num_logical_processors, count);

  std::vector<std::thread> threads;

  auto count_per_thread = count / num_threads;
  for (size_t thread_id = 0; thread_id < num_threads; thread_id++) {
    auto start = thread_id * count_per_thread;
    if (thread_id == num_threads - 1) {
      count_per_thread += count % num_threads;
    }
    threads.emplace_back([start, count_per_thread, body] {
      for (size_t i = 0; i < count_per_thread; i++) {
        body(start + i);
      }
    });
  }

  std::exception_ptr exception_ptr = nullptr;
  for (std::thread& t : threads) {
    try {
      t.join();
    } catch (...) {
      if (!exception_ptr) {
        exception_ptr = std::current_exception();
      }
    }
  }
  if (exception_ptr) {
    std::rethrow_exception(exception_ptr);
  }
}

} // namespace risc0
