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

use criterion::{criterion_group, criterion_main, BenchmarkId, Criterion};
use rand::thread_rng;
use risc0_core::field::{baby_bear::BabyBearElem, Elem};
use risc0_zkp::core::ntt::interpolate_ntt;

pub fn ntt(c: &mut Criterion) {
    let mut group = c.benchmark_group("interpolate_ntt");
    for n in [10, 15, 20].iter() {
        group.bench_function(BenchmarkId::from_parameter(n), |b| {
            let size = 1 << n;
            let mut rng = thread_rng();
            let mut buf = vec![BabyBearElem::random(&mut rng); size];
            b.iter(|| interpolate_ntt::<BabyBearElem, BabyBearElem>(&mut buf));
        });
    }
}

criterion_group!(benches, ntt);
criterion_main!(benches);
