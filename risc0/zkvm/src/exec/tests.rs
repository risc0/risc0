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

fn init() {
    let _ = env_logger::builder()
        .format_timestamp_millis()
        .is_test(true)
        .try_init();
}

#[test]
fn system_split() {
    init();

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
#[test_log::test]
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

#[test_log::test]
fn sha_accel() {
    let input = to_vec(&MultiTestSpec::ShaConforms).unwrap();
    let env = ExecutorEnv::builder().add_input(&input).build();
    let mut exec = Executor::from_elf(env, MULTI_TEST_ELF).unwrap();
    exec.run().unwrap();
}

#[test_log::test]
fn sha_cycle_count() {
    let input = to_vec(&MultiTestSpec::ShaCycleCount).unwrap();
    let env = ExecutorEnv::builder().add_input(&input).build();
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
        let env = ExecutorEnv::builder()
            .read_fd(FD, MSG.as_bytes())
            .stdin(bytemuck::cast_slice(&spec))
            .stdout(&mut stdout)
            .build();
        let mut exec = Executor::from_elf(env, MULTI_TEST_ELF).unwrap();
        exec.run().unwrap();
    }
    assert_eq!(MSG, core::str::from_utf8(&stdout).unwrap());
}

// #[cfg(feature = "profiler")]
// #[test]
// fn profiler() {
//     use crate::{
//         binfmt::elf::Program,
//         prove::profiler::{Frame, Profiler},
//     };

//     let mut prof = Profiler::new("multi_test.elf", MULTI_TEST_ELF).unwrap();
//     {
//         let opts = ProverOpts::default()
//             .with_skip_seal(true)
//             .with_trace_callback(prof.make_trace_callback());
//         let mut prover = Prover::new_with_opts(MULTI_TEST_ELF,
// opts).unwrap();         prover.add_input_u32_slice(&to_vec(&
// MultiTestSpec::Profiler).unwrap());         prover.run().unwrap();
//     }

//     prof.finalize();

//     // Gather up anything containing our profile_test functions.
//     // If the test doesn't pass, we don't want to display the
//     // whole profiling structure.
//     let occurences: Vec<_> = prof
//         .iter()
//         .filter(|(frames, _addr, _count)| frames.iter().any(|fr|
// fr.name.contains("profile_test")))         .collect();

//     assert!(!occurences.is_empty(), "{:#?}", Vec::from_iter(prof.iter()));

//     let elf_mem = Program::load_elf(MULTI_TEST_ELF, u32::MAX).unwrap().image;

//     assert!(
//         occurences.iter().any(|(fr, addr, _count)| {
//             match fr.as_slice() {
//                 [fr1 @ Frame {
//                     name: name1,
//                     filename: fn1,
//                     ..
//                 }, fr2 @ Frame {
//                     name: name2,
//                     filename: fn2,
//                     ..
//                 }] => {
//                     println!("Inspecting frames:\n{fr1:?}\n{fr2:?}\n");
//                     if name1 != "profile_test_func2" || name2 !=
// "profile_test_func1" {                         println!("Names did not match:
// {}, {}", name1, name2);                         return false;
//                     }
//                     if !fn1.ends_with("multi_test.rs") ||
// !fn2.ends_with("multi_test.rs") {                         println!("Filenames
// did not match: {}, {}", fn1, fn2);                         return false;
//                     }
//                     // Check to make sure we hit the "nop" instruction
//                     match elf_mem.get(&(*addr as u32)) {
//                         None => {
//                             println!("Addr {addr} not present in elf");
//                             return false;
//                         }
//                         Some(0x00_00_00_13) => (),
//                         Some(inst) => {
//                             println!("Looking for 'nop'; got 0x{inst:08x}");
//                             return false;
//                         }
//                     }

//                     // All checks passed; this is the occurence we were
// looking for.                     true
//                 }
//                 _ => {
//                     println!("{:#?}", fr);
//                     false
//                 }
//             }
//         }),
//         "{:#?}",
//         occurences
//     );
// }

// #[test]
// fn trace() {
//     let mut events: Vec<TraceEvent> = Vec::new();
//     {
//         let opts = ProverOpts::default()
//             .with_skip_seal(true)
//             .with_trace_callback(|event| Ok(events.push(event)));
//         let mut prover = Prover::new_with_opts(MULTI_TEST_ELF,
// opts).unwrap();         prover.add_input_u32_slice(&to_vec(&
// MultiTestSpec::EventTrace).unwrap());

//         prover.run().unwrap();
//     }
//     let occurances = events
//         .windows(4)
//         .filter_map(|window| {
//             if let &[TraceEvent::InstructionStart {
//                 // li x5, 1337
//                 cycle: cycle1,
//                 pc: pc1,
//             }, TraceEvent::RegisterSet {
//                 reg: 5,
//                 value: 1337,
//             }, TraceEvent::InstructionStart {
//                 // sw x5, 548(zero)
//                 cycle: cycle2,
//                 pc: pc2,
//             }, TraceEvent::RegisterSet {
//                 reg: 6,
//                 value: 0x08000000,
//             }] = window
//             {
//                 assert_eq!(cycle1 + 1, cycle2, "li should take 1 cycles:
// {:#?}", window);                 assert_eq!(
//                     pc1 + WORD_SIZE as u32,
//                     pc2,
//                     "program counter should advance one word: {:#?}",
//                     window
//                 );
//                 Some(())
//             } else {
//                 None
//             }
//         })
//         .count();
//     assert_eq!(occurances, 1, "trace events: {:#?}", &events);
//     assert!(events.contains(&TraceEvent::MemorySet {
//         addr: 0x08000224,
//         value: 1337
//     }));
// }

// #[test]
// #[cfg_attr(feature = "insecure_skip_seal", ignore)]
// #[cfg_attr(feature = "cuda", serial)]
// fn posix_style_read() {
//     // Tests sys_read into a buffer of bytes that may not be word
//     // aligned.  To make sure we don't miss any edge cases, this tries
//     // all permutations of start alignment, end alignment, and 0, 1,
//     // or 2 whole words.

//     // Initial buffer to read bytes on top of.
//     let orig: Vec<u8> = (b'a'..b'z')
//         .chain(b'0'..b'9')
//         .chain(b"!@#$%^&*()".iter().cloned())
//         .collect();
//     // Input to read bytes from.
//     let readbuf: Vec<u8> = (b'A'..b'Z').collect();

//     let run = |pos_and_len: Vec<(u32, u32)>| {
//         let mut expected = orig.to_vec();

//         let mut expected_readbuf = readbuf.as_slice();
//         for (pos, len) in pos_and_len.iter() {
//             let pos = *pos as usize;
//             let len = *len as usize;

//             let this_read;
//             (this_read, expected_readbuf) = expected_readbuf.split_at(len);
//             expected[pos..pos + len].clone_from_slice(this_read);
//         }

//         let opts = ProverOpts::default()
//             .with_skip_seal(true)
//             .with_read_fd(123, readbuf.as_slice());

//         let mut prover = Prover::new_with_opts(MULTI_TEST_ELF,
// opts).unwrap();         prover.add_input_u32_slice(
//             &to_vec(&MultiTestSpec::SysRead {
//                 fd: 123,
//                 orig: orig.to_vec(),
//                 pos_and_len: pos_and_len.clone(),
//             })
//             .unwrap(),
//         );
//         let receipt = prover.run().unwrap();

//         let actual: Vec<u8> = from_slice(&receipt.journal).unwrap();
//         assert_eq!(
//             std::str::from_utf8(&actual).unwrap(),
//             std::str::from_utf8(&expected).unwrap(),
//             "pos and lens: {pos_and_len:?}"
//         );
//     };

//     fn next_offset(mut pos: u32, offset: u32) -> u32 {
//         while (pos % WORD_SIZE as u32) != offset {
//             pos += 1;
//         }
//         pos
//     }

//     for start_offset in 0..WORD_SIZE as u32 {
//         for end_offset in 0..WORD_SIZE as u32 {
//             let mut pos = 0;
//             let mut pos_and_len: Vec<(u32, u32)> = Vec::new();

//             // Make up a bunch of reads to overwrite parts of the buffer.
//             for nwords in 0..3 {
//                 pos = next_offset(pos, start_offset);
//                 let start = pos;
//                 pos += nwords * WORD_SIZE as u32;
//                 pos = next_offset(pos, end_offset);
//                 let len = pos - start;
//                 pos_and_len.push((pos, len));
//                 assert!(
//                     pos + len < orig.len() as u32,
//                     "Ran out of space to test writes. pos: {pos} len: {len}
// end: {end_offset} start = {start_offset}"                 );
//                 // Make sure there's at least one non-overwritten character
// between reads.                 pos += 1;
//             }

//             run(pos_and_len);
//         }
//     }
// }

// #[test]
// #[cfg_attr(feature = "insecure_skip_seal", ignore)]
// #[cfg_attr(feature = "cuda", serial)]
// fn environment() {
//     let opts = ProverOpts::default()
//         .with_env_var("TEST_MODE", "ENV_VARS")
//         .with_env_var("ENV_VAR1", "val1")
//         .with_env_var("ENV_VAR2", "")
//         .with_read_fd(
//             fileno::STDIN,
//             Cursor::new(
//                 r"ENV_VAR1
// ENV_VAR2
// ENV_VAR3",
//             ),
//         );
//     let mut prover = Prover::new_with_opts(STANDARD_LIB_ELF, opts).unwrap();
//     let receipt = prover.run().unwrap();
//     let actual = receipt.journal.as_slice();
//     assert_eq!(
//         from_utf8(actual).unwrap(),
//         r"ENV_VAR1=val1
// ENV_VAR2=
// !ENV_VAR3
// "
//     );
// }

// #[test]
// #[cfg_attr(feature = "insecure_skip_seal", ignore)]
// #[cfg_attr(feature = "cuda", serial)]
// fn commit_hello_world() {
//     let mut prover = Prover::new(HELLO_COMMIT_ELF).unwrap();
//     prover.run().unwrap();
// }

// #[test]
// #[cfg_attr(feature = "insecure_skip_seal", ignore)]
// #[cfg_attr(feature = "cuda", serial)]
// fn do_random() {
//     let mut prover = Prover::new(MULTI_TEST_ELF).unwrap();
//     prover.add_input_u32_slice(&to_vec(&MultiTestSpec::DoRandom).unwrap());
//     prover.run().unwrap();
// }

// #[test]
// #[cfg_attr(feature = "insecure_skip_seal", ignore)]
// #[cfg_attr(feature = "cuda", serial)]
// fn slice_io() {
//     let run = |slice: &[u8]| {
//         let mut prover = Prover::new(SLICE_IO_ELF).unwrap();
//         prover.add_input_u32_slice(&[slice.len() as u32]);
//         prover.add_input_u8_slice(slice);
//         let receipt = prover.run().unwrap();
//         assert_eq!(receipt.journal, slice);
//     };

//     run(b"");
//     run(b"xyz");
//     run(b"0000");
// }

// #[test]
// #[cfg_attr(feature = "cuda", serial)]
// fn fail() {
//     // Check that a compliant host will fault.
//     let mut prover = Prover::new(MULTI_TEST_ELF).unwrap();
//     prover.add_input_u32_slice(&to_vec(&MultiTestSpec::Fail).unwrap());

//     assert!(unwrap_err(prover.run())
//         .to_string()
//         .contains("MultiTestSpec::Fail invoked"));
// }

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

            let env = ExecutorEnv::default();
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
