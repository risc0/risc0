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

pub(crate) mod bibc;
pub(crate) mod bigint;
mod executor;
pub mod gdb;
pub(crate) mod pager;
pub mod platform;
pub(crate) mod poseidon2;
pub(crate) mod r0vm;
pub(crate) mod rv32im;
pub(crate) mod segment;
pub(crate) mod sha2;
mod syscall;
#[cfg(test)]
mod tests;
pub mod testutil;

#[cfg(feature = "rv32im-m3")]
mod block_tracker;

pub use self::{
    bigint::analyze::analyze as bigint_analyze,
    executor::{CycleLimit, Executor, ExecutorResult, SegmentUpdate, SimpleSession},
    platform::*,
    segment::Segment,
    syscall::{Syscall, SyscallContext},
};

pub const DEFAULT_SEGMENT_LIMIT_PO2: usize = 20;

pub(crate) fn node_idx(page_idx: u32) -> u32 {
    MEMORY_PAGES as u32 + page_idx
}

#[inline]
#[cold]
fn cold() {}

#[inline]
#[allow(dead_code)]
fn likely(b: bool) -> bool {
    if !b {
        cold()
    }
    b
}

#[inline]
fn unlikely(b: bool) -> bool {
    if b {
        cold()
    }
    b
}
