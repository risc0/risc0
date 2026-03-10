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

#include "rv32im/emu/trace.h"

#include "core/log.h"
#include "core/util.h"
#include "rv32im/emu/blocks.h"
#include "rv32im/emu/povw.h"

#include <algorithm>
#include <iostream>
#include <vector>

namespace risc0::rv32im {

Trace::Trace(
    size_t maxRows, RowInfo* rows, uint32_t* aux, PovwNonce povwNonce, uint32_t* block_counts)
    : rowBegin(rows)
    , rowNext(rows)
    , rowEnd(rows + maxRows)
    , auxBegin(aux)
    , auxNext(aux)
    , block_counts(block_counts) {
  globals = &makeGlobals();
  globals->p2Count = 0;
  globals->finalCycle = 0;
  globals->v2Compat = 0;
  memcpy(&globals->povwNonce, povwNonce.data(), sizeof(globals->povwNonce));
}

Trace::~Trace() {}

void Trace::finalize() {
  while (rowNext != rowEnd) {
    rowNext->rowType = uint32_t(BlockType::Empty);
    rowNext->blockCount = 0;
    rowNext->auxOffset = 0;
    rowNext++;
  }
  std::stable_sort(
      rowBegin, rowEnd, [](const RowInfo& a, const RowInfo& b) { return a.rowType < b.rowType; });
}

} // namespace risc0::rv32im
