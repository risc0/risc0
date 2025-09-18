// Copyright 2025 RISC Zero, Inc.
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

mod hal;
#[cfg(test)]
mod tests;
mod witgen;

use anyhow::Result;
use cfg_if::cfg_if;
use risc0_core::scope;

use crate::execute::segment::Segment;

pub use witgen::PreflightResults;

const GLOBAL_MIX: usize = 0;
const GLOBAL_OUT: usize = 1;

pub type Seal = Vec<u32>;

pub trait SegmentProver {
    fn prove(&self, segment: &Segment) -> Result<Seal> {
        scope!("prove");
        let results = self.preflight(segment)?;
        self.prove_core(results)
    }

    fn preflight(&self, segment: &Segment) -> Result<PreflightResults>;

    fn prove_core(&self, preflight_results: PreflightResults) -> Result<Seal>;
}

pub fn segment_prover() -> Result<Box<dyn SegmentProver>> {
    cfg_if! {
        if #[cfg(feature = "cuda")] {
            self::hal::cuda::segment_prover()
        // } else if #[cfg(any(all(target_os = "macos", target_arch = "aarch64"), target_os = "ios"))] {
        // self::hal::metal::segment_prover(hashfn)
        } else {
            self::hal::cpu::segment_prover()
        }
    }
}
