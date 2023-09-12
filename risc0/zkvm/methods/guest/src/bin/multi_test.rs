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

extern crate alloc;

use alloc::{format, vec};
use core::arch::asm;

use getrandom::getrandom;
use risc0_zkp::core::hash::sha::testutil::test_sha_impl;
use risc0_zkvm::{
    guest::{env, memory_barrier, sha},
    sha::{Digest, Sha256},
};
use risc0_zkvm_methods::multi_test::{MultiTestSpec, SYS_MULTI_TEST};
use risc0_zkvm_platform::{
    fileno, memory,
    syscall::{bigint, sys_bigint, sys_read, sys_read_words, sys_write},
};

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
    let impl_select: MultiTestSpec = env::read();
    match impl_select {
        MultiTestSpec::DoNothing => {}
        MultiTestSpec::ShaConforms => test_sha_impl::<sha::Impl>(),
        MultiTestSpec::ShaCycleCount => {
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
        MultiTestSpec::EventTrace => unsafe {
            // Execute some instructions with distinctive arguments
            // that are easy to find in the event trace.
            asm!(r"
      // Dry run first to make sure all regions are paged in
      li x5, 1336
      li x6, 0x08000000
      sw x5, 548(x6)
      // Now, run what we're actually looking for.
      li x5, 1337
      li x6, 0x08000000
      sw x5, 548(x6)
", out("x5") _, out("x6") _);
        },
        MultiTestSpec::Profiler => {
            // Call an external function to make sure it's detected during profiling.
            profile_test_func1()
        }
        MultiTestSpec::Fail => {
            panic!("MultiTestSpec::Fail invoked");
        }
        MultiTestSpec::ReadWriteMem { values } => {
            for (addr, value) in values.into_iter() {
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
        MultiTestSpec::ShaDigest { data } => {
            let digest = sha::Impl::hash_bytes(&data);
            env::commit(&digest);
        }
        MultiTestSpec::ShaDigestIter { data, num_iter } => {
            let mut hash = &data[..];
            for _ in 0..num_iter {
                hash = sha::Impl::hash_bytes(hash).as_bytes();
            }
            env::commit(&Digest::try_from(hash).unwrap())
        }
        MultiTestSpec::Syscall { count } => {
            let mut input: &[u8] = &[];
            let mut input_len: usize = 0;

            for _ in 0..count {
                let host_data = env::send_recv_slice::<u8, u8>(SYS_MULTI_TEST, &input[..input_len]);

                input = bytemuck::cast_slice(host_data);
                input_len = input.len();
            }
        }
        MultiTestSpec::DoRandom => {
            // Test random number generation in the zkvm
            let mut rand_buf = [0u8; 7];
            getrandom(rand_buf.as_mut_slice()).expect("random number generation failed");
            env::commit_slice(&rand_buf);
            assert_ne!(rand_buf, vec![0u8; rand_buf.len()].as_slice());
        }
        MultiTestSpec::SysRead {
            mut buf,
            fd,
            pos_and_len,
        } => {
            for (pos, len) in pos_and_len {
                let num_read =
                    unsafe { sys_read(fd, buf.as_mut_ptr().add(pos as usize), len as usize) };
                assert_eq!(num_read, len as usize);
            }
            env::commit(&buf);
        }
        MultiTestSpec::PauseContinue => {
            env::log("before");
            env::pause();
            env::log("after");
        }
        MultiTestSpec::EchoStdout { nbytes, fd } => {
            // Unaligned buffer size to exercise things a little bit.
            let mut buf = vec![0u8; nbytes as usize];
            loop {
                let nread = unsafe { sys_read(fd, buf.as_mut_ptr(), buf.len()) };
                if nread == 0 {
                    break;
                }
                unsafe { sys_write(fileno::STDOUT, buf.as_ptr(), nread) }
            }
        }
        MultiTestSpec::EchoWords { fd, nwords } => {
            let nwords = nwords as usize;
            let mut buf = vec![0u32; nwords];
            unsafe { sys_read_words(fd, buf.as_mut_ptr(), nwords) };
            env::commit_slice(&buf);
        }
        MultiTestSpec::BusyLoop { cycles } => {
            let mut last_cycles = env::get_cycle_count();

            // Count all the cycles that have happened so far before we got to this point.
            env::log("Busy loop starting!");
            let mut tot_cycles = last_cycles;

            while tot_cycles < cycles as usize {
                let now_cycles = env::get_cycle_count();
                if now_cycles <= last_cycles {
                    // Cycle count may have reset or wrapped around.
                    // Since we don't know which, just start counting
                    // from zero.
                    tot_cycles += now_cycles;
                } else {
                    tot_cycles += now_cycles - last_cycles;
                }
                last_cycles = now_cycles;
            }
            env::log("Busy loop complete");
        }
        MultiTestSpec::BigInt { x, y, modulus } => {
            let mut result = [0u32; bigint::WIDTH_WORDS];
            unsafe {
                sys_bigint(&mut result, bigint::OP_MULTIPLY, &x, &y, &modulus);
            }
            env::commit_slice(&result);
        }
        MultiTestSpec::LibM => {
            use core::hint::black_box;
            let f = black_box(1.0_f32);
            black_box(f.min(1.0));
        }
        MultiTestSpec::Oom => {
            use core::hint::black_box;
            // (STACK_TOP - RESERVED_STACK) is the top address the
            // heap could ever grow to.  The heap starts after program
            // data, so this is guaranteed to be larger than the
            // available heap:
            let len = (memory::STACK_TOP - memory::RESERVED_STACK) as usize;
            let _data = black_box(vec![0_u8; len]);
        }
        MultiTestSpec::RsaCompat => {
            // This test comes from: https://github.com/RustCrypto/RSA/blob/master/tests/pkcs1v15.rs
            use risc0_zkvm::sha::rust_crypto::Sha256;
            use rsa::{
                pkcs1v15::SigningKey, pkcs8::DecodePrivateKey, signature::Signer, RsaPrivateKey,
            };

            let pem = include_str!("rsa2048-priv.pem");
            let private_key = RsaPrivateKey::from_pkcs8_pem(pem).unwrap();
            let signing_key = SigningKey::<Sha256>::new(private_key);

            let signature = signing_key.sign(b"rsa4096");
            let expected = "029E365B60971D5A499FF5E1C288B954D3A5DCF52482CEE46DB90DC860B725A8D6CA031146FA156E9F17579BE6122FFB11DAC35E59B2193D75F7B31CE1442DDE7F4FF7885AD5D6080266E9A33BB4CEC93FCC2B6B885457A0ABF19E2DAA00876F694B37F535F119925CCCF9A17B90AE6CF39F07D7FEFBEECDF1B344C14B728196DDD154230BADDEDA5A7EFF373F6CD3EF6D41789572A7A068E3A252D3B7D5D706C6170D8CFDB48C8E738A4B3BFEA3E15716805E376EBD99EA09C6E82F3CFA13CEB23CD289E8F95C27F489ADC05AAACE8A9276EE7CED3B7A5C7264F0D34FF18CEDC3E91D667FCF9992A8CFDE8562F65FDDE1E06595C27E0F82063839A358C927B2";
            assert_eq!(format!("{}", signature), expected);
        }
        MultiTestSpec::OutOfBounds => unsafe {
            let addr: u32 = env::read();
            // Access memory outside of allowed boundaries. This is intended to cause a
            // fault
            asm!( "mv x6, {}", "sw x5, (x6)" , in(reg) addr, out("x5") _, out("x6") _);
        },
    }
}
