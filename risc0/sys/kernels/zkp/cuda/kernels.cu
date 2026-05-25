// Copyright 2022 Risc0, Inc.
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

#include "fp.h"
#include "fpext.h"

constexpr size_t kFriFold = 16;

/// Compute `ceil(log_2(in))`, i.e. find the smallest value `out` such that `2^out >= in`.
__device__ inline constexpr size_t log2Ceil(size_t in) {
  size_t r = 0;
  while ((1 << r) < in) {
    r++;
  }
  return r;
}

__global__ void batch_bit_reverse(Fp* io, const uint32_t nBits, const uint32_t count) {
    uint32_t rowSize = 1 << nBits;
    uint32_t rowIdx = blockIdx.y;
    uint32_t idx = blockIdx.x * blockDim.x + threadIdx.x;

    uint32_t numRows = count / rowSize;

    if (rowIdx < numRows && idx < rowSize) {
        uint32_t ridx = __brev(idx) >> (32 - nBits);

        if (idx < ridx) {
            size_t baseIdx = rowIdx * rowSize;
            size_t idx1 = baseIdx + idx;
            size_t idx2 = baseIdx + ridx;

            Fp tmp = io[idx1];
            io[idx1] = io[idx2];
            io[idx2] = tmp;
        }
    }
}

__global__ void batch_evaluate_any(
    FpExt* out, const Fp* coeffs, const uint32_t* which, const FpExt* xs, const uint32_t deg,
    const uint32_t eval_n, const uint32_t chunk_n) {

    uint32_t x_idx = blockIdx.x % eval_n;
    uint32_t chunk = blockIdx.x / eval_n;
    uint32_t poly = which[x_idx];

    const Fp* coeff = coeffs + poly * deg;
    FpExt x = xs[x_idx];

    size_t cidx = chunk * (deg / chunk_n) + threadIdx.x*4;
    FpExt stepx = pow(x, blockDim.x*4);
    FpExt powx  = pow(x, cidx);

    FpExt tot, tot1, tot2, tot3;
    // FpExt x2 = x * x;
    // FpExt x3 = x2 * x;

    #pragma unroll 1
    for (size_t i = threadIdx.x; i < deg/(4*chunk_n); i += blockDim.x) {
        // size_t idx = base_idx + i * 4;

        uint4 vec = *reinterpret_cast<const uint4*>(&coeff[cidx]);
        Fp c0 = Fp::fromRaw(vec.x);
        Fp c1 = Fp::fromRaw(vec.y);
        Fp c2 = Fp::fromRaw(vec.z);
        Fp c3 = Fp::fromRaw(vec.w);

        tot  += powx * c0;
        tot1 += powx * c1;// * x;
        tot2 += powx * c2;// * x2;
        tot3 += powx * c3;// * x3;

        powx *= stepx;
        cidx += blockDim.x*4;
    }
    tot += x*(tot1 + (x*(tot2 + (tot3*x))));

    extern __shared__ uint32_t totsBuf[];
    FpExt* tots = reinterpret_cast<FpExt*>(totsBuf);
    tots[threadIdx.x] = tot;
    __syncthreads();

    unsigned cur = blockDim.x;
    while (cur) {
        cur /= 2;
        if (threadIdx.x < cur) {
            tots[threadIdx.x] = tots[threadIdx.x] + tots[threadIdx.x + cur];
        }
        __syncthreads();
    }

    if (threadIdx.x == 0) {
        out[blockIdx.x] = tots[0];
    }
}

// Merge chunk results for batch_evaluate_any
__global__ void batch_evaluate_any_merge(
    FpExt* out, const FpExt* chunk_out, const FpExt* xs,
    const uint32_t eval_n, const uint32_t chunk_n, const uint32_t csize) {

    uint32_t i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i >= eval_n) return;

    FpExt x = xs[i];
    // FpExt xp = pow(x, csize);

    FpExt y = chunk_out[i];
    // FpExt xpow = FpExt(1);
    for (uint32_t c = 1; c < chunk_n; c++) {
        // xpow = xpow * xp;
        y += chunk_out[i + eval_n * c];
        // y = y + (chunk_out[i + eval_n * c] * xpow);
    }
    out[i] = y;
}

extern __constant__ Fp x_pows[50*5];
// out_dev, coeffs, which, x_pows, deg, poly_n, 1, chunk_n
__global__ void batch_evaluate_same_x(
    Fp* out, const Fp* coeffs, const uint32_t* which, const uint32_t deg,
    const uint32_t poly_n, const uint32_t x_n, const uint32_t chunk_n) {

    int poly  = blockIdx.x % poly_n;
    int chunk = blockIdx.x / poly_n;
    const Fp* coeff = coeffs + poly * deg;

    Fp sum[25], powx[25];
    #pragma unroll
    for (uint32_t xid=0; xid<x_n; xid++) {
        sum[xid] = Fp(0);
        powx[xid] = pow(x_pows[xid*5 + 3], threadIdx.x);
    }

    size_t cidx = (chunk * (deg / chunk_n)) + (threadIdx.x*4);

    #pragma unroll 1
    for (uint32_t j=0, i = threadIdx.x; i < deg/(4*chunk_n); i += blockDim.x, j++) {

        uint4 vec = *reinterpret_cast<const uint4*>(&coeff[cidx]);
        Fp c0 = Fp::fromRaw(vec.x);
        Fp c1 = Fp::fromRaw(vec.y);
        Fp c2 = Fp::fromRaw(vec.z);
        Fp c3 = Fp::fromRaw(vec.w);

        #pragma unroll
        for (uint32_t xid=0; xid<x_n; xid++) {
            //         0  1    2    3    4
            // x_pows, x, x^2, x^3, x^4, x^(block*4)
            // sum[xid] += powx[xid] * c0;
            // sum[xid] += powx[xid] * c1 * x_pows[xid*5];     // x
            // sum[xid] += powx[xid] * c2 * x_pows[xid*5 + 1]; // x^2
            // sum[xid] += powx[xid] * c3 * x_pows[xid*5 + 2]; // x^3

            Fp tmp = c0 + (c1*x_pows[xid*5])     +
                          (c2*x_pows[xid*5 + 1]) +
                          (c3*x_pows[xid*5 + 2]);
            sum[xid] += powx[xid] * tmp;

            powx[xid] *= x_pows[xid*5 + 4];
        }

        cidx += blockDim.x*4;
    }

    const unsigned int laneId = threadIdx.x % 32;// warpSize;
    const unsigned int warpId = threadIdx.x / 32; //warpSize;

    #pragma unroll
    for (uint32_t xid=0; xid<x_n; xid++) {
        Fp tot = sum[xid];

        for (int offset = 16; offset > 0; offset /= 2) { // 4
            uint32_t other_val = __shfl_down_sync(0xffffffff, tot.asRaw(), offset);
            tot = tot + Fp::fromRaw(other_val);
        }

        extern __shared__ uint32_t totsBuf[];
        Fp* tots = reinterpret_cast<Fp*>(totsBuf);
        if (laneId == 0) {
            tots[warpId] = tot;
        }
        __syncthreads();

        unsigned cur = (blockDim.x + 32 - 1) / 32; // 8
        while (cur) {
            cur /= 2;
            if (threadIdx.x < cur) {
                tots[threadIdx.x] = tots[threadIdx.x] + tots[threadIdx.x + cur];
            }
            __syncthreads();
        }

        if (threadIdx.x == 0) {
            out[blockIdx.x + xid*gridDim.x] = tots[0];
        }
    }

    // out[blockIdx.x] = tot;
}

__global__ void fri_fold(Fp* out, const Fp* in, const FpExt* mix, const uint32_t count) {
  uint idx = blockIdx.x * blockDim.x + threadIdx.x;
  if (idx < count) {
    FpExt tot;
    FpExt curMix(1);
    for (uint32_t i = 0; i < kFriFold; i++) {
      size_t rev_i = __brev(i) >> (32 - log2Ceil(kFriFold));
      size_t rev_idx = rev_i * count + idx;
      FpExt factor(in[0 * count * kFriFold + rev_idx],
                   in[1 * count * kFriFold + rev_idx],
                   in[2 * count * kFriFold + rev_idx],
                   in[3 * count * kFriFold + rev_idx]);
      tot += curMix * factor;
      curMix *= *mix;
    }
    for (size_t i = 0; i < 4; i++) {
      out[count * i + idx] = tot.elems[i];
    }
  }
}

__global__ void gather_sample(
    Fp* dst, const Fp* src, const uint32_t idx, const uint32_t size, const uint32_t stride) {
  uint gid = blockIdx.x * blockDim.x + threadIdx.x;
  if (gid < size) {
    dst[gid] = src[gid * stride + idx];
  }
}

// One launch handles n_idxs row pickups. blockIdx.y indexes into idxs[].
__global__ void gather_samples_batch(Fp* dst,
                                     const Fp* src,
                                     const uint32_t* idxs,
                                     const uint32_t n_idxs,
                                     const uint32_t col_size,
                                     const uint32_t stride) {
  uint gid = blockIdx.x * blockDim.x + threadIdx.x; // 0..col_size
  uint k = blockIdx.y;                              // 0..n_idxs
  if (gid < col_size && k < n_idxs) {
    uint32_t idx = idxs[k];
    dst[k * col_size + gid] = src[gid * stride + idx];
  }
}

// Gather n digests (8 × u32 each) from src[idxs[k]] into dst[k]. One thread per digest.
// Used to batch the per-idx merkle-path get_at into one kernel + one D2H instead of
// ~50 × depth tiny cudaMemcpy calls.
__global__ void gather_digests_batch(uint32_t* dst,
                                     const uint32_t* src,
                                     const uint32_t* idxs,
                                     const uint32_t n) {
  uint k = blockIdx.x * blockDim.x + threadIdx.x;
  if (k < n) {
    uint32_t idx = idxs[k];
    #pragma unroll
    for (int i = 0; i < 8; i++) {
      dst[k * 8 + i] = src[idx * 8 + i];
    }
  }
}

__global__ void scatter(Fp* into,
                        const uint32_t* index,
                        const uint32_t* offsets,
                        const Fp* values,
                        const uint32_t count) {
  uint gid = blockIdx.x * blockDim.x + threadIdx.x;
  if (gid < count) {
    for (uint32_t idx = index[gid]; idx < index[gid + 1]; idx++) {
      into[offsets[idx]] = values[idx];
    }
  }
}

__global__ void mix_poly_coeffs(FpExt* out,
                                const Fp* in,
                                const uint32_t* combos,
                                const FpExt* mixStart,
                                const FpExt* mix,
                                const uint32_t inputSize,
                                const uint32_t count) {
  uint idx = blockIdx.x * blockDim.x + threadIdx.x;
  if (idx < count) {
    FpExt cur = *mixStart;
    for (size_t i = 0; i < inputSize; i++) {
      size_t id = combos[i];
      out[count * id + idx] += cur * in[count * i + idx];
      cur *= *mix;
    }
  }
}
