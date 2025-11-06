// Copyright Supranational LLC
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#ifndef __SPPARK_MSM_BATCH_ADDITION_CUH__
#define __SPPARK_MSM_BATCH_ADDITION_CUH__

#include <cuda.h>
#include <cooperative_groups.h>
#include <vector>

#include <ff/shfl.cuh>

#ifndef WARP_SZ
# define WARP_SZ 32
#endif

#define BATCH_ADD_BLOCK_SIZE 256
#ifndef BATCH_ADD_NSTREAMS
# define BATCH_ADD_NSTREAMS 8
#elif BATCH_ADD_NSTREAMS == 0
# error "invalid BATCH_ADD_NSTREAMS"
#endif

template<class bucket_t, class affine_h,
         class bucket_h = class bucket_t::mem_t,
         class affine_t = class bucket_t::affine_t>
__device__ __forceinline__
static void add(bucket_h ret[], const affine_h points[], uint32_t npoints,
                const uint32_t bitmap[], const uint32_t refmap[],
                bool accumulate, uint32_t sid)
{
    static __device__ uint32_t streams[BATCH_ADD_NSTREAMS];
    uint32_t& current = streams[sid % BATCH_ADD_NSTREAMS];

    const uint32_t degree = bucket_t::degree;
    const uint32_t warp_sz = WARP_SZ / degree;
    const uint32_t tid = (threadIdx.x + blockDim.x*blockIdx.x) / degree;
    const uint32_t xid = tid % warp_sz;

    uint32_t laneid;
    asm("mov.u32 %0, %laneid;" : "=r"(laneid));

    bucket_t acc;
    acc.inf();

    if (accumulate && tid < gridDim.x*blockDim.x/WARP_SZ)
        acc = ret[tid];

    uint32_t base = laneid == 0 ? atomicAdd(&current, 32*WARP_SZ) : 0;
    base = __shfl_sync(0xffffffff, base, 0);

    uint32_t chunk = min(32*WARP_SZ, npoints-base);
    uint32_t bits, refs, word, sign = 0, off = 0xffffffff;

    for (uint32_t i = 0, j = 0; base < npoints;) {
        if (i == 0) {
            bits = bitmap[base/WARP_SZ + laneid];
            refs = refmap ? refmap[base/WARP_SZ + laneid] : 0;

            bits ^= refs;
            refs &= bits;
        }

        for (; i < chunk && j < warp_sz; i++) {
            if (i%32 == 0)
                word = __shfl_sync(0xffffffff, bits, i/32);
            if (refmap && (i%32 == 0))
                sign = __shfl_sync(0xffffffff, refs, i/32);

            if (word & 1) {
                if (j++ == xid)
                    off = (base + i) | (sign << 31);
            }
            word >>= 1;
            sign >>= 1;
        }

        if (i == chunk) {
            base = laneid == 0 ? atomicAdd(&current, 32*WARP_SZ) : 0;
            base = __shfl_sync(0xffffffff, base, 0);
            chunk = min(32*WARP_SZ, npoints-base);
            i = 0;
        }

        if (base >= npoints || j == warp_sz) {
            if (off != 0xffffffff) {
                affine_t p = points[off & 0x7fffffff];
                if (degree == 2)
                    acc.uadd(p, off >> 31);
                else
                    acc.add(p, off >> 31);
                off = 0xffffffff;
            }
            j = 0;
        }
    }

    for (uint32_t off = 1; off < warp_sz;) {
        auto down = shfl_down(acc, off*degree);

        off <<= 1;
        if ((xid & (off-1)) == 0)
            acc.uadd(down); // .add() triggers spills ... in .shfl_down()
    }

    cooperative_groups::this_grid().sync();

    if (xid == 0)
        ret[tid/warp_sz] = acc;

    if (threadIdx.x + blockIdx.x == 0)
        current = 0;
}

template<class bucket_t, class affine_h,
         class bucket_h = class bucket_t::mem_t,
         class affine_t = class bucket_t::affine_t>
__launch_bounds__(BATCH_ADD_BLOCK_SIZE) __global__
void batch_addition(bucket_h ret[], const affine_h points[], uint32_t npoints,
                    const uint32_t bitmap[], bool accumulate = false,
                    uint32_t sid = 0)
{   add<bucket_t>(ret, points, npoints, bitmap, nullptr, accumulate, sid);   }

template<class bucket_t, class affine_h,
         class bucket_h = class bucket_t::mem_t,
         class affine_t = class bucket_t::affine_t>
__launch_bounds__(BATCH_ADD_BLOCK_SIZE) __global__
void batch_diff(bucket_h ret[], const affine_h points[], uint32_t npoints,
                const uint32_t bitmap[], const uint32_t refmap[],
                bool accumulate = false, uint32_t sid = 0)
{   add<bucket_t>(ret, points, npoints, bitmap, refmap, accumulate, sid);   }

template<class bucket_t, class affine_h,
         class bucket_h = class bucket_t::mem_t,
         class affine_t = class bucket_t::affine_t>
__launch_bounds__(BATCH_ADD_BLOCK_SIZE) __global__
void batch_addition(bucket_h ret[], const affine_h points[], size_t npoints,
                    const uint32_t digits[], const uint32_t& ndigits)
{
    const uint32_t degree = bucket_t::degree;
    const uint32_t warp_sz = WARP_SZ / degree;
    const uint32_t tid = (threadIdx.x + blockDim.x*blockIdx.x) / degree;
    const uint32_t xid = tid % warp_sz;

    bucket_t acc;
    acc.inf();

    for (size_t i = tid; i < ndigits; i += gridDim.x*blockDim.x/degree) {
        uint32_t digit = digits[i];
        affine_t p = points[digit & 0x7fffffff];
        if (degree == 2)
            acc.uadd(p, digit >> 31);
        else
            acc.add(p, digit >> 31);
    }

    for (uint32_t off = 1; off < warp_sz;) {
        auto down = shfl_down(acc, off*degree);

        off <<= 1;
        if ((xid & (off-1)) == 0)
            acc.uadd(down); // .add() triggers spills ... in .shfl_down()
    }

    if (xid == 0)
        ret[tid/warp_sz] = acc;
}

template<class bucket_t>
bucket_t sum_up(const bucket_t inp[], size_t n)
{
    bucket_t sum = inp[0];
    for (size_t i = 1; i < n; i++)
        sum.add(inp[i]);
    return sum;
}

template<class bucket_t>
bucket_t sum_up(const std::vector<bucket_t>& inp)
{   return sum_up(&inp[0], inp.size());   }
#endif
