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

#include "cuda.h"
#include "supra/fp.h"

namespace risc0::circuit::recursion::cuda {

__device__ FpExt poly_fp(uint32_t idx,
                         uint32_t size,
                         const Fp* ctrl,
                         const Fp* out,
                         const Fp* data,
                         const Fp* mix,
                         const Fp* accum,
                         const FpExt* poly_mix);

__global__ void eval_check(Fp* check,
                           const Fp* ctrl,
                           const Fp* data,
                           const Fp* accum,
                           const Fp* mix,
                           const Fp* out,
                           const Fp rou,
                           uint32_t po2,
                           uint32_t domain,
                           const FpExt* poly_mix) {
  uint32_t cycle = blockDim.x * blockIdx.x + threadIdx.x;
  if (cycle < domain) {
    FpExt tot = poly_fp(cycle, domain, ctrl, out, data, mix, accum, poly_mix);
    Fp x = pow(rou, cycle);
    Fp y = pow(Fp(3) * x, 1 << po2);
    FpExt ret = tot * inv(y - Fp(1));
    check[domain * 0 + cycle] = ret[0];
    check[domain * 1 + cycle] = ret[1];
    check[domain * 2 + cycle] = ret[2];
    check[domain * 3 + cycle] = ret[3];
  }
}

} // namespace risc0::circuit::recursion::cuda

extern "C" const char* risc0_circuit_recursion_cuda_eval_check(Fp* check,
                                                               const Fp* ctrl,
                                                               const Fp* data,
                                                               const Fp* accum,
                                                               const Fp* mix,
                                                               const Fp* out,
                                                               const Fp& rou,
                                                               uint32_t po2,
                                                               uint32_t domain,
                                                               const FpExt* poly_mix_pows) {

  try {
    CUDA_OK(cudaDeviceSynchronize());
    CudaStream stream;
    LaunchConfig cfg = getSimpleConfig(domain);
    risc0::circuit::recursion::cuda::eval_check<<<cfg.grid, cfg.block, 0, stream>>>(
        check, ctrl, data, accum, mix, out, rou, po2, domain, poly_mix_pows);
    CUDA_OK(cudaStreamSynchronize(stream));
  } catch (const std::exception& err) {
    return strdup(err.what());
  }
  return nullptr;
}
