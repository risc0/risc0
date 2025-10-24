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

// Permutes the data in an array such that data[i] = data[bit_reverse(i)]
// and data[bit_reverse(i)] = data[i]
template<class fr_t>
__launch_bounds__(1024) __global__
void bit_rev_permutation(fr_t* d_out, const fr_t *d_in, uint32_t lg_domain_size)
{
    if (gridDim.x == 1 && blockDim.x == (1 << lg_domain_size)) {
        uint32_t idx = threadIdx.x;
        uint32_t rev = bit_rev(idx, lg_domain_size);

        fr_t t = d_in[idx];
        if (d_out == d_in)
            __syncthreads();
        d_out[rev] = t;
    } else {
        index_t idx = threadIdx.x + blockDim.x * (index_t)blockIdx.x;
        index_t rev = bit_rev(idx, lg_domain_size);
        bool copy = d_out != d_in && idx == rev;

        if (idx < rev || copy) {
            fr_t t0 = d_in[idx];
            if (!copy) {
                fr_t t1 = d_in[rev];
                d_out[idx] = t1;
            }
            d_out[rev] = t0;
        }
    }
}

template<unsigned int Z_COUNT, class fr_t>
__launch_bounds__(192, 2) __global__
void bit_rev_permutation_z(fr_t* out, const fr_t* in, uint32_t lg_domain_size)
{
    static_assert((Z_COUNT & (Z_COUNT-1)) == 0, "unvalid Z_COUNT");
    const uint32_t LG_Z_COUNT = lg2(Z_COUNT);

    extern __shared__ int xchg_bit_rev[];
    fr_t (*xchg)[Z_COUNT][Z_COUNT] = reinterpret_cast<decltype(xchg)>(xchg_bit_rev);

    uint32_t gid = threadIdx.x / Z_COUNT;
    uint32_t idx = threadIdx.x % Z_COUNT;
    uint32_t rev = bit_rev(idx, LG_Z_COUNT);

    index_t step = (index_t)1 << (lg_domain_size - LG_Z_COUNT);
    index_t tid = threadIdx.x + blockDim.x * (index_t)blockIdx.x;

    #pragma unroll 1
    do {
        (Z_COUNT > warpSize) ? __syncthreads() : __syncwarp();

        index_t group_idx = tid >> LG_Z_COUNT;
        index_t group_rev = bit_rev(group_idx, lg_domain_size - 2*LG_Z_COUNT);

        if (group_idx > group_rev)
            continue;

        index_t base_idx = group_idx * Z_COUNT + idx;
        index_t base_rev = group_rev * Z_COUNT + idx;

        fr_t regs[Z_COUNT];

#ifndef __HIP_DEVICE_COMPILE__
        #pragma unroll
        for (uint32_t i = 0; i < Z_COUNT; i++) {
            xchg[gid][i][rev] = (regs[i] = in[i * step + base_idx]);
            if (group_idx != group_rev)
                regs[i] = in[i * step + base_rev];
        }
#else
        #pragma unroll
        for (uint32_t i = 0; i < Z_COUNT; i++)
            xchg[gid][i][rev] = (regs[i] = in[i * step + base_idx]);

        if (group_idx != group_rev) {
            #pragma unroll
            for (uint32_t i = 0; i < Z_COUNT; i++)
                regs[i] = in[i * step + base_rev];
        } else {
            #pragma unroll
            for (uint32_t i = 0; i < Z_COUNT; i++)
                regs[i].zero();
        }

        asm("" : "+v"(base_idx));
        asm("" : "+v"(base_rev));
#endif

        (Z_COUNT > warpSize) ? __syncthreads() : __syncwarp();

        #pragma unroll
        for (uint32_t i = 0; i < Z_COUNT; i++)
            out[i * step + base_rev] = xchg[gid][rev][i];

        if (group_idx == group_rev)
            continue;

        (Z_COUNT > warpSize) ? __syncthreads() : __syncwarp();

        #pragma unroll
        for (uint32_t i = 0; i < Z_COUNT; i++)
            xchg[gid][i][rev] = regs[i];

        (Z_COUNT > warpSize) ? __syncthreads() : __syncwarp();

        #pragma unroll
        for (uint32_t i = 0; i < Z_COUNT; i++)
            out[i * step + base_idx] = xchg[gid][rev][i];

#ifdef __CUDA_ARCH__
    } while (Z_COUNT <= WARP_SZ && (tid += blockDim.x*gridDim.x) < step);
    // without "Z_COUNT <= WARP_SZ" compiler spills 128 bytes to stack :-(
#else
    } while ((tid += blockDim.x*gridDim.x) < step);
#endif
}

template<class fr_t>
__device__ __forceinline__
fr_t get_intermediate_root(index_t pow, const fr_t (*roots)[WINDOW_SIZE])
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
void LDE_distribute_powers(fr_t* d_inout, uint32_t lg_domain_size,
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
        r *= get_intermediate_root(pow, gen_powers);

        d_inout[idx] = r;
    }
}

template<class fr_t>
__launch_bounds__(1024) __global__
void LDE_spread_distribute_powers(fr_t* out, fr_t* in,
                                  const fr_t (*gen_powers)[WINDOW_SIZE],
                                  uint32_t lg_domain_size, uint32_t lg_blowup,
                                  bool perform_shift = true,
                                  bool ext_pow = false)
{
    extern __shared__ int xchg_lde_spread[]; // block size
    fr_t* exchange = reinterpret_cast<decltype(exchange)>(xchg_lde_spread);

    size_t domain_size = (size_t)1 << lg_domain_size;
    uint32_t blowup = 1u << lg_blowup;
    uint32_t stride = gridDim.x * blockDim.x;

    assert(lg_domain_size + lg_blowup <= MAX_LG_DOMAIN_SIZE &&
           (stride & (stride-1)) == 0);

    bool overlapping_data = false;

    if ((in < out && (in + domain_size) > out)
     || (in >= out && (out + domain_size * blowup) > in))
    {
        overlapping_data = true;
        assert(&out[domain_size * (blowup - 1)] == &in[0]);
    }

    index_t idx0 = blockDim.x * blockIdx.x;

#if 0
    index_t iters = domain_size / stride;
#else
    index_t iters = domain_size >> (31 - __clz(stride));
#endif

    for (index_t iter = 0; iter < iters; iter++) {
        index_t idx = idx0 + threadIdx.x;

        fr_t r = in[idx];

        if (perform_shift) {
            index_t pow = bit_rev(idx, lg_domain_size +
                                  (ext_pow ? lg_blowup : 0));

            r = r * get_intermediate_root(pow, gen_powers);
        }

        __syncthreads();

        exchange[threadIdx.x] = r;

        if (overlapping_data && (iter >= (blowup - 1) * (iters >> lg_blowup)))
            cooperative_groups::this_grid().sync();
        else
            __syncthreads();

        for (uint32_t offset = threadIdx.x, i = 0; i < blowup; i += 2) {
#ifdef __HIP_DEVICE_COMPILE__
            r = exchange[offset >> lg_blowup];
            r = czero(r, offset & (blowup-1));
#else
            r.zero();
            if ((offset & (blowup-1)) == 0)
                r = exchange[offset >> lg_blowup];
#endif
            out[(idx0 << lg_blowup) + offset] = r;
            offset += blockDim.x;

#ifdef __HIP_DEVICE_COMPILE__
            r = exchange[offset >> lg_blowup];
            r = czero(r, offset & (blowup-1));
#else
            r.zero();
            if ((offset & (blowup-1)) == 0)
                r = exchange[offset >> lg_blowup];
#endif
            out[(idx0 << lg_blowup) + offset] = r;
            offset += blockDim.x;
        }

        idx0 += stride;
    }
}

template<class fr_t>
__device__ __forceinline__
void get_intermediate_roots(fr_t& root0, fr_t& root1,
                            index_t idx0, index_t idx1,
                            const fr_t (*roots)[WINDOW_SIZE])
{
    int win = (WINDOW_NUM - 1) * LG_WINDOW_SIZE;
    int off = (WINDOW_NUM - 1);
    index_t idxo = idx0 | idx1;
    index_t mask = ((index_t)1 << win) - 1;

    root0 = roots[off][idx0 >> win];
    root1 = roots[off][idx1 >> win];
    #pragma unroll 1
    while (off-- && (idxo & mask)) {
        fr_t t;
        win -= LG_WINDOW_SIZE;
        mask >>= LG_WINDOW_SIZE;
        root0 *= (t = roots[off][(idx0 >> win) % WINDOW_SIZE]);
        root1 *= (t = roots[off][(idx1 >> win) % WINDOW_SIZE]);
    }
}

template<int z_count, class fr_t>
__device__ __forceinline__
void coalesced_load(fr_t r[z_count], const fr_t* inout, index_t idx,
                    const unsigned int stage)
{
    const unsigned int x = threadIdx.x & (z_count - 1);
    idx &= ~((index_t)(z_count - 1) << stage);
    idx += x;

    #pragma unroll
    for (int z = 0; z < z_count; z++, idx += (index_t)1 << stage)
        r[z] = inout[idx];
}

template<int z_count, class fr_t>
__device__ __forceinline__
void transpose(fr_t r[z_count])
{
    extern __shared__ int xchg_transpose[];
    fr_t (*xchg)[z_count] = reinterpret_cast<decltype(xchg)>(xchg_transpose);

    const unsigned int x = threadIdx.x & (z_count - 1);
    const unsigned int y = threadIdx.x & ~(z_count - 1);

    #pragma unroll
    for (int z = 0; z < z_count; z++)
        xchg[y + z][x] = r[z];

    __syncthreads();

    #pragma unroll
    for (int z = 0; z < z_count; z++)
        r[z] = xchg[y + x][z];

    __syncthreads();
}

template<int z_count, class fr_t>
__device__ __forceinline__
void coalesced_store(fr_t* inout, index_t idx, const fr_t r[z_count],
                     const unsigned int stage)
{
    const unsigned int x = threadIdx.x & (z_count - 1);
    idx &= ~((index_t)(z_count - 1) << stage);
    idx += x;

    #pragma unroll
    for (int z = 0; z < z_count; z++, idx += (index_t)1 << stage)
        inout[idx] = r[z];
}

#if defined(FEATURE_BABY_BEAR) || defined(FEATURE_GOLDILOCKS)
# include "kernels/gs_mixed_radix_narrow.cuh"
# include "kernels/ct_mixed_radix_narrow.cuh"
#else // 256-bit fields
# include "kernels/gs_mixed_radix_wide.cuh"
# include "kernels/ct_mixed_radix_wide.cuh"
#endif

#endif /* __NTT_KERNELS_CU__ */
