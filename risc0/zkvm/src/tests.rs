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

use std::{fmt, io::Cursor, str::from_utf8, sync::Mutex};

use anyhow::Result;
use risc0_zeroio::to_vec;
use risc0_zkp::core::sha::Digest;
use risc0_zkvm_methods::MULTI_TEST_ID;
use risc0_zkvm_methods::{
    multi_test::{MultiTestSpec, SYS_MULTI_TEST},
    HELLO_COMMIT_ELF, MULTI_TEST_ELF, SLICE_IO_ELF, STANDARD_LIB_ELF,
};
use risc0_zkvm_platform::{fileno, memory::HEAP, WORD_SIZE};
use serial_test::serial;
use test_log::test;

use super::{Prover, ProverOpts, Receipt};
use crate::prove::TraceEvent;

#[test]
#[serial]
fn sha_basics() {
    assert_eq!(
        run_sha(""),
        Digest::from([
            0xe3b0c442_u32.to_be(),
            0x98fc1c14_u32.to_be(),
            0x9afbf4c8_u32.to_be(),
            0x996fb924_u32.to_be(),
            0x27ae41e4_u32.to_be(),
            0x649b934c_u32.to_be(),
            0xa495991b_u32.to_be(),
            0x7852b855_u32.to_be(),
        ])
    );
    assert_eq!(
        run_sha("a"),
        Digest::from([
            0xca978112_u32.to_be(),
            0xca1bbdca_u32.to_be(),
            0xfac231b3_u32.to_be(),
            0x9a23dc4d_u32.to_be(),
            0xa786eff8_u32.to_be(),
            0x147c4e72_u32.to_be(),
            0xb9807785_u32.to_be(),
            0xafee48bb_u32.to_be(),
        ])
    );
    assert_eq!(
        run_sha("abc"),
        Digest::from([
            0xba7816bf_u32.to_be(),
            0x8f01cfea_u32.to_be(),
            0x414140de_u32.to_be(),
            0x5dae2223_u32.to_be(),
            0xb00361a3_u32.to_be(),
            0x96177a9c_u32.to_be(),
            0xb410ff61_u32.to_be(),
            0xf20015ad_u32.to_be()
        ])
    );
    assert_eq!(
        run_sha("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"),
        Digest::from([
            0x248d6a61_u32.to_be(),
            0xd20638b8_u32.to_be(),
            0xe5c02693_u32.to_be(),
            0x0c3e6039_u32.to_be(),
            0xa33ce459_u32.to_be(),
            0x64ff2167_u32.to_be(),
            0xf6ecedd4_u32.to_be(),
            0x19db06c1_u32.to_be()
        ])
    );
}

fn run_sha(msg: &str) -> Digest {
    let mut prover = Prover::new(MULTI_TEST_ELF).unwrap();
    prover.add_input_u32_slice(&to_vec(&MultiTestSpec::ShaDigest { data: msg.into() }).unwrap());
    let receipt = prover.run().unwrap();
    Digest::try_from(receipt.journal.as_slice()).unwrap()
}

fn unwrap_err<T, E: fmt::Debug>(result: Result<T, E>) -> String {
    match result {
        Ok(_) => panic!("Expected err"),
        Err(e) => format!("{e:?}"),
    }
}

#[test]
#[serial]
fn memory_io() {
    // Double writes are fine
    run_memio(&[(HEAP.start(), 1), (HEAP.start(), 1)]).unwrap();

    // Writes at different addresses are fine
    run_memio(&[(HEAP.start(), 1), (HEAP.start() + 4, 2)]).unwrap();

    // Aligned write is fine
    run_memio(&[(HEAP.start(), 1)]).unwrap();

    // Unaligned write is bad
    let err = unwrap_err(run_memio(&[(HEAP.start() + 1001, 1)]));
    assert!(
        err.starts_with("eqz failed at: ./cirgen/circuit/rv32im/rv32im.inl")
            || err.starts_with("AlignmentFault"),
        "Actual: {err}"
    );

    // Aligned read is fine
    run_memio(&[(HEAP.start(), 0)]).unwrap();

    // Unaligned read is bad
    let err = unwrap_err(run_memio(&[(HEAP.start() + 1, 0)]));
    assert!(
        err.starts_with("eqz failed at: ./cirgen/circuit/rv32im/rv32im.inl")
            || err.starts_with("AlignmentFault"),
        "Actual: {err}"
    );
}

fn run_memio(pairs: &[(usize, usize)]) -> Result<Receipt> {
    let spec = MultiTestSpec::ReadWriteMem {
        values: pairs
            .iter()
            .cloned()
            .map(|(addr, value)| (addr as u32, value as u32))
            .collect(),
    };
    let mut prover = Prover::new(MULTI_TEST_ELF).unwrap();
    prover.add_input_u32_slice(&to_vec(&spec).unwrap());
    prover.run()
}

fn run_do_nothing(opts: ProverOpts) -> Result<Receipt> {
    let mut prover = Prover::new_with_opts(MULTI_TEST_ELF, opts).unwrap();
    prover.add_input_u32_slice(&to_vec(&MultiTestSpec::DoNothing).unwrap());
    prover.run()
}

#[test]
#[cfg_attr(feature = "cuda", serial)]
fn receipt_serde_with_seal() {
    let receipt = run_do_nothing(ProverOpts::default()).unwrap();
    let ser: Vec<u32> = crate::serde::to_vec(&receipt).unwrap();
    let de: Receipt = crate::serde::from_slice(&ser).unwrap();
    assert_eq!(de.journal, receipt.journal);
    assert_eq!(de.seal, receipt.seal);
    de.verify(&MULTI_TEST_ID).unwrap();
}

#[test]
#[cfg_attr(feature = "insecure_skip_seal", ignore)]
fn receipt_serde_no_seal() {
    let receipt = run_do_nothing(ProverOpts::default().with_skip_seal(true)).unwrap();
    let ser: Vec<u32> = crate::serde::to_vec(&receipt).unwrap();
    let de: Receipt = crate::serde::from_slice(&ser).unwrap();
    assert_eq!(de.journal, receipt.journal);
    assert_eq!(de.seal, receipt.seal);
    assert!(de.verify(&MULTI_TEST_ID).is_err());
}

#[test]
#[cfg_attr(feature = "cuda", serial)]
fn fail() {
    // Check that a compliant host will fault.
    let mut prover = Prover::new(MULTI_TEST_ELF).unwrap();
    prover.add_input_u32_slice(&to_vec(&MultiTestSpec::Fail).unwrap());

    assert!(unwrap_err(prover.run())
        .to_string()
        .contains("MultiTestSpec::Fail invoked"));
}

#[test]
#[cfg_attr(feature = "insecure_skip_seal", ignore)]
#[cfg_attr(feature = "cuda", serial)]
fn check_image_id() {
    let receipt = run_do_nothing(ProverOpts::default()).unwrap();
    receipt.verify(&MULTI_TEST_ID).unwrap();
    let mut digest: Digest = MULTI_TEST_ID.into();
    for word in digest.as_mut_words() {
        *word = word.wrapping_add(1);
    }
    assert_eq!(
        receipt
            .verify(&digest)
            .expect_err("Verification should fail with a corrupted image_id")
            .to_string(),
        "Verification failed: image_id mismatch"
    );
}

#[test]
#[cfg_attr(feature = "insecure_skip_seal", ignore)]
#[cfg_attr(feature = "cuda", serial)]
fn commit_hello_world() {
    let mut prover = Prover::new(HELLO_COMMIT_ELF).unwrap();
    prover.run().unwrap();
}

#[test]
#[cfg_attr(feature = "insecure_skip_seal", ignore)]
#[cfg_attr(feature = "cuda", serial)]
fn do_random() {
    let mut prover = Prover::new(MULTI_TEST_ELF).unwrap();
    prover.add_input_u32_slice(&to_vec(&MultiTestSpec::DoRandom).unwrap());
    prover.run().unwrap();
}

#[test]
#[cfg_attr(feature = "insecure_skip_seal", ignore)]
#[cfg_attr(feature = "cuda", serial)]
fn slice_io() {
    let run = |slice: &[u8]| {
        let mut prover = Prover::new(SLICE_IO_ELF).unwrap();
        prover.add_input_u32_slice(&[slice.len() as u32]);
        prover.add_input_u8_slice(slice);
        let receipt = prover.run().unwrap();
        assert_eq!(receipt.journal, slice);
    };

    run(b"");
    run(b"xyz");
    run(b"0000");
}

#[test]
fn host_syscall() {
    let expected: Vec<Vec<u8>> = vec![
        "".into(),
        "H".into(),
        "He".into(),
        "Hel".into(),
        "Hell".into(),
        "Hello".into(),
    ];
    let actual: Mutex<Vec<Vec<u8>>> = Vec::new().into();
    let opts = ProverOpts::default()
        .with_skip_seal(true)
        .with_sendrecv_callback(SYS_MULTI_TEST, |buf: &[u8]| -> Vec<u8> {
            let mut act = actual.lock().unwrap();
            act.push(buf.into());
            expected[act.len()].clone()
        });
    let mut prover = Prover::new_with_opts(MULTI_TEST_ELF, opts).unwrap();
    prover.add_input_u32_slice(
        &to_vec(&MultiTestSpec::Syscall {
            count: expected.len() as u32 - 1,
        })
        .unwrap(),
    );
    prover.run().unwrap();

    assert_eq!(*actual.lock().unwrap(), expected[..expected.len() - 1]);
}

// Make sure panics in the callback get propagated correctly.
#[test]
#[should_panic(expected = "I am panicking from here!")]
fn host_syscall_callback_panic() {
    let opts = ProverOpts::default()
        .with_skip_seal(true)
        .with_sendrecv_callback(SYS_MULTI_TEST, |_buf: &[u8]| -> Vec<u8> {
            panic!("I am panicking from here!");
        });
    let mut prover = Prover::new_with_opts(MULTI_TEST_ELF, opts).unwrap();
    prover.add_input_u32_slice(&to_vec(&MultiTestSpec::Syscall { count: 5 }).unwrap());
    prover.run().unwrap();
}

#[test]
fn sha_accel() {
    let opts = ProverOpts::default().with_skip_seal(true);
    let mut prover = Prover::new_with_opts(MULTI_TEST_ELF, opts).unwrap();
    prover.add_input_u32_slice(&to_vec(&MultiTestSpec::ShaConforms).unwrap());
    prover.run().unwrap();
}

#[test]
fn sha_cycle_count() {
    let opts = ProverOpts::default().with_skip_seal(true);
    let mut prover = Prover::new_with_opts(MULTI_TEST_ELF, opts).unwrap();
    prover.add_input_u32_slice(&to_vec(&MultiTestSpec::ShaCycleCount).unwrap());
    prover.run().unwrap();
}

#[test]
fn test_poseidon_proof() {
    use risc0_zkp::core::config::HashSuitePoseidon;

    use crate::prove::default_poseidon_hal;
    let (hal, eval) = default_poseidon_hal();
    let opts = ProverOpts::default().with_skip_verify(true);
    let mut prover = Prover::new_with_opts(MULTI_TEST_ELF, opts).unwrap();
    prover.add_input_u32_slice(&to_vec(&MultiTestSpec::DoNothing).unwrap());
    let receipt = prover.run_with_hal(hal.as_ref(), &eval).unwrap();
    receipt
        .verify_with_hash::<HashSuitePoseidon, _>(&MULTI_TEST_ID)
        .unwrap();
}

#[test]
fn test_blake2b_proof() {
    use risc0_circuit_rv32im::cpu::CpuEvalCheck;
    use risc0_core::field::baby_bear::BabyBear;
    use risc0_zkp::{
        core::blake2b::{Blake2bCpuImpl, HashSuiteBlake2b, HashSuiteBlake2bCpu},
        hal::cpu::CpuHal,
    };

    use crate::CIRCUIT;

    let hal = CpuHal::<BabyBear, HashSuiteBlake2bCpu>::new();
    let eval = CpuEvalCheck::new(&CIRCUIT);
    let opts = ProverOpts::default().with_skip_verify(true);
    let mut prover = Prover::new_with_opts(MULTI_TEST_ELF, opts).unwrap();
    prover.add_input_u32_slice(&to_vec(&MultiTestSpec::DoNothing).unwrap());
    let receipt = prover.run_with_hal(&hal, &eval).unwrap();
    receipt
        .verify_with_hash::<HashSuiteBlake2b<Blake2bCpuImpl>, _>(&MULTI_TEST_ID)
        .unwrap();
}

#[cfg(feature = "profiler")]
#[test]
fn profiler() {
    use crate::{
        binfmt::elf::Program,
        prove::profiler::{Frame, Profiler},
    };

    let mut prof = Profiler::new("multi_test.elf", MULTI_TEST_ELF).unwrap();
    {
        let opts = ProverOpts::default()
            .with_skip_seal(true)
            .with_trace_callback(prof.make_trace_callback());
        let mut prover = Prover::new_with_opts(MULTI_TEST_ELF, opts).unwrap();
        prover.add_input_u32_slice(&to_vec(&MultiTestSpec::Profiler).unwrap());
        prover.run().unwrap();
    }

    prof.finalize();

    // Gather up anything containing our profile_test functions.
    // If the test doesn't pass, we don't want to display the
    // whole profiling structure.
    let occurences: Vec<_> = prof
        .iter()
        .filter(|(frames, _addr, _count)| frames.iter().any(|fr| fr.name.contains("profile_test")))
        .collect();

    assert!(!occurences.is_empty(), "{:#?}", Vec::from_iter(prof.iter()));

    let elf_mem = Program::load_elf(MULTI_TEST_ELF, u32::MAX).unwrap().image;

    assert!(
        occurences.iter().any(|(fr, addr, _count)| {
            match fr.as_slice() {
                [fr1 @ Frame {
                    name: name1,
                    filename: fn1,
                    ..
                }, fr2 @ Frame {
                    name: name2,
                    filename: fn2,
                    ..
                }] => {
                    println!("Inspecting frames:\n{fr1:?}\n{fr2:?}\n");
                    if name1 != "profile_test_func2" || name2 != "profile_test_func1" {
                        println!("Names did not match: {}, {}", name1, name2);
                        return false;
                    }
                    if !fn1.ends_with("multi_test.rs") || !fn2.ends_with("multi_test.rs") {
                        println!("Filenames did not match: {}, {}", fn1, fn2);
                        return false;
                    }
                    // Check to make sure we hit the "nop" instruction
                    match elf_mem.get(&(*addr as u32)) {
                        None => {
                            println!("Addr {addr} not present in elf");
                            return false;
                        }
                        Some(0x00_00_00_13) => (),
                        Some(inst) => {
                            println!("Looking for 'nop'; got 0x{inst:08x}");
                            return false;
                        }
                    }

                    // All checks passed; this is the occurence we were looking for.
                    true
                }
                _ => {
                    println!("{:#?}", fr);
                    false
                }
            }
        }),
        "{:#?}",
        occurences
    );
}

#[test]
fn trace() {
    let mut events: Vec<TraceEvent> = Vec::new();
    {
        let opts = ProverOpts::default()
            .with_skip_seal(true)
            .with_trace_callback(|event| Ok(events.push(event)));
        let mut prover = Prover::new_with_opts(MULTI_TEST_ELF, opts).unwrap();
        prover.add_input_u32_slice(&to_vec(&MultiTestSpec::EventTrace).unwrap());

        prover.run().unwrap();
    }
    let occurances = events
        .windows(4)
        .filter_map(|window| {
            if let &[TraceEvent::InstructionStart {
                // li x5, 1337
                cycle: cycle1,
                pc: pc1,
            }, TraceEvent::RegisterSet {
                reg: 5,
                value: 1337,
            }, TraceEvent::InstructionStart {
                // sw x5, 548(zero)
                cycle: cycle2,
                pc: pc2,
            }, TraceEvent::RegisterSet {
                reg: 6,
                value: 0x08000000,
            }] = window
            {
                assert_eq!(cycle1 + 1, cycle2, "li should take 1 cycles: {:#?}", window);
                assert_eq!(
                    pc1 + WORD_SIZE as u32,
                    pc2,
                    "program counter should advance one word: {:#?}",
                    window
                );
                Some(())
            } else {
                None
            }
        })
        .count();
    assert_eq!(occurances, 1, "trace events: {:#?}", &events);
    assert!(events.contains(&TraceEvent::MemorySet {
        addr: 0x08000224,
        value: 1337
    }));
}

// These tests come from:
// https://github.com/riscv-software-src/riscv-tests
// They were built using the toolchain from:
// https://github.com/risc0/toolchain/releases/tag/2022.03.25
mod riscv_tests {
    macro_rules! test_case {
        ($func_name:ident) => {
            #[test_log::test]
            #[cfg_attr(feature = "cuda", serial_test::serial)]
            fn $func_name() {
                use std::io::Read;

                use flate2::read::GzDecoder;
                use tar::Archive;
                use $crate::Prover;

                let bytes = include_bytes!("testdata/riscv-tests.tgz");
                let gz = GzDecoder::new(&bytes[..]);
                let mut tar = Archive::new(gz);
                for entry in tar.entries().unwrap() {
                    let mut entry = entry.unwrap();
                    if !entry.header().entry_type().is_file() {
                        continue;
                    }
                    let path = entry.path().unwrap();
                    let filename = path.file_name().unwrap().to_str().unwrap();
                    if filename != stringify!($func_name) {
                        continue;
                    }
                    let mut elf = Vec::new();
                    entry.read_to_end(&mut elf).unwrap();

                    let mut prover = Prover::new(elf.as_slice()).unwrap();
                    prover.run().unwrap();
                }
            }
        };
    }

    test_case!(add);
    test_case!(addi);
    test_case!(and);
    test_case!(andi);
    test_case!(auipc);
    test_case!(beq);
    test_case!(bge);
    test_case!(bgeu);
    test_case!(blt);
    test_case!(bltu);
    test_case!(bne);
    test_case!(div);
    test_case!(divu);
    test_case!(jal);
    test_case!(jalr);
    test_case!(lb);
    test_case!(lbu);
    test_case!(lh);
    test_case!(lhu);
    test_case!(lui);
    test_case!(lw);
    test_case!(mul);
    test_case!(mulh);
    test_case!(mulhsu);
    test_case!(mulhu);
    test_case!(or);
    test_case!(ori);
    test_case!(rem);
    test_case!(remu);
    test_case!(sb);
    test_case!(sh);
    test_case!(simple);
    test_case!(sll);
    test_case!(slli);
    test_case!(slt);
    test_case!(slti);
    test_case!(sltiu);
    test_case!(sltu);
    test_case!(sra);
    test_case!(srai);
    test_case!(srl);
    test_case!(srli);
    test_case!(sub);
    test_case!(sw);
    test_case!(xor);
    test_case!(xori);
}

#[test]
#[cfg_attr(feature = "insecure_skip_seal", ignore)]
#[cfg_attr(feature = "cuda", serial)]
fn posix_style_read() {
    // Tests sys_read into a buffer of bytes that may not be word
    // aligned.  To make sure we don't miss any edge cases, this tries
    // all permutations of start alignment, end alignment, and 0, 1,
    // or 2 whole words.

    // Initial buffer to read bytes on top of.
    let orig: Vec<u8> = (b'a'..b'z')
        .chain(b'0'..b'9')
        .chain(b"!@#$%^&*()".iter().cloned())
        .collect();
    // Input to read bytes from.
    let readbuf: Vec<u8> = (b'A'..b'Z').collect();

    let run = |pos_and_len: Vec<(u32, u32)>| {
        let mut expected = orig.to_vec();

        let mut expected_readbuf = readbuf.as_slice();
        for (pos, len) in pos_and_len.iter() {
            let pos = *pos as usize;
            let len = *len as usize;

            let this_read;
            (this_read, expected_readbuf) = expected_readbuf.split_at(len);
            expected[pos..pos + len].clone_from_slice(this_read);
        }

        let opts = ProverOpts::default()
            .with_skip_seal(true)
            .with_read_fd(123, readbuf.as_slice());

        let mut prover = Prover::new_with_opts(MULTI_TEST_ELF, opts).unwrap();
        prover.add_input_u32_slice(
            &to_vec(&MultiTestSpec::SysRead {
                fd: 123,
                orig: orig.to_vec(),
                pos_and_len: pos_and_len.clone(),
            })
            .unwrap(),
        );
        let receipt = prover.run().unwrap();

        use risc0_zeroio::Deserialize;
        // Ugh, journal is of u8s which might not be u32-aligned,
        // causing bytemuck::cast_slice to fail.
        let journal_copy: Vec<u32> = receipt
            .journal
            .chunks(WORD_SIZE)
            .map(|word| u32::from_le_bytes(word.try_into().unwrap()))
            .collect();
        let actual = Vec::<u8>::deserialize_from(&journal_copy);
        assert_eq!(
            std::str::from_utf8(&actual).unwrap(),
            std::str::from_utf8(&expected).unwrap(),
            "pos and lens: {pos_and_len:?}"
        );
    };

    fn next_offset(mut pos: u32, offset: u32) -> u32 {
        while (pos % WORD_SIZE as u32) != offset {
            pos += 1;
        }
        pos
    }

    for start_offset in 0..WORD_SIZE as u32 {
        for end_offset in 0..WORD_SIZE as u32 {
            let mut pos = 0;
            let mut pos_and_len: Vec<(u32, u32)> = Vec::new();

            // Make up a bunch of reads to overwrite parts of the buffer.
            for nwords in 0..3 {
                pos = next_offset(pos, start_offset);
                let start = pos;
                pos += nwords * WORD_SIZE as u32;
                pos = next_offset(pos, end_offset);
                let len = pos - start;
                pos_and_len.push((pos, len));
                assert!(
                    pos + len < orig.len() as u32,
                    "Ran out of space to test writes. pos: {pos} len: {len} end: {end_offset} start = {start_offset}"
                );
                // Make sure there's at least one non-overwritten character between reads.
                pos += 1;
            }

            run(pos_and_len);
        }
    }
}

#[test]
#[cfg_attr(feature = "insecure_skip_seal", ignore)]
#[cfg_attr(feature = "cuda", serial)]
fn environment() {
    let opts = ProverOpts::default()
        .with_env_var("TEST_MODE", "ENV_VARS")
        .with_env_var("ENV_VAR1", "val1")
        .with_env_var("ENV_VAR2", "")
        .with_read_fd(
            fileno::STDIN,
            Cursor::new(
                r"ENV_VAR1
ENV_VAR2
ENV_VAR3",
            ),
        );
    let mut prover = Prover::new_with_opts(STANDARD_LIB_ELF, opts).unwrap();
    let receipt = prover.run().unwrap();
    let actual = receipt.journal.as_slice();
    assert_eq!(
        from_utf8(actual).unwrap(),
        r"ENV_VAR1=val1
ENV_VAR2=
!ENV_VAR3
"
    );
}

#[test]
#[cfg_attr(feature = "insecure_skip_seal", ignore)]
#[cfg_attr(feature = "cuda", serial)]
fn pause_continue() {
    let mut prover = Prover::new(MULTI_TEST_ELF).unwrap();
    prover.add_input_u32_slice(&to_vec(&MultiTestSpec::PauseContinue).unwrap());

    // Run until sys_pause
    prover.run().unwrap();

    // Run until sys_halt
    prover.run().unwrap();
}
