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

//! CubeCL-based GPU HAL implementation for the ZKP system.
//!
//! This module provides a portable GPU implementation using cubecl,
//! supporting CUDA, WGPU, ROCm, and Metal backends from a single codebase.

pub mod buffer;
pub mod ext_field;
pub mod field;
pub mod hal;
pub mod kernels;
pub mod ntt;
pub mod poseidon2;
pub mod twiddle;

#[cfg(test)]
mod tests;
