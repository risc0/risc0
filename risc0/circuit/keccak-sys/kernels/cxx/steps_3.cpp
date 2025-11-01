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
void step_Top_2(ExecContext& ctx,MutableBuf arg0)   {
// ControlState(zirgen/circuit/keccak/top.zir:295)
// ComputeCurrentStep(zirgen/circuit/keccak/top.zir:335)
set(ctx,arg0, 11, Val(9));
// ControlState(zirgen/circuit/keccak/top.zir:296)
set(ctx,arg0, 12, Val(0));
// ControlState(zirgen/circuit/keccak/top.zir:297)
set(ctx,arg0, 13, Val(0));
return ;
}
void step_Top_18(ExecContext& ctx,MutableBuf arg0)   {
// NextPreimage(zirgen/circuit/keccak/top.zir:183)
// CheckNextPreimage(zirgen/circuit/keccak/top.zir:321)
// Poseidon2NextRound(zirgen/circuit/keccak/top.zir:316)
// ComputeCurrentStep(zirgen/circuit/keccak/top.zir:347)
Val x1 = INVOKE_EXTERN(ctx,nextPreimage);
// builtin NondetReg
set(ctx,arg0, 941, x1);
Val x2 = get(ctx,arg0, 941, 0);
if (to_size_t(x2)) {
// CheckNextPreimage(zirgen/circuit/keccak/top.zir:324)
step_Top_16(ctx,arg0);
}
if (to_size_t((Val(1) - x2))) {
step_Top_17(ctx,arg0);
}
return ;
}

} // namespace risc0::circuit::keccak::cpu
