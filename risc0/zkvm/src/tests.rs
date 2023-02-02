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

use std::{fmt, sync::Mutex};

use anyhow::Result;
use risc0_zeroio::{from_slice, to_vec};
use risc0_zkp::core::sha::Digest;
use risc0_zkvm_methods::{
    multi_test::MultiTestSpec, HELLO_COMMIT_ELF, HELLO_COMMIT_ID, MULTI_TEST_ELF, MULTI_TEST_ID,
};
use risc0_zkvm_platform::{
    memory::{COMMIT, HEAP},
    WORD_SIZE,
};
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
    let mut prover = Prover::new(MULTI_TEST_ELF, MULTI_TEST_ID).unwrap();
    prover.add_input_u32_slice(&to_vec(&MultiTestSpec::ShaDigest { data: msg.into() }).unwrap());
    let receipt = prover.run().unwrap();
    from_slice::<Digest>(&receipt.journal).unwrap().into_orig()
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
    run_memio(&[(COMMIT.start(), 1), (COMMIT.start(), 1)]).unwrap();

    // Writes at different addresses are fine
    run_memio(&[(COMMIT.start(), 1), (COMMIT.start() + 4, 2)]).unwrap();

    // Aligned write is fine
    run_memio(&[(HEAP.start(), 1)]).unwrap();

    // Unaligned write is bad
    assert!(unwrap_err(run_memio(&[(HEAP.start() + 1001, 1)]))
        .starts_with("eqz failed at: ./cirgen/circuit/rv32im/rv32im.inl"));

    // Aligned read is fine
    run_memio(&[(HEAP.start(), 0)]).unwrap();

    // Unaligned read is bad
    assert!(unwrap_err(run_memio(&[(HEAP.start() + 1, 0)]))
        .starts_with("eqz failed at: ./cirgen/circuit/rv32im/rv32im.inl"));
}

fn run_memio(pairs: &[(usize, usize)]) -> Result<Receipt> {
    let spec = MultiTestSpec::ReadWriteMem {
        values: pairs
            .iter()
            .cloned()
            .map(|(addr, value)| (addr as u32, value as u32))
            .collect(),
    };
    let mut prover = Prover::new(MULTI_TEST_ELF, MULTI_TEST_ID).unwrap();
    prover.add_input_u32_slice(&to_vec(&spec).unwrap());
    prover.run()
}

fn run_do_nothing(opts: ProverOpts) -> Result<Receipt> {
    let mut prover = Prover::new_with_opts(MULTI_TEST_ELF, MULTI_TEST_ID, opts).unwrap();
    prover.add_input_u32_slice(&to_vec(&MultiTestSpec::DoNothing).unwrap());
    prover.run()
}

#[test]
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
fn fail() {
    // Check that a compliant host will fault.
    let mut prover = Prover::new(MULTI_TEST_ELF, MULTI_TEST_ID).unwrap();
    prover.add_input_u32_slice(&to_vec(&MultiTestSpec::Fail).unwrap());

    assert!(unwrap_err(prover.run())
        .to_string()
        .contains("MultiTestSpec::Fail invoked"));
}

#[test]
#[cfg_attr(feature = "insecure_skip_seal", ignore)]
fn check_image_id() {
    let receipt = run_do_nothing(ProverOpts::default()).unwrap();
    receipt
        .verify(&MULTI_TEST_ID)
        .expect("Verification should succeed before we corrupt the image_id");
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
fn commit_hello_world() {
    let receipt = {
        let mut prover = Prover::new(HELLO_COMMIT_ELF, HELLO_COMMIT_ID).unwrap();
        prover.run().expect("Could not get receipt")
    };

    receipt
        .verify(&HELLO_COMMIT_ID)
        .expect("Could not verify receipt");
}

#[test]
fn host_sendrecv() {
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
        .with_sendrecv_callback(5, |channel_id, buf| -> Vec<u8> {
            assert_eq!(channel_id, 5);
            let mut act = actual.lock().unwrap();
            act.push(buf.into());
            expected[act.len()].clone()
        });
    let mut prover = Prover::new_with_opts(MULTI_TEST_ELF, MULTI_TEST_ID, opts).unwrap();
    prover.add_input_u32_slice(
        &to_vec(&MultiTestSpec::SendRecv {
            channel_id: 5,
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
fn host_sendrecv_callback_panic() {
    let opts = ProverOpts::default()
        .with_skip_seal(true)
        .with_sendrecv_callback(5, |_channel_id, _buf| -> Vec<u8> {
            panic!("I am panicking from here!");
        });
    let mut prover = Prover::new_with_opts(MULTI_TEST_ELF, MULTI_TEST_ID, opts).unwrap();
    prover.add_input_u32_slice(
        &to_vec(&MultiTestSpec::SendRecv {
            channel_id: 5,
            count: 5,
        })
        .unwrap(),
    );
    prover.run().unwrap();
}

#[test]
fn sha_accel() {
    let opts = ProverOpts::default().with_skip_seal(true);
    let mut prover = Prover::new_with_opts(MULTI_TEST_ELF, MULTI_TEST_ID, opts).unwrap();
    prover.add_input_u32_slice(&to_vec(&MultiTestSpec::ShaConforms).unwrap());
    prover.run().unwrap();
}

#[test]
fn sha_cycle_count() {
    let opts = ProverOpts::default().with_skip_seal(true);
    let mut prover = Prover::new_with_opts(MULTI_TEST_ELF, MULTI_TEST_ID, opts).unwrap();
    prover.add_input_u32_slice(&to_vec(&MultiTestSpec::ShaCycleCount).unwrap());
    prover.run().unwrap();
}

#[cfg(feature = "profiler")]
#[test]
fn profiler() {
    use crate::binfmt::elf::Program;
    use crate::prove::profiler::{Frame, Profiler};

    let mut prof = Profiler::new("multi_test.elf", MULTI_TEST_ELF).unwrap();
    {
        let opts = ProverOpts::default()
            .with_skip_seal(true)
            .with_trace_callback(prof.make_trace_callback());
        let mut prover = Prover::new_with_opts(MULTI_TEST_ELF, MULTI_TEST_ID, opts).unwrap();
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
        let mut prover = Prover::new_with_opts(MULTI_TEST_ELF, MULTI_TEST_ID, opts).unwrap();
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
            fn $func_name() {
                use std::io::Read;

                use flate2::read::GzDecoder;
                use risc0_zkvm_platform::{memory::MEM_SIZE, PAGE_SIZE};
                use tar::Archive;
                use $crate::{MemoryImage, Program, Prover};

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

                    let program = Program::load_elf(elf.as_slice(), MEM_SIZE as u32).unwrap();
                    let image = MemoryImage::new(&program, PAGE_SIZE as u32);

                    let mut prover = Prover::new(elf.as_slice(), image.root).unwrap();
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
