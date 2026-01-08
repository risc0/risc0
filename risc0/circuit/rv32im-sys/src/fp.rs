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

use bytemuck::{Pod, Zeroable};
use risc0_zkp::field::baby_bear::{self, Elem as BabyBearElem};

/// This is the field point type that proving uses. It has weaker guarantees than BabyBearElem and
/// implements `Pod`
#[derive(Debug, Copy, Clone, PartialEq, Eq, Pod, Zeroable, Default, PartialOrd, Ord)]
#[repr(C)]
pub struct Fp(u32);

impl From<BabyBearElem> for Fp {
    fn from(elem: BabyBearElem) -> Self {
        Self(elem.as_u32())
    }
}

impl Fp {
    pub fn as_raw(&self) -> u32 {
        self.0
    }

    pub fn new_raw(v: u32) -> Self {
        Self(v)
    }

    pub fn from_elem_array<const N: usize>(elems: [BabyBearElem; N]) -> [Self; N] {
        let mut self_ = [Self(0); N];
        for (self_cell, &elem) in self_.iter_mut().zip(elems.iter()) {
            *self_cell = Self(elem.as_u32_montgomery());
        }
        self_
    }

    pub fn as_elem_array<const N: usize>(elems: &[Self; N]) -> &[BabyBearElem; N] {
        for &elem in elems {
            assert!(elem.0 < baby_bear::P, "invalid baby bear element");
        }
        unsafe { std::mem::transmute(elems) }
    }

    pub fn to_elem(&self) -> BabyBearElem {
        assert!(self.0 < baby_bear::P, "invalid baby bear element");
        BabyBearElem::new_raw(self.0)
    }
}
