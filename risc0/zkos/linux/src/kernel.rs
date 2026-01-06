// Copyright 2025 RISC Zero, Inc.
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

use no_std_strings::{str_format, str256};

use crate::constants::KERNEL_SPACE_START;
use crate::constants::*;
use crate::host_calls::{host_argc, host_log, host_terminate};
use crate::linux_abi::{handle_linux_syscall, start_linux_binary};
use risc0_zkos_common::softfloat::init_softfloat;

// Debug configuration - set to true to enable debug prints, false to disable
pub const DEBUG_ENABLED: bool = false;
pub const TRACE_ENABLED: bool = false;
// Debug print macro that avoids str_format evaluation when debug is disabled
#[macro_export]
macro_rules! debug_print {
    ($($arg:tt)*) => {
        if DEBUG_ENABLED {
            let msg = str_format!(str256, $($arg)*);
            print(&msg);
        }
    };
}

macro_rules! trace_print {
    ($($arg:tt)*) => {
        if TRACE_ENABLED {
            let msg = str_format!(str256, $($arg)*);
            print(&msg);
        }
    };
}

macro_rules! kprint {
    ($($arg:tt)*) => {
            let msg = str_format!(str256, $($arg)*);
            print(&msg);
    };
}

// Debug print macro for simple string literals (no formatting)
macro_rules! debug_print_simple {
    ($msg:literal) => {
        if DEBUG_ENABLED {
            print($msg);
        }
    };
}

#[macro_export]
macro_rules! kpanic {
    ($($arg:tt)*) => {
        debug_print!($($arg)*);
        host_terminate(1, 0);
        #[allow(unreachable_code)]
        loop {}
    };
}

#[cfg(target_arch = "riscv32")]
core::arch::global_asm!(include_str!("kernel.s"));

#[cfg(target_arch = "riscv32")]
#[panic_handler]
fn panic(_info: &core::panic::PanicInfo) -> ! {
    kpanic!("Panic: {}", _info);
    unsafe { core::arch::asm!("unimp", options(noreturn)) }
}

/// Validate a user pointer + length range. Returns Some((addr, end)) if valid.
fn validate_user_range(ptr: usize, len: usize) -> Option<(usize, usize)> {
    if len == 0 {
        return None;
    }
    if ptr >= KERNEL_SPACE_START as usize {
        return None;
    }
    let end = ptr.checked_add(len)?;
    if end > KERNEL_SPACE_START as usize {
        return None;
    }
    Some((ptr, end))
}

#[unsafe(no_mangle)]
unsafe extern "C" fn kstart() -> ! {
    debug_print_simple!("kstart");
    init_softfloat();
    // args - get actual argc and argv from host
    let argc = host_argc();
    debug_print!("argc is {argc}");
    // Check if we have any arguments
    if argc == 0 {
        kpanic!("No arguments provided");
    } else {
        start_linux_binary(argc)
    }
}

#[unsafe(no_mangle)]
unsafe extern "C" fn ecall_dispatch() -> ! {
    handle_linux_syscall()
}
pub fn print(msg: &str) {
    let msg = msg.as_bytes();
    host_log(msg.as_ptr(), msg.len());
}

/// Copy data from kernel memory to user memory
/// Returns the number of bytes copied, or 0 if the copy failed
/// This function checks that the destination is in user memory (below kernel space)
pub fn copy_to_user(dst: *mut u8, src: *const u8, len: usize) -> usize {
    if src.is_null() {
        debug_print!("copy_to_user: source pointer is null");
        return 0;
    }
    let dst_addr = dst as usize;
    if validate_user_range(dst_addr, len).is_none() {
        debug_print!(
            "copy_to_user: invalid destination range dst=0x{:08x} len={}",
            dst_addr,
            len
        );
        return 0;
    }
    unsafe {
        core::ptr::copy_nonoverlapping(src, dst, len);
    }
    len
}

/// Copy data from user memory into kernel memory.
/// Returns number of bytes copied or 0 on failure.
#[allow(dead_code)]
pub fn copy_from_user(dst: *mut u8, src: *const u8, len: usize) -> usize {
    if dst.is_null() {
        debug_print!("copy_from_user: destination pointer is null");
        return 0;
    }
    let src_addr = src as usize;
    if validate_user_range(src_addr, len).is_none() {
        debug_print!(
            "copy_from_user: invalid source range src=0x{:08x} len={}",
            src_addr,
            len
        );
        return 0;
    }
    unsafe {
        core::ptr::copy_nonoverlapping(src, dst, len);
    }
    len
}
