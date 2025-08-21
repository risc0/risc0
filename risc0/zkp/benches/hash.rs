// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use criterion::{Criterion, criterion_group, criterion_main};
use risc0_core::field::{Elem, baby_bear::BabyBearElem};
use risc0_zkp::core::hash::poseidon2::{CELLS as POSEIDON2_CELLS, poseidon2_mix};

fn benchmark_poseidon2_mix(c: &mut Criterion) {
    let mut rng = rand::rng();
    let mut cells = [BabyBearElem::random(&mut rng); POSEIDON2_CELLS];
    c.bench_function("poseidon2_mix", |b| b.iter(|| poseidon2_mix(&mut cells)));
}

criterion_group!(benches, benchmark_poseidon2_mix);
criterion_main!(benches);
