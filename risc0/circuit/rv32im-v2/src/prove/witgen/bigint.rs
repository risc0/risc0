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
    execute::bigint::{BigIntState, BIGINT_STATE_COUNT},
    zirgen::circuit::{BigIntStateLayout, LAYOUT_TOP},
};

const BIGINT_STATE_LAYOUT: &BigIntStateLayout = LAYOUT_TOP.inst_result.arm12.state;

impl BigIntState {
    pub(crate) const fn offsets() -> [usize; BIGINT_STATE_COUNT] {
        [
            BIGINT_STATE_LAYOUT.is_ecall._super.offset,
            BIGINT_STATE_LAYOUT.pc._super.offset,
            BIGINT_STATE_LAYOUT.poly_op._super.offset,
            BIGINT_STATE_LAYOUT.coeff._super.offset,
            BIGINT_STATE_LAYOUT.bytes[0]._super.offset,
            BIGINT_STATE_LAYOUT.bytes[1]._super.offset,
            BIGINT_STATE_LAYOUT.bytes[2]._super.offset,
            BIGINT_STATE_LAYOUT.bytes[3]._super.offset,
            BIGINT_STATE_LAYOUT.bytes[4]._super.offset,
            BIGINT_STATE_LAYOUT.bytes[5]._super.offset,
            BIGINT_STATE_LAYOUT.bytes[6]._super.offset,
            BIGINT_STATE_LAYOUT.bytes[7]._super.offset,
            BIGINT_STATE_LAYOUT.bytes[8]._super.offset,
            BIGINT_STATE_LAYOUT.bytes[9]._super.offset,
            BIGINT_STATE_LAYOUT.bytes[10]._super.offset,
            BIGINT_STATE_LAYOUT.bytes[11]._super.offset,
            BIGINT_STATE_LAYOUT.bytes[12]._super.offset,
            BIGINT_STATE_LAYOUT.bytes[13]._super.offset,
            BIGINT_STATE_LAYOUT.bytes[14]._super.offset,
            BIGINT_STATE_LAYOUT.bytes[15]._super.offset,
            BIGINT_STATE_LAYOUT.next_state._super.offset,
        ]
    }

    pub(crate) fn as_array(&self) -> [u32; BIGINT_STATE_COUNT] {
        [
            self.is_ecall as u32,
            self.pc.0,
            self.poly_op as u32,
            self.coeff,
            self.bytes[0] as u32,
            self.bytes[1] as u32,
            self.bytes[2] as u32,
            self.bytes[3] as u32,
            self.bytes[4] as u32,
            self.bytes[5] as u32,
            self.bytes[6] as u32,
            self.bytes[7] as u32,
            self.bytes[8] as u32,
            self.bytes[9] as u32,
            self.bytes[10] as u32,
            self.bytes[11] as u32,
            self.bytes[12] as u32,
            self.bytes[13] as u32,
            self.bytes[14] as u32,
            self.bytes[15] as u32,
            self.next_state as u32,
        ]
    }
}
