// Copyright Supranational LLC
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#if !defined(__SPPARK_POLYNOMIAL_EVALUATE_CUH__) && \
    (defined(__CUDACC__) || defined(__HIPCC__))
#define __SPPARK_POLYNOMIAL_EVALUATE_CUH__

#include <cassert>
#ifdef __HIPCC__
# include <hip/hip_cooperative_groups.h>
#else
# include <cooperative_groups.h>
#endif
#include <ff/shfl.cuh>
#include <util/vec2d_t.hpp>

template<int N, class fr_t>
constexpr static int d_evaluate_bsize()
{   return N*sizeof(fr_t) <= 48 ? 1024 : 512;   }

template<int N, class fr_t>
__global__ __launch_bounds__(d_evaluate_bsize<N, fr_t>())
void d_evaluate(fr_t ret[/*nx*/], const fr_t x[/*nx*/], int nx, // nx <= N
                const fr_t coeffs[/*len*/], size_t len,
                size_t top_row, fr_t scratch[/*N][gridDim.x*/])
{
#if 0
    assert(blockDim.x%WARP_SZ == 0 && gridDim.x <= blockDim.x && nx <= N);
#endif

    struct warp {
        /*
         * Compiler apparently doesn't fuse loops, at least not these ones,
         * it has to be done "manually."
         */
        __device__ __forceinline__
        static void redux(fr_t x_lanes[N], unsigned limit = WARP_SZ)
        {
            #pragma unroll 1
            for (unsigned off = 1u << (32 - __clz(limit-1)); off >>= 1;) {
                #pragma unroll
                for (int i = 0; i < N; i++)
                    x_lanes[i] += shfl_down(x_lanes[i], off);
            }
        }
    };

    const uint32_t tid    = threadIdx.x + blockDim.x*blockIdx.x;
    const uint32_t laneid = threadIdx.x % WARP_SZ;
    const uint32_t warpid = threadIdx.x / WARP_SZ;
    const uint32_t nwarps = blockDim.x  / WARP_SZ;

    extern __shared__ int xchg_evaluate[];
    fr_t (*xchg)[WARP_SZ] = reinterpret_cast<decltype(xchg)>(xchg_evaluate);

    /*
     * Calculate ascending powers of |x| in ascending threads across
     * the grid and the |x|^(blockDim.x*gridDim.x). Since the kernel
     * is invoked cooperatively, gridDim.x would be not larger than
     * the amount of SMs, which would be far from the limit for this
     * part of the implementation, 33*32+1. ["This part" refers to
     * the fact that a stricter limitation is implied elsewhere,
     * gridDim.x <= blockDim.x.]
     */
    fr_t x_pow_grid[N];
    fr_t x_top_grid[N];
    fr_t (*tmp)[WARP_SZ] = &xchg[2*(N-1)*warpid];

    fr_t prefetch_x = x[nx-1];

    __builtin_assume(nx > 0);

    #pragma unroll 1
    for (int i = N==1 ? N : nx; i--;) {
        x_pow_grid[0] = mul_up(prefetch_x);             // x^(laneid+1)

        if (N > 1)
            prefetch_x = x[i > 0 ? i-1 : 0];

        fr_t x_pow = shfl_idx(x_pow_grid[0], WARP_SZ-1);
        x_pow = mul_up(x_pow, nwarps);
        if (warpid != 0)
            x_pow_grid[0] *= shfl_idx(x_pow, warpid-1); // x^(threadIdx.x+1)

        x_top_grid[0] = shfl_idx(x_pow, nwarps-1);      // x^(blockDim.x*gridDim.x)

        if (gridDim.x > 1) {
            x_pow = x_top_grid[0];
            x_pow = mul_up(x_pow, min(WARP_SZ, gridDim.x));
            x_top_grid[0] = shfl_idx(x_pow, (gridDim.x - 1)%WARP_SZ);
            fr_t x_pow_block = shfl_idx(x_pow, (blockIdx.x - 1)%WARP_SZ);

            if (gridDim.x > WARP_SZ) {
                x_pow = shfl_idx(x_pow, WARP_SZ - 1);
                x_pow = mul_up(x_pow, (gridDim.x + WARP_SZ - 1)/WARP_SZ);
                x_top_grid[0] *= shfl_idx(x_pow, (gridDim.x - 1)/WARP_SZ - 1);
                if (blockIdx.x > WARP_SZ)
                    x_pow_block *= shfl_idx(x_pow, (blockIdx.x - 1)/WARP_SZ - 1);
            }

            if (blockIdx.x != 0)
                x_pow_grid[0] *= x_pow_block;           // x^(tid+1)
        }

        if (i != 0) {
            tmp[2*i-2][laneid] = x_pow_grid[0];
            tmp[2*i-1][laneid] = x_top_grid[0];
        }
    }

    #pragma unroll
    for (int i = 1; i < N; i++) {
        x_pow_grid[i] = tmp[2*i-2][laneid];
        x_top_grid[i] = tmp[2*i-1][laneid];
    }

#if 0
    auto check = x[0]^(tid+1);
    check -= x_pow_grid[0];
    assert(check.is_zero());
    check = x[0]^(blockDim.x*gridDim.x);
    check -= x_top_grid[0];
    assert(check.is_zero());
#endif

    /*
     * Accumulate cᵢ⋅xⁱ evaluations by "column[s]":
     *
     * c1*x   c2*x^2 c3*x^3 c4*x^4
     * c5*x^5 c6*x^6 c7*x^7 c8*x^8
     * c9*x^9 ...
     */
    fr_t accum[N];

    #pragma unroll
    for (int i = 0; i < N; i++)
        accum[i].zero();

    size_t idx = top_row + tid;
    bool done = idx >= len;

    fr_t prefetch;
#ifdef __CUDA_ARCH__
    if (!done)
        prefetch = coeffs[idx];
#else
    prefetch = coeffs[done ? len-1 : idx];
#endif

    if (top_row == 1) { // a.k.a. short polynomial
        #pragma unroll
        for (int i = 0; i < N; i++) {
            accum[i] = czero(prefetch, done);
            accum[i] *= x_pow_grid[i];
        }
    } else if (N <= 2 && sizeof(fr_t) < 8) {
        uint32_t gridsz = blockDim.x * gridDim.x;

#if 0   // due to top_row != 1
        bool done2 = idx <= gridsz;
        if (done2)
            gridsz = 0;
#else
        bool done2 = false;
#endif
        fr_t prefetch2 = coeffs[idx -= gridsz];

        #pragma unroll 1
        do {
            fr_t coeff = czero(prefetch, done);
            fr_t coeff2 = czero(prefetch2, done2);

            done = idx <= gridsz || done2;
            if (done)
                gridsz = 0;
            prefetch = coeffs[idx -= gridsz];

            bool next2 = idx <= gridsz;
            if (next2)
                gridsz = 0;
            prefetch2 = coeffs[idx -= gridsz];

            #pragma unroll
            for (int i = 0; i < N; i++) {
                accum[i] += coeff;
                accum[i] *= fr_t::csel(x_pow_grid[i], x_top_grid[i], done2);
                x_pow_grid[i] = fr_t::csel(fr_t::one(), x_pow_grid[i], done2);

                accum[i] += coeff2;
                accum[i] *= fr_t::csel(x_pow_grid[i], x_top_grid[i], done);
            }

            done2 = next2;
        } while (!done);
    } else {
        uint32_t gridsz = blockDim.x * gridDim.x;

        #pragma unroll 1
        do {
            fr_t coeff = czero(prefetch, done);

            done = idx <= gridsz;
            if (done)
                gridsz = 0;
            prefetch = coeffs[idx -= gridsz];

            #pragma unroll
            for (int i = 0; i < N; i++) {
                accum[i] += coeff;
                accum[i] *= fr_t::csel(x_pow_grid[i], x_top_grid[i], done);
            }
        } while (!done);
    }

    if (blockIdx.x + threadIdx.x == 0)
        prefetch = coeffs[0];

    /*
     * Accumulate the "row[s]."
     */
    warp::redux(accum);

    if (laneid == 0) {
        #pragma unroll
        for (int i = 0; i < N; i++)
            xchg[i][warpid] = accum[i];
    }

    __syncthreads();

    #pragma unroll
    for (int i = 0; i < N; i++)
        accum[i].zero();

    if (laneid < nwarps) {
        #pragma unroll
        for (int i = 0; i < N; i++)
            accum[i] = xchg[i][laneid];
    }

    warp::redux(accum, nwarps);

    if (gridDim.x > 1) {
        vec2d_t<fr_t> xfer{scratch, gridDim.x};

        if (threadIdx.x == 0) {
            #pragma unroll
            for (int i = 0; i < N; i++)
                xfer[i][blockIdx.x] = accum[i];
        }

        cooperative_groups::this_grid().sync();
        __syncthreads();

        if (blockIdx.x == 0) {
            #pragma unroll
            for (int i = 0; i < N; i++)
                accum[i].zero();

            if (threadIdx.x < gridDim.x) {
                #pragma unroll
                for (int i = 0; i < N; i++)
                    accum[i] = xfer[i][threadIdx.x];
            }

            unsigned ceiling = min(WARP_SZ, gridDim.x);

            warp::redux(accum, ceiling);

            if (gridDim.x > WARP_SZ) {
                if (laneid == 0) {
                    #pragma unroll
                    for (int i = 0; i < N; i++)
                        xchg[i][warpid] = accum[i];
                }

                __syncthreads();

                #pragma unroll
                for (int i = 0; i < N; i++)
                    accum[i] = xchg[i][laneid];

                ceiling = (gridDim.x + WARP_SZ - 1)/WARP_SZ;

                warp::redux(accum, ceiling);
            }
        }
    }

    /*
     * Final touch, add c0.
     */
    if (blockIdx.x + threadIdx.x == 0) {
        #pragma unroll
        for (int i = 0; i < N; i++)
            accum[i] += prefetch;

        #pragma unroll
        for (int i = 0; i < N; i++) {
            if (N == 1 || i < nx)
                ret[i] = accum[i];
        }
    }
}

/*
 * Evaluate d_coeffs[len] polynomial at x[n] points.
 */
template<class fr_t, class stream_t>
void evaluate(fr_t d_ret[/*n*/], const fr_t d_x[/*n*/], size_t n,
              const fr_t d_coeffs[/*len*/], size_t len,
              const stream_t& s, int gridDim = 0)
{
    if (gridDim <= 0)
        gridDim = s.sm_count();

    /*
     *  bits    N   M   L
     * -------+---+---+---
     *  32      6   4   2
     *  64      5   3   2(*)
     *  128     4   3   2(*)
     *  256     3   2   1
     *
     * (*) H100 and presumably other HBM GPUs are at disadvantage here,
     *     additional K=1 would give an extra kick, but we let it slide
     *     for uniformity.
     */
    const int N = sizeof(fr_t) <= 54 ? (64 - sizeof(fr_t)) / 10 : 1;
    const int M = N > 1 ? (N * 3) / 4 : 1;
    const int L = M > 1 ? (M * 2) / 3 : 1;

    /*
     * blockDim can be larger for M or L, hence the initial parameter
     * adjustment is the most "conservative."
     */
    int blockDim = d_evaluate_bsize<N, fr_t>();

    if (gridDim > blockDim) // there are no such large GPUs, not for now...
        gridDim = blockDim;

    size_t blocks = (len + blockDim - 1)/blockDim;

    if (blocks < (unsigned)gridDim)
        gridDim = (int)blocks;

    if (gridDim < 12)
        gridDim = 1;

    dev_ptr_t<fr_t> d_scratch{gridDim>1 ? (unsigned)N*gridDim : 0, s};

#if 1
    if (n > M) {
        unsigned gridSz = gridDim * blockDim;
        size_t top_row = len - (len-1) % gridSz;
        if (top_row == len)
            top_row -= gridSz;

        auto sharedSz = max(N*WARP_SZ, 2*(N-1)*blockDim);

        while (n > M) {
            auto step = min(n, (size_t)N);
            s.launch_coop(d_evaluate<N>,
                          {gridDim, blockDim, sizeof(fr_t)*sharedSz},
                          d_ret, d_x, (int)step, d_coeffs, len, top_row,
                          gridDim>1 ? &d_scratch[0] : nullptr);
            d_ret += step;
            d_x += step;
            n -= step;
        }
    }

    if (M > 1 && n != 0) {
        blockDim = n > L ? d_evaluate_bsize<M, fr_t>()
                         : d_evaluate_bsize<L, fr_t>();
        blocks = (len + blockDim - 1)/blockDim;
        if (blocks < (unsigned)gridDim)
            gridDim = (int)blocks;

        if (gridDim < 12)
            gridDim = 1;

        unsigned gridSz = gridDim * blockDim;
        size_t top_row = len - (len-1) % gridSz;
        if (top_row == len)
            top_row -= gridSz;

        if (n > L) {
            auto sharedSz = max(M*WARP_SZ, 2*(M-1)*blockDim);
            s.launch_coop(d_evaluate<M>,
                          {gridDim, blockDim, sizeof(fr_t)*sharedSz},
                          d_ret, d_x, (int)n, d_coeffs, len, top_row,
                          gridDim>1 ? &d_scratch[0] : nullptr);
        } else {
            auto sharedSz = max(L*WARP_SZ, 2*(L-1)*blockDim);
            s.launch_coop(d_evaluate<L>,
                          {gridDim, blockDim, sizeof(fr_t)*sharedSz},
                          d_ret, d_x, (int)n, d_coeffs, len, top_row,
                          gridDim>1 ? &d_scratch[0] : nullptr);
        }
    }
#else   // for troubleshooting
    auto sharedSz = max(N*WARP_SZ, 2*(N-1)*blockDim);
    unsigned gridSz = gridDim * blockDim;
    size_t top_row = len - (len-1) % gridSz;
    if (top_row == len)
        top_row -= gridSz;

    s.launch_coop(d_evaluate<N>, {gridDim, blockDim, sizeof(fr_t)*sharedSz},
                  d_ret, d_x, (int)n, d_coeffs, len, top_row,
                  gridDim>1 ? &d_scratch[0] : nullptr);
#endif
}

template<class fr_t, class stream_t>
void evaluate(fr_t* d_ret, const fr_t& x, const fr_t d_coeffs[], size_t len,
              const stream_t& s)
{   evaluate(d_ret, &x, 1, d_coeffs, len, s);   }
#endif
