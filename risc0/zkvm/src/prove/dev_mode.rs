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
use risc0_binfmt::MemoryImage;

use crate::{
    prove::Prover,
    receipt::{InnerReceipt, Receipt, VerifierContext},
    Executor, ExecutorEnv, Segment, SegmentReceipt, Session,
};

/// An implementation of a [Prover] for development and testing purposes.
///
/// This DevModeProver does not produce an actual proof.
/// Instead, the guest code is executed and a fake receipt is returned with
/// accurate journal contents but no cryptographic information.
/// Because the receipt is fake, a verifier can only "verify" this receipt
/// if dev mode is turned on; verification will otherwise fail.
///
/// CONVENIENT, BUT NOT MEANT FOR PRODUCTION
/// Dev mode supports rapid development by allowing the developer to quickly
/// iterate on code without being forced to wait for proving to complete.
/// However, it must not be used in production as it provides no security
/// whatsoever.
///
/// How to enable and disable dev mode:
/// Dev mode is only used when the environment variable `RISC0_DEV_MODE` is set.
/// It can be fully disabled at compile time, regardless of environment
/// variables, by setting the feature flag `disable-dev-mode` on the
/// `risc0_zkvm` crate.
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
        // we don't actually run the prover in dev mode.
        0
    }

    fn prove_session(&self, _ctx: &VerifierContext, session: &Session) -> Result<Receipt> {
        log::info!("prove_session: {}", self.name);
        eprintln!(
            "WARNING: Proving in dev mode does not generate a valid receipt. \
            Receipts generated from this process are invalid and should never be used in production."
        );

        if cfg!(feature = "disable-dev-mode") && std::env::var("RISC0_DEV_MODE").is_ok() {
            panic!("zkVM: dev mode is disabled. Unset RISC0_DEV_MODE environment variable to produce valid proofs")
        }

        Ok(Receipt::new(InnerReceipt::Fake, session.journal.clone()))
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
