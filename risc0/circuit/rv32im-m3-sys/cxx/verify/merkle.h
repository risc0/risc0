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

#include "verify/read_iop.h"

#include <vector>

namespace risc0 {

class MerkleVerifier {
public:
  // Construct verifier, read root/top from iop, mix
  MerkleVerifier(ReadIop& iop, size_t _rows, size_t _cols, size_t queries);
  // Get root
  Digest getRoot() { return top[1]; }
  // Do a query, get the row queried for
  std::vector<Fp> query(ReadIop& iop, size_t idx);
  // Get # of rows
  size_t rows() { return _rows; }
  // Get # of col
  size_t cols() { return _cols; }

private:
  size_t _rows;
  size_t _cols;
  size_t topSize;
  std::vector<Digest> top;
};

}  // namespace risc0
