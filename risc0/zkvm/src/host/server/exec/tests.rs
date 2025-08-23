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

use std::{
    collections::{BTreeMap, HashSet},
    io::Cursor,
    str::from_utf8,
    sync::Mutex,
};

use anyhow::Result;
use bytes::Bytes;
use risc0_binfmt::{ExitCode, MemoryImage, PovwJobId, PovwLogId, Program, ProgramBinary};
use risc0_circuit_rv32im::TerminateState;
use risc0_zkos_v1compat::V1COMPAT_ELF;
use risc0_zkp::digest;
use risc0_zkvm_methods::{
    multi_test::{MultiTestSpec, SYS_MULTI_TEST, SYS_MULTI_TEST_WORDS},
    BLST_ELF, HEAP_ELF, HEAP_LIMITS_ELF, HELLO_COMMIT_ELF, MULTI_TEST_ELF, RAND2_ELF, RAND_ELF,
    SLICE_IO_ELF, STANDARD_LIB_ELF, SYS_ARGS_ELF, SYS_ENV_ELF, ZKVM_527_ELF,
};
use risc0_zkvm_platform::{
    fileno,
    syscall::{bigint, nr::SYS_RANDOM},
    WORD_SIZE,
};
use rstest::rstest;
use sha2::{Digest as _, Sha256};

use crate::{
    host::server::exec::{
        executor::ExecutorImpl,
        profiler::Profiler,
        syscall::{Syscall, SyscallContext},
    },
    serde::to_vec,
    sha::{Digest, Digestible},
    ExecutorEnv, Session, SimpleSegmentRef,
};

fn execute_elf(env: ExecutorEnv, elf: &[u8]) -> Result<Session> {
    let session = ExecutorImpl::from_elf(env, elf)
        .unwrap()
        .run_with_callback(|segment| Ok(Box::new(SimpleSegmentRef::new(segment))))?;
    session.log();
    Ok(session)
}

fn multi_test(spec: MultiTestSpec) {
    let session = multi_test_raw(spec).unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));
}

fn multi_test_raw(spec: MultiTestSpec) -> Result<Session> {
    let env = ExecutorEnv::builder()
        .write(&spec)
        .unwrap()
        .build()
        .unwrap();
    execute_elf(env, MULTI_TEST_ELF)
}

#[test_log::test]
fn cpp_test() {
    let session = execute_elf(ExecutorEnv::default(), BLST_ELF).unwrap();
    let message: String = session.journal.unwrap().decode().unwrap();
    assert_eq!(message.as_str(), "blst is such a blast");
}

#[rstest]
#[should_panic(expected = "too small")]
fn insufficient_segment_limit() {
    let env = ExecutorEnv::builder()
        .segment_limit_po2(13) // 8K cycles
        .write(&MultiTestSpec::DoNothing)
        .unwrap()
        .build()
        .unwrap();
    execute_elf(env, MULTI_TEST_ELF).unwrap();
}

#[test_log::test]
fn basic() {
    let program = risc0_circuit_rv32im::execute::testutil::user::basic();
    let env = ExecutorEnv::default();
    let kernel = Program::load_elf(V1COMPAT_ELF, u32::MAX).unwrap();
    let mut image = MemoryImage::with_kernel(program, kernel);
    let pre_image_id = image.image_id();

    let mut exec = ExecutorImpl::new(env, image).unwrap();
    let session = exec
        .run_with_callback(|segment| Ok(Box::new(SimpleSegmentRef::new(segment))))
        .unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));
    let segment = session.segments.first().unwrap().resolve().unwrap();

    assert_eq!(session.segments.len(), 1);
    assert_eq!(segment.inner.claim.pre_state, pre_image_id);
    assert_ne!(segment.inner.claim.post_state, pre_image_id);
    assert_eq!(segment.inner.claim.input, Digest::ZERO);
    assert_eq!(segment.inner.claim.output, Some(Digest::ZERO));
    assert_eq!(
        segment.inner.claim.terminate_state,
        Some(TerminateState::default())
    );
    assert_eq!(segment.index, 0);
}

#[test_log::test]
fn system_split_v2() {
    let program = risc0_circuit_rv32im::execute::testutil::kernel::simple_loop(200);
    let mut image = MemoryImage::new_kernel(program);
    let pre_image_id = image.image_id();

    let env = ExecutorEnv::builder()
        .segment_limit_po2(13) // 8K cycles
        .build()
        .unwrap();
    let mut exec = ExecutorImpl::new(env, image).unwrap();
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

    assert_eq!(segments[0].inner.claim.pre_state, pre_image_id);
    assert_ne!(segments[0].inner.claim.post_state, pre_image_id);
    assert_eq!(segments[0].inner.claim.input, Digest::ZERO);
    assert_eq!(segments[0].inner.claim.output, None);
    assert_eq!(segments[0].inner.claim.terminate_state, None);

    assert_eq!(
        segments[1].inner.claim.pre_state,
        segments[0].inner.claim.post_state
    );
    assert_ne!(
        segments[1].inner.claim.post_state,
        segments[1].inner.claim.pre_state
    );
    assert_eq!(segments[1].inner.claim.input, Digest::ZERO);
    assert_eq!(segments[1].inner.claim.output, Some(Digest::ZERO));
    assert_eq!(
        segments[1].inner.claim.terminate_state,
        Some(TerminateState::default())
    );

    assert_eq!(segments[0].index, 0);
    assert_eq!(segments[1].index, 1);
}

#[test_log::test]
fn libm_build() {
    multi_test(MultiTestSpec::LibM);
}

#[test_log::test]
fn poseidon2_basic() {
    multi_test(MultiTestSpec::Poseidon2Basic);
}

#[test_log::test]
fn poseidon2_continue() {
    multi_test(MultiTestSpec::Poseidon2Continue);
}

#[test_log::test]
fn poseidon2_short() {
    multi_test(MultiTestSpec::Poseidon2Short);
}

#[test_log::test]
fn poseidon2_long() {
    multi_test(MultiTestSpec::Poseidon2Long);
}

#[test_log::test]
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
    let session = execute_elf(env, MULTI_TEST_ELF).unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));
    assert_eq!(*actual.lock().unwrap(), expected[..expected.len() - 1]);
}

#[test_log::test]
fn host_syscall_words() {
    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::SyscallWords)
        .unwrap()
        .io_callback(SYS_MULTI_TEST_WORDS, Ok)
        .build()
        .unwrap();
    let session = execute_elf(env, MULTI_TEST_ELF).unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));
}

// Make sure panics in the callback get propagated correctly.
#[test_log::test]
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
    let session = execute_elf(env, MULTI_TEST_ELF).unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));
}

#[test_log::test]
fn sha_accel() {
    multi_test(MultiTestSpec::ShaConforms);
}

#[test_log::test]
fn sha_cycle_count() {
    multi_test(MultiTestSpec::ShaCycleCount);
}

#[test_log::test]
fn rsa_compat() {
    multi_test(MultiTestSpec::RsaCompat);
}

#[test_log::test]
fn bigint_accel() {
    use crate::host::server::testutils::generate_bigint_test_cases;

    let cases = generate_bigint_test_cases(10);
    for case in cases {
        println!("Running BigInt circuit test case: {case:x?}");
        let input = MultiTestSpec::BigInt {
            count: 1,
            x: case.x,
            y: case.y,
            modulus: case.modulus,
        };

        let env = ExecutorEnv::builder()
            .write(&input)
            .unwrap()
            .build()
            .unwrap();
        let session = execute_elf(env, MULTI_TEST_ELF).unwrap();
        assert_eq!(session.exit_code, ExitCode::Halted(0));
        assert_eq!(
            session.journal.unwrap().bytes.as_slice(),
            bytemuck::cast_slice::<u32, u8>(case.expected().as_slice())
        );
    }
}

#[test_log::test]
#[should_panic(expected = "IllegalInstruction")]
fn bigint_accel_mod_zero_product_too_large() {
    let input = MultiTestSpec::BigInt {
        count: 1,
        x: [u32::MAX; bigint::WIDTH_WORDS],
        y: [u32::MAX; bigint::WIDTH_WORDS],
        modulus: [0u32; bigint::WIDTH_WORDS],
    };

    let env = ExecutorEnv::builder()
        .write(&input)
        .unwrap()
        .build()
        .unwrap();
    execute_elf(env, MULTI_TEST_ELF).unwrap();
}

#[test_log::test]
fn bigint_repeat() {
    let input = MultiTestSpec::BigInt {
        count: 100,
        x: [1, 2, 3, 4, 5, 6, 7, 8],
        y: [9, 10, 11, 12, 13, 14, 15, 16],
        modulus: [17, 18, 19, 20, 21, 22, 23, 24],
    };

    let env = ExecutorEnv::builder()
        .write(&input)
        .unwrap()
        .build()
        .unwrap();
    let session = execute_elf(env, MULTI_TEST_ELF).unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));
}

const BIGINT_LEGAL_ADDR: u32 = 0x3000_0000;
const BIGINT_ILLEGAL_ADDR: u32 = 0xc000_0000;

#[rstest]
#[case(
    BIGINT_LEGAL_ADDR,
    BIGINT_LEGAL_ADDR,
    BIGINT_LEGAL_ADDR,
    BIGINT_LEGAL_ADDR
)]
#[should_panic(expected = "IllegalInstruction")]
#[case(
    BIGINT_ILLEGAL_ADDR,
    BIGINT_LEGAL_ADDR,
    BIGINT_LEGAL_ADDR,
    BIGINT_LEGAL_ADDR
)]
#[should_panic(expected = "IllegalInstruction")]
#[case(
    BIGINT_LEGAL_ADDR,
    BIGINT_ILLEGAL_ADDR,
    BIGINT_LEGAL_ADDR,
    BIGINT_LEGAL_ADDR
)]
#[should_panic(expected = "IllegalInstruction")]
#[case(
    BIGINT_LEGAL_ADDR,
    BIGINT_LEGAL_ADDR,
    BIGINT_ILLEGAL_ADDR,
    BIGINT_LEGAL_ADDR
)]
#[should_panic(expected = "IllegalInstruction")]
#[case(
    BIGINT_LEGAL_ADDR,
    BIGINT_LEGAL_ADDR,
    BIGINT_LEGAL_ADDR,
    BIGINT_ILLEGAL_ADDR
)]
#[test_log::test]
fn bigint_raw(#[case] result: u32, #[case] x: u32, #[case] y: u32, #[case] modulus: u32) {
    let input = MultiTestSpec::BigIntRaw {
        result,
        x,
        y,
        modulus,
    };
    let env = ExecutorEnv::builder()
        .write(&input)
        .unwrap()
        .build()
        .unwrap();
    let session = execute_elf(env, MULTI_TEST_ELF).unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));
}

#[test_log::test]
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
        let session = execute_elf(env, MULTI_TEST_ELF).unwrap();
        assert_eq!(session.exit_code, ExitCode::Halted(0));
    }
    assert_eq!(MSG, from_utf8(&stdout).unwrap());
}

// Tests sys_read into a buffer of bytes that may not be word aligned.
//
// To make sure we don't miss any edge cases, this tries all permutations of
// start alignment, end alignment, and 0, 1, or 2 whole words.
#[test_log::test]
fn posix_style_read() {
    const FD: u32 = 123;
    // Initial buffer to read bytes on top of.
    let buf: Vec<u8> = (b'a'..=b'z').cycle().take(8192).collect();

    // Input to read bytes from.
    let readbuf: Vec<u8> = (b'A'..=b'Z').cycle().take(8192).collect();

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
        let session = execute_elf(env, MULTI_TEST_ELF).unwrap();
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
            for nwords in [0, 1, 2, 3, 8, 16, 32, 64, 128, 256, 512] {
                pos = next_offset(pos, start_offset);
                let start = pos;
                pos += nwords * WORD_SIZE as u32;
                pos = next_offset(pos, end_offset);
                let len = pos - start;
                pos_and_len.push((pos, len));
                assert!(
                    pos + len < buf.len() as u32,
                    "Ran out of space to test writes. \
                    pos: {pos} len: {len} end: {end_offset} start = {start_offset}"
                );
                // Make sure there's at least one non-overwritten character between reads.
                pos += 1;
            }

            run(pos_and_len);
        }
    }
}

#[rstest]
#[case(0, 0, b"abcdefghijkl")]
#[case(0, 1, b"abcdefghijkl")]
#[case(0, 2, b"abcdefghijkl")]
#[case(0, 3, b"abcdefghijkl")]
#[case(0, 4, b"\0\0\0\0efghijkl")]
#[case(0, 5, b"\0\0\0\0efghijkl")]
#[case(0, 6, b"\0\0\0\0efghijkl")]
#[case(0, 7, b"\0\0\0\0efghijkl")]
#[case(1, 0, b"Abcdefghijkl")]
#[case(1, 1, b"Abcdefghijkl")]
#[case(1, 2, b"Abcdefghijkl")]
#[case(1, 3, b"A\0\0\0efghijkl")]
#[case(1, 4, b"A\0\0\0efghijkl")]
#[case(1, 5, b"A\0\0\0efghijkl")]
#[case(1, 6, b"A\0\0\0efghijkl")]
#[case(1, 7, b"A\0\0\0\0\0\0\0ijkl")]
#[case(2, 0, b"ABcdefghijkl")]
#[case(2, 1, b"ABcdefghijkl")]
#[case(2, 2, b"AB\0\0efghijkl")]
#[case(2, 3, b"AB\0\0efghijkl")]
#[case(2, 4, b"AB\0\0efghijkl")]
#[case(2, 5, b"AB\0\0efghijkl")]
#[case(2, 6, b"AB\0\0\0\0\0\0ijkl")]
#[case(2, 7, b"AB\0\0\0\0\0\0ijkl")]
#[case(3, 0, b"ABCdefghijkl")]
#[case(3, 1, b"ABC\0efghijkl")]
#[case(3, 2, b"ABC\0efghijkl")]
#[case(3, 3, b"ABC\0efghijkl")]
#[case(3, 4, b"ABC\0efghijkl")]
#[case(3, 5, b"ABC\0\0\0\0\0ijkl")]
#[case(3, 6, b"ABC\0\0\0\0\0ijkl")]
#[case(3, 7, b"ABC\0\0\0\0\0ijkl")]
#[test_log::test]
fn short_read_combinations(
    #[case] read_len: usize,
    #[case] excess_buffer: usize,
    #[case] expected: &[u8],
) {
    const FD: u32 = 123;
    // Initial buffer to read bytes on top of.
    let buf: Vec<u8> = (b'a'..=b'l').collect();
    // Input to read bytes from.
    let readbuf: Vec<u8> = (b'A'..b'L').collect();

    let buffer = read_len + excess_buffer;

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
    let session = execute_elf(env, MULTI_TEST_ELF).unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));

    let (actual, num_read): (Vec<u8>, Vec<usize>) = session.journal.unwrap().decode().unwrap();
    assert_eq!(
        [read_len].as_slice(),
        &num_read,
        "length mismatch, length {read_len} buffer: {buffer}"
    );
    assert_eq!(
        from_utf8(&actual).unwrap(),
        from_utf8(expected).unwrap(),
        "length {read_len}, buffer {buffer}"
    );
}

#[test_log::test]
fn unaligned_short_read() {
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
    let session = execute_elf(env, MULTI_TEST_ELF).unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));

    let actual: Vec<u8> = session.journal.unwrap().decode().unwrap();
    let mut expected = readbuf.to_vec();
    expected.resize(buf.len(), 0);
    assert_eq!(actual, expected, "pos and lens: {spec:?}");
}

#[test_log::test]
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
    let session = execute_elf(env, MULTI_TEST_ELF).unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));

    let actual: &[u32] = bytemuck::cast_slice(&session.journal.as_ref().unwrap().bytes);
    assert_eq!(actual, expected);
}

#[test_log::test]
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
        let session = execute_elf(env, MULTI_TEST_ELF).unwrap();
        assert_eq!(session.exit_code, ExitCode::Halted(0));
    }
    let actual: &[u32] = bytemuck::cast_slice(&stdout);
    assert_eq!(&buf, actual);
}

mod sys_verify {
    use crate::{MaybePruned, ReceiptClaim};

    use super::*;

    fn exec_hello_commit() -> Session {
        let session = execute_elf(ExecutorEnv::default(), HELLO_COMMIT_ELF).unwrap();
        assert_eq!(session.exit_code, ExitCode::Halted(0));
        session
    }

    fn exec_halt(exit_code: u8) -> Session {
        let env = ExecutorEnv::builder()
            .write(&MultiTestSpec::Halt(exit_code))
            .unwrap()
            .build()
            .unwrap();
        let session = execute_elf(env, MULTI_TEST_ELF).unwrap();
        assert_eq!(session.exit_code, ExitCode::Halted(exit_code as u32));
        session
    }

    fn exec_pause(exit_code: u8) -> Session {
        let env = ExecutorEnv::builder()
            .write(&MultiTestSpec::PauseResume(exit_code))
            .unwrap()
            .build()
            .unwrap();
        let session = execute_elf(env, MULTI_TEST_ELF).unwrap();
        assert_eq!(session.exit_code, ExitCode::Paused(exit_code as u32));
        session
    }

    #[test_log::test]
    fn sys_verify() {
        use risc0_zkvm_methods::HELLO_COMMIT_ID;

        let hello_commit_session = exec_hello_commit();

        let spec = &MultiTestSpec::SysVerify(vec![(
            HELLO_COMMIT_ID.into(),
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
        let session = execute_elf(env, MULTI_TEST_ELF).unwrap();
        assert_eq!(session.exit_code, ExitCode::Halted(0));

        // Test that it does not work when the assumption is not added.
        let env = ExecutorEnv::builder()
            .write(&spec)
            .unwrap()
            .build()
            .unwrap();
        assert!(execute_elf(env, MULTI_TEST_ELF).is_err());
    }

    #[test_log::test]
    fn sys_verify_halt_codes() {
        use risc0_zkvm_methods::MULTI_TEST_ID;

        for code in [0u8, 1, 2, 255] {
            tracing::debug!("sys_verify_pause_codes: code = {code}");
            let halt_session = exec_halt(code);

            let spec = &MultiTestSpec::SysVerify(vec![(MULTI_TEST_ID.into(), Vec::new())]);

            let env = ExecutorEnv::builder()
                .write(&spec)
                .unwrap()
                .add_assumption(halt_session.claim().unwrap())
                .build()
                .unwrap();
            let session = execute_elf(env, MULTI_TEST_ELF);

            if code == 0 {
                assert_eq!(session.unwrap().exit_code, ExitCode::Halted(0));
            } else {
                assert!(session.is_err());
            }
        }
    }

    #[test_log::test]
    fn sys_verify_integrity() {
        let hello_commit_session = exec_hello_commit();
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
        let session = execute_elf(env, MULTI_TEST_ELF).unwrap();
        assert_eq!(session.exit_code, ExitCode::Halted(0));

        // Test that it does not work when the assumption is not added.
        let env = ExecutorEnv::builder()
            .write(&spec)
            .unwrap()
            .build()
            .unwrap();
        assert!(execute_elf(env, MULTI_TEST_ELF).is_err());
    }

    #[test_log::test]
    fn sys_verify_integrity_halt_codes() {
        for code in [0u8, 1, 2, 255] {
            tracing::debug!("sys_verify_pause_codes: code = {code}");
            let halt_session = exec_halt(code);
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
            let session = execute_elf(env, MULTI_TEST_ELF).unwrap();
            assert_eq!(session.exit_code, ExitCode::Halted(0));
        }
    }

    #[test_log::test]
    fn sys_verify_integrity_pause_codes() {
        for code in [0u8, 1, 2, 255] {
            tracing::debug!("sys_verify_halt_codes: code = {code}");
            let pause_session = exec_pause(code);
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
            let session = execute_elf(env, MULTI_TEST_ELF).unwrap();
            assert_eq!(session.exit_code, ExitCode::Halted(0));
        }
    }

    #[test_log::test]
    fn sys_verify_integrity_pruned_claim() {
        let hello_commit_session = exec_hello_commit();
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
        let err = execute_elf(env, MULTI_TEST_ELF).map(|_| ()).unwrap_err();

        tracing::debug!("err: {err}");
        assert!(err
            .to_string()
            .contains("env::verify_integrity returned error"));
    }
}

#[test_log::test]
fn large_sha() {
    let data = vec![0u8; 100_000];
    let expected = hex::encode(Sha256::digest(&data));
    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::ShaDigest { data })
        .unwrap()
        .build()
        .unwrap();
    let session = execute_elf(env, MULTI_TEST_ELF).unwrap();
    let actual = hex::encode(Digest::try_from(session.journal.unwrap().bytes).unwrap());
    assert_eq!(expected, actual);
}

#[test_log::test]
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
        execute_elf(env, STANDARD_LIB_ELF).unwrap();
    }
    assert_eq!(from_utf8(&stdout).unwrap(), expected_stdout());
    assert_eq!(from_utf8(&stderr).unwrap(), EXPECTED_STDERR);
}

#[test_log::test]
fn std_environment() {
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
    let session = execute_elf(env, STANDARD_LIB_ELF).unwrap();
    let actual = &session.journal.as_ref().unwrap().bytes;
    assert_eq!(
        from_utf8(actual).unwrap(),
        r"ENV_VAR1=val1
ENV_VAR2=
!ENV_VAR3
"
    );
}

#[rstest]
#[test_log::test]
fn std_args(
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
    let session = execute_elf(env, STANDARD_LIB_ELF).unwrap();
    let output: Vec<String> = session.journal.unwrap().decode().unwrap();
    assert_eq!(output, args,);
}

#[test_log::test]
fn std_buf_read() {
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
    let session = execute_elf(env, STANDARD_LIB_ELF).unwrap();
    let output = session.journal.unwrap().bytes;
    assert_eq!(output, input);
}

#[test_log::test]
fn commit_hello_world() {
    execute_elf(ExecutorEnv::default(), HELLO_COMMIT_ELF).unwrap();
}

#[test_log::test]
fn random() {
    multi_test(MultiTestSpec::DoRandom);
}

#[test_log::test]
#[should_panic(expected = "WARNING: `getrandom()` called from guest.")]
fn getrandom_panic() {
    let env = ExecutorEnv::default();
    execute_elf(env, RAND_ELF).unwrap();
}

#[test_log::test]
fn getrandom2() {
    let env = ExecutorEnv::default();
    execute_elf(env, RAND2_ELF).unwrap();
}

#[test_log::test]
#[should_panic(expected = "Guest panicked: sys_getenv is disabled")]
fn sys_getenv_panic() {
    let env = ExecutorEnv::default();
    execute_elf(env, SYS_ENV_ELF).unwrap();
}

#[test_log::test]
#[should_panic(expected = "Guest panicked: sys_argc is disabled")]
fn sys_args_panic() {
    let env = ExecutorEnv::default();
    execute_elf(env, SYS_ARGS_ELF).unwrap();
}

#[test_log::test]
fn slice_io() {
    let run = |slice: &[u8]| {
        let env = ExecutorEnv::builder()
            .write_slice(&[slice.len() as u32])
            .write_slice(slice)
            .build()
            .unwrap();
        let session = execute_elf(env, SLICE_IO_ELF).unwrap();
        assert_eq!(session.journal.unwrap().bytes, slice);
    };

    run(b"");
    run(b"xyz");
    run(b"0000");
}

// Check that a compliant host will return an error on panic.
#[test_log::test]
fn panic() {
    let err = multi_test_raw(MultiTestSpec::Panic).err().unwrap();
    assert!(err.to_string().contains("MultiTestSpec::Panic invoked"));
}

#[test_log::test]
fn fault() {
    let err = multi_test_raw(MultiTestSpec::Fault).err().unwrap();
    assert!(err.to_string().contains("StoreAccessFault"));
}

#[test_log::test]
fn profiler() {
    let binary = ProgramBinary::decode(MULTI_TEST_ELF).unwrap();
    let mut profiler = Profiler::new(
        &binary,
        Some("multi_test.elf"),
        true, /* enable_inline_functions */
    )
    .unwrap();
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

    let test_samples: Vec<_> = profile
        .iter()
        .filter(|sample| {
            sample
                .frames
                .iter()
                .any(|fr| fr.frame.name.contains("profile_test"))
                && sample.frames[0].frame.name != "[PageIn]"
                && sample.frames[0].frame.name != "[PageOut]"
        })
        .collect();

    let mut named_stacks_and_counts = BTreeMap::new();

    for sample in &test_samples {
        let frames = Vec::from_iter(sample.frames.iter().map(|fr| fr.frame.name.clone()));
        *named_stacks_and_counts.entry(frames).or_default() += sample.count;
    }

    // Check the stacks
    assert_eq!(
        Vec::from_iter(named_stacks_and_counts.into_iter()),
        vec![
            (
                vec![
                    "multi_test::profiler::profile_test_func1".into(),
                    "multi_test::main".into(),
                    "main".into(),
                    "__start".into()
                ],
                2 // auicpc + jr
            ),
            (
                vec![
                    "multi_test::profiler::profile_test_func2".into(),
                    "multi_test::profiler::profile_test_func1".into(),
                    "multi_test::main".into(),
                    "main".into(),
                    "__start".into(),
                ],
                1 // nop
            ),
            (
                vec![
                    "multi_test::profiler::profile_test_func3".into(),
                    "multi_test::profiler::profile_test_func1".into(),
                    "multi_test::main".into(),
                    "main".into(),
                    "__start".into(),
                ],
                1 // nop
            ),
            (
                vec![
                    "multi_test::profiler::profile_test_func3".into(),
                    "multi_test::profiler::profile_test_func5".into(),
                    "multi_test::profiler::profile_test_func1".into(),
                    "multi_test::main".into(),
                    "main".into(),
                    "__start".into(),
                ],
                10 // nop * 10
            ),
            (
                vec![
                    "multi_test::profiler::profile_test_func4".into(),
                    "multi_test::profiler::profile_test_func1".into(),
                    "multi_test::main".into(),
                    "main".into(),
                    "__start".into(),
                ],
                4 // la, jr, nop
            ),
            (
                vec![
                    "multi_test::profiler::profile_test_func5".into(),
                    "multi_test::profiler::profile_test_func1".into(),
                    "multi_test::main".into(),
                    "main".into(),
                    "__start".into(),
                ],
                1 // ret
            ),
        ]
    );

    // Check the file names and line numbers
    for sample in &test_samples {
        for frame in &sample.frames {
            let frame = &frame.frame;
            if frame.name.contains("profile_test_func") {
                assert!(
                    frame
                        .filename
                        .ends_with("/zkvm/methods/guest/src/bin/multi_test/profiler.rs"),
                    "{}",
                    frame.filename
                );
                assert!(frame.lineno != 0);
            }
        }
    }

    let program = Program::load_elf(binary.user_elf, u32::MAX).unwrap();

    // Check that the addresses for these two functions point to the right place
    for func_name in [
        "multi_test::profiler::profile_test_func2",
        "multi_test::profiler::profile_test_func3",
    ] {
        let test_func = test_samples
            .iter()
            .find(|sample| sample.frames[0].frame.name == func_name)
            .unwrap();

        let addr = test_func.frames[0].address;
        let inst = program
            .read_u32(&(addr as u32))
            .unwrap_or_else(|| panic!("0x{addr:x} found in elf"));

        // check its nop
        assert_eq!(inst, 0x00_00_00_13, "found 0x{inst:08x} instead of nop");
    }
}

#[test_log::test]
fn oom() {
    let err = multi_test_raw(MultiTestSpec::Oom).err().unwrap();
    assert!(err.to_string().contains("Out of memory"), "{err:?}");
}

#[rstest]
#[should_panic(expected = "Guest panicked: Out of memory!")]
#[case("heap_overflow_via_alloc")]
#[should_panic(expected = "Guest panicked: Out of memory!")]
#[case("heap_overflow_via_sys_alloc_aligned")]
#[test_log::test]
fn heap_overflow(#[case] name: &str) {
    let env = ExecutorEnv::builder()
        .write(&name)
        .unwrap()
        .build()
        .unwrap();

    execute_elf(env, HEAP_LIMITS_ELF).unwrap();
}

#[test_log::test]
fn memory_access() {
    let access_memory = |addr: u32| -> Result<ExitCode> {
        let env = ExecutorEnv::builder()
            .write(&MultiTestSpec::OutOfBounds)
            .unwrap()
            .write(&addr)
            .unwrap()
            .build()
            .unwrap();
        let session = execute_elf(env, MULTI_TEST_ELF)?;
        Ok(session.exit_code)
    };

    assert!(access_memory(0x0000_0000)
        .err()
        .unwrap()
        .to_string()
        .contains("StoreAccessFault"));

    let addr = 0xC000_0000;
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
#[test_log::test]
fn post_state_digest_randomization() {
    // Run a number of iterations of a guest and confirm all have the unique post
    // state digest.
    const ITERATIONS: usize = 10;
    let post_state_digests: HashSet<Digest> = (0..ITERATIONS)
        .map(|_| {
            // Run the guest and extract the post state digest.
            let session = execute_elf(ExecutorEnv::default(), HELLO_COMMIT_ELF).unwrap();
            let inner = session.segments.last().unwrap().resolve().unwrap().inner;
            inner.claim.post_state
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
                .inner
                .claim
                .post_state
        })
        .collect();
    assert_eq!(post_state_digests.len(), 1);
}

#[test_log::test]
fn aligned_alloc() {
    multi_test(MultiTestSpec::AlignedAlloc);
}

#[test_log::test]
fn alloc_zeroed() {
    multi_test(MultiTestSpec::AllocZeroed);
}

#[rstest]
#[should_panic(expected = "LoadAccessFault")]
#[test_log::test]
fn out_of_bounds_ecall() {
    multi_test(MultiTestSpec::OutOfBoundsEcall);
}

#[ignore]
#[test_log::test]
fn sys_fork() {
    multi_test(MultiTestSpec::SysFork);
}

#[ignore]
#[test_log::test]
#[should_panic(expected = "Unknown syscall")]
fn sys_fork_fork_panic() {
    multi_test(MultiTestSpec::SysForkFork);
}

#[ignore]
#[test_log::test]
#[should_panic(expected = "Bad write file descriptor 3")]
fn sys_fork_journal_panic() {
    multi_test(MultiTestSpec::SysForkJournalPanic);
}

#[test_log::test]
fn heap_alloc() {
    let env = ExecutorEnv::builder()
        .write(&6_u32)
        .unwrap()
        .env_var("ALL_FORKS", "testing")
        .build()
        .unwrap();
    let session = execute_elf(env, HEAP_ELF).unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));
}

#[test_log::test]
fn heap_bug_zkvm_527() {
    let env = ExecutorEnv::builder().build().unwrap();
    let session = execute_elf(env, ZKVM_527_ELF).unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));
}

#[test_log::test]
fn keccak_update() {
    multi_test(MultiTestSpec::KeccakUpdate);
}

#[test_log::test]
fn keccak_update2() {
    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::KeccakUpdate2)
        .unwrap()
        .keccak_max_po2(15)
        .unwrap()
        .build()
        .unwrap();
    let session = execute_elf(env, MULTI_TEST_ELF).unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));
    assert_eq!(
        session.pending_keccaks[0].claim_digest,
        digest!("4be4abacf05e312a566673392786c5ae69b8c7ed2b77bb2d63119e035420866c")
    );
    assert_eq!(session.pending_keccaks[0].po2, 15,);
}

#[test_log::test]
fn sha_single_keccak() {
    multi_test(MultiTestSpec::ShaSingleKeccak);
}

#[test_log::test]
fn sys_keccak() {
    multi_test(MultiTestSpec::SysKeccak);
}

#[cfg(feature = "docker")]
mod docker {
    use super::*;

    use crate::TraceEvent;

    #[ignore]
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
    execute_elf(env, MULTI_TEST_ELF).unwrap();
}

#[test_log::test]
fn povw_nonce_assignment() {
    let spec = MultiTestSpec::BusyLoop { cycles: 1 << 18 };
    let povw_job_id = PovwJobId {
        log: PovwLogId::from(0x202ce_u64),
        job: 42,
    };
    let env = ExecutorEnv::builder()
        .write(&spec)
        .unwrap()
        .segment_limit_po2(17)
        .povw(povw_job_id)
        .build()
        .unwrap();
    let session = execute_elf(env, MULTI_TEST_ELF).unwrap();
    for (i, segment_ref) in session.segments.into_iter().enumerate() {
        let segment = segment_ref.resolve().unwrap();
        assert_eq!(segment.inner.povw_nonce, Some(povw_job_id.nonce(i as u32)));
    }
}

#[test_log::test]
fn povw_nonce_default_assignment() {
    let spec = MultiTestSpec::BusyLoop { cycles: 1 << 18 };
    let env = ExecutorEnv::builder()
        .write(&spec)
        .unwrap()
        .segment_limit_po2(17)
        .build()
        .unwrap();
    let session = execute_elf(env, MULTI_TEST_ELF).unwrap();
    // If no PoVW work information is set in the ExecutorEnv, the povw_nonce should be None.
    for segment_ref in session.segments.into_iter() {
        let segment = segment_ref.resolve().unwrap();
        assert_eq!(segment.inner.povw_nonce, None);
    }
}
