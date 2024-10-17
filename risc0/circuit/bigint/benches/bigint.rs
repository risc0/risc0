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

criterion_group!(benches, bench_rsa, bench_ec_mul);
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

fn bench_ec_mul(c: &mut Criterion) {
    let prog: BigIntProgram = ec::EC_MUL_SECP256K1;
    let [x, y, s, u, v] = [
        from_hex("79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798"),
        from_hex("483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8"),
        from_hex("2f"), // 47
        from_hex("77f230936ee88cbbd73df930d64702ef881d811e0e1498e2f1c13eb1fc345d74"),
        from_hex("958ef42a7886b6400a08266e9ba1b37896c95330d97077cbbe8eb3c7671c60d6"),
    ];
    let claim = ec::mul_claim(&prog, x, y, s, u, v);
    c.bench_function("ec_mul_secp256k1", |b| {
        b.iter(|| {
            generate_proof_input(&[&claim], &prog).unwrap();
        })
    });
}
