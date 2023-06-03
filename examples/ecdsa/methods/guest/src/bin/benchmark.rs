// Copyright 2023 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

use std::{hint::black_box, ops::Add};

use hex_literal::hex;
use k256::{
    elliptic_curve::{
        bigint::{Encoding, U256},
        ops::{Invert, LinearCombination, Reduce},
    },
    FieldElement, ProjectivePoint, Scalar,
};
use risc0_zkvm::guest::env;

fn bench(name: &str, func: impl Fn()) {
    // Run the inner function twice, only logging the cycles in the second run, in
    // order to ensure the code and memory has been paged-in.
    bench_inner(name, &func, true);
    bench_inner(name, &func, false);
}

#[inline(never)]
fn bench_inner(name: &str, func: impl FnOnce(), silent: bool) {
    black_box({
        let start = env::get_cycle_count();

        black_box(func());

        let end = env::get_cycle_count();
        if !silent {
            println!("{}: {} cycles", name, end - start)
        };
    })
}

fn benchmark_field() {
    println!("Field operations:");
    let x = black_box(
        FieldElement::from_bytes(
            &hex!("EC08EAC2CBCEFE58E61038DCA45BA2B4A56BDF05A3595EBEE1BCFC488889C1CF").into(),
        )
        .unwrap(),
    );
    let y = black_box(
        FieldElement::from_bytes(
            &hex!("9FC3E90D2FAD03C8669F437A26374FA694CA76A7913C5E016322EBAA5C7616C5").into(),
        )
        .unwrap(),
    );

    bench("add", || {
        black_box(x.add(&y));
    });
    bench("mul", || {
        black_box(x.mul(&y));
    });
    bench("mul_single", || {
        black_box(x.mul_single(42));
    });
    bench("square", || {
        black_box(x.square());
    });
    bench("negate", || {
        black_box(x.negate(0));
    });
    bench("invert", || {
        black_box(x.invert().unwrap());
    });
}

fn benchmark_scalar() {
    println!("");
    println!("Scalar operations:");
    let x = black_box(Scalar::reduce(U256::from_be_bytes(hex!(
        "2A3F714FCDDEA4984F228C4D1DBD41A79B470B1546C68F6BB268A04AA0394BAC"
    ))));
    let y = black_box(Scalar::reduce(U256::from_be_bytes(hex!(
        "98973615F3B819529D885BBED9A69BC66A678D00289A8B1F3A0FF19801C10CDD"
    ))));

    bench("add", || {
        black_box(x.add(&y));
    });
    bench("mul", || {
        black_box(x.mul(&y));
    });
    bench("square", || {
        black_box(x.square());
    });
    bench("negate", || {
        black_box(x.negate());
    });
    bench("invert", || {
        black_box(x.invert().unwrap());
    });
    bench("invert_vartime", || {
        black_box(x.invert_vartime().unwrap());
    });
}

fn benchmark_group() {
    println!("");
    println!("Group operations:");
    let x = black_box(Scalar::reduce(U256::from_be_bytes(hex!(
        "2a3f714fcddea4984f228c4d1dbd41a79b470b1546c68f6bb268a04aa0394bac"
    ))));
    let y = black_box(Scalar::reduce(U256::from_be_bytes(hex!(
        "2a3f714fcddea4984f228c4d1dbd41a79b470b1546c68f6bb268a04aa0394bac"
    ))));

    bench("lincomb", || {
        black_box(
            ProjectivePoint::lincomb(
                &ProjectivePoint::GENERATOR,
                &x,
                &ProjectivePoint::GENERATOR,
                &y,
            )
            .to_affine(),
        );
    });
}

fn main() {
    benchmark_field();
    benchmark_scalar();
    benchmark_group();
}
