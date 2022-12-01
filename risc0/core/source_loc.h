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

/// \file
/// SourceLoc is basically a near clone of std::source_location, but since it's not in the spec
/// until c++20, we build our own minialist version.  This is currently used to help track EDSL
/// expressions for the IR.

#ifdef __clang__
#if defined(__has_builtin)
#if __has_builtin(__builtin_FILE) && __has_builtin(__builtin_LINE)
#define HAS_FILE_LINE 1
#else // __has_builtin(__builtin_FILE) && __has_builtin(__builtin_LINE)
#define HAS_FILE_LINE 0
#endif //  __has_builtin(__builtin_FILE) && __has_builtin(__builtin_LINE)
#if __has_builtin(__builtin_COLUMN) && __has_builtin(__builtin_COLUMN)
#define HAS_COLUMN 1
#else // __has_builtin(__builtin_COLUMN) && __has_builtin(__builtin_COLUMN)
#define HAS_COLUMN 0
#endif // __has_builtin(__builtin_COLUMN) && __has_builtin(__builtin_COLUMN)
#else  //  defined(__has_builtin)
#define HAS_FILE_LINE 0
#define HAS_COLUMN 0
#endif //  defined(__has_builtin)
#elif defined(__GNUC__) && __GNUC__ >= 7
// gcc says it supports __has_builtin but experimentation indicates otherwise.
#define HAS_FILE_LINE 1
#define HAS_COLUMN 0
#else // defined(__GNUC__) && __GNUC__ >= 7
#define HAS_FILE_LINE 0
#define HAS_COLUMN 0
#endif // defined(__GNUC__) && __GNUC__ >= 7

namespace risc0 {

/// A source location.  Capture as much as we can from the compiler, which might be nothing.
struct SourceLoc {
public:
  /// Get the "current" source location.  When used in default values, this effectively captures the
  /// call site of the function declaring the default value, which is very useful.
  static constexpr SourceLoc current(
#if HAS_FILE_LINE
      const char* filename = __builtin_FILE(),
      int line = __builtin_LINE(),
#else
      const char* filename = __FILE__,
      int line = __LINE__,
#endif
#if HAS_COLUMN
      int column = __builtin_COLUMN()
#else
      int column = 0
#endif
          ) noexcept {
    SourceLoc loc;
    loc.filename = filename;
    loc.line = line;
    loc.column = column;
    return loc;
  }

  constexpr SourceLoc() noexcept : filename(""), line(0), column(0) {}

  const char* filename;
  size_t line;
  size_t column;
};

} // namespace risc0
