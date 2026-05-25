// Copyright Supranational LLC
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#ifndef __NTT_KERNELS_CU__
#define __NTT_KERNELS_CU__

#if defined(__NVCC__)
# include <cooperative_groups.h>
#elif defined(__HIPCC__)
# include <hip/hip_cooperative_groups.h>
#endif

#include <ntt/parameters.cuh>

__device__
fr_t get_intermed_root(index_t pow, const fr_t (*roots)[WINDOW_SIZE])
{
    unsigned int off = 0;

    fr_t t, root;

    if (sizeof(fr_t) <= 8) {
        root = fr_t::one();
        bool root_set = false;

        #pragma unroll
        for (unsigned int pow_win, i = 0; i < WINDOW_NUM; i++) {
            if (!root_set && (pow_win = pow % WINDOW_SIZE)) {
                root = roots[i][pow_win];
                root_set = true;
            }
            if (!root_set) {
                pow >>= LG_WINDOW_SIZE;
                off++;
            }
        }
    } else {
        if ((pow % WINDOW_SIZE) == 0) {
            pow >>= LG_WINDOW_SIZE;
            off++;
        }
        root = roots[off][pow % WINDOW_SIZE];
    }

    #pragma unroll 1
    while (pow >>= LG_WINDOW_SIZE)
        root *= (t = roots[++off][pow % WINDOW_SIZE]);

    return root;
}

template<class fr_t>
__launch_bounds__(1024) __global__
void LDE_distribute_pows(fr_t* d_inout, uint32_t lg_domain_size,
                           uint32_t lg_blowup, bool bitrev,
                           const fr_t (*gen_powers)[WINDOW_SIZE])
{
#if 0
    assert(blockDim.x * gridDim.x == blockDim.x * (size_t)gridDim.x);
#endif
    size_t domain_size = (size_t)1 << lg_domain_size;
    index_t idx = threadIdx.x + blockDim.x * blockIdx.x;

    #pragma unroll 1
    for (; idx < domain_size; idx += blockDim.x * gridDim.x) {
        fr_t r = d_inout[idx];

        index_t pow = bitrev ? bit_rev(idx, lg_domain_size) : idx;
        pow <<= lg_blowup;
        r *= get_intermed_root(pow, gen_powers);

        d_inout[idx] = r;
    }
}

template<class fr_t>
__global__ //__launch_bounds__(1024)
void LDE_distribute_shift(fr_t* d_inout, uint32_t lg_domain_size,
                           uint32_t factor, bool bitrev,
                           const fr_t (*gen_powers)[WINDOW_SIZE], const uint32_t poly_count)
{
#if 0
    assert(blockDim.x * gridDim.x == blockDim.x * (size_t)gridDim.x);
#endif
    size_t domain_size = (size_t)1 << lg_domain_size;
    index_t idx = threadIdx.x + blockDim.x * blockIdx.x;

    #pragma unroll 1
    for (; idx < domain_size; idx += blockDim.x * gridDim.x) {
        index_t pow = bitrev ? bit_rev(idx, lg_domain_size) : idx;
        pow *= factor;
        fr_t p = get_intermed_root(pow, gen_powers);

        #pragma unroll
        for (uint32_t j=0; j<poly_count; j++) {
            fr_t r = d_inout[idx + j*domain_size];
            r *= p;
            d_inout[idx + j*domain_size] = r;
        }
    }
}

template<class fr_t>
__global__ //__launch_bounds__(1024)
void LDE_distribute_shift_outplace(fr_t* d_in, fr_t* d_out, uint32_t lg_domain_size,
                           uint32_t factor, bool bitrev,
                           const fr_t (*gen_powers)[WINDOW_SIZE], const uint32_t poly_count)
{
#if 0
    assert(blockDim.x * gridDim.x == blockDim.x * (size_t)gridDim.x);
#endif
    size_t domain_size = (size_t)1 << lg_domain_size;
    // index_t idx = threadIdx.x + blockDim.x * blockIdx.x;

    index_t idx = (threadIdx.x + blockDim.x * blockIdx.x) << 2;

    #pragma unroll 1
    for (; idx < domain_size; idx += blockDim.x * 4 * gridDim.x) {
        index_t pow0 = bitrev ? bit_rev(idx+0, lg_domain_size) : idx+0;
        index_t pow1 = bitrev ? bit_rev(idx+1, lg_domain_size) : idx+1;
        index_t pow2 = bitrev ? bit_rev(idx+2, lg_domain_size) : idx+2;
        index_t pow3 = bitrev ? bit_rev(idx+3, lg_domain_size) : idx+3;
        pow0 *= factor;
        pow1 *= factor;
        pow2 *= factor;
        pow3 *= factor;

        // fr_t p = get_intermediate_root(pow, gen_powers);
        fr_t p0 = get_intermed_root(pow0, gen_powers);
        fr_t p1 = get_intermed_root(pow1, gen_powers);
        fr_t p2 = get_intermed_root(pow2, gen_powers);
        fr_t p3 = get_intermed_root(pow3, gen_powers);

        #pragma unroll
        for (uint32_t j=0; j<poly_count; j++) {

            uint4 vec = *reinterpret_cast<const uint4*>(&d_in[idx + j*domain_size]);
            fr_t c0 = fr_t(vec.x);
            fr_t c1 = fr_t(vec.y);
            fr_t c2 = fr_t(vec.z);
            fr_t c3 = fr_t(vec.w);
            c0 *= p0;
            c1 *= p1;
            c2 *= p2;
            c3 *= p3;
            vec.x = *c0;
            vec.y = *c1;
            vec.z = *c2;
            vec.w = *c3;
            *reinterpret_cast<uint4*>(&d_out[idx + j*domain_size]) = vec;
        }


    }
}

#endif // __NTT_KERNELS_CU__

