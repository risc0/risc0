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

#pragma once

#include "fp.h"
#include "fpext.h"

struct ShaDigest;

__global__ void eltwise_add_fp(Fp* out, const Fp* x, const Fp* y, const uint32_t count);

__global__ void eltwise_mul_factor_fp(Fp* io, Fp factor, const uint32_t count);

__global__ void eltwise_copy_fp(Fp* out, const Fp* in, const uint32_t count);

__global__ void
eltwise_sum_fpext(Fp* out, const FpExt* in, const uint32_t to_add, const uint32_t count);

__global__ void eltwise_zeroize_fp(Fp* elems);

__global__ void eltwise_zeroize_fpext(FpExt* elems);

__global__ void fri_fold(Fp* out, const Fp* in, const FpExt* mix, const uint32_t count);

__global__ void mix_poly_coeffs(FpExt* out,
                                const Fp* in,
                                const uint32_t* combos,
                                const FpExt* mixStart,
                                const FpExt* mix,
                                const uint32_t inputSize,
                                const uint32_t count);

__global__ void batch_bit_reverse(Fp* io, const uint32_t nBits, const uint32_t count);

__global__ void batch_evaluate_any(
    FpExt* out, const Fp* coeffs, const uint32_t* which, const FpExt* xs, const uint32_t deg);

__global__ void gather_sample(
    Fp* dst, const Fp* src, const uint32_t idx, const uint32_t size, const uint32_t stride);

__global__ void sha_rows(ShaDigest* out, const Fp* matrix, uint32_t count, uint32_t colSize);

__global__ void sha_fold(ShaDigest* out, const ShaDigest* in, uint32_t count);
