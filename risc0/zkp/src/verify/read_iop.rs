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

use alloc::boxed::Box;

use risc0_core::field::{Elem, Field};

use crate::{
    core::{
        digest::Digest,
        hash::{Rng, RngFactory},
    },
    verify::VerificationError,
};

pub struct ReadIOP<'a, F: Field> {
    proof: &'a [u32],
    rng: Box<dyn Rng<F>>,
}

impl<'a, F: Field> ReadIOP<'a, F> {
    pub fn new(proof: &'a [u32], rng: &dyn RngFactory<F>) -> Self {
        ReadIOP {
            proof,
            rng: rng.new_rng(),
        }
    }

    pub fn read_u32s(&mut self, n: usize) -> Result<&'a [u32], VerificationError> {
        let Some(u32s) = self.proof.split_off(..n) else {
            tracing::debug!(
                "Tried to read {n} u32s from seal; seal length remaining {}",
                self.proof.len()
            );
            return Err(VerificationError::ReceiptFormatError);
        };
        Ok(u32s)
    }

    /// Read some field elements from this IOP, and check to make sure
    /// they're not INVALID.
    pub fn read_field_elem_slice<T: Elem>(
        &mut self,
        n: usize,
    ) -> Result<&'a [T], VerificationError> {
        let u32s = self.read_u32s(n * T::WORDS)?;
        T::try_from_u32_slice(u32s).map_err(|e| {
            tracing::debug!("casting seal elems to field slice failed: {e}");
            VerificationError::ReceiptFormatError
        })
    }

    /// Read some plain old data from this IOP without doing any
    /// validation.  Prefer to use read_field_elem_slice if reading
    /// field elements.
    pub fn read_pod_slice<T: bytemuck::Pod>(
        &mut self,
        n: usize,
    ) -> Result<&'a [T], VerificationError> {
        let read_size = n * core::mem::size_of::<T>() / core::mem::size_of::<u32>();
        let u32s = self.read_u32s(read_size)?;
        bytemuck::try_cast_slice(u32s).map_err(|e| {
            tracing::debug!("casting seal elems to slice failed: {e}");
            VerificationError::ReceiptFormatError
        })
    }

    pub fn commit(&mut self, digest: &Digest) {
        self.rng.mix(digest);
    }

    /// Checks that the entire data of the IOP has been read.
    pub fn verify_complete(&self) -> Result<(), VerificationError> {
        if !self.proof.is_empty() {
            tracing::debug!(
                "verify_complete called with {} words remaining in seal",
                self.proof.len()
            );
            return Err(VerificationError::ReceiptFormatError);
        }
        Ok(())
    }

    /// Get a cryptographically uniform u32
    pub fn random_bits(&mut self, bits: usize) -> u32 {
        self.rng.random_bits(bits)
    }

    /// Get a cryptographically uniform field element
    pub fn random_elem(&mut self) -> F::Elem {
        self.rng.random_elem()
    }

    /// Get a cryptographically uniform extension field element
    pub fn random_ext_elem(&mut self) -> F::ExtElem {
        self.rng.random_ext_elem()
    }
}
