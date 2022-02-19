#include "risc0/zkp/prove/step/step.h"

#include "risc0/core/log.h"

#include <array>

#define DO_LOG(...)                                                                                \
  if (getLogLevel() >= 2) {                                                                        \
    int size = snprintf(NULL, 0, __VA_ARGS__);                                                     \
    char* buf = new char[size + 1];                                                                \
    sprintf(buf, __VA_ARGS__);                                                                     \
    LOG(2, buf);                                                                                   \
    delete[] buf;                                                                                  \
  }

namespace risc0 {

#define STEP_INC
#include "risc0/zkp/prove/step/step.cpp.inc"

} // namespace risc0
