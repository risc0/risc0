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

//! Run the zkVM guest and prove its results.

mod dev_mode;
mod prover_impl;
#[cfg(test)]
mod tests;

use std::rc::Rc;

use anyhow::{anyhow, bail, Result};
use cfg_if::cfg_if;
use risc0_core::field::baby_bear::{BabyBear, Elem, ExtElem};
use risc0_zkp::hal::{CircuitHal, Hal};

use self::{dev_mode::DevModeProver, prover_impl::ProverImpl};
use crate::{
    host::{
        prove_info::ProveInfo,
        receipt::{CompositeReceipt, InnerReceipt, SegmentReceipt, SuccinctReceipt},
    },
    is_dev_mode, ExecutorEnv, ExecutorImpl, ProverOpts, Segment, Session, VerifierContext,
};

/// A ProverServer can execute a given ELF binary and produce a [ProveInfo] which contains a [crate::Receipt]
/// that can be used to verify correct computation.
pub trait ProverServer {
    /// Prove the specified ELF binary.
    fn prove(&self, env: ExecutorEnv<'_>, elf: &[u8]) -> Result<ProveInfo> {
        self.prove_with_ctx(env, &VerifierContext::default(), elf)
    }

    /// Prove the specified ELF binary using the specified [VerifierContext].
    fn prove_with_ctx(
        &self,
        env: ExecutorEnv<'_>,
        ctx: &VerifierContext,
        elf: &[u8],
    ) -> Result<ProveInfo> {
        let mut exec = ExecutorImpl::from_elf(env, elf)?;
        let session = exec.run()?;
        self.prove_session(ctx, &session)
    }

    /// Prove the specified [Session].
    fn prove_session(&self, ctx: &VerifierContext, session: &Session) -> Result<ProveInfo>;

    /// Prove the specified [Segment].
    fn prove_segment(&self, ctx: &VerifierContext, segment: &Segment) -> Result<SegmentReceipt>;

    /// Return the peak memory usage that this [ProverServer] has experienced.
    fn get_peak_memory_usage(&self) -> usize;

    /// Lift a [SegmentReceipt] into a [SuccinctReceipt]
    fn lift(&self, receipt: &SegmentReceipt) -> Result<SuccinctReceipt>;

    /// Join two [SuccinctReceipt] into a [SuccinctReceipt]
    fn join(&self, a: &SuccinctReceipt, b: &SuccinctReceipt) -> Result<SuccinctReceipt>;

    /// Resolve an assumption from a conditional [SuccinctReceipt] by providing a [SuccinctReceipt]
    /// proving the validity of the assumption.
    fn resolve(
        &self,
        conditional: &SuccinctReceipt,
        assumption: &SuccinctReceipt,
    ) -> Result<SuccinctReceipt>;

    /// Convert a [SuccinctReceipt] with a Poseidon hash function that uses a 254-bit field
    fn identity_p254(&self, a: &SuccinctReceipt) -> Result<SuccinctReceipt>;

    /// Compress a [CompositeReceipt] into a single [SuccinctReceipt].
    ///
    /// A [CompositeReceipt] may contain an arbitrary number of receipts assembled into
    /// continuations and compositions. Together, these receipts collectively prove a top-level
    /// [ReceiptClaim](crate::ReceiptClaim). This function compresses all of the constituent receipts of a
    /// [CompositeReceipt] into a single [SuccinctReceipt] that proves the same top-level claim. It
    /// accomplishes this by iterative application of the recursion programs including lift, join,
    /// and resolve.
    fn compress(&self, receipt: &CompositeReceipt) -> Result<SuccinctReceipt> {
        // Compress all receipts in the top-level session into one succinct receipt for the session.
        let continuation_receipt = receipt
            .segments
            .iter()
            .try_fold(
                None,
                |left: Option<SuccinctReceipt>, right: &SegmentReceipt| -> Result<_> {
                    Ok(Some(match left {
                        Some(left) => self.join(&left, &self.lift(right)?)?,
                        None => self.lift(right)?,
                    }))
                },
            )?
            .ok_or(anyhow!(
                "malformed composite receipt has no continuation segment receipts"
            ))?;

        // Compress assumptions and resolve them to get the final succinct receipt.
        receipt.assumptions.iter().try_fold(
            continuation_receipt,
            |conditional: SuccinctReceipt, assumption: &InnerReceipt| match assumption {
                InnerReceipt::Succinct(assumption) => self.resolve(&conditional, assumption),
                InnerReceipt::Composite(assumption) => {
                    self.resolve(&conditional, &self.compress(assumption)?)
                }
                InnerReceipt::Fake { .. } => bail!(
                    "compressing composite receipts with fake receipt assumptions is not supported"
                ),
                InnerReceipt::Compact(_) => bail!(
                    "compressing composite receipts with Compact receipt assumptions is not supported"
                )
            },
        )
    }
}

/// A pair of [Hal] and [CircuitHal].
#[derive(Clone)]
pub struct HalPair<H, C>
where
    H: Hal<Field = BabyBear, Elem = Elem, ExtElem = ExtElem>,
    C: CircuitHal<H>,
{
    /// A [Hal] implementation.
    pub hal: Rc<H>,

    /// An [CircuitHal] implementation.
    pub circuit_hal: Rc<C>,
}

impl Session {
    /// For each segment, call [ProverServer::prove_session] and collect the
    /// receipts.
    pub fn prove(&self) -> Result<ProveInfo> {
        let prover = get_prover_server(&ProverOpts::default())?;
        prover.prove_session(&VerifierContext::default(), self)
    }
}

#[cfg(feature = "cuda")]
mod cuda {
    use std::rc::Rc;

    use anyhow::{bail, Result};
    use risc0_circuit_rv32im::prove::hal::cuda::{CudaCircuitHalPoseidon2, CudaCircuitHalSha256};
    use risc0_zkp::hal::cuda::{CudaHalPoseidon2, CudaHalSha256};

    use super::{HalPair, ProverImpl, ProverServer};
    use crate::ProverOpts;

    pub fn get_prover_server(opts: &ProverOpts) -> Result<Rc<dyn ProverServer>> {
        match opts.hashfn.as_str() {
            "sha-256" => {
                let hal = Rc::new(CudaHalSha256::new());
                let circuit_hal = Rc::new(CudaCircuitHalSha256::new(hal.clone()));
                Ok(Rc::new(ProverImpl::new(
                    "cuda",
                    HalPair { hal, circuit_hal },
                    opts.receipt_kind.clone(),
                )))
            }
            "poseidon2" => {
                let hal = Rc::new(CudaHalPoseidon2::new());
                let circuit_hal = Rc::new(CudaCircuitHalPoseidon2::new(hal.clone()));
                Ok(Rc::new(ProverImpl::new(
                    "cuda",
                    HalPair { hal, circuit_hal },
                    opts.receipt_kind.clone(),
                )))
            }
            _ => bail!("Unsupported hashfn: {}", opts.hashfn),
        }
    }
}

#[cfg(feature = "metal")]
mod metal {
    use std::rc::Rc;

    use anyhow::{bail, Result};
    use risc0_circuit_rv32im::prove::hal::metal::MetalCircuitHal;
    use risc0_zkp::hal::metal::{
        MetalHalPoseidon2, MetalHalSha256, MetalHashPoseidon2, MetalHashSha256,
    };

    use super::{HalPair, ProverImpl, ProverServer};
    use crate::ProverOpts;

    pub fn get_prover_server(opts: &ProverOpts) -> Result<Rc<dyn ProverServer>> {
        match opts.hashfn.as_str() {
            "sha-256" => {
                let hal = Rc::new(MetalHalSha256::new());
                let circuit_hal = Rc::new(MetalCircuitHal::<MetalHashSha256>::new(hal.clone()));
                Ok(Rc::new(ProverImpl::new(
                    "metal",
                    HalPair { hal, circuit_hal },
                    opts.receipt_kind.clone(),
                )))
            }
            "poseidon2" => {
                let hal = Rc::new(MetalHalPoseidon2::new());
                let circuit_hal = Rc::new(MetalCircuitHal::<MetalHashPoseidon2>::new(hal.clone()));
                Ok(Rc::new(ProverImpl::new(
                    "metal",
                    HalPair { hal, circuit_hal },
                    opts.receipt_kind.clone(),
                )))
            }
            _ => bail!("Unsupported hashfn: {}", opts.hashfn),
        }
    }
}

#[allow(dead_code)]
mod cpu {
    use std::rc::Rc;

    use anyhow::{bail, Result};
    use risc0_circuit_rv32im::prove::hal::cpu::CpuCircuitHal;
    use risc0_zkp::{
        core::hash::{poseidon2::Poseidon2HashSuite, sha::Sha256HashSuite},
        hal::cpu::CpuHal,
    };

    use super::{HalPair, ProverImpl, ProverServer};
    use crate::ProverOpts;

    pub fn get_prover_server(opts: &ProverOpts) -> Result<Rc<dyn ProverServer>> {
        let suite = match opts.hashfn.as_str() {
            "sha-256" => Sha256HashSuite::new_suite(),
            "poseidon2" => Poseidon2HashSuite::new_suite(),
            _ => bail!("Unsupported hashfn: {}", opts.hashfn),
        };
        let hal = Rc::new(CpuHal::new(suite));
        let circuit_hal = Rc::new(CpuCircuitHal::new());
        let hal_pair = HalPair { hal, circuit_hal };
        Ok(Rc::new(ProverImpl::new(
            "cpu",
            hal_pair,
            opts.receipt_kind.clone(),
        )))
    }
}

/// Select a [ProverServer] based on the specified [ProverOpts] and currently
/// compiled features.
pub fn get_prover_server(opts: &ProverOpts) -> Result<Rc<dyn ProverServer>> {
    if is_dev_mode() {
        eprintln!("WARNING: proving in dev mode. This will not generate valid, secure proofs.");
        return Ok(Rc::new(DevModeProver));
    }

    cfg_if! {
        if #[cfg(feature = "cuda")] {
            cuda::get_prover_server(opts)
        } else if #[cfg(feature = "metal")] {
            metal::get_prover_server(opts)
        } else {
            cpu::get_prover_server(opts)
        }
    }
}
