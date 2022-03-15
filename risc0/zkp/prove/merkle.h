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

#pragma once

#include "risc0/zkp/accel/accel.h"
#include "risc0/zkp/prove/write_iop.h"
#include "risc0/zkp/verify/merkle.h"

#include <vector>

namespace risc0 {

class MerkleTreeProver : public MerkeTreeParams {
public:
  // Gernerate a merkle tree from a matrix of values.  The proofs will prove a single 'column' of
  // values in the tree at a certain row.  Layout is presumed to be packed row-major.  The number of
  // queries represents the expected # of queries and determines the size of the 'top' layer.  It is
  // important that the verifier is constructed with identical size parameters, including # of
  // queries, or verification may fail.
  MerkleTreeProver(AccelConstSlice<Fp> matrix, size_t rowSize, size_t colSize, size_t queries);

  // Write the 'top' of the merkle tree and commit to the root
  void commit(WriteIOP& iop) const;

  // Get the root digest of the tree
  ShaDigest getRoot() const;

  // Generate a proof at a given index, and return the values at that column.  The format of the
  // proof is always: 1) The column itself 2) The 'other' digests up to the top.  It is presumed the
  // verifier is given the index of the row from other parts of the protocol, and verification will
  // of course fail if the wrong row is specified.
  std::vector<Fp> prove(WriteIOP& iop, size_t idx) const;

private:
  // The retained matrix of values
  AccelConstSlice<Fp> matrix;
  // A heap style array where node N has children 2*N and 2*N+1.  The size of
  // this buffer is (1 << (layers + 1)) and begins at offset 1 (zero is unused
  // to make indexing nicer).
  AccelSlice<ShaDigest> nodes;
  // The root value
  ShaDigest root;
  // Buffers to copy proofs though to limit GPU/CPU transfers
  AccelSlice<Fp> colTmp;
  AccelSlice<ShaDigest> proofTmp;
};

} // End namespace risc0
