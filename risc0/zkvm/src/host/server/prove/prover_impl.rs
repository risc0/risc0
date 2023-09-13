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

use anyhow::Result;
use risc0_circuit_rv32im::{
    layout::{OutBuffer, LAYOUT},
    REGISTER_GROUP_ACCUM, REGISTER_GROUP_CODE, REGISTER_GROUP_DATA,
};
use risc0_core::field::baby_bear::{BabyBear, Elem, ExtElem};
use risc0_zkp::{
    adapter::TapsProvider,
    hal::{CircuitHal, Hal},
    layout::Buffer,
    prove::adapter::ProveAdapter,
};

use super::{exec::MachineContext, HalPair, ProverServer};
use crate::{
    host::{receipt::SegmentReceipts, CIRCUIT},
    InnerReceipt, Loader, Receipt, Segment, SegmentReceipt, Session, VerifierContext,
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
        log::info!("prove_session: {}", self.name);
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
        let inner = InnerReceipt::Flat(SegmentReceipts(segments));
        let receipt = Receipt::new(inner, session.journal.clone());
        let image_id = session.segments[0].resolve()?.pre_image.compute_id();
        receipt.verify_with_context(ctx, image_id)?;
        Ok(receipt)
    }

    fn prove_segment(&self, ctx: &VerifierContext, segment: &Segment) -> Result<SegmentReceipt> {
        use risc0_zkp::prove::executor::Executor;

        log::info!(
            "prove_segment[{}]: po2: {}, insn_cycles: {}",
            segment.index,
            segment.po2,
            segment.insn_cycles,
        );
        let (hal, circuit_hal) = (self.hal_pair.hal.as_ref(), &self.hal_pair.circuit_hal);
        let hashfn = &hal.get_hash_suite().name;

        let io = segment.prepare_globals();
        let machine = MachineContext::new(segment);
        let mut executor = Executor::new(&CIRCUIT, machine, segment.po2, segment.po2, &io);

        let loader = Loader::new();
        loader.load(|chunk, fini| executor.step(chunk, fini))?;
        executor.finalize();

        let mut adapter = ProveAdapter::new(&mut executor);
        let mut prover = risc0_zkp::prove::Prover::new(hal, CIRCUIT.get_taps());

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

        log::debug!("Globals: {:?}", OutBuffer(out_slice).tree(&LAYOUT));
        let out = hal.copy_from_elem("out", &adapter.get_io().as_slice());

        let seal = prover.finalize(&[&mix, &out], circuit_hal.as_ref());

        let receipt = SegmentReceipt {
            seal,
            index: segment.index,
            hashfn: hashfn.clone(),
        };
        receipt.verify_with_context(ctx)?;

        Ok(receipt)
    }

    fn get_peak_memory_usage(&self) -> usize {
        self.hal_pair.hal.get_memory_usage()
    }
}
