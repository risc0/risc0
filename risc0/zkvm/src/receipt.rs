// Copyright 2022 RISC Zero, Inc.
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

use alloc::vec::Vec;

use anyhow::{anyhow, Result};
use risc0_zeroio::{Deserialize as ZeroioDeserialize, Serialize as ZeroioSerialize};
use risc0_zkp::{core::sha::Digest, MIN_CYCLES_PO2};
use serde::{Deserialize, Serialize};

use crate::{method_id::MethodId, CIRCUIT};

#[cfg(all(feature = "std", not(target_os = "zkvm")))]
pub fn insecure_skip_seal() -> bool {
    cfg!(feature = "insecure_skip_seal")
        && std::env::var("RISC0_INSECURE_SKIP_SEAL").unwrap_or_default() == "1"
}

#[cfg(target_os = "zkvm")]
pub fn insecure_skip_seal() -> bool {
    cfg!(feature = "insecure_skip_seal")
}

#[derive(Deserialize, Serialize, ZeroioSerialize, ZeroioDeserialize, Clone, Debug)]
/// The receipt serves as a zero-knowledge proof of computation.
pub struct Receipt {
    /// The journal contains the public outputs of the computation.
    pub journal: Vec<u32>,
    /// The seal is an opaque cryptographic blob that attests to the integrity
    /// of the computation. It consists of merkle commitments and query data for
    /// an AIR-FRI STARK that includes a PLONK-based permutation argument.
    pub seal: Vec<u32>,
}

pub fn verify_with_hal<H, M>(hal: &H, method_id: M, seal: &[u32], journal: &[u32]) -> Result<()>
where
    H: risc0_zkp::verify::VerifyHal,
    MethodId: From<M>,
{
    use risc0_zkp::verify::VerificationError;

    let method_id: MethodId = method_id.into();
    let check_code = |po2: u32, merkle_root: &Digest| -> Result<(), VerificationError> {
        let po2 = po2 as usize;
        let which = po2 - MIN_CYCLES_PO2;
        #[cfg(not(target_os = "zkvm"))]
        if log::log_enabled!(log::Level::Debug) {
            log::debug!("merkle_root: {merkle_root}");
            log::debug!("MethodId");
            for (i, entry) in method_id.table.iter().enumerate() {
                let marker = if i == which { "*" } else { "" };
                log::debug!("  {i}: {entry}{marker}");
            }
        }
        if which >= method_id.table.len() {
            return Err(VerificationError::MethodCycleError { required: po2 });
        }
        if method_id.table[which] != *merkle_root {
            Err(VerificationError::MethodVerificationError)
        } else {
            Ok(())
        }
    };

    #[cfg(any(feature = "std", target_os = "zkvm"))]
    if insecure_skip_seal() {
        return Ok(());
    }

    risc0_zkp::verify::verify(hal, &CIRCUIT, seal, journal, check_code)
        .map_err(|err| anyhow!("Verification failed: {}", err))
}

impl Receipt {
    pub fn new(journal: &[u32], seal: &[u32]) -> Self {
        Self {
            journal: Vec::from(journal),
            seal: Vec::from(seal),
        }
    }

    #[cfg(not(target_os = "zkvm"))]
    /// Verifies a receipt using CPU.
    pub fn verify<M>(&self, method_id: M) -> Result<()>
    where
        MethodId: From<M>,
    {
        let sha = crate::sha::sha();
        let hal = risc0_zkp::verify::CpuVerifyHal::new(sha, &crate::CIRCUIT);

        verify_with_hal(&hal, method_id, &self.seal, &self.journal)
    }

    /// Verifies a receipt using the hardware acceleration layer.
    pub fn verify_with_hal<H, M>(&self, hal: &H, method_id: M) -> Result<()>
    where
        H: risc0_zkp::verify::VerifyHal,
        MethodId: From<M>,
    {
        verify_with_hal(hal, method_id, &self.seal, &self.journal)
    }

    /// Extracts the journal from the receipt, as a series of bytes.
    pub fn get_journal_bytes(&self) -> &[u8] {
        bytemuck::cast_slice(self.journal.as_slice())
    }

    /// Extracts the seal from the receipt, as a series of bytes.
    pub fn get_seal_bytes(&self) -> &[u8] {
        bytemuck::cast_slice(self.seal.as_slice())
    }
}
