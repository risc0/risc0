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
#include "fp.h"
#include "fpext.h"
#include "kernels.h"

#include "vendor/nvtx3/nvtx3.hpp"

#include <cstdint>
#include <exception>

extern "C" {

const char* risc0_zkp_cuda_eltwise_add_fp(cudaStream_t stream, Fp* out, const Fp* x, const Fp* y, uint32_t count) {
  return launchKernel(eltwise_add_fp, stream, count, 0, out, x, y, count);
}

const char* risc0_zkp_cuda_eltwise_mul_factor_fp(cudaStream_t stream, Fp* io, Fp factor, uint32_t count) {
  return launchKernel(eltwise_mul_factor_fp, stream, count, 0, io, factor, count);
}

const char* risc0_zkp_cuda_eltwise_copy_fp(cudaStream_t stream, Fp* out, const Fp* in, const uint32_t count) {
  return launchKernel(eltwise_copy_fp, stream, count, 0, out, in, count);
}

const char* risc0_zkp_cuda_eltwise_copy_fp_region(cudaStream_t stream,
                                                  Fp* into,
                                                  const Fp* from,
                                                  const uint32_t fromRows,
                                                  const uint32_t fromCols,
                                                  const uint32_t fromOffset,
                                                  const uint32_t fromStride,
                                                  const uint32_t intoOffset,
                                                  const uint32_t intoStride) {
  return launchKernel(eltwise_copy_fp_region,
                      stream,
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

const char* risc0_zkp_cuda_eltwise_sum_fpext(cudaStream_t stream,
                                             Fp* out,
                                             const FpExt* in,
                                             const uint32_t to_add,
                                             const uint32_t count) {
  return launchKernel(eltwise_sum_fpext, stream, count, 0, out, in, to_add, count);
}

const char* risc0_zkp_cuda_eltwise_zeroize_fp(cudaStream_t stream, Fp* elems, const uint32_t count) {
  return launchKernel(eltwise_zeroize_fp, stream, count, 0, elems, count);
}

const char* risc0_zkp_cuda_eltwise_zeroize_fpext(cudaStream_t stream, FpExt* elems, const uint32_t count) {
  return launchKernel(eltwise_zeroize_fpext, stream, count, 0, elems, count);
}

const char* risc0_zkp_cuda_fri_fold(cudaStream_t stream, Fp* out, const Fp* in, const FpExt* mix, const uint32_t count) {
  return launchKernel(fri_fold, stream, count, 0, out, in, *mix, count);
}

const char* risc0_zkp_cuda_mix_poly_coeffs(cudaStream_t stream,
                                           FpExt* out,
                                           const Fp* in,
                                           const uint32_t* combos,
                                           const FpExt* mixStart,
                                           const FpExt* mix,
                                           const uint32_t inputSize,
                                           const uint32_t count) {
  return launchKernel(
      mix_poly_coeffs, stream, count, 0, out, in, combos, *mixStart, *mix, inputSize, count);
}

const char* risc0_zkp_cuda_batch_bit_reverse(cudaStream_t stream, Fp* io, const uint32_t nBits, const uint32_t count) {
  return launchKernel(batch_bit_reverse, stream, count, 0, io, nBits, count);
}

const char* risc0_zkp_cuda_batch_evaluate_any(cudaStream_t stream,
                                              FpExt* out,
                                              const Fp* coeffs,
                                              const uint32_t* which,
                                              const FpExt* xs,
                                              uint32_t shared_size,
                                              const uint32_t count,
                                              const uint32_t deg) {
  return launchKernel(batch_evaluate_any, stream, count, shared_size, out, coeffs, which, xs, deg);
}

const char* risc0_zkp_cuda_gather_sample(
    cudaStream_t stream, Fp* dst, const Fp* src, const uint32_t idx, const uint32_t size, const uint32_t stride) {
  return launchKernel(gather_sample, stream, size, 0, dst, src, idx, size, stride);
}

const char* risc0_zkp_cuda_scatter(cudaStream_t stream,
                                   Fp* into,
                                   const uint32_t* index,
                                   const uint32_t* offsets,
                                   const Fp* values,
                                   const uint32_t count) {
  return launchKernel(scatter, stream, count, 0, into, index, offsets, values, count);
}

const char*
risc0_zkp_cuda_sha_rows(cudaStream_t stream, ShaDigest* output, const Fp* matrix, uint32_t rowSize, uint32_t colSize) {
  return launchKernel(sha_rows, stream, rowSize, 0, output, matrix, rowSize, colSize);
}

const char* risc0_zkp_cuda_sha_fold(cudaStream_t stream, ShaDigest* output, const ShaDigest* input, uint32_t count) {
  return launchKernel(sha_fold, stream, count, 0, output, input, count);
}

const char* risc0_zkp_cuda_combos_prepare(cudaStream_t stream,
                                          FpExt* combos,
                                          const FpExt* coeffU,
                                          const uint32_t comboCount,
                                          const uint32_t cycles,
                                          const uint32_t regsCount,
                                          const uint32_t* regSizes,
                                          const uint32_t* regComboIds,
                                          const uint32_t checkSize,
                                          const FpExt* mix) {

  try {
    combos_prepare<<<1, 1, 0, stream>>>(
        combos, coeffU, regsCount, regSizes, regComboIds, cycles, mix, checkSize, comboCount);
    CUDA_OK(cudaStreamSynchronize(stream));
  } catch (const std::exception& err) {
    CUDA_OK(cudaStreamSynchronize(stream));
    return strdup(err.what());
  }
  return nullptr;
}

const char* risc0_zkp_cuda_fri_prove(cudaStream_t stream,
                                     uint32_t* out_values,
                                     const size_t values_column_width,
                                     uint32_t* out_digests,
                                     const size_t digests_column_width,
                                     uint32_t* positions,
                                     const size_t positions_len,
                                     CudaMerkleTreeProver* trees,
                                     const size_t trees_len,
                                     uint32_t* groups) {
  try {
    LaunchConfig cfg1 = getSimpleConfig(trees_len * positions_len * values_column_width);
    fri_prove_values<<<cfg1.grid, cfg1.block, 0, stream>>>(
        out_values, values_column_width, positions, positions_len, trees, trees_len, groups);

    LaunchConfig cfg2 = getSimpleConfig(trees_len * positions_len * digests_column_width);
    fri_prove_digests<<<cfg2.grid, cfg2.block, 0, stream>>>(
        out_digests, digests_column_width, positions, positions_len, trees, trees_len, groups);

    CUDA_OK(cudaStreamSynchronize(stream));
  } catch (const std::exception& err) {
    CUDA_OK(cudaStreamSynchronize(stream));
    return strdup(err.what());
  }
  return nullptr;
}

} // extern "C"
