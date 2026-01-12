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

#include "steps.h"
#include "witgen.h"

namespace risc0::circuit::keccak::cpu {
void step_Top_5(ExecContext& ctx,MutableBuf arg0)   {
// ControlState(zirgen/circuit/keccak/top.zir:296)
Val x1 = get(ctx,arg0, 12, 1);
if (to_size_t(x1)) {
// ComputeCurrentStep(zirgen/circuit/keccak/top.zir:336)
step_Top_3(ctx,arg0);
}
if (to_size_t((Val(1) - x1))) {
step_Top_4(ctx,arg0);
}
return ;
}
void step_Top_21(ExecContext& ctx,MutableBuf arg0)   {
if (to_size_t(get(ctx,arg0, 0, 1))) {
// ComputeCurrentStep(zirgen/circuit/keccak/top.zir:333)
step_Top_1(ctx,arg0);
}
if (to_size_t(get(ctx,arg0, 1, 1))) {
step_Top_2(ctx,arg0);
}
if (to_size_t(get(ctx,arg0, 2, 1))) {
step_Top_5(ctx,arg0);
}
if (to_size_t(get(ctx,arg0, 3, 1))) {
step_Top_6(ctx,arg0);
}
if (to_size_t(get(ctx,arg0, 4, 1))) {
step_Top_7(ctx,arg0);
}
if (to_size_t(get(ctx,arg0, 5, 1))) {
step_Top_8(ctx,arg0);
}
if (to_size_t(get(ctx,arg0, 6, 1))) {
step_Top_9(ctx,arg0);
}
if (to_size_t(get(ctx,arg0, 7, 1))) {
step_Top_10(ctx,arg0);
}
if (to_size_t(get(ctx,arg0, 8, 1))) {
step_Top_13(ctx,arg0);
}
if (to_size_t(get(ctx,arg0, 9, 1))) {
step_Top_19(ctx,arg0);
}
if (to_size_t(get(ctx,arg0, 10, 1))) {
step_Top_20(ctx,arg0);
}
return ;
}

} // namespace risc0::circuit::keccak::cpu
