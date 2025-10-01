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

#include "verify/merkle.h"

#include "core/util.h"

namespace risc0 {

MerkleVerifier::MerkleVerifier(ReadIop& iop, size_t _rows, size_t _cols, size_t queries)
    : _rows(_rows)
    , _cols(_cols)
{
  topSize = std::min(greatestLePo2(queries), _rows);
  top.resize(topSize * 2);
  iop.read(top.data() + topSize, topSize);
  for (size_t i = topSize - 1; i > 0; i--)  {
    top[i] = poseidon2HashPair(top[2*i], top[2*i + 1]);
  }
  iop.commit(top[1]);
}

std::vector<Fp> MerkleVerifier::query(ReadIop& iop, size_t idx) {
  if (idx > _rows) {
    throw std::runtime_error("MerkleVerifier: idx out of range");
  }
  idx += _rows;
  std::vector<Fp> out(_cols);
  iop.read(out.data(), _cols);
  Digest cur = poseidon2Hash(out.data(), _cols);
  Digest other;
  while(idx >= topSize * 2) {
    // Retrieve the other parent from the IOP.
    iop.read(&other, 1);
    // Now ascend to the parent index, and compute the hash there.
    if (idx % 2) {
      cur = poseidon2HashPair(other, cur);
    } else {
      cur = poseidon2HashPair(cur, other);
    }
    idx /= 2;
  }
  if (cur != top[idx]) {
    throw std::runtime_error("MerkleVerifier: Invalid merkle proof");
  }
  return out;
}

}  // namespace risc0
