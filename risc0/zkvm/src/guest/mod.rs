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

//! The RISC Zero zkVM's guest-side RISC-V API.
//!
//! Code that is validated by the [RISC Zero zkVM](crate) is run inside the
//! guest. In the minimal case, an entrypoint (the guest's "`main`" function)
//! must be provided by using the [entry! macro](entry). In almost all
//! practical cases, the guest will want to read private input data from the
//! host and write public data to the journal. In the simplest case, this can be
//! done with [env::read] and [env::commit], respectively; additional I/O
//! functionality is also available in [mod@env].
//!
//! ## Installation
//!
//! To build and run RISC Zero zkVM code, you will need to install the RISC Zero
//! toolchain, which can be done using the
//! [`cargo-risczero`](https://crates.io/crates/cargo-risczero) tool:
//!
//! ```sh
//! cargo install cargo-risczero
//! cargo risczero install
//! ```
//!
//! ## Example
//!
//! The following guest code[^starter-ex] proves a number is
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
//! If you encounter problems building zkVM guest code, you can see if we have a
//! known workaround for your issue by looking in our
//! [rust guest workarounds](https://github.com/risc0/risc0/issues?q=is%3Aissue+is%3Aopen+label%3A%22rust+guest+workarounds%22)
//! tag on GitHub.
//!
//! [^starter-ex]: The example is based on the [Factors example](https://github.com/risc0/risc0/tree/main/examples/factors).

#![deny(missing_docs)]

mod alloc;
pub mod env;
pub mod sha;

#[cfg(target_os = "zkvm")]
use core::arch::asm;

#[cfg(target_os = "zkvm")]
use getrandom::{register_custom_getrandom, Error};
use risc0_zkvm_platform::syscall::sys_panic;
#[cfg(target_os = "zkvm")]
use risc0_zkvm_platform::{syscall::sys_rand, WORD_SIZE};

pub use crate::entry;

/// This is a getrandom handler for the zkvm. It's intended to hook into a
/// getrandom crate or a depdent of the getrandom crate used by the guest code.
#[cfg(target_os = "zkvm")]
pub fn zkvm_getrandom(dest: &mut [u8]) -> Result<(), Error> {
    if dest.is_empty() {
        return Ok(());
    }

    let words = (dest.len() + WORD_SIZE - 1) / WORD_SIZE;
    let mut buf = ::alloc::vec![0u32; words];
    unsafe {
        sys_rand(buf.as_mut_ptr(), words);
    }
    dest.clone_from_slice(&bytemuck::cast_slice(buf.as_slice())[..dest.len()]);
    Ok(())
}

#[cfg(target_os = "zkvm")]
register_custom_getrandom!(zkvm_getrandom);

#[cfg(target_os = "zkvm")]
core::arch::global_asm!(include_str!("memset.s"));
#[cfg(target_os = "zkvm")]
core::arch::global_asm!(include_str!("memcpy.s"));

#[cfg(target_os = "zkvm")]
mod libm_extern;

/// Aborts the guest with the given message.
pub fn abort(msg: &str) -> ! {
    // SAFETY: A compliant host should fault when it receives this syscall.
    // sys_panic will issue an invalid instruction for non-compliant hosts.
    unsafe {
        sys_panic(msg.as_ptr(), msg.len());
    }
}

#[cfg(all(not(feature = "std"), target_os = "zkvm"))]
mod handlers {
    use core::panic::PanicInfo;

    #[panic_handler]
    fn panic_fault(panic_info: &PanicInfo) -> ! {
        let msg = ::alloc::format!("{}", panic_info);
        crate::guest::abort(&msg)
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
unsafe extern "C" fn __start() {
    env::init();

    {
        extern "C" {
            fn main();
        }
        main()
    }

    env::finalize(true, 0);
}

#[cfg(target_os = "zkvm")]
static STACK_TOP: u32 = risc0_zkvm_platform::memory::STACK_TOP;

// Entry point; sets up global pointer and stack pointer and passes
// to zkvm_start.  TODO: when asm_const is stablized, use that here
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
    jal ra, __start;
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
