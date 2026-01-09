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

#include "prove/merkle.h"
#include "core/util.h"

namespace risc0 {

MerkleProver::MerkleProver(IHalPtr hal, HalMatrix<Fp> input, size_t queries)
    : hal(hal), input(input) {
  topSize = std::min(greatestLePo2(queries), input.rows());
  size_t steps = log2Ceil(input.rows()) - log2Ceil(topSize);
  size_t querySize = steps * p2impl::CELLS_DIGEST + input.cols();
  tree = hal->allocateArray<Digest>(2 * input.rows());
  queryTmp = hal->allocateArray<Fp>(querySize);
}

void MerkleProver::compute(WriteIop& iop) {
  size_t size = input.rows();
  hal->hashRows(tree.slice(size, size), input);
  while (size != 1) {
    hal->hashFold(tree.slice(size / 2, size / 2), tree.slice(size, size));
    size /= 2;
  }
  // Get 'top' of tree
  PinnedArrayRO<Digest> topBuf(hal, tree.slice(1, 2 * topSize));
  // Set the root
  root = topBuf[0];
  // Write top to iop
  iop.write(topBuf.data() + topSize - 1, topSize);
  // Commit root
  iop.commit(root);
}

void MerkleProver::query(WriteIop& iop, size_t idx) {
  if (idx > 2 * input.rows()) {
    throw std::runtime_error("MerkleProver: idx out of range");
  }
  hal->query(queryTmp, input, tree, topSize, idx);
  PinnedArrayRO<Fp> queryCopy(hal, queryTmp);
  iop.write(queryCopy.data(), queryCopy.size());
}

} // namespace risc0
