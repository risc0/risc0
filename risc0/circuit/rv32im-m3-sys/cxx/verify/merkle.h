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
