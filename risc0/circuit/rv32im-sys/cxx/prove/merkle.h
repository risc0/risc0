// Copyright 2026 RISC Zero, Inc.
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
