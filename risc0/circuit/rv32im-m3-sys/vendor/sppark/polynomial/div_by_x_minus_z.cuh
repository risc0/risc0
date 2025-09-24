// Copyright Supranational LLC
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#if !defined(__SPPARK_POLYNOMIAL_DIVISION_CUH__) && \
    (defined(__CUDACC__) || defined(__HIPCC__))
#define __SPPARK_POLYNOMIAL_DIVISION_CUH__

#include <cassert>
#ifdef __HIPCC__
# include <hip/hip_cooperative_groups.h>
#else
# include <cooperative_groups.h>
#endif
#include <ff/shfl.cuh>

template<class fr_t, int N, bool rotate, int BSZ>
__global__ __launch_bounds__(BSZ)
void d_div_by_x_minus_z(fr_t d_inout[], size_t len, fr_t z)
{
    struct my {
        __device__ __forceinline__
        static void madd_up(fr_t& coeff, fr_t& z_pow, uint32_t limit = WARP_SZ)
        {
            const uint32_t laneid = threadIdx.x % WARP_SZ;

            __builtin_assume(limit > 1);

            #pragma unroll 1
            for (uint32_t off = 1; off < limit; off <<= 1) {
                auto temp = shfl_up(coeff, off);
                temp = fr_t::csel(temp, z_pow, laneid != 0);
                z_pow *= temp;          // 0th lane squares z_pow
                temp = coeff + z_pow;
                coeff = fr_t::csel(coeff, temp, laneid < off);
                z_pow = shfl_idx(z_pow, 0);
            }
            /* beware that resulting |z_pow| can be fed to the next madd_up() */
        }

        __device__ __noinline__
        static fr_t mult_up(fr_t z_lane, uint32_t limit = WARP_SZ)
        {
            const uint32_t laneid = threadIdx.x % WARP_SZ;

            __builtin_assume(limit > 1);

            #pragma unroll 1
            for (uint32_t off = 1; off < limit; off <<= 1) {
                auto temp = shfl_up(z_lane, off);
                temp *= z_lane;
                z_lane = fr_t::csel(z_lane, temp, laneid < off);
            }

            return z_lane;
        }
    };

#if 0
    assert(blockDim.x%WARP_SZ == 0 && gridDim.x <= blockDim.x);
#endif

    const uint32_t tidx   = N * (threadIdx.x + blockDim.x*blockIdx.x);
    const uint32_t laneid = threadIdx.x % WARP_SZ;
    const uint32_t warpid = threadIdx.x / WARP_SZ;
    const uint32_t nwarps = blockDim.x  / WARP_SZ;

    extern __shared__ int xchg_div_by_x_minus_z[];
    fr_t* xchg = reinterpret_cast<decltype(xchg)>(xchg_div_by_x_minus_z);
    static __shared__ fr_t z_pow_carry[WARP_SZ], z_top_block, z_top_carry, z_n;

    /*
     * Calculate ascending powers of |z| in ascending threads across
     * the grid. Since the kernel is invoked cooperatively, gridDim.x
     * would be not larger than the amount of SMs, which would be far
     * from the limit for this part of the implementation, 33*32+1.
     * ["This part" refers to the fact that a stricter limitation is
     * implied elsewhere, gridDim.x <= blockDim.x.]
     */
    fr_t z_pow = z;
    if (N > 1)
        z_pow ^= N;
    z_pow = my::mult_up(z_pow);
    fr_t z_pow_warp = z_pow;        // z^(laneid+1)

    fr_t z_pow_block = z_pow_warp;  // z^(threadIdx.x+1)
    z_pow = shfl_idx(z_pow, WARP_SZ-1);
    z_pow = my::mult_up(z_pow, nwarps);
    if (warpid != 0) {
        z_pow_block = shfl_idx(z_pow, warpid - 1);
        z_pow_block *= z_pow_warp;
    }
    z_pow = shfl_idx(z_pow, nwarps - 1);

    if (threadIdx.x == 0) {
        z_n = z_pow_warp;
        z_top_block = z_pow;
    }

    fr_t z_pow_grid = z_pow_block;  // z^(blockDim.x*blockIdx.x+threadIdx.x+1)
    if (blockIdx.x != 0) {
        z_pow = my::mult_up(z_pow, min(WARP_SZ, gridDim.x));
        z_pow_grid = shfl_idx(z_pow, (blockIdx.x - 1)%WARP_SZ);

        // Offload z^(z_top_block*(laneid+1)) to the shared memory to
        // alleviate register pressure.
        if (warpid == 0)
            z_pow_carry[laneid] = z_pow;

        if (blockIdx.x > WARP_SZ) {
            z_pow = shfl_idx(z_pow, WARP_SZ - 1);
            z_pow = my::mult_up(z_pow, (gridDim.x + WARP_SZ - 1)/WARP_SZ);
            z_pow = shfl_idx(z_pow, (blockIdx.x - 1)/WARP_SZ - 1);
            z_pow_grid *= z_pow;
        }

        if (threadIdx.x == 0)
            z_top_carry = z_pow_grid;

        z_pow_grid *= z_pow_block;
    }

    __syncthreads();

#if 0
    auto check = z^(tidx+N);
    check -= z_pow_grid;
    assert(check.is_zero());
#endif

    /*
     * Given ∑cᵢ⋅xⁱ the goal is to sum up columns as following
     *
     * cf ce cd cc cb ca a9 c8 c7 c6 c5 c4 c3 c2 c1 c0
     *    cf ce cd cc cb ca a9 c8 c7 c6 c5 c4 c3 c2 c1 * z
     *       cf ce cd cc cb ca a9 c8 c7 c6 c5 c4 c3 c2 * z^2
     *          cf ce cd cc cb ca a9 c8 c7 c6 c5 c4 c3 * z^3
     *             cf ce cd cc cb ca a9 c8 c7 c6 c5 c4 * z^4
     *                cf ce cd cc cb ca a9 c8 c7 c6 c5 * z^5
     *                   cf ce cd cc cb ca a9 c8 c7 c6 * z^6
     *                      cf ce cd cc cb ca a9 c8 c7 * z^7
     *                         cf ce cd cc cb ca a9 c8 * z^8
     *                            cf ce cd cc cb ca a9 * z^9
     *                               cf ce cd cc cb ca * z^10
     *                                  cf ce cd cc cb * z^11
     *                                     cf ce cd cc * z^12
     *                                        cf ce cd * z^13
     *                                           cf ce * z^14
     *                                              cf * z^15
     *
     * If |rotate| is false, the first element of the output is
     * the remainder and the rest is the quotient. Otherwise
     * the remainder is stored at the end and the quotient is
     * "shifted" toward the beginning of the |d_inout| vector.
     */
    class rev_ptr_t {
        fr_t* p;
    public:
        __device__ rev_ptr_t(fr_t* ptr, size_t len) : p(ptr + len - 1) {}
        __device__ fr_t& operator[](size_t i)             { return *(p - i); }
        __device__ const fr_t& operator[](size_t i) const { return *(p - i); }
    };
    rev_ptr_t inout{d_inout, len};
    fr_t coeff[N], prefetch;
    uint32_t stride = N*blockDim.x*gridDim.x;
    size_t idx;
    auto __grid = cooperative_groups::this_grid();

    if (tidx < len)
        prefetch = inout[tidx];

    for (size_t chunk = 0; chunk < len; chunk += stride) {
        idx = chunk + tidx;

        #pragma unroll
        for (int i = 1; i < N; i++) {
            if (idx + i < len)
                coeff[i] = inout[idx + i];
        }
        coeff[0] = prefetch;

        if (idx + stride < len)
            prefetch = inout[idx + stride];

        z_pow = z;
        #pragma unroll
        for (int i = 1; i < N; i++)
            coeff[i] += coeff[i-1] * z_pow;

        fr_t carry_over;
        bool tail_sync = false;

        if (sizeof(fr_t) <= 32) {
            my::madd_up(coeff[N-1], z_pow = z_n);

            if (laneid == WARP_SZ-1)
                xchg[warpid] = coeff[N-1];

            __syncthreads();

            carry_over = xchg[laneid];

            my::madd_up(carry_over, z_pow, nwarps);

            if (warpid != 0) {
                carry_over = shfl_idx(carry_over, warpid - 1);
                carry_over *= z_pow_warp;
                coeff[N-1] += carry_over;
            }

            carry_over.zero();

            size_t remaining = len - chunk;

            if (gridDim.x > 1 && remaining > N*blockDim.x) {
                tail_sync = remaining <= 2*stride - N*blockDim.x;
                uint32_t bias = tail_sync ? 0 : stride;
                size_t grid_idx = chunk + (blockIdx.x*N*blockDim.x + bias
                                        + N*(rotate && blockIdx.x == 0));
                if (threadIdx.x == blockDim.x-1 && grid_idx < len)
                    inout[grid_idx] = coeff[N-1];

                __grid.sync();
                __syncthreads();

                if (blockIdx.x != 0) {
                    grid_idx = chunk + (threadIdx.x*N*blockDim.x + bias
                                     + N*(rotate && threadIdx.x == 0));
                    if (threadIdx.x < gridDim.x && grid_idx < len)
                        carry_over = inout[grid_idx];

                    my::madd_up(carry_over, z_pow = z_top_block,
                                min(WARP_SZ, gridDim.x));

                    if (gridDim.x > WARP_SZ) {
                        if (laneid == WARP_SZ-1)
                            xchg[warpid] = carry_over;

                        __syncthreads();

                        fr_t temp = xchg[laneid];

                        my::madd_up(temp, z_pow,
                                    (gridDim.x + WARP_SZ - 1)/WARP_SZ);

                        if (warpid != 0) {
                            temp = shfl_idx(temp, warpid - 1);
                            temp *= (z_pow = z_pow_carry[laneid]);
                            carry_over += temp;
                        }
                    }

                    if (threadIdx.x < gridDim.x)
                        xchg[threadIdx.x] = carry_over;

                    __syncthreads();

                    carry_over = xchg[blockIdx.x-1];
                    coeff[N-1] += carry_over * z_pow_block;
                }
            }

            if (chunk != 0) {
                fr_t carry = inout[chunk - !rotate];
                coeff[N-1] += carry * z_pow_grid;

                if (N > 1) {
                    if (blockIdx.x == 0)
                        carry_over = carry;
                    else
                        carry_over += carry * (z_pow = z_top_carry);
                }
            }
        } else {    // ~14KB loop size with 256-bit field, yet unused...
            fr_t z_pow_adjust, offload, acc = coeff[N-1];

            z_pow = z_n;
            uint32_t limit = WARP_SZ;
            uint32_t adjust = 0;
            int pc = -1;

            do {
                my::madd_up(acc, z_pow, limit);

                if (adjust != 0) {
                    acc = shfl_idx(acc, adjust - 1);
                tail_mul:
                    coeff[N-1] += acc * z_pow_adjust;
                }

                switch (++pc) {
                case 0:
                    coeff[N-1] = acc;

                    if (laneid == WARP_SZ-1)
                        xchg[warpid] = acc;

                    __syncthreads();

                    acc = xchg[laneid];

                    limit = nwarps;
                    adjust = warpid;
                    z_pow_adjust = z_pow_warp;
                    if (N > 1)
                        carry_over.zero();
                    break;
                case 1:
                    if (gridDim.x > 1 && len - chunk > N*blockDim.x) {
                        tail_sync = len - chunk <= 2*stride - N*blockDim.x;
                        uint32_t bias = tail_sync ? 0 : stride;
                        size_t xchg_idx = chunk + (blockIdx.x*N*blockDim.x + bias
                                                + N*(rotate && blockIdx.x == 0));
                        if (threadIdx.x == blockDim.x-1 && xchg_idx < len)
                            inout[xchg_idx] = coeff[N-1];

                        __grid.sync();
                        __syncthreads();

                        if (blockIdx.x != 0) {
                            xchg_idx = chunk + (threadIdx.x*N*blockDim.x + bias
                                             + N*(rotate && threadIdx.x == 0));
                            if (threadIdx.x < gridDim.x && xchg_idx < len)
                                acc = inout[xchg_idx];

                            z_pow = z_top_block;
                            limit = min(WARP_SZ, gridDim.x);
                            adjust = 0;
                        } else {
                            goto final;
                        }
                    } else {
                        goto final;
                    }
                    break;
                case 2: // blockIdx.x != 0
                    carry_over = coeff[N-1];
                    coeff[N-1] = acc;

                    if (gridDim.x > WARP_SZ) {
                        if (laneid == WARP_SZ-1)
                            xchg[warpid] = acc;

                        __syncthreads();

                        acc = xchg[laneid];

                        limit = (gridDim.x + WARP_SZ - 1)/WARP_SZ;
                        adjust = warpid;
                        z_pow_adjust = z_pow_carry[laneid];
                        break;
                    }   // else fall through
                case 3: // blockIdx.x != 0
                    if (threadIdx.x < gridDim.x)
                        xchg[threadIdx.x] = coeff[N-1];

                    __syncthreads();

                    coeff[N-1] = carry_over;
                    acc = xchg[blockIdx.x-1];
                    z_pow_adjust = z_pow_block;
                    if (N > 1)
                        carry_over = acc;
                    pc = 3;
                    goto tail_mul;
                case 4:
                final:
                    if (chunk == 0) {
                        pc = -1;
                        break;
                    }

                    acc = inout[chunk - !rotate];
                    z_pow_adjust = z_pow_grid;
                    pc = 4;
                    goto tail_mul;
                case 5:
                    if (N > 1) {
                        if (blockIdx.x == 0) {
                            carry_over = acc;
                        } else {
                            offload = coeff[N-1];
                            coeff[N-1] = carry_over;
                            z_pow_adjust = z_top_carry;
                            goto tail_mul;
                        }
                    }
                    pc = -1;
                    break;
                case 6:
                    if (N > 1) {
                        carry_over = coeff[N-1];
                        coeff[N-1] = offload;
                    }
                    // fall through
                default:
                    pc = -1;
                    break;
                }
            } while (pc >= 0);
        }

        if (N > 1) {
            if (laneid == WARP_SZ-1)
                xchg[warpid] = coeff[N-1];

            __syncthreads();

            fr_t carry = shfl_up(coeff[N-1], 1);

            if (laneid == 0 && warpid != 0)
                carry_over = xchg[warpid-1];

            carry = fr_t::csel(carry_over, carry, laneid == 0);

            z_pow = z;
            #pragma unroll
            for (int i = 0; i < N-1; i++)
                coeff[i] += (carry *= z_pow);
        }

        if (tail_sync) {
            __grid.sync();
            __syncthreads();
        }

        #pragma unroll
        for (int i = 0; i < N; i++) {
            if (idx + i < len - rotate)
                inout[idx + i + rotate] = coeff[i];
        }
    }

    if (rotate) {
        int rem = static_cast<int>(--len % N);
        if (idx == len - rem) {
            #pragma unroll
            for (int i = 1; i < N; i++)
                coeff[0] = fr_t::csel(coeff[i], coeff[0], i == rem);

            inout[0] = coeff[0];
        }
    }
}

template<bool rotate = false, class fr_t, class stream_t>
void div_by_x_minus_z(fr_t d_inout[], size_t len, const fr_t& z,
                      const stream_t& s, int gridDim = 0)
{
    if (gridDim <= 0)
        gridDim = s.sm_count();

    constexpr int N = 2;
    constexpr int BSZ = sizeof(fr_t) <= 16 ? 1024 : 0;
    int blockDim = BSZ;

    if (BSZ == 0) {
        static int saved_blockDim = 0;

        if (saved_blockDim == 0) {
            cudaFuncAttributes attr;
            CUDA_OK(cudaFuncGetAttributes(&attr, d_div_by_x_minus_z<fr_t, N, rotate, BSZ>));
            saved_blockDim = attr.maxThreadsPerBlock;
            assert(saved_blockDim%WARP_SZ == 0);
        }

        blockDim = saved_blockDim;
    }

    if (gridDim > blockDim) // there are no such large GPUs, not for now...
        gridDim = blockDim;

    size_t blocks = (len + blockDim - 1)/blockDim;

    if ((unsigned)gridDim > blocks)
        gridDim = (int)blocks;

    if (gridDim < 3)
        gridDim = 1;

    size_t sharedSz = sizeof(fr_t) * max(blockDim/WARP_SZ, gridDim);

    s.launch_coop(d_div_by_x_minus_z<fr_t, N, rotate, BSZ>,
                  {gridDim, blockDim, sharedSz},
                  d_inout, len, z);
}
#endif
