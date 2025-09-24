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

#include "hal/hal.h"
#include "prove/write_iop.h"

namespace risc0 {

class MerkleProver {
public:
  // Construct prover to be used later
  MerkleProver(IHalPtr hal, HalMatrix<Fp> input, size_t queries);
  // Read from input, make merkle tree, write to Iop + commit
  void compute(WriteIop& iop);
  // Write a query to the Iop
  void query(WriteIop& iop, size_t idx);
  // Get the root
  Digest getRoot() const { return root; }
  // Get # of rows
  size_t rows() const { return input.rows(); }
  // Get # of cols
  size_t cols() const { return input.cols(); }

private:
  IHalPtr hal;
  size_t topSize;
  HalMatrix<Fp> input;
  HalArray<Digest> tree;
  HalArray<Fp> queryTmp;
  Digest root;
};

} // namespace risc0
