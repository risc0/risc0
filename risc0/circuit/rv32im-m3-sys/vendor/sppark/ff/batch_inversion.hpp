// Copyright Supranational LLC
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#ifndef __SPPARK_FF_BATCH_INVERSION_HPP__
#define __SPPARK_FF_BATCH_INVERSION_HPP__

/*
 * Since the batch inversion requires twice the storage, on GPU there
 * is incentive to use the shared memory. If deemed beneficial, the
 * suggestion is to have the caller wrap T[] in S with custom operator[]
 * that would address the shared memory and offload the input.
 */
template<class T, size_t N, typename S = T[N]>
#if defined(__CUDACC__) || defined(__HIPCC__)
__device__ __host__ __forceinline__
#endif
static void batch_inversion(T out[N], const S inp, bool preloaded = false)
{
    if (!preloaded)
        out[0] = inp[0];

    bool zero = out[0].is_zero();
    out[0] = T::csel(T::one(), out[0], zero);
    unsigned int map = zero;

    for (size_t i = 1; i < N; i++) {
        if (!preloaded)
            out[i] = inp[i];
        zero = out[i].is_zero();
        out[i] *= out[i-1];
        out[i] = T::csel(out[i-1], out[i], zero);
        if (N <= 32)
            map = (map << 1) + zero;
    }

    T tmp, inv = 1/out[N-1];

    for (size_t i = N; --i; map >>= (N<=32)) {
        out[i] = inv*out[i-1];
        tmp = inp[i];
        tmp *= inv;
        if (N <= 32)
            zero = map&1;
        else
            zero = tmp.is_zero();
        inv = T::csel(inv, tmp, zero);
        out[i] = czero(out[i], zero);
    }

    out[0] = czero(inv, map);
}
#endif
