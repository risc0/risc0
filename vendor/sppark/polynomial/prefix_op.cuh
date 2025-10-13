// Copyright Supranational LLC
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#if !defined(__SPPARK_POLYNOMIAL_PREFIX_OP_CUH__) && \
    (defined(__CUDACC__) || defined(__HIPCC__))
#define __SPPARK_POLYNOMIAL_PREFIX_OP_CUH__

#include <cassert>
#ifdef __HIPCC__
# include <hip/hip_cooperative_groups.h>
#else
# include <cooperative_groups.h>
#endif
#include <ff/shfl.cuh>

template <typename fr_t>
class Add {
public:
    using T = fr_t;
    static const int CHUNK = 192 / sizeof(fr_t);
    static_assert(CHUNK != 0, "field size is too large");

    __device__ __host__ __forceinline__
    fr_t operator()(const fr_t& a, const fr_t& b) const
    {   return a + b;   }

    __device__ __host__ __forceinline__
    fr_t identity() const
    {   fr_t ret; ret.zero(); return ret;   }
};

template <typename fr_t>
class Multiply {
public:
    using T = fr_t;
    static const int CHUNK = 128 / sizeof(fr_t);
    static_assert(CHUNK != 0, "field size is too large");

    __device__ __host__ __forceinline__
    fr_t operator()(const fr_t& a, const fr_t& b) const
    {   return a * b;   }

    __device__ __host__ __forceinline__
    fr_t identity() const
    {   return fr_t::one();   }
};

template <typename Operation, int CHUNK, typename fr_t = typename Operation::T,
          class OutPtr = fr_t*, class InPtr = const fr_t*>
__global__ __launch_bounds__(sizeof(fr_t)<=16 ? 1024 : 512)
void d_prefix_op(OutPtr out, InPtr inp, size_t len)
{
    struct warp {
        __device__ __forceinline__
        static fr_t& prefix_op(fr_t& x_lane, uint32_t limit = WARP_SZ)
        {
            const uint32_t laneid = threadIdx.x % WARP_SZ;
            const Operation op;

            __builtin_assume(limit > 1);

            #pragma unroll 1
            for (uint32_t offset = 1; offset < limit; offset <<= 1) {
                fr_t temp = shfl_up(x_lane, offset);
                temp = op(temp, x_lane);
                x_lane = fr_t::csel(x_lane, temp, laneid < offset);
            }

            return x_lane;
        }

        /*
         * Compiler apparently doesn't fuse loops, at least not these ones,
         * it has to be done "manually."
         */
        __device__ __forceinline__
        static void prefix_op(fr_t chunk[CHUNK])
        {
            const uint32_t laneid = threadIdx.x % WARP_SZ;
            const Operation op;

            #pragma unroll 1
            for (uint32_t offset = 1; offset < WARP_SZ; offset <<= 1) {
                #pragma unroll
                for (int i = 0; i < CHUNK; i++) {
                    fr_t temp = shfl_up(chunk[i], offset);
                    temp = op(temp, chunk[i]);
                    chunk[i] = fr_t::csel(chunk[i], temp, laneid < offset);
                }
            }
        }
#ifdef __HIPCC__
        static __device__ __noinline__ void noop() { asm(""); }
#else
        static __device__ __forceinline__ void noop() {}
#endif
    };

#if 0
    assert(blockDim.x%WARP_SZ == 0 && gridDim.x <= blockDim.x);
#endif

    const uint32_t tid    = threadIdx.x + blockDim.x * blockIdx.x;
    const uint32_t warpid = threadIdx.x / WARP_SZ;
    const uint32_t laneid = threadIdx.x % WARP_SZ;
    const uint32_t nwarps = blockDim.x  / WARP_SZ;

    static __shared__ fr_t xchg[1024/WARP_SZ]; // 1024 is maximum for blockDim

    const uint32_t chunk_size = blockDim.x * CHUNK;
    const uint32_t blob_size = gridDim.x * chunk_size;

    constexpr bool coalesce = CHUNK/sizeof(fr_t) > 1;
    const uint32_t lane_off = (tid / WARP_SZ) * WARP_SZ * CHUNK +
                              (coalesce ? laneid : laneid*CHUNK);

    const Operation op;
    const fr_t identity = op.identity();

    fr_t grid_carry = identity;
    fr_t chunk[CHUNK];

    const bool do_prefetch = true;
    fr_t prefetch;

    if (do_prefetch) {
#ifdef __CUDA_ARCH__
        prefetch = identity;
        if (lane_off < len)
            prefetch = inp[lane_off];
#else
        prefetch = inp[lane_off<len ? lane_off : len-1];
#endif
    }

    __builtin_assume(len > 0);

    #pragma unroll 1
    for (size_t blob = 0; blob < len; blob += blob_size) {
        size_t lane_idx = blob + lane_off;
        int top = CHUNK;

        if (do_prefetch) {
            if (lane_idx >= len)
                top = 0;

            chunk[0] = prefetch;
        }

        #pragma unroll
        for (int i = do_prefetch; i < CHUNK; i++) {
            size_t idx = lane_idx + (coalesce ? WARP_SZ*i : i);

            if (top == CHUNK && idx >= len)
                top = i;

#ifdef __CUDA_ARCH__
            chunk[i] = identity;
            if (i < top)
                chunk[i] = inp[idx];
#else
            chunk[i] = inp[i<top ? idx : len-1];
#endif
        }

        if (do_prefetch) {
            size_t idx = lane_idx + blob_size;

#ifdef __CUDA_ARCH__
            prefetch = identity;
            if (idx < len)
                prefetch = inp[idx];
#else
            prefetch = inp[idx<len ? idx : len-1];
#endif
        }

#ifndef __CUDA_ARCH__
        #pragma unroll
        for (int i = 0; i < CHUNK; i++)
            chunk[i] = fr_t::csel(chunk[i], identity, i < top);
#endif

        if (coalesce) {
            warp::prefix_op(chunk);

            #pragma unroll
            for (int i = 1; i < CHUNK; i++)
                chunk[i] = op(chunk[i], shfl_idx(chunk[i-1], WARP_SZ-1));
        } else {
            #pragma unroll
            for (int i = 1; i < CHUNK; i++)
                chunk[i] = op(chunk[i], chunk[i-1]);

            chunk[CHUNK-1] = warp::prefix_op(chunk[CHUNK-1]);
        }

        if (laneid == WARP_SZ-1 && warpid < 1024/WARP_SZ-1)
            xchg[warpid] = chunk[CHUNK - 1];

        __syncthreads();

        fr_t warp_carry = identity;

        if (laneid < nwarps && laneid > 0)
            warp_carry = xchg[laneid - 1];

        warp_carry = warp::prefix_op(warp_carry, nwarps);
        warp_carry = shfl_idx(warp_carry, warpid);

        if (coalesce) {
            chunk[CHUNK - 1] = op(chunk[CHUNK - 1], warp_carry);
        } else {
            fr_t lane_carry = shfl_up(chunk[CHUNK-1], 1);
            lane_carry = fr_t::csel(identity, lane_carry, laneid == 0);

            chunk[CHUNK - 1] = op(chunk[CHUNK - 1], warp_carry);

            warp_carry = op(warp_carry, lane_carry);
        }

        fr_t grid_carry_in = grid_carry;

        if (gridDim.x == 1) {
            if (threadIdx.x == blockDim.x-1)
                xchg[1024/WARP_SZ - 1] = chunk[CHUNK - 1];

            __syncthreads();

            grid_carry = xchg[1024/WARP_SZ - 1];
            grid_carry = op(grid_carry, grid_carry_in);
        } else {
            bool tail_sync = !do_prefetch ||
                             (len - blob) <= (2*blob_size - chunk_size);
            uint32_t bias = tail_sync ? 0 : blob_size;

            size_t grid_xchg = blob + (blockIdx.x*chunk_size + bias);
            if (threadIdx.x == blockDim.x-1 && grid_xchg < len)
                out[grid_xchg] = chunk[CHUNK - 1];

            cooperative_groups::this_grid().sync();
            __syncthreads();

            uint32_t rank = gridDim.x <= WARP_SZ ? laneid : threadIdx.x;

            fr_t block_carry = identity;

            grid_xchg = blob + (rank*chunk_size + bias);
            if (rank < gridDim.x && grid_xchg < len)
                block_carry = out[grid_xchg];

            block_carry = warp::prefix_op(block_carry, min(WARP_SZ, gridDim.x));

            if (gridDim.x <= WARP_SZ) {
                grid_carry = op(grid_carry, shfl_idx(block_carry, gridDim.x-1));

                if (blockIdx.x > 0)
                    block_carry = shfl_idx(block_carry, blockIdx.x - 1);
                else
                    block_carry = identity;
            } else {
                const uint32_t nwarps = (gridDim.x + WARP_SZ - 1) / WARP_SZ;

                // The last warp saves a value only when gridDim.x is
                // divisible by WARP_SZ. However, note that this value is
                // later disregarded, hence there is no need to handle all
                // divisibility cases, comparison to gridDim.x suffices.
                if (laneid == WARP_SZ - 1 && threadIdx.x < gridDim.x)
                    xchg[warpid] = block_carry;

                __syncthreads();

                fr_t inner_carry = identity;

                if (laneid < nwarps && laneid > 0)
                    inner_carry = xchg[laneid - 1];

                inner_carry = warp::prefix_op(inner_carry, nwarps);
                inner_carry = shfl_idx(inner_carry, warpid);

                __syncthreads();

                if (threadIdx.x == blockIdx.x-1 || threadIdx.x == gridDim.x-1) {
                    block_carry = op(block_carry, inner_carry);
                    xchg[threadIdx.x == gridDim.x-1] = block_carry;
                }

                __syncthreads();

                if (blockIdx.x > 0)
                    block_carry = xchg[0];
                else
                    block_carry = identity;

                grid_carry = xchg[1];
                grid_carry = op(grid_carry, grid_carry_in);
            }

            if (tail_sync) {
                cooperative_groups::this_grid().sync();
                __syncthreads();
            }

            grid_carry_in = op(grid_carry_in, block_carry);
        }

        warp_carry = op(warp_carry, grid_carry_in);

        #pragma unroll
        for (int i = 0; i < CHUNK-1; i++)
            chunk[i] = op(chunk[i], warp_carry);

        chunk[CHUNK - 1] = op(chunk[CHUNK - 1], grid_carry_in);

        #pragma unroll
        for(int i = 0; i < CHUNK; i++) {
            if (i < top)
                out[lane_idx + (coalesce ? WARP_SZ*i : i)] = chunk[i];
        }
    }
}

template <typename Operation, typename fr_t = typename Operation::T,
          class OutPtr = fr_t*, class InPtr = const fr_t*,
          class stream_t>
void prefix_op(OutPtr d_out, InPtr d_inp, size_t len, const stream_t& s,
               int gridDim = 0)
{
    if (gridDim <= 0)
        gridDim = s.sm_count();

    int blockDim = sizeof(fr_t)<=16 ? 1024 : 512;
    int chunkSize = blockDim * Operation::CHUNK;

    size_t blocks = (len + chunkSize - 1)/chunkSize;

# define __PREFIX_OP__(N) d_prefix_op<Operation, N, fr_t, OutPtr, InPtr>

    if (blocks <= (unsigned)gridDim) {
        if ((Operation::CHUNK/4)*4 == Operation::CHUNK &&
            blocks*4 <= (unsigned)gridDim) {
            // +70-90% improvement depending on field and GPU
            chunkSize = blockDim * Operation::CHUNK/4;
            gridDim = (int)((len + chunkSize - 1)/chunkSize);
            s.launch_coop(__PREFIX_OP__(Operation::CHUNK/4),
                          {gridDim, blockDim},
                          d_out, d_inp, len);
            return;
        } else if ((Operation::CHUNK/2)*2 == Operation::CHUNK &&
                   blocks*2 <= (unsigned)gridDim) {
            // +20-40% improvement depending on field and GPU
            chunkSize = blockDim * Operation::CHUNK/2;
            gridDim = (int)((len + chunkSize - 1)/chunkSize);
            s.launch_coop(__PREFIX_OP__(Operation::CHUNK/2),
                          {gridDim, blockDim},
                          d_out, d_inp, len);
            return;
        } else if ((Operation::CHUNK*3/4)*4 == Operation::CHUNK*3 &&
                   blocks*4 <= (unsigned)gridDim*3) {
            // +10-20% improvement depending on field and GPU
            chunkSize = blockDim * Operation::CHUNK*3/4;
            gridDim = (int)((len + chunkSize - 1)/chunkSize);
            s.launch_coop(__PREFIX_OP__(Operation::CHUNK*3/4),
                          {gridDim, blockDim},
                          d_out, d_inp, len);
            return;
        }

        gridDim = (int)blocks;
    } else if ((Operation::CHUNK*3/4)*4 == Operation::CHUNK*3) {
        chunkSize = blockDim * (Operation::CHUNK*3/4);
        blocks = (len + chunkSize - 1)/chunkSize;

        if (blocks <= (unsigned)gridDim*2) {
            // +10-20% improvement depending on field and GPU
            s.launch_coop(__PREFIX_OP__(Operation::CHUNK*3/4),
                          {gridDim, blockDim},
                          d_out, d_inp, len);
            return;
        }
    }

    s.launch_coop(__PREFIX_OP__(Operation::CHUNK),
                  {gridDim, blockDim},
                  d_out, d_inp, len);

# undef __PREFIX_OP__
}

template <typename Operation, typename fr_t = typename Operation::T, class stream_t>
void prefix_op(fr_t* d_inout, size_t len, const stream_t& s, int gridDim = 0)
{
    prefix_op<Operation>(d_inout, reinterpret_cast<const fr_t*>(d_inout), len,
                         s, gridDim);
}
#endif
