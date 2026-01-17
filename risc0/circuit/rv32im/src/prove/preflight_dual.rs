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

use anyhow::Result;

use crate::execute::Segment;
use risc0_circuit_rv32im_sys::*;

use super::preflight::{PreflightContext as PreflightContext2, SegmentContext as SegmentContext2};
use super::preflight_cxx::{
    PreflightContext as PreflightContext1, SegmentContext as SegmentContext1,
};

#[derive(Default)]
pub struct PreflightContext {
    ctx1: PreflightContext1,
    ctx2: PreflightContext2,
}

pub struct SegmentContext {
    ctx1: SegmentContext1,
    ctx2: SegmentContext2,
}

impl SegmentContext {
    pub fn new(segment: &Segment) -> Result<Self> {
        Ok(Self {
            ctx1: SegmentContext1::new(segment)?,
            ctx2: SegmentContext2::new(segment)?,
        })
    }

    pub fn preflight(&self, po2: usize) -> Result<PreflightContext> {
        let ctx1 = self.ctx1.preflight(po2)?;
        let ctx2 = self.ctx2.preflight(po2)?;

        assert_trace_eq(&ctx1, &ctx2);

        Ok(PreflightContext { ctx1, ctx2 })
    }
}

impl PreflightContext {
    pub fn is_final(&self) -> bool {
        let a = self.ctx1.is_final();
        let b = self.ctx2.is_final;
        assert_eq!(a, b);
        a
    }

    pub fn po2(&self) -> u32 {
        let a = self.ctx1.po2();
        let b = self.ctx2.po2;
        assert_eq!(a, b);
        a
    }

    pub fn block_counts(&self) -> enum_map::EnumMap<BlockType, u32> {
        let a = self.ctx1.block_counts();
        let b = self.ctx2.block_counts();
        assert_eq!(a, b);
        a
    }
}

fn assert_trace_eq(a: &PreflightContext1, b: &PreflightContext2) {
    let a_rows = unsafe { std::slice::from_raw_parts(a.row_info_ptr(), a.row_info_size()) };
    let a_aux = unsafe { std::slice::from_raw_parts(a.aux_ptr(), a.aux_size()) };
    let trace_a = super::preflight::trace::decode_trace(a_rows, a_aux);

    let trace_b = super::preflight::trace::decode_trace(&b.row_info, &b.aux);

    let mut equality_report = vec![];
    for block_type in BlockType::iter() {
        let a: Vec<_> = trace_a
            .iter()
            .filter(|b| b.block_type() == block_type)
            .collect();
        let b: Vec<_> = trace_b
            .iter()
            .filter(|b| b.block_type() == block_type)
            .collect();

        if a.len() != b.len() {
            equality_report.push(format!(
                "{block_type:?} lengths don't match; {} != {}",
                a.len(),
                b.len()
            ));
        } else {
            for i in 0..a.len() {
                if a[i] != b[i] {
                    equality_report.push(format!(
                        "{block_type:?} index={i}: {:?} != {:?}",
                        a[i], b[i]
                    ));
                }
            }
        }
    }
    if !equality_report.is_empty() {
        panic!(
            "traces not equal: \n{}",
            equality_report.join("\n\n=============\n")
        );
    }
    assert_eq!(a_rows.len(), b.row_info.len());
}
