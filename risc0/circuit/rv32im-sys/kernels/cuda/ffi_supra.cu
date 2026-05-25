// Copyright 2024 RISC Zero, Inc.
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

#include "eval_check.cuh"

#include "cuda.h"
#include "supra/fp.h"

#include <exception>

namespace risc0::circuit::rv32im_v2::cuda {

__constant__ FpExt poly_mix[kNumPolyMixPows];
#ifdef LOW_VRAM
__constant__ size_t INV_RATE;
#endif

#ifdef LOW_VRAM
__launch_bounds__(32, 4) __global__ void eval_check_interleave(Fp* check,
    const Fp* ctrl,
    const Fp* data,
    const Fp* accum,
    const Fp* mix,
    const Fp* out,
    const Fp rou,
    uint32_t po2,
    uint32_t domain,
    uint32_t codeword_id) {

    uint32_t cycle = blockDim.x * blockIdx.x + threadIdx.x;
    if (cycle < domain) {

        FpExt tot = poly_fp(cycle, domain, ctrl, out, data, mix, accum);

        Fp x = pow(rou, 4*cycle + codeword_id);
        Fp y = pow(Fp(3) * x, 1 << po2);
        FpExt ret = tot * inv(y - Fp(1));
        check[domain * 0  + 4*cycle + codeword_id] = ret[0];
        check[domain * 4  + 4*cycle + codeword_id] = ret[1];
        check[domain * 8  + 4*cycle + codeword_id] = ret[2];
        check[domain * 12 + 4*cycle + codeword_id] = ret[3];
    }
}
#endif

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

} // namespace risc0::circuit::rv32im_v2::cuda

using namespace risc0::circuit::rv32im_v2::cuda;

extern "C" {


#ifdef LOW_VRAM
const char* risc0_circuit_rv32im_cuda_eval_check(Fp* check,
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
    auto cfg = getSimpleConfig(domain);
    const size_t inv_rate = 4;
    cudaMemcpyToSymbol(poly_mix, poly_mix_pows, sizeof(poly_mix));
    cudaMemcpyToSymbol(INV_RATE, &inv_rate, sizeof(size_t));

    cfg.block.x >>= 3;
    cfg.grid.x  <<= 3;

    eval_check<<<cfg.grid, cfg.block, 0, stream>>>(
    check, ctrl, data, accum, mix, out, rou, po2, domain);

    CUDA_OK(cudaStreamSynchronize(stream));
} catch (const std::exception& err) {
return strdup(err.what());
} catch (...) {
return strdup("Generic exception");
}
return nullptr;
}

const char* risc0_circuit_rv32im_cuda_eval_check_interleave(Fp* check,
    const Fp* ctrl,
    const Fp* data,
    const Fp* accum,
    const Fp* mix,
    const Fp* out,
    const Fp& rou,
    uint32_t po2,
    const FpExt* poly_mix_pows,
    uint32_t codeword_id) {
try {
    CUDA_OK(cudaDeviceSynchronize());

    CudaStream stream;
    uint32_t domain = 1<<po2;

    const size_t inv_rate = 1;
    cudaMemcpyToSymbol(poly_mix, poly_mix_pows, sizeof(poly_mix));
    cudaMemcpyToSymbol(INV_RATE, &inv_rate, sizeof(size_t));
    CUDA_OK(cudaStreamSynchronize(stream));

    uint32_t block = 32;
    uint32_t grid  = (domain + block-1) / block;

    eval_check_interleave<<<grid, block, 0, stream>>>(
    check, ctrl, data, accum, mix, out, rou, po2, domain, codeword_id);

    CUDA_OK(cudaStreamSynchronize(stream));

} catch (const std::exception& err) {
return strdup(err.what());
} catch (...) {
return strdup("Generic exception");
}
return nullptr;
}

#else
const char* risc0_circuit_rv32im_cuda_eval_check(Fp* check,
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
auto cfg = getSimpleConfig(domain);
cudaMemcpyToSymbol(poly_mix, poly_mix_pows, sizeof(poly_mix));
eval_check<<<cfg.grid, cfg.block, 0, stream>>>(
check, ctrl, data, accum, mix, out, rou, po2, domain);
CUDA_OK(cudaStreamSynchronize(stream));
} catch (const std::exception& err) {
return strdup(err.what());
} catch (...) {
return strdup("Generic exception");
}
return nullptr;
}
#endif

} // extern "C"
