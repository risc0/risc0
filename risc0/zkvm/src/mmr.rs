// Copyright 2024 RISC Zero, Inc.
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
use risc0_zkp::core::digest::Digest;

use crate::{receipt_claim::UnionClaim, sha::Digestible};

#[derive(Debug, Default)]
pub struct Mmr {
    peaks: Vec<Peak>,
}

impl Mmr {
    pub fn insert(&mut self, digest: Digest) {
        let mut to_add = Peak::new(digest);
        loop {
            // We're at the end. This means that we've accumulated everything in `to_add`
            if self.peaks.is_empty() {
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

    pub fn root(&self) -> Result<Digest> {
        if self.peaks.is_empty() {
            bail!("no elements");
        }
        if self.peaks.len() == 1 {
            return Ok(self.peaks[0].digest);
        }

        let mut digest = self.peaks[0].digest;
        for peak in &self.peaks[1..] {
            digest = UnionClaim {
                left: digest,
                right: peak.digest,
            }
            .digest();
        }
        Ok(digest)
    }
}

#[derive(Debug)]
struct Peak {
    height: u32,
    digest: Digest,
}

impl Peak {
    pub(crate) fn new(digest: Digest) -> Self {
        Self { digest, height: 0 }
    }

    // assumes that both inputs have same height
    pub(crate) fn merge(left: Peak, right: Peak) -> Self {
        let digest = UnionClaim {
            left: left.digest,
            right: right.digest,
        }
        .digest();
        Self {
            digest,
            height: left.height + 1,
        }
    }
}
