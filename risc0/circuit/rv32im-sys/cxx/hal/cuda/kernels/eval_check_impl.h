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

#include "hal/cuda/kernels/base.h"
#include "rv32im/circuit/eval_check.h"

template <typename Kernel> int max_legal_1d_block_threads(Kernel k, cudaStream_t stream) {
  constexpr size_t fallbackMaxThreads = 256;
  int device = -1;
  cudaError_t error;

  if (cudaStreamGetDevice(stream, &device) != cudaSuccess) {
    return fallbackMaxThreads;
  }
  cudaDeviceProp prop{};
  if (cudaGetDeviceProperties(&prop, device) != cudaSuccess) {
    return fallbackMaxThreads;
  }

  cudaFuncAttributes attr{};
  if (cudaFuncGetAttributes(&attr, (const void*)k) != cudaSuccess) {
    return fallbackMaxThreads;
  }

  int t = prop.maxThreadsPerBlock;
  t = std::min(t, prop.maxThreadsDim[0]);
  t = std::min(t, attr.maxThreadsPerBlock);
  return t;
}

namespace NAMESPACE {

__global__ void kernel(Fp* check,
                       const Fp* data,
                       const Fp* accum,
                       const Fp* globals,
                       const FpExt* accMix,
                       FpExt ecMix,
                       Fp rou) {
  uint32_t row = blockDim.x * blockIdx.x + threadIdx.x;
  if (row >= (1 << (NUM_ROWS_PO2 + 2))) {
    return;
  }
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
  static int maxThreads = max_legal_1d_block_threads(kernel, stream);

  constexpr size_t NUM_ROWS = size_t(1) << (NUM_ROWS_PO2 + 2);
  size_t blockSize = maxThreads;
  if (blockSize > 512) {
    blockSize = 512;
  }
  if (blockSize > NUM_ROWS) {
    blockSize = NUM_ROWS;
  }
  size_t numBlocks = (NUM_ROWS + blockSize - 1) / blockSize;
  kernel<<<numBlocks, blockSize, 0, stream>>>(check, data, accum, globals, accMix, ecMix, rou);
}
