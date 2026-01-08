// Copyright 2026 RISC Zero, Inc.
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

use alloc::boxed::Box;

use risc0_core::field::{Elem, Field};

use crate::core::{
    digest::Digest,
    hash::{Rng, RngFactory},
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

    pub fn read_u32s(&mut self, n: usize) -> &'a [u32] {
        let u32s;
        (u32s, self.proof) = self.proof.split_at(n);
        u32s
    }

    /// Read some field elements from this IOP, and check to make sure
    /// they're not INVALID.
    pub fn read_field_elem_slice<T: Elem>(&mut self, n: usize) -> &'a [T] {
        let u32s = self.read_u32s(n * T::WORDS);
        T::from_u32_slice(u32s)
    }

    /// Read some plain old data from this IOP without doing any
    /// validation.  Prefer to use read_field_elem_slice if reading
    /// field elements.
    pub fn read_pod_slice<T: bytemuck::Pod>(&mut self, n: usize) -> &'a [T] {
        let u32s;
        (u32s, self.proof) = self
            .proof
            .split_at(n * core::mem::size_of::<T>() / core::mem::size_of::<u32>());
        bytemuck::cast_slice(u32s)
    }

    pub fn commit(&mut self, digest: &Digest) {
        self.rng.mix(digest);
    }

    /// Checks that the entire data of the IOP has been read.
    pub fn verify_complete(&self) {
        assert_eq!(self.proof.len(), 0);
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
