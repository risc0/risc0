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

use std::sync::OnceLock;

use anyhow::Result;
use risc0_binfmt::{MemoryImage, PovwJobId, PovwLogId, PovwNonce};
use risc0_circuit_rv32im::TerminateState;
use risc0_zkp::{core::digest::Digest, verify::VerificationError};
use risc0_zkvm_methods::{MULTI_TEST_ELF, MULTI_TEST_ID, multi_test::MultiTestSpec};
use risc0_zkvm_platform::{WORD_SIZE, memory};
use rstest::rstest;

use super::get_prover_server;
use crate::{
    ExecutorEnv, ExitCode, InnerReceipt, ProveInfo, ProverOpts, Receipt, ReceiptKind, Session,
    SimpleSegmentRef, SuccinctReceiptVerifierParameters, VerifierContext,
    host::server::{exec::executor::ExecutorImpl, testutils},
    serde::{from_slice, to_vec},
    sha::Digestible,
};

#[allow(dead_code)]
fn prove_nothing(kind: ReceiptKind) -> ProveInfo {
    match kind {
        ReceiptKind::Composite => prove_nothing_composite(),
        ReceiptKind::Succinct => prove_nothing_succinct(),
        ReceiptKind::Groth16 => prove_nothing_groth16(),
    }
}

fn prove_nothing_impl(kind: ReceiptKind) -> ProveInfo {
    let opts = ProverOpts::default().with_receipt_kind(kind);
    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::DoNothing)
        .unwrap()
        .build()
        .unwrap();
    get_prover_server(&opts)
        .unwrap()
        .prove(env, MULTI_TEST_ELF)
        .unwrap()
}

fn prove_nothing_composite() -> ProveInfo {
    static ONCE: OnceLock<ProveInfo> = OnceLock::new();
    ONCE.get_or_init(|| prove_nothing_impl(ReceiptKind::Composite))
        .clone()
}

fn prove_nothing_succinct() -> ProveInfo {
    static ONCE: OnceLock<ProveInfo> = OnceLock::new();
    ONCE.get_or_init(|| prove_nothing_impl(ReceiptKind::Succinct))
        .clone()
}

#[allow(dead_code)]
fn prove_nothing_groth16() -> ProveInfo {
    static ONCE: OnceLock<ProveInfo> = OnceLock::new();
    ONCE.get_or_init(|| prove_nothing_impl(ReceiptKind::Groth16))
        .clone()
}

fn execute_elf(env: ExecutorEnv, elf: &[u8]) -> Result<Session> {
    ExecutorImpl::from_elf(env, elf)
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

#[test_log::test]
#[cfg_attr(all(ci, not(ci = "slow")), ignore = "slow test")]
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
    // ensure that we got a succinct receipt.
    prove_nothing_succinct().receipt.inner.succinct().unwrap();
}

#[test_log::test]
fn verifier_parameters_mismatch() {
    let receipt = prove_nothing_succinct().receipt;

    // Construct a different set of verifier parameters. Doesn't really matter in what way it is
    // different as long as it is a different control root.
    let verifier_ctx = VerifierContext::default()
        .with_succinct_verifier_parameters(SuccinctReceiptVerifierParameters::from_max_po2(14));
    let err = receipt
        .verify_integrity_with_context(&verifier_ctx)
        .unwrap_err();

    assert!(matches!(
        err,
        VerificationError::VerifierParametersMismatch { .. }
    ));
}

/// We don't currently support a hashfn value other than "poseidon2", so we are testing that we get
/// an error if you try to create a proof using that hashfn, or if you try to verify a receipt that
/// is using that hashfn.
#[test_log::test]
fn sha256_hashfn_fails() {
    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::DoNothing)
        .unwrap()
        .build()
        .unwrap();
    let opts = ProverOpts::fast().with_hashfn("sha-256".into());
    let err = get_prover_server(&opts)
        .unwrap()
        .prove(env, MULTI_TEST_ELF)
        .map(|_| ())
        .unwrap_err();
    assert_eq!(
        err.to_string(),
        "provided `ProverOpts` has unsupported `hashfn` value of \"sha-256\"; \
        supported `hashfn` values are: \"poseidon2\"."
    );

    let mut info = prove_nothing_composite();
    let InnerReceipt::Composite(composite_receipt) = &mut info.receipt.inner else {
        panic!("unexpected receipt type");
    };
    for seg in &mut composite_receipt.segments {
        seg.hashfn = "sha-256".into();
    }

    let err = info.receipt.verify(MULTI_TEST_ID).unwrap_err();
    assert_eq!(err, VerificationError::InvalidHashSuite);
}

#[test_log::test]
fn receipt_serde() {
    let receipt = prove_nothing_composite().receipt;
    let encoded: Vec<u32> = to_vec(&receipt).unwrap();
    let decoded: Receipt = from_slice(&encoded).unwrap();
    assert_eq!(decoded, receipt);
    let ctx = VerifierContext::default();
    decoded.verify_with_context(&ctx, MULTI_TEST_ID).unwrap();
}

#[test_log::test]
fn check_image_id() {
    let receipt = prove_nothing_composite().receipt;
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
#[cfg_attr(all(ci, not(ci = "slow")), ignore = "slow test")]
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
#[cfg_attr(all(ci, not(ci = "slow")), ignore = "slow test")]
fn bigint_accel() {
    let cases = testutils::generate_bigint_test_cases(10);
    for case in cases {
        println!("Running BigInt circuit test case: {case:08x?}");
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
        let mut exec = ExecutorImpl::from_elf(env, MULTI_TEST_ELF).unwrap();
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
        let session = ExecutorImpl::from_kernel_elf(env, elf)
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
    let mut exec = ExecutorImpl::from_elf(env, MULTI_TEST_ELF).unwrap();

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
    let mut exec = ExecutorImpl::from_elf(env, MULTI_TEST_ELF).unwrap();

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

    let program = risc0_circuit_rv32im::execute::testutil::kernel::simple_loop(200);
    let image = MemoryImage::new_kernel(program);

    let env = ExecutorEnv::builder()
        .segment_limit_po2(13) // 8k cycles
        .build()
        .unwrap();
    let session = ExecutorImpl::new(env, image).unwrap().run().unwrap();
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
    let mut exec = ExecutorImpl::from_elf(env, MULTI_TEST_ELF).unwrap();
    let session = exec.run().unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));
    prove_session(&session).unwrap();
}

#[rstest]
#[case(ReceiptKind::Composite, ReceiptKind::Composite)]
#[case(ReceiptKind::Composite, ReceiptKind::Succinct)]
#[case(ReceiptKind::Composite, ReceiptKind::Groth16)]
#[case(ReceiptKind::Succinct, ReceiptKind::Composite)]
#[case(ReceiptKind::Succinct, ReceiptKind::Succinct)]
#[case(ReceiptKind::Succinct, ReceiptKind::Groth16)]
#[case(ReceiptKind::Groth16, ReceiptKind::Composite)]
#[case(ReceiptKind::Groth16, ReceiptKind::Succinct)]
#[case(ReceiptKind::Groth16, ReceiptKind::Groth16)]
#[test_log::test]
#[cfg(any(feature = "cuda", feature = "docker"))]
fn compress(#[case] from: ReceiptKind, #[case] into: ReceiptKind) {
    let from_receipt = prove_nothing(from).receipt;
    let opts = ProverOpts::default().with_receipt_kind(into);
    let prover = get_prover_server(&opts).unwrap();
    let receipt = prover.compress(&opts, &from_receipt).unwrap();
    match from {
        ReceiptKind::Composite => match receipt.inner {
            InnerReceipt::Composite(_) | InnerReceipt::Succinct(_) | InnerReceipt::Groth16(_) => {}
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

#[rstest]
#[case(ReceiptKind::Groth16, ReceiptKind::Composite)]
#[case(ReceiptKind::Groth16, ReceiptKind::Succinct)]
#[case(ReceiptKind::Groth16, ReceiptKind::Groth16)]
#[test_log::test]
#[cfg(any(feature = "cuda", feature = "docker"))]
fn fake_compress(#[case] from: ReceiptKind, #[case] into: ReceiptKind) {
    use crate::{DevModeProver, FakeReceipt, ProverServer as _};

    let from_receipt = prove_nothing(from).receipt;
    let opts = ProverOpts::default().with_receipt_kind(into);
    let fake = Receipt::new(
        InnerReceipt::Fake(FakeReceipt {
            claim: from_receipt.claim().unwrap(),
        }),
        from_receipt.clone().journal.bytes,
    );

    let prover = DevModeProver::new();
    let receipt = prover.compress(&opts.with_dev_mode(true), &fake).unwrap();
    let InnerReceipt::Fake(_) = receipt.inner else {
        panic!("expected fake receipt");
    };
}

#[test_log::test]
#[cfg(feature = "cuda")]
fn shrink_wrap() {
    // Perform many proofs in parallel. The initial implementation of the
    // groth16 prover on CUDA had issues with this. Ensure that we got a groth16
    // receipt.

    use rayon::prelude::*;
    (0..5).into_par_iter().for_each(|_| {
        prove_nothing_impl(ReceiptKind::Groth16)
            .receipt
            .inner
            .groth16()
            .unwrap();
    });
}

#[rstest]
#[case(ReceiptKind::Composite)]
#[case(ReceiptKind::Succinct)]
#[case(ReceiptKind::Groth16)]
#[test_log::test]
#[cfg(any(feature = "cuda", feature = "docker"))]
fn verify_in_guest(#[case] kind: ReceiptKind) {
    use risc0_zkvm_methods::VERIFY_ELF;

    let receipt = prove_nothing(kind).receipt;
    let input: (_, Digest, bool) = (
        receipt.clone(),
        MULTI_TEST_ID.into(),
        /* dev_mode */ false,
    );
    let env = ExecutorEnv::builder()
        .write(&input)
        .unwrap()
        .build()
        .unwrap();
    let session = ExecutorImpl::from_elf(env, VERIFY_ELF)
        .unwrap()
        .run()
        .unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));
    println!("{:?}", session.stats());
}

mod sys_verify {
    use std::sync::OnceLock;

    use risc0_zkp::{core::hash::poseidon2::Poseidon2HashSuite, digest};
    use risc0_zkvm_methods::{HELLO_COMMIT_ELF, HELLO_COMMIT_ID};

    use super::*;
    use crate::{
        Assumption, RECURSION_PO2, SuccinctReceipt, Unknown,
        recursion::{MerkleGroup, prove::zkr, test_zkr},
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
    fn sys_verify_with_povw() -> Result<()> {
        let spec = MultiTestSpec::SysVerify(vec![(
            HELLO_COMMIT_ID.into(),
            hello_commit_receipt().journal.bytes.clone(),
        )]);

        // Test that providing the proven assumption results in an unconditional
        // receipt.
        let povw_job_id: PovwJobId = rand::random();
        let env = ExecutorEnv::builder()
            .write(&spec)
            .unwrap()
            .add_assumption(hello_commit_receipt().clone())
            .povw(povw_job_id)
            .build()
            .unwrap();

        let opts = ProverOpts::succinct();
        let prove_info = get_prover_server(&opts)?.prove(env, MULTI_TEST_ELF)?;

        prove_info.receipt.verify(MULTI_TEST_ID)?;
        let work_receipt = prove_info.work_receipt.unwrap();
        work_receipt.verify_integrity()?;

        // NOTE: The work claim will only contain value for the conditional receipt.
        // PoVW value for the assumption receipts is considered seperately, instead of in the take
        // WorkClaim (i.e. the same compact range representation).
        let work_claim = work_receipt.claim().as_value()?.clone();
        assert_eq!(
            work_claim.claim.digest(),
            prove_info.receipt.claim()?.digest()
        );
        let work = work_claim.work.value()?;
        assert!(work.value > 0);
        assert_eq!(work.nonce_min.log, povw_job_id.log);
        assert_eq!(work.nonce_min.job, povw_job_id.job);
        assert_eq!(work.nonce_min.segment, 0);
        assert_eq!(work.nonce_max.log, povw_job_id.log);
        assert_eq!(work.nonce_max.job, povw_job_id.job);
        // We expect that the verify action only takes one segment.
        assert_eq!(work.nonce_max.segment, 0);
        Ok(())
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
        let session = ExecutorImpl::from_elf(env, MULTI_TEST_ELF)?.run()?;
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

#[test_log::test]
fn povw_nonce_assignment() -> Result<()> {
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
    let session = ExecutorImpl::from_elf(env, MULTI_TEST_ELF)?.run()?;
    let receipt = prove_session(&session).unwrap();
    let segments = &receipt.inner.composite().unwrap().segments;
    for (i, segment) in segments.iter().enumerate() {
        segment
            .verify_integrity_with_context(&VerifierContext::default())
            .unwrap();
        assert_eq!(segment.povw_nonce().unwrap(), povw_job_id.nonce(i as u32));
    }
    Ok(())
}

#[test_log::test]
fn povw_nonce_default_assignment() -> Result<()> {
    let spec = MultiTestSpec::BusyLoop { cycles: 1 << 18 };
    let env = ExecutorEnv::builder()
        .write(&spec)
        .unwrap()
        .segment_limit_po2(17)
        .build()
        .unwrap();
    let session = ExecutorImpl::from_elf(env, MULTI_TEST_ELF)?.run()?;
    let receipt = prove_session(&session).unwrap();
    let segments = &receipt.inner.composite().unwrap().segments;
    for segment in segments.iter() {
        segment
            .verify_integrity_with_context(&VerifierContext::default())
            .unwrap();
        assert_eq!(segment.povw_nonce().unwrap(), PovwNonce::default());
    }
    Ok(())
}

#[test_log::test]
fn povw_prove_work_receipt() -> Result<()> {
    let segment_limit_po2 = 16; // 64k cycles
    let cycles = 1 << segment_limit_po2;
    let povw_job_id: PovwJobId = rand::random();
    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::BusyLoop { cycles })
        .unwrap()
        .segment_limit_po2(segment_limit_po2)
        .povw(povw_job_id)
        .build()
        .unwrap();

    let opts = ProverOpts::succinct();
    let prove_info = get_prover_server(&opts)?.prove(env, MULTI_TEST_ELF)?;

    prove_info.receipt.verify(MULTI_TEST_ID)?;
    let work_receipt = prove_info.work_receipt.unwrap();
    work_receipt.verify_integrity()?;

    let work_claim = work_receipt.claim().as_value()?.clone();
    assert_eq!(
        work_claim.claim.digest(),
        prove_info.receipt.claim()?.digest()
    );
    let work = work_claim.work.value()?;
    assert!(work.value >= 1 << 16);
    assert_eq!(work.nonce_min.log, povw_job_id.log);
    assert_eq!(work.nonce_min.job, povw_job_id.job);
    assert_eq!(work.nonce_min.segment, 0);
    assert_eq!(work.nonce_max.log, povw_job_id.log);
    assert_eq!(work.nonce_max.job, povw_job_id.job);
    assert!(work.nonce_max.segment > 0);
    Ok(())
}

mod soundness {
    // use risc0_circuit_rv32im::{prove::emu::exec::DEFAULT_SEGMENT_LIMIT_PO2, CIRCUIT};
    use risc0_circuit_rv32im::{CircuitImpl, execute::DEFAULT_SEGMENT_LIMIT_PO2};
    use risc0_zkp::{
        adapter::TapsProvider,
        field::{
            ExtElem,
            baby_bear::{BabyBear, BabyBearExtElem},
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
