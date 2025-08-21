// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

// Definitions for test selection codes used by the "multi_test" test.
extern crate alloc;

use alloc::vec::Vec;

use risc0_zkvm::sha::Digest;
use risc0_zkvm_platform::syscall::bigint;
use serde::{Deserialize, Serialize};

#[derive(Serialize, Deserialize, Debug, PartialEq, Eq)]
pub enum MultiTestSpec {
    AlignedAlloc,
    AllocZeroed,
    BigInt {
        count: u32,
        x: [u32; bigint::WIDTH_WORDS],
        y: [u32; bigint::WIDTH_WORDS],
        modulus: [u32; bigint::WIDTH_WORDS],
    },
    BigIntRaw {
        result: u32,
        x: u32,
        y: u32,
        modulus: u32,
    },
    BusyLoop {
        /// Busy loop until the guest has run for at least this number of cycles
        cycles: u64,
    },
    DoNothing,
    DoRandom,
    Echo {
        bytes: Vec<u8>,
    },
    EchoStdout {
        nbytes: u32,
        fd: u32,
    },
    EchoWords {
        fd: u32,
        nwords: u32,
    },
    EventTrace,
    Fault,
    Halt(u8),
    KeccakUpdate,
    KeccakUpdate2,
    KeccakUnion(usize),
    LibM,
    Oom,
    OutOfBounds,
    OutOfBoundsEcall,
    Panic,
    PauseResume(u8),
    Poseidon2Basic,
    Poseidon2Continue,
    Poseidon2Long,
    Poseidon2Short,
    Profiler,
    ReadWriteMem {
        /// Tuples of (address, value). Zero means read the value and
        /// output it; nonzero means write that value.
        values: Vec<(u32, u32)>,
    },
    RsaCompat,
    RunUnconstrained {
        // True to actually call run_unconstrained, false to run the busy loop directly as a control.
        unconstrained: bool,
        // Number of guest cycles to use, including startup.
        cycles: u64,
    },
    ShaConforms,
    ShaCycleCount,
    ShaDigest {
        data: Vec<u8>,
    },
    ShaDigestIter {
        data: Vec<u8>,
        num_iter: u32,
    },
    ShaSingleKeccak,
    SysFork,
    SysForkFork,
    SysForkJournalPanic,
    SysInput(Digest),
    SysKeccak,
    SysLogInvalidAddr,
    SysRead {
        // Buffer to read to
        buf: Vec<u8>,
        fd: u32,
        // Position and length to do reads
        pos_and_len: Vec<(u32, u32)>,
    },
    SysVerify(Vec<(Digest, Vec<u8>)>),
    SysVerifyIntegrity {
        // ReceiptClaim: Field is serialized to avoid circular dependency issues.
        claim_words: Vec<u32>,
    },
    SysVerifyAssumption {
        // Assumption: Field is serialized to avoid circular dependency issues.
        assumption_words: Vec<u32>,
    },
    TooManySha,
}
