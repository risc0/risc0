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

#include <iostream>

namespace risc0 {

/// Set the logging level so that logs of level <= \p level are printed
void setLogLevel(int level);

/// Get the currently log level.
/// Usually used to optionally do extra computation required only for logging.
int getLogLevel();

/// Logs a timestamp to cerr (the first part of a log message)
void logTimestamp();

#define LOG(num, vals)                                                                             \
  do {                                                                                             \
    if (::risc0::getLogLevel() >= num) {                                                           \
      ::risc0::logTimestamp();                                                                     \
      std::cerr << vals << std::endl;                                                              \
    }                                                                                              \
  } while (0)

std::string hex(uint32_t value, int digits);
std::string hex(uint32_t value);

} // End namespace risc0
