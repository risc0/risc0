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

use num_bigint::BigUint;
use num_traits::Num as _;
use risc0_circuit_bigint::zkr::register_zkrs;
use risc0_circuit_bigint_test_methods::EC_MUL_ELF;
use risc0_zkvm::{ExecutorEnv, ExecutorImpl};

fn main() {
    tracing_subscriber::fmt()
        .with_env_filter(tracing_subscriber::EnvFilter::from_default_env())
        .init();

    register_zkrs();

    // Parameters for `s * (x, y) = (u, v) on secp256k1`
    let x = from_hex("79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798");
    let y = from_hex("483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8");
    let s = from_hex("2f");
    let u = from_hex("77f230936ee88cbbd73df930d64702ef881d811e0e1498e2f1c13eb1fc345d74");
    let v = from_hex("958ef42a7886b6400a08266e9ba1b37896c95330d97077cbbe8eb3c7671c60d6");
    let claims = vec![[x, y, s, u, v]];

    let env = ExecutorEnv::builder()
        .write(&claims)
        .unwrap()
        .build()
        .unwrap();

    let session = ExecutorImpl::from_elf(env, EC_MUL_ELF)
        .unwrap()
        .run()
        .unwrap();
    assert_eq!(session.segments.len(), 1);
}

fn from_hex(s: &str) -> BigUint {
    BigUint::from_str_radix(s, 16).expect("Unable to parse hex value")
}
