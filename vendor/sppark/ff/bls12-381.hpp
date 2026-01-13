// Copyright Supranational LLC
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#ifndef __SPPARK_FF_BLS13_381_HPP__
#define __SPPARK_FF_BLS13_381_HPP__

#include <cstdint>
#if defined(__CUDACC__) || defined(__HIPCC__)

namespace device {
#define TO_CUDA_T(limb64) (uint32_t)(limb64), (uint32_t)(limb64>>32)
    static __device__ __constant__ __align__(16) const uint32_t BLS12_381_P[12] = {
        TO_CUDA_T(0xb9feffffffffaaab), TO_CUDA_T(0x1eabfffeb153ffff),
        TO_CUDA_T(0x6730d2a0f6b0f624), TO_CUDA_T(0x64774b84f38512bf),
        TO_CUDA_T(0x4b1ba7b6434bacd7), TO_CUDA_T(0x1a0111ea397fe69a)
    };
    static __device__ __constant__ __align__(16) const uint32_t BLS12_381_RR[12] = { /* (1<<768)%P */
        TO_CUDA_T(0xf4df1f341c341746), TO_CUDA_T(0x0a76e6a609d104f1),
        TO_CUDA_T(0x8de5476c4c95b6d5), TO_CUDA_T(0x67eb88a9939d83c0),
        TO_CUDA_T(0x9a793e85b519952d), TO_CUDA_T(0x11988fe592cae3aa)
    };
    static __device__ __constant__ __align__(16) const uint32_t BLS12_381_one[12] = { /* (1<<384)%P */
        TO_CUDA_T(0x760900000002fffd), TO_CUDA_T(0xebf4000bc40c0002),
        TO_CUDA_T(0x5f48985753c758ba), TO_CUDA_T(0x77ce585370525745),
        TO_CUDA_T(0x5c071a97a256ec6d), TO_CUDA_T(0x15f65ec3fa80e493)
    };
    static __device__ __constant__ __align__(16) const uint32_t BLS12_381_Px8[12] = { /* left-aligned value of the modulus */
        TO_CUDA_T(0xcff7fffffffd5558), TO_CUDA_T(0xf55ffff58a9ffffd),
        TO_CUDA_T(0x39869507b587b120), TO_CUDA_T(0x23ba5c279c2895fb),
        TO_CUDA_T(0x58dd3db21a5d66bb), TO_CUDA_T(0xd0088f51cbff34d2)
    };
    static __device__ __constant__ const uint32_t BLS12_381_M0 = 0xfffcfffd;

    static __device__ __constant__ __align__(16) const uint32_t BLS12_381_r[8] = {
        TO_CUDA_T(0xffffffff00000001), TO_CUDA_T(0x53bda402fffe5bfe),
        TO_CUDA_T(0x3339d80809a1d805), TO_CUDA_T(0x73eda753299d7d48)
    };
    static __device__ __constant__ __align__(16) const uint32_t BLS12_381_rRR[8] = { /* (1<<512)%P */
        TO_CUDA_T(0xc999e990f3f29c6d), TO_CUDA_T(0x2b6cedcb87925c23),
        TO_CUDA_T(0x05d314967254398f), TO_CUDA_T(0x0748d9d99f59ff11)
    };
    static __device__ __constant__ __align__(16) const uint32_t BLS12_381_rone[8] = { /* (1<<256)%P */
        TO_CUDA_T(0x00000001fffffffe), TO_CUDA_T(0x5884b7fa00034802),
        TO_CUDA_T(0x998c4fefecbc4ff5), TO_CUDA_T(0x1824b159acc5056f)
    };
    static __device__ __constant__ __align__(16) const uint32_t BLS12_381_rx2[8] = { /* left-aligned value of the modulus */
        TO_CUDA_T(0xfffffffe00000002), TO_CUDA_T(0xa77b4805fffcb7fd),
        TO_CUDA_T(0x6673b0101343b00a), TO_CUDA_T(0xe7db4ea6533afa90),
    };
    static __device__ __constant__ /*const*/ uint32_t BLS12_381_m0 = 0xffffffff;
}
# if defined(__CUDA_ARCH__) || defined(__HIPCC__)   // device-side field types
#  if defined(__CUDA_ARCH__)
#   include "mont_t.cuh"
#  elif defined(__HIPCC__)
#   include "mont_t.hip"
typedef uint64_t vec256[4];
#  endif

namespace bls12_381 {

typedef mont_t<381, device::BLS12_381_P, device::BLS12_381_M0,
                    device::BLS12_381_RR, device::BLS12_381_one,
                    device::BLS12_381_Px8> fp_mont;
struct fp_t : public fp_mont {
    using mem_t = fp_t;
    __device__ __forceinline__ fp_t() {}
    __device__ __forceinline__ fp_t(const fp_mont& a) : fp_mont(a) {}
    template<typename... Ts> constexpr fp_t(Ts... a)  : fp_mont{a...} {}
};
typedef mont_t<255, device::BLS12_381_r, device::BLS12_381_m0,
                    device::BLS12_381_rRR, device::BLS12_381_rone,
                    device::BLS12_381_rx2> fr_mont;
struct fr_t : public fr_mont {
    using mem_t = fr_t;
    __device__ __forceinline__ fr_t() {}
    __device__ __forceinline__ fr_t(const fr_mont& a) : fr_mont(a) {}
    template<typename... Ts> constexpr fr_t(Ts... a)  : fr_mont{a...} {}
#  ifdef __HIPCC__
    __host__   __forceinline__ fr_t(vec256 a)         : fr_mont(a) {}
#  endif
};

} // namespace bls12_381

# endif
#endif

#if !defined(__CUDA_ARCH__) && !defined(__HIPCC__)  // host-side field types
# include <blst_t.hpp>

# if defined(__GNUC__) && !defined(__clang__)
#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wsubobject-linkage"
# endif

namespace bls12_381 {

static const vec384 BLS12_381_P = {
    TO_LIMB_T(0xb9feffffffffaaab), TO_LIMB_T(0x1eabfffeb153ffff),
    TO_LIMB_T(0x6730d2a0f6b0f624), TO_LIMB_T(0x64774b84f38512bf),
    TO_LIMB_T(0x4b1ba7b6434bacd7), TO_LIMB_T(0x1a0111ea397fe69a)
};
static const vec384 BLS12_381_RR = {    /* (1<<768)%P */
    TO_LIMB_T(0xf4df1f341c341746), TO_LIMB_T(0x0a76e6a609d104f1),
    TO_LIMB_T(0x8de5476c4c95b6d5), TO_LIMB_T(0x67eb88a9939d83c0),
    TO_LIMB_T(0x9a793e85b519952d), TO_LIMB_T(0x11988fe592cae3aa)
};
static const vec384 BLS12_381_ONE = {   /* (1<<384)%P */
    TO_LIMB_T(0x760900000002fffd), TO_LIMB_T(0xebf4000bc40c0002),
    TO_LIMB_T(0x5f48985753c758ba), TO_LIMB_T(0x77ce585370525745),
    TO_LIMB_T(0x5c071a97a256ec6d), TO_LIMB_T(0x15f65ec3fa80e493)
};
typedef blst_384_t<381, BLS12_381_P, 0x89f3fffcfffcfffd,
                        BLS12_381_RR, BLS12_381_ONE> fp_mont;
struct fp_t : public fp_mont {
    using mem_t = fp_t;
    inline fp_t() {}
    inline fp_t(const fp_mont& a) : fp_mont(a) {}
    template<typename... Ts>
    constexpr fp_t(Ts... a)  : fp_mont{a...} {}
};

static const vec256 BLS12_381_r = { 
    TO_LIMB_T(0xffffffff00000001), TO_LIMB_T(0x53bda402fffe5bfe),
    TO_LIMB_T(0x3339d80809a1d805), TO_LIMB_T(0x73eda753299d7d48)
};
static const vec256 BLS12_381_rRR = {   /* (1<<512)%r */
    TO_LIMB_T(0xc999e990f3f29c6d), TO_LIMB_T(0x2b6cedcb87925c23),
    TO_LIMB_T(0x05d314967254398f), TO_LIMB_T(0x0748d9d99f59ff11)
};
static const vec256 BLS12_381_rONE = {  /* (1<<256)%r */
    TO_LIMB_T(0x00000001fffffffe), TO_LIMB_T(0x5884b7fa00034802),
    TO_LIMB_T(0x998c4fefecbc4ff5), TO_LIMB_T(0x1824b159acc5056f)
};
typedef blst_256_t<255, BLS12_381_r, 0xfffffffeffffffff,
                        BLS12_381_rRR, BLS12_381_rONE> fr_mont;
struct fr_t : public fr_mont {
    using mem_t = fr_t;
    inline fr_t() {}
    inline fr_t(const fr_mont& a) : fr_mont(a) {}
    template<typename... Ts>
    constexpr fr_t(Ts... a)  : fr_mont{a...} {}
};

} // namespace bls12_381

# if defined(__GNUC__) && !defined(__clang__)
#  pragma GCC diagnostic pop
# endif
#endif

#ifdef FEATURE_BLS12_381
using namespace bls12_381;
#endif

#endif
