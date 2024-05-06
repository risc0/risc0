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

#include "cuda.h"
#include "fp.h"
#include "fpext.h"
#include "kernels.h"

#include <cstring>
#include <cuda_runtime.h>
#include <stdexcept>

LaunchConfig getSimpleConfig(uint32_t count) {
  int device;
  CUDA_OK(cudaGetDevice(&device));

  int maxThreads;
  CUDA_OK(cudaDeviceGetAttribute(&maxThreads, cudaDevAttrMaxThreadsPerBlock, device));

  int block = maxThreads / 4;
  int grid = (count + block - 1) / block;
  return LaunchConfig{grid, block, 0};
}

extern "C" {

const char* risc0_circuit_rv32im_cuda_step_verify_bytes(
    void* ctx, uint32_t steps, uint32_t count, Fp* ctrl, Fp* io, Fp* data) {
  try {
    CUDA_OK(cudaDeviceSynchronize());

    CudaStream stream;
    auto cfg = getSimpleConfig(count);
    step_verify_bytes<<<cfg.grid, cfg.block, 0, stream>>>(
        ctx, steps, count, ctrl, io, data, nullptr, nullptr);
    CUDA_OK(cudaStreamSynchronize(stream));
  } catch (const std::runtime_error& err) {
    return strdup(err.what());
  }
  return nullptr;
}

const char* risc0_circuit_rv32im_cuda_step_compute_accum(
    void* ctx, uint32_t steps, uint32_t count, Fp* ctrl, Fp* io, Fp* data, Fp* mix, Fp* accum) {
  try {
    CUDA_OK(cudaDeviceSynchronize());

    CudaStream stream;
    auto cfg = getSimpleConfig(count);
    step_compute_accum<<<cfg.grid, cfg.block, 0, stream>>>(
        ctx, steps, count, ctrl, io, data, mix, accum);
    CUDA_OK(cudaStreamSynchronize(stream));
  } catch (const std::runtime_error& err) {
    return strdup(err.what());
  }
  return nullptr;
}

const char* risc0_circuit_rv32im_cuda_step_verify_accum(
    void* ctx, uint32_t steps, uint32_t count, Fp* ctrl, Fp* io, Fp* data, Fp* mix, Fp* accum) {
  try {
    CUDA_OK(cudaDeviceSynchronize());

    CudaStream stream;
    auto cfg = getSimpleConfig(count);
    step_verify_accum<<<cfg.grid, cfg.block, 0, stream>>>(
        ctx, steps, count, ctrl, io, data, mix, accum);
    CUDA_OK(cudaStreamSynchronize(stream));
  } catch (const std::runtime_error& err) {
    return strdup(err.what());
  }
  return nullptr;
}

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
  } catch (const std::runtime_error& err) {
    return strdup(err.what());
  }
  return nullptr;
}

} // extern "C"
