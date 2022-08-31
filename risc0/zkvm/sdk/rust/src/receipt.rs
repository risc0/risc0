// Copyright 2022 Risc0, Inc.
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

use anyhow::Result;
use serde::{Deserialize, Serialize};

use crate::method_id::MethodId;

#[derive(Deserialize, Serialize, Clone)]
pub struct Receipt {
    pub journal: Vec<u32>,
    pub seal: Vec<u32>,
}

// FIXME: Remove this temporary conversion once our API is the same between
// FFI and rust-based provers.
impl From<&MethodId> for MethodId {
    fn from(method_id: &MethodId) -> Self {
        method_id.clone()
    }
}

#[cfg(feature = "verify")]
pub fn verify_with_hal<'a, M, H>(hal: &H, method_id: &'a M, seal: &[u32]) -> Result<()>
where
    H: risc0_zkp::verify::VerifyHal,
    M: ?Sized,
    MethodId: From<&'a M>,
{
    use crate::CIRCUIT;
    use anyhow::anyhow;
    use risc0_zkp::{
        core::{log2_ceil, sha::Digest},
        verify::verify,
        MIN_CYCLES,
    };

    let method_id: MethodId = method_id.into();
    let check_code = |po2, merkle_root: &Digest| {
        let which = po2 as usize - log2_ceil(MIN_CYCLES);
        #[cfg(not(target_arch = "riscv32"))]
        if log::log_enabled!(log::Level::Debug) {
            log::debug!("merkle_root: {merkle_root}");
            log::debug!("MethodId");
            for (i, entry) in method_id.table.iter().enumerate() {
                let marker = if i == which { "*" } else { "" };
                log::debug!("  {i}: {entry}{marker}");
            }
        }
        method_id.table[which] == *merkle_root
    };

    verify(hal, &CIRCUIT, seal, check_code).map_err(|err| anyhow!("Verification failed: {:?}", err))
}

impl Receipt {
    #[cfg(all(feature = "verify", feature = "host"))]
    pub fn verify<'a, M>(&self, method_id: &'a M) -> Result<()>
    where
        M: ?Sized,
        MethodId: From<&'a M>,
    {
        use crate::CIRCUIT;
        use risc0_zkp::{core::sha::default_implementation, verify::VerifyImpl};

        let sha = default_implementation();
        let hal = VerifyImpl::new(sha, &CIRCUIT);
        self.verify_with_hal(&hal, method_id)
    }

    #[cfg(feature = "verify")]
    pub fn verify_with_hal<'a, M, H>(&self, hal: &H, method_id: &'a M) -> Result<()>
    where
        H: risc0_zkp::verify::VerifyHal,
        M: ?Sized,
        MethodId: From<&'a M>,
    {
        verify_with_hal(hal, method_id, &self.seal)
    }

    // Compatible API with FFI-based prover.
    pub fn get_journal_vec(&self) -> Result<Vec<u32>> {
        Ok(self.journal.clone())
    }

    // Compatible API with FFI-based prover.
    pub fn get_journal(&self) -> Result<&[u8]> {
        Ok(bytemuck::cast_slice(self.journal.as_slice()))
    }

    // Compatible API with FFI-based prover.
    // FIXME: Change API to avoid copy.
    pub fn get_seal(&self) -> Result<&[u32]> {
        Ok(self.seal.as_slice())
    }
}
