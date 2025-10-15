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
/// Logging Support.
///
/// The logging system has support for multiple log levels, and automatically
/// adds timetamps, including time delta's between log lines.  Logging is
/// automatically disabled in GPU device code. Logging uses C++ ostream as it's
/// basis, and currently always outputs to stderr.  Newlines are automatically
/// added for each log line.
///
/// Example:
/// \code
/// LOG(1, "The value of foo is: " << foo);
/// \endcode

#include <cstdint>
#include <iostream>
#include <sstream>
#include <vector>

/// Declare the low level logging function, either callback to rust or normal stderr
extern "C" void risc0_log_callback(int level, const char* str);

namespace risc0 {

/// Set the logging level so that logs of level <= \p level are printed
void setR0LogLevel(unsigned level);

/// Get the currently log level.
/// Usually used to optionally do extra computation required only for logging.
unsigned getR0LogLevel();

#define LOG(num, vals)                                                                             \
  do {                                                                                             \
    if (::risc0::getR0LogLevel() >= num) {                                                         \
      std::ostringstream oss;                                                                      \
      oss << vals;                                                                                 \
      risc0_log_callback(num, oss.str().c_str());                                                  \
    }                                                                                              \
  } while (0)

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

template <typename T> inline std::ostream& operator<<(std::ostream& os, const std::vector<T>& x) {
  return stringify_collection(os, x.begin(), x.end());
}

} // End namespace risc0
