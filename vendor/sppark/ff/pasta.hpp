// Copyright Supranational LLC
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#ifndef __SPPARK_FF_PASTA_HPP__
#define __SPPARK_FF_PASTA_HPP__

#include <cstdint>
#if defined(__CUDACC__) || defined(__HIPCC__)

namespace device {
    static __device__ __constant__ __align__(16) const uint32_t Vesta_P[8] = {
        0x00000001, 0x8c46eb21, 0x0994a8dd, 0x224698fc,
        0x00000000, 0x00000000, 0x00000000, 0x40000000
    };
    static __device__ __constant__ __align__(16) const uint32_t Vesta_RR[8] = { /* (1<<512)%P */
        0x0000000f, 0xfc9678ff, 0x891a16e3, 0x67bb433d,
        0x04ccf590, 0x7fae2310, 0x7ccfdaa9, 0x096d41af
    };
    static __device__ __constant__ __align__(16) const uint32_t Vesta_one[8] = { /* (1<<256)%P */
        0xfffffffd, 0x5b2b3e9c, 0xe3420567, 0x992c350b,
        0xffffffff, 0xffffffff, 0xffffffff, 0x3fffffff
    };
    static __device__ __constant__ __align__(16) const uint32_t Vesta_Px2[8] = { /* left-aligned modulus */
        0x00000002, 0x188dd642, 0x132951bb, 0x448d31f8,
        0x00000000, 0x00000000, 0x00000000, 0x80000000
    };

    static __device__ __constant__ __align__(16) const uint32_t Pallas_P[8] = {
        0x00000001, 0x992d30ed, 0x094cf91b, 0x224698fc,
        0x00000000, 0x00000000, 0x00000000, 0x40000000
    };
    static __device__ __constant__ __align__(16) const uint32_t Pallas_RR[8] = { /* (1<<512)%P */
        0x0000000f, 0x8c78ecb3, 0x8b0de0e7, 0xd7d30dbd,
        0xc3c95d18, 0x7797a99b, 0x7b9cb714, 0x096d41af
    };
    static __device__ __constant__ __align__(16) const uint32_t Pallas_one[8] = { /* (1<<256)%P */
        0xfffffffd, 0x34786d38, 0xe41914ad, 0x992c350b,
        0xffffffff, 0xffffffff, 0xffffffff, 0x3fffffff
    };
    static __device__ __constant__ __align__(16) const uint32_t Pallas_Px2[8] = { /* left-aligned modulus */
        0x00000002, 0x325a61da, 0x1299f237, 0x448d31f8,
        0x00000000, 0x00000000, 0x00000000, 0x80000000
    };
    static __device__ __constant__ /*const*/ uint32_t Pasta_M0 = 0xffffffff;
}

# if defined(__CUDA_ARCH__) || defined(__HIPCC__)   // device-side field types
#  if defined(__CUDA_ARCH__)
#   include "mont_t.cuh"
#  elif defined(__HIPCC__)
#   include "mont_t.hip"
typedef uint64_t vec256[4];
#  endif
typedef mont_t<255, device::Vesta_P, device::Pasta_M0,
                    device::Vesta_RR, device::Vesta_one,
                    device::Vesta_Px2> vesta_mont;
struct vesta_t : public vesta_mont {
    using mem_t = vesta_t;
    __device__ __forceinline__ vesta_t() {}
    __device__ __forceinline__ vesta_t(const vesta_mont& a) : vesta_mont(a) {}
    template<typename... Ts> constexpr vesta_t(Ts... a)     : vesta_mont{a...} {}
#  ifdef __HIPCC__
    __host__   __forceinline__ vesta_t(vec256 a)            : vesta_mont(a) {}
#  endif
};
typedef mont_t<255, device::Pallas_P, device::Pasta_M0,
                    device::Pallas_RR, device::Pallas_one,
                    device::Pallas_Px2> pallas_mont;
struct pallas_t : public pallas_mont {
    using mem_t = pallas_t;
    __device__ __forceinline__ pallas_t() {}
    __device__ __forceinline__ pallas_t(const pallas_mont& a) : pallas_mont(a) {}
    template<typename... Ts> constexpr pallas_t(Ts... a)      : pallas_mont{a...} {}
#  ifdef __HIPCC__
    __host__   __forceinline__ pallas_t(vec256 a)             : pallas_mont(a) {}
#  endif
};
# endif
#endif

#if !defined(__CUDA_ARCH__) && !defined(__HIPCC__)  // host-side field types
# include <pasta_t.hpp>
#endif

# if defined(__GNUC__) && !defined(__clang__)
#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wsubobject-linkage"
# endif

#if defined(FEATURE_PALLAS)
namespace pallas {
typedef pallas_t fp_t;
typedef vesta_t fr_t;
}
using namespace pallas;
#elif defined(FEATURE_VESTA)
namespace vesta {
typedef vesta_t fp_t;
typedef pallas_t fr_t;
}
using namespace vesta;
#endif

#endif
