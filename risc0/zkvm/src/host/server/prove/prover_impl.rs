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

use anyhow::{bail, Result};
use risc0_binfmt::SegmentRecord;
use risc0_circuit_rv32im::prove::vm::prove_segment;
use risc0_core::field::baby_bear::{BabyBear, Elem, ExtElem};
use risc0_zkp::hal::{CircuitHal, Hal};

use super::{HalPair, ProverServer};
use crate::{
    host::{
        receipt::{CompositeReceipt, InnerReceipt, SegmentReceipt, SuccinctReceipt},
        recursion::{identity_p254, join, lift},
    },
    sha::Digestible,
    Receipt, Segment, Session, VerifierContext,
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
}

impl<H, C> ProverServer for ProverImpl<H, C>
where
    H: Hal<Field = BabyBear, Elem = Elem, ExtElem = ExtElem>,
    C: CircuitHal<H>,
{
    fn prove_session(&self, ctx: &VerifierContext, session: &Session) -> Result<Receipt> {
        tracing::info!(
            "prove_session: {}, exit_code = {:?}, journal = {:?}",
            self.name,
            session.exit_code,
            session.journal.as_ref().map(|x| hex::encode(x))
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
        let inner = InnerReceipt::Composite(CompositeReceipt {
            segments,
            assumptions: session
                .assumptions
                .iter()
                .map(|a| Ok(a.as_receipt()?.inner.clone()))
                .collect::<Result<Vec<_>>>()?,
            journal_digest: session.journal.as_ref().map(|journal| journal.digest()),
        });
        let receipt = Receipt::new(inner, session.journal.clone().unwrap_or_default().bytes);

        receipt.verify_integrity_with_context(ctx)?;
        let receipt_claim = receipt.get_claim()?;
        let session_claim = session.get_claim()?;
        if receipt_claim.digest() != session_claim.digest() {
            tracing::debug!("receipt and session claim do not match");
            tracing::debug!("receipt claim: {receipt_claim:#?}");
            tracing::debug!("session claim: {session_claim:#?}");
            bail!(
                "session and receipt claim do not match: session {}, receipt {}",
                hex::encode(&session_claim.digest()),
                hex::encode(&receipt_claim.digest())
            );
        }
        Ok(receipt)
    }

    fn prove_segment(&self, ctx: &VerifierContext, segment: &Segment) -> Result<SegmentReceipt> {
        tracing::debug!(
            "prove_segment[{}]: po2: {}, cycles: {}",
            segment.index,
            segment.po2,
            segment.cycles,
        );
        let (hal, circuit_hal) = (self.hal_pair.hal.as_ref(), &self.hal_pair.circuit_hal);
        let hashfn = &hal.get_hash_suite().name;

        let io = segment.prepare_globals()?;
        let segment_record = SegmentRecord {
            pre_image: *(segment.pre_image).clone(),
            faults: segment.faults.clone(),
            syscalls: segment.syscalls.clone(),
            split_insn: segment.split_insn,
        };

        let seal = prove_segment(
            hal,
            circuit_hal.as_ref(),
            segment_record,
            segment.po2 as usize,
            &io,
        )?;

        let receipt = SegmentReceipt {
            seal,
            index: segment.index,
            hashfn: hashfn.clone(),
            claim: segment.get_claim()?,
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

    fn identity_p254(&self, a: &SuccinctReceipt) -> Result<SuccinctReceipt> {
        identity_p254(a)
    }
}
