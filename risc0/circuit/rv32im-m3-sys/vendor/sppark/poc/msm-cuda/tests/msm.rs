// Copyright Supranational LLC
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#[cfg(feature = "bls12_377")]
use ark_bls12_377::{G1Affine, G2Affine};
#[cfg(feature = "bls12_381")]
use ark_bls12_381::{G1Affine, G2Affine};
#[cfg(feature = "bn254")]
use ark_bn254::{G1Affine, G2Affine};
use ark_ec::msm::VariableBaseMSM;
use ark_ec::ProjectiveCurve;
use ark_ff::BigInteger256;

use std::str::FromStr;

use msm_cuda::*;

#[test]
fn msm_correctness() {
    let test_npow = std::env::var("TEST_NPOW").unwrap_or("15".to_string());
    let npoints_npow = i32::from_str(&test_npow).unwrap();

    let (points, scalars) =
        util::generate_points_scalars::<G1Affine>(1usize << npoints_npow);

    let msm_result = multi_scalar_mult_arkworks(points.as_slice(), unsafe {
        std::mem::transmute::<&[_], &[BigInteger256]>(scalars.as_slice())
    })
    .into_affine();

    let arkworks_result =
        VariableBaseMSM::multi_scalar_mul(points.as_slice(), unsafe {
            std::mem::transmute::<&[_], &[BigInteger256]>(scalars.as_slice())
        })
        .into_affine();

    assert_eq!(msm_result, arkworks_result);
}

#[cfg(any(feature = "bls12_381", feature = "bls12_377", feature = "bn254"))]
#[test]
fn msm_fp2_correctness() {
    let test_npow = std::env::var("TEST_NPOW").unwrap_or("14".to_string());
    let npoints_npow = i32::from_str(&test_npow).unwrap();

    let (points, scalars) =
        util::generate_points_scalars::<G2Affine>(1usize << npoints_npow);

    let msm_result =
        multi_scalar_mult_fp2_arkworks(points.as_slice(), unsafe {
            std::mem::transmute::<&[_], &[BigInteger256]>(scalars.as_slice())
        })
        .into_affine();

    let arkworks_result =
        VariableBaseMSM::multi_scalar_mul(points.as_slice(), unsafe {
            std::mem::transmute::<&[_], &[BigInteger256]>(scalars.as_slice())
        })
        .into_affine();

    assert_eq!(msm_result, arkworks_result);
}
