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

pub(crate) mod bonsai;
pub(crate) mod external;
#[cfg(feature = "prove")]
pub(crate) mod local;

use std::{path::PathBuf, rc::Rc};

use anyhow::Result;
use risc0_binfmt::{MemoryImage, Program};
use risc0_zkvm_platform::{memory::GUEST_MAX_MEM, PAGE_SIZE};
use serde::{Deserialize, Serialize};

use self::{bonsai::BonsaiProver, external::ExternalProver};
use crate::{is_dev_mode, ExecutorEnv, Receipt, SessionInfo, VerifierContext};

/// A Prover can execute a given [MemoryImage] or ELF binary and produce a
/// [Receipt] that can be used to verify correct computation.
///
/// # Usage
/// To produce a proof, you must minimally provide an [ExecutorEnv] and either
/// an ELF binary or a [MemoryImage]. See the
/// [risc0_build](https://docs.rs/risc0-build/latest/risc0_build/) crate for
/// more information on producing ELF binaries from Rust source code.
///
/// ```rust
/// use risc0_zkvm::{
///     default_prover,
///     ExecutorEnv,
///     GUEST_MAX_MEM,
///     MemoryImage,
///     PAGE_SIZE,
///     Program,
///     ProverOpts,
///     VerifierContext,
/// };
/// use risc0_zkvm_methods::FIB_ELF;
///
/// # #[cfg(not(feature = "cuda"))]
/// # {
/// // A straightforward case with an ELF binary
/// let env = ExecutorEnv::builder().write_slice(&[20]).build().unwrap();
/// let receipt = default_prover().prove_elf(env, FIB_ELF).unwrap();
///
/// // Or you can specify a context and options
/// // (Using the defaults as we do here is equivalent to the above code.)
/// let env = ExecutorEnv::builder().write_slice(&[20]).build().unwrap();
/// let ctx = VerifierContext::default();
/// let opts = ProverOpts::default();
/// let receipt = default_prover().prove_elf_with_ctx(env, &ctx, FIB_ELF, &opts).unwrap();
///
/// // Or you can prove from a `MemoryImage`
/// // (generating a `MemoryImage` from an ELF binary in this way is equivalent
/// // to the above code.)
/// let program = Program::load_elf(FIB_ELF, GUEST_MAX_MEM as u32).unwrap();
/// let image = MemoryImage::new(&program, PAGE_SIZE as u32).unwrap();
/// let env = ExecutorEnv::builder().write_slice(&[20]).build().unwrap();
/// let ctx = VerifierContext::default();
/// let opts = ProverOpts::default();
/// let receipt = default_prover().prove(env, &ctx, &opts, image).unwrap();
/// # }
/// ```
pub trait Prover {
    /// Return a name for this [Prover].
    fn get_name(&self) -> String;

    /// Prove the specified [MemoryImage].
    fn prove(
        &self,
        env: ExecutorEnv<'_>,
        ctx: &VerifierContext,
        opts: &ProverOpts,
        image: MemoryImage,
    ) -> Result<Receipt>;

    /// Prove the specified ELF binary.
    fn prove_elf(&self, env: ExecutorEnv<'_>, elf: &[u8]) -> Result<Receipt> {
        self.prove_elf_with_ctx(
            env,
            &VerifierContext::default(),
            elf,
            &ProverOpts::default(),
        )
    }

    /// Prove the specified [MemoryImage] with the specified [VerifierContext].
    fn prove_elf_with_ctx(
        &self,
        env: ExecutorEnv<'_>,
        ctx: &VerifierContext,
        elf: &[u8],
        opts: &ProverOpts,
    ) -> Result<Receipt> {
        let program = Program::load_elf(elf, GUEST_MAX_MEM as u32)?;
        let image = MemoryImage::new(&program, PAGE_SIZE as u32)?;
        self.prove(env, ctx, opts, image)
    }
}

/// An Executor can execute a given [MemoryImage] or ELF binary.
pub trait Executor {
    /// Execute the specified [MemoryImage].
    ///
    /// This only executes the program and does not generate a receipt.
    fn execute(&self, env: ExecutorEnv<'_>, image: MemoryImage) -> Result<SessionInfo>;

    /// Execute the specified ELF binary.
    ///
    /// This only executes the program and does not generate a receipt.
    fn execute_elf(&self, env: ExecutorEnv<'_>, elf: &[u8]) -> Result<SessionInfo> {
        let program = Program::load_elf(elf, GUEST_MAX_MEM as u32)?;
        let image = MemoryImage::new(&program, PAGE_SIZE as u32)?;
        self.execute(env, image)
    }
}

/// Options to configure a [Prover].
#[derive(Clone, Serialize, Deserialize)]
pub struct ProverOpts {
    /// The hash function to use.
    pub hashfn: String,
}

impl Default for ProverOpts {
    fn default() -> Self {
        Self {
            hashfn: "poseidon".to_string(),
        }
    }
}

/// Return a default [Prover] based on environment variables and feature flags.
///
/// The `RISC0_PROVER` environment variable, if specified, will select the
/// following [Prover] implementation:
/// * `bonsai`: [BonsaiProver] to prove on Bonsai.
/// * `local`: [local::LocalProver] to prove locally in-process. Note: this
///   requires the `prove` feature flag.
/// * `ipc`: [ExternalProver] to prove using an `r0vm` sub-process. Note: `r0vm`
///   must be installed. To specify the path to `r0vm`, use `RISC0_SERVER_PATH`.
///
/// If `RISC0_PROVER` is not specified, the following rules are used to select a
/// [Prover]:
/// * [BonsaiProver] if the `BONSAI_API_URL` and `BONSAI_API_KEY` environment
///   variables are set unless `RISC0_DEV_MODE` is enabled.
/// * [local::LocalProver] if the `prove` feature flag is enabled.
/// * [ExternalProver] otherwise.
pub fn default_prover() -> Rc<dyn Prover> {
    let explicit = std::env::var("RISC0_PROVER").unwrap_or(String::new());
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
/// * `local`: [local::LocalProver] to execute locally in-process. Note: this is
///   only available when the `prove` feature is enabled.
/// * `ipc`: [ExternalProver] to execute using an `r0vm` sub-process. Note:
///   `r0vm` must be installed. To specify the path to `r0vm`, use
///   `RISC0_SERVER_PATH`.
///
/// If `RISC0_EXECUTOR` is not specified, the following rules are used to select
/// an [Executor]:
/// * [local::LocalProver] if the `prove` feature flag is enabled.
/// * [ExternalProver] otherwise.
pub fn default_executor() -> Rc<dyn Executor> {
    let explicit = std::env::var("RISC0_EXECUTOR").unwrap_or(String::new());
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
