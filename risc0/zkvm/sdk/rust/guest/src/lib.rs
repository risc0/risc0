// Copyright 2022 Risc0, Inc.
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

#![no_std]
#![allow(unused)]
#![deny(missing_docs)]
#![doc = include_str!("../README.md")]
#![cfg_attr(target_arch = "riscv32", feature(alloc_error_handler))]
#![cfg_attr(target_arch = "riscv32", feature(new_uninit))]

extern crate alloc as _alloc;

mod alloc;

/// Functions for interacting with the host environment.
pub mod env;

mod gpio;

/// Functions for computing SHA-256 hashes.
pub mod sha;

use core::{arch::asm, mem, panic::PanicInfo, ptr};
use gpio::{FaultDescriptor, GPIO_DESC_FAULT, GPIO_FAULT};

const REGION_SIZE_256KB: usize = 256 * 1024;
// const REGION_SIZE_512KB: usize = 0x0008_0000;
const REGION_SIZE_1MB: usize = 1024 * 1024;

const REGION_HEAP_START: usize = 0x0008_0000;
const REGION_HEAP_LEN: usize = REGION_SIZE_1MB + REGION_SIZE_256KB;
const REGION_HEAP_END: usize = REGION_HEAP_START + REGION_HEAP_LEN;

const REGION_SHA_START: usize = 0x0030_0000;
// const REGION_SHA_LEN: usize = REGION_SIZE_256KB;
// const REGION_SHA_END: usize = REGION_SHA_START + REGION_SHA_LEN;

const REGION_INPUT_START: usize = 0x0018_0000;
const REGION_INPUT_LEN: usize = REGION_SIZE_256KB;
// const REGION_INPUT_END: usize = REGION_INPUT_START + REGION_INPUT_LEN;

const REGION_OUTPUT_START: usize = 0x0034_0000;
const REGION_OUTPUT_LEN: usize = REGION_SIZE_256KB;

const REGION_COMMIT_START: usize = 0x0038_0000;
const REGION_COMMIT_LEN: usize = REGION_SIZE_256KB;

const WORD_SIZE: usize = mem::size_of::<u32>();

extern "C" {
    fn _fault() -> !;
}

#[cfg(target_arch = "riscv32")]
#[panic_handler]
unsafe fn panic_fault(panic_info: &PanicInfo<'static>) -> ! {
    let msg = _alloc::format!("{}\0", panic_info);

    let ptr = msg.as_ptr();
    crate::memory_barrier(ptr);
    GPIO_DESC_FAULT.write_volatile(FaultDescriptor {
        // addr: "panic\0".as_ptr() as usize,
        addr: ptr as usize,
    });
    // A compliant host should fault when it receives this descriptor.
    GPIO_FAULT.write_volatile(GPIO_DESC_FAULT);

    // As a fallback for uncompliant hosts, force an unaligned write, which causes a
    // fault within the Risc0 VM.
    _fault()
}

/// Used for defining a main entrypoint.
///
/// # Example
///
/// ```
/// risc0_zkvm_guest::entry!(main);
///
/// pub fn main() { }
/// ```
#[macro_export]
macro_rules! entry {
    ($path:path) => {
        #[no_mangle]
        fn __main() {
            // type check the given path
            let f: fn() = $path;
            f()
        }
    };
}

#[cfg(target_arch = "riscv32")]
#[no_mangle]
unsafe extern "C" fn __start(result: *mut usize) {
    extern "C" {
        static mut __bss_begin: u8;
        static mut __bss_size: usize;
    }
    ptr::write_bytes(&mut __bss_begin as *mut u8, 0, __bss_size);

    env::init();

    extern "Rust" {
        fn __main();
    }
    __main();

    env::finalize(result);
}

/// Align the given address `addr` upwards to alignment `align`.
///
/// Requires that `align` is a power of two.
pub(crate) const fn align_up(addr: usize, align: usize) -> usize {
    (addr + align - 1) & !(align - 1)
}

#[cfg(all(target_arch = "riscv32", not(feature = "bazel")))]
core::arch::global_asm!(
    r#"
.section .text._start;
.globl _start;
_start:
    .option push;
    .option norelax;
    la gp, __global_pointer$;
    .option pop;
    la sp, __stack_init$;
    la a0, __result
    jal ra, __start
    la x10, __result
    lw x1, 0(x10)
    lw x2, 4(x10)
    lw x3, 8(x10)
    lw x4, 12(x10)
    lw x5, 16(x10)
    lw x6, 20(x10)
    lw x7, 24(x10)
    lw x8, 28(x10)
    lw x9, 32(x10)
    ecall

.globl _fault;
_fault:
    sw x0, 1(x0)
"#
);

/// Require that accesses to behind the given pointer before the memory
/// barrier don't get optimized away or reordered to after the memory
/// barrier.
pub fn memory_barrier<T>(ptr: *const T) {
    // SAFETY: This passes a pointer in, but does nothing with it.
    unsafe { asm!("/* {0} */", in(reg) (ptr)) }
}
