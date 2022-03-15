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
#![feature(alloc_error_handler)]
#![feature(new_uninit)]

extern crate alloc as _alloc;

mod alloc;
pub mod env;
mod gpio;
pub mod sha;

use core::{panic::PanicInfo, ptr};

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

extern "C" {
    fn _fault() -> !;
}

#[panic_handler]
unsafe fn panic_fault(panic_info: &PanicInfo<'static>) -> ! {
    let msg = _alloc::format!("{}\0", panic_info);

    GPIO_DESC_FAULT.write_volatile(FaultDescriptor {
        addr: msg.as_ptr() as usize,
    });
    // A compliant host should fault when it receives this descriptor.
    GPIO_FAULT.write_volatile(GPIO_DESC_FAULT);

    // As a fallback for uncompliant hosts, force an unaligned write, which causes a
    // fault within the Risc0 VM.
    _fault()
}

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
pub(crate) fn align_up(addr: usize, align: usize) -> usize {
    (addr + align - 1) & !(align - 1)
}
