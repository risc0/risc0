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

#pragma once

#include "zkp/taps.h"
#include "prove/merkle.h"

namespace risc0 {

class PolyGroup {
public:
  // Allocate poly group.  Coeffs are presumed to be in bit reversed form and
  // safe to overwrite.
  PolyGroup(IHalPtr hal, HalMatrix<Fp> coeffs, PtrRange<Tap> taps, size_t numCols);

  // Evaluate on expanded domain from coefficients, merklize, and commit
  void commit(WriteIop& iop);

  // Evaluate at z (or z^deg for check group) and various 'backs', transform to
  // coefficient form, write results to output pointer (count = # taps)
  void evaluate(FpExt* out, FpExt z);

  // Mix polynomials into the combo, update curMix
  void mix(HalMatrix<FpExt> combos, FpExt& curMix, FpExt comboMix);

  IHalPtr hal;
  HalMatrix<Fp> coeffs;
  PtrRange<Tap> taps;
  size_t numCols;
  HalMatrix<Fp> expanded;
  MerkleProver merkle;
  HalArray<FpExt> out;
  HalArray<uint32_t> cols;
  HalArray<FpExt> xs;
  HalArray<uint32_t> whichCombo;
  Fp rou;
};

}  // namespace risc0
