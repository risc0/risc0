// Copyright Supranational LLC
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#ifndef __SPPARK_FF_POW_HPP__
#define __SPPARK_FF_POW_HPP__

#if defined(__CUDACC__) || defined(__HIPCC__)
# define inline __host__ __device__ __forceinline__
#endif

#if defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable: 4068)
#elif defined(__GNUC__) && !defined(__clang__)
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunknown-pragmas"
#endif

/*
 * Raise to a variable power, e.g. variable in respect to threadIdx.
 */
template<class T, typename U = unsigned>
inline T& pow_byref(T& val, U p)
{
    T sqr = val;
    val = T::csel(val, T::one(), p&1);

    #pragma unroll 1
    while (p >>= 1) {
        sqr.sqr();
        if (p&1)
            val *= sqr;
    }

    return val;
}

#if defined(__CUDACC__) || defined(__HIPCC__)
/*
 * This is meant to be used for code size optimization by deduplicating
 * otherwise inlined pow_byref.
 */
template<class T> __device__ __noinline__
T pow_byval(T val, unsigned p)
{   return pow_byref(val, p);   }
#endif

#include <cassert>

/*
 * Raise to a constant power, e.g. x^7. The idea is to let compiler
 * "decide" how to unroll with expectation that for small constants
 * it will be fully inrolled.
 */
template<class T>
inline T& pow_byref(T& val, int p)
{
    assert(p >= 2);

    T sqr = val;
    if ((p&1) == 0) {
        do {
            sqr.sqr();
            p >>= 1;
        } while ((p&1) == 0);
        val = sqr;
    }
    for (p >>= 1; p; p >>= 1) {
        sqr.sqr();
        if (p&1)
            val *= sqr;
    }
    return val;
}

#if defined(__CUDACC__) || defined(__HIPCC__)
/*
 * This is meant to be used for code size optimization by deduplicating
 * otherwise inlined pow_byref.
 */
template<class T> __device__ __noinline__
T pow_byval(T val, int p)
{   return pow_byref(val, p);   }

# undef inline
#endif

#if defined(_MSC_VER)
# pragma warning(pop)
#elif defined(__GNUC__) && !defined(__clang__)
# pragma GCC diagnostic pop
#endif

#endif
