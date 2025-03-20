// Copyright 2025 RISC Zero, Inc.
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

#[path = "multi_test/profiler.rs"]
mod profiler;

extern crate alloc;

use alloc::{
    alloc::{alloc_zeroed, Layout},
    format, vec,
};
use core::arch::asm;

use getrandom::getrandom;
use risc0_circuit_keccak::{KeccakState, KECCAK_DEFAULT_PO2};
use risc0_zkp::{core::hash::sha::testutil::test_sha_impl, digest};
use risc0_zkvm::{
    guest::{
        env::{self, testing::sha_single_keccak, FdReader, FdWriter, Read as _, Write as _},
        memory_barrier, sha,
    },
    sha::{Digest, Sha256, SHA256_INIT},
    Assumption, ReceiptClaim, GUEST_MAX_MEM,
};
use risc0_zkvm_methods::multi_test::{MultiTestSpec, SYS_MULTI_TEST, SYS_MULTI_TEST_WORDS};
use risc0_zkvm_platform::{
    fileno,
    syscall::{
        bigint, ecall, sys_bigint, sys_exit, sys_fork, sys_keccak, sys_log, sys_pipe,
        sys_prove_zkr, sys_read, sys_read_words, sys_write, DIGEST_WORDS,
    },
    PAGE_SIZE,
};

risc0_zkvm::entry!(main);

const KECCAK_UPDATE: KeccakState = [
    0xF1258F7940E1DDE7,
    0x84D5CCF933C0478A,
    0xD598261EA65AA9EE,
    0xBD1547306F80494D,
    0x8B284E056253D057,
    0xFF97A42D7F8E6FD4,
    0x90FEE5A0A44647C4,
    0x8C5BDA0CD6192E76,
    0xAD30A6F71B19059C,
    0x30935AB7D08FFC64,
    0xEB5AA93F2317D635,
    0xA9A6E6260D712103,
    0x81A57C16DBCF555F,
    0x43B831CD0347C826,
    0x01F22F1A11A5569F,
    0x05E5635A21D9AE61,
    0x64BEFEF28CC970F2,
    0x613670957BC46611,
    0xB87C5A554FD00ECB,
    0x8C3EE88A1CCF32C8,
    0x940C7922AE3A2614,
    0x1841F924A2C509E4,
    0x16F53526E70465C2,
    0x75F644E97F30A13B,
    0xEAF1FF7B5CECA249,
];

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
            profiler::profile_test_func1()
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
        MultiTestSpec::BigInt {
            count,
            x,
            y,
            modulus,
        } => {
            let mut result = [0u32; bigint::WIDTH_WORDS];
            for _ in 0..count {
                unsafe { sys_bigint(&mut result, bigint::OP_MULTIPLY, &x, &y, &modulus) };
            }
            env::commit_slice(&result);
        }
        MultiTestSpec::BigIntRaw {
            result,
            x,
            y,
            modulus,
        } => unsafe {
            asm!(
                "ecall",
                in("t0") ecall::BIGINT,
                in("a0") result,
                in("a1") bigint::OP_MULTIPLY,
                in("a2") x,
                in("a3") y,
                in("a4") modulus,
            );
        },
        MultiTestSpec::LibM => {
            use core::hint::black_box;
            let f = black_box(1.0_f32);
            black_box(f.min(1.0));
        }
        MultiTestSpec::Oom => {
            use core::hint::black_box;
            // GUEST_MAX_MEM is the max amount of memory so this will be as large as the heap could get.
            // setting this as the length results in a capacity error so allocate two of these instead
            let len = GUEST_MAX_MEM / 2;
            let _data1 = black_box(vec![0_u8; len]);
            let _data2 = black_box(vec![0_u8; len]);
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
        #[allow(asm_sub_register)]
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
                in("t0") ecall::SHA,
                in("a0") 0x0,
                in("a1") 0x0,
                in("a2") 0x0,
                in("a3") 0x0,
                in("a4") 10000,
            );
        },
        MultiTestSpec::TooManySha => unsafe {
            let out_state = [0u32; DIGEST_WORDS];
            let in_state = [0u32; DIGEST_WORDS];
            let block = [0u32; 2 * DIGEST_WORDS];
            asm!(
                "ecall",
                in("t0") ecall::SHA,
                in("a0") out_state.as_ptr(),
                in("a1") in_state.as_ptr(),
                in("a2") block.as_ptr(),
                in("a3") block.as_ptr().add(DIGEST_WORDS),
                in("a4") 10000,
            );
        },
        MultiTestSpec::SysLogInvalidAddr => unsafe {
            let addr: *const u8 = GUEST_MAX_MEM as _;
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
        MultiTestSpec::RunUnconstrained {
            unconstrained,
            cycles,
        } => {
            // Calculate cycles left to the target cycle count, since
            // we've used a bunch paging in the program and reading
            // input.
            let cycles_left: u32 = (cycles - env::cycle_count()).try_into().unwrap();
            env::log("Starting running unconstrained");

            // Runs a busy loop to advance the current cycle counter to `cycles`.
            let busy_loop = || {
                // Unfortunately we can't use env::cycle_count like
                // MultiTestSpec::BusyLoop does, since it's always
                // zero when running unconstrained.

                const CYCLES_PER_LOOP: u32 = 2; // Determined empirically

                for _ in 0..cycles_left / CYCLES_PER_LOOP {
                    unsafe { asm!("") }
                }
            };
            if unconstrained {
                // test; run in unconstrained mode
                env::run_unconstrained(busy_loop);
                env::log("Done running unconstrained");
            } else {
                // control; run in regular constrained proven mode
                busy_loop();
                env::log("Done running control");
            }
        }
        MultiTestSpec::SysProveZkr {
            control_id,
            input,
            claim_digest,
            control_root,
        } => {
            unsafe {
                sys_prove_zkr(
                    claim_digest.as_ref(),
                    control_id.as_ref(),
                    control_root.as_ref(),
                    input.as_ptr(),
                    input.len(),
                );
            }
            env::verify_assumption(claim_digest, control_root)
                .expect("env::verify_integrity returned error");
        }
        MultiTestSpec::SysKeccak => {
            // Test vectors are from KeccakCodePackage
            let mut state = KeccakState::default();

            unsafe { sys_keccak(&state, &mut state) };

            assert_eq!(state, KECCAK_UPDATE);

            unsafe { sys_keccak(&state, &mut state) };

            assert_eq!(
                state,
                [
                    0x2D5C954DF96ECB3C,
                    0x6A332CD07057B56D,
                    0x093D8D1270D76B6C,
                    0x8A20D9B25569D094,
                    0x4F9C4F99E5E7F156,
                    0xF957B9A2DA65FB38,
                    0x85773DAE1275AF0D,
                    0xFAF4F247C3D810F7,
                    0x1F1B9EE6F79A8759,
                    0xE4FECC0FEE98B425,
                    0x68CE61B6B9CE68A1,
                    0xDEEA66C4BA8F974F,
                    0x33C43D836EAFB1F5,
                    0xE00654042719DBD9,
                    0x7CF8A9F009831265,
                    0xFD5449A6BF174743,
                    0x97DDAD33D8994B40,
                    0x48EAD5FC5D0BE774,
                    0xE3B8C8EE55B7B03C,
                    0x91A0226E649E42E9,
                    0x900E3129E7BADD7B,
                    0x202A9EC5FAA3CCE8,
                    0x5B3402464E1C3DB6,
                    0x609F4E62A44C1059,
                    0x20D06CD26A8FBF5C,
                ]
            );
        }
        MultiTestSpec::ShaSingleKeccak => {
            let mut sha_state = SHA256_INIT;
            let mut keccak_state = KeccakState::default();
            unsafe { sys_keccak(&keccak_state, &mut keccak_state) };
            sha_single_keccak(&mut sha_state, &keccak_state);
            assert_eq!(
                sha_state,
                digest!("60ad7130b65fa874a29b3f44aeb6f46bb57cc45aa7f4a9a8db8ab4d378a66f06")
            );

            sha_single_keccak(&mut sha_state, &keccak_state);
            assert_eq!(
                sha_state,
                digest!("d72929ecbe90afdba8444f4b4e4dae6a3cb0465f67ee5dc12321a390dc7911b3")
            );
        }
        MultiTestSpec::KeccakUpdate => {
            let mut state = KeccakState::default();
            env::risc0_keccak_update(&mut state);
            assert_eq!(state, KECCAK_UPDATE);
        }
        MultiTestSpec::KeccakUpdate2 => {
            fn test_input() -> KeccakState {
                let mut state = KeccakState::default();
                let mut pows = 987654321_u64;
                for part in state.as_mut_slice() {
                    *part = pows;
                    pows = pows.wrapping_mul(123456789);
                }
                state
            }
            let mut state = test_input();

            env::risc0_keccak_update(&mut state);
            assert_eq!(
                state,
                [
                    0xd79e8c6b59a6985b,
                    0xbd19ccee63a9d40,
                    0xa0a6df6a1793fd20,
                    0x6f5e7d6a579ba02d,
                    0x6ff99cb37183ea75,
                    0x4a7736b846248f01,
                    0xed6d5dac353f6586,
                    0xa59ea1c9373e19f7,
                    0x2a82c3bd8daf69db,
                    0x7e49515cc085cfcb,
                    0xf65fb55c8584c54c,
                    0xf89d733d89b147df,
                    0xeb85471d7cbcad68,
                    0x2786372c23d217c,
                    0xac0b725dc2443591,
                    0x1cad0517091d449d,
                    0x6afd9494cb125e27,
                    0x74fb209306e9daa0,
                    0x352c0570fa607115,
                    0xc1b2b78e8fd1ab23,
                    0x661c47f949651c0d,
                    0x91bdd8d5e378e77a,
                    0xdbaf74e7812a697b,
                    0xe4458a47859ad246,
                    0xd5f9328619cd99f7
                ]
            );
        }
        MultiTestSpec::KeccakUnion(proof_count) => {
            let cycles = 1 << KECCAK_DEFAULT_PO2;
            let count = cycles / 200 * proof_count;

            let mut state = KeccakState::default();

            for _i in 0..count {
                env::risc0_keccak_update(&mut state);
            }
        }
    }
}
