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

#include "hal/cuda/kernels/base.h"
#include "rv32im/circuit/eval_check.h"

namespace NAMESPACE {

__global__ void kernel(Fp* check,
                       const Fp* data,
                       const Fp* accum,
                       const Fp* globals,
                       const FpExt* accMix,
                       FpExt ecMix,
                       Fp rou) {
  uint32_t row = blockDim.x * blockIdx.x + threadIdx.x;
  computeRow<NUM_ROWS_PO2>(check, data, accum, globals, accMix, ecMix, rou, row);
}

} // namespace NAMESPACE

using namespace NAMESPACE;

extern "C" void FUNCNAME(cudaStream_t stream,
                         Fp* check,
                         const Fp* data,
                         const Fp* accum,
                         const Fp* globals,
                         const FpExt* accMix,
                         FpExt ecMix,
                         Fp rou) {
  constexpr size_t NUM_ROWS = size_t(1) << (NUM_ROWS_PO2 + 2);
  constexpr size_t block_size = NUM_ROWS < 256 ? NUM_ROWS : 256;
  constexpr size_t num_blocks = (NUM_ROWS + block_size - 1) / block_size;
  kernel<<<num_blocks, block_size, 0, stream>>>(check, data, accum, globals, accMix, ecMix, rou);
}
