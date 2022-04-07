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

#include "risc0/zkvm/prove/step.h"
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

// Ignore values in generated code that are computed unnecessarily;
// the optimizer should remove these.

#if defined(__GNUC__)
# pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif
#if defined(__clang__)
# pragma clang diagnostic ignored "-Wunused-but-set-variable"
#endif

#define STEP_INC
#include "risc0/zkvm/circuit/step.cpp.inc"

} // namespace risc0
