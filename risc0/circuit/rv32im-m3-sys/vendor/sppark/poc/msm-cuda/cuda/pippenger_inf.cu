// Copyright Supranational LLC
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#include <cuda.h>

#if defined(FEATURE_BLS12_381)
# include <ff/bls12-381-fp2.hpp>
#elif defined(FEATURE_BLS12_377)
# include <ff/bls12-377-fp2.hpp>
#elif defined(FEATURE_BN254)
# include <ff/alt_bn128-fp2.hpp>
#else
# error "no FEATURE"
#endif

#include <ec/jacobian_t.hpp>
#include <ec/xyzz_t.hpp>

typedef jacobian_t<fp_t> point_t;
typedef xyzz_t<fp_t> bucket_t;
typedef bucket_t::affine_inf_t affine_t;
typedef fr_t scalar_t;

#define SPPARK_DONT_INSTANTIATE_TEMPLATES
#include <msm/pippenger.cuh>

extern "C"
RustError::by_value mult_pippenger_inf(point_t* out, const affine_t points[],
                                       size_t npoints, const scalar_t scalars[],
                                       size_t ffi_affine_sz)
{
    return mult_pippenger<bucket_t>(out, points, npoints, scalars, false, ffi_affine_sz);
}

#if defined(FEATURE_BLS12_381) || defined(FEATURE_BLS12_377) || defined(FEATURE_BN254)
typedef jacobian_t<fp2_t> point_fp2_t;
typedef xyzz_t<fp2_t> bucket_fp2_t;
typedef bucket_fp2_t::affine_inf_t affine_fp2_t;

extern "C"
RustError::by_value mult_pippenger_fp2_inf(point_fp2_t* out, const affine_fp2_t points[],
                                           size_t npoints, const scalar_t scalars[],
                                           size_t ffi_affine_sz)
{
    return mult_pippenger<bucket_fp2_t>(out, points, npoints, scalars, false, ffi_affine_sz);
}
#endif
