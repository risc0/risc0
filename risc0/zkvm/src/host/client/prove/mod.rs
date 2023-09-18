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
use risc0_zkvm_platform::{memory::MEM_SIZE, PAGE_SIZE};
use serde::{Deserialize, Serialize};

use self::{bonsai::BonsaiProver, external::ExternalProver};
use crate::{is_dev_mode, ExecutorEnv, Receipt, VerifierContext};

/// A Prover can execute a given [MemoryImage] or ELF file and produce a
/// [Receipt] that can be used to verify correct computation.
///
/// # Usage
/// To produce a proof, you must minimally provide an [ExecutorEnv] and either
/// an ELF file or a [MemoryImage]. See the
/// [risc0_build](https://docs.rs/risc0-build/latest/risc0_build/) crate for
/// more information on producing ELF files from Rust source code.
///
/// ```rust
/// use risc0_zkvm::{
///     default_prover,
///     ExecutorEnv,
///     MEM_SIZE,
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
/// // A straightforward case with an ELF file
/// let env = ExecutorEnv::builder().add_input(&[20]).build().unwrap();
/// let receipt = default_prover().prove_elf(env, FIB_ELF).unwrap();
///
/// // Or you can specify a context and options
/// // (Using the defaults as we do here is equivalent to the above code.)
/// let env = ExecutorEnv::builder().add_input(&[20]).build().unwrap();
/// let ctx = VerifierContext::default();
/// let opts = ProverOpts::default();
/// let receipt = default_prover().prove_elf_with_ctx(env, &ctx, FIB_ELF, &opts).unwrap();
///
/// // Or you can prove from a `MemoryImage`
/// // (generating a `MemoryImage` from an ELF file in this way is equivalent
/// // to the above code.)
/// let program = Program::load_elf(FIB_ELF, MEM_SIZE as u32).unwrap();
/// let image = MemoryImage::new(&program, PAGE_SIZE as u32).unwrap();
/// let env = ExecutorEnv::builder().add_input(&[20]).build().unwrap();
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
        let program = Program::load_elf(elf, MEM_SIZE as u32)?;
        let image = MemoryImage::new(&program, PAGE_SIZE as u32)?;
        self.prove(env, ctx, opts, image)
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
            hashfn: "sha-256".to_string(),
        }
    }
}

/// Return a default [Prover] based on environment variables, falling back to a
/// default CPU-based prover.
pub fn default_prover() -> Rc<dyn Prover> {
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

fn get_r0vm_path() -> PathBuf {
    todo!()
}
