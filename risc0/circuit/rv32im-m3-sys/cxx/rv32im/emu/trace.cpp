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

#include "rv32im/emu/trace.h"

#include "core/log.h"
#include "core/util.h"
#include "rv32im/emu/blocks.h"

#include <algorithm>
#include <execution>
#include <iostream>
#include <vector>

namespace risc0::rv32im {

Trace::Trace(size_t maxRows, RowInfo* rows, uint32_t* aux)
    : rowBegin(rows), rowNext(rows), rowEnd(rows + maxRows), auxBegin(aux), auxNext(aux) {
  globals = &makeGlobals();
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
