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

use alloc::vec::Vec;
use anyhow::{bail, Result};

use crate::{SuccinctReceipt, Unknown};

#[derive(Debug, Default)]
pub struct UnionMmr {
    peaks: Vec<Peak>,
}

impl UnionMmr {
    pub fn insert(&mut self, receipt: SuccinctReceipt<Unknown>) {
        let mut to_add = Peak::new(receipt);
        loop {
            if self.peaks.is_empty() {
                // at the point a peak has been accumulated to `to_add`
                break;
            }
            if to_add.height == self.peaks.last().unwrap().height {
                let to_merge = self.peaks.pop().unwrap();
                to_add = Peak::merge(to_add, to_merge);
            } else {
                break;
            }
        }
        self.peaks.push(to_add);
    }

    pub fn root(&self) -> Result<SuccinctReceipt<Unknown>> {
        if self.peaks.is_empty() {
            bail!("no elements");
        }
        if self.peaks.len() == 1 {
            return Ok(self.peaks[0].receipt.clone());
        }

        let receipt = self.peaks[0].receipt.clone();
        for peak in &self.peaks[1..] {
            Peak::merge_item(&receipt, &peak.receipt)?;
        }
        Ok(receipt)
    }
}

#[derive(Debug)]
struct Peak {
    height: u32,
    receipt: SuccinctReceipt<Unknown>,
}

impl Peak {
    pub(crate) fn new(receipt: SuccinctReceipt<Unknown>) -> Self {
        Self { receipt, height: 0 }
    }

    pub(crate) fn merge(_a: Peak, _b: Peak) -> Self {
        todo!() // make sure we call union with correct order
    }
    pub(crate) fn merge_item(
        _a: &SuccinctReceipt<Unknown>,
        _b: &SuccinctReceipt<Unknown>,
    ) -> Result<()> {
        todo!()
    }
}
