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

#include "vendor/nvtx3/nvtx3.hpp"

#include <cstdint>
#include <exception>

extern "C" {

const char* risc0_zkp_cuda_eltwise_add_fp(Fp* out, const Fp* x, const Fp* y, uint32_t count) {
  return launchKernel(eltwise_add_fp, count, 0, out, x, y, count);
}

const char* risc0_zkp_cuda_eltwise_mul_factor_fp(Fp* io, Fp factor, uint32_t count) {
  return launchKernel(eltwise_mul_factor_fp, count, 0, io, factor, count);
}

const char* risc0_zkp_cuda_eltwise_copy_fp(Fp* out, const Fp* in, const uint32_t count) {
  return launchKernel(eltwise_copy_fp, count, 0, out, in, count);
}

const char* risc0_zkp_cuda_eltwise_copy_fp_region(Fp* into,
                                                  const Fp* from,
                                                  const uint32_t fromRows,
                                                  const uint32_t fromCols,
                                                  const uint32_t fromOffset,
                                                  const uint32_t fromStride,
                                                  const uint32_t intoOffset,
                                                  const uint32_t intoStride) {
  return launchKernel(eltwise_copy_fp_region,
                      fromRows,
                      0,
                      into,
                      from,
                      fromRows,
                      fromCols,
                      fromOffset,
                      fromStride,
                      intoOffset,
                      intoStride);
}

const char* risc0_zkp_cuda_eltwise_sum_fpext(Fp* out,
                                             const FpExt* in,
                                             const uint32_t to_add,
                                             const uint32_t count) {
  return launchKernel(eltwise_sum_fpext, count, 0, out, in, to_add, count);
}

const char* risc0_zkp_cuda_eltwise_zeroize_fp(Fp* elems, const uint32_t count) {
  return launchKernel(eltwise_zeroize_fp, count, 0, elems);
}

const char* risc0_zkp_cuda_eltwise_zeroize_fpext(FpExt* elems, const uint32_t count) {
  return launchKernel(eltwise_zeroize_fpext, count, 0, elems);
}

const char* risc0_zkp_cuda_fri_fold(Fp* out, const Fp* in, const FpExt* mix, const uint32_t count) {
  return launchKernel(fri_fold, count, 0, out, in, mix, count);
}

const char* risc0_zkp_cuda_mix_poly_coeffs(FpExt* out,
                                           const Fp* in,
                                           const uint32_t* combos,
                                           const FpExt* mixStart,
                                           const FpExt* mix,
                                           const uint32_t inputSize,
                                           const uint32_t count) {
  return launchKernel(mix_poly_coeffs, count, 0, out, in, combos, mixStart, mix, inputSize, count);
}

const char* risc0_zkp_cuda_batch_bit_reverse(Fp* io, const uint32_t nBits, const uint32_t count) {
try {
    CudaStream stream;
    #ifdef LOW_VRAM
    CUDA_OK(cudaStreamSynchronize(stream));
    #endif

    int device;
    CUDA_OK(cudaGetDevice(&device));
    int maxThreads;
    CUDA_OK(cudaDeviceGetAttribute(&maxThreads, cudaDevAttrMaxThreadsPerBlock, device));

    uint32_t rowSize = 1 << nBits;
    uint32_t numRows = count / rowSize;

    int blockSize = maxThreads;
    int blocksPerRow = (rowSize + blockSize - 1) / blockSize;

    dim3 gridDim(blocksPerRow, numRows);
    dim3 blockDim(blockSize);

    cudaLaunchConfig_t config;
    config.attrs = nullptr;
    config.numAttrs = 0;
    config.gridDim = gridDim;
    config.blockDim = blockDim;
    config.dynamicSmemBytes = 0;
    config.stream = stream;

    CUDA_OK(cudaLaunchKernelEx(&config, batch_bit_reverse, io, nBits, count));
    CUDA_OK(cudaStreamSynchronize(stream));
  } catch (const std::exception& err) {
    return strdup(err.what());
  } catch (...) {
    return strdup("Generic exception");
  }
  return nullptr;
}

const char* risc0_zkp_cuda_batch_evaluate_any(FpExt* d_out,
    FpExt* d_chunk_out,
    const Fp* coeffs,
    const uint32_t* which,
    const FpExt* xs,
    const uint32_t eval_n,
    const uint32_t deg,
    const uint32_t chunk_n) {

    try {
        CudaStream stream;
        #ifdef LOW_VRAM
        CUDA_OK(cudaStreamSynchronize(stream));
        #endif
        int device;
        CUDA_OK(cudaGetDevice(&device));
        int maxThreads;
        CUDA_OK(cudaDeviceGetAttribute(&maxThreads, cudaDevAttrMaxThreadsPerBlock, device));
        int block = maxThreads / 4; // 256 threads for better occupancy
        // Use the shared_size passed from Rust, or calculate if needed
        int ssize = block * 4 * sizeof(uint32_t); // Shared memory for FpExt (4 Fp elements)
        int grid  = eval_n * chunk_n; // grid = eval_n * chunk_n blocks

        // Launch batch_evaluate_any kernel to compute chunk results
        cudaLaunchConfig_t config;
        config.attrs            = nullptr;
        config.numAttrs         = 0;
        config.gridDim          = grid;
        config.blockDim         = block;
        config.dynamicSmemBytes = ssize;
        config.stream           = stream;

        CUDA_OK(cudaLaunchKernelEx(&config, batch_evaluate_any, d_chunk_out, coeffs, which, xs, deg, eval_n, chunk_n));

        // Launch merge kernel to combine chunk results

        // int merge_block = 256;
        // int merge_grid = (eval_n + merge_block - 1) / merge_block;
        block = 256;
        grid  = (eval_n + block - 1) / block;

        // cudaLaunchConfig_t merge_config;
        config.attrs            = nullptr;
        config.numAttrs         = 0;
        config.gridDim          = grid;
        config.blockDim         = block;
        config.dynamicSmemBytes = 0;
        config.stream           = stream;

        uint32_t csize = deg / chunk_n;
        CUDA_OK(cudaLaunchKernelEx(&config, batch_evaluate_any_merge, d_out, d_chunk_out, xs, eval_n, chunk_n, csize));

        CUDA_OK(cudaStreamSynchronize(stream));
    } catch (const std::exception& err) {
        return strdup(err.what());
    } catch (...) {
        return strdup("Generic exception");
    }
    return nullptr;
}

__constant__ Fp x_pows[50*5];
const char* risc0_zkp_cuda_batch_evaluate_same_x(Fp* out_host,
                                                 const Fp* coeffs,
                                                 const uint32_t* which,
                                                 const Fp* xs_h,
                                                 uint32_t chunk_n,
                                                 const uint32_t poly_n,
                                                 const uint32_t deg,
                                                 const uint32_t x_n) {
  try {

    size_t out_size = poly_n * chunk_n * sizeof(Fp) * x_n;
    Fp* out_dev = nullptr;
    CUDA_OK(cudaMalloc(&out_dev, out_size));

    CudaStream stream;
    CUDA_OK(cudaStreamSynchronize(stream));
    int device;
    CUDA_OK(cudaGetDevice(&device));
    int maxThreads;
    CUDA_OK(cudaDeviceGetAttribute(&maxThreads, cudaDevAttrMaxThreadsPerBlock, device));
    int block = maxThreads / 4;// / 4; // 256 threads
    int ssize = block * 4;
    int grid  = poly_n * chunk_n;      // poly_n * 4 blocks

    static Fp powxs_h[50*5];
    for (uint32_t i=0; i<x_n; i++) {
        Fp x = xs_h[i];
        powxs_h[i*5] = x;
        powxs_h[i*5 + 1] = x*x;     // x^2
        powxs_h[i*5 + 2] = powxs_h[i*5 + 1]*x; // x^3
        powxs_h[i*5 + 3] = powxs_h[i*5 + 2]*x; // x^4
        powxs_h[i*5 + 4] = pow(x, block*4);      // x^(block*4)
    }
    cudaMemcpyToSymbol(x_pows, &powxs_h, sizeof(powxs_h));
    CUDA_OK(cudaStreamSynchronize(stream));

    cudaLaunchConfig_t config;
    config.attrs = nullptr;
    config.numAttrs = 0;
    config.gridDim = grid;
    config.blockDim = block;
    config.dynamicSmemBytes = ssize;
    config.stream = stream;

    // Launch kernel with device memory
    CUDA_OK(cudaLaunchKernelEx(&config, batch_evaluate_same_x, out_dev, coeffs, which, deg, poly_n, x_n, chunk_n));
    // CUDA_OK(cudaStreamSynchronize(stream));

    // Copy results from device to host
    CUDA_OK(cudaMemcpy(out_host, out_dev, out_size, cudaMemcpyDeviceToHost));

    // Free device memory
    CUDA_OK(cudaFree(out_dev));
    CUDA_OK(cudaStreamSynchronize(stream));
  } catch (const std::exception& err) {
    return strdup(err.what());
  } catch (...) {
    return strdup("Generic exception");
  }
  return nullptr;
}

const char* risc0_zkp_cuda_gather_sample(
    Fp* dst, const Fp* src, const uint32_t idx, const uint32_t size, const uint32_t stride) {
  return launchKernel(gather_sample, size, 0, dst, src, idx, size, stride);
}

const char* risc0_zkp_cuda_gather_samples_batch(Fp* dst,
                                                const Fp* src,
                                                const uint32_t* idxs,
                                                const uint32_t n_idxs,
                                                const uint32_t col_size,
                                                const uint32_t stride) {
  try {
    CudaStream stream;
    int device;
    CUDA_OK(cudaGetDevice(&device));
    int maxThreads;
    CUDA_OK(cudaDeviceGetAttribute(&maxThreads, cudaDevAttrMaxThreadsPerBlock, device));

    // 1D block over col_size, 2D grid (col_blocks, n_idxs).
    int block = maxThreads / 4; // 256 typical
    int col_blocks = (col_size + block - 1) / block;
    dim3 grid(col_blocks, n_idxs);

    cudaLaunchConfig_t config;
    config.attrs = nullptr;
    config.numAttrs = 0;
    config.gridDim = grid;
    config.blockDim = dim3(block);
    config.dynamicSmemBytes = 0;
    config.stream = stream;
    CUDA_OK(cudaLaunchKernelEx(&config, gather_samples_batch,
                               dst, src, idxs, n_idxs, col_size, stride));
    CUDA_OK(cudaStreamSynchronize(stream));
  } catch (const std::exception& err) {
    return strdup(err.what());
  } catch (...) {
    return strdup("Generic exception");
  }
  return nullptr;
}

const char* risc0_zkp_cuda_scatter(Fp* into,
                                   const uint32_t* index,
                                   const uint32_t* offsets,
                                   const Fp* values,
                                   const uint32_t count) {
  return launchKernel(scatter, count, 0, into, index, offsets, values, count);
}

const char* risc0_zkp_cuda_gather_digests_batch(uint32_t* dst,
                                                const uint32_t* src,
                                                const uint32_t* idxs,
                                                const uint32_t n) {
  return launchKernel(gather_digests_batch, n, 0, dst, src, idxs, n);
}

const char*
risc0_zkp_cuda_sha_rows(ShaDigest* output, const Fp* matrix, uint32_t rowSize, uint32_t colSize) {
  return launchKernel(sha_rows, rowSize, 0, output, matrix, rowSize, colSize);
}

const char* risc0_zkp_cuda_sha_fold(ShaDigest* output, const ShaDigest* input, uint32_t count) {
  return launchKernel(sha_fold, count, 0, output, input, count);
}

const char* risc0_zkp_cuda_combos_prepare(FpExt* combos,
                                          const FpExt* coeffU,
                                          const uint32_t comboCount,
                                          const uint32_t cycles,
                                          const uint32_t regsCount,
                                          const uint32_t* regSizes,
                                          const uint32_t* regComboIds,
                                          const uint32_t checkSize,
                                          const FpExt* mix) {

  try {
    CudaStream stream;
    #ifdef LOW_VRAM
    CUDA_OK(cudaStreamSynchronize(stream));
    #endif
    combos_prepare<<<1, 1, 0, stream>>>(
        combos, coeffU, regsCount, regSizes, regComboIds, cycles, mix, checkSize, comboCount);
    CUDA_OK(cudaStreamSynchronize(stream));
  } catch (const std::exception& err) {
    return strdup(err.what());
  }
  return nullptr;
}

} // extern "C"
