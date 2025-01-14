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

use std::{
    collections::{BTreeMap, HashMap, HashSet},
    io::Cursor,
    str::from_utf8,
    sync::Mutex,
};

use anyhow::Result;
use bytes::Bytes;
use risc0_binfmt::{ExitCode, MemoryImage, MemoryImage2, Program};
use risc0_circuit_rv32im::prove::emu::testutil;
use risc0_zkos_v1compat::V1COMPAT_ELF;
use risc0_zkp::digest;
use risc0_zkvm_methods::{
    multi_test::{MultiTestSpec, SYS_MULTI_TEST, SYS_MULTI_TEST_WORDS},
    BLST_ELF, HEAP_ELF, HELLO_COMMIT_ELF, MULTI_TEST_ELF, RAND_ELF, SLICE_IO_ELF, STANDARD_LIB_ELF,
    SYS_ARGS_ELF, SYS_ENV_ELF, ZKVM_527_ELF,
};
use risc0_zkvm_platform::{fileno, syscall::nr::SYS_RANDOM, PAGE_SIZE, WORD_SIZE};
use rstest::*;
use rstest_reuse::*;
use sha2::{Digest as _, Sha256};

use crate::{
    host::server::exec::{
        executor2::Executor2,
        profiler::{Frame, Profiler},
        syscall::{Syscall, SyscallContext},
    },
    serde::to_vec,
    sha::{Digest, Digestible},
    ExecutorEnv, ExecutorImpl, Session, SimpleSegmentRef,
};

#[derive(Clone, Copy)]
enum TestVersion {
    V1,
    V2,
}
use TestVersion::{V1, V2};

#[template]
#[rstest]
#[case(V1)]
#[case(V2)]
#[test_log::test]
fn base(#[case] version: TestVersion) {}

fn execute_elf(version: TestVersion, env: ExecutorEnv, elf: &[u8]) -> Result<Session> {
    match version {
        V1 => ExecutorImpl::from_elf(env, elf)
            .unwrap()
            .run_with_callback(|segment| Ok(Box::new(SimpleSegmentRef::new(segment)))),
        V2 => Executor2::from_elf(env, elf)
            .unwrap()
            .run_with_callback(|segment| Ok(Box::new(SimpleSegmentRef::new(segment)))),
    }
}

fn multi_test(version: TestVersion, spec: MultiTestSpec) {
    let session = multi_test_raw(version, spec).unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));
}

fn multi_test_raw(version: TestVersion, spec: MultiTestSpec) -> Result<Session> {
    let env = ExecutorEnv::builder()
        .write(&spec)
        .unwrap()
        .build()
        .unwrap();
    execute_elf(version, env, MULTI_TEST_ELF)
}

#[apply(base)]
fn cpp_test(#[case] version: TestVersion) {
    let session = execute_elf(version, ExecutorEnv::default(), BLST_ELF).unwrap();
    let message: String = session.journal.unwrap().decode().unwrap();
    assert_eq!(message.as_str(), "blst is such a blast");
}

#[rstest]
#[case(V1)]
#[ignore]
#[case(V2)]
#[should_panic(expected = "too small")]
fn insufficient_segment_limit(#[case] version: TestVersion) {
    let env = ExecutorEnv::builder()
        .segment_limit_po2(13) // 8K cycles
        .write(&MultiTestSpec::DoNothing)
        .unwrap()
        .build()
        .unwrap();
    execute_elf(version, env, MULTI_TEST_ELF).unwrap();
}

#[test_log::test]
fn basic_v1() {
    let program = testutil::basic();
    let env = ExecutorEnv::default();
    let image = MemoryImage::new(&program, PAGE_SIZE as u32).unwrap();
    let pre_image_id = image.compute_id();

    let mut exec = ExecutorImpl::new(env, image).unwrap();
    let session = exec
        .run_with_callback(|segment| Ok(Box::new(SimpleSegmentRef::new(segment))))
        .unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));
    let segment = session.segments.first().unwrap().resolve().unwrap();

    assert_eq!(session.segments.len(), 1);
    assert_eq!(segment.inner.v1().exit_code, ExitCode::Halted(0));
    assert_eq!(segment.inner.v1().pre_state.digest(), pre_image_id);
    assert_ne!(segment.inner.v1().post_state.digest(), pre_image_id);
    assert_eq!(segment.index, 0);
}

#[test_log::test]
fn basic_v2() {
    let program = testutil::basic();
    let env = ExecutorEnv::default();
    let kernel = Program::load_elf(V1COMPAT_ELF, u32::MAX).unwrap();
    let mut image = MemoryImage2::with_kernel(program, kernel);
    let pre_image_id = image.image_id();

    let mut exec = Executor2::new(env, image).unwrap();
    let session = exec
        .run_with_callback(|segment| Ok(Box::new(SimpleSegmentRef::new(segment))))
        .unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));
    let segment = session.segments.first().unwrap().resolve().unwrap();

    assert_eq!(session.segments.len(), 1);
    assert_eq!(segment.inner.v2().exit_code, ExitCode::Halted(0));
    assert_eq!(segment.inner.v2().pre_digest, pre_image_id);
    assert_ne!(segment.inner.v2().post_digest, pre_image_id);
    assert_eq!(segment.index, 0);
}

#[test_log::test]
fn system_split_v1() {
    let entry = 0x4000;
    let env = ExecutorEnv::builder()
        .segment_limit_po2(14) // 16K cycles
        .build()
        .unwrap();
    let mut image = BTreeMap::new();
    let mut pc = entry;
    for _ in 0..100 {
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
    assert_eq!(session.exit_code, ExitCode::Halted(0));
    let segments: Vec<_> = session
        .segments
        .iter()
        .map(|x| x.resolve().unwrap())
        .collect();

    assert_eq!(segments.len(), 2);
    assert_eq!(segments[0].inner.v1().exit_code, ExitCode::SystemSplit);
    assert_eq!(segments[0].inner.v1().pre_state.digest(), pre_image_id);
    assert_ne!(segments[0].inner.v1().post_state.digest(), pre_image_id);
    assert_eq!(segments[1].inner.v1().exit_code, ExitCode::Halted(0));
    assert_eq!(
        segments[1].inner.v1().pre_state.digest(),
        segments[0].inner.v1().post_state.digest()
    );
    assert_eq!(segments[0].index, 0);
    assert_eq!(segments[1].index, 1);
}

#[test_log::test]
fn system_split_v2() {
    let program = risc0_circuit_rv32im_v2::execute::testutil::simple_loop(200);
    let mut image = MemoryImage2::new_kernel(program);
    let pre_image_id = image.image_id();

    let env = ExecutorEnv::builder()
        .segment_limit_po2(13) // 8K cycles
        .build()
        .unwrap();
    let mut exec = Executor2::new(env, image).unwrap();
    let session = exec
        .run_with_callback(|segment| Ok(Box::new(SimpleSegmentRef::new(segment))))
        .unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));
    let segments: Vec<_> = session
        .segments
        .iter()
        .map(|x| x.resolve().unwrap())
        .collect();

    assert_eq!(segments.len(), 2);
    assert_eq!(segments[0].inner.v2().exit_code, ExitCode::SystemSplit);
    assert_eq!(segments[0].inner.v2().pre_digest, pre_image_id);
    assert_ne!(segments[0].inner.v2().post_digest, pre_image_id);
    assert_eq!(segments[1].inner.v2().exit_code, ExitCode::Halted(0));
    assert_eq!(
        segments[1].inner.v2().pre_digest,
        segments[0].inner.v2().post_digest
    );
    assert_eq!(segments[0].index, 0);
    assert_eq!(segments[1].index, 1);
}

#[apply(base)]
fn libm_build(#[case] version: TestVersion) {
    multi_test(version, MultiTestSpec::LibM);
}

#[apply(base)]
fn host_syscall(#[case] version: TestVersion) {
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
    let session = execute_elf(version, env, MULTI_TEST_ELF).unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));
    assert_eq!(*actual.lock().unwrap(), expected[..expected.len() - 1]);
}

#[apply(base)]
fn host_syscall_words(#[case] version: TestVersion) {
    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::SyscallWords)
        .unwrap()
        .io_callback(SYS_MULTI_TEST_WORDS, Ok)
        .build()
        .unwrap();
    let session = execute_elf(version, env, MULTI_TEST_ELF).unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));
}

// Make sure panics in the callback get propagated correctly.
#[apply(base)]
#[should_panic(expected = "I am panicking from here!")]
fn host_syscall_callback_panic(#[case] version: TestVersion) {
    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::Syscall { count: 5 })
        .unwrap()
        .io_callback(SYS_MULTI_TEST, |_| {
            panic!("I am panicking from here!");
        })
        .build()
        .unwrap();
    let session = execute_elf(version, env, MULTI_TEST_ELF).unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));
}

#[apply(base)]
fn sha_accel(#[case] version: TestVersion) {
    multi_test(version, MultiTestSpec::ShaConforms);
}

#[apply(base)]
fn sha_cycle_count(#[case] version: TestVersion) {
    multi_test(version, MultiTestSpec::ShaCycleCount);
}

#[apply(base)]
fn rsa_compat(#[case] version: TestVersion) {
    multi_test(version, MultiTestSpec::RsaCompat);
}

#[rstest]
#[case(V1)]
#[ignore]
#[case(V2)]
#[test_log::test]
fn bigint_accel(#[case] version: TestVersion) {
    use crate::host::server::testutils::generate_bigint_test_cases;

    let cases = generate_bigint_test_cases(&mut rand::thread_rng(), 10);
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
        let session = execute_elf(version, env, MULTI_TEST_ELF).unwrap();
        assert_eq!(session.exit_code, ExitCode::Halted(0));
        assert_eq!(
            session.journal.unwrap().bytes.as_slice(),
            bytemuck::cast_slice::<u32, u8>(case.expected().as_slice())
        );
    }
}

#[apply(base)]
fn env_stdio(#[case] version: TestVersion) {
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
        let session = execute_elf(version, env, MULTI_TEST_ELF).unwrap();
        assert_eq!(session.exit_code, ExitCode::Halted(0));
    }
    assert_eq!(MSG, from_utf8(&stdout).unwrap());
}

// Tests sys_read into a buffer of bytes that may not be word aligned.
//
// To make sure we don't miss any edge cases, this tries all permutations of
// start alignment, end alignment, and 0, 1, or 2 whole words.
#[apply(base)]
fn posix_style_read(#[case] version: TestVersion) {
    const FD: u32 = 123;
    // Initial buffer to read bytes on top of.
    let buf: Vec<u8> = (b'a'..=b'z')
        .chain(b'0'..=b'9')
        .chain(b"!@#$%^&*()".iter().cloned())
        .collect();
    // Input to read bytes from.
    let readbuf: Vec<u8> = (b'A'..=b'Z').collect();

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
        let session = execute_elf(version, env, MULTI_TEST_ELF).unwrap();
        assert_eq!(session.exit_code, ExitCode::Halted(0));

        let (actual, num_read): (Vec<u8>, Vec<usize>) = session.journal.unwrap().decode().unwrap();
        for ((_, len), n_read) in pos_and_len.iter().zip(num_read) {
            assert_eq!(
                *len as usize, n_read,
                "length mismatch, pos and lens: {pos_and_len:?}"
            )
        }
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

#[apply(base)]
fn short_read_combinations(#[case] version: TestVersion) {
    const FD: u32 = 123;
    // Initial buffer to read bytes on top of.
    let buf: Vec<u8> = (b'a'..=b'l').collect();
    // Input to read bytes from.
    let readbuf: Vec<u8> = (b'A'..b'L').collect();

    for read_len in 0..WORD_SIZE {
        for excess_buffer in 0..WORD_SIZE * 2 {
            let buffer = read_len + excess_buffer;
            let mut expected = buf.to_vec();

            expected[..read_len].copy_from_slice(&readbuf[..read_len]);

            // The current behaviour of the read call for more bytes than available is to write
            // zeroes for the remaining bytes.
            expected[read_len..buffer].fill(0);

            let spec = MultiTestSpec::SysRead {
                fd: FD,
                buf: buf.to_vec(),
                pos_and_len: vec![(0, buffer as u32)],
            };
            let env = ExecutorEnv::builder()
                .read_fd(FD, &readbuf[..read_len])
                .write(&spec)
                .unwrap()
                .build()
                .unwrap();
            let session = execute_elf(version, env, MULTI_TEST_ELF).unwrap();
            assert_eq!(session.exit_code, ExitCode::Halted(0));

            let (actual, num_read): (Vec<u8>, Vec<usize>) =
                session.journal.unwrap().decode().unwrap();
            assert_eq!(
                [read_len].as_slice(),
                &num_read,
                "length mismatch, length {read_len} buffer: {buffer}"
            );
            assert_eq!(
                from_utf8(&actual).unwrap(),
                from_utf8(&expected).unwrap(),
                "length {read_len}, buffer {buffer}"
            );
        }
    }
}

#[apply(base)]
fn unaligned_short_read(#[case] version: TestVersion) {
    const FD: u32 = 123;
    // Initial buffer to read bytes on top of.
    let buf: Vec<u8> = vec![0; 9];
    let readbuf: &[u8] = b"1234567";

    let spec = MultiTestSpec::SysRead {
        fd: FD,
        buf: buf.clone(),
        pos_and_len: vec![(0, 9)],
    };
    let env = ExecutorEnv::builder()
        .read_fd(FD, readbuf)
        .write(&spec)
        .unwrap()
        .build()
        .unwrap();
    let session = execute_elf(version, env, MULTI_TEST_ELF).unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));

    let actual: Vec<u8> = session.journal.unwrap().decode().unwrap();
    let mut expected = readbuf.to_vec();
    expected.resize(buf.len(), 0);
    assert_eq!(actual, expected, "pos and lens: {spec:?}");
}

#[apply(base)]
fn large_io_words(#[case] version: TestVersion) {
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
    let session = execute_elf(version, env, MULTI_TEST_ELF).unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));

    let actual: &[u32] = bytemuck::cast_slice(&session.journal.as_ref().unwrap().bytes);
    assert_eq!(actual, expected);
}

#[apply(base)]
fn large_io_bytes(#[case] version: TestVersion) {
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
        let session = execute_elf(version, env, MULTI_TEST_ELF).unwrap();
        assert_eq!(session.exit_code, ExitCode::Halted(0));
    }
    let actual: &[u32] = bytemuck::cast_slice(&stdout);
    assert_eq!(&buf, actual);
}

mod sys_verify {
    use crate::{compute_image_id_v2, MaybePruned, ReceiptClaim};

    use super::*;

    fn exec_hello_commit(version: TestVersion) -> Session {
        let session = execute_elf(version, ExecutorEnv::default(), HELLO_COMMIT_ELF).unwrap();
        assert_eq!(session.exit_code, ExitCode::Halted(0));
        session
    }

    fn exec_halt(version: TestVersion, exit_code: u8) -> Session {
        let env = ExecutorEnv::builder()
            .write(&MultiTestSpec::Halt(exit_code))
            .unwrap()
            .build()
            .unwrap();
        let session = execute_elf(version, env, MULTI_TEST_ELF).unwrap();
        assert_eq!(session.exit_code, ExitCode::Halted(exit_code as u32));
        session
    }

    fn exec_pause(version: TestVersion, exit_code: u8) -> Session {
        let env = ExecutorEnv::builder()
            .write(&MultiTestSpec::PauseResume(exit_code))
            .unwrap()
            .build()
            .unwrap();
        let session = execute_elf(version, env, MULTI_TEST_ELF).unwrap();
        assert_eq!(session.exit_code, ExitCode::Paused(exit_code as u32));
        session
    }

    #[apply(base)]
    fn sys_verify(#[case] version: TestVersion) {
        use risc0_zkvm_methods::{HELLO_COMMIT_ID, HELLO_COMMIT_V2_USER_ID};

        let hello_commit_session = exec_hello_commit(version);

        let image_id: Digest = match version {
            V1 => HELLO_COMMIT_ID.into(),
            V2 => compute_image_id_v2(HELLO_COMMIT_V2_USER_ID).unwrap(),
        };
        tracing::debug!("image_id: {image_id}");

        let spec = &MultiTestSpec::SysVerify(vec![(
            image_id,
            hello_commit_session.journal.clone().unwrap().bytes,
        )]);

        let claim = hello_commit_session.claim().unwrap();
        tracing::debug!("claim: {claim:#?}");
        tracing::debug!("digest: {}", claim.digest());

        // Test that it works when the assumption is added.
        let env = ExecutorEnv::builder()
            .write(&spec)
            .unwrap()
            .add_assumption(claim)
            .build()
            .unwrap();
        let session = execute_elf(version, env, MULTI_TEST_ELF).unwrap();
        assert_eq!(session.exit_code, ExitCode::Halted(0));

        // Test that it does not work when the assumption is not added.
        let env = ExecutorEnv::builder()
            .write(&spec)
            .unwrap()
            .build()
            .unwrap();
        assert!(execute_elf(version, env, MULTI_TEST_ELF).is_err());
    }

    #[apply(base)]
    fn sys_verify_halt_codes(#[case] version: TestVersion) {
        use risc0_zkvm_methods::{MULTI_TEST_ID, MULTI_TEST_V2_USER_ID};

        let image_id: Digest = match version {
            V1 => MULTI_TEST_ID.into(),
            V2 => compute_image_id_v2(MULTI_TEST_V2_USER_ID).unwrap(),
        };

        for code in [0u8, 1, 2, 255] {
            tracing::debug!("sys_verify_pause_codes: code = {code}");
            let halt_session = exec_halt(version, code);

            let spec = &MultiTestSpec::SysVerify(vec![(image_id, Vec::new())]);

            let env = ExecutorEnv::builder()
                .write(&spec)
                .unwrap()
                .add_assumption(halt_session.claim().unwrap())
                .build()
                .unwrap();
            let session = execute_elf(version, env, MULTI_TEST_ELF);

            if code == 0 {
                assert_eq!(session.unwrap().exit_code, ExitCode::Halted(0));
            } else {
                assert!(session.is_err());
            }
        }
    }

    #[apply(base)]
    fn sys_verify_integrity(#[case] version: TestVersion) {
        let hello_commit_session = exec_hello_commit(version);
        let claim = hello_commit_session.claim().unwrap();

        let spec = &MultiTestSpec::SysVerifyIntegrity {
            claim_words: to_vec(&claim).unwrap(),
        };

        // Test that it works when the assumption is added.
        let env = ExecutorEnv::builder()
            .write(&spec)
            .unwrap()
            .add_assumption(claim)
            .build()
            .unwrap();
        let session = execute_elf(version, env, MULTI_TEST_ELF).unwrap();
        assert_eq!(session.exit_code, ExitCode::Halted(0));

        // Test that it does not work when the assumption is not added.
        let env = ExecutorEnv::builder()
            .write(&spec)
            .unwrap()
            .build()
            .unwrap();
        assert!(execute_elf(version, env, MULTI_TEST_ELF).is_err());
    }

    #[apply(base)]
    fn sys_verify_integrity_halt_codes(#[case] version: TestVersion) {
        for code in [0u8, 1, 2, 255] {
            tracing::debug!("sys_verify_pause_codes: code = {code}");
            let halt_session = exec_halt(version, code);
            let claim = halt_session.claim().unwrap();

            let spec = &MultiTestSpec::SysVerifyIntegrity {
                claim_words: to_vec(&claim).unwrap(),
            };

            let env = ExecutorEnv::builder()
                .write(&spec)
                .unwrap()
                .add_assumption(claim)
                .build()
                .unwrap();
            let session = execute_elf(version, env, MULTI_TEST_ELF).unwrap();
            assert_eq!(session.exit_code, ExitCode::Halted(0));
        }
    }

    #[apply(base)]
    fn sys_verify_integrity_pause_codes(#[case] version: TestVersion) {
        for code in [0u8, 1, 2, 255] {
            tracing::debug!("sys_verify_halt_codes: code = {code}");
            let pause_session = exec_pause(version, code);
            let claim = pause_session.claim().unwrap();

            let spec = &MultiTestSpec::SysVerifyIntegrity {
                claim_words: to_vec(&claim).unwrap(),
            };

            let env = ExecutorEnv::builder()
                .write(&spec)
                .unwrap()
                .add_assumption(claim)
                .build()
                .unwrap();
            let session = execute_elf(version, env, MULTI_TEST_ELF).unwrap();
            assert_eq!(session.exit_code, ExitCode::Halted(0));
        }
    }

    #[apply(base)]
    fn sys_verify_integrity_pruned_claim(#[case] version: TestVersion) {
        let hello_commit_session = exec_hello_commit(version);
        let claim = hello_commit_session.claim().unwrap();

        // Prune the claim before providing it as input so that it cannot be checked to have no
        // assumptions.
        let mut pruned_claim: ReceiptClaim = claim.clone();
        pruned_claim.output = MaybePruned::Pruned(pruned_claim.output.digest());
        let spec = &MultiTestSpec::SysVerifyIntegrity {
            claim_words: to_vec(&pruned_claim).unwrap(),
        };

        // Test that it works when the assumption is added.
        let env = ExecutorEnv::builder()
            .write(&spec)
            .unwrap()
            .add_assumption(claim)
            .build()
            .unwrap();

        // Result of execution should be a guest panic resulting from the pruned input.
        let err = execute_elf(version, env, MULTI_TEST_ELF)
            .map(|_| ())
            .unwrap_err();

        tracing::debug!("err: {err}");
        assert!(err
            .to_string()
            .contains("env::verify_integrity returned error"));
    }
}

#[apply(base)]
fn large_sha(#[case] version: TestVersion) {
    let data = vec![0u8; 100_000];
    let expected = hex::encode(Sha256::digest(&data));
    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::ShaDigest { data })
        .unwrap()
        .build()
        .unwrap();
    let session = execute_elf(version, env, MULTI_TEST_ELF).unwrap();
    let actual = hex::encode(Digest::try_from(session.journal.unwrap().bytes).unwrap());
    assert_eq!(expected, actual);
}

#[apply(base)]
fn std_stdio(#[case] version: TestVersion) {
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
        execute_elf(version, env, STANDARD_LIB_ELF).unwrap();
    }
    assert_eq!(from_utf8(&stdout).unwrap(), expected_stdout());
    assert_eq!(from_utf8(&stderr).unwrap(), EXPECTED_STDERR);
}

#[apply(base)]
fn std_environment(#[case] version: TestVersion) {
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
    let session = execute_elf(version, env, STANDARD_LIB_ELF).unwrap();
    let actual = &session.journal.as_ref().unwrap().bytes;
    assert_eq!(
        from_utf8(actual).unwrap(),
        r"ENV_VAR1=val1
ENV_VAR2=
!ENV_VAR3
"
    );
}

#[apply(base)]
fn std_args(
    #[case] version: TestVersion,
    #[values(
        &[],
        &["grep", "-c", "foo bar", "-"])
    ]
    args: &[&str],
) {
    let args: Vec<_> = args.iter().map(|s| s.to_string()).collect();
    let env = ExecutorEnv::builder()
        .env_var("TEST_MODE", "ARGS")
        .args(&args)
        .build()
        .unwrap();
    let session = execute_elf(version, env, STANDARD_LIB_ELF).unwrap();
    let output: Vec<String> = session.journal.unwrap().decode().unwrap();
    assert_eq!(output, args,);
}

#[apply(base)]
fn std_buf_read(#[case] version: TestVersion) {
    // Host-provided input is 7 bytes, while the guest requests to read 9.
    let input = b"1234567";
    let env = ExecutorEnv::builder()
        .env_var("TEST_MODE", "BUF_READ")
        // Previously failed on anything > buf and not % 4 == 0
        // https://github.com/risc0/risc0/pull/1557
        .write(&9usize)
        .unwrap()
        .write_slice(input.as_slice())
        .build()
        .unwrap();
    let session = execute_elf(version, env, STANDARD_LIB_ELF).unwrap();
    let output = session.journal.unwrap().bytes;
    assert_eq!(output, input);
}

#[apply(base)]
fn commit_hello_world(#[case] version: TestVersion) {
    execute_elf(version, ExecutorEnv::default(), HELLO_COMMIT_ELF).unwrap();
}

#[apply(base)]
fn random(#[case] version: TestVersion) {
    multi_test(version, MultiTestSpec::DoRandom);
}

#[apply(base)]
#[should_panic(expected = "WARNING: `getrandom()` called from guest.")]
fn getrandom_panic(#[case] version: TestVersion) {
    let env = ExecutorEnv::default();
    execute_elf(version, env, RAND_ELF).unwrap();
}

#[apply(base)]
#[should_panic(expected = "Guest panicked: sys_getenv is disabled")]
fn sys_getenv_panic(#[case] version: TestVersion) {
    let env = ExecutorEnv::default();
    execute_elf(version, env, SYS_ENV_ELF).unwrap();
}

#[apply(base)]
#[should_panic(expected = "Guest panicked: sys_argc is disabled")]
fn sys_args_panic(#[case] version: TestVersion) {
    let env = ExecutorEnv::default();
    execute_elf(version, env, SYS_ARGS_ELF).unwrap();
}

#[apply(base)]
fn slice_io(#[case] version: TestVersion) {
    let run = |slice: &[u8]| {
        let env = ExecutorEnv::builder()
            .write_slice(&[slice.len() as u32])
            .write_slice(slice)
            .build()
            .unwrap();
        let session = execute_elf(version, env, SLICE_IO_ELF).unwrap();
        assert_eq!(session.journal.unwrap().bytes, slice);
    };

    run(b"");
    run(b"xyz");
    run(b"0000");
}

// Check that a compliant host will return an error on panic.
#[apply(base)]
fn panic(#[case] version: TestVersion) {
    let err = multi_test_raw(version, MultiTestSpec::Panic).err().unwrap();
    assert!(err.to_string().contains("MultiTestSpec::Panic invoked"));
}

#[apply(base)]
fn fault(#[case] version: TestVersion) {
    let err = multi_test_raw(version, MultiTestSpec::Fault).err().unwrap();
    assert!(err.to_string().contains("StoreAccessFault"));
}

#[test_log::test]
fn profiler() {
    let mut profiler = Profiler::new(MULTI_TEST_ELF, Some("multi_test.elf")).unwrap();
    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::Profiler)
        .unwrap()
        .trace_callback(&mut profiler)
        .build()
        .unwrap();
    ExecutorImpl::from_elf(env, MULTI_TEST_ELF)
        .unwrap()
        .run()
        .unwrap();

    let profile = profiler.finalize();

    // Gather up anything containing our profile_test functions.
    // If the test doesn't pass, we don't want to display the
    // whole profiling structure.
    let occurrences: Vec<_> = profile
        .iter()
        .filter(|(frames, _addr, _count)| frames.iter().any(|fr| fr.name.contains("profile_test")))
        .collect();

    assert!(
        !occurrences.is_empty(),
        "{:#?}",
        Vec::from_iter(profile.iter())
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

#[apply(base)]
fn oom(#[case] version: TestVersion) {
    let err = multi_test_raw(version, MultiTestSpec::Oom).err().unwrap();
    assert!(err.to_string().contains("Out of memory"), "{err:?}");
}

#[apply(base)]
fn memory_access(#[case] version: TestVersion) {
    let access_memory = |addr: u32| -> Result<ExitCode> {
        let env = ExecutorEnv::builder()
            .write(&MultiTestSpec::OutOfBounds)
            .unwrap()
            .write(&addr)
            .unwrap()
            .build()
            .unwrap();
        let session = execute_elf(version, env, MULTI_TEST_ELF)?;
        Ok(session.exit_code)
    };

    assert!(access_memory(0x0000_0000)
        .err()
        .unwrap()
        .to_string()
        .contains("StoreAccessFault"));

    let addr = match version {
        V1 => 0x0C00_0000,
        V2 => 0xC000_0000,
    };

    assert!(access_memory(addr)
        .err()
        .unwrap()
        .to_string()
        .contains("StoreAccessFault"));

    assert_eq!(access_memory(0x0B00_0000).unwrap(), ExitCode::Halted(0));
}

/// The post-state digest (i.e. the Merkle root of the memory state at the end
/// of the program) should be randomized on each execution to avoid potential
/// leakage of private information.
#[apply(base)]
fn post_state_digest_randomization(#[case] version: TestVersion) {
    // Run a number of iterations of a guest and confirm all have the unique post
    // state digest.
    const ITERATIONS: usize = 10;
    let post_state_digests: HashSet<Digest> = (0..ITERATIONS)
        .map(|_| {
            // Run the guest and extract the post state digest.
            let session = execute_elf(version, ExecutorEnv::default(), HELLO_COMMIT_ELF).unwrap();
            let inner = session.segments.last().unwrap().resolve().unwrap().inner;
            match version {
                V1 => inner.v1().post_state.digest(),
                V2 => inner.v2().post_digest,
            }
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

            match version {
                V1 => {
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
                        .inner
                        .v1()
                        .post_state
                        .digest()
                }
                V2 => {
                    let mut exec =
                        Executor2::from_elf(ExecutorEnv::default(), HELLO_COMMIT_ELF).unwrap();
                    // Override the default randomness syscall using crate-internal API.
                    exec.syscall_table.with_syscall(SYS_RANDOM, RiggedRandom);
                    exec.run()
                        .unwrap()
                        .segments
                        .last()
                        .unwrap()
                        .resolve()
                        .unwrap()
                        .inner
                        .v2()
                        .post_digest
                }
            }
        })
        .collect();
    assert_eq!(post_state_digests.len(), 1);
}

#[apply(base)]
fn aligned_alloc(#[case] version: TestVersion) {
    multi_test(version, MultiTestSpec::AlignedAlloc);
}

#[apply(base)]
fn alloc_zeroed(#[case] version: TestVersion) {
    multi_test(version, MultiTestSpec::AllocZeroed);
}

#[rstest]
#[case(V1)]
#[ignore]
#[case(V2)]
#[test_log::test]
#[should_panic(expected = "too small")]
fn too_many_sha(#[case] version: TestVersion) {
    let env = ExecutorEnv::builder()
        .segment_limit_po2(15) // 32K cycles
        .write(&MultiTestSpec::TooManySha)
        .unwrap()
        .build()
        .unwrap();
    execute_elf(version, env, MULTI_TEST_ELF).unwrap();
}

#[rstest]
#[should_panic(expected = "is an invalid guest address")]
#[case(V1)]
#[should_panic(expected = "LoadAccessFault")]
#[case(V2)]
#[test_log::test]
fn out_of_bounds_ecall(#[case] version: TestVersion) {
    multi_test(version, MultiTestSpec::OutOfBoundsEcall);
}

#[apply(base)]
fn sys_fork(#[case] version: TestVersion) {
    multi_test(version, MultiTestSpec::SysFork);
}

#[apply(base)]
#[should_panic(expected = "Unknown syscall")]
fn sys_fork_fork_panic(#[case] version: TestVersion) {
    multi_test(version, MultiTestSpec::SysForkFork);
}

#[apply(base)]
#[should_panic(expected = "Bad write file descriptor 3")]
fn sys_fork_journal_panic(#[case] version: TestVersion) {
    multi_test(version, MultiTestSpec::SysForkJournalPanic);
}

#[apply(base)]
fn heap_alloc(#[case] version: TestVersion) {
    let env = ExecutorEnv::builder()
        .write(&6_u32)
        .unwrap()
        .build()
        .unwrap();
    let session = execute_elf(version, env, HEAP_ELF).unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));
}

#[apply(base)]
fn heap_bug_zkvm_527(#[case] version: TestVersion) {
    let env = ExecutorEnv::builder().build().unwrap();
    let session = execute_elf(version, env, ZKVM_527_ELF).unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));
}

#[apply(base)]
fn keccak_update(#[case] version: TestVersion) {
    multi_test(version, MultiTestSpec::KeccakUpdate);
}

#[apply(base)]
fn keccak_update2(#[case] version: TestVersion) {
    let mut vars = HashMap::new();
    vars.insert("RISC0_KECCAK_PO2".to_string(), 15u32.to_string());
    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::KeccakUpdate2)
        .unwrap()
        .env_vars(vars)
        .build()
        .unwrap();
    let session = execute_elf(version, env, MULTI_TEST_ELF).unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));
    assert_eq!(
        session.pending_keccaks[0].claim_digest,
        digest!("4be4abacf05e312a566673392786c5ae69b8c7ed2b77bb2d63119e035420866c")
    );
    assert_eq!(session.pending_keccaks[0].po2, 15,);
}

#[apply(base)]
fn sha_single_keccak(#[case] version: TestVersion) {
    multi_test(version, MultiTestSpec::ShaSingleKeccak);
}

#[apply(base)]
fn sys_keccak(#[case] version: TestVersion) {
    multi_test(version, MultiTestSpec::SysKeccak);
}

#[cfg(feature = "docker")]
mod docker {
    use super::*;

    use crate::TraceEvent;

    #[test_log::test]
    fn trace() {
        let mut events: Vec<TraceEvent> = Vec::new();
        {
            let env = ExecutorEnv::builder()
                .write(&MultiTestSpec::EventTrace)
                .unwrap()
                .trace_callback(|event| {
                    events.push(event);
                    Ok(())
                })
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
            region: 1337_u32.to_le_bytes().to_vec()
        }));
    }
}

#[rstest]
#[case((0, 16, 1))]
// this should contain exactly 2 segments
#[case((16, 16, 2))]
// it's ok to run with a limit that's higher than the actual count
#[case((16, 16, 10))]
#[case((16, 15, 17))]
// This test should always fail if the last parameter is zero
#[should_panic(expected = "Session limit exceeded")]
#[case((0, 16, 0))]
#[should_panic(expected = "Session limit exceeded")]
#[case((16, 16, 1))]
#[should_panic(expected = "Session limit exceeded")]
#[case((16, 15, 2))]
#[test_log::test]
fn session_limit(
    #[case] (loop_cycles_po2, segment_limit_po2, session_count_limit): (u32, u32, u64),
    #[values(V1, V2)] version: TestVersion,
) {
    // run_session(version, params.0, params.1, params.2).unwrap();
    let session_cycles = (1 << segment_limit_po2) * session_count_limit;
    let spec = MultiTestSpec::BusyLoop {
        cycles: 1 << loop_cycles_po2,
    };
    let env = ExecutorEnv::builder()
        .write(&spec)
        .unwrap()
        .segment_limit_po2(segment_limit_po2)
        .session_limit(Some(session_cycles))
        .build()
        .unwrap();
    execute_elf(version, env, MULTI_TEST_ELF).unwrap();
}
