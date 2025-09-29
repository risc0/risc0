// Copyright Supranational LLC
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#if !defined(__SPPARK_FF_SHFL_CUH__) && \
    (defined(__CUDACC__) || defined(__HIPCC__))
#define __SPPARK_FF_SHFL_CUH__

#ifndef WARP_SZ
# define WARP_SZ 32
#endif

template<class T> __device__ __forceinline__
static T shfl_idx(const T& src, unsigned int idx)
{
    const size_t len = sizeof(T)/sizeof(int);
    union { T val; int vec[len]; } ret{src};

    for (size_t i = 0; i < len; i++)
        ret.vec[i] = __shfl_sync(0xffffffff, ret.vec[i], idx);

    return ret.val;
}

template<class T> __device__ __forceinline__
static T shfl_xor(const T& src, unsigned int mask)
{
    const size_t len = sizeof(T)/sizeof(int);
    union { T val; int vec[len]; } ret{src};

    for (size_t i = 0; i < len; i++)
        ret.vec[i] = __shfl_xor_sync(0xffffffff, ret.vec[i], mask);

    return ret.val;
}

template<class T> __device__ __forceinline__
static T shfl_down(const T& src, unsigned int off)
{
    const size_t len = sizeof(T)/sizeof(int);
    union { T val; int vec[len]; } ret{src};

    for (size_t i = 0; i < len; i++)
        ret.vec[i] = __shfl_down_sync(0xffffffff, ret.vec[i], off);

    return ret.val;
}

template<class T> __device__ __forceinline__
static T shfl_up(const T& src, unsigned int off)
{
    const size_t len = sizeof(T)/sizeof(int);
    union { T val; int vec[len]; } ret{src};

    for (size_t i = 0; i < len; i++)
        ret.vec[i] = __shfl_up_sync(0xffffffff, ret.vec[i], off);

    return ret.val;
}

template<class T> __device__ __forceinline__
static T& add_up(T& x_lane, unsigned limit)
{
    const unsigned laneid = threadIdx.x % WARP_SZ;

    __builtin_assume(limit > 1);

    #pragma unroll 1
    for (unsigned off = 1; off < limit; off <<= 1) {
        auto temp = shfl_up(x_lane, off);
        temp += x_lane;
        x_lane = T::csel(x_lane, temp, laneid < off);
    }

    return x_lane;
}

template<class T> __device__ __forceinline__
static T& add_up(T& x_lane)
{
    if (sizeof(T) > 16)
        return add_up(x_lane, WARP_SZ);

    const unsigned laneid = threadIdx.x % WARP_SZ;

    #pragma unroll
    for (unsigned off = 1; off < WARP_SZ; off <<= 1) {
        auto temp = shfl_up(x_lane, off);
        temp += x_lane;
        x_lane = T::csel(x_lane, temp, laneid < off);
    }

    return x_lane;
}

template<class T> __device__ __forceinline__
static T& mul_up(T& x_lane, unsigned limit)
{
    const unsigned laneid = threadIdx.x % WARP_SZ;

    __builtin_assume(limit > 1);

    #pragma unroll 1
    for (unsigned off = 1; off < limit; off <<= 1) {
        auto temp = shfl_up(x_lane, off);
        temp *= x_lane;
        x_lane = T::csel(x_lane, temp, laneid < off);
    }

    return x_lane;
}

template<class T> __device__ __forceinline__
static T& mul_up(T& x_lane)
{
    if (sizeof(T) > 4)
        return mul_up(x_lane, WARP_SZ);

    const unsigned laneid = threadIdx.x % WARP_SZ;

    #pragma unroll
    for (unsigned off = 1; off < WARP_SZ; off <<= 1) {
        auto temp = shfl_up(x_lane, off);
        temp *= x_lane;
        x_lane = T::csel(x_lane, temp, laneid < off);
    }

    return x_lane;
}
#endif
