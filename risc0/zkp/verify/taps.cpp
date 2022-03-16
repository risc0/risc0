// Copyright 2022 Risc0, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "risc0/zkp/verify/taps.h"

#include "risc0/core/util.h"

namespace risc0 {

TapSet::TapSet() : finalized_(false) {}

void TapSet::addTap(RegisterGroup group, size_t offset, size_t back) {
  all_[group][offset].insert(back);
}

TapSetRef TapSet::getRef() {
  if (!finalized_) {
    finalize();
  }
  return TapSetRef(&data_);
}

void TapSet::finalize() {
  std::vector<reg_t> combos;
  std::map<reg_t, size_t> combosToID;
  // Pre-insert the 'only self' combo
  std::set<size_t> self = {0};
  combos.push_back(self);
  combosToID.insert(std::make_pair(self, 0));
  // Walk over thing hierarchicly and build flat table
  for (size_t groupID = 0; groupID < kNumRegisterGroups; groupID++) {
    RegisterGroup group = static_cast<RegisterGroup>(groupID);
    // Make sure there is always at least one tap per group
    REQUIRE(all_.count(group));
    // Set the group offset
    data_.groupBegin[groupID] = taps_.size();
    // Look at this group
    group_t& regs = all_[group];
    // Get the count of registers (max + 1)
    size_t regCount = regs.rbegin()->first + 1;
    for (size_t reg = 0; reg < regCount; reg++) {
      // Make sure all registers have at least one tap
      REQUIRE(regs.count(reg));
      // Get the taps for the register
      reg_t combo = regs[reg];
      REQUIRE(combo.size() > 0);
      // If this is a new combo, add it
      if (!combosToID.count(combo)) {
        combosToID[combo] = combos.size();
        combos.push_back(combo);
      }
      // Get the combo ID
      size_t comboID = combosToID[combo];
      // Add the actual taps
      for (size_t back : combo) {
        impl::TapData data;
        REQUIRE(back < 65536);
        REQUIRE(reg < 65536);
        REQUIRE(combo.size() < 256);
        REQUIRE(comboID < 256);
        data.group = group;
        data.offset = reg;
        data.back = back;
        data.combo = comboID;
        data.skip = combo.size();
        taps_.push_back(data);
      }
    }
  }
  data_.groupBegin[kNumRegisterGroups] = taps_.size();
  data_.taps = taps_.data();
  // Now make flat combo state
  for (auto combo : combos) {
    comboBegin_.push_back(comboTaps_.size());
    for (size_t tap : combo) {
      comboTaps_.push_back(tap);
    }
  }
  comboBegin_.push_back(comboTaps_.size());
  REQUIRE(comboTaps_.size() < 65536);
  data_.combos.taps = comboTaps_.data();
  data_.combos.offsets = comboBegin_.data();
  data_.combos.count = combos.size();
  // Set finalize and clear temp data
  finalized_ = true;
  all_.clear();
}

} // namespace risc0
