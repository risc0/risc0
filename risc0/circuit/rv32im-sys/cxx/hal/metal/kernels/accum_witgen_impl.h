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

#include "base.h"
#include "rv32im/circuit/accum_witgen.h"

kernel void FUNCNAME_APPEND(phase1)(device Fp* accum,
                     const device Fp* data,
                     const device Fp* globals,
                     const device FpExt* accMix,
                     const device Fp& rou,
                     uint row [[thread_position_in_grid]]
                     ) {
  computeRowPhase1<NUM_ROWS_PO2>(accum, data, globals, accMix, rou, row);
}

kernel void FUNCNAME_APPEND(phase2)(device Fp* accum,
                     const device Fp* data,
                     const device Fp* globals,
                     const device FpExt* accMix,
                     const device Fp& rou,
                     uint row [[thread_position_in_grid]]
                     ) {
  computeRowPhase2<NUM_ROWS_PO2>(accum, data, globals, accMix, rou, row);
}

