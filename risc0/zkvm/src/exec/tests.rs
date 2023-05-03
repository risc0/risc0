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

use std::{collections::BTreeMap, io::Cursor, str::from_utf8, sync::Mutex};

use risc0_zkvm_methods::{
    multi_test::{MultiTestSpec, SYS_MULTI_TEST},
    HELLO_COMMIT_ELF, MULTI_TEST_ELF, SLICE_IO_ELF, STANDARD_LIB_ELF,
};
use risc0_zkvm_platform::{fileno, PAGE_SIZE, WORD_SIZE};
use test_log::test;

use super::{Executor, ExecutorEnv, TraceEvent};
use crate::{
    serde::{from_slice, to_vec},
    testutils, ExitCode, MemoryImage, Program,
};

#[test]
fn basic() {
    let env = ExecutorEnv::default();
    let image = BTreeMap::from([
        (0x4000, 0x1234b137), // lui x2, 0x1234b000
        (0x4004, 0xf387e1b7), // lui x3, 0xf387e000
        (0x4008, 0x003100b3), // add x1, x2, x3
        (0x400c, 0x00000073), // ecall(halt)
    ]);
    let program = Program {
        entry: 0x4000,
        image,
    };
    let image = MemoryImage::new(&program, PAGE_SIZE as u32).unwrap();
    let pre_image_id = image.get_root();

    let mut exec = Executor::new(env, image, program.entry);
    let session = exec.run().unwrap();
    let segments = session.resolve().unwrap();

    assert_eq!(segments.len(), 1);
    assert_eq!(segments[0].exit_code, ExitCode::Halted(0));
    assert_eq!(segments[0].pre_image.get_root(), pre_image_id);
    assert_ne!(segments[0].post_image_id, pre_image_id);
    assert_eq!(segments[0].index, 0);
}

#[test]
fn system_split() {
    let entry = 0x4000;
    let env = ExecutorEnv::builder()
        .segment_limit_po2(14) // 16K cycles
        .build();
    let mut image = BTreeMap::new();
    let mut pc = entry;
    for _ in 0..1000 {
        image.insert(pc, 0x1234b137); // lui x2, 0x1234b000
        pc += WORD_SIZE as u32;
    }
    image.insert(pc, 0x000055b7); // lui a1, 0x00005000
    pc += WORD_SIZE as u32;
    image.insert(pc, 0xc0058593); // addi a1, a1, -0x400
    pc += WORD_SIZE as u32;
    image.insert(pc, 0x00000073); // ecall(halt)

    let program = Program { entry, image };
    let image = MemoryImage::new(&program, PAGE_SIZE as u32).unwrap();
    let pre_image_id = image.get_root();

    let mut exec = Executor::new(env, image, program.entry);
    let session = exec.run().unwrap();
    let segments = session.resolve().unwrap();

    assert_eq!(segments.len(), 2);
    assert!(std::matches!(segments[0].exit_code, ExitCode::SystemSplit));
    assert_eq!(segments[0].pre_image.get_root(), pre_image_id);
    assert_ne!(segments[0].post_image_id, pre_image_id);
    assert_eq!(segments[1].exit_code, ExitCode::Halted(0));
    assert_eq!(segments[1].pre_image.get_root(), segments[0].post_image_id);
    assert_eq!(segments[0].index, 0);
    assert_eq!(segments[1].index, 1);
}

#[test]
fn libm_build() {
    let env = ExecutorEnv::builder()
        .add_input(&to_vec(&MultiTestSpec::LibM).unwrap())
        .build();

    let mut exec = Executor::from_elf(env, MULTI_TEST_ELF).unwrap();
    exec.run().expect("Could not get receipt");
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
    let input = to_vec(&MultiTestSpec::Syscall {
        count: expected.len() as u32 - 1,
    })
    .unwrap();
    let actual: Mutex<Vec<Vec<u8>>> = Vec::new().into();
    let env = ExecutorEnv::builder()
        .add_input(&input)
        .io_callback(SYS_MULTI_TEST, |buf: &[u8]| -> Vec<u8> {
            let mut actual = actual.lock().unwrap();
            actual.push(buf.into());
            expected[actual.len()].clone()
        })
        .build();
    let mut exec = Executor::from_elf(env, MULTI_TEST_ELF).unwrap();
    exec.run().unwrap();
    assert_eq!(*actual.lock().unwrap(), expected[..expected.len() - 1]);
}

// Make sure panics in the callback get propagated correctly.
#[test]
#[should_panic(expected = "I am panicking from here!")]
fn host_syscall_callback_panic() {
    let input = to_vec(&MultiTestSpec::Syscall { count: 5 }).unwrap();
    let env = ExecutorEnv::builder()
        .add_input(&input)
        .io_callback(SYS_MULTI_TEST, |_buf: &[u8]| -> Vec<u8> {
            panic!("I am panicking from here!");
        })
        .build();
    let mut exec = Executor::from_elf(env, MULTI_TEST_ELF).unwrap();
    exec.run().unwrap();
}

#[test]
fn sha_accel() {
    let input = to_vec(&MultiTestSpec::ShaConforms).unwrap();
    let env = ExecutorEnv::builder().add_input(&input).build();
    let mut exec = Executor::from_elf(env, MULTI_TEST_ELF).unwrap();
    exec.run().unwrap();
}

#[test]
fn bigint_accel() {
    let cases = testutils::generate_bigint_test_cases(&mut rand::thread_rng(), 10);
    for case in cases {
        println!("Running BigInt circuit test case: {:x?}", case);
        let input = to_vec(&MultiTestSpec::BigInt {
            x: case.x,
            y: case.y,
            modulus: case.modulus,
        })
        .unwrap();

        let env = ExecutorEnv::builder().add_input(&input).build();
        let mut exec = Executor::from_elf(env, MULTI_TEST_ELF).unwrap();
        let session = exec.run().unwrap();
        assert_eq!(
            session.journal.as_slice(),
            bytemuck::cast_slice(case.expected().as_slice())
        );
    }
}

#[test]
fn sha_cycle_count() {
    let input = to_vec(&MultiTestSpec::ShaCycleCount).unwrap();
    let env = ExecutorEnv::builder().add_input(&input).build();
    let mut exec = Executor::from_elf(env, MULTI_TEST_ELF).unwrap();
    exec.run().unwrap();
}

#[test]
fn stdio() {
    const MSG: &str = "Hello world!  This is a test of standard input and output.";
    const FD: u32 = 123;
    let spec = to_vec(&MultiTestSpec::CopyToStdout { fd: FD }).unwrap();
    let mut stdout: Vec<u8> = Vec::new();
    {
        let env = ExecutorEnv::builder()
            .read_fd(FD, MSG.as_bytes())
            .stdin(bytemuck::cast_slice(&spec))
            .stdout(&mut stdout)
            .build();
        let mut exec = Executor::from_elf(env, MULTI_TEST_ELF).unwrap();
        exec.run().unwrap();
    }
    assert_eq!(MSG, from_utf8(&stdout).unwrap());
}

// Tests sys_read into a buffer of bytes that may not be word aligned.
//
// To make sure we don't miss any edge cases, this tries all permutations of
// start alignment, end alignment, and 0, 1, or 2 whole words.
#[test]
fn posix_style_read() {
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

        let spec = to_vec(&MultiTestSpec::SysRead {
            fd: 123,
            orig: orig.to_vec(),
            pos_and_len: pos_and_len.clone(),
        })
        .unwrap();
        let env = ExecutorEnv::builder()
            .read_fd(123, readbuf.as_slice())
            .add_input(&spec)
            .build();
        let mut exec = Executor::from_elf(env, MULTI_TEST_ELF).unwrap();
        let session = exec.run().unwrap();

        let actual: Vec<u8> = from_slice(&session.journal).unwrap();
        assert_eq!(
            from_utf8(&actual).unwrap(),
            from_utf8(&expected).unwrap(),
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
fn environment() {
    let env = ExecutorEnv::builder()
        .env_var("TEST_MODE", "ENV_VARS")
        .env_var("ENV_VAR1", "val1")
        .env_var("ENV_VAR2", "")
        .read_fd(
            fileno::STDIN,
            Cursor::new(
                r"ENV_VAR1
ENV_VAR2
ENV_VAR3",
            ),
        )
        .build();
    let mut exec = Executor::from_elf(env, STANDARD_LIB_ELF).unwrap();
    let session = exec.run().unwrap();
    let actual = session.journal.as_slice();
    assert_eq!(
        from_utf8(actual).unwrap(),
        r"ENV_VAR1=val1
ENV_VAR2=
!ENV_VAR3
"
    );
}

#[test]
fn commit_hello_world() {
    let mut exec = Executor::from_elf(ExecutorEnv::default(), HELLO_COMMIT_ELF).unwrap();
    exec.run().unwrap();
}

#[test]
fn random() {
    let spec = to_vec(&MultiTestSpec::DoRandom).unwrap();
    let env = ExecutorEnv::builder().add_input(&spec).build();
    let mut exec = Executor::from_elf(env, MULTI_TEST_ELF).unwrap();
    exec.run().unwrap();
}

#[test]
fn slice_io() {
    let run = |slice: &[u8]| {
        let env = ExecutorEnv::builder()
            .add_input(&[slice.len() as u32])
            .add_input(slice)
            .build();
        let mut exec = Executor::from_elf(env, SLICE_IO_ELF).unwrap();
        let session = exec.run().unwrap();
        assert_eq!(session.journal, slice);
    };

    run(b"");
    run(b"xyz");
    run(b"0000");
}

// Check that a compliant host will fault.
#[test]
fn fail() {
    let spec = to_vec(&MultiTestSpec::Fail).unwrap();
    let env = ExecutorEnv::builder().add_input(&spec).build();
    let mut exec = Executor::from_elf(env, MULTI_TEST_ELF).unwrap();
    let err = exec.run().err().unwrap();
    assert!(err.to_string().contains("MultiTestSpec::Fail invoked"));
}

#[cfg(feature = "profiler")]
#[test]
fn profiler() {
    use crate::{
        binfmt::elf::Program,
        exec::profiler::{Frame, Profiler},
    };

    let mut prof = Profiler::new("multi_test.elf", MULTI_TEST_ELF).unwrap();
    {
        let env = ExecutorEnv::builder()
            .add_input(&to_vec(&MultiTestSpec::Profiler).unwrap())
            .trace_callback(prof.make_trace_callback())
            .build();
        let mut exec = Executor::from_elf(env, MULTI_TEST_ELF).unwrap();
        exec.run().unwrap();
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
        let env = ExecutorEnv::builder()
            .add_input(&to_vec(&MultiTestSpec::EventTrace).unwrap())
            .trace_callback(|event| Ok(events.push(event)))
            .build();
        let mut exec = Executor::from_elf(env, MULTI_TEST_ELF).unwrap();
        exec.run().unwrap();
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
