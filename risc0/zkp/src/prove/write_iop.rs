// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use alloc::vec::Vec;

use risc0_core::field::{Elem, Field};

use crate::core::{
    digest::Digest,
    hash::{Rng, RngFactory},
};

pub struct WriteIOP<F: Field> {
    pub proof: Vec<u32>,
    pub rng: Box<dyn Rng<F>>,
}

impl<F: Field> WriteIOP<F> {
    /// Create a new empty proof
    pub fn new(rng: &dyn RngFactory<F>) -> Self {
        Self {
            proof: Vec::new(),
            rng: rng.new_rng(),
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
    pub fn write_field_elem_slice<T: Elem>(&mut self, slice: &[T]) {
        self.proof.extend(Elem::as_u32_slice(slice))
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
