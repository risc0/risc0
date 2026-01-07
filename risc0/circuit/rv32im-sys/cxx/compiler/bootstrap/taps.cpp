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

#include "core/log.h"
#include "verify/info/rv32im.h"

#include <fstream>
#include <string>

static std::string prefix = R"***(// Copyright 2025 RISC Zero, Inc.
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

use super::super::verify::CircuitInfo;
use risc0_zkp::{
    adapter::TapsProvider,
    taps::{TapData, TapSet},
};

pub const TAPSET: &TapSet = &TapSet::<'static> {
)***";

static std::string suffix = R"***(
impl TapsProvider for CircuitInfo {
    fn get_taps(&self) -> &'static TapSet<'static> {
        TAPSET
    }
}
)***";

using namespace risc0;

void emitTaps(const std::string path) {
  std::fstream outs;
  outs.open(path, std::ios::out);
  if (!outs.is_open()) {
    LOG(0, "Could not open '" << path << "' to create taps file");
    throw std::runtime_error("File IO");
  }

  VerifyCircuitInfo ci;
  setupVerifyInfo(ci);
  auto& taps = ci.taps;

  outs << prefix;
  outs << "    taps: &[\n";
  for (const Column& col : taps.getColumns()) {
    size_t count = col.getTaps().size();
    for (const Tap& tap : col.getTaps()) {
      outs << "        TapData {\n";
      outs << "            offset: " << tap.column << ",\n";
      outs << "            back: " << tap.back << ",\n";
      outs << "            group: " << tap.group << ",\n";
      outs << "            combo: " << tap.comboId << ",\n";
      outs << "            skip: " << count << ",\n";
      outs << "        },\n";
    }
  }
  outs << "    ],\n";
  outs << "    combo_taps: &[";
  bool first = true;
  for (const Combo& combo : taps.getCombos()) {
    for (uint32_t back : combo.backs) {
      if (!first)
        outs << ", ";
      first = false;
      outs << back;
    }
  }
  outs << "],\n";
  outs << "    combo_begin: &[";
  size_t idx = 0;
  for (const Combo& combo : taps.getCombos()) {
    outs << idx << ", ";
    idx += combo.backs.size();
  }
  outs << idx << "],\n";
  outs << "    group_begin: &[";
  idx = 0;
  for (const Group& group : taps.getGroups()) {
    outs << idx << ", ";
    idx += group.getTaps().size();
  }
  outs << idx << "],\n";
  outs << "    combos_count: " << taps.getCombos().size() << ",\n";
  outs << "    reg_count: " << taps.getColumns().size() << ",\n";
  outs << "    tot_combo_backs: " << taps.comboSizeTot() << ",\n";
  // TODO: group_names is hardcoded
  outs << "    group_names: &[\"data\", \"accum\"],\n";
  outs << "};\n";
  outs << suffix;
}
