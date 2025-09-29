// Copyright Supranational LLC
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#[cfg(feature = "bls12_377")]
use ark_bls12_377::{Fr, G1Affine, G1Projective, G2Affine, G2Projective};
#[cfg(feature = "bls12_381")]
use ark_bls12_381::{Fr, G1Affine, G1Projective, G2Affine, G2Projective};
#[cfg(feature = "bn254")]
use ark_bn254::{Fr, G1Affine, G1Projective, G2Affine, G2Projective};
use ark_ec::AffineCurve;
use ark_ff::PrimeField;
use ark_std::Zero;
use blst::*;

pub mod util;

pub fn multi_scalar_mult(
    points: &[blst_p1_affine],
    scalars: &[blst_scalar],
) -> blst_p1 {
    #[cfg_attr(feature = "quiet", allow(improper_ctypes))]
    extern "C" {
        fn mult_pippenger(
            out: *mut blst_p1,
            points: *const blst_p1_affine,
            npoints: usize,
            scalars: *const blst_scalar,
        ) -> sppark::Error;
    }

    let npoints = points.len();
    if npoints != scalars.len() {
        panic!("length mismatch")
    }

    let mut ret = blst_p1::default();
    let err =
        unsafe { mult_pippenger(&mut ret, &points[0], npoints, &scalars[0]) };
    if err.code != 0 {
        panic!("{}", String::from(err));
    }
    ret
}

pub fn multi_scalar_mult_arkworks<G: AffineCurve>(
    points: &[G],
    scalars: &[<G::ScalarField as PrimeField>::BigInt],
) -> G::Projective {
    #[cfg_attr(feature = "quiet", allow(improper_ctypes))]
    extern "C" {
        fn mult_pippenger_inf(
            out: *mut G1Projective,
            points_with_infinity: *const G1Affine,
            npoints: usize,
            scalars: *const Fr,
            ffi_affine_sz: usize,
        ) -> sppark::Error;
    }

    let npoints = points.len();
    if npoints != scalars.len() {
        panic!("length mismatch")
    }

    let mut ret = G::Projective::zero();
    let err = unsafe {
        mult_pippenger_inf(
            &mut ret as *mut _ as *mut _,
            points.as_ptr() as *const _,
            npoints,
            scalars.as_ptr() as *const _,
            std::mem::size_of::<G>(),
        )
    };
    if err.code != 0 {
        panic!("{}", String::from(err));
    }

    ret
}

#[cfg(any(feature = "bls12_381", feature = "bls12_377", feature = "bn254"))]
pub fn multi_scalar_mult_fp2_arkworks<G: AffineCurve>(
    points: &[G],
    scalars: &[<G::ScalarField as PrimeField>::BigInt],
) -> G::Projective {
    #[cfg_attr(feature = "quiet", allow(improper_ctypes))]
    extern "C" {
        fn mult_pippenger_fp2_inf(
            out: *mut G2Projective,
            points_with_infinity: *const G2Affine,
            npoints: usize,
            scalars: *const Fr,
            ffi_affine_sz: usize,
        ) -> sppark::Error;
    }

    let npoints = points.len();
    if npoints != scalars.len() {
        panic!("length mismatch")
    }

    let mut ret = G::Projective::zero();
    let err = unsafe {
        mult_pippenger_fp2_inf(
            &mut ret as *mut _ as *mut _,
            points.as_ptr() as *const _,
            npoints,
            scalars.as_ptr() as *const _,
            std::mem::size_of::<G>(),
        )
    };
    if err.code != 0 {
        panic!("{}", String::from(err));
    }

    ret
}
