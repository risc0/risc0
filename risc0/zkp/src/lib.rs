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

#![doc = include_str!("../README.md")]
#![cfg_attr(not(feature = "std"), no_std)]
#![deny(rustdoc::broken_intra_doc_links)]
#![cfg_attr(docsrs, feature(doc_cfg))]

extern crate alloc;

pub mod adapter;
pub mod core;
#[cfg(feature = "prove")]
pub mod hal;
pub mod layout;
mod merkle;
#[cfg(feature = "prove")]
pub mod prove;
pub mod taps;
pub mod verify;

pub use risc0_core::field;

pub const MIN_CYCLES_PO2: usize = 13;
pub const MIN_CYCLES: usize = 1 << MIN_CYCLES_PO2; // 8K
pub const MAX_CYCLES_PO2: usize = 24;
pub const MAX_CYCLES: usize = 1 << MAX_CYCLES_PO2; // 16M

/// 50 FRI queries are sufficient to achieve our security target of 97 bits (conjectured security)
pub const QUERIES: usize = 50;
pub const ZK_CYCLES: usize = 1024; // TODO: Ideally we'd compute ZK_CYCLES programmatically
pub const MIN_PO2: usize = core::log2_ceil(1 + ZK_CYCLES);

/// Inverse of Reed-Solomon Expansion Rate
pub const INV_RATE: usize = 4;

const FRI_FOLD_PO2: usize = 4;

/// FRI folding factor is 2 ^ FRI_FOLD_PO2
pub const FRI_FOLD: usize = 1 << FRI_FOLD_PO2;

/// FRI continues until the degree of the FRI polynomial reaches FRI_MIN_DEGREE
const FRI_MIN_DEGREE: usize = 256;
