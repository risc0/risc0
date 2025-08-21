// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

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
