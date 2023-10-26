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

use std::{
    collections::{BTreeMap, HashSet},
    io::Cursor,
    str::from_utf8,
    sync::Mutex,
};

use anyhow::Result;
use bytes::Bytes;
use risc0_zkp::core::digest::Digest;
use risc0_zkvm_methods::{
    multi_test::{MultiTestSpec, SYS_MULTI_TEST},
    HELLO_COMMIT_ELF, MULTI_TEST_ELF, SLICE_IO_ELF, STANDARD_LIB_ELF,
};
use risc0_zkvm_platform::{fileno, syscall::nr::SYS_RANDOM, PAGE_SIZE, WORD_SIZE};
use sha2::{Digest as _, Sha256};
use test_log::test;

use super::executor::ExecutorImpl;
use crate::{
    host::server::{
        exec::{
            executor::ExecutorError,
            syscall::{Syscall, SyscallContext},
        },
        testutils,
    },
    serde::to_vec,
    ExecutorEnv, ExitCode, MemoryImage, Program, Session,
};

fn run_test(spec: MultiTestSpec) {
    let env = ExecutorEnv::builder()
        .write(&spec)
        .unwrap()
        .build()
        .unwrap();
    ExecutorImpl::from_elf(env, MULTI_TEST_ELF)
        .unwrap()
        .run()
        .unwrap();
}

#[test]
fn basic() {
    let env = ExecutorEnv::default();
    let image = BTreeMap::from([
        (0x4000, 0x1234b137), // lui x2, 0x1234b000
        (0x4004, 0xf387e1b7), // lui x3, 0xf387e000
        (0x4008, 0x003100b3), // add x1, x2, x3
        (0x400c, 0x000055b7), // lui x11, 0x5
        (0x4010, 0x00000073), // ecall(halt)
    ]);
    let program = Program {
        entry: 0x4000,
        image,
    };
    let image = MemoryImage::new(&program, PAGE_SIZE as u32).unwrap();
    let pre_image_id = image.compute_id();

    let mut exec = ExecutorImpl::new(env, image).unwrap();
    let session = exec.run().unwrap();
    let segments = session.resolve().unwrap();

    assert_eq!(segments.len(), 1);
    assert_eq!(segments[0].exit_code, ExitCode::Halted(0));
    assert_eq!(segments[0].pre_image.compute_id(), pre_image_id);
    assert_ne!(segments[0].post_image_id, pre_image_id);
    assert_eq!(segments[0].index, 0);
}

#[test]
fn system_split() {
    let entry = 0x4000;
    let env = ExecutorEnv::builder()
        .segment_limit_po2(14) // 16K cycles
        .build()
        .unwrap();
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
    let pre_image_id = image.compute_id();

    let mut exec = ExecutorImpl::new(env, image).unwrap();
    let session = exec.run().unwrap();
    let segments = session.resolve().unwrap();

    assert_eq!(segments.len(), 2);
    assert_eq!(segments[0].exit_code, ExitCode::SystemSplit);
    assert_eq!(segments[0].pre_image.compute_id(), pre_image_id);
    assert_ne!(segments[0].post_image_id, pre_image_id);
    assert_eq!(segments[1].exit_code, ExitCode::Halted(0));
    assert_eq!(
        segments[1].pre_image.compute_id(),
        segments[0].post_image_id
    );
    assert_eq!(segments[0].index, 0);
    assert_eq!(segments[1].index, 1);
}

#[test]
fn libm_build() {
    run_test(MultiTestSpec::LibM);
}

#[test]
fn host_syscall() {
    let expected: Vec<Bytes> = vec![
        "".into(),
        "H".into(),
        "He".into(),
        "Hel".into(),
        "Hell".into(),
        "Hello".into(),
    ];
    let input = MultiTestSpec::Syscall {
        count: expected.len() as u32 - 1,
    };
    let actual: Mutex<Vec<Bytes>> = Vec::new().into();
    let env = ExecutorEnv::builder()
        .write(&input)
        .unwrap()
        .io_callback(SYS_MULTI_TEST, |buf| {
            let mut actual = actual.lock().unwrap();
            actual.push(buf);
            Ok(expected[actual.len()].clone())
        })
        .build()
        .unwrap();
    ExecutorImpl::from_elf(env, MULTI_TEST_ELF)
        .unwrap()
        .run()
        .unwrap();
    assert_eq!(*actual.lock().unwrap(), expected[..expected.len() - 1]);
}

// Make sure panics in the callback get propagated correctly.
#[test]
#[should_panic(expected = "I am panicking from here!")]
fn host_syscall_callback_panic() {
    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::Syscall { count: 5 })
        .unwrap()
        .io_callback(SYS_MULTI_TEST, |_| {
            panic!("I am panicking from here!");
        })
        .build()
        .unwrap();
    ExecutorImpl::from_elf(env, MULTI_TEST_ELF)
        .unwrap()
        .run()
        .unwrap();
}

#[test]
fn sha_accel() {
    run_test(MultiTestSpec::ShaConforms);
}

#[test]
fn sha_cycle_count() {
    run_test(MultiTestSpec::ShaCycleCount);
}

#[test]
fn rsa_compat() {
    run_test(MultiTestSpec::RsaCompat);
}

#[test]
fn bigint_accel() {
    let cases = testutils::generate_bigint_test_cases(&mut rand::thread_rng(), 10);
    for case in cases {
        println!("Running BigInt circuit test case: {:x?}", case);
        let input = MultiTestSpec::BigInt {
            x: case.x,
            y: case.y,
            modulus: case.modulus,
        };

        let env = ExecutorEnv::builder()
            .write(&input)
            .unwrap()
            .build()
            .unwrap();
        let mut exec = ExecutorImpl::from_elf(env, MULTI_TEST_ELF).unwrap();
        let session = exec.run().unwrap();
        assert_eq!(
            &session.journal.bytes,
            bytemuck::cast_slice::<u32, u8>(case.expected().as_slice())
        );
    }
}

#[test]
fn env_stdio() {
    const MSG: &str = "Hello world!  This is a test of standard input and output.";
    const FD: u32 = 123;
    let spec = to_vec(&MultiTestSpec::EchoStdout { nbytes: 9, fd: FD }).unwrap();
    let mut stdout: Vec<u8> = Vec::new();
    {
        let env = ExecutorEnv::builder()
            .read_fd(FD, MSG.as_bytes())
            .stdin(bytemuck::cast_slice(&spec))
            .stdout(&mut stdout)
            .build()
            .unwrap();
        ExecutorImpl::from_elf(env, MULTI_TEST_ELF)
            .unwrap()
            .run()
            .unwrap();
    }
    assert_eq!(MSG, from_utf8(&stdout).unwrap());
}

// Tests sys_read into a buffer of bytes that may not be word aligned.
//
// To make sure we don't miss any edge cases, this tries all permutations of
// start alignment, end alignment, and 0, 1, or 2 whole words.
#[test]
fn posix_style_read() {
    const FD: u32 = 123;
    // Initial buffer to read bytes on top of.
    let buf: Vec<u8> = (b'a'..b'z')
        .chain(b'0'..b'9')
        .chain(b"!@#$%^&*()".iter().cloned())
        .collect();
    // Input to read bytes from.
    let readbuf: Vec<u8> = (b'A'..b'Z').collect();

    let run = |pos_and_len: Vec<(u32, u32)>| {
        let mut expected = buf.to_vec();

        let mut expected_readbuf = readbuf.as_slice();
        for (pos, len) in pos_and_len.iter() {
            let pos = *pos as usize;
            let len = *len as usize;

            let this_read;
            (this_read, expected_readbuf) = expected_readbuf.split_at(len);
            expected[pos..pos + len].clone_from_slice(this_read);
        }

        let spec = MultiTestSpec::SysRead {
            fd: FD,
            buf: buf.to_vec(),
            pos_and_len: pos_and_len.clone(),
        };
        let env = ExecutorEnv::builder()
            .read_fd(FD, readbuf.as_slice())
            .write(&spec)
            .unwrap()
            .build()
            .unwrap();
        let mut exec = ExecutorImpl::from_elf(env, MULTI_TEST_ELF).unwrap();
        let session = exec.run().unwrap();

        let actual: Vec<u8> = session.journal.decode().unwrap();
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
                    pos + len < buf.len() as u32,
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
fn large_io_words() {
    const FD: u32 = 123;
    let buf: Vec<u32> = (0..400_000).collect();
    let expected = buf.clone();
    let input = MultiTestSpec::EchoWords {
        fd: FD,
        nwords: buf.len() as u32,
    };
    let env = ExecutorEnv::builder()
        .read_fd(FD, bytemuck::cast_slice(&buf))
        .write(&input)
        .unwrap()
        .session_limit(Some(20_000_000))
        .build()
        .unwrap();
    let mut exec = ExecutorImpl::from_elf(env, MULTI_TEST_ELF).unwrap();
    let session = exec.run().unwrap();

    let actual: &[u32] = bytemuck::cast_slice(&session.journal.bytes);
    assert_eq!(actual, expected);
}

#[test]
fn large_io_bytes() {
    const FD: u32 = 123;
    let buf: Vec<u32> = (0..400_000).collect();
    let nbytes = (buf.len() * WORD_SIZE) as u32;
    let spec = to_vec(&MultiTestSpec::EchoStdout { nbytes, fd: FD }).unwrap();
    let mut stdout: Vec<u8> = Vec::new();
    {
        let env = ExecutorEnv::builder()
            .read_fd(FD, bytemuck::cast_slice(&buf))
            .stdin(bytemuck::cast_slice(&spec))
            .stdout(&mut stdout)
            .build()
            .unwrap();
        ExecutorImpl::from_elf(env, MULTI_TEST_ELF)
            .unwrap()
            .run()
            .unwrap();
    }
    let actual: &[u32] = bytemuck::cast_slice(&stdout);
    assert_eq!(&buf, actual);
}

#[test]
fn large_sha() {
    let data = vec![0u8; 100_000];
    let expected = hex::encode(Sha256::digest(&data));
    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::ShaDigest { data })
        .unwrap()
        .build()
        .unwrap();
    let mut exec = ExecutorImpl::from_elf(env, MULTI_TEST_ELF).unwrap();
    let session = exec.run().unwrap();
    let actual = hex::encode(Digest::try_from(session.journal.bytes).unwrap());
    assert_eq!(expected, actual);
}

#[test]
fn std_stdio() {
    const STDIN: &str = "Hello world from stdin!\n";
    const EXPECTED_STDOUT: &str = "Hello world on stdout!\n";
    const EXPECTED_STDERR: &str = "Hello world on stderr!\n";

    fn expected_stdout() -> String {
        format!("{EXPECTED_STDOUT}{STDIN}")
    }

    let mut stderr: Vec<u8> = Vec::new();
    let mut stdout: Vec<u8> = Vec::new();
    {
        let env = ExecutorEnv::builder()
            .env_var("TEST_MODE", "STDIO")
            .stdin(STDIN.as_bytes())
            .stderr(&mut stderr)
            .stdout(&mut stdout)
            .build()
            .unwrap();
        ExecutorImpl::from_elf(env, STANDARD_LIB_ELF)
            .unwrap()
            .run()
            .unwrap();
    }
    assert_eq!(from_utf8(&stdout).unwrap(), expected_stdout());
    assert_eq!(from_utf8(&stderr).unwrap(), EXPECTED_STDERR);
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
        .build()
        .unwrap();
    let mut exec = ExecutorImpl::from_elf(env, STANDARD_LIB_ELF).unwrap();
    let session = exec.run().unwrap();
    let actual = &session.journal.bytes;
    assert_eq!(
        from_utf8(actual).unwrap(),
        r"ENV_VAR1=val1
ENV_VAR2=
!ENV_VAR3
"
    );
}

#[test]
fn args() {
    let test_cases: [&[String]; 3] = [
        &[String::default()],
        &[
            "grep".to_string(),
            "-c".to_string(),
            "foo bar".to_string(),
            "-".to_string(),
        ],
        &[String::default()],
    ];
    for args_arr in test_cases {
        let env = ExecutorEnv::builder()
            .env_var("TEST_MODE", "ARGS")
            .args(&args_arr)
            .build()
            .unwrap();
        let mut exec = ExecutorImpl::from_elf(env, STANDARD_LIB_ELF).unwrap();
        let session = exec.run().unwrap();
        let output: Vec<String> = session.journal.decode().unwrap();
        assert_eq!(
            output,
            args_arr
                .into_iter()
                .map(|s| s.to_string())
                .collect::<Vec<String>>(),
        );
    }
}

#[test]
fn commit_hello_world() {
    ExecutorImpl::from_elf(ExecutorEnv::default(), HELLO_COMMIT_ELF)
        .unwrap()
        .run()
        .unwrap();
}

#[test]
fn random() {
    run_test(MultiTestSpec::DoRandom);
}

#[test]
fn slice_io() {
    let run = |slice: &[u8]| {
        let env = ExecutorEnv::builder()
            .write_slice(&[slice.len() as u32])
            .write_slice(slice)
            .build()
            .unwrap();
        let mut exec = ExecutorImpl::from_elf(env, SLICE_IO_ELF).unwrap();
        let session = exec.run().unwrap();
        assert_eq!(session.journal.bytes, slice);
    };

    run(b"");
    run(b"xyz");
    run(b"0000");
}

// Check that a compliant host will fault.
#[test]
fn fail() {
    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::Fail)
        .unwrap()
        .build()
        .unwrap();
    let mut exec = ExecutorImpl::from_elf(env, MULTI_TEST_ELF).unwrap();
    let err = exec.run().err().unwrap();
    assert!(err.to_string().contains("MultiTestSpec::Fail invoked"));
}

#[cfg(feature = "profiler")]
#[test]
fn profiler() {
    use risc0_binfmt::Program;

    use crate::host::server::exec::profiler::{Frame, Profiler};

    let mut prof = Profiler::new("multi_test.elf", MULTI_TEST_ELF).unwrap();
    {
        let env = ExecutorEnv::builder()
            .write(&MultiTestSpec::Profiler)
            .unwrap()
            .trace_callback(prof.make_trace_callback())
            .build()
            .unwrap();
        ExecutorImpl::from_elf(env, MULTI_TEST_ELF)
            .unwrap()
            .run()
            .unwrap();
    }

    prof.finalize();

    // Gather up anything containing our profile_test functions.
    // If the test doesn't pass, we don't want to display the
    // whole profiling structure.
    let occurrences: Vec<_> = prof
        .iter()
        .filter(|(frames, _addr, _count)| frames.iter().any(|fr| fr.name.contains("profile_test")))
        .collect();

    assert!(
        !occurrences.is_empty(),
        "{:#?}",
        Vec::from_iter(prof.iter())
    );

    let elf_mem = Program::load_elf(MULTI_TEST_ELF, u32::MAX).unwrap().image;

    // stitch frames together
    let (fr, addr) = occurrences.into_iter().fold(
        (Vec::new(), 0),
        |(mut acc_frames, _), (frames, addr, _count)| {
            acc_frames.extend(frames);
            (acc_frames, addr)
        },
    );

    let check = |fr: &Vec<Frame>, addr: usize| -> bool {
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
                match elf_mem.get(&(addr as u32)) {
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

                // All checks passed; this is the occurrence we were looking for.
                true
            }
            _ => {
                println!("{:#?}", fr);
                false
            }
        }
    };

    assert!(check(&fr, addr), "{fr:#?} {addr}");
}

#[test]
fn oom() {
    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::Oom)
        .unwrap()
        .build()
        .unwrap();
    let mut exec = ExecutorImpl::from_elf(env, MULTI_TEST_ELF).unwrap();
    let err = exec.run().err().unwrap();
    assert!(err.to_string().contains("Out of memory"), "{err:?}");
}

#[test]
fn memory_access() {
    fn session_faulted(session: Result<Session, ExecutorError>) -> bool {
        if cfg!(feature = "fault-proof") {
            match session {
                Err(ExecutorError::Fault(_)) => true,
                _ => false,
            }
        } else {
            // this will be removed once this feature is more mature
            session.is_err()
        }
    }

    fn access_memory(addr: u32) -> Result<Session, ExecutorError> {
        let env = ExecutorEnv::builder()
            .write(&MultiTestSpec::OutOfBounds)
            .unwrap()
            .write(&addr)
            .unwrap()
            .build()
            .unwrap();
        ExecutorImpl::from_elf(env, MULTI_TEST_ELF).unwrap().run()
    }

    assert!(session_faulted(access_memory(0x0000_0000)));
    assert!(session_faulted(access_memory(0x0C00_0000)));
    assert!(!session_faulted(access_memory(0x0B00_0000)));
}

/// The post-state digest (i.e. the Merkle root of the memory state at the end
/// of the pogram) should be randomized on each execution to avoid potential
/// leakage of private information.
#[test]
fn post_state_digest_randomization() {
    // Run a number of iterations of a guest and confirm all have the unique post
    // state digest.
    const ITERATIONS: usize = 10;
    let post_state_digests: HashSet<Digest> = (0..ITERATIONS)
        .map(|_| {
            // Run the guest and extract the post state digest.
            ExecutorImpl::from_elf(ExecutorEnv::default(), HELLO_COMMIT_ELF)
                .unwrap()
                .run()
                .unwrap()
                .segments
                .last()
                .unwrap()
                .resolve()
                .unwrap()
                .post_image_id
        })
        .collect();
    assert_eq!(post_state_digests.len(), ITERATIONS);

    // Replacement syscall for sys_random to disable the memory image randomization.
    struct RiggedRandom;
    impl Syscall for RiggedRandom {
        fn syscall(
            &mut self,
            _syscall: &str,
            _ctx: &mut dyn SyscallContext,
            to_guest: &mut [u32],
        ) -> Result<(u32, u32)> {
            let rand_buf = vec![27u8; to_guest.len() * WORD_SIZE];
            bytemuck::cast_slice_mut(to_guest).clone_from_slice(rand_buf.as_slice());
            Ok((0, 0))
        }
    }

    // Run a number of iterations of a guest with rigged randomness and confirm all
    // have the same post state digest.
    let post_state_digests: HashSet<Digest> = (0..ITERATIONS)
        .map(|_| {
            // Run the guest and extract the post state digest.
            let mut exec =
                ExecutorImpl::from_elf(ExecutorEnv::default(), HELLO_COMMIT_ELF).unwrap();
            // Override the default randomness syscall using crate-internal API.
            exec.syscall_table.with_syscall(SYS_RANDOM, RiggedRandom);

            exec.run()
                .unwrap()
                .segments
                .last()
                .unwrap()
                .resolve()
                .unwrap()
                .post_image_id
        })
        .collect();
    assert_eq!(post_state_digests.len(), 1);
}

#[test]
#[should_panic(expected = "cycle count too large")]
fn too_many_sha() {
    run_test(MultiTestSpec::TooManySha);
}

#[test]
#[should_panic(expected = "is an invalid guest address")]
fn out_of_bounds_ecall() {
    run_test(MultiTestSpec::OutOfBoundsEcall);
}

#[cfg(feature = "docker")]
mod docker {
    use risc0_zkvm_methods::{multi_test::MultiTestSpec, MULTI_TEST_ELF};
    use risc0_zkvm_platform::WORD_SIZE;

    use crate::{
        host::server::exec::executor::ExecutorError, ExecutorEnv, ExecutorImpl, Session, TraceEvent,
    };

    #[test]
    fn trace() {
        let mut events: Vec<TraceEvent> = Vec::new();
        {
            let env = ExecutorEnv::builder()
                .write(&MultiTestSpec::EventTrace)
                .unwrap()
                .trace_callback(|event| Ok(events.push(event)))
                .build()
                .unwrap();
            ExecutorImpl::from_elf(env, MULTI_TEST_ELF)
                .unwrap()
                .run()
                .unwrap();
        }
        let occurrences = events
            .windows(4)
            .filter_map(|window| {
                if let &[TraceEvent::InstructionStart {
                    // li x5, 1337
                    cycle: cycle1,
                    pc: pc1,
                    ..
                }, TraceEvent::RegisterSet {
                    idx: 5,
                    value: 1337,
                }, TraceEvent::InstructionStart {
                    // sw x5, 548(zero)
                    cycle: cycle2,
                    pc: pc2,
                    ..
                }, TraceEvent::RegisterSet {
                    idx: 6,
                    value: 0x08000000,
                }] = window
                {
                    // Note: it's possible that these instructions could lie between page
                    // boundaries. If that is the case, it means that the difference between cycle2
                    // and cycle1 could be multiples of page-in, which takes up 1094 cycles. Once we
                    // figure out a way to get reproducible builds, we should restrict the
                    // difference of cycles to a single number rather than taking the mod.
                    assert_eq!(
                        (cycle2 - cycle1) % 1094,
                        1,
                        "li should take multiples of page-in cycles + 1: {:#?}",
                        window
                    );
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
        assert_eq!(occurrences, 1, "trace events: {:#?}", &events);
        assert!(events.contains(&TraceEvent::MemorySet {
            addr: 0x08000224,
            value: 1337
        }));
    }

    #[test]
    fn session_limit() {
        fn run_session(
            loop_cycles: u32,
            segment_limit_po2: u32,
            session_count_limit: u64,
        ) -> Result<Session, ExecutorError> {
            let session_cycles = (1 << segment_limit_po2) * session_count_limit;
            let spec = MultiTestSpec::BusyLoop {
                cycles: loop_cycles,
            };
            let env = ExecutorEnv::builder()
                .write(&spec)
                .unwrap()
                .segment_limit_po2(segment_limit_po2)
                .session_limit(Some(session_cycles))
                .build()
                .unwrap();
            ExecutorImpl::from_elf(env, MULTI_TEST_ELF).unwrap().run()
        }

        // This test should always fail if the last parameter is zero
        let err = run_session(0, 16, 0).err().unwrap();
        assert!(err.to_string().contains("Session limit exceeded"));

        assert!(run_session(0, 16, 1).is_ok());

        let err = run_session(1 << 16, 16, 1).err().unwrap();
        assert!(err.to_string().contains("Session limit exceeded"));

        // this should contain exactly 2 segments
        assert!(run_session(1 << 16, 16, 2).is_ok());

        // make sure that it's ok to run with a limit that's higher the actual count
        assert!(run_session(1 << 16, 16, 10).is_ok());

        let err = run_session(1 << 16, 15, 3).err().unwrap();
        assert!(err.to_string().contains("Session limit exceeded"));

        assert!(run_session(1 << 16, 15, 10).is_ok());
    }
}
