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

#include "verify/verify.h"

#include "rv32im/base/constants.h"
#include "rv32im/emu/blocks.h"
#include "verify/fri.h"
#include "verify/info/rv32im.h"
#include "verify/merkle.h"
#include "zkp/params.h"
#include "zkp/rou.h"

namespace risc0 {

using namespace rv32im;
void verifyRv32im(ReadIop& iop, size_t po2) {
  VerifyCircuitInfo ci;
  setupVerifyInfo(ci);
  verify(ci, iop, po2);
};

} // namespace risc0
