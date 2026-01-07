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
#include "rv32im/emu/blocks.h"
#include "rv32im/emu/povw.h"
#include "zkp/fp.h"

#include <deque>

namespace risc0::rv32im {

struct Trace {
private:
  RowInfo* rowBegin;
  RowInfo* rowNext;
  RowInfo* rowEnd;
  uint32_t* auxBegin;
  uint32_t* auxNext;
  GlobalsWitness* globals;
  uint32_t userCycles = 0;

#define BLOCK_TYPE(name, count)                                                                    \
  RowInfo* row##name = nullptr;                                                                    \
  name##Witness* wit##name##Begin = nullptr;                                                       \
  name##Witness* wit##name##End = nullptr;
  BLOCK_TYPES
#undef BLOCK_TYPE

public:
  Trace(size_t maxRows, RowInfo* rows, uint32_t* aux, PovwNonce povwNonce);
  ~Trace();

  inline GlobalsWitness& getGlobals() { return *globals; }

  inline size_t getRowCount() const { return rowNext - rowBegin; }
  inline size_t getAuxSize() const { return auxNext - auxBegin; }

#define BLOCK_TYPE(name, count)                                                                    \
  inline name##Witness& make##name() {                                                             \
    if (wit##name##Begin == wit##name##End) {                                                      \
      wit##name##Begin = reinterpret_cast<name##Witness*>(auxNext);                                \
      wit##name##End = wit##name##Begin + count;                                                   \
      row##name = rowNext++;                                                                       \
      row##name->rowType = size_t(BlockType::name);                                                \
      row##name->blockCount = 0;                                                                   \
      row##name->auxOffset = auxNext - auxBegin;                                                   \
      auxNext = reinterpret_cast<uint32_t*>(wit##name##End);                                       \
    }                                                                                              \
    row##name->blockCount++;                                                                       \
    return *wit##name##Begin++;                                                                    \
  }
  BLOCK_TYPES
#undef BLOCK_TYPE

  // Must be called before the accessors below
  void finalize();

  const RowInfo* getRows() const { return rowBegin; }
  const uint32_t* getAux() const { return auxBegin; }

  void setUserCycles(uint32_t cycles) { userCycles = cycles; }
  inline uint32_t getUserCycles() const { return userCycles; }
};

} // namespace risc0::rv32im
