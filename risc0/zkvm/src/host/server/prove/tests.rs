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

use anyhow::Result;
use risc0_binfmt::MemoryImage2;
use risc0_circuit_rv32im_v2::TerminateState;
use risc0_zkp::{core::digest::Digest, verify::VerificationError};
use risc0_zkvm_methods::{multi_test::MultiTestSpec, MULTI_TEST_ELF, MULTI_TEST_ID};
use risc0_zkvm_platform::{memory, WORD_SIZE};
use rstest::rstest;

use super::get_prover_server;
use crate::{
    host::server::{exec::executor2::Executor2, testutils},
    serde::{from_slice, to_vec},
    ExecutorEnv, ExitCode, ProveInfo, ProverOpts, Receipt, Session, SimpleSegmentRef,
    VerifierContext,
};

fn execute_elf(env: ExecutorEnv, elf: &[u8]) -> Result<Session> {
    Executor2::from_elf(env, elf)
        .unwrap()
        .run_with_callback(|segment| Ok(Box::new(SimpleSegmentRef::new(segment))))
}

fn prove_session(session: &Session) -> Result<Receipt> {
    let opts = ProverOpts::fast();
    let ctx = VerifierContext::default();
    let prover = get_prover_server(&opts)?;
    Ok(prover.prove_session(&ctx, session)?.receipt)
}

fn prove_elf(env: ExecutorEnv, elf: &[u8]) -> Result<Receipt> {
    let opts = ProverOpts::fast();
    Ok(get_prover_server(&opts)?.prove(env, elf)?.receipt)
}

fn prove_elf_succinct(env: ExecutorEnv, elf: &[u8]) -> Result<Receipt> {
    let opts = ProverOpts::succinct();
    Ok(get_prover_server(&opts)?.prove(env, elf)?.receipt)
}

fn prove_nothing() -> Result<ProveInfo> {
    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::DoNothing)
        .unwrap()
        .build()
        .unwrap();
    let opts = ProverOpts::composite();
    get_prover_server(&opts).unwrap().prove(env, MULTI_TEST_ELF)
}

#[test_log::test]
fn prove_nothing_succinct() {
    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::DoNothing)
        .unwrap()
        .build()
        .unwrap();
    let opts = ProverOpts::succinct();
    get_prover_server(&opts)
        .unwrap()
        .prove(env, MULTI_TEST_ELF)
        .unwrap()
        .receipt
        .inner
        .succinct()
        .unwrap(); // ensure that we got a succinct receipt.
}

#[test_log::test]
fn keccak_union() {
    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::KeccakUnion(3))
        .unwrap()
        .build()
        .unwrap();
    let opts = ProverOpts::succinct();
    get_prover_server(&opts)
        .unwrap()
        .prove(env, MULTI_TEST_ELF)
        .unwrap();
}

#[test_log::test]
fn basic() {
    prove_nothing().unwrap();
}

#[test_log::test]
fn receipt_serde() {
    let receipt = prove_nothing().unwrap().receipt;
    let encoded: Vec<u32> = to_vec(&receipt).unwrap();
    let decoded: Receipt = from_slice(&encoded).unwrap();
    assert_eq!(decoded, receipt);
    let ctx = VerifierContext::default();
    decoded.verify_with_context(&ctx, MULTI_TEST_ID).unwrap();
}

#[test_log::test]
fn check_image_id() {
    let receipt = prove_nothing().unwrap().receipt;
    let mut image_id: Digest = MULTI_TEST_ID.into();
    for word in image_id.as_mut_words() {
        *word = word.wrapping_add(1);
    }
    let ctx = VerifierContext::default();
    assert!(matches!(
        receipt.verify_with_context(&ctx, image_id).unwrap_err(),
        VerificationError::ClaimDigestMismatch { .. }
    ));
}

#[test_log::test]
fn sha_basics() {
    let run_sha = |msg: &str| -> String {
        let env = ExecutorEnv::builder()
            .write(&MultiTestSpec::ShaDigest { data: msg.into() })
            .unwrap()
            .build()
            .unwrap();
        let receipt = prove_elf(env, MULTI_TEST_ELF).unwrap();
        hex::encode(Digest::try_from(receipt.journal.bytes).unwrap())
    };

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

#[test_log::test]
fn sha_iter() {
    let input = MultiTestSpec::ShaDigestIter {
        data: Vec::from([0u8; 32]),
        num_iter: 1500,
    };
    let env = ExecutorEnv::builder()
        .write(&input)
        .unwrap()
        .build()
        .unwrap();
    let receipt = prove_elf(env, MULTI_TEST_ELF).unwrap();
    let digest = Digest::try_from(receipt.journal.bytes).unwrap();
    assert_eq!(
        hex::encode(digest),
        "9d4d1940b5c0c6d09c10add9631806f9df9467884d3e9ce4a147113e27f5c02a"
    )
}

#[test_log::test]
fn bigint_accel() {
    let cases = testutils::generate_bigint_test_cases(&mut rand::thread_rng(), 10);
    for case in cases {
        println!("Running BigInt circuit test case: {:08x?}", case);
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
        let mut exec = Executor2::from_elf(env, MULTI_TEST_ELF).unwrap();
        let session = exec.run().unwrap();
        let receipt = prove_session(&session).unwrap();
        let expected = case.expected();
        let expected: &[u8] = bytemuck::cast_slice(expected.as_slice());
        assert_eq!(receipt.journal.bytes, expected);
    }
}

// Pick a memory position in the middle of the memory space, which is unlikely
// to be touched by either the stack or heap:
const POS: usize = crate::align_up(
    (memory::TEXT_START + memory::STACK_TOP) as usize / 2,
    WORD_SIZE,
);

#[rstest]
// Double writes are fine
#[case(&[(POS, 1), (POS, 1)])]
// Writes at different addresses are fine
#[case(&[(POS, 1), (POS + 4, 2)])]
// Aligned write is fine
#[case(&[(POS, 1)])]
// Aligned read is fine
#[case(&[(POS, 0)])]
// Unaligned write is bad
#[should_panic(expected = "StoreAddressMisaligned")]
#[case(&[(POS + 1001, 1)])]
// Unaligned read is bad
#[should_panic(expected = "LoadAddressMisaligned")]
#[case(&[(POS + 1, 0)])]
#[test_log::test]
fn memory_io(#[case] pairs: &[(usize, usize)]) {
    let input = MultiTestSpec::ReadWriteMem {
        values: pairs
            .iter()
            .cloned()
            .map(|(addr, value)| (addr as u32, value as u32))
            .collect(),
    };
    let env = ExecutorEnv::builder()
        .write(&input)
        .unwrap()
        .build()
        .unwrap();
    let receipt = prove_elf(env, MULTI_TEST_ELF).unwrap();
    let ctx = VerifierContext::default();
    receipt.verify_integrity_with_context(&ctx).unwrap();
    assert_eq!(
        receipt.claim().unwrap().as_value().unwrap().exit_code,
        ExitCode::Halted(0)
    );
}

#[test_log::test]
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

    let mut session = execute_elf(ExecutorEnv::default(), HELLO_COMMIT_ELF).unwrap();
    let on_pre_prove_segment_flag = Rc::new(RefCell::new(false));
    let on_post_prove_segment_flag = Rc::new(RefCell::new(false));
    let logger = Logger {
        on_pre_prove_segment_flag: on_pre_prove_segment_flag.clone(),
        on_post_prove_segment_flag: on_post_prove_segment_flag.clone(),
    };
    session.add_hook(logger);
    prove_session(&session).unwrap();
    assert_eq!(session.hooks.len(), 1);
    assert!(on_pre_prove_segment_flag.take());
    assert!(on_post_prove_segment_flag.take());
}

// These tests come from:
// https://github.com/riscv-software-src/riscv-tests
// They were built using the toolchain from:
// https://github.com/risc0/toolchain/releases/tag/2022.03.25
mod riscv {
    use super::*;
    use crate::ExecutorEnv;

    fn prove_elf(env: ExecutorEnv, elf: &[u8]) -> Result<Receipt> {
        let session = Executor2::from_kernel_elf(env, elf)
            .unwrap()
            .run_with_callback(|segment| Ok(Box::new(SimpleSegmentRef::new(segment))))?;
        prove_session(&session)
    }

    fn run_test(test_name: &str) {
        use std::io::Read;

        use flate2::read::GzDecoder;
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

            let env = ExecutorEnv::default();
            prove_elf(env, &elf).unwrap();
        }
    }

    macro_rules! test_case {
        ($func_name:ident) => {
            #[test_log::test]
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

#[test_log::test]
fn pause_resume() {
    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::PauseResume(0))
        .unwrap()
        .build()
        .unwrap();
    let mut exec = Executor2::from_elf(env, MULTI_TEST_ELF).unwrap();

    // Run until sys_pause
    let session = exec.run().unwrap();
    assert_eq!(session.segments.len(), 1);
    assert_eq!(session.exit_code, ExitCode::Paused(0));
    let receipt = prove_session(&session).unwrap();
    let segments = &receipt.inner.composite().unwrap().segments;
    assert_eq!(segments.len(), 1);
    assert_eq!(segments[0].index, 0);

    // Run until sys_halt
    let session = exec.run().unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));
    prove_session(&session).unwrap();
}

#[test_log::test]
fn pause_exit_nonzero() {
    let user_exit_code = 1;
    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::PauseResume(user_exit_code))
        .unwrap()
        .build()
        .unwrap();
    let mut exec = Executor2::from_elf(env, MULTI_TEST_ELF).unwrap();

    // Run until sys_pause
    let session = exec.run().unwrap();
    assert_eq!(session.segments.len(), 1);
    assert_eq!(session.exit_code, ExitCode::Paused(user_exit_code as u32));
    prove_session(&session).unwrap();

    // Run until sys_halt
    let session = exec.run().unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));
    prove_session(&session).unwrap();
}

#[test_log::test]
fn continuation() {
    const COUNT: usize = 2; // Number of total chunks to aim for.

    let program = risc0_circuit_rv32im_v2::execute::testutil::kernel::simple_loop(200);
    let image = MemoryImage2::new_kernel(program);

    let env = ExecutorEnv::builder()
        .segment_limit_po2(13) // 8k cycles
        .build()
        .unwrap();
    let session = Executor2::new(env, image).unwrap().run().unwrap();
    let segments: Vec<_> = session
        .segments
        .iter()
        .map(|x| x.resolve().unwrap())
        .collect();
    assert_eq!(segments.len(), COUNT);

    let (final_segment, segments) = segments.split_last().unwrap();
    for segment in segments {
        assert_eq!(segment.inner.claim.terminate_state, None);
    }
    assert_eq!(
        final_segment.inner.claim.terminate_state,
        Some(TerminateState::default())
    );

    let receipt = prove_session(&session).unwrap();
    for (idx, receipt) in receipt
        .inner
        .composite()
        .unwrap()
        .segments
        .iter()
        .enumerate()
    {
        assert_eq!(receipt.index, idx as u32);
    }
}

#[test_log::test]
fn sys_input() {
    use hex::FromHex;
    let digest =
        Digest::from_hex("ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad")
            .unwrap();
    let spec = MultiTestSpec::SysInput(digest);
    let env = ExecutorEnv::builder()
        .input_digest(digest)
        .write(&spec)
        .unwrap()
        .build()
        .unwrap();
    let mut exec = Executor2::from_elf(env, MULTI_TEST_ELF).unwrap();
    let session = exec.run().unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));
    prove_session(&session).unwrap();
}

#[cfg(feature = "docker")]
#[cfg(target_arch = "x86_64")]
mod docker {
    use risc0_zkvm_methods::{MULTI_TEST_ID, VERIFY_ELF};

    use super::*;
    use crate::{
        host::server::prove::dev_mode::DevModeProver, FakeReceipt, InnerReceipt, ProverServer as _,
        ReceiptKind,
    };

    #[test_log::test]
    fn stark2snark() {
        let env = ExecutorEnv::builder()
            .write(&MultiTestSpec::DoNothing)
            .unwrap()
            .build()
            .unwrap();
        let opts = ProverOpts::groth16();
        get_prover_server(&opts)
            .unwrap()
            .prove(env, MULTI_TEST_ELF)
            .unwrap()
            .receipt
            .inner
            .groth16()
            .unwrap(); // ensure that we got a groth16 receipt.
    }

    fn test_compress(opts: ProverOpts, receipt: &Receipt) {
        let prover = get_prover_server(&opts).unwrap();
        let receipt = prover.compress(&opts, receipt).unwrap();
        match opts.receipt_kind {
            ReceiptKind::Composite => match receipt.inner {
                InnerReceipt::Composite(_)
                | InnerReceipt::Succinct(_)
                | InnerReceipt::Groth16(_) => {}
                InnerReceipt::Fake { .. } => panic!("unexpected fake receipt"),
            },
            ReceiptKind::Succinct => match receipt.inner {
                InnerReceipt::Succinct(_) | InnerReceipt::Groth16(_) => {}
                InnerReceipt::Composite(_) => panic!("expected receipt to be succinct or smaller"),
                InnerReceipt::Fake { .. } => panic!("unexpected fake receipt"),
            },
            ReceiptKind::Groth16 => match receipt.inner {
                InnerReceipt::Groth16(_) => {}
                InnerReceipt::Succinct(_) | InnerReceipt::Composite(_) => {
                    panic!("expected receipt to be groth16 or smaller")
                }
                InnerReceipt::Fake { .. } => panic!("unexpected fake receipt"),
            },
        };
        receipt.verify(MULTI_TEST_ID).unwrap();
    }

    fn test_fake_compress(receipt: &Receipt) {
        fn ensure_fake(receipt: Receipt) {
            let InnerReceipt::Fake(_) = receipt.inner else {
                panic!("expected fake receipt");
            };
        }
        let fake = Receipt::new(
            InnerReceipt::Fake(FakeReceipt {
                claim: receipt.claim().unwrap(),
            }),
            receipt.clone().journal.bytes,
        );

        let prover = DevModeProver;
        let receipt = prover.compress(&ProverOpts::composite(), &fake).unwrap();
        ensure_fake(receipt);
        let receipt = prover.compress(&ProverOpts::succinct(), &fake).unwrap();
        ensure_fake(receipt);
        let receipt = prover.compress(&ProverOpts::groth16(), &fake).unwrap();
        ensure_fake(receipt);
    }

    fn generate_receipt(opts: ProverOpts) -> Receipt {
        let env = ExecutorEnv::builder()
            .write(&MultiTestSpec::DoNothing)
            .unwrap()
            .build()
            .unwrap();
        let prover = get_prover_server(&opts).unwrap();
        prover.prove(env, MULTI_TEST_ELF).unwrap().receipt
    }

    fn exec_verify(receipt: &Receipt) {
        let input: (_, Digest) = (receipt.clone(), MULTI_TEST_ID.into());
        let env = ExecutorEnv::builder()
            .write(&input)
            .unwrap()
            .build()
            .unwrap();
        let session = Executor2::from_elf(env, VERIFY_ELF).unwrap().run().unwrap();
        assert_eq!(session.exit_code, ExitCode::Halted(0));
        println!("{:?}", session.stats());
    }

    #[test_log::test]
    fn verify_in_guest() {
        let composite_receipt_sha256 = generate_receipt(ProverOpts::fast());
        exec_verify(&composite_receipt_sha256);
        let composite_receipt = generate_receipt(ProverOpts::composite());
        exec_verify(&composite_receipt);
        let succinct_receipt = get_prover_server(&ProverOpts::succinct())
            .unwrap()
            .compress(&ProverOpts::succinct(), &composite_receipt)
            .unwrap();
        exec_verify(&succinct_receipt);
        let groth16_receipt = get_prover_server(&ProverOpts::groth16())
            .unwrap()
            .compress(&ProverOpts::groth16(), &succinct_receipt)
            .unwrap();
        exec_verify(&groth16_receipt);
        groth16_receipt.inner.groth16().unwrap();
    }

    #[test_log::test]
    fn prover_stark2snark() {
        // composite receipts
        let composite_receipt = &generate_receipt(ProverOpts::composite());
        self::test_compress(ProverOpts::composite(), composite_receipt);
        self::test_compress(ProverOpts::succinct(), composite_receipt);
        self::test_compress(ProverOpts::groth16(), composite_receipt);

        // succinct receipts
        let succinct_receipt = &generate_receipt(ProverOpts::succinct());
        self::test_compress(ProverOpts::composite(), succinct_receipt);
        self::test_compress(ProverOpts::succinct(), succinct_receipt);
        self::test_compress(ProverOpts::groth16(), succinct_receipt);

        // groth16 receipts
        let groth16_receipt = &generate_receipt(ProverOpts::groth16());
        self::test_compress(ProverOpts::composite(), groth16_receipt);
        self::test_compress(ProverOpts::succinct(), groth16_receipt);
        self::test_compress(ProverOpts::groth16(), groth16_receipt);

        // fake receipts
        self::test_fake_compress(groth16_receipt);
    }
}

mod sys_verify {
    use std::{cell::RefCell, rc::Rc, sync::OnceLock};

    use risc0_zkp::{core::hash::poseidon2::Poseidon2HashSuite, digest};
    use risc0_zkvm_methods::{HELLO_COMMIT_ELF, HELLO_COMMIT_ID};

    use super::*;
    use crate::{
        recursion::{prove::zkr, test_zkr, MerkleGroup},
        register_zkr,
        sha::Digestible as _,
        Assumption, CoprocessorCallback, ProveKeccakRequest, ProveZkrRequest, SuccinctReceipt,
        Unknown, RECURSION_PO2,
    };

    fn prove_halt(exit_code: u8) -> Receipt {
        let opts = ProverOpts::fast().with_prove_guest_errors(true);

        let env = ExecutorEnv::builder()
            .write(&MultiTestSpec::Halt(exit_code))
            .unwrap()
            .build()
            .unwrap();
        let halt_receipt = get_prover_server(&opts)
            .unwrap()
            .prove(env, MULTI_TEST_ELF)
            .unwrap()
            .receipt;

        // Double check that the receipt verifies with the expected image ID and exit code.
        halt_receipt
            .verify_integrity_with_context(&VerifierContext::default())
            .unwrap();
        let halt_claim = halt_receipt.claim().unwrap();
        assert_eq!(
            halt_claim.as_value().unwrap().exit_code,
            ExitCode::Halted(exit_code as u32)
        );

        halt_receipt
    }

    // The test_recursion_circuit is a program for the recursion VM that does some very simple
    // operations. It is used here to provide an "out-of-tree" recursion program receipt, in that
    // this program is not in the standard tree of allowed recursion programs, but should be
    // verifiable in the guest via composition with the provided control root.
    fn prove_test_recursion_circuit() -> SuccinctReceipt<Unknown> {
        // Random Poseidon2 "digest" to act as the "control root".
        let suite = Poseidon2HashSuite::new_suite();
        let (_, control_id) = zkr::test_recursion_circuit(&suite.name).unwrap();
        let control_tree = MerkleGroup::new(vec![control_id]).unwrap();
        let control_root = control_tree.calc_root(suite.hashfn.as_ref());

        let digest2 = digest!("00000000000000de00000000000000ad00000000000000be00000000000000ef");
        test_zkr(&control_root, &digest2, RECURSION_PO2).unwrap()
    }

    fn hello_commit_receipt() -> &'static Receipt {
        static ONCE: OnceLock<Receipt> = OnceLock::new();
        ONCE.get_or_init(|| prove_elf(ExecutorEnv::default(), HELLO_COMMIT_ELF).unwrap())
    }

    #[test_log::test]
    fn sys_verify_1() {
        let spec = MultiTestSpec::SysVerify(vec![(
            HELLO_COMMIT_ID.into(),
            hello_commit_receipt().journal.bytes.clone(),
        )]);

        // Test that providing the proven assumption results in an unconditional
        // receipt.
        let env = ExecutorEnv::builder()
            .write(&spec)
            .unwrap()
            .add_assumption(hello_commit_receipt().clone())
            .build()
            .unwrap();

        prove_elf(env, MULTI_TEST_ELF)
            .unwrap()
            .verify_with_context(&VerifierContext::default(), MULTI_TEST_ID)
            .unwrap();
    }

    #[test_log::test]
    fn sys_verify_2() {
        let spec = MultiTestSpec::SysVerify(vec![(
            HELLO_COMMIT_ID.into(),
            hello_commit_receipt().journal.bytes.clone(),
        )]);

        // Test that proving without a provided assumption results in an execution
        // failure.
        let env = ExecutorEnv::builder()
            .write(&spec)
            .unwrap()
            .build()
            .unwrap();
        assert!(prove_elf(env, MULTI_TEST_ELF).is_err());
    }

    #[test_log::test]
    fn sys_verify_3() {
        let spec = MultiTestSpec::SysVerify(vec![(
            HELLO_COMMIT_ID.into(),
            hello_commit_receipt().journal.bytes.clone(),
        )]);

        // Test that providing an unresolved assumption results in a conditional
        // receipt.
        let env = ExecutorEnv::builder()
            .write(&spec)
            .unwrap()
            .add_assumption(hello_commit_receipt().claim().unwrap())
            .build()
            .unwrap();

        // TODO(#982) Conditional receipts currently return an error on verification.
        assert!(prove_elf(env, MULTI_TEST_ELF).is_err());

        // TODO(#982) With conditional receipts, implement the following cases.
        // verify with proven corroboration in verifier success.
        // verify with unresolved corroboration in verifier success.
        // verify with no resolution results in verifier error.
        // verify with wrong resolution results in verifier error.
    }

    #[test_log::test]
    fn sys_verify_integrity() {
        let spec = &MultiTestSpec::SysVerifyIntegrity {
            claim_words: to_vec(&hello_commit_receipt().claim().unwrap().as_value().unwrap())
                .unwrap(),
        };

        // Test that providing the proven assumption results in an unconditional
        // receipt.
        let env = ExecutorEnv::builder()
            .write(&spec)
            .unwrap()
            .add_assumption(hello_commit_receipt().clone())
            .build()
            .unwrap();
        prove_elf(env, MULTI_TEST_ELF)
            .unwrap()
            .verify_with_context(&VerifierContext::default(), MULTI_TEST_ID)
            .unwrap();

        // Test that proving without a provided assumption results in an execution
        // failure.
        let env = ExecutorEnv::builder()
            .write(&spec)
            .unwrap()
            .build()
            .unwrap();
        assert!(prove_elf(env, MULTI_TEST_ELF).is_err());

        // Test that providing an unresolved assumption results in a conditional
        // receipt.
        let env = ExecutorEnv::builder()
            .write(&spec)
            .unwrap()
            .add_assumption(hello_commit_receipt().claim().unwrap())
            .build()
            .unwrap();
        // TODO(#982) Conditional receipts currently return an error on verification.
        assert!(prove_elf(env, MULTI_TEST_ELF).is_err());
    }

    #[test_log::test]
    fn sys_verify_integrity_halt_1() {
        // Generate a receipt for an execution ending in a guest error indicated
        // by ExitCode::Halted(1).
        let halt_receipt = prove_halt(1);

        let spec = &MultiTestSpec::SysVerifyIntegrity {
            claim_words: to_vec(halt_receipt.claim().unwrap().as_value().unwrap()).unwrap(),
        };

        // Test that proving results in a success execution and unconditional receipt.
        let env = ExecutorEnv::builder()
            .write(&spec)
            .unwrap()
            .add_assumption(halt_receipt)
            .build()
            .unwrap();
        prove_elf(env, MULTI_TEST_ELF)
            .unwrap()
            .verify_with_context(&VerifierContext::default(), MULTI_TEST_ID)
            .unwrap();
    }

    #[test_log::test]
    fn sys_verify_assumption() {
        let test_circuit_receipt = prove_test_recursion_circuit();
        let test_circuit_assumption = Assumption {
            claim: test_circuit_receipt.claim.digest(),
            control_root: test_circuit_receipt.control_root().unwrap(),
        };
        let spec = &MultiTestSpec::SysVerifyAssumption {
            assumption_words: to_vec(&test_circuit_assumption).unwrap(),
        };

        // Test that we can produce a verifying CompositeReceipt.
        let env = ExecutorEnv::builder()
            .write(&spec)
            .unwrap()
            .add_assumption(test_circuit_receipt.clone())
            .build()
            .unwrap();
        let receipt = prove_elf(env, MULTI_TEST_ELF).unwrap();
        receipt
            .verify_with_context(&VerifierContext::default(), MULTI_TEST_ID)
            .unwrap();
        // Double-check that the result is a composite receipt.
        receipt.inner.composite().unwrap();

        // Test that we can produce a verifying SuccinctReceipt.
        let env = ExecutorEnv::builder()
            .write(&spec)
            .unwrap()
            .add_assumption(test_circuit_receipt.clone())
            .build()
            .unwrap();
        let receipt = prove_elf_succinct(env, MULTI_TEST_ELF).unwrap();
        receipt
            .verify_with_context(&VerifierContext::default(), MULTI_TEST_ID)
            .unwrap();
        // Double-check that the result is a succinct receipt.
        receipt.inner.succinct().unwrap();

        // Test that proving without a provided assumption results in an execution
        // failure.
        let env = ExecutorEnv::builder()
            .write(&spec)
            .unwrap()
            .build()
            .unwrap();
        assert!(prove_elf(env, MULTI_TEST_ELF).is_err());
    }

    #[test_log::test]
    fn sys_prove_zkr() {
        // Random Poseidon2 "digest" to act as the "control root".
        let suite = Poseidon2HashSuite::new_suite();
        let (program, control_id) = zkr::test_recursion_circuit(&suite.name).unwrap();
        register_zkr(&control_id, move || Ok(program.clone()));
        let control_tree = MerkleGroup::new(vec![control_id]).unwrap();
        let control_root = control_tree.calc_root(suite.hashfn.as_ref());

        let inner_claim_digest =
            digest!("00000000000000de00000000000000ad00000000000000be00000000000000ef");
        let claim_digest =
            digest!("a558268a11892374b41d03857a40cdc5e87e351a3bfc17aa2054f47712a17bc3");

        let mut input: Vec<u32> = Vec::new();
        input.extend(control_root.as_words());
        input.extend(inner_claim_digest.as_words());

        let spec = &MultiTestSpec::SysProveZkr {
            control_id,
            input,
            claim_digest,
            control_root,
        };

        // Test that we can produce a verifying Receipt.
        let env = ExecutorEnv::builder()
            .write(&spec)
            .unwrap()
            .build()
            .unwrap();
        let opts = ProverOpts::succinct().with_control_ids(control_tree.leaves);
        get_prover_server(&opts)
            .unwrap()
            .prove(env, MULTI_TEST_ELF)
            .unwrap()
            .receipt
            .verify(MULTI_TEST_ID)
            .unwrap();
    }

    struct Coprocessor {
        pub(crate) zkr_requests: Vec<ProveZkrRequest>,
        pub(crate) keccak_requests: Vec<ProveKeccakRequest>,
    }

    impl Coprocessor {
        fn new() -> Self {
            Self {
                zkr_requests: vec![],
                keccak_requests: vec![],
            }
        }
    }

    impl CoprocessorCallback for Coprocessor {
        fn prove_zkr(&mut self, proof_request: ProveZkrRequest) -> anyhow::Result<()> {
            self.zkr_requests.push(proof_request);
            Ok(())
        }

        fn prove_keccak(&mut self, proof_request: ProveKeccakRequest) -> anyhow::Result<()> {
            self.keccak_requests.push(proof_request);
            Ok(())
        }
    }

    #[test_log::test]
    fn sys_prove_zkr_noop() {
        let suite = Poseidon2HashSuite::new_suite();
        let (_, control_id) = zkr::test_recursion_circuit(&suite.name).unwrap();
        let control_tree = MerkleGroup::new(vec![control_id]).unwrap();
        let control_root = control_tree.calc_root(suite.hashfn.as_ref());

        let inner_claim_digest =
            digest!("00000000000000de00000000000000ad00000000000000be00000000000000ef");
        let test_receipt = test_zkr(&control_root, &inner_claim_digest, RECURSION_PO2).unwrap();

        let claim_digest =
            digest!("a558268a11892374b41d03857a40cdc5e87e351a3bfc17aa2054f47712a17bc3");

        let mut input: Vec<u32> = Vec::new();
        input.extend(control_root.as_words());
        input.extend(inner_claim_digest.as_words());

        let spec = &MultiTestSpec::SysProveZkr {
            control_id,
            input,
            claim_digest,
            control_root,
        };

        let coprocessor = Rc::new(RefCell::new(Coprocessor::new()));

        let env = ExecutorEnv::builder()
            .coprocessor_callback_ref(coprocessor.clone())
            .add_assumption(test_receipt)
            .write(&spec)
            .unwrap()
            .build()
            .unwrap();
        let session = execute_elf(env, MULTI_TEST_ELF).unwrap();
        assert_eq!(session.exit_code, ExitCode::Halted(0));

        // Because we added an already proven assumption, there should be no
        // request to invoke the coprocessor.
        assert!(coprocessor.borrow().zkr_requests.is_empty());
        assert!(coprocessor.borrow().keccak_requests.is_empty());
    }
}

#[ignore]
#[test_log::test]
fn run_unconstrained() -> Result<()> {
    const RUN_UNCONSTRAINED_PO2: u32 = 17;
    const RUN_UNCONSTRAINED_CYCLES: u64 = 1 << RUN_UNCONSTRAINED_PO2;

    for unconstrained in [false, true] {
        let spec = MultiTestSpec::RunUnconstrained {
            unconstrained,
            cycles: RUN_UNCONSTRAINED_CYCLES,
        };
        let env = ExecutorEnv::builder()
            .segment_limit_po2(RUN_UNCONSTRAINED_PO2)
            .write(&spec)
            .unwrap()
            .build()
            .unwrap();
        let session = Executor2::from_elf(env, MULTI_TEST_ELF)?.run()?;
        let receipt = prove_session(&session).unwrap();
        let segments = &receipt.inner.composite().unwrap().segments;

        if unconstrained {
            // Test
            assert_eq!(segments.len(), 1);
        } else {
            // Control
            assert_eq!(
                segments.len(),
                2,
                "Expecting 2 segments; adjust RUN_UNCONSTRAINED_CYCLES here, or CYCLES_PER_LOOP in multi_test?"
            );
        }
    }
    Ok(())
}

mod soundness {
    // use risc0_circuit_rv32im::{prove::emu::exec::DEFAULT_SEGMENT_LIMIT_PO2, CIRCUIT};
    use risc0_circuit_rv32im_v2::{execute::DEFAULT_SEGMENT_LIMIT_PO2, CircuitImpl};
    use risc0_zkp::{
        adapter::TapsProvider,
        field::{
            baby_bear::{BabyBear, BabyBearExtElem},
            ExtElem,
        },
        hal::cpu::CpuHal,
        prove::soundness,
    };

    #[test_log::test]
    fn proven() {
        let cycles = 1 << DEFAULT_SEGMENT_LIMIT_PO2;
        let ext_size = BabyBearExtElem::EXT_SIZE;
        let coeffs_size = cycles * ext_size;
        let circuit = CircuitImpl;
        let taps = circuit.get_taps();

        let security = soundness::proven::<CpuHal<BabyBear>>(taps, coeffs_size);
        assert_eq!(security, 41.56704);
    }

    #[test_log::test]
    fn conjectured_strict() {
        let cycles = 1 << DEFAULT_SEGMENT_LIMIT_PO2;
        let ext_size = BabyBearExtElem::EXT_SIZE;
        let coeffs_size = cycles * ext_size;
        let circuit = CircuitImpl;
        let taps = circuit.get_taps();

        let security = soundness::conjectured_strict::<CpuHal<BabyBear>>(taps, coeffs_size);
        assert_eq!(security, 74.87678);
    }

    #[test_log::test]
    fn toy_model() {
        let cycles: usize = 1 << DEFAULT_SEGMENT_LIMIT_PO2;
        let ext_size = BabyBearExtElem::EXT_SIZE;
        let coeffs_size = cycles * ext_size;
        let circuit = CircuitImpl;
        let taps = circuit.get_taps();

        let security = soundness::toy_model_security::<CpuHal<BabyBear>>(taps, coeffs_size);
        assert_eq!(security, 97.14198);
    }
}
