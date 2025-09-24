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

#include <functional>
#include <vector>

#include "verify/read_iop.h"
#include "zkp/taps.h"

namespace risc0 {

struct VerifyGroupInfo {
  size_t globalCount;  // How many global values we need
  size_t mixCount;  // How many elements of FS prng we need
};

// Similar to EvalCheckFunc, but runs in extension field
//   * `evals` is the evaluation of all of the taps at point z in "natural sorting order" (group, then column, then distance)
//   * `globals` is the value of all global values (concatenated between groups)
//   * `ecMix` is the eval check mixing value
//   * `z` is the challenge point in extension field
using VerifyEvalCheckFunc = std::function<FpExt(FpExt* evals, Fp* globals, FpExt* mix, FpExt ecMix, FpExt z)>;

struct VerifyCircuitInfo {
  TapManager taps;
  std::vector<VerifyGroupInfo> groups;
  VerifyEvalCheckFunc evalCheck;
};

void verify(VerifyCircuitInfo& ci, ReadIop& iop, size_t po2);

}  // namespace risc0
