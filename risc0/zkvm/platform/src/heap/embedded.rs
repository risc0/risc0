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

use critical_section::RawRestoreState;
use embedded_alloc::TlsfHeap as Heap;

#[global_allocator]
pub static HEAP: Heap = Heap::empty();

struct CriticalSection;
critical_section::set_impl!(CriticalSection);

unsafe impl critical_section::Impl for CriticalSection {
    unsafe fn acquire() -> RawRestoreState {
        // this is a no-op. we're in a single-threaded, non-preemptive context
    }

    unsafe fn release(_token: RawRestoreState) {
        // this is a no-op. we're in a single-threaded, non-preemptive context
    }
}

/// Initialize the embedded-alloc allocator with the memory allocations defined in the [memory][crate::memory] module.
///
/// # Safety
///
/// This function must be called exactly once.
pub unsafe fn init() {
    unsafe extern "C" {
        static _end: u8;
    }
    let heap_pos: usize = unsafe { (&_end) as *const u8 as usize };
    let heap_size: usize = crate::memory::GUEST_MAX_MEM - heap_pos;
    unsafe { HEAP.init(heap_pos, heap_size) }
}
