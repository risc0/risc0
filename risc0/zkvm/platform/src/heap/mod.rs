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

#[cfg(not(feature = "heap-embedded-alloc"))]
pub(crate) mod bump;

#[cfg(feature = "heap-embedded-alloc")]
pub mod embedded;

/// Estimate of used memory on the heap, in bytes.
pub fn used() -> usize {
    cfg_if::cfg_if! {
        if #[cfg(feature = "heap-embedded-alloc")] {
            0
        } else {
            bump::used()
        }
    }
}

/// Estimate of free memory on the heap, in bytes.
pub fn free() -> usize {
    cfg_if::cfg_if! {
        if #[cfg(feature = "heap-embedded-alloc")] {
            0
        } else {
            bump::free()
        }
    }
}

/// Initialize the heap with the memory allocations defined in the [memory][crate::memory] module.
///
/// # Safety
///
/// This function must be called exactly once, before the heap is used.
pub unsafe fn init() {
    cfg_if::cfg_if! {
        if #[cfg(feature = "heap-embedded-alloc")] {
            unsafe { embedded::init(); }
        } else {
            unsafe { bump::init(); }
        }
    }
}
