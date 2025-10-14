// Copyright Supranational LLC
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

use criterion::{criterion_group, criterion_main, Criterion};

#[cfg(feature = "bls12_377")]
use ark_bls12_377::{G1Affine, G2Affine};
#[cfg(feature = "bls12_381")]
use ark_bls12_381::{G1Affine, G2Affine};
#[cfg(feature = "bn254")]
use ark_bn254::G1Affine;
use ark_ff::BigInteger256;

use std::str::FromStr;

use msm_cuda::*;

fn criterion_benchmark(c: &mut Criterion) {
    let bench_npow = std::env::var("BENCH_NPOW").unwrap_or("23".to_string());
    let npoints_npow = i32::from_str(&bench_npow).unwrap();

    let (points, scalars) =
        util::generate_points_scalars::<G1Affine>(1usize << npoints_npow);

    let mut group = c.benchmark_group("CUDA");
    group.sample_size(20);

    let name = format!("2**{}", npoints_npow);
    group.bench_function(name, |b| {
        b.iter(|| {
            let _ = multi_scalar_mult_arkworks(&points.as_slice(), unsafe {
                std::mem::transmute::<&[_], &[BigInteger256]>(
                    scalars.as_slice(),
                )
            });
        })
    });

    group.finish();
}

#[cfg(not(any(feature = "bls12_381", feature = "bls12_377")))]
criterion_group!(benches, criterion_benchmark);

#[cfg(any(feature = "bls12_381", feature = "bls12_377"))]
fn criterion_benchmark_fp2(c: &mut Criterion) {
    let bench_npow = std::env::var("BENCH_NPOW").unwrap_or("23".to_string());
    let npoints_npow = i32::from_str(&bench_npow).unwrap();

    let (points, scalars) =
        util::generate_points_scalars::<G2Affine>(1usize << npoints_npow);

    let mut group = c.benchmark_group("CUDA");
    group.sample_size(10);

    let name = format!("2**{}", npoints_npow);
    group.bench_function(name, |b| {
        b.iter(|| {
            let _ = multi_scalar_mult_fp2_arkworks(&points.as_slice(), unsafe {
                std::mem::transmute::<&[_], &[BigInteger256]>(
                    scalars.as_slice(),
                )
            });
        })
    });

    group.finish();
}

#[cfg(any(feature = "bls12_381", feature = "bls12_377"))]
criterion_group!(benches, criterion_benchmark, criterion_benchmark_fp2);

criterion_main!(benches);
