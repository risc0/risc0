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

#include <memory>
#include <vector>

#include "risc0/core/util.h"
#include "risc0/zkp/verify/read_iop.h"

namespace risc0 {

// Support for merkle trees, but with a very narrow focus: specifically matrixes of Fp values, where
// each column is hashed as a whole column and then the rows are rolled up in a binary tree (and the
// number of rows are a power of two).  Each proof then verifies a single column.  Additionally, as
// an optimization,  we send a full layer of the merkle tree and not just the root in advance of
// sending a lot of queries / proofs, to prevent needless duplication on the 'top' section of the
// proofs, since for example the top 2 nodes will be used over and over. Thus, the last few 'steps'
// of each proof are ommited, but we must validate the top of the tree seperately.
//
// Since Fp values fit nicely into uint32_t values, as do the hashes, we represent a proof a simple
// vector of uint32_t values.  We thus really only need two objects: The generator of proofs, and
// the verifier of proofs.  The verifier itself returns void and throws on any validation error,
// since errors are unexpected.  The verifier also checks the 'top' and throws during construction.
// Also, the verifier does check the uint32_t values that are part of the column are in range.

// We begin with a base class the computes the relevant parameters (mostly the top layer + size)
// from the specified inputs (rowSize, colSize, queries) to reduce code duplication.
class MerkeTreeParams {
public:
  MerkeTreeParams(size_t rowSize, size_t colSize, size_t queries);

protected:
  // The size of a row (i.e. the number of columns)
  size_t rowSize;
  // The size of a column (i.e. the number of rows)
  size_t colSize;
  // The expected number of queries
  size_t queries;
  // Number of layers.  A 'zero' level/layer tree has a single root that is also
  // a leaf, whereas a 4 level tree has 16 roots, and 15 non-leaf nodes,
  // including the root.
  size_t layers;
  // The 'top' layer selected
  size_t topLayer;
  // The size of the top layer
  size_t topSize;
};

class MerkleTreeVerifier : public MerkeTreeParams {
public:
  // Construct a merkle tree verifier, reading the top from the IOP, commit to root.
  MerkleTreeVerifier(ReadIOP& iop, size_t rowSize, size_t colSize, size_t queries);

  // Get the root digest of the tree
  ShaDigest getRoot() const;

  // Verify a proof, return the column values, throw on error
  std::vector<Fp> verify(ReadIOP& iop, size_t idx) const;

private:
  std::vector<ShaDigest> top;
};

} // End namespace risc0
