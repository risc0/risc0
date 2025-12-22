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

#![cfg_attr(target_os = "zkvm", no_std)]

use crate::constants::USER_REGS_PTR;

pub mod atomics;
pub mod constants;
pub mod emul;
pub mod softfloat;

pub fn get_ureg(idx: usize) -> u32 {
    // x0 (register 0) should always return 0
    if idx == 0 {
        return 0;
    }
    unsafe { USER_REGS_PTR.add(idx).read() }
}

pub fn set_ureg(idx: usize, word: u32) {
    // Guard against writing to x0 (register 0) - it should always remain 0
    if idx == 0 {
        return;
    }
    unsafe { USER_REGS_PTR.add(idx).write_volatile(word) };
}

pub fn mret() -> ! {
    #[cfg(target_arch = "riscv32")]
    unsafe {
        core::arch::asm!("mret", options(noreturn))
    }
    #[cfg(not(target_arch = "riscv32"))]
    unimplemented!()
}
