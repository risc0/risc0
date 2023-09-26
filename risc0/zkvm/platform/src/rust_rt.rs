// Copyright 2023 RISC Zero, Inc.
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

//! This module contains the components required to link a Rust binary.
//!
//! In particular:
//! * It defines an entrypoint ensuring initialization and finalization are done properly.
//! * It includes a panic handler.
//! * It includes an allocator.

use core::alloc::{GlobalAlloc, Layout};

use core::panic::PanicInfo;

use crate::syscall;

extern crate alloc;

/// panic! implementation for use in no_std guest programs.
#[cfg_attr(feature = "panic-handler", panic_handler)]
pub fn panic_fault(panic_info: &PanicInfo) -> ! {
    let msg = alloc::format!("{}", panic_info);
    let msg_bytes = msg.as_bytes();
    unsafe { syscall::sys_panic(msg.as_ptr(), msg.len()) }
}

#[cfg(feature = "entrypoint")]
mod entrypoint {
    // Entry point; sets up global pointer and stack pointer and passes
    // to __start.  TODO: when asm_const is stablized, use that here
    // instead of defining a symbol and dereferencing it.
    //
    // This version of _start is marked as "weak" so it only gets used if
    // start isn't already defined by e.g. risc0_zkvm::guest which needs
    // to initialize things like the journal.

    static STACK_TOP: u32 = crate::memory::STACK_TOP;

    core::arch::global_asm!(
        r#"
    .section .text._start
    .weak _start
    _start:
        .option push;
        .option norelax
        la gp, __global_pointer$
        .option pop
        la sp, {0}
        lw sp, 0(sp)
        call main
        li a1, 0
        call sys_halt
    "#,
        sym STACK_TOP
    );
}

struct BumpPointerAlloc;

unsafe impl GlobalAlloc for BumpPointerAlloc {
    unsafe fn alloc(&self, layout: Layout) -> *mut u8 {
        syscall::sys_alloc_aligned(layout.size(), layout.align())
    }

    unsafe fn dealloc(&self, _: *mut u8, _: Layout) {
        // this allocator never deallocates memory
    }
}

#[global_allocator]
static HEAP: BumpPointerAlloc = BumpPointerAlloc;
