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

#include <functional>

#include "hal/hal.h"
#include "prove/merkle.h"
#include "zkp/params.h"

namespace risc0 {

class FriProverRound {
public:
  FriProverRound(IHalPtr hal, HalMatrix<Fp> coeffsIn);

  void compute(WriteIop& iop);
  void query(WriteIop& iop, size_t& pos);

  IHalPtr hal;
  HalMatrix<Fp> coeffsIn;
  HalMatrix<Fp> evaluated;
  MerkleProver merkle;
  HalMatrix<Fp> coeffsOut;
};

using ProvePointFunction = std::function<void(WriteIop&, size_t)>;

class FriProver {
public:
  FriProver(IHalPtr hal, HalMatrix<Fp> coeffs);

  void compute(WriteIop& iop, ProvePointFunction func);

private:
  IHalPtr hal;
  size_t degree;
  size_t domain;
  std::vector<FriProverRound> rounds;
  HalMatrix<Fp> last;
  HalMatrix<Fp> finalCoeffs;
};

}  // namespace risc0
