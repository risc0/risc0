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

#![doc = include_str!("../README.md")]
#![allow(unused_variables)]
#![cfg_attr(all(not(feature = "std"), target_os = "zkvm"), no_std)]
#![feature(alloc_error_handler)]
#![feature(panic_info_message)]

pub mod memory;
#[macro_use]
pub mod syscall;

pub const WORD_SIZE: usize = core::mem::size_of::<u32>();
pub const PAGE_SIZE: usize = 1024;

/// Standard IO file descriptors for use with sys_read and sys_write.
pub mod fileno {
    pub const STDIN: u32 = 0;
    pub const STDOUT: u32 = 1;
    pub const STDERR: u32 = 2;
    pub const JOURNAL: u32 = 3;
}

#[cfg(all(not(feature = "std"), target_os = "zkvm"))]
mod handlers {
    use core::{alloc::Layout, panic::PanicInfo};

    fn abort(s: &str) -> ! {
        let bytes = s.as_bytes();
        unsafe { crate::syscall::sys_panic(bytes.as_ptr(), bytes.len()) }
    }

    #[panic_handler]
    fn panic_fault(panic_info: &PanicInfo) -> ! {
        if let Some(msg) = panic_info.message().and_then(|msg| msg.as_str()) {
            // Prefer to include the panic message if we don't have to
            // invoke allocation or formatting.
            abort(msg);
        } else {
            abort("Panic occured");
        }
    }

    #[alloc_error_handler]
    fn alloc_fault(_layout: Layout) -> ! {
        abort("Memory allocation failure")
    }
}
