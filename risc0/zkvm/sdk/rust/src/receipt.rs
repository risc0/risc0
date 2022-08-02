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

use crate::method_id::MethodId;

use anyhow::Result;
use serde::{Deserialize, Serialize};

#[derive(Deserialize, Serialize)]
pub struct Receipt {
    pub journal: Vec<u32>,
    pub seal: Vec<u32>,
}

// FIXME: Remove this temporary trait to convert method IDs once our API is the
// same between FFI and rust-based provers.
pub trait IntoMethodId {}
impl IntoMethodId for &MethodId {}
impl IntoMethodId for &[u8] {}

impl Receipt {
    #[cfg(feature = "verify")]
    pub fn verify<M>(&self, _method_id: M) -> Result<()>
    where
        M: IntoMethodId,
    {
        todo!()
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
