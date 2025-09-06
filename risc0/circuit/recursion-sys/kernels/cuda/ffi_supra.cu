// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "cuda.h"
#include "supra/fp.h"

extern __constant__ FpExt poly_mix[158];

namespace risc0::circuit::recursion::cuda {

__device__ FpExt poly_fp(uint32_t idx,
                         uint32_t size,
                         const Fp* ctrl,
                         const Fp* out,
                         const Fp* data,
                         const Fp* mix,
                         const Fp* accum);

__global__ void eval_check(Fp* check,
                           const Fp* ctrl,
                           const Fp* data,
                           const Fp* accum,
                           const Fp* mix,
                           const Fp* out,
                           const Fp rou,
                           uint32_t po2,
                           uint32_t domain) {
  uint32_t cycle = blockDim.x * blockIdx.x + threadIdx.x;
  if (cycle < domain) {
    FpExt tot = poly_fp(cycle, domain, ctrl, out, data, mix, accum);
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
    cudaMemcpyToSymbol(poly_mix, poly_mix_pows, sizeof(poly_mix));
    risc0::circuit::recursion::cuda::eval_check<<<cfg.grid, cfg.block, 0, stream>>>(
        check, ctrl, data, accum, mix, out, rou, po2, domain);
    CUDA_OK(cudaStreamSynchronize(stream));
  } catch (const std::exception& err) {
    return strdup(err.what());
  }
  return nullptr;
}
