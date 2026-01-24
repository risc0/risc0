// Copyright 2026 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
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
    CommitSingleKeccak,
    DoNothing,
    DoRandom,
    Echo {
        bytes: Vec<u8>,
    },
    /// Read from the given file descriptor in a loop until EOF, writing to stdout.
    /// Uses a buffer of `nbytes` size for each read operation. This tests POSIX-style
    /// reading with a fixed-size buffer, where the total amount of data read may
    /// exceed the buffer size.
    EchoStdout {
        /// Buffer size for each read operation (not the total amount to read).
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
    KeccakProve {
        claim_digest: Digest,
        po2: u32,
    },
    KeccakUnion(usize),
    KeccakUpdate,
    KeccakUpdate2,
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
