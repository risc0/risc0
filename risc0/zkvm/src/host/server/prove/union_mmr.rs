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

use alloc::collections::VecDeque;
use anyhow::{bail, Result};

use crate::{recursion::prove::union, SuccinctReceipt, Unknown};

#[derive(Debug)]
pub struct MerkleMountainAccumulator<T: Peak> {
    peaks: VecDeque<T>,
}

impl<T> MerkleMountainAccumulator<T>
where
    T: Peak,
{
    pub fn new() -> Self {
        Self {
            peaks: VecDeque::new(),
        }
    }
    pub fn insert(&mut self, item: T::Item) -> Result<()> {
        let mut to_add: T = T::new(item);
        loop {
            if self.peaks.is_empty() {
                // at the point a peak has been accumulated to `to_add`
                break;
            }
            if to_add.height() == self.peaks.back().unwrap().height() {
                let to_merge = self.peaks.pop_back().unwrap();
                to_add = *Peak::merge(to_add, to_merge)?;
            } else {
                break;
            }
        }
        self.peaks.push_back(to_add);
        Ok(())
    }

    pub fn root(mut self) -> Result<T::Item> {
        if self.peaks.is_empty() {
            bail!("no elements for host mmr");
        }
        if self.peaks.len() == 1 {
            return Ok(self.peaks.pop_back().unwrap().item());
        }

        let mut item = self.peaks.pop_front().unwrap().item();
        for peak in self.peaks.into_iter() {
            T::merge_item(&mut item, peak.item())?;
        }
        Ok(item)
    }
}

#[derive(Debug)]
pub struct UnionPeak {
    height: u32,
    receipt: SuccinctReceipt<Unknown>,
}

pub trait Peak {
    type Item;
    fn new(item: Self::Item) -> Self;
    fn new_with_height(item: Self::Item, height: u32) -> Self;
    fn height(&self) -> u32;
    fn item(self) -> Self::Item;
    fn merge(a: Self, b: Self) -> Result<Box<Self>>
    where
        Self: Sized,
    {
        if a.height() != b.height() {
            bail!("merge attempted on peaks of different heights")
        }
        let height = a.height();
        let mut a: Self::Item = a.item();
        Self::merge_item(&mut a, b.item())?;
        Ok(Box::new(Self::new_with_height(a, height + 1)))
    }

    fn merge_item(a: &mut Self::Item, b: Self::Item) -> Result<()>;
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
