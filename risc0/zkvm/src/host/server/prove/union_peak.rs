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

use anyhow::Result;

use crate::{SuccinctReceipt, Unknown, mmr::Peak, recursion::prove::union};

#[derive(Debug)]
pub struct UnionPeak {
    receipt: SuccinctReceipt<Unknown>,
    height: u32,
}

impl Peak for UnionPeak {
    type Item = SuccinctReceipt<Unknown>;

    fn new(item: Self::Item) -> Self {
        Self::new_with_height(item, 0)
    }

    fn new_with_height(item: Self::Item, height: u32) -> Self {
        Self {
            receipt: item,
            height,
        }
    }

    fn height(&self) -> u32 {
        self.height
    }

    fn merge_item(a: &mut Self::Item, b: Self::Item) -> Result<()> {
        *a = union(a, &b)?.into_unknown();
        Ok(())
    }

    fn item(self) -> Self::Item {
        self.receipt
    }
}
