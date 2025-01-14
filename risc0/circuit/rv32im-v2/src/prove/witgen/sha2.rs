// Copyright 2025 RISC Zero, Inc.
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

use crate::{
    execute::sha2::Sha2State,
    zirgen::circuit::{ShaStateLayout, LAYOUT_TOP},
};

const SHA2_STATE_LAYOUT: &ShaStateLayout = LAYOUT_TOP.inst_result.arm11.state;
const SHA2_FP_COUNT: usize = 7;
const SHA2_U32_COUNT: usize = 3;

impl Sha2State {
    pub(crate) const fn fp_offsets() -> [usize; SHA2_FP_COUNT] {
        [
            SHA2_STATE_LAYOUT.state_in_addr._super.offset,
            SHA2_STATE_LAYOUT.state_out_addr._super.offset,
            SHA2_STATE_LAYOUT.data_addr._super.offset,
            SHA2_STATE_LAYOUT.count._super.offset,
            SHA2_STATE_LAYOUT.k_addr._super.offset,
            SHA2_STATE_LAYOUT.round._super.offset,
            SHA2_STATE_LAYOUT.next_state._super.offset,
        ]
    }

    pub(crate) const fn u32_offsets() -> [usize; SHA2_U32_COUNT] {
        [
            SHA2_STATE_LAYOUT.a[0]._super.offset,
            SHA2_STATE_LAYOUT.e[0]._super.offset,
            SHA2_STATE_LAYOUT.w[0]._super.offset,
        ]
    }

    pub(crate) fn fp_array(&self) -> [u32; SHA2_FP_COUNT] {
        [
            self.state_in_addr.0,
            self.state_out_addr.0,
            self.data_addr.0,
            self.count,
            self.k_addr.0,
            self.round,
            self.next_state as u32,
        ]
    }

    pub(crate) fn u32_array(&self) -> [u32; SHA2_U32_COUNT] {
        [self.a, self.e, self.w]
    }
}
