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

#[cfg(feature = "bonsai")]
pub(crate) mod bonsai;
pub(crate) mod default;
pub(crate) mod external;
#[cfg(feature = "prove")]
pub(crate) mod local;
pub(crate) mod opts;

use core::ops::Deref;
use std::{path::PathBuf, rc::Rc};

use anyhow::{Result, anyhow};

#[cfg(feature = "bonsai")]
use self::bonsai::BonsaiProver;

use self::{default::DefaultProver, external::ExternalProver, opts::ProverOpts};

use crate::{
    ExecutorEnv, Receipt, SessionInfo, VerifierContext, get_version, host::prove_info::ProveInfo,
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
        let opts = ProverOpts::default();
        let ctx = VerifierContext::default();
        self.prove_with_ctx(env, &ctx, elf, &opts)
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
        let ctx = VerifierContext::default().with_dev_mode(opts.dev_mode());
        self.prove_with_ctx(env, &ctx, elf, opts)
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
    /// NOTE: Compression to [Groth16Receipt](crate::Groth16Receipt) requires
    /// Docker to be installed. See issue
    /// [#1749](https://github.com/risc0/risc0/issues/1749) for more information.
    ///
    /// If the receipt is already at least as compressed as the requested compression level (e.g.
    /// it is already succinct or Groth16 and a succinct receipt is required) this function is a
    /// no-op. As a result, it is idempotent.
    fn compress(&self, opts: &ProverOpts, receipt: &Receipt) -> Result<Receipt>;
}

// Implementation of Prover for `Rc<Prover>` which allows it to satisfy trait bounds for Prover.
impl<P: Prover + ?Sized> Prover for Rc<P> {
    fn get_name(&self) -> String {
        self.deref().get_name()
    }

    fn prove_with_ctx(
        &self,
        env: ExecutorEnv<'_>,
        ctx: &VerifierContext,
        elf: &[u8],
        opts: &ProverOpts,
    ) -> Result<ProveInfo> {
        self.deref().prove_with_ctx(env, ctx, elf, opts)
    }

    fn compress(&self, opts: &ProverOpts, receipt: &Receipt) -> Result<Receipt> {
        self.deref().compress(opts, receipt)
    }
}

/// An Executor can execute a given ELF binary.
pub trait Executor {
    /// Execute the specified ELF binary.
    ///
    /// This only executes the program and does not generate a receipt.
    fn execute(&self, env: ExecutorEnv<'_>, elf: &[u8]) -> Result<SessionInfo>;
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
            "actor" => Rc::new(DefaultProver::new(get_r0vm_path().unwrap()).unwrap()),
            #[cfg(feature = "bonsai")]
            "bonsai" => Rc::new(BonsaiProver::new("bonsai")),
            "ipc" => Rc::new(ExternalProver::new("ipc", get_r0vm_path().unwrap())),
            #[cfg(feature = "prove")]
            "local" => Rc::new(self::local::LocalProver::new("local")),
            _ => unimplemented!("Unsupported prover: {explicit}"),
        };
    }

    #[cfg(feature = "bonsai")]
    {
        if !crate::is_dev_mode_enabled_via_environment()
            && std::env::var("BONSAI_API_URL").is_ok()
            && std::env::var("BONSAI_API_KEY").is_ok()
        {
            return Rc::new(BonsaiProver::new("bonsai"));
        }
    }

    if cfg!(feature = "prove") {
        #[cfg(feature = "prove")]
        return Rc::new(self::local::LocalProver::new("local"));
    }

    Rc::new(DefaultProver::new(get_r0vm_path().unwrap()).unwrap())
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

/// Return a local [Executor].
#[cfg(feature = "prove")]
pub fn local_executor() -> Rc<dyn Executor> {
    Rc::new(self::local::LocalProver::new("local"))
}

pub(crate) fn get_r0vm_path() -> Result<PathBuf> {
    if let Ok(path) = std::env::var("RISC0_SERVER_PATH") {
        let path = PathBuf::from(path);
        if path.is_file() {
            return Ok(path);
        }
    }

    let mut version = get_version().map_err(|err| anyhow!(err))?;
    tracing::debug!("version: {version}");

    if let Ok(rzup) = rzup::Rzup::new() {
        if let Ok(dir) = rzup.get_version_dir(&rzup::Component::R0Vm, &version) {
            return Ok(dir.join("r0vm"));
        }

        // Try again, but with these fields stripped
        version.patch = 0;
        version.build = Default::default();

        if let Ok(dir) = rzup.get_version_dir(&rzup::Component::R0Vm, &version) {
            return Ok(dir.join("r0vm"));
        }
    }

    Ok("r0vm".into())
}
