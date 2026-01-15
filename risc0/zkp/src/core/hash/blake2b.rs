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

//! A Blake2b HashSuite.
use alloc::{boxed::Box, rc::Rc, vec::Vec};
use core::marker::PhantomData;

use blake2::{
    Blake2bVar,
    digest::{Update, VariableOutput},
};
use rand_core::{RngCore, impls};
use risc0_core::field::{
    Elem, ExtElem,
    baby_bear::{BabyBear, BabyBearElem, BabyBearExtElem},
};

use super::{HashFn, HashSuite, Rng, RngFactory};
use crate::core::digest::Digest;

/// Hash function trait.
pub trait Blake2b: Send + Sync {
    /// A function producing a hash from a list of u8.
    fn blake2b<T: AsRef<[u8]>>(data: T) -> [u8; 32];
}

/// Implementation of blake2b using CPU.
pub struct Blake2bCpuImpl;

/// Type alias for Blake2b HashSuite using CPU.
pub type Blake2bCpuHashSuite = Blake2bHashSuite<Blake2bCpuImpl>;

impl Blake2b for Blake2bCpuImpl {
    fn blake2b<T: AsRef<[u8]>>(data: T) -> [u8; 32] {
        let mut result = [0; 32];
        let mut hasher = Blake2bVar::new(32).expect("Initializing Blake2bVar failed");

        hasher.update(data.as_ref());
        hasher
            .finalize_variable(&mut result)
            .expect("Finalizing Blake2bVar failed");
        result
    }
}

struct Blake2bRngFactory<T: Blake2b> {
    phantom: PhantomData<T>,
}

impl<T: Blake2b> Blake2bRngFactory<T> {
    fn new() -> Self {
        Self {
            phantom: PhantomData,
        }
    }
}

impl<T: Blake2b + 'static> RngFactory<BabyBear> for Blake2bRngFactory<T> {
    fn new_rng(&self) -> Box<dyn Rng<BabyBear>> {
        let rng: Blake2bRng<T> = Blake2bRng::new();
        Box::new(rng)
    }
}

/// Blake2b HashSuite.
/// We are using a generic hasher to allow different implementations.
pub struct Blake2bHashSuite<T: Blake2b> {
    phantom: PhantomData<T>,
}

impl<T: Blake2b + 'static> Blake2bHashSuite<T> {
    /// Create a new HashSuite
    pub fn new_suite() -> HashSuite<BabyBear> {
        HashSuite {
            name: "blake2b".into(),
            hashfn: Rc::new(Blake2bHashFn::<T>::new()),
            rng: Rc::new(Blake2bRngFactory::<T>::new()),
        }
    }
}

/// Blake2b HashFn.
struct Blake2bHashFn<T: Blake2b> {
    phantom: PhantomData<T>,
}

impl<T: Blake2b> Blake2bHashFn<T> {
    fn new() -> Self {
        Self {
            phantom: PhantomData,
        }
    }
}

impl<T: Blake2b> HashFn<BabyBear> for Blake2bHashFn<T> {
    fn hash_pair(&self, a: &Digest, b: &Digest) -> Box<Digest> {
        let concat = [a.as_bytes(), b.as_bytes()].concat();
        Box::new(Digest::from(T::blake2b(concat)))
    }

    fn hash_elem_slice(&self, slice: &[BabyBearElem]) -> Box<Digest> {
        let mut data = Vec::<u8>::new();
        for el in slice {
            data.extend_from_slice(el.as_u32_montgomery().to_be_bytes().as_slice());
        }
        Box::new(Digest::from(T::blake2b(data)))
    }

    fn hash_ext_elem_slice(&self, slice: &[BabyBearExtElem]) -> Box<Digest> {
        let mut data = Vec::<u8>::new();
        for ext_el in slice {
            for el in ext_el.subelems() {
                data.extend_from_slice(el.as_u32_montgomery().to_be_bytes().as_slice());
            }
        }
        Box::new(Digest::from(T::blake2b(data)))
    }
}

/// Blake2b-based random number generator.
pub struct Blake2bRng<T: Blake2b> {
    current: [u8; 32],
    hasher: PhantomData<T>,
}

impl<T: Blake2b> Blake2bRng<T> {
    fn new() -> Self {
        Self {
            current: [0; 32],
            hasher: Default::default(),
        }
    }
}

impl<T: Blake2b> Rng<BabyBear> for Blake2bRng<T> {
    fn mix(&mut self, val: &Digest) {
        let concat = [self.current.as_ref(), val.as_bytes()].concat();
        self.current = T::blake2b(concat);
    }

    fn random_bits(&mut self, bits: usize) -> u32 {
        ((1 << bits) - 1) & self.next_u32()
    }

    fn random_elem(&mut self) -> BabyBearElem {
        BabyBearElem::random(self)
    }

    fn random_ext_elem(&mut self) -> BabyBearExtElem {
        BabyBearExtElem::random(self)
    }
}

impl<T: Blake2b> RngCore for Blake2bRng<T> {
    fn next_u32(&mut self) -> u32 {
        let next = T::blake2b(self.current);
        self.current = next;
        ((next[0] as u32) << 24)
            + ((next[1] as u32) << 16)
            + ((next[2] as u32) << 8)
            + (next[3] as u32)
    }

    fn next_u64(&mut self) -> u64 {
        impls::next_u64_via_u32(self)
    }

    fn fill_bytes(&mut self, dest: &mut [u8]) {
        impls::fill_bytes_via_next(self, dest);
    }
}
