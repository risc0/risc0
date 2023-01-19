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

//! Runs different tests based on the supplied MultiTestSpec.

#![no_main]
#![no_std]

use core::arch::asm;

use risc0_zeroio::deserialize::Deserialize;
use risc0_zkp::core::sha::{testutil::test_sha_impl, Digest, Sha256};
use risc0_zkvm::guest::{env, memory_barrier, sha};
use risc0_zkvm_methods::multi_test::{MultiTestSpec, MultiTestSpecRef};
use risc0_zkvm_platform::io::SENDRECV_CHANNEL_INITIAL_INPUT;

risc0_zkvm::entry!(main);

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
    let initial_input = env::send_recv(SENDRECV_CHANNEL_INITIAL_INPUT, &[]);
    let impl_select = MultiTestSpec::deserialize_from(bytemuck::cast_slice(initial_input));
    match impl_select {
        MultiTestSpecRef::DoNothing(_) => {}
        MultiTestSpecRef::ShaConforms(_) => test_sha_impl::<sha::Impl>(),
        MultiTestSpecRef::ShaCycleCount(_) => {
            // Time the simulated sha so that it estimates what we'd
            // see when it's a custom circuit.
            let a: &Digest = &Digest::from([1, 2, 3, 4, 5, 6, 7, 8]);

            let count1 = env::get_cycle_count();
            memory_barrier(&count1);
            let count2 = env::get_cycle_count();
            memory_barrier(&count2);
            let result = sha::Impl::hash_pair(a, a);
            memory_barrier(&result);
            let count3 = env::get_cycle_count();
            memory_barrier(&count3);

            let overhead = count2 - count1;
            let total = (count3 - count2) - overhead;

            // We expect our acceleration circuit to use 72 cycles, so make sure that
            // our simulation doesn't run faster.
            assert!(total >= 72, "total: {total}");
        }
        MultiTestSpecRef::EventTrace(_) => unsafe {
            // Execute some instructions with distinctive arguments
            // that are easy to find in the event trace.
            asm!(r"
      li x5, 1337
      li x6, 0x08000000
      sw x5, 548(x6)
", out("x5") _, out("x6") _);
        },
        MultiTestSpecRef::Profiler(_) => {
            // Call an external function to make sure it's detected during profiling.
            profile_test_func1()
        }
        MultiTestSpecRef::Fail(_) => {
            panic!("MultiTestSpec::Fail invoked");
        }
        MultiTestSpecRef::ReadWriteMem(values) => {
            for (addr, value) in values.values().iter() {
                if value != 0 {
                    let ptr = addr as *mut u32;
                    unsafe { ptr.write_volatile(value) };
                } else {
                    let ptr = addr as *const u32;
                    let value = unsafe { ptr.read_volatile() };
                    env::write(&value);
                }
            }
        }
        MultiTestSpecRef::ShaDigest(data) => {
            let digest = sha::Impl::hash_bytes(data.data());
            env::commit(&digest);
        }
        MultiTestSpecRef::SendRecv(sendrecv) => {
            let mut input: &[u8] = &[];
            let mut input_len: usize = 0;

            for _ in 0..sendrecv.count() {
                let host_data = env::send_recv(sendrecv.channel_id(), &input[..input_len]);

                input = bytemuck::cast_slice(host_data);
                input_len = input.len();
            }
        }
    }
}
