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

use std::rc::Rc;

use anyhow::Result;
use risc0_circuit_rv32im::cpu::CpuCircuitHal;
use risc0_zkp::{
    core::{digest::Digest, hash::blake2b::Blake2bCpuHashSuite},
    hal::cpu::CpuHal,
    verify::VerificationError,
};
use risc0_zkvm_methods::{multi_test::MultiTestSpec, MULTI_TEST_ELF, MULTI_TEST_ID};
use risc0_zkvm_platform::{memory, WORD_SIZE};
use serial_test::serial;
use test_log::test;

use super::{get_prover_server, HalPair, ProverImpl};
use crate::{
    host::{server::testutils, CIRCUIT},
    serde::{from_slice, to_vec},
    Executor, ExecutorEnv, ExitCode, ProverOpts, ProverServer, Receipt,
};

fn prove_nothing(hashfn: &str) -> Result<Receipt> {
    let input = to_vec(&MultiTestSpec::DoNothing).unwrap();
    let env = ExecutorEnv::builder().add_input(&input).build().unwrap();
    let opts = ProverOpts {
        hashfn: hashfn.to_string(),
    };
    get_prover_server(&opts)
        .unwrap()
        .prove_elf(env, MULTI_TEST_ELF)
}

#[test]
#[cfg_attr(feature = "cuda", serial)]
fn hashfn_poseidon() {
    prove_nothing("poseidon").unwrap();
}

#[test]
fn hashfn_blake2b() {
    let hal_pair = HalPair {
        hal: Rc::new(CpuHal::new(Blake2bCpuHashSuite::new_suite())),
        circuit_hal: Rc::new(CpuCircuitHal::new(&CIRCUIT)),
    };
    let input = to_vec(&MultiTestSpec::DoNothing).unwrap();
    let env = ExecutorEnv::builder().add_input(&input).build().unwrap();
    let prover = ProverImpl::new("cpu:blake2b", hal_pair);
    prover.prove_elf(env, MULTI_TEST_ELF).unwrap();
}

#[test]
#[cfg_attr(feature = "cuda", serial)]
fn receipt_serde() {
    let receipt = prove_nothing("sha-256").unwrap();
    let encoded: Vec<u32> = to_vec(&receipt).unwrap();
    let decoded: Receipt = from_slice(&encoded).unwrap();
    assert_eq!(decoded, receipt);
    decoded.verify(MULTI_TEST_ID).unwrap();
}

#[test]
#[cfg_attr(feature = "cuda", serial)]
fn check_image_id() {
    let receipt = prove_nothing("sha-256").unwrap();
    let mut image_id: Digest = MULTI_TEST_ID.into();
    for word in image_id.as_mut_words() {
        *word = word.wrapping_add(1);
    }
    assert_eq!(
        receipt.verify(image_id).unwrap_err(),
        VerificationError::ImageVerificationError
    );
}

#[test]
#[serial]
fn sha_basics() {
    fn run_sha(msg: &str) -> String {
        let input = to_vec(&MultiTestSpec::ShaDigest { data: msg.into() }).unwrap();
        let env = ExecutorEnv::builder().add_input(&input).build().unwrap();
        let mut exec = Executor::from_elf(env, MULTI_TEST_ELF).unwrap();
        let session = exec.run().unwrap();
        let receipt = session.prove().unwrap();
        hex::encode(Digest::try_from(receipt.journal).unwrap())
    }

    assert_eq!(
        run_sha(""),
        "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"
    );
    assert_eq!(
        run_sha("a"),
        "ca978112ca1bbdcafac231b39a23dc4da786eff8147c4e72b9807785afee48bb"
    );
    assert_eq!(
        run_sha("abc"),
        "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad"
    );
    assert_eq!(
        run_sha("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"),
        "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1"
    );
}

#[test]
#[serial]
fn sha_iter() {
    let input = to_vec(&MultiTestSpec::ShaDigestIter {
        data: Vec::from([0u8; 32]),
        num_iter: 1500,
    })
    .unwrap();
    let env = ExecutorEnv::builder().add_input(&input).build().unwrap();
    let mut exec = Executor::from_elf(env, MULTI_TEST_ELF).unwrap();
    let session = exec.run().unwrap();
    let receipt = session.prove().unwrap();
    let digest = Digest::try_from(receipt.journal).unwrap();
    assert_eq!(
        hex::encode(digest),
        "9d4d1940b5c0c6d09c10add9631806f9df9467884d3e9ce4a147113e27f5c02a"
    )
}

#[test]
fn bigint_accel() {
    let cases = testutils::generate_bigint_test_cases(&mut rand::thread_rng(), 10);
    for case in cases {
        println!("Running BigInt circuit test case: {:08x?}", case);
        let input = to_vec(&MultiTestSpec::BigInt {
            x: case.x,
            y: case.y,
            modulus: case.modulus,
        })
        .unwrap();

        let env = ExecutorEnv::builder().add_input(&input).build().unwrap();
        let mut exec = Executor::from_elf(env, MULTI_TEST_ELF).unwrap();
        let session = exec.run().unwrap();
        let receipt = session.prove().unwrap();
        let expected = case.expected();
        let expected: &[u8] = bytemuck::cast_slice(expected.as_slice());
        assert_eq!(receipt.journal, expected);
    }
}

#[test]
#[serial]
fn memory_io() {
    fn run_memio(pairs: &[(usize, usize)]) -> Result<Receipt> {
        let spec = MultiTestSpec::ReadWriteMem {
            values: pairs
                .iter()
                .cloned()
                .map(|(addr, value)| (addr as u32, value as u32))
                .collect(),
        };
        let input = to_vec(&spec)?;
        let env = ExecutorEnv::builder().add_input(&input).build().unwrap();
        let mut exec = Executor::from_elf(env, MULTI_TEST_ELF)?;
        let session = exec.run()?;
        session.prove()
    }

    // Pick a memory position in the middle of the memory space, which is unlikely
    // to be touched by either the stack or heap:
    const POS: usize = crate::align_up(
        (memory::TEXT_START + memory::STACK_TOP) as usize / 2,
        WORD_SIZE,
    );

    // Double writes are fine
    run_memio(&[(POS, 1), (POS, 1)]).unwrap();

    // Writes at different addresses are fine
    run_memio(&[(POS, 1), (POS + 4, 2)]).unwrap();

    // Aligned write is fine
    run_memio(&[(POS, 1)]).unwrap();

    // Unaligned write is bad
    run_memio(&[(POS + 1001, 1)]).unwrap_err();

    // Aligned read is fine
    run_memio(&[(POS, 0)]).unwrap();

    // Unaligned read is bad
    run_memio(&[(POS + 1, 0)]).unwrap_err();
}

#[test]
#[cfg_attr(feature = "cuda", serial)]
fn pause_continue() {
    let env = ExecutorEnv::builder()
        .add_input(&to_vec(&MultiTestSpec::PauseContinue).unwrap())
        .build()
        .unwrap();
    let mut exec = Executor::from_elf(env, MULTI_TEST_ELF).unwrap();

    // Run until sys_pause
    let session = exec.run().unwrap();
    assert_eq!(session.segments.len(), 1);
    assert_eq!(session.exit_code, ExitCode::Paused(0));
    let receipt = session.prove().unwrap();
    let segments = receipt.inner.flat().unwrap();
    assert_eq!(segments.len(), 1);
    assert_eq!(segments[0].index, 0);

    // Run until sys_halt
    let session = exec.run().unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));
    session.prove().unwrap();
}

#[test]
fn session_events() {
    use std::{cell::RefCell, rc::Rc};

    use risc0_zkvm_methods::HELLO_COMMIT_ELF;

    use crate::{Segment, SessionEvents};

    struct Logger {
        on_pre_prove_segment_flag: Rc<RefCell<bool>>,
        on_post_prove_segment_flag: Rc<RefCell<bool>>,
    }

    impl SessionEvents for Logger {
        fn on_pre_prove_segment(&self, _: &Segment) {
            self.on_pre_prove_segment_flag.replace(true);
        }

        fn on_post_prove_segment(&self, _: &Segment) {
            self.on_post_prove_segment_flag.replace(true);
        }
    }

    let mut exec = Executor::from_elf(ExecutorEnv::default(), HELLO_COMMIT_ELF).unwrap();
    let mut session = exec.run().unwrap();
    let on_pre_prove_segment_flag = Rc::new(RefCell::new(false));
    let on_post_prove_segment_flag = Rc::new(RefCell::new(false));
    let logger = Logger {
        on_pre_prove_segment_flag: on_pre_prove_segment_flag.clone(),
        on_post_prove_segment_flag: on_post_prove_segment_flag.clone(),
    };
    session.add_hook(logger);
    session.prove().unwrap();
    assert_eq!(session.hooks.len(), 1);
    assert_eq!(on_pre_prove_segment_flag.take(), true);
    assert_eq!(on_post_prove_segment_flag.take(), true);
}

#[test]
#[cfg_attr(feature = "cuda", serial)]
fn continuation() {
    const COUNT: usize = 2; // Number of total chunks to aim for.
    let segment_limit_po2 = 16; // 64k cycles
    let cycles = 1 << segment_limit_po2;

    let spec = &to_vec(&MultiTestSpec::BusyLoop { cycles }).unwrap();
    let env = ExecutorEnv::builder()
        .add_input(&spec)
        .segment_limit_po2(segment_limit_po2)
        .build()
        .unwrap();
    let mut exec = Executor::from_elf(env, MULTI_TEST_ELF).unwrap();
    let session = exec.run().unwrap();
    let segments = session.resolve().unwrap();
    assert_eq!(segments.len(), COUNT);

    let (final_segment, segments) = segments.split_last().unwrap();
    for segment in segments {
        assert_eq!(segment.exit_code, ExitCode::SystemSplit);
    }
    assert_eq!(final_segment.exit_code, ExitCode::Halted(0));

    let receipt = session.prove().unwrap();
    for (idx, receipt) in receipt.inner.flat().unwrap().iter().enumerate() {
        assert_eq!(receipt.index, idx as u32);
    }
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
            let image = MemoryImage::new(&program, PAGE_SIZE as u32).unwrap();

            let env = ExecutorEnv::default();
            let mut exec = Executor::new(env, image).unwrap();
            let session = exec.run().unwrap();
            session.prove().unwrap();
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
