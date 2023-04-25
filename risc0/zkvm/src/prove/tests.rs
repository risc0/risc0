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

use anyhow::Result;
use num_bigint::BigUint;
use risc0_circuit_rv32im::cpu::CpuEvalCheck;
use risc0_core::field::baby_bear::{BabyBear, Elem, ExtElem};
use risc0_zkp::{
    core::{digest::Digest, hash::blake2b::Blake2bCpuHashSuite},
    hal::{cpu::CpuHal, EvalCheck, Hal},
    verify::{HashSuite, VerificationError},
};
use risc0_zkvm_methods::{multi_test::MultiTestSpec, MULTI_TEST_ELF, MULTI_TEST_ID};
use risc0_zkvm_platform::{memory::HEAP, syscall::bigint};
use serial_test::serial;
use test_log::test;

use super::{default_hal, default_poseidon_hal};
use crate::{
    serde::{from_slice, to_vec},
    ControlId, Executor, ExecutorEnv, ExitCode, SessionReceipt, CIRCUIT,
};

fn prove_nothing<H, E>(hal: &H, eval: &E) -> Result<SessionReceipt>
where
    H: Hal<Field = BabyBear, Elem = Elem, ExtElem = ExtElem>,
    <<H as Hal>::HashSuite as HashSuite<BabyBear>>::HashFn: ControlId,
    E: EvalCheck<H>,
{
    let input = to_vec(&MultiTestSpec::DoNothing).unwrap();
    let env = ExecutorEnv::builder().add_input(&input).build();
    let mut exec = Executor::from_elf(env, MULTI_TEST_ELF).unwrap();
    let session = exec.run().unwrap();
    session.prove(hal, eval)
}

#[test]
#[cfg_attr(feature = "cuda", serial)]
fn hashfn_poseidon() {
    let (hal, eval) = default_poseidon_hal();
    prove_nothing(hal.as_ref(), &eval).unwrap();
}

#[test]
fn hashfn_blake2b() {
    let hal = CpuHal::<BabyBear, Blake2bCpuHashSuite>::new();
    let eval = CpuEvalCheck::new(&CIRCUIT);
    prove_nothing(&hal, &eval).unwrap();
}

#[test]
#[cfg_attr(feature = "cuda", serial)]
fn receipt_serde() {
    let (hal, eval) = default_hal();
    let receipt = prove_nothing(hal.as_ref(), &eval).unwrap();
    let encoded: Vec<u32> = to_vec(&receipt).unwrap();
    let decoded: SessionReceipt = from_slice(&encoded).unwrap();
    assert_eq!(decoded, receipt);
    decoded.verify(MULTI_TEST_ID).unwrap();
}

#[test]
#[cfg_attr(feature = "cuda", serial)]
fn check_image_id() {
    let (hal, eval) = default_hal();
    let receipt = prove_nothing(hal.as_ref(), &eval).unwrap();
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
        let env = ExecutorEnv::builder().add_input(&input).build();
        let mut exec = Executor::from_elf(env, MULTI_TEST_ELF).unwrap();
        let session = exec.run().unwrap();
        let (hal, eval) = default_hal();
        let receipt = session.prove(hal.as_ref(), &eval).unwrap();
        hex::encode(Digest::try_from(receipt.journal.as_slice()).unwrap())
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
fn bigint_accel() {
    let zero = [0, 0, 0, 0, 0, 0, 0, 0];
    let one = [1, 0, 0, 0, 0, 0, 0, 0];

    struct Case {
        x: [u32; bigint::WIDTH_WORDS],
        y: [u32; bigint::WIDTH_WORDS],
        modulus: [u32; bigint::WIDTH_WORDS],
    }

    let cases = [
        Case {
            x: [1, 2, 3, 4, 5, 6, 7, 8],
            y: [9, 10, 11, 12, 13, 14, 15, 16],
            modulus: [17u32, 18u32, 19u32, 20u32, 21u32, 22u32, 23u32, 24u32],
        },
        Case {
            x: [1, 2, 3, 4, 5, 6, 7, 8],
            y: zero,
            modulus: [17u32, 18u32, 19u32, 20u32, 21u32, 22u32, 23u32, 24u32],
        },
        Case {
            x: [1, 2, 3, 4, 5, 6, 7, 8],
            y: one,
            modulus: [17u32, 18u32, 19u32, 20u32, 21u32, 22u32, 23u32, 24u32],
        },
    ];

    for Case { x, y, modulus } in cases {
        let expected = {
            let z =
                (BigUint::from_slice(&x) * BigUint::from_slice(&y)) % BigUint::from_slice(&modulus);
            let mut vec = z.to_u32_digits();
            if vec.len() > bigint::WIDTH_WORDS {
                panic!("modular multiplication result larger than input modulus");
            }
            vec.resize(bigint::WIDTH_WORDS, 0);
            vec
        };

        let input = to_vec(&MultiTestSpec::BigInt { x, y, modulus }).unwrap();
        let env = ExecutorEnv::builder().add_input(&input).build();
        let mut exec = Executor::from_elf(env, MULTI_TEST_ELF).unwrap();
        let session = exec.run().unwrap();
        let (hal, eval) = default_hal();
        let receipt = session.prove(hal.as_ref(), &eval).unwrap();
        assert_eq!(
            receipt.journal.as_slice(),
            bytemuck::cast_slice(expected.as_slice())
        );
    }
}

#[test]
#[serial]
fn memory_io() {
    fn run_memio(pairs: &[(usize, usize)]) -> Result<SessionReceipt> {
        let spec = MultiTestSpec::ReadWriteMem {
            values: pairs
                .iter()
                .cloned()
                .map(|(addr, value)| (addr as u32, value as u32))
                .collect(),
        };
        let input = to_vec(&spec)?;
        let env = ExecutorEnv::builder().add_input(&input).build();
        let mut exec = Executor::from_elf(env, MULTI_TEST_ELF)?;
        let session = exec.run()?;
        let (hal, eval) = default_hal();
        session.prove(hal.as_ref(), &eval)
    }

    // Double writes are fine
    run_memio(&[(HEAP.start(), 1), (HEAP.start(), 1)]).unwrap();

    // Writes at different addresses are fine
    run_memio(&[(HEAP.start(), 1), (HEAP.start() + 4, 2)]).unwrap();

    // Aligned write is fine
    run_memio(&[(HEAP.start(), 1)]).unwrap();

    // Unaligned write is bad
    run_memio(&[(HEAP.start() + 1001, 1)]).unwrap_err();

    // Aligned read is fine
    run_memio(&[(HEAP.start(), 0)]).unwrap();

    // Unaligned read is bad
    run_memio(&[(HEAP.start() + 1, 0)]).unwrap_err();
}

#[test]
#[cfg_attr(feature = "cuda", serial)]
fn pause_continue() {
    let env = ExecutorEnv::builder()
        .add_input(&to_vec(&MultiTestSpec::PauseContinue).unwrap())
        .build();
    let mut exec = Executor::from_elf(env, MULTI_TEST_ELF).unwrap();
    let (hal, eval) = default_hal();

    // Run until sys_pause
    let session = exec.run().unwrap();
    assert_eq!(session.exit_code, ExitCode::Paused);
    session.prove(hal.as_ref(), &eval).unwrap();

    // Run until sys_halt
    let session = exec.run().unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));
    session.prove(hal.as_ref(), &eval).unwrap();
}

#[test]
#[cfg_attr(feature = "cuda", serial)]
fn continuation() {
    const COUNT: usize = 7; // Number of total chunks to aim for.
    let segment_limit_po2 = 15; // 32k cycles
    let cycles = 1 << segment_limit_po2;

    let spec = &to_vec(&MultiTestSpec::BusyLoop { cycles }).unwrap();
    let env = ExecutorEnv::builder()
        .add_input(&spec)
        .segment_limit_po2(segment_limit_po2)
        .build();
    let mut exec = Executor::from_elf(env, MULTI_TEST_ELF).unwrap();
    let session = exec.run().unwrap();
    assert_eq!(session.segments.len(), COUNT);

    let (final_segment, segments) = session.segments.split_last().unwrap();
    for segment in segments {
        assert!(std::matches!(segment.exit_code, ExitCode::SystemSplit(_)));
    }
    assert_eq!(final_segment.exit_code, ExitCode::Halted(0));

    let (hal, eval) = default_hal();
    session.prove(hal.as_ref(), &eval).unwrap();
}

// These tests come from:
// https://github.com/riscv-software-src/riscv-tests
// They were built using the toolchain from:
// https://github.com/risc0/toolchain/releases/tag/2022.03.25
mod riscv {
    use crate::{prove::default_hal, Executor, ExecutorEnv, MemoryImage, Program};

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
            let session = exec.run().unwrap();

            let (hal, eval) = default_hal();
            session.prove(hal.as_ref(), &eval).unwrap();
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
