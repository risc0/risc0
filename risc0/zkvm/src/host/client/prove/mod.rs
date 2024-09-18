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

use anyhow::{anyhow, Result};
use risc0_build::risc0_data;
use serde::{Deserialize, Serialize};

use risc0_circuit_recursion::control_id::ALLOWED_CONTROL_IDS;
use risc0_zkp::core::digest::Digest;

use self::{bonsai::BonsaiProver, external::ExternalProver};
use crate::{
    get_version, host::prove_info::ProveInfo, is_dev_mode, receipt::DEFAULT_MAX_PO2, ExecutorEnv,
    Receipt, SessionInfo, VerifierContext,
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
/// let env = ExecutorEnv::builder().write(&20u32).unwrap().build().unwrap();
/// let receipt = default_prover().prove(env, FIB_ELF).unwrap();
///
/// // Or you can specify a context and options
/// // Here we are using ProverOpts::succinct() to get a constant size proof through recursion.
/// let env = ExecutorEnv::builder().write(&20u32).unwrap().build().unwrap();
/// let opts = ProverOpts::succinct();
/// let receipt = default_prover().prove_with_opts(env, FIB_ELF, &opts).unwrap();
/// # }
/// ```
pub trait Prover {
    /// Return a name for this [Prover].
    fn get_name(&self) -> String;

    /// Prove zkVM execution of the specified ELF binary.
    ///
    /// Use this method unless you have need to configure the prover options or verifier context.
    /// Default [VerifierContext] and [ProverOpts] will be used.
    fn prove(&self, env: ExecutorEnv<'_>, elf: &[u8]) -> Result<ProveInfo> {
        self.prove_with_ctx(
            env,
            &VerifierContext::default(),
            elf,
            &ProverOpts::default(),
        )
    }

    /// Prove zkVM execution of the specified ELF binary and using the specified [ProverOpts].
    ///
    /// Use this method when you want to specify the receipt type you would like (e.g. groth16 or
    /// succinct), or if you need to tweak other parameter in [ProverOpts].
    ///
    /// Default [VerifierContext] will be used.
    fn prove_with_opts(
        &self,
        env: ExecutorEnv<'_>,
        elf: &[u8],
        opts: &ProverOpts,
    ) -> Result<ProveInfo> {
        self.prove_with_ctx(
            env,
            &VerifierContext::from_max_po2(opts.max_segment_po2),
            elf,
            opts,
        )
    }

    /// Prove zkVM execution of the specified ELF binary and using the specified [VerifierContext]
    /// and [ProverOpts].
    ///
    /// Use this method if you are using non-standard verification parameters. The
    /// [VerifierContext] specified here should match what you expect the verifier to use in your
    /// application.
    fn prove_with_ctx(
        &self,
        env: ExecutorEnv<'_>,
        ctx: &VerifierContext,
        elf: &[u8],
        opts: &ProverOpts,
    ) -> Result<ProveInfo>;

    /// Compress a [Receipt], proving the same computation using a smaller representation.
    ///
    /// Proving will, by default, produce a [CompositeReceipt](crate::CompositeReceipt), which
    /// may contain an arbitrary number of receipts assembled into segments and assumptions.
    /// Together, these receipts collectively prove a top-level
    /// [ReceiptClaim](crate::ReceiptClaim). This function can be used to compress all of the constituent
    /// receipts of a [CompositeReceipt](crate::CompositeReceipt) into a single
    /// [SuccinctReceipt](crate::SuccinctReceipt) or [Groth16Receipt](crate::Groth16Receipt) that proves the same top-level claim.
    ///
    /// Compression from [Groth16Receipt](crate::CompositeReceipt) to
    /// [SuccinctReceipt](crate::SuccinctReceipt) is accomplished by iterative application of the
    /// recursion programs including lift, join, and resolve.
    ///
    /// Compression from [SuccinctReceipt](crate::SuccinctReceipt) to
    /// [Groth16Receipt](crate::Groth16Receipt) is accomplished by running a Groth16 recursive
    /// verifier, referred to as the "STARK-to-SNARK" operation.
    ///
    /// NOTE: Compression to [Groth16Receipt](crate::Groth16Receipt) is currently only supported on
    /// x86 hosts, and requires Docker to be installed. See issue
    /// [#1749](https://github.com/risc0/risc0/issues/1749) for more information.
    ///
    /// If the receipt is already at least as compressed as the requested compression level (e.g.
    /// it is already succinct or Groth16 and a succinct receipt is required) this function is a
    /// no-op. As a result, it is idempotent.
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
#[non_exhaustive]
pub struct ProverOpts {
    /// Identifier of the hash function to use for the STARK proving protocol.
    pub hashfn: String,

    /// When false, only prove execution sessions that end in a successful
    /// [crate::ExitCode] (i.e. `Halted(0)` or `Paused(0)`).
    /// When set to true, any completed execution session will be proven, including indicated
    /// errors (e.g. `Halted(1)`) and sessions ending in `Fault`.
    pub prove_guest_errors: bool,

    /// Kind of receipt to be generated by the prover.
    pub receipt_kind: ReceiptKind,

    /// List of control IDs to enable for recursion proving.
    ///
    /// This list is used to construct the control root, which commits to the set of recursion
    /// programs that are allowed to run and is a key field in the
    /// [SuccinctReceiptVerifierParameters][crate::SuccinctReceiptVerifierParameters].
    pub control_ids: Vec<Digest>,

    /// Maximum cycle count, as a power of two (po2) that these prover options support.
    pub(crate) max_segment_po2: usize,
}

/// An enumeration of receipt kinds that can be requested to be generated.
#[derive(Clone, Copy, Serialize, Deserialize, PartialEq, Eq)]
#[non_exhaustive]
pub enum ReceiptKind {
    /// Request that a [CompositeReceipt][crate::CompositeReceipt] be generated.
    ///
    /// Composite receipts are made up of a receipt for every segment in a zkVM execution, and
    /// every assumption. They are linear in size with respect to the execution length.
    Composite,

    /// Request that a [SuccinctReceipt][crate::SuccinctReceipt] be generated.
    ///
    /// Succinct receipts are constant in size, with respect to the execution length.
    ///
    Succinct,

    /// Request that a [Groth16Receipt][crate::Groth16Receipt] be generated.
    ///
    /// Groth16 receipts are proven using Groth16, are constant in size, and are the smallest
    /// available receipt format. A Groth16 receipt can be serialized to a few hundred bytes.
    Groth16,
}

impl Default for ProverOpts {
    /// Return [ProverOpts] that are intended to work for most applications.
    ///
    /// Proof generated with these options may be linear in size with the execution length, but
    /// can be compressed using the [Prover::compress] methods.
    fn default() -> Self {
        Self {
            hashfn: "poseidon2".to_string(),
            prove_guest_errors: false,
            receipt_kind: ReceiptKind::Composite,
            control_ids: ALLOWED_CONTROL_IDS.to_vec(),
            max_segment_po2: DEFAULT_MAX_PO2,
        }
    }
}

impl ProverOpts {
    /// Construct a [ProverOpts] ready to prove segments with up to the given max cycle count as a
    /// power of two (po2). All fields are equal to the default expect where they need to be
    /// adjusted to support a larger po2.
    ///
    /// NOTE: If the po2 used to prove is greater than the targeted verifier supports,
    /// [DEFAULT_MAX_PO2] by default, receipts will be rejected by the verifier.
    #[stability::unstable]
    pub fn from_max_po2(po2_max: usize) -> Self {
        Self {
            hashfn: "poseidon2".to_string(),
            prove_guest_errors: false,
            receipt_kind: ReceiptKind::Composite,
            control_ids: crate::receipt::succinct::allowed_control_ids("poseidon2", po2_max)
                .unwrap()
                .collect(),
            max_segment_po2: po2_max,
        }
    }

    /// Construct a verifier context that will accept receipts with control any of the default
    /// control ID associated with cycle counts of all supported powers of two (po2).
    #[stability::unstable]
    pub fn all_po2s() -> Self {
        Self::from_max_po2(risc0_zkp::MAX_CYCLES_PO2)
    }

    /// Choose the fastest prover options. Receipt will be linear in length of the execution,
    /// and does not support compression via recursion.
    pub fn fast() -> Self {
        Self {
            hashfn: "sha-256".to_string(),
            prove_guest_errors: false,
            receipt_kind: ReceiptKind::Composite,
            control_ids: risc0_circuit_rv32im::control_ids("sha-256", DEFAULT_MAX_PO2).collect(),
            max_segment_po2: DEFAULT_MAX_PO2,
        }
    }

    /// Choose the prover that generates composite receipts, linear in the length of the execution,
    /// and supports compression via recursion.
    pub fn composite() -> Self {
        Self {
            hashfn: "poseidon2".to_string(),
            prove_guest_errors: false,
            receipt_kind: ReceiptKind::Composite,
            control_ids: ALLOWED_CONTROL_IDS.to_vec(),
            max_segment_po2: DEFAULT_MAX_PO2,
        }
    }

    /// Choose the prover that generates succinct receipts, which are constant size in the length
    /// of execution.
    pub fn succinct() -> Self {
        Self {
            hashfn: "poseidon2".to_string(),
            prove_guest_errors: false,
            receipt_kind: ReceiptKind::Succinct,
            control_ids: ALLOWED_CONTROL_IDS.to_vec(),
            max_segment_po2: DEFAULT_MAX_PO2,
        }
    }

    /// Choose the prover that generates Groth16 receipts which are constant size in the length of
    /// the execution and small enough to verify on blockchains, like Ethereum.
    ///
    /// Only supported for x86_64 Linux with Docker installed.
    pub fn groth16() -> Self {
        Self {
            hashfn: "poseidon2".to_string(),
            prove_guest_errors: false,
            receipt_kind: ReceiptKind::Groth16,
            control_ids: ALLOWED_CONTROL_IDS.to_vec(),
            max_segment_po2: DEFAULT_MAX_PO2,
        }
    }

    /// Return [ProverOpts] with the hashfn set to the given value.
    pub fn with_hashfn(self, hashfn: String) -> Self {
        Self {
            hashfn: hashfn.to_owned(),
            ..self
        }
    }

    /// Return [ProverOpts] with prove_guest_errors set to the given value.
    pub fn with_prove_guest_errors(self, prove_guest_errors: bool) -> Self {
        Self {
            prove_guest_errors,
            ..self
        }
    }

    /// Return [ProverOpts] with the receipt_kind set to the given value.
    pub fn with_receipt_kind(self, receipt_kind: ReceiptKind) -> Self {
        Self {
            receipt_kind,
            ..self
        }
    }

    /// Return [ProverOpts] with the control_ids set to the given value.
    pub fn with_control_ids(self, control_ids: Vec<Digest>) -> Self {
        Self {
            control_ids,
            ..self
        }
    }

    /// Return [ProverOpts] with the max_segment_po2 set to the given value.
    #[stability::unstable]
    pub fn with_segment_po2_max(self, max_segment_po2: usize) -> Self {
        Self {
            max_segment_po2,
            ..self
        }
    }

    #[cfg(feature = "prove")]
    pub(crate) fn hash_suite(
        &self,
    ) -> Result<risc0_zkp::core::hash::HashSuite<risc0_zkp::field::baby_bear::BabyBear>> {
        risc0_zkp::core::hash::hash_suite_from_name(&self.hashfn)
            .ok_or_else(|| anyhow::anyhow!("unsupported hash suite: {}", self.hashfn))
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
            "ipc" => Rc::new(ExternalProver::new("ipc", get_r0vm_path().unwrap())),
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

    Rc::new(ExternalProver::new("ipc", get_r0vm_path().unwrap()))
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
            "ipc" => Rc::new(ExternalProver::new("ipc", get_r0vm_path().unwrap())),
            #[cfg(feature = "prove")]
            "local" => Rc::new(self::local::LocalProver::new("local")),
            _ => unimplemented!("Unsupported executor: {explicit}"),
        };
    }

    if cfg!(feature = "prove") {
        #[cfg(feature = "prove")]
        return Rc::new(self::local::LocalProver::new("local"));
    }

    Rc::new(ExternalProver::new("ipc", get_r0vm_path().unwrap()))
}

fn try_r0vm_path(version: String) -> Option<PathBuf> {
    let path = risc0_data().ok()?.join("r0vm").join(version).join("r0vm");
    tracing::debug!("Checking for r0vm: {}", path.display());
    if let Ok(path) = path.canonicalize() {
        if path.is_file() {
            return Some(path);
        }
    }
    None
}

pub(crate) fn get_r0vm_path() -> Result<PathBuf> {
    if let Ok(path) = std::env::var("RISC0_SERVER_PATH") {
        let path = PathBuf::from(path);
        if path.is_file() {
            return Ok(path);
        }
    }

    let version = get_version().map_err(|err| anyhow!(err))?;
    tracing::debug!("version: {version}");

    if let Some(path) = try_r0vm_path(version.to_string()) {
        return Ok(path);
    }

    if version.pre.is_empty() {
        if let Some(path) = try_r0vm_path(format!("{}.{}", version.major, version.minor)) {
            return Ok(path);
        }
    }

    Ok("r0vm".into())
}
