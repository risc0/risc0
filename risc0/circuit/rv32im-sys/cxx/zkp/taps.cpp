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

#include "zkp/taps.h"
#include "zkp/params.h"

#include <algorithm>
#include <assert.h>

namespace risc0 {

TapManager::TapManager() {}

void TapManager::addTap(uint32_t group, uint32_t col, uint32_t back) {
  taps.emplace_back(group, col, back);
}

void TapManager::done() {
  // Order + dedup taps
  std::sort(taps.begin(), taps.end());
  taps.erase(std::unique(taps.begin(), taps.end()), taps.end());
  assert(!taps.empty());
  // Group into columns
  Column curColumn;
  curColumn.group = taps[0].group;
  curColumn.column = taps[0].column;
  curColumn.begin = taps.data();
  for (const Tap& tap : taps) {
    if (curColumn.group != tap.group || curColumn.column != tap.column) {
      curColumn.end = &tap;
      columns.push_back(curColumn);
      curColumn.group = tap.group;
      curColumn.column = tap.column;
      curColumn.begin = &tap;
    }
  }
  curColumn.end = taps.data() + taps.size();
  columns.push_back(curColumn);
  // Group into groups
  Group curGroup;
  curGroup.group = columns[0].group;
  curGroup.tapBegin = columns[0].begin;
  curGroup.colBegin = columns.data();
  for (const Column& column : columns) {
    if (curGroup.group != column.group) {
      curGroup.tapEnd = column.begin;
      curGroup.colEnd = &column;
      groups.push_back(curGroup);
      curGroup.group = column.group;
      curGroup.tapBegin = column.begin;
      curGroup.colBegin = &column;
    }
  }
  curGroup.tapEnd = taps.data() + taps.size();
  curGroup.colEnd = columns.data() + columns.size();
  groups.push_back(curGroup);
  // Compute all the unique combos
  using ComboVec = std::vector<uint32_t>;
  std::map<ComboVec, uint32_t> comboToId;
  for (const Column& column : columns) {
    ComboVec curCombo;
    for (const Tap& tap : column.getTaps()) {
      curCombo.push_back(tap.back);
    }
    comboToId[curCombo] = 0;
  }
  // Number the combos
  size_t offset = 0;
  for (auto& kvp : comboToId) {
    kvp.second = combos.size();
    combos.emplace_back();
    combos.back().comboId = kvp.second;
    combos.back().offset = offset;
    combos.back().backs = kvp.first;
    offset += kvp.first.size();
  }
  // Attach combo number to taps + columns
  for (const Column& column : columns) {
    ComboVec curCombo;
    for (const Tap& tap : column.getTaps()) {
      curCombo.push_back(tap.back);
    }
    uint32_t comboId = comboToId[curCombo];
    for (const Tap& tap : column.getTaps()) {
      const_cast<Tap&>(tap).comboId = comboId;
    }
    const_cast<Column&>(column).comboId = comboId;
  }
}

size_t TapManager::comboSizeTot() const {
  size_t tot = 0;
  for (const Combo& combo : combos) {
    tot += combo.backs.size();
  }
  return tot;
}

} // namespace risc0
