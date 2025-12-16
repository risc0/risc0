// Copyright 2025 RISC Zero, Inc.
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

#![cfg_attr(not(feature = "std"), no_std)]
#![deny(rustdoc::broken_intra_doc_links)]
#![deny(missing_docs)]
#![cfg_attr(docsrs, feature(doc_cfg))]

//! The RISC Zero zkVM is a RISC-V virtual machine that produces [zero-knowledge
//! proofs] of code it executes. By using the zkVM, a cryptographic [receipt] is
//! produced which anyone can [verify][receipt-verify] was produced by the
//! zkVM's guest code. No additional information about the code execution (such
//! as, for example, the inputs provided) is revealed by publishing the
//! [receipt].
//!
//! Additional (non-reference) resources for using our zkVM that you may also
//! find helpful, especially if you're new to the RISC Zero zkVM. These include:
//!
//! * Our [zkVM Tutorial], which walks you through writing your first zkVM
//!   project.
//! * The [`cargo risczero` tool]. It includes a `new` command which generates
//!   code for building and launching a zkVM guest and guidance on where
//!   projects most commonly modify host and guest code.
//! * The [examples], which contains various examples using our zkVM.
//! * [This clip][zkHack] from our presentation at ZK Hack III gives an overview
//!   of the RISC Zero zkVM. [Our YouTube channel][YouTube] has many more videos
//!   as well.
//! * We track zkVM issues with known workarounds using the [rust guest
//!   workarounds] GitHub tag. If you're having problems running your code in
//!   the zkVM, you can see if there's a workaround, and if you're using a
//!   workaround, you can track when it gets resolved to a permanent solution.
//! * And more on [the RISC Zero developer website][dev-docs]!
//!
//! # Crate Feature Flags
//!
//! The following feature flags are supported.
//!
//! Note that in order to use `risc0-zkvm` in the guest, you must disable the
//! default features by setting `default-features = false`.
//!
//! | Feature          | Target(s)         | Implies    | Description                                                                                                                                                  |
//! | ---------------- | ----------------- | ---------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------ |
//! | client           | all except rv32im | std        | Enables the client API.                                                                                                                                      |
//! | cuda             |                   | prove, std | Enables CUDA GPU acceleration for the prover. Requires CUDA toolkit to be installed.                                                                         |
//! | disable-dev-mode | all except rv32im |            | Disables dev mode so that proving and verifying may not be faked. Used to prevent a misplaced `RISC0_DEV_MODE` from breaking security in production systems. |
//! | metal            | macos             | prove, std | Deprecated - Metal GPU acceleration for the prover is now enabled by default on Apple Silicon.                                                               |
//! | prove            | all except rv32im | std        | Enables the prover, incompatible within the zkvm guest.                                                                                                      |
//! | std              | all               |            | Support for the Rust stdlib.                                                                                                                                 |
//!
//! [`cargo risczero` tool]: https://crates.io/crates/cargo-risczero
//! [dev-docs]: https://dev.risczero.com
//! [examples]: https://dev.risczero.com/api/zkvm/examples
//! [receipt]: crate::receipt::Receipt
//! [receipt-verify]: crate::receipt::Receipt::verify
//! [rust guest workarounds]:
//!     https://github.com/risc0/risc0/issues?q=is%3Aissue+is%3Aopen+label%3A%22rust+guest+workarounds%22
//! [YouTube]: https://www.youtube.com/@risczero
//! [zero-knowledge proofs]: https://en.wikipedia.org/wiki/Zero-knowledge_proof
//! [zkHack]: https://youtu.be/cLqFvhmXiD0
//! [zkVM Tutorial]: https://dev.risczero.com/api/zkvm/tutorials/hello-world

extern crate alloc;

mod claim;
pub mod guest;
#[cfg(not(target_os = "zkvm"))]
mod host;
mod mmr;
mod receipt;
pub mod serde;
pub mod sha;

pub use ::serde::de::DeserializeOwned;
pub use anyhow::Result;
pub use risc0_binfmt::{ExitCode, InvalidExitCodeError, SystemState};
pub use risc0_zkp::{
    core::digest::{Digest, digest},
    verify::VerificationError,
};
pub use risc0_zkvm_platform::{PAGE_SIZE, align_up, declare_syscall, memory::GUEST_MAX_MEM};

#[cfg(not(target_os = "zkvm"))]
#[cfg(any(feature = "client", feature = "prove"))]
pub use bytes::Bytes;

#[cfg(not(target_os = "zkvm"))]
#[cfg(feature = "prove")]
pub use self::host::{
    client::prove::{local::LocalProver, local_executor},
    recursion::{
        self, RECURSION_PO2,
        prove::{prove_registered_zkr, prove_zkr, register_zkr},
    },
    server::{
        exec::executor::ExecutorImpl,
        prove::{
            HalPair, ProverServer,
            dev_mode::{DevModeDelay, DevModeProver},
            get_prover_server,
        },
        session::{
            FileSegmentRef, NullSegmentRef, PreflightResults, Segment, SegmentRef, Session,
            SessionEvents, SimpleSegmentRef,
        },
    },
};

#[cfg(not(target_os = "zkvm"))]
#[cfg(feature = "bonsai")]
pub use self::host::client::prove::bonsai::BonsaiProver;

#[cfg(not(target_os = "zkvm"))]
#[cfg(feature = "client")]
pub use {
    self::host::client::{
        env::{ExecutorEnv, ExecutorEnvBuilder},
        prove::{
            Executor, Prover, SegmentInfo, SessionInfo,
            default::DefaultProver,
            default_executor, default_prover,
            opts::{ProverOpts, ReceiptKind},
        },
    },
    risc0_circuit_rv32im::trace::{TraceCallback, TraceEvent},
};

/// TODO
#[cfg(not(target_os = "zkvm"))]
#[cfg(feature = "client")]
pub mod rpc {
    pub use super::host::rpc::*;
}

#[cfg(not(target_os = "zkvm"))]
#[cfg(feature = "client")]
pub use self::host::client::env::{CoprocessorCallback, ProveKeccakRequest};

#[cfg(not(target_os = "zkvm"))]
pub use {
    self::host::{
        prove_info::{ProveInfo, SessionStats},
        recursion::{ALLOWED_CONTROL_IDS, ALLOWED_CONTROL_ROOT, BN254_IDENTITY_CONTROL_ID},
    },
    risc0_binfmt::{compute_image_id, compute_kernel_id},
    risc0_groth16::Seal as Groth16Seal,
};

pub use self::{
    claim::{
        Unknown,
        maybe_pruned::{MaybePruned, PrunedValueError},
        merge::{Merge, MergeInequalityError},
        receipt::{Assumption, Assumptions, Input, Output, ReceiptClaim, UnionClaim},
        work::{Work, WorkClaim},
    },
    receipt::{
        AssumptionReceipt, CompositeReceipt, CompositeReceiptVerifierParameters, DEFAULT_MAX_PO2,
        FakeReceipt, GenericReceipt, Groth16Receipt, Groth16ReceiptVerifierParameters,
        InnerAssumptionReceipt, InnerReceipt, Journal, Receipt, ReceiptMetadata, SegmentReceipt,
        SegmentReceiptVerifierParameters, SuccinctReceipt, SuccinctReceiptVerifierParameters,
        VerifierContext,
    },
};

use semver::Version;

/// Reports the current version of this crate.
pub const VERSION: &str = env!("CARGO_PKG_VERSION");

/// Reports the current version of this crate as represented by a
/// [semver::Version].
pub fn get_version() -> Result<Version, semver::Error> {
    Version::parse(VERSION)
}

/// Returns `true` if dev mode is enabled.
#[cfg(feature = "std")]
#[deprecated(
    note = "dev-mode can be enabled programmatically, so this function is no longer authoritative. \
            Use `ProverOpts::is_dev_mode` or `VerifierContext::is_dev_mode`"
)]
pub fn is_dev_mode() -> bool {
    is_dev_mode_enabled_via_environment()
}

/// Returns `true` if the dev mode environment variable is enabled, the `disable-dev-mode` cfg flag
/// is not set, and we are not being compiled as a guest inside the zkvm.
#[cfg(all(feature = "std", not(target_os = "zkvm")))]
fn is_dev_mode_enabled_via_environment() -> bool {
    let is_env_set = std::env::var("RISC0_DEV_MODE")
        .ok()
        .map(|x| x.to_lowercase())
        .filter(|x| x == "1" || x == "true" || x == "yes")
        .is_some();

    let dev_mode_disabled = cfg!(feature = "disable-dev-mode");

    if dev_mode_disabled && is_env_set {
        panic!(
            "zkVM: Inconsistent settings -- please resolve. \
            The RISC0_DEV_MODE environment variable is set but dev mode has been disabled by feature flag."
        );
    }

    !dev_mode_disabled && is_env_set
}

/// Returns `true` if the dev mode environment variable is enabled, the `disable-dev-mode` cfg flag
/// is not set, and we are not being compiled as a guest inside the zkvm.
#[cfg(any(not(feature = "std"), target_os = "zkvm"))]
fn is_dev_mode_enabled_via_environment() -> bool {
    false
}

#[cfg(feature = "metal")]
#[test]
fn metal_implies_prove() {
    // we should be able to access prove feature items when metal has been enabled
    let _prover = get_prover_server(&ProverOpts::default());
}
