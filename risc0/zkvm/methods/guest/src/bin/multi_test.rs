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

//! Runs different tests based on the supplied MultiTestSpec.

#![no_main]
#![no_std]

extern crate alloc;

use alloc::{
    alloc::{alloc_zeroed, Layout},
    format, vec,
};
use core::arch::asm;

use getrandom::getrandom;
use risc0_zkp::core::hash::sha::testutil::test_sha_impl;
use risc0_zkvm::{
    guest::{
        env::{self, FdReader, FdWriter, Read as _, Write as _},
        memory_barrier, sha,
    },
    sha::{Digest, Sha256},
    Assumption, ReceiptClaim,
};
use risc0_zkvm_methods::multi_test::{MultiTestSpec, SYS_MULTI_TEST, SYS_MULTI_TEST_WORDS};
use risc0_zkvm_platform::{
    fileno,
    memory::{self, SYSTEM},
    syscall::{
        bigint, sys_bigint, sys_exit, sys_fork, sys_log, sys_pipe, sys_read, sys_read_words,
        sys_write,
    },
    PAGE_SIZE,
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

fn main() {
    let impl_select: MultiTestSpec = env::read();
    match impl_select {
        MultiTestSpec::DoNothing => {}
        MultiTestSpec::ShaConforms => test_sha_impl::<sha::Impl>(),
        MultiTestSpec::ShaCycleCount => {
            // Time the simulated sha so that it estimates what we'd
            // see when it's a custom circuit.
            let a: &Digest = &Digest::from([1, 2, 3, 4, 5, 6, 7, 8]);

            let count1 = env::cycle_count();
            memory_barrier(&count1);
            let count2 = env::cycle_count();
            memory_barrier(&count2);
            let result = sha::Impl::hash_pair(a, a);
            memory_barrier(&result);
            let count3 = env::cycle_count();
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
        MultiTestSpec::Panic => {
            panic!("MultiTestSpec::Panic invoked");
        }
        MultiTestSpec::Fault => unsafe {
            asm!("sw x0, 1(x0)");
        },
        MultiTestSpec::Halt(exit_code) => {
            env::exit(exit_code);
        }
        MultiTestSpec::PauseResume(exit_code) => {
            env::log("before");
            env::pause(exit_code);
            env::log("after");
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
        MultiTestSpec::SyscallWords => {
            let input: &[u64] = &[0x0102030405060708];

            let host_data = env::send_recv_slice::<u64, u32>(SYS_MULTI_TEST_WORDS, &input);
            assert_eq!(host_data, &[0x05060708, 0x01020304]);
        }
        MultiTestSpec::DoRandom => {
            // Test random number generation in the zkvm
            // Test for a combination of lengths and data alignments to make sure all cases
            // are handled.
            for size in 0..=15 {
                for alignment in 0..=usize::min(3, size) {
                    let rand_buf = &mut vec![0u8; size][alignment..];
                    getrandom(rand_buf).expect("random number generation failed");
                    env::commit_slice(&rand_buf);

                    // If we generated more than 2 bytes, make sure that they are at least not zero.
                    // Only check for len > 2 to avoid false positives.
                    if rand_buf.len() > 2 {
                        assert_ne!(&rand_buf, &vec![0u8; rand_buf.len()].as_slice());
                    }
                }
            }
        }
        MultiTestSpec::SysInput(digest) => {
            assert_eq!(env::input_digest(), digest);
        }
        MultiTestSpec::SysRead {
            mut buf,
            fd,
            pos_and_len,
        } => {
            let mut num_read = alloc::vec::Vec::with_capacity(pos_and_len.len());
            for (pos, len) in pos_and_len {
                let n = unsafe { sys_read(fd, buf.as_mut_ptr().add(pos as usize), len as usize) };
                num_read.push(n);
                assert!(n <= len as usize);
            }
            env::commit(&(buf, num_read));
        }
        MultiTestSpec::SysVerify(pairs) => {
            for (image_id, journal) in pairs.into_iter() {
                env::verify(image_id, &journal).unwrap();
            }
        }
        MultiTestSpec::SysVerifyIntegrity { claim_words } => {
            let claim: ReceiptClaim = risc0_zkvm::serde::from_slice(&claim_words).unwrap();
            // NOTE: This panic string is used in a test.
            env::verify_integrity(&claim).expect("env::verify_integrity returned error");
        }
        MultiTestSpec::SysVerifyAssumption { assumption_words } => {
            let assumption: Assumption = risc0_zkvm::serde::from_slice(&assumption_words).unwrap();
            env::verify_assumption(assumption.claim, assumption.control_root).unwrap();
        }
        MultiTestSpec::Echo { bytes } => {
            env::commit_slice(&bytes);
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
            let mut last_cycles = env::cycle_count();

            // Count all the cycles that have happened so far before we got to this point.
            env::log("Busy loop starting!");
            let mut tot_cycles = last_cycles;

            while tot_cycles < cycles {
                let now_cycles = env::cycle_count();
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
            // SYSTEM memory starts above the guest memory so this is guaranteed
            // to be larger than the available heap:
            let len = memory::SYSTEM.start() as usize;
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
            asm!(
                "mv x6, {}",
                "sw x5, (x6)",
                in(reg) addr,
                out("x5") _,
                out("x6") _
            );
        },
        MultiTestSpec::OutOfBoundsEcall => unsafe {
            asm!(
                "ecall",
                in("x5") 3,
                in("x10") 0x0,
                in("x11") 0x0,
                in("x12") 0x0,
                in("x13") 0x0,
                in("x14") 10000,
            );
        },
        MultiTestSpec::TooManySha => unsafe {
            asm!(
                "ecall",
                in("x5") 3,
                in("x10") 0x400,
                in("x11") 0x400,
                in("x12") 0x400,
                in("x13") 0x400,
                in("x14") 10000,
            );
        },
        MultiTestSpec::SysLogInvalidAddr => unsafe {
            let addr: *const u8 = SYSTEM.start() as _;
            sys_log(addr, 100);
        },
        MultiTestSpec::AlignedAlloc => {
            #[repr(align(1024))]
            struct AlignTest1 {
                pub _test: u32,
            }

            impl AlignTest1 {
                pub fn new(_test: u32) -> Self {
                    AlignTest1 { _test }
                }
            }

            let a = &AlignTest1::new(54) as *const _;
            let b = &AlignTest1::new(60) as *const _;
            assert_eq!(PAGE_SIZE, b as usize - a as usize);
        }
        MultiTestSpec::AllocZeroed => {
            // Bump allocator was modified to not manually zero memory in the zkVM. Simple test to
            // ensure that zkVM memory is zeroed in initialization.
            let array: &[u32; 512] = unsafe {
                // Allocate some arbitrary amount of bytes
                let layout = Layout::new::<[u32; 512]>();
                let ptr = alloc_zeroed(layout);

                &*(ptr as *const [u32; 512])
            };
            for value in array {
                assert_eq!(*value, 0);
            }
        }
        MultiTestSpec::SysFork => {
            const MSG: &[u8] = b"hello";
            let mut pipe = [0u32; 2];
            unsafe { sys_pipe(pipe.as_mut_ptr()) };
            let pid = sys_fork();
            if pid == 0 {
                env::log("child");
                let mut writer = FdWriter::new(pipe[1], |_| {});
                writer.write_slice(MSG);
                sys_exit(0);
            } else {
                env::log("parent");
                let mut reader = FdReader::new(pipe[0]);
                let mut buf: [u8; MSG.len()] = [0; MSG.len()];
                reader.read_slice(&mut buf);
                assert_eq!(buf, MSG);
            }
        }
        MultiTestSpec::SysForkFork => {
            let pid = sys_fork();
            if pid == 0 {
                sys_fork();
            }
        }
        MultiTestSpec::SysForkJournalPanic => {
            let pid = sys_fork();
            if pid == 0 {
                env::commit_slice(b"should panic");
            }
        }
    }
}
