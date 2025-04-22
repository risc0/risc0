// Copyright 2024 RISC Zero, Inc.
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

//! The RISC Zero zkVM's guest-side RISC-V API.
//!
//! Code that is validated by the [RISC Zero zkVM](crate) is run inside the guest. In almost all
//! practical cases, the guest will want to read private input data from the host and write public
//! data to the journal. This can be done with [env::read] and [env::commit], respectively;
//! additional I/O functionality is also available in [mod@env].
//!
//! ## Installation
//!
//! To build and run RISC Zero zkVM code, you will need to install the RISC Zero
//! toolchain, which can be done using the rzup utility:
//!
//! ```sh
//! curl -L https://risczero.com/install | bash
//! rzup install
//! ```
//!
//! ## Example
//!
//! The following guest code[^starter-ex] proves a number is
//! composite by multiplying two unsigned integers, and panicking if either is
//! `1` or if the multiplication overflows:
//!
//! ```ignore
//! #![no_main]
//! #![no_std]
//!
//! use risc0_zkvm::guest::env;
//!
//! risc0_zkvm::guest::entry!(main);
//!
//! fn main() {
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
//!
//! Notice how [env::read] is used to load the two factors, and [env::commit] is used to make their
//! composite product publicly available. All input an output of your guest is private except for
//! what is written to the journal with [env::commit].
//!
//! By default, the guest only has the Rust `core` libraries and not `std`. A partial
//! implementation of the Rust standard libraries can be enabled with the `std` feature on this [crate].
//! When this feature is not enabled, the lines including `#![no_std]` and `#![no_main]` are
//! required, as well as the use of the [crate::guest::entry] macro. When `std` is enabled, these
//! three lines can be omitted and many features of `std` can be used.
//!
//! If you encounter problems building zkVM guest code, you can see if we have a
//! known workaround for your issue by looking in our
//! [rust guest workarounds](https://github.com/risc0/risc0/issues?q=is%3Aissue+is%3Aopen+label%3A%22rust+guest+workarounds%22)
//! tag on GitHub.
//!
//! [^starter-ex]: The example is based on the [Factors example](https://github.com/risc0/risc0/tree/main/examples/factors).

#![deny(missing_docs)]

pub mod env;

#[cfg(target_os = "zkvm")]
use core::arch::asm;

use risc0_zkvm_platform::syscall::sys_panic;

pub use risc0_zkp::core::hash::sha;

pub use crate::entry;

#[cfg(target_os = "zkvm")]
core::arch::global_asm!(include_str!("memset.s"));
#[cfg(target_os = "zkvm")]
#[no_mangle]
/// TODO
pub unsafe fn memcpy(mut dest: *mut u8, mut src: *const u8, mut n: usize) -> *mut u8 {
    use core::{mem::size_of, ptr};

    let orig_dest = dest;
    let word_size = size_of::<usize>();
    let align_mask = word_size - 1;

    // Align dest
    while (src as usize & align_mask) != 0 && n > 0 {
        ptr::write(dest, ptr::read(src));
        dest = dest.add(1);
        src = src.add(1);
        n -= 1;
    }

    if dest as usize % 4 == 0 {
        // Bulk copy using word-sized ops
        let mut d_word = dest as *mut usize;
        let mut s_word = src as *const usize;

        // Copy in larger unrolled chunks if available
        while n >= 4 * word_size {
            ptr::write(d_word, ptr::read(s_word));
            ptr::write(d_word.add(1), ptr::read(s_word.add(1)));
            ptr::write(d_word.add(2), ptr::read(s_word.add(2)));
            ptr::write(d_word.add(3), ptr::read(s_word.add(3)));

            d_word = d_word.add(4);
            s_word = s_word.add(4);
            n -= 4 * word_size;
        }
        dest = d_word as *mut u8;
        src = s_word as *const u8;
        if n & 8 == 8 {
            *d_word = *s_word;
            *(d_word.add(1)) = *(s_word.add(1));
            d_word = d_word.add(2);
            s_word = s_word.add(2);
            dest = d_word as *mut u8;
            src = s_word as *const u8;
        }
        if n & 4 == 4 {
            ptr::write(d_word, ptr::read(s_word));
            d_word = d_word.add(1);
            s_word = s_word.add(1);
            dest = d_word as *mut u8;
            src = s_word as *const u8;
        }
        if n & 2 == 2 {
            ptr::write(dest, ptr::read(src));
            dest = dest.add(1);
            src = src.add(1);
            ptr::write(dest, ptr::read(src));
            dest = dest.add(1);
            src = src.add(1);
        }
        if n & 1 == 1 {
            ptr::write(dest, ptr::read(src));
        }
        return orig_dest;
    }
    if (n >= 32) switch (dest as usize % 4) {
        case 1:
            w = *(u32 *)s;
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
            n -= 3;
            for (; n>=17; s+=16, d+=16, n-=16) {
                x = *(u32 *)(s+1);
                *(u32 *)(d+0) = (w LS 24) | (x RS 8);
                w = *(u32 *)(s+5);
                *(u32 *)(d+4) = (x LS 24) | (w RS 8);
                x = *(u32 *)(s+9);
                *(u32 *)(d+8) = (w LS 24) | (x RS 8);
                w = *(u32 *)(s+13);
                *(u32 *)(d+12) = (x LS 24) | (w RS 8);
            }
            break;
        case 2:
            w = *(u32 *)s;
            *d++ = *s++;
            *d++ = *s++;
            n -= 2;
            for (; n>=18; s+=16, d+=16, n-=16) {
                x = *(u32 *)(s+2);
                *(u32 *)(d+0) = (w LS 16) | (x RS 16);
                w = *(u32 *)(s+6);
                *(u32 *)(d+4) = (x LS 16) | (w RS 16);
                x = *(u32 *)(s+10);
                *(u32 *)(d+8) = (w LS 16) | (x RS 16);
                w = *(u32 *)(s+14);
                *(u32 *)(d+12) = (x LS 16) | (w RS 16);
            }
            break;
        case 3:
            w = *(u32 *)s;
            *d++ = *s++;
            n -= 1;
            for (; n>=19; s+=16, d+=16, n-=16) {
                x = *(u32 *)(s+3);
                *(u32 *)(d+0) = (w LS 8) | (x RS 24);
                w = *(u32 *)(s+7);
                *(u32 *)(d+4) = (x LS 8) | (w RS 24);
                x = *(u32 *)(s+11);
                *(u32 *)(d+8) = (w LS 8) | (x RS 24);
                w = *(u32 *)(s+15);
                *(u32 *)(d+12) = (x LS 8) | (w RS 24);
            }
            break;
        }

    orig_dest
}

fn _fault() -> ! {
    #[cfg(target_os = "zkvm")]
    unsafe {
        asm!("sw x0, 1(x0)")
    };
    unreachable!();
}

/// Aborts the guest with the given message.
pub fn abort(msg: &str) -> ! {
    // SAFETY: A compliant host should fault when it receives this syscall.
    // sys_panic will issue an invalid instruction for non-compliant hosts.
    unsafe {
        sys_panic(msg.as_ptr(), msg.len());
    }
}

/// Used for defining the guest's entrypoint and main function.
///
/// When `#![no_main]` is used, the programs entrypoint and main function is left undefined. The
/// `entry` macro is required to indicate the main function and link it to an entrypoint provided
/// by the RISC Zero SDK.
///
/// When `std` is enabled, the entrypoint will be linked automatically and this macro is not
/// required.
///
/// # Example
///
/// ```ignore
/// #![no_main]
/// #![no_std]
///
/// risc0_zkvm::entry!(main);
///
/// fn main() { }
/// ```
#[macro_export]
macro_rules! entry {
    ($path:path) => {
        // Type check the given path
        const ZKVM_ENTRY: fn() = $path;

        // Include generated main in a module so we don't conflict
        // with any other definitions of "main" in this file.
        mod zkvm_generated_main {
            #[no_mangle]
            fn main() {
                super::ZKVM_ENTRY()
            }
        }
    };
}

#[cfg(target_os = "zkvm")]
#[no_mangle]
unsafe extern "C" fn __start() -> ! {
    risc0_zkvm_platform::heap::init();
    env::init();

    {
        extern "C" {
            fn main();
        }
        main()
    }

    env::finalize(true, 0);
    unreachable!();
}

#[cfg(target_os = "zkvm")]
static STACK_TOP: u32 = risc0_zkvm_platform::memory::STACK_TOP;

// Entry point; sets up global pointer and stack pointer and passes
// to zkvm_start.  TODO: when asm_const is stabilized, use that here
// instead of defining a symbol and dereferencing it.
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
    la sp, {0}
    lw sp, 0(sp)
    call __start;
"#,
    sym STACK_TOP
);

/// Require that accesses to behind the given pointer before the memory
/// barrier don't get optimized away or reordered to after the memory
/// barrier.
#[allow(unused_variables)]
pub fn memory_barrier<T>(ptr: *const T) {
    // SAFETY: This passes a pointer in, but does nothing with it.
    #[cfg(target_os = "zkvm")]
    unsafe {
        asm!("/* {0} */", in(reg) (ptr))
    }
    #[cfg(not(target_os = "zkvm"))]
    core::sync::atomic::fence(core::sync::atomic::Ordering::SeqCst)
}

// When std is not linked, register a panic handler here so the user does not
// have to. If std is linked, it will define the panic handler instead. This
// panic handler must not be included.
#[cfg(all(target_os = "zkvm", not(feature = "std")))]
#[panic_handler]
fn panic_impl(panic_info: &core::panic::PanicInfo) -> ! {
    risc0_zkvm_platform::rust_rt::panic_fault(panic_info);
}
