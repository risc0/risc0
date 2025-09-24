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

#include "rv32im/emu/decode.h"
#include "rv32im/witness/witness.h"

namespace risc0::rv32im {

inline constexpr const char* getBlockTypeName(BlockType type) {
  switch(type) {
#define BLOCK_TYPE(name, count) case BlockType::name: return #name;
BLOCK_TYPES
#undef BLOCK_TYPE
    default: return "***UNKNOWN***";
  }
}

inline constexpr size_t getBlockCountPerRow(BlockType type) {
  switch(type) {
#define BLOCK_TYPE(name, count) case BlockType::name: return count;
BLOCK_TYPES
#undef BLOCK_TYPE
    default: return 0;
  }
}

size_t computeMaxWitPerRow(bool tune = false);
size_t computeMaxDataPerRow(bool tune = false);
size_t computeMaxAccumPerRow(bool tune = false);
size_t computeAccumTopSize();
inline size_t computeTotalAccum() { return computeMaxAccumPerRow() + computeAccumTopSize(); }
size_t computeMaxDegree(bool tune = false);

FpExt computeConstraintPoly(const FpExt* data, const Fp* globals, const FpExt* accMix, FpExt ecMix, FpExt z);

} // namespace risc0::rv32im
