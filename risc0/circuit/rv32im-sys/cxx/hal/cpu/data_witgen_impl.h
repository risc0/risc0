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

#include "core/util.h"
#include "hal/hal.h"

using risc0::RowInfo;

#include "rv32im/circuit/data_witgen.h"

namespace risc0 {

void FUNCNAME(
    Fp* data, Fp* globals, const RowInfo* info, const uint32_t* aux, uint32_t* tables, Fp rou) {
  size_t NUM_ROWS = size_t(1) << NUM_ROWS_PO2;
  parallel_map(NUM_ROWS, [&data, &globals, info, aux, tables, rou](size_t i) {
    computeRowSet<NUM_ROWS_PO2>(data, globals, info, aux, tables, rou, i);
  });
  parallel_map(NUM_ROWS, [&data, &globals, info, aux, tables, rou](size_t i) {
    computeRowFinalize<NUM_ROWS_PO2>(data, globals, info, aux, tables, rou, i);
  });
}

} // namespace risc0
