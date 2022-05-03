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
mod mem_layout;
mod mutex;
pub mod sha;

use core::{mem, panic::PanicInfo, ptr};

use gpio::{FaultDescriptor, LogDescriptor, GPIO_DESC_FAULT, GPIO_DESC_LOG, GPIO_FAULT, GPIO_LOG};
// use mem_layout::{OutputZone, CommitZone, ShaDescZone};
use risc0_zkvm_core::{set_logger, Log};

pub const WORD_SIZE: usize = mem::size_of::<u32>();

extern "C" {
    fn _fault() -> !;
}

#[panic_handler]
unsafe fn panic_fault(panic_info: &PanicInfo<'static>) -> ! {
    let msg = _alloc::format!("{}\0", panic_info);

    GPIO_DESC_FAULT.write_volatile(FaultDescriptor {
        // addr: "panic\0".as_ptr() as usize,
        addr: msg.as_ptr() as usize,
    });
    // A compliant host should fault when it receives this descriptor.
    GPIO_FAULT.write_volatile(GPIO_DESC_FAULT.ptr());

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

struct Logger;

impl Log for Logger {
    fn log(&self, msg: &str) {
        let msg = _alloc::format!("{}\0", msg);
        GPIO_DESC_LOG.write_volatile(LogDescriptor {
            addr: msg.as_ptr() as usize,
        });
        GPIO_LOG.write_volatile(GPIO_DESC_LOG.ptr());
    }
}

static LOGGER: Logger = Logger;

#[no_mangle]
unsafe extern "C" fn __start(result: *mut usize) {
    extern "C" {
        static mut __bss_begin: u8;
        static mut __bss_size: usize;
    }
    ptr::write_bytes(&mut __bss_begin as *mut u8, 0, __bss_size);

    set_logger(&LOGGER);

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

pub fn padded_u32_from_u8(val: &[u8]) -> u32 {
    if val.len() == WORD_SIZE {
        u32::from_le_bytes(val.try_into().unwrap())
    } else {
        assert!(val.len() < WORD_SIZE);
        let mut padded: [u8; WORD_SIZE] = [0; WORD_SIZE];
        padded[..val.len()].clone_from_slice(val);
        u32::from_le_bytes(padded)
    }
}
