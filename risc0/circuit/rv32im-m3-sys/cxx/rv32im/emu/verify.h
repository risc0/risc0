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

#include "core/util.h"
#include "zkp/fp.h"
#include "zkp/rou.h"
#include "hal/hal.h"
#include "hal/po2s.h"

namespace risc0 {

#define PO2(x) \
  void verify_cpu_ ## x(const Fp* data, const Fp* globals, Fp rou);
PO2S
#undef PO2

inline void verify(const Fp* data, const Fp* globals, size_t numRows) {
  size_t po2 = log2Ceil(numRows);
  if (po2 < MIN_PO2 || po2 > MAX_PO2) {
    LOG(0, "PO2 = " << po2);
    throw std::runtime_error("Invalid po2");
  }
  if (numRows != (size_t(1) << po2)) {
    throw std::runtime_error("numRows is not a power of 2");
  }

  switch(po2) {
#define PO2(x) \
    case x: verify_cpu_ ## x(data, globals, ROU_FWD[po2]); break;
    PO2S
#undef PO2
    default: throw std::runtime_error("Unreachable");
  }
}

}  // namespace risc0

