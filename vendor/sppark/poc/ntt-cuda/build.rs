// Copyright Supranational LLC
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

use std::env;

fn feature_check() {
    let fr_s = [
        "bls12_377",
        "bls12_381",
        "pallas",
        "vesta",
        "bn254",
        "gl64",
        "bb31",
    ];
    let fr_s_as_features: Vec<String> = (0..fr_s.len())
        .map(|i| format!("CARGO_FEATURE_{}", fr_s[i].to_uppercase()))
        .collect();

    let mut fr_counter = 0;
    for fr_feature in fr_s_as_features.iter() {
        fr_counter += env::var(&fr_feature).is_ok() as i32;
    }

    match fr_counter {
        0 => panic!("Can't run without a field being specified,\nplease select one with --features=<field>. Available options are\n{:#?}\n", fr_s),
        2.. => panic!("Multiple fields are not supported, please select only one."),
        _ => (),
    };
}

fn main() {
    if cfg!(target_os = "windows") && !cfg!(target_env = "msvc") {
        panic!("unsupported compiler");
    }

    feature_check();

    let mut fr = "";
    if cfg!(feature = "bls12_377") {
        fr = "FEATURE_BLS12_377";
    } else if cfg!(feature = "bls12_381") {
        fr = "FEATURE_BLS12_381";
    } else if cfg!(feature = "pallas") {
        fr = "FEATURE_PALLAS";
    } else if cfg!(feature = "vesta") {
        fr = "FEATURE_VESTA";
    } else if cfg!(feature = "bn254") {
        fr = "FEATURE_BN254"
    } else if cfg!(feature = "gl64") {
        fr = "FEATURE_GOLDILOCKS";
    } else if cfg!(feature = "bb31") {
        fr = "FEATURE_BABY_BEAR";
    }

    println!("cargo:rerun-if-changed=cuda");
    println!("cargo:rerun-if-env-changed=CXXFLAGS");

    let mut ccmd : cc::Build = sppark::build::ccmd();
    ccmd.define(fr, None);
    if cfg!(feature = "gl64") {
        ccmd.define("GL64_NO_REDUCTION_KLUDGE", None);
    }
    ccmd.file("cuda/ntt_api.cu").compile("sppark_ntt");
}
