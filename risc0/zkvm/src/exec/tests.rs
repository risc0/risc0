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

use std::{collections::BTreeMap, sync::Mutex};

use risc0_zkvm_methods::{
    multi_test::{MultiTestSpec, SYS_MULTI_TEST},
    MULTI_TEST_ELF,
};
use risc0_zkvm_platform::{PAGE_SIZE, WORD_SIZE};

use super::{Executor, ExecutorEnv};
use crate::{serde::to_vec, ExitCode, MemoryImage, Program};

#[test_log::test]
fn basic() {
    let env = ExecutorEnv::default().build();
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

fn init() {
    let _ = env_logger::builder()
        .format_timestamp_millis()
        .is_test(true)
        .try_init();
}

#[test]
fn system_split() {
    init();

    let entry = 0x4000_u32;
    let env = ExecutorEnv::default()
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
    assert_eq!(session.segments[0].exit_code, ExitCode::SystemSplit);
    assert_eq!(session.segments[0].pre_image.get_root(), pre_image_id);
    assert_ne!(session.segments[0].post_image_id, pre_image_id);
    assert_eq!(session.segments[1].exit_code, ExitCode::Halted(0));
    assert_eq!(
        session.segments[1].pre_image.get_root(),
        session.segments[0].post_image_id
    );
}

#[test_log::test]
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
    let env = ExecutorEnv::default()
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
#[test_log::test]
#[should_panic(expected = "I am panicking from here!")]
fn host_syscall_callback_panic() {
    let input = to_vec(&MultiTestSpec::Syscall { count: 5 }).unwrap();
    let env = ExecutorEnv::default()
        .add_input(&input)
        .io_callback(SYS_MULTI_TEST, |_buf: &[u8]| -> Vec<u8> {
            panic!("I am panicking from here!");
        })
        .build();
    let mut exec = Executor::from_elf(env, MULTI_TEST_ELF).unwrap();
    exec.run().unwrap();
}

#[test_log::test]
fn sha_accel() {
    let input = to_vec(&MultiTestSpec::ShaConforms).unwrap();
    let env = ExecutorEnv::default().add_input(&input).build();
    let mut exec = Executor::from_elf(env, MULTI_TEST_ELF).unwrap();
    exec.run().unwrap();
}

#[test_log::test]
fn sha_cycle_count() {
    let input = to_vec(&MultiTestSpec::ShaCycleCount).unwrap();
    let env = ExecutorEnv::default().add_input(&input).build();
    let mut exec = Executor::from_elf(env, MULTI_TEST_ELF).unwrap();
    exec.run().unwrap();
}

#[test_log::test]
fn stdio() {
    const MSG: &str = "Hello world!  This is a test of standard input and output.";
    const FD: u32 = 123;
    let spec = to_vec(&MultiTestSpec::CopyToStdout { fd: FD }).unwrap();
    let mut stdout: Vec<u8> = Vec::new();
    {
        let env = ExecutorEnv::default()
            .read_fd(FD, MSG.as_bytes())
            .stdin(bytemuck::cast_slice(&spec))
            .stdout(&mut stdout)
            .build();
        let mut exec = Executor::from_elf(env, MULTI_TEST_ELF).unwrap();
        exec.run().unwrap();
    }
    assert_eq!(MSG, core::str::from_utf8(&stdout).unwrap());
}

// These tests come from:
// https://github.com/riscv-software-src/riscv-tests
// They were built using the toolchain from:
// https://github.com/risc0/toolchain/releases/tag/2022.03.25
mod riscv {
    use crate::{Executor, ExecutorEnv, MemoryImage, Program};

    fn run_test(test_name: &str) {
        use std::io::Read;

        use flate2::read::GzDecoder;
        use risc0_zkvm_platform::{memory::MEM_SIZE, PAGE_SIZE};
        use tar::Archive;

        let bytes = include_bytes!("../testdata/riscv-tests.tgz");
        let gz = GzDecoder::new(&bytes[..]);
        let mut tar = Archive::new(gz);
        for entry in tar.entries().unwrap() {
            let mut entry = entry.unwrap();
            if !entry.header().entry_type().is_file() {
                continue;
            }
            let path = entry.path().unwrap();
            let filename = path.file_name().unwrap().to_str().unwrap();
            if filename != test_name {
                continue;
            }
            let mut elf = Vec::new();
            entry.read_to_end(&mut elf).unwrap();

            let program = Program::load_elf(elf.as_slice(), MEM_SIZE as u32).unwrap();
            let image = MemoryImage::new(&program, PAGE_SIZE as u32);

            let env = ExecutorEnv::default().build();
            let mut exec = Executor::new(env, image, program.entry);
            exec.run().unwrap();
        }
    }

    macro_rules! test_case {
        ($func_name:ident) => {
            #[test_log::test]
            #[cfg_attr(feature = "cuda", serial_test::serial)]
            fn $func_name() {
                run_test(stringify!($func_name));
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
