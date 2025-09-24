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

#include "zkp/taps.h"
#include "prove/fri.h"
#include "prove/poly_group.h"

#include <functional>

namespace risc0 {

// For a given group, the prover's state for that group
struct GroupState {
  // Any globals in the group
  HalArray<Fp> global;

  // Any mix values in the group (not for group 0, for other groups)
  HalArray<FpExt> mix;

  // The rows and columns of the group
  HalMatrix<Fp> table;

  // The rows and columns after RS expansion
  HalMatrix<Fp> expTable;
};

// Take in the state of all groups (preceding groups are all defined) and compute
// the witness for this group.
using WitgenFunc = std::function<void(std::vector<GroupState>& state)>;

// Writes `out` (shape: 4 x po2) with the value of the validity polynomial evaltuated with state and mix
using EvalCheckFunc = std::function<void(HalMatrix<Fp> out, std::vector<GroupState>& state, FpExt mix)>;

struct GroupInfo {
  size_t globalCount;  // How many global values we need
  size_t mixCount;  // How many elements of FS prng we need
  WitgenFunc witgen;  // Witgen function for the group
};

struct CircuitInfo {
  TapManager taps;
  std::vector<GroupInfo> groups;

  // For every group, collect
  EvalCheckFunc evalCheck;
};

class Prover {
public:
  // One time setup
  Prover(IHalPtr hal, const CircuitInfo& circuitInfo, size_t po2);

  // Per proof
  void prove(WriteIop& iop);

private:
  IHalPtr hal;
  const CircuitInfo& circuitInfo;
  size_t po2;
  size_t rows;
  size_t domain;
  size_t checkSize;
  size_t evalSize;
  size_t checkComboId;
  size_t totCombos;
  std::vector<Tap> checkTaps;
  std::vector<GroupState> groups;
  std::vector<PolyGroup> polys;
  HalMatrix<Fp> checkRaw;
  PolyGroup check;
  HalMatrix<FpExt> combos;
  HalArray<FpExt> evalCoeffs;
  HalArray<EvalInfo> evalInfo;
  HalArray<DivideInfo> divideInfo;
  HalMatrix<Fp> friCoeffs;
  FriProver fri;
};

}  // namespace risc0
