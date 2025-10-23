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

#include "steps.h"
#include "witgen.h"

namespace risc0::circuit::keccak::cpu {
void step_Top_1(ExecContext& ctx,MutableBuf arg0)   {
// ControlState(zirgen/circuit/keccak/top.zir:296)
// ComputeCurrentStep(zirgen/circuit/keccak/top.zir:335)
// Top(zirgen/circuit/keccak/top.zir:369)
set(ctx,arg0, 11, Val(0));
// ControlState(zirgen/circuit/keccak/top.zir:297)
set(ctx,arg0, 12, Val(0));
// ControlState(zirgen/circuit/keccak/top.zir:298)
set(ctx,arg0, 13, Val(0));
return ;
}
void step_Top_17(ExecContext& ctx,MutableBuf arg0)   {
// ControlState(zirgen/circuit/keccak/top.zir:296)
// CheckNextPreimage(zirgen/circuit/keccak/top.zir:328)
// Poseidon2NextRound(zirgen/circuit/keccak/top.zir:317)
// ComputeCurrentStep(zirgen/circuit/keccak/top.zir:348)
set(ctx,arg0, 11, Val(0));
// ControlState(zirgen/circuit/keccak/top.zir:297)
set(ctx,arg0, 12, Val(0));
// ControlState(zirgen/circuit/keccak/top.zir:298)
set(ctx,arg0, 13, Val(0));
return ;
}

} // namespace risc0::circuit::keccak::cpu
