// Copyright 2024 RISC Zero, Inc.
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

pub(crate) mod bonsai;
pub(crate) mod external;
#[cfg(feature = "prove")]
pub(crate) mod local;

use std::{path::PathBuf, rc::Rc};

use anyhow::Result;
use serde::{Deserialize, Serialize};

use self::{bonsai::BonsaiProver, external::ExternalProver};
use crate::{
    host::prove_info::ProveInfo, is_dev_mode, ExecutorEnv, Receipt, SessionInfo, VerifierContext,
};

/// A Prover can execute a given ELF binary and produce a
/// [Receipt] that can be used to verify correct computation.
///
/// # Usage
/// To produce a proof, you must minimally provide an [ExecutorEnv] and an ELF
/// binary. See the [risc0_build](https://docs.rs/risc0-build/*/risc0_build)
/// crate for more information on producing ELF binaries from Rust source code.
///
/// ```rust
/// use risc0_zkvm::{
///     default_prover,
///     ExecutorEnv,
///     ProverOpts,
///     VerifierContext,
/// };
/// use risc0_zkvm_methods::FIB_ELF;
///
/// # #[cfg(not(feature = "cuda"))]
/// # {
/// // A straightforward case with an ELF binary
/// let env = ExecutorEnv::builder().write_slice(&[20]).build().unwrap();
/// let receipt = default_prover().prove(env, FIB_ELF).unwrap();
///
/// // Or you can specify a context and options
/// // (Using the defaults as we do here is equivalent to the above code.)
/// let env = ExecutorEnv::builder().write_slice(&[20]).build().unwrap();
/// let ctx = VerifierContext::default();
/// let opts = ProverOpts::default();
/// let receipt = default_prover().prove_with_ctx(env, &ctx, FIB_ELF, &opts).unwrap();
/// # }
/// ```
pub trait Prover {
    /// Return a name for this [Prover].
    fn get_name(&self) -> String;

    /// Prove zkVM execution starting from the specified ELF binary.
    fn prove(&self, env: ExecutorEnv<'_>, elf: &[u8]) -> Result<ProveInfo> {
        self.prove_with_ctx(
            env,
            &VerifierContext::default(),
            elf,
            &ProverOpts::default(),
        )
    }

    /// Prove zkVM execution starting from the specified ELF binary with the
    /// specified [VerifierContext] and [ProverOpts].
    fn prove_with_ctx(
        &self,
        env: ExecutorEnv<'_>,
        ctx: &VerifierContext,
        elf: &[u8],
        opts: &ProverOpts,
    ) -> Result<ProveInfo>;

    /// Compress a [Receipt], guaranteeing that the resulting receipt is of constant size.
    ///
    /// Proving will, by default, produce a [CompositeReceipt](crate::CompositeReceipt), which
    /// may contain an arbitrary number of receipts assembled into continuations and compositions.
    /// Together, these receipts collectively prove a top-level
    /// [ReceiptClaim](crate::ReceiptClaim). This function compresses all of the constituent
    /// receipts of a [CompositeReceipt](crate::CompositeReceipt) into a single
    /// [SuccinctReceipt](crate::SuccinctReceipt) that proves the same top-level claim. It
    /// accomplishes this by iterative application of the recursion programs including lift, join,
    /// and resolve.
    ///
    /// If the receipt is succinct, this function will do nothing (i.e. it is idemopotent).
    fn compress(&self, opts: &ProverOpts, receipt: &Receipt) -> Result<Receipt>;
}

/// An Executor can execute a given ELF binary.
pub trait Executor {
    /// Execute the specified ELF binary.
    ///
    /// This only executes the program and does not generate a receipt.
    fn execute(&self, env: ExecutorEnv<'_>, elf: &[u8]) -> Result<SessionInfo>;
}

/// Options to configure a [Prover].
#[derive(Clone, Serialize, Deserialize)]
pub struct ProverOpts {
    /// The hash function to use.
    pub hashfn: String,
    /// When false, only prove execution sessions that end in a successful
    /// [crate::ExitCode] (i.e. `Halted(0)` or `Paused(0)`).
    /// When set to true, any completed execution session will be proven, including indicated
    /// errors (e.g. `Halted(1)`) and sessions ending in `Fault`.
    // TODO(1.0): This option exists to avoid wasting resourcing proving a guest that exited with
    // Fault or another abnormal exit conditional. It is currently not consistently enforced, and
    // it seems like this might not be the right place for this option and it's not clear at the
    // moment if there is a better place. At some point before 1.0, this option should be moved or
    // dropped.
    pub prove_guest_errors: bool,
    /// The kind of receipt to be generated.
    pub receipt_kind: ReceiptKind,
}

/// This enum represents the various receipt kinds that can be generated.
#[derive(Clone, Serialize, Deserialize, PartialEq)]
pub enum ReceiptKind {
    /// Composite Receipts resulting from proving a session
    Composite,
    /// Succinct Receipts resulting from applying the lift and join programgs so Composite receipts
    Succinct,
    /// Compact Receipts resulting from stark2snark on the Succinct receipts
    Compact,
}

impl Default for ProverOpts {
    /// Return [ProverOpts] with the Poseidon2 hash function and
    /// `prove_guest_errors` set to false.
    fn default() -> Self {
        Self {
            hashfn: "poseidon2".to_string(),
            prove_guest_errors: false,
            receipt_kind: ReceiptKind::Composite,
        }
    }
}

impl ProverOpts {
    /// Choose the fastest prover options. May not be compatible with recursion.
    pub fn fast() -> Self {
        Self {
            hashfn: "sha-256".to_string(),
            prove_guest_errors: false,
            receipt_kind: ReceiptKind::Composite,
        }
    }

    /// Choose the prover that enables succinct receipts.
    pub fn succinct() -> Self {
        Self {
            hashfn: "poseidon2".to_string(),
            prove_guest_errors: false,
            receipt_kind: ReceiptKind::Succinct,
        }
    }

    /// Choose the prover that enables compact, snark receipts, only supported for x86_64 linux
    pub fn compact() -> Self {
        Self {
            hashfn: "poseidon2".to_string(),
            prove_guest_errors: false,
            receipt_kind: ReceiptKind::Compact,
        }
    }
}

/// Return a default [Prover] based on environment variables and feature flags.
///
/// The `RISC0_PROVER` environment variable, if specified, will select the
/// following [Prover] implementation:
/// * `bonsai`: [BonsaiProver] to prove on Bonsai.
/// * `local`: LocalProver to prove locally in-process. Note: this
///   requires the `prove` feature flag.
/// * `ipc`: [ExternalProver] to prove using an `r0vm` sub-process. Note: `r0vm`
///   must be installed. To specify the path to `r0vm`, use `RISC0_SERVER_PATH`.
///
/// If `RISC0_PROVER` is not specified, the following rules are used to select a
/// [Prover]:
/// * [BonsaiProver] if the `BONSAI_API_URL` and `BONSAI_API_KEY` environment
///   variables are set unless `RISC0_DEV_MODE` is enabled.
/// * LocalProver if the `prove` feature flag is enabled.
/// * [ExternalProver] otherwise.
pub fn default_prover() -> Rc<dyn Prover> {
    let explicit = std::env::var("RISC0_PROVER").unwrap_or_default();
    if !explicit.is_empty() {
        return match explicit.to_lowercase().as_str() {
            "bonsai" => Rc::new(BonsaiProver::new("bonsai")),
            "ipc" => Rc::new(ExternalProver::new("ipc", get_r0vm_path())),
            #[cfg(feature = "prove")]
            "local" => Rc::new(self::local::LocalProver::new("local")),
            _ => unimplemented!("Unsupported prover: {explicit}"),
        };
    }

    if !is_dev_mode()
        && std::env::var("BONSAI_API_URL").is_ok()
        && std::env::var("BONSAI_API_KEY").is_ok()
    {
        return Rc::new(BonsaiProver::new("bonsai"));
    }

    if cfg!(feature = "prove") {
        #[cfg(feature = "prove")]
        return Rc::new(self::local::LocalProver::new("local"));
    }

    Rc::new(ExternalProver::new("ipc", get_r0vm_path()))
}

/// Return a default [Executor] based on environment variables and feature
/// flags.
///
/// The `RISC0_EXECUTOR` environment variable, if specified, will select the
/// following [Executor] implementation:
/// * `local`: LocalProver to execute locally in-process. Note: this is
///   only available when the `prove` feature is enabled.
/// * `ipc`: [ExternalProver] to execute using an `r0vm` sub-process. Note:
///   `r0vm` must be installed. To specify the path to `r0vm`, use
///   `RISC0_SERVER_PATH`.
///
/// If `RISC0_EXECUTOR` is not specified, the following rules are used to select
/// an [Executor]:
/// * LocalProver if the `prove` feature flag is enabled.
/// * [ExternalProver] otherwise.
pub fn default_executor() -> Rc<dyn Executor> {
    let explicit = std::env::var("RISC0_EXECUTOR").unwrap_or_default();
    if !explicit.is_empty() {
        return match explicit.to_lowercase().as_str() {
            "ipc" => Rc::new(ExternalProver::new("ipc", get_r0vm_path())),
            #[cfg(feature = "prove")]
            "local" => Rc::new(self::local::LocalProver::new("local")),
            _ => unimplemented!("Unsupported executor: {explicit}"),
        };
    }

    if cfg!(feature = "prove") {
        #[cfg(feature = "prove")]
        return Rc::new(self::local::LocalProver::new("local"));
    }

    Rc::new(ExternalProver::new("ipc", get_r0vm_path()))
}

pub(crate) fn get_r0vm_path() -> PathBuf {
    std::env::var("RISC0_SERVER_PATH")
        .unwrap_or("r0vm".to_string())
        .into()
}
