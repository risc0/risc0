// Copyright 2024 RISC Zero, Inc.
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
use num_bigint::BigUint;
use num_traits::Num as _;
use risc0_circuit_bigint::{ec, generate_proof_input, rsa, BigIntProgram};

criterion_group!(benches, bench_rsa);
criterion_main!(benches);

fn from_hex(s: &str) -> BigUint {
    BigUint::from_str_radix(s, 16).expect("Unable to parse hex value")
}

fn do_rsa(c: &mut Criterion, prog: BigIntProgram) {
    // these values aren't meant to be accurate, just valid to run the benchmark
    let n = from_hex("9c98f9aacfc0b73c916a824db9afe39673dcb56c42dffe9de5b86d5748aca4d5");
    let s = from_hex("de67116c809a5cc876cebb5e8c72d998f983a4d61b499dd9ae23b789a7183677");
    let m = from_hex("1fb897fac8aa8870b936631d3af1a17930c8af0ca4376b3056677ded52adf5aa");
    let claim = rsa::claim(&prog, n, s, m);
    c.bench_function(prog.name, |b| {
        b.iter(|| {
            generate_proof_input(&[&claim], &prog).unwrap();
        })
    });
}

fn bench_rsa(c: &mut Criterion) {
    do_rsa(c, rsa::RSA_256_X1);
    do_rsa(c, rsa::RSA_256_X2);
    do_rsa(c, rsa::RSA_3072_X15);
}
