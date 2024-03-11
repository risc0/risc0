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

use anyhow::{bail, Result};
use risc0_binfmt::{ExitCode, SystemState};
use risc0_core::field::baby_bear::{BabyBear, Elem, ExtElem};
use risc0_zkp::{
    core::digest::Digest,
    hal::{CircuitHal, Hal},
};

use super::{HalPair, ProverServer};
use crate::{
    host::{
        receipt::{CompositeReceipt, InnerReceipt, SegmentReceipt, SuccinctReceipt},
        recursion::{identity_p254, join, lift, resolve},
    },
    sha::Digestible,
    Receipt, ReceiptClaim, Segment, Session, VerifierContext,
};

/// An implementation of a Prover that runs locally.
pub struct ProverImpl<H, C>
where
    H: Hal<Field = BabyBear, Elem = Elem, ExtElem = ExtElem>,
    C: CircuitHal<H>,
{
    name: String,
    hal_pair: HalPair<H, C>,
}

impl<H, C> ProverImpl<H, C>
where
    H: Hal<Field = BabyBear, Elem = Elem, ExtElem = ExtElem>,
    C: CircuitHal<H>,
{
    /// Construct a [ProverImpl] with the given name and [HalPair].
    pub fn new(name: &str, hal_pair: HalPair<H, C>) -> Self {
        Self {
            name: name.to_string(),
            hal_pair,
        }
    }

    /// Calculate for the [ReceiptClaim] associated with this [Segment]. The
    /// [ReceiptClaim] is the claim that will be proven if this [Segment]
    /// is passed to the [crate::Prover].
    fn get_segment_claim(&self, segment: &Segment) -> Result<ReceiptClaim> {
        // NOTE: When a segment ends in a Halted(_) state, it may not update the post state
        // digest. As a result, it will be the same as the pre_image. All other exit codes require
        // the post state digest to reflect the final memory state.
        // NOTE: The PC on the post state is stored "+ 4". See ReceiptClaim for more detail.
        let post_state = SystemState {
            pc: segment.post_state.pc,
            // .checked_add(WORD_SIZE as u32)
            // .context("invalid pc in segment post state")?,
            merkle_root: match segment.exit_code {
                ExitCode::Halted(_) => segment.pre_state.merkle_root.clone(),
                _ => segment.post_state.merkle_root.clone(),
            },
        };

        Ok(ReceiptClaim {
            pre: segment.pre_state.clone().into(),
            post: post_state.into(),
            exit_code: segment.exit_code,
            input: Digest::ZERO,
            output: None.into(), // segment.output.clone().into(), TODO
        })
    }
}

impl<H, C> ProverServer for ProverImpl<H, C>
where
    H: Hal<Field = BabyBear, Elem = Elem, ExtElem = ExtElem>,
    C: CircuitHal<H>,
{
    fn prove_session(&self, ctx: &VerifierContext, session: &Session) -> Result<Receipt> {
        tracing::info!(
            "prove_session: {}, exit_code = {:?}, journal = {:?}, segments: {}",
            self.name,
            session.exit_code,
            session.journal.as_ref().map(|x| hex::encode(x)),
            session.segments.len()
        );
        let mut segments = Vec::new();
        for segment_ref in session.segments.iter() {
            let segment = segment_ref.resolve()?;
            for hook in &session.hooks {
                hook.on_pre_prove_segment(&segment);
            }
            segments.push(self.prove_segment(ctx, &segment)?);
            for hook in &session.hooks {
                hook.on_post_prove_segment(&segment);
            }
        }
        // TODO(#982): Support unresolved assumptions here.
        let assumptions = session
            .assumptions
            .iter()
            .map(|x| Ok(x.as_receipt()?.inner.clone()))
            .collect::<Result<Vec<_>>>()?;
        let composite_receipt = CompositeReceipt {
            segments,
            assumptions,
            journal_digest: session.journal.as_ref().map(|journal| journal.digest()),
        };

        // Verify the receipt to catch if something is broken in the proving process.
        composite_receipt.verify_integrity_with_context(ctx)?;
        if composite_receipt.get_claim()?.digest() != session.get_claim()?.digest() {
            tracing::debug!("composite receipt and session claim do not match");
            tracing::debug!(
                "composite receipt claim: {:#?}",
                composite_receipt.get_claim()?
            );
            tracing::debug!("session claim: {:#?}", session.get_claim()?);
            bail!(
                "session and composite receipt claim do not match: session {}, receipt {}",
                hex::encode(&session.get_claim()?.digest()),
                hex::encode(&composite_receipt.get_claim()?.digest())
            );
        }

        let receipt = Receipt::new(
            InnerReceipt::Composite(composite_receipt),
            session.journal.clone().unwrap_or_default().bytes,
        );

        // Verify the receipt to catch if something is broken in the proving process.
        receipt.verify_integrity_with_context(ctx)?;
        if receipt.get_claim()?.digest() != session.get_claim()?.digest() {
            tracing::debug!("receipt and session claim do not match");
            tracing::debug!("receipt claim: {:#?}", receipt.get_claim()?);
            tracing::debug!("session claim: {:#?}", session.get_claim()?);
            bail!(
                "session and receipt claim do not match: session {}, receipt {}",
                hex::encode(&session.get_claim()?.digest()),
                hex::encode(&receipt.get_claim()?.digest())
            );
        }

        Ok(receipt)
    }

    #[cfg(not(feature = "parallel-witgen"))]
    fn prove_segment(&self, ctx: &VerifierContext, segment: &Segment) -> Result<SegmentReceipt> {
        use risc0_circuit_rv32im::{
            layout::{OutBuffer, LAYOUT},
            CIRCUIT, REGISTER_GROUP_ACCUM, REGISTER_GROUP_CODE, REGISTER_GROUP_DATA,
        };

        use risc0_zkp::{
            adapter::TapsProvider,
            layout::Buffer,
            prove::{adapter::ProveAdapter, executor::Executor, Prover},
        };

        use super::{loader::Loader, machine::MachineContext};

        tracing::debug!(
            "prove_segment[{}]: po2: {}, cycles: {}",
            segment.index,
            segment.po2,
            segment.cycles,
        );
        let (hal, circuit_hal) = (self.hal_pair.hal.as_ref(), &self.hal_pair.circuit_hal);
        let hashfn = &hal.get_hash_suite().name;

        let io = segment.prepare_globals();
        let machine = MachineContext::new(segment);
        let po2 = segment.po2 as usize;
        let mut executor = Executor::new(&CIRCUIT, machine, po2, po2, &io);

        tracing::info_span!("execute").in_scope(|| -> Result<()> {
            let loader = Loader::new();
            loader.load(|chunk, fini| executor.step(chunk, fini))?;
            executor.finalize();
            Ok(())
        })?;

        let seal = tracing::info_span!("prove").in_scope(|| {
            let mut adapter = ProveAdapter::new(&mut executor);
            let mut prover = Prover::new(hal, CIRCUIT.get_taps());

            adapter.execute(prover.iop());

            prover.set_po2(adapter.po2() as usize);

            prover.commit_group(
                REGISTER_GROUP_CODE,
                hal.copy_from_elem("code", &adapter.get_code().as_slice()),
            );
            prover.commit_group(
                REGISTER_GROUP_DATA,
                hal.copy_from_elem("data", &adapter.get_data().as_slice()),
            );
            adapter.accumulate(prover.iop());
            prover.commit_group(
                REGISTER_GROUP_ACCUM,
                hal.copy_from_elem("accum", &adapter.get_accum().as_slice()),
            );

            let mix = hal.copy_from_elem("mix", &adapter.get_mix().as_slice());
            let out_slice = &adapter.get_io().as_slice();

            tracing::debug!("Globals: {:?}", OutBuffer(out_slice).tree(LAYOUT));
            let out = hal.copy_from_elem("out", &adapter.get_io().as_slice());

            prover.finalize(&[&mix, &out], circuit_hal.as_ref())
        });

        let receipt = SegmentReceipt {
            seal,
            index: segment.index,
            hashfn: hashfn.clone(),
            claim: segment.get_claim()?,
        };
        receipt.verify_integrity_with_context(ctx)?;

        Ok(receipt)
    }

    #[cfg(feature = "parallel-witgen")]
    fn prove_segment(&self, ctx: &VerifierContext, segment: &Segment) -> Result<SegmentReceipt> {
        use risc0_circuit_rv32im::prove::{engine::SegmentProverImpl, SegmentProver as _};

        let hashfn = self.hal_pair.hal.get_hash_suite().name.clone();

        let prover =
            SegmentProverImpl::new(self.hal_pair.hal.clone(), self.hal_pair.circuit_hal.clone());
        let seal = prover.prove_segment(segment)?;

        let receipt = SegmentReceipt {
            seal,
            index: segment.index as u32,
            hashfn,
            claim: self.get_segment_claim(segment)?,
        };
        receipt.verify_integrity_with_context(ctx)?;

        Ok(receipt)
    }

    fn get_peak_memory_usage(&self) -> usize {
        self.hal_pair.hal.get_memory_usage()
    }

    fn lift(&self, receipt: &SegmentReceipt) -> Result<SuccinctReceipt> {
        lift(receipt)
    }

    fn join(&self, a: &SuccinctReceipt, b: &SuccinctReceipt) -> Result<SuccinctReceipt> {
        join(a, b)
    }

    fn resolve(
        &self,
        conditional: &SuccinctReceipt,
        assumption: &SuccinctReceipt,
    ) -> Result<SuccinctReceipt> {
        resolve(conditional, assumption)
    }

    fn identity_p254(&self, a: &SuccinctReceipt) -> Result<SuccinctReceipt> {
        identity_p254(a)
    }
}
