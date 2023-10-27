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

#![doc = include_str!("../README.md")]
#![cfg_attr(not(feature = "std"), no_std)]
#![deny(rustdoc::broken_intra_doc_links)]
#![deny(missing_docs)]

extern crate alloc;
mod fault_ids;
pub use fault_ids::{FAULT_CHECKER_ELF, FAULT_CHECKER_ID};

#[cfg(feature = "fault-proof")]
mod fault_monitor;
pub mod guest;
#[cfg(not(target_os = "zkvm"))]
mod host;
pub mod serde;
pub mod sha;

use semver::Version;

/// Re-exports for recursion
#[cfg(not(target_os = "zkvm"))]
#[cfg(feature = "prove")]
pub mod recursion {
    pub use super::host::recursion::*;
}

pub use anyhow::Result;
#[cfg(not(target_os = "zkvm"))]
#[cfg(any(feature = "client", feature = "prove"))]
pub use bytes::Bytes;
#[cfg(not(target_os = "zkvm"))]
pub use risc0_binfmt::{MemoryImage, Program, SystemState};
pub use risc0_zkvm_platform::{declare_syscall, memory::GUEST_MAX_MEM, PAGE_SIZE};

#[cfg(feature = "fault-proof")]
pub use self::fault_monitor::FaultCheckMonitor;
#[cfg(not(target_os = "zkvm"))]
#[cfg(feature = "profiler")]
#[cfg(feature = "prove")]
pub use self::host::server::exec::profiler::Profiler;
#[cfg(not(target_os = "zkvm"))]
#[cfg(feature = "prove")]
pub use self::host::{
    api::server::Server as ApiServer,
    client::prove::local::LocalProver,
    server::{
        exec::executor::ExecutorImpl,
        prove::{get_prover_server, loader::Loader, HalPair, ProverServer},
        session::{FileSegmentRef, Segment, SegmentRef, Session, SessionEvents, SimpleSegmentRef},
    },
};
#[cfg(not(target_os = "zkvm"))]
#[cfg(feature = "client")]
pub use self::host::{
    api::{
        client::Client as ApiClient, Asset, AssetRequest, Binary, Connector, SegmentInfo,
        SessionInfo,
    },
    client::{
        env::{ExecutorEnv, ExecutorEnvBuilder},
        exec::TraceEvent,
        prove::{
            bonsai::BonsaiProver, default_executor, default_prover, external::ExternalProver,
            Executor, Prover, ProverOpts,
        },
    },
};
#[cfg(not(target_os = "zkvm"))]
pub use self::host::{
    control_id::POSEIDON_CONTROL_ID,
    receipt::{
        ExitCode, InnerReceipt, Journal, Receipt, ReceiptMetadata, SegmentReceipt, SegmentReceipts,
        VerifierContext,
    },
    recursion::{SuccinctReceipt, ALLOWED_IDS_ROOT},
};

/// Reports the current version of this crate.
pub const VERSION: &str = env!("CARGO_PKG_VERSION");

/// Reports the current version of this crate as represented by a
/// [semver::Version].
pub fn get_version() -> Result<Version, semver::Error> {
    Version::parse(VERSION)
}

/// Align the given address `addr` upwards to alignment `align`.
///
/// Requires that `align` is a power of two.
pub const fn align_up(addr: usize, align: usize) -> usize {
    (addr + align - 1) & !(align - 1)
}

/// Returns `true` if dev mode is enabled.
#[cfg(feature = "std")]
pub fn is_dev_mode() -> bool {
    let is_env_set = std::env::var("RISC0_DEV_MODE")
        .ok()
        .map(|x| x.to_lowercase())
        .filter(|x| x == "1" || x == "true" || x == "yes")
        .is_some();

    if cfg!(feature = "disable-dev-mode") && is_env_set {
        panic!("zkVM: Inconsistent settings -- please resolve. \
            The RISC0_DEV_MODE environment variable is set but dev mode has been disabled by feature flag.");
    }

    cfg!(not(feature = "disable-dev-mode")) && is_env_set
}
