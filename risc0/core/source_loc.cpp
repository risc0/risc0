#include "risc0/core/source_loc.h"

#include <assert.h>
#include <cstring>

#if defined(CIRCUIT_BACKTRACE) && !defined(__clang__)
#include <cxxabi.h>
#include <mutex>
#endif

namespace risc0 {

#if defined(CIRCUIT_BACKTRACE) && !defined(__clang__)
namespace {
void error_callback(void* data, const char* msg, int errnum) {
  throw(std::runtime_error(std::string(msg) + ": errnum=" + std::to_string(errnum)));
}

struct fill_backtrace_data {
  std::string frames;
};

// Fills our fill_backtrace_data with a shortened description of our
// stack trace.  We try to make it as short as possible while still
// being useful by excluding a bunch of stuff.
int fill_backtrace(
    void* data_arg, uintptr_t /* pc */, const char* filename, int linenum, const char* function) {
  fill_backtrace_data& data = *reinterpret_cast<fill_backtrace_data*>(data_arg);
  bool last_frame = false;

  std::string this_frame;
  if (filename) {
    if (!strncmp(filename, "/usr/include/", 13)) {
      // Skip system headers, go to next frame
      return 0;
    }

    // Try to trim stuff off filename if possible.
    const char* pos = strrchr(filename, '/');
    if (pos) {
      filename = pos + 1;
    }

    this_frame += filename;
  } else {
    // Don't know where we are!  Skip this frame.
    return 0;
  }

  this_frame += ":" + std::to_string(linenum) + "(";

  if (function) {
    char* realname = abi::__cxa_demangle(function, nullptr /* allocatememory */, 0, nullptr);

    if (realname) {
      function = realname;
    }

    if (!strcmp(function, "operator()")) {
      function = "lambda";
    }

    if (!strncmp(function, "testing::", 9) || strstr(function, "libc_start")) {
      // If we hit a framework or libc_start, we're done.
      return 1;
    }

    if (!strncmp(function, "addFunc", 7)) {
      // addFunc should be transparent; skip this one.
      return 0;
    }

    std::string shortname = function;

    // Try to trim down the function name so it's not quite so big.
    auto left_paren = shortname.find('(');
    if (left_paren != std::string::npos) {
      shortname = shortname.substr(0, left_paren);
    }
    auto ns = shortname.rfind("::");
    if (ns != std::string::npos) {
      shortname = shortname.substr(ns + 2);
    }
    auto less_than = shortname.rfind('<');
    if (less_than != std::string::npos) {
      shortname = shortname.substr(0, less_than);
    }
    //    std::cerr << "Long name '" << function << "' short name '" << shortname << "'\n";

    this_frame += shortname;

    if (realname) {
      free(realname);
    }
  }
  this_frame += ")";

  // Successfully got a frame!  Add it to our list
  if (!data.frames.empty()) {
    data.frames += ",";
  }
  data.frames += this_frame;

  return last_frame ? -1 : 0;
}

static std::once_flag init;
static backtrace_state* bt = nullptr;

void init_backtrace() {
  std::call_once(init, []() {
    bt = backtrace_create_state(nullptr /* don't know our filename  */,
                                1 /* possibly threaded */,
                                error_callback,
                                nullptr /* no extra error data */);
  });
}

} // namespace

#endif // CIRCUIT_BACKTRACE

SourceLoc SourceLoc::current(const char* filename, int line, int column) {
  SourceLoc loc;
  loc.filename = filename;
  loc.line = line;
  loc.column = column;

#if defined(CIRCUIT_BACKTRACE) && !defined(__clang__)
  init_backtrace();

  fill_backtrace_data data;
  backtrace_full(bt,
                 1, // skip SourceLoc::current and the thing before us that supplied its location.
                 fill_backtrace,
                 error_callback,
                 &data);
  loc.frames = data.frames;
#endif // CIRCUIT_BACKTRACE

  return loc;
}

std::string SourceLoc::as_string() const {
  if (!frames.empty()) {
    return frames;
  } else {
    return std::string(filename) + ":" + std::to_string(line);
  }
}

} // namespace risc0
