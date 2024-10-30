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
use risc0_zkvm::{ExecutorEnv, ExecutorImpl};
use risc0_zkvm_platform::syscall::sys_rsa;

fn main() {
    tracing_subscriber::fmt()
        .with_env_filter(tracing_subscriber::EnvFilter::from_default_env())
        .init();

    register_zkrs();

    // TODO: This whole thing is a bit hacky, clean up
    // Parameters for a message `m` with signature `s` under the RSA public key modulus `n`.
    let n = from_hex("9c98f9aacfc0b73c916a824db9afe39673dcb56c42dffe9de5b86d5748aca4d5");
    let s = from_hex("de67116c809a5cc876cebb5e8c72d998f983a4d61b499dd9ae23b789a7183677");
    let n_claim = n.clone();
    let s_claim = s.clone();
    // let m = from_hex("1fb897fac8aa8870b936631d3af1a17930c8af0ca4376b3056677ded52adf5aa");
    // println!("The bitwidth of n is {}", n.bits());
    let mut n = n.to_u32_digits();  // Ugh `mut` what a hack TODO
    n.resize(96, 0); // TODO: need more care
    let n: [u32; 96] = n.try_into().expect("modulus should fit in 96 32-bit words");
    let mut s = s.to_u32_digits();  // Ugh `mut` what a hack TODO
    s.resize(96, 0); // TODO: need more care
    let s: [u32; 96] = s.try_into().expect("base should fit in 96 32-bit words");
    // TODO: Feels a bit hacky
    const fn zero() -> u32 {
        0
    }
    let mut m = [zero(); 96];  // TODO: Feels a bit hacky
    unsafe {
        sys_rsa(&mut m, &s, &n);  // TODO: Actually manage the 3 inputs (first is buffer for output) and call
    }
    // let m_claim = BigUint::from_bytes_le(m.map(|elem| elem.to_le_bytes()).flatten());
    // TODO: This code should be replaced with the `flatten` code above once `flatten` is stable
    let m_words = m.map(|elem| elem.to_le_bytes());
    let mut m_claim = Vec::<u8>::new();  // TODO: Clean up style
    for word in m_words {
        for byte in word {
            m_claim.push(byte);
        }
    }
    let m_claim = BigUint::from_bytes_le(&m_claim);
    let claims = vec![[n_claim, s_claim, m_claim]];

    let env = ExecutorEnv::builder()
        .write(&claims)
        .unwrap()
        .build()
        .unwrap();

    let session = ExecutorImpl::from_elf(env, RSA_ELF).unwrap().run().unwrap();
    assert_eq!(session.segments.len(), 1);
}

fn from_hex(s: &str) -> BigUint {
    BigUint::from_str_radix(s, 16).expect("Unable to parse hex value")
}
