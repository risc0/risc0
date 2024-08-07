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

pub mod emu;
pub mod engine;
pub mod hal;
pub mod segment;

use anyhow::Result;
use cfg_if::cfg_if;

use self::segment::Segment;

pub type Seal = Vec<u32>;

pub trait SegmentProver {
    fn prove_segment(&self, segment: &Segment) -> Result<Seal>;
}

pub fn segment_prover(hashfn: &str) -> Result<Box<dyn SegmentProver>> {
    cfg_if! {
        if #[cfg(feature = "cuda")] {
            self::hal::cuda::segment_prover(hashfn)
        } else if #[cfg(any(all(target_os = "macos", target_arch = "aarch64"), target_os = "ios"))] {
            self::hal::metal::segment_prover(hashfn)
        } else {
            self::hal::cpu::segment_prover(hashfn)
        }
    }
}
