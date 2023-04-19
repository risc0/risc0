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

use super::{Executor, ExecutorEnv};
use crate::{
    serde::{from_slice, to_vec},
    ExitCode, MemoryImage, Program,
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
    let image = MemoryImage::new(&program, PAGE_SIZE as u32);
    let pre_image_id = image.get_root();

    let mut exec = Executor::new(env, image, program.entry);
    let session = exec.run().unwrap();

    assert_eq!(session.segments.len(), 1);
    assert_eq!(session.segments[0].exit_code, ExitCode::Halted(0));
    assert_eq!(session.segments[0].pre_image.get_root(), pre_image_id);
    assert_ne!(session.segments[0].post_image_id, pre_image_id);
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
    image.insert(pc, 0x00000073); // ecall(halt)

    let program = Program { entry, image };
    let image = MemoryImage::new(&program, PAGE_SIZE as u32);
    let pre_image_id = image.get_root();

    let mut exec = Executor::new(env, image, program.entry);
    let session = exec.run().unwrap();

    assert_eq!(session.segments.len(), 2);
    assert!(std::matches!(
        session.segments[0].exit_code,
        ExitCode::SystemSplit(_)
    ));
    assert_eq!(session.segments[0].pre_image.get_root(), pre_image_id);
    assert_ne!(session.segments[0].post_image_id, pre_image_id);
    assert_eq!(session.segments[1].exit_code, ExitCode::Halted(0));
    assert_eq!(
        session.segments[1].pre_image.get_root(),
        session.segments[0].post_image_id
    );
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
