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
use risc0_circuit_bigint_test_methods::RSA_ELF;
use risc0_zkvm::{default_prover, ExecutorEnv};

fn main() {
    // Note: This example is for demonstration purposes and is not for production use
    // If you want something with production features, look into our fork of the RustCrypto RSA repo
    //
    // This example computes an RSA exponentiation, i.e., computes m^65537 (mod n). It does not
    // require you to know the answer ahead of time -- it will compute it and commit it
    tracing_subscriber::fmt()
        .with_env_filter(tracing_subscriber::EnvFilter::from_default_env())
        .init();

    register_zkrs();

    // We compute the modpow of `base` to 65537 mod `modulus`, commit it to the journal, and compare to `expected`
    let modulus = from_hex("9c98f9aacfc0b73c916a824db9afe39673dcb56c42dffe9de5b86d5748aca4d5");
    let base = from_hex("de67116c809a5cc876cebb5e8c72d998f983a4d61b499dd9ae23b789a7183677");
    let inputs = vec![[modulus, base]];

    let env = ExecutorEnv::builder()
        .write(&inputs)
        .unwrap()
        .build()
        .unwrap();

    let prover = default_prover();
    let prove_info = prover.prove(env, RSA_ELF).unwrap();
    assert_eq!(prove_info.stats.segments, 1);

    let result: Vec<BigUint> = prove_info.receipt.journal.decode().expect("TODO");
    let expected = from_hex("1fb897fac8aa8870b936631d3af1a17930c8af0ca4376b3056677ded52adf5aa");
    assert_eq!(result[0], expected);
    println!("RSA example produces expected result");
}

fn from_hex(s: &str) -> BigUint {
    BigUint::from_str_radix(s, 16).expect("Unable to parse hex value")
}
