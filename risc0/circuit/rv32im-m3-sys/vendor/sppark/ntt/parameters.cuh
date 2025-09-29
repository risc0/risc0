// Copyright Supranational LLC
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#ifndef __SPPARK_NTT_PARAMETERS_CUH__
#define __SPPARK_NTT_PARAMETERS_CUH__

// Maximum domain size supported. Can be adjusted at will, but with the
// target field in mind. Most fields handle up to 2^32 elements, BLS12-377
// can handle up to 2^47, alt_bn128 - 2^28...
#ifndef MAX_LG_DOMAIN_SIZE
# if defined(FEATURE_BN254)
#  define MAX_LG_DOMAIN_SIZE 28
# elif defined(FEATURE_BABY_BEAR)
#  define MAX_LG_DOMAIN_SIZE 27
# else
#  define MAX_LG_DOMAIN_SIZE 28 // tested only up to 2^31 for now
# endif
#endif

#if MAX_LG_DOMAIN_SIZE <= 32
typedef unsigned int index_t;
#else
typedef size_t index_t;
#endif

#if defined(FEATURE_BABY_BEAR)
# define LG_WINDOW_SIZE ((MAX_LG_DOMAIN_SIZE + 4) / 5)
#elif defined(FEATURE_GOLDILOCKS)
# if MAX_LG_DOMAIN_SIZE <= 28
#  define LG_WINDOW_SIZE ((MAX_LG_DOMAIN_SIZE + 3) / 4)
# else
#  define LG_WINDOW_SIZE ((MAX_LG_DOMAIN_SIZE + 4) / 5)
# endif
#else // 256-bit fields
# if MAX_LG_DOMAIN_SIZE <= 28
#  define LG_WINDOW_SIZE ((MAX_LG_DOMAIN_SIZE + 1) / 2)
# else
#  define LG_WINDOW_SIZE ((MAX_LG_DOMAIN_SIZE + 2) / 3)
# endif
#endif

#define WINDOW_SIZE (1 << LG_WINDOW_SIZE)
#define WINDOW_NUM ((MAX_LG_DOMAIN_SIZE + LG_WINDOW_SIZE - 1) / LG_WINDOW_SIZE)

__device__ __constant__ fr_t forward_radix6_twiddles[32] = {};
__device__ __constant__ fr_t inverse_radix6_twiddles[32] = {};

#if !defined(__CUDA_ARCH__) && !defined(__HIP_DEVICE_COMPILE__)
# if defined(FEATURE_BLS12_377)
#  include "parameters/bls12_377.h"
# elif defined(FEATURE_BLS12_381)
#  include "parameters/bls12_381.h"
# elif defined(FEATURE_PALLAS)
#  include "parameters/vesta.h"     // Fr for Pallas curve is Vesta
# elif defined(FEATURE_VESTA)
#  include "parameters/pallas.h"    // Fr for Vesta curve is Pallas
# elif defined(FEATURE_BN254)
#  include "parameters/alt_bn128.h"
# elif defined(FEATURE_BABY_BEAR)
#  include "parameters/baby_bear.h"
# elif defined(FEATURE_GOLDILOCKS)
#  include "parameters/goldilocks.h"
# endif
#else
extern const fr_t group_gen, group_gen_inverse;
extern const fr_t forward_roots_of_unity[];
extern const fr_t inverse_roots_of_unity[];
extern const fr_t domain_size_inverse[];
#endif

template<typename T>
__device__ __forceinline__
T bit_rev(T i, unsigned int nbits)
{
    if (sizeof(i) == 4 || nbits <= 32)
        return __brev(i) >> (8*sizeof(unsigned int) - nbits);
    else
        return __brevll(i) >> (8*sizeof(unsigned long long) - nbits);
}

template<typename T>
static __device__ __host__ constexpr uint32_t lg2(T n)
{   uint32_t ret=0; while (n>>=1) ret++; return ret;   }

template<class fr_t> __global__
void generate_partial_twiddles(fr_t (*roots)[WINDOW_SIZE],
                               const fr_t root_of_unity)
{
    const unsigned int tid = threadIdx.x + blockDim.x * blockIdx.x;
    assert(tid < WINDOW_SIZE);

    fr_t root = root_of_unity^tid;

    roots[0][tid] = root;

    for (int off = 1; off < WINDOW_NUM; off++) {
        for (int i = 0; i < LG_WINDOW_SIZE; i++)
            root.sqr();
        roots[off][tid] = root;
    }
}

template<class fr_t> __launch_bounds__(512) __global__
void generate_all_twiddles(fr_t* d_radixX_twiddles, const fr_t root10)
{
    fr_t root = root10^threadIdx.x;

    d_radixX_twiddles[threadIdx.x] = root;

    d_radixX_twiddles += 512;
    if (threadIdx.x % 2 == 0)
        d_radixX_twiddles[threadIdx.x/2] = root;

    d_radixX_twiddles += 256;
    if (threadIdx.x % 4 == 0)
        d_radixX_twiddles[threadIdx.x/4] = root;

    d_radixX_twiddles += 128;
    if (threadIdx.x % 8 == 0)
        d_radixX_twiddles[threadIdx.x/8] = root;

    d_radixX_twiddles += 64;
    if (threadIdx.x % 16 == 0)
        d_radixX_twiddles[threadIdx.x/16] = root;
}

template<class fr_t> __launch_bounds__(512) __global__
void generate_radixX_twiddles_X(fr_t* d_radixX_twiddles_X, int n,
                                const fr_t root_of_unity)
{
    unsigned int nbits = 31 - __clz(blockDim.x);
    unsigned int pow_rev = bit_rev(threadIdx.x, nbits);

    if (gridDim.x == 1) {
        d_radixX_twiddles_X[threadIdx.x] = fr_t::one();
        d_radixX_twiddles_X += blockDim.x;

        fr_t root0 = root_of_unity^pow_rev;

        d_radixX_twiddles_X[threadIdx.x] = root0;
        d_radixX_twiddles_X += blockDim.x;

        fr_t root1 = root0;

        for (int i = 2; i < n; i++) {
            root1 *= root0;
            d_radixX_twiddles_X[threadIdx.x] = root1;
            d_radixX_twiddles_X += blockDim.x;
        }
    } else {
        fr_t root0 = root_of_unity^(pow_rev * gridDim.x);
        fr_t root1 = root_of_unity^(pow_rev * blockIdx.x);
        unsigned int tid = blockIdx.x * blockDim.x + threadIdx.x;

        d_radixX_twiddles_X[tid] = root1;
        d_radixX_twiddles_X += gridDim.x * blockDim.x;

        for (int i = gridDim.x; i < n; i += gridDim.x) {
            root1 *= root0;
            d_radixX_twiddles_X[tid] = root1;
            d_radixX_twiddles_X += gridDim.x * blockDim.x;
        }
    }
}

template<class fr_t> __launch_bounds__(1024) __global__
void generate_plus_one_twiddles(fr_t (*d_plus_one_twiddles)[1024],
                                const fr_t root_of_unity)
{
    unsigned int tid = blockIdx.x * blockDim.x + threadIdx.x;

    fr_t root = root_of_unity^bit_rev(tid, 10);

    d_plus_one_twiddles[0][tid] = root;

    for (unsigned int off = 1; off < MAX_LG_DOMAIN_SIZE-15; off++) {
        root.sqr();
        d_plus_one_twiddles[off][tid] = root;
    }
}

class NTTParameters {
private:
    const gpu_t& gpu;
    bool inverse;

public:
    fr_t (*partial_twiddles)[WINDOW_SIZE];

    fr_t* twiddles[5];

    fr_t (*partial_group_gen_powers)[WINDOW_SIZE]; // for LDE

#if !defined(FEATURE_BABY_BEAR) && !defined(FEATURE_GOLDILOCKS)
    fr_t* radix6_twiddles_6, * radix7_twiddles_7,
        * radix8_twiddles_8, * radix9_twiddles_9;

private:
    fr_t* twiddles_X(int num_blocks, int block_size, const fr_t& root,
                     stream_t& s)
    {
        fr_t* ret = (fr_t*)s.Dmalloc(num_blocks * block_size * sizeof(fr_t));
        generate_radixX_twiddles_X<<<16, block_size, 0, s>>>(ret, num_blocks, root);
        CUDA_OK(cudaGetLastError());
        return ret;
    }
#else
    fr_t (*plus_one_twiddles)[1024];
#endif

public:
    NTTParameters(const bool _inverse, int id)
        : gpu(select_gpu(id)), inverse(_inverse)
    {
        const fr_t* roots = inverse ? inverse_roots_of_unity
                                    : forward_roots_of_unity;

        const size_t blob_sz = 512 + 256 + 128 + 64 + 32;

        fr_t* blob = reinterpret_cast<decltype(blob)>
                     (gpu[0].Dmalloc(blob_sz * sizeof(fr_t)));

        twiddles[4] = blob;                 /* radix10_twiddles */
        twiddles[3] = twiddles[4] + 512;    /* radix9_twiddles */
        twiddles[2] = twiddles[3] + 256;    /* radix8_twiddles */
        twiddles[1] = twiddles[2] + 128;    /* radix7_twiddles */
        twiddles[0] = twiddles[1] + 64;     /* radix6_twiddles */

        generate_all_twiddles<<<1, 512, 0, gpu[0]>>>(blob, roots[10]);
        CUDA_OK(cudaGetLastError());

        /* copy radix6_twiddles to the constant segment */
        fr_t* radix6_twiddles;
        CUDA_OK(cudaGetSymbolAddress((void**)&radix6_twiddles,
                                     inverse ? inverse_radix6_twiddles
                                             : forward_radix6_twiddles));
        CUDA_OK(cudaMemcpyAsync(radix6_twiddles, twiddles[0],
                                32 * sizeof(fr_t), cudaMemcpyDeviceToDevice,
                                gpu[0]));
        twiddles[0] = radix6_twiddles;

#if !defined(FEATURE_BABY_BEAR) && !defined(FEATURE_GOLDILOCKS)
        radix6_twiddles_6 = twiddles_X(64, 64, roots[12], gpu[1]);
        radix7_twiddles_7 = twiddles_X(128, 128, roots[14], gpu[2]);
        radix8_twiddles_8 = twiddles_X(256, 256, roots[16], gpu[0]);
        radix9_twiddles_9 = twiddles_X(512, 512, roots[18], gpu[1]);
#else
        plus_one_twiddles = reinterpret_cast<decltype(plus_one_twiddles)>
                            (gpu[1].Dmalloc((MAX_LG_DOMAIN_SIZE-15) * 1024 * sizeof(fr_t)));

        generate_plus_one_twiddles<<<1, 1024, 0, gpu[1]>>>(plus_one_twiddles,
                                                           roots[MAX_LG_DOMAIN_SIZE]);
        CUDA_OK(cudaGetLastError());
#endif

        const size_t partial_sz = WINDOW_NUM * WINDOW_SIZE;

        partial_twiddles = reinterpret_cast<decltype(partial_twiddles)>
                           (gpu[2].Dmalloc(2 * partial_sz * sizeof(fr_t)));
        partial_group_gen_powers = &partial_twiddles[WINDOW_NUM];

        generate_partial_twiddles<<<WINDOW_SIZE/32, 32, 0, gpu[2]>>>
            (partial_twiddles, roots[MAX_LG_DOMAIN_SIZE]);
        CUDA_OK(cudaGetLastError());

        generate_partial_twiddles<<<WINDOW_SIZE/32, 32, 0, gpu[2]>>>
            (partial_group_gen_powers, inverse ? group_gen_inverse
                                               : group_gen);
        CUDA_OK(cudaGetLastError());
    }
    NTTParameters(const NTTParameters&) = delete;
    NTTParameters(NTTParameters&&) = default;

    ~NTTParameters()
    {
        int current_id;
        if (cudaGetDevice(&current_id) != cudaSuccess) {
            gpu.select();

            (void)cudaFreeAsync(partial_twiddles, gpu[2]);
#if !defined(FEATURE_BABY_BEAR) && !defined(FEATURE_GOLDILOCKS)
            (void)cudaFreeAsync(radix9_twiddles_9, gpu[1]);
            (void)cudaFreeAsync(radix8_twiddles_8, gpu[0]);
            (void)cudaFreeAsync(radix7_twiddles_7, gpu[2]);
            (void)cudaFreeAsync(radix6_twiddles_6, gpu[1]);
#else
            (void)cudaFreeAsync(plus_one_twiddles, gpu[1]);
#endif
            (void)cudaFreeAsync(twiddles[4], gpu[0]);

            (void)cudaSetDevice(current_id);
        }
    }

    inline void sync() const    { gpu.sync(); }

private:
    class all_params { friend class NTTParameters;
        std::vector<NTTParameters> forward;
        std::vector<NTTParameters> inverse;

        all_params()
        {
            int current_id;
            (void)cudaGetDevice(&current_id);

            size_t nids = ngpus();
            forward.reserve(nids);
            for (size_t id = 0; id < nids; id++)
                forward.emplace_back(false, id);
            inverse.reserve(nids);
            for (size_t id = 0; id < nids; id++)
                inverse.emplace_back(true, id);
            for (size_t id = 0; id < nids; id++)
                inverse[id].sync();

            (void)cudaSetDevice(current_id);
        }
    };

public:
    static const auto& all(bool inverse = false)
    {
        static all_params params;
        return inverse ? params.inverse : params.forward;
    }
};
#endif /* __SPPARK_NTT_PARAMETERS_CUH__ */
