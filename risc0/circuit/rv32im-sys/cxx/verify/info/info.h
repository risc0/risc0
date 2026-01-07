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

#include <functional>
#include <vector>

#include "zkp/taps.h"

namespace risc0 {

struct VerifyGroupInfo {
  size_t globalCount; // How many global values we need
  size_t mixCount;    // How many elements of FS prng we need
};

// Similar to EvalCheckFunc, but runs in extension field
//   * `evals` is the evaluation of all of the taps at point z in "natural
//   sorting order" (group, then column, then distance)
//   * `globals` is the value of all global values (concatenated between groups)
//   * `ecMix` is the eval check mixing value
//   * `z` is the challenge point in extension field
using VerifyEvalCheckFunc =
    std::function<FpExt(FpExt* evals, Fp* globals, FpExt* mix, FpExt ecMix, FpExt z)>;

struct VerifyCircuitInfo {
  TapManager taps;
  std::vector<VerifyGroupInfo> groups;
  VerifyEvalCheckFunc evalCheck;
};

} // namespace risc0
