// Copyright 2022 Risc0, Inc.
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

//! Runs different tests based on the first u32 provided.

#![no_main]
#![no_std]
#![feature(alloc_error_handler)]

use core::arch::asm;

#[cfg(feature = "pure-prove")]
use risc0_zkp::core::sha::{Digest, Sha};
use risc0_zkvm_guest::{env, sha};
use risc0_zkvm_methods::multi_test::MultiTestSpec;

risc0_zkvm_guest::entry!(main);
risc0_zkvm_guest::standalone_handlers!();

#[inline(never)]
#[no_mangle]
fn profile_test_func1() {
    profile_test_func2()
}

#[inline(always)]
#[no_mangle]
fn profile_test_func2() {
    unsafe { asm!("nop") }
}

pub fn main() {
    let impl_select: MultiTestSpec = env::read();
    let data: &[u8] = env::read();
    let digest = sha::digest_u8_slice(data);
    env::commit(&digest);

    match impl_select {
        MultiTestSpec::ShaConforms => {
            risc0_zkp::core::sha::testutil::test_sha_impl(&risc0_zkvm_guest::sha::Impl {})
        }
        #[cfg(feature = "pure-prove")]
        MultiTestSpec::ShaInsecureConforms => {
            risc0_zkp::core::sha::testutil::test_sha_impl(&risc0_zkvm_guest::sha_insecure::Impl {})
        }
        #[cfg(feature = "pure-prove")]
        MultiTestSpec::ShaCycleCount => {
            // Time the simulated sha so that it estimates what we'd
            // see when it's a custom circuit.
            let a: &Digest = &Digest::new([1, 2, 3, 4, 5, 6, 7, 8]);

            let count1 = env::get_cycle_count();
            risc0_zkvm_guest::memory_barrier(&count1);
            let count2 = env::get_cycle_count();
            risc0_zkvm_guest::memory_barrier(&count2);
            let result = risc0_zkvm_guest::sha_insecure::Impl {}.hash_pair(a, a);
            risc0_zkvm_guest::memory_barrier(&result);
            let count3 = env::get_cycle_count();
            risc0_zkvm_guest::memory_barrier(&count3);

            let overhead = count2 - count1;
            let total = (count3 - count2) - overhead;

            // We expect our acceleration circuit to use 72 cycles, so make sure that
            // our simulation doesn't run faster.
            assert!(total >= 72, "total: {total}");
        }
        #[cfg(feature = "pure-prove")]
        MultiTestSpec::EventTrace => unsafe {
            let mut _x: u32;
            // Exeute some instructions with distinctive arguments
            // that are easy to find in the event trace.
            asm!(r"
      li x5, 1337
      sw x5, 548(zero)
", out("x5") _x,);
        },
        #[cfg(feature = "pure-prove")]
        MultiTestSpec::Profiler => {
            // Call an external function to make sure it's detected during profiling.
            profile_test_func1()
        }
        #[cfg(not(feature = "pure-prove"))]
        _ => unimplemented!(),
    }
}
