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

#include <array>

#include "zkp/digest.h"
#include "zkp/fp.h"
#include "zkp/fpext.h"

namespace risc0 {

// Hashing functions used by the proof system itself
Digest poseidon2Hash(const Fp* data, size_t size, size_t stride = 1);
Digest poseidon2HashPair(Digest x, Digest y);
// A helper for proofs
inline Digest poseidon2Hash(const FpExt* data, size_t size) {
  return poseidon2Hash(reinterpret_cast<const Fp*>(data), size * 4);
}

namespace p2impl {

constexpr size_t CELLS = 24;
constexpr size_t CELLS_RATE = 16;
constexpr size_t CELLS_DIGEST = 8;
constexpr size_t ROUNDS_HALF_FULL = 4;
constexpr size_t ROUNDS_PARTIAL = 21;

using cells_t = std::array<Fp, CELLS>;

// Raw access to inner poseidon sponge function + friends
void poseidonMultiplyByMExt(cells_t& cells);
void poseidonDoExtRound(cells_t& cells, size_t idx);
void poseidonDoIntRounds(cells_t& cells);
void poseidonSponge(cells_t& cells);

}  // end namespace p2impl

} // namespace risc0
