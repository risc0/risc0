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
use risc0_zkp::{core::digest::Digest, verify::VerificationError};
use risc0_zkvm_methods::{multi_test::MultiTestSpec, MULTI_TEST_ELF, MULTI_TEST_ID};
use risc0_zkvm_platform::memory::HEAP;
use serial_test::serial;
use test_log::test;

use super::default_hal;
use crate::{
    serde::{from_slice, to_vec},
    Executor, ExecutorEnv, SessionReceipt,
};

fn prove_nothing() -> Result<SessionReceipt> {
    let input = to_vec(&MultiTestSpec::DoNothing).unwrap();
    let env = ExecutorEnv::builder().add_input(&input).build();
    let mut exec = Executor::from_elf(env, MULTI_TEST_ELF).unwrap();
    let session = exec.run().unwrap();
    let (hal, eval) = default_hal();
    session.prove(hal.as_ref(), &eval)
}

#[test]
#[cfg_attr(feature = "cuda", serial)]
fn receipt_serde() {
    let receipt = prove_nothing().unwrap();
    let encoded: Vec<u32> = to_vec(&receipt).unwrap();
    let decoded: SessionReceipt = from_slice(&encoded).unwrap();
    assert_eq!(decoded, receipt);
    decoded.verify(MULTI_TEST_ID).unwrap();
}

#[test]
#[cfg_attr(feature = "cuda", serial)]
fn check_image_id() {
    let receipt = prove_nothing().unwrap();
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

// #[test]
// #[cfg_attr(feature = "insecure_skip_seal", ignore)]
// #[cfg_attr(feature = "cuda", serial)]
// fn pause_continue() {
//     let mut prover = Prover::new(MULTI_TEST_ELF).unwrap();
//     prover.add_input_u32_slice(&to_vec(&MultiTestSpec::PauseContinue).
// unwrap());

//     // Run until sys_pause
//     prover.run().unwrap();
//     assert_eq!(prover.exit_code, halt::PAUSE);

//     // Run until sys_halt
//     prover.run().unwrap();
//     assert_eq!(prover.exit_code, halt::TERMINATE);
// }

// #[test]
// #[cfg_attr(feature = "insecure_skip_seal", ignore)]
// #[cfg_attr(feature = "cuda", serial)]
// fn continuation() {
//     let segment_limit_po2 = 17; // 128k cycles
//     const COUNT: usize = 4; // Number of total chunks to aim for.

//     let opts =
// ProverOpts::default().with_segment_limit_po2(segment_limit_po2);     let mut
// prover = Prover::new_with_opts(MULTI_TEST_ELF, opts).unwrap();     prover.
// add_input_u32_slice(         &to_vec(&MultiTestSpec::BusyLoop {
//             // BusyLoop goes for *at least* this many cycles, so should fill
// up (COUNT - 1) blocks             // and then slightly overflow into the next
// one.             cycles: ((COUNT - 1) * (1 << segment_limit_po2)) as u32,
//         })
//         .unwrap(),
//     );

//     for count in 0..COUNT {
//         prover.run().unwrap();
//         if count == COUNT - 1 {
//             assert_eq!(prover.exit_code, halt::TERMINATE);
//         } else {
//             assert_eq!(
//                 prover.exit_code,
//                 halt::SPLIT,
//                 "expected a split at part {count}"
//             );
//         }
//     }
// }
