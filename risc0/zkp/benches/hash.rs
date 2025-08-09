// Copyright 2025 RISC Zero, Inc.
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

use criterion::{criterion_group, criterion_main, Criterion};
use rand::{Rng, SeedableRng};
use rand::rngs::{OsRng, SmallRng};
use risc0_core::field::{baby_bear::BabyBearElem, Elem};
use risc0_zkp::core::hash::poseidon2::{poseidon2_mix, CELLS as POSEIDON2_CELLS};

fn benchmark_poseidon2_mix(c: &mut Criterion) {
    let mut rng = SmallRng::from_rng(OsRng).unwrap();

    let mut cells = [BabyBearElem::ZERO; POSEIDON2_CELLS];
    for cell in cells.iter_mut() {
        *cell = BabyBearElem::random(&mut rng);
    }

    c.bench_function("poseidon2_mix", |b| b.iter(|| poseidon2_mix(&mut cells)));
}

criterion_group!(benches, benchmark_poseidon2_mix);
criterion_main!(benches);
