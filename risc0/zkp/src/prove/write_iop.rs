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

use alloc::vec::Vec;

use risc0_core::field;

use crate::core::{
    sha::{Digest, Sha256},
    sha_rng::ShaRng,
};

pub struct WriteIOP<S: Sha256> {
    pub proof: Vec<u32>,
    pub rng: ShaRng<S>,
}

impl<S: Sha256> WriteIOP<S> {
    /// Create a new empty proof
    pub fn new() -> Self {
        Self {
            proof: Vec::new(),
            rng: ShaRng::<S>::new(),
        }
    }

    /// Called by the prover to write some data.
    ///
    /// This data is not cryptographically verifiable on its own,
    /// but is typically committed by a later hash which includes it.
    pub fn write_u32_slice(&mut self, slice: &[u32]) {
        self.proof.extend_from_slice(slice);
    }

    /// Write some field elements to this IOP.
    pub fn write_field_elem_slice<T: field::Elem>(&mut self, slice: &[T]) {
        self.proof.extend(field::Elem::as_u32_slice(slice))
    }

    /// Write some plain old data to this IOP.
    pub fn write_pod_slice<T: bytemuck::Pod>(&mut self, slice: &[T]) {
        self.proof.extend(bytemuck::cast_slice(slice))
    }

    /// Called by the prover to commit to some hash (usually data written
    /// earlier or a Merkle root).
    pub fn commit(&mut self, message: &Digest) {
        self.rng.mix(message);
    }
}
