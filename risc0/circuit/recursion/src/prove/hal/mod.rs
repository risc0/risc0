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

use anyhow::Result;
use risc0_circuit_recursion_sys::{RawPreflightTrace, StepMode};
use risc0_zkp::hal::Hal;

pub(crate) mod cpu;
#[cfg(feature = "cuda")]
pub(crate) mod cuda;
// #[cfg(all(
//     feature = "prove",
//     any(all(target_os = "macos", target_arch = "aarch64"), target_os = "ios")
// ))]
// pub mod metal;

pub(crate) trait CircuitWitnessGenerator<H: Hal> {
    fn generate_witness(
        &self,
        mode: StepMode,
        total_cycles: u32,
        preflight: &RawPreflightTrace,
        ctrl: &H::Buffer<H::Elem>,
        data: &H::Buffer<H::Elem>,
        global: &H::Buffer<H::Elem>,
    ) -> Result<()>;
}

pub(crate) trait CircuitAccumulator<H: Hal> {
    #[allow(clippy::too_many_arguments)]
    fn accumulate(
        &self,
        work_cycles: u32,
        total_cycles: u32,
        ctrl: &H::Buffer<H::Elem>,
        global: &H::Buffer<H::Elem>,
        data: &H::Buffer<H::Elem>,
        mix: &H::Buffer<H::Elem>,
        accum: &H::Buffer<H::Elem>,
    ) -> Result<()>;
}
