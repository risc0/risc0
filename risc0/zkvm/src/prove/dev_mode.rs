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

use alloc::collections::BTreeMap;

use anyhow::Result;
use risc0_binfmt::MemoryImage;

use crate::{
    prove::Prover,
    receipt::{InnerReceipt, Receipt, VerifierContext},
    Executor, ExecutorEnv, Segment, SegmentReceipt, Session,
};

/// An implementation of a [Prover] for development and testing purposes.
pub struct DevModeProver {
    name: String,
}

impl DevModeProver {
    /// Construct a [DevModeProver] with the given name
    pub fn new(name: &str) -> Self {
        Self {
            name: name.to_string(),
        }
    }
}

impl Prover for DevModeProver {
    fn get_name(&self) -> String {
        self.name.clone()
    }

    fn get_peak_memory_usage(&self) -> usize {
        // note, we don't actually run the prover, so very little memory is consumed
        // while generating the receipt
        0
    }

    fn prove_session(&self, _ctx: &VerifierContext, session: &Session) -> Result<Receipt> {
        log::info!("prove_session: {}", self.name);
        eprintln!(
            "WARNING: Proving in DevMode does not generate a valid receipt. \
            Receipts generated from this process are invalid and should never be used in production."
        );

        if cfg!(feature = "disable-dev-mode") && std::env::var("DEV_MODE").is_ok() {
            panic!("zkVM: dev mode is disabled. unset DEV_MODE environment variable to produce valid proofs")
        }

        let receipt = Receipt::new(InnerReceipt::Fake, session.journal.clone());
        let image_id = session.segments[0].resolve()?.pre_image.compute_id();
        receipt.verify_with_context(
            &VerifierContext {
                suites: BTreeMap::new(),
                #[cfg(not(feature = "disable-dev-mode"))]
                dev_mode: true,
            },
            image_id,
        )?;
        Ok(receipt)
    }

    fn prove_segment(&self, _ctx: &VerifierContext, _segment: &Segment) -> Result<SegmentReceipt> {
        unimplemented!("this is unimplemented for prover [{}]", self.get_name())
    }

    fn prove(
        &self,
        env: ExecutorEnv<'_>,
        ctx: &VerifierContext,
        image: MemoryImage,
    ) -> Result<Receipt> {
        let mut exec = Executor::new(env, image);
        let session = exec.run()?;
        self.prove_session(ctx, &session)
    }
}
