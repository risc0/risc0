// Copyright 2025 RISC Zero, Inc.
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
/// Logging Support.
///
/// The logging system has support for multiple log levels, and automatically adds timetamps,
/// including time delta's between log lines.  Logging is automatically disabled in GPU device code.
/// Logging uses C++ ostream as it's basis, and currently always outputs to stderr.  Newlines are
/// automatically added for each log line.
///
/// Example:
/// \code
/// LOG(1, "The value of foo is: " << foo);
/// \endcode

#include <cstdint>
#include <iostream>
#include <vector>

namespace risc0 {

/// Set the logging level so that logs of level <= \p level are printed
void setLogLevel(unsigned level);

/// Get the currently log level.
/// Usually used to optionally do extra computation required only for logging.
unsigned getLogLevel();

/// Logs a timestamp to cerr (the first part of a log message)
void logTimestamp();

#define LOG(num, vals)                                                                             \
  do {                                                                                             \
    if (::risc0::getLogLevel() >= num) {                                                           \
      ::risc0::logTimestamp();                                                                     \
      std::cerr << vals << std::endl;                                                              \
    }                                                                                              \
  } while (0)

// template <typename T> struct ArrayRef {
//   const T* ptr;
//   size_t size;

//   ArrayRef(const T* ptr, size_t size) : ptr(ptr), size(size) {}
// };

template <typename Iterator>
std::ostream& stringify_collection(std::ostream& os, Iterator it, Iterator itEnd) {
  os << '[';
  if (it != itEnd) {
    os << *it++;
  }
  for (; it != itEnd; ++it) {
    os << ", " << *it;
  }
  os << ']';
  return os;
}

// template <typename T> inline std::ostream& operator<<(std::ostream& os, ArrayRef<T> x) {
//   return stringify_collection(os, x.ptr, x.ptr + x.size);
// }

template <typename T> inline std::ostream& operator<<(std::ostream& os, const std::vector<T>& x) {
  return stringify_collection(os, x.begin(), x.end());
}

} // End namespace risc0
