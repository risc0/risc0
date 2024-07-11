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
  return launchKernel(batch_bit_reverse, count, 0, io, nBits, count);
}

const char* risc0_zkp_cuda_batch_evaluate_any(FpExt* out,
                                              const Fp* coeffs,
                                              const uint32_t* which,
                                              const FpExt* xs,
                                              uint32_t shared_size,
                                              const uint32_t count,
                                              const uint32_t deg) {
  return launchKernel(batch_evaluate_any, count, shared_size, out, coeffs, which, xs, deg);
}

const char* risc0_zkp_cuda_gather_sample(
    Fp* dst, const Fp* src, const uint32_t idx, const uint32_t size, const uint32_t stride) {
  return launchKernel(gather_sample, size, 0, dst, src, idx, size, stride);
}

const char*
risc0_zkp_cuda_sha_rows(ShaDigest* output, const Fp* matrix, uint32_t rowSize, uint32_t colSize) {
  return launchKernel(sha_rows, rowSize, 0, output, matrix, rowSize, colSize);
}

const char* risc0_zkp_cuda_sha_fold(ShaDigest* output, const ShaDigest* input, uint32_t count) {
  return launchKernel(sha_fold, count, 0, output, input, count);
}

} // extern "C"
