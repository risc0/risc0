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

//! The RISC Zero ZKVM's guest-side RISC-V API.
//!
//! Code that is validated by the [RISC Zero zkVM](crate) is run inside the
//! guest. In the minimal case, an entrypoint (the guest's "`main`" function)
//! must be provided by using the [entry! macro](entry). In almost all
//! practical cases, the guest will want to read private input data using
//! [env::read] and commit public output data using [env::commit]; additional
//! I/O functionality is also available in [mod@env].
//!
//! For example[^starter-ex], the following guest code proves a number is
//! composite by multiplying two unsigned integers, and panicking if either is
//! `1` or if the multiplication overflows:
//! ```ignore
//! use risc0_zkvm::guest::env;
//!
//! risc0_zkvm::entry!(main);
//!
//! pub fn main() {
//!     // Load the first number from the host
//!     let a: u64 = env::read();
//!     // Load the second number from the host
//!     let b: u64 = env::read();
//!     // Verify that neither of them are 1 (i.e. nontrivial factors)
//!     if a == 1 || b == 1 {
//!         panic!("Trivial factors")
//!     }
//!     // Compute the product while being careful with integer overflow
//!     let product = a.checked_mul(b).expect("Integer overflow");
//!     env::commit(&product);
//! }
//! ```
//! Notice how the [entry! macro](entry) is used to indicate the
//! entrypoint, [env::read] is used to load the two factors, and [env::commit]
//! is used to make their composite product publically available.
//!
//! [^starter-ex]: The example is based on the [RISC Zero Rust Starter repository](https://github.com/risc0/risc0-rust-starter).

#![allow(unused)]
#![deny(missing_docs)]

mod alloc;
pub mod env;
pub mod sha;

use core::{arch::asm, mem, ptr};

use risc0_zkvm_platform::syscall::sys_panic;

pub use crate::entry;

#[cfg(target_os = "zkvm")]
core::arch::global_asm!(include_str!("memset.s"));
#[cfg(target_os = "zkvm")]
core::arch::global_asm!(include_str!("memcpy.s"));

fn _fault() -> ! {
    #[cfg(target_os = "zkvm")]
    unsafe {
        asm!("sw x0, 1(x0)")
    };
    unreachable!();
}

/// Aborts the guest with the given message.
pub fn abort(msg: &str) -> ! {
    // A compliant host should fault when it receives this syscall.
    unsafe { sys_panic(msg.as_ptr(), msg.len()) };

    // As a fallback for non-compliant hosts, issue an illegal instruction.
    _fault()
}

#[cfg(all(not(feature = "std"), target_os = "zkvm"))]
mod handlers {
    use core::{alloc::Layout, panic::PanicInfo};

    #[panic_handler]
    fn panic_fault(panic_info: &PanicInfo) -> ! {
        let msg = ::alloc::format!("{}", panic_info);
        crate::guest::abort(&msg)
    }

    #[alloc_error_handler]
    fn alloc_fault(_layout: Layout) -> ! {
        crate::guest::abort("Memory allocation failure")
    }
}

/// Used for defining a main entrypoint.
///
/// # Example
///
/// ```ignore
/// risc0_zkvm::entry!(main);
///
/// fn main() { }
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

#[cfg(target_os = "zkvm")]
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

#[cfg(target_os = "zkvm")]
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
"#
);

/// Require that accesses to behind the given pointer before the memory
/// barrier don't get optimized away or reordered to after the memory
/// barrier.
pub fn memory_barrier<T>(ptr: *const T) {
    // SAFETY: This passes a pointer in, but does nothing with it.
    unsafe { asm!("/* {0} */", in(reg) (ptr)) }
}
