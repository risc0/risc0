#pragma once

#include <cstddef>

/// \file
/// SourceLoc is basically a near clone of std::source_location, but since it's not in the spec
/// until c++20, we build our own minialist version.  This is currently used to help track EDSL
/// expressions for the IR.

namespace risc0 {

/// A source location.  Capture as much as we can from the compiler, which might be nothing.
struct SourceLoc {
public:
  /// Get the "current" source location.  When used in default values, this effectively captures the
  /// call site of the function declaring the default value, which is very useful.
  static constexpr SourceLoc current(const char* filename = __builtin_FILE(),
                                     int line = __builtin_LINE(),
#ifdef __has_builtin
#if __has_builtin(__builtin_COLUMN)
#define COLUMN_EXPR __builtin_COLUMN()
#else
#define COLUMN_EXPR 0
#endif
#else
#define COLUMN_EXPR 0
#endif
                                     int column = COLUMN_EXPR) noexcept {
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
