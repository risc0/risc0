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

#![no_std]
#![cfg_attr(target_os = "zkvm", no_main)]

use core::{arch::asm, panic::PanicInfo};

use no_std_strings::{str256, str_format};

const HOST_ECALL_READ: u32 = 1;
const HOST_ECALL_WRITE: u32 = 2;
const WORD_SIZE: u32 = 4;
const MAX_IO_BYTES: u32 = 1024;
const USER_REGS_ADDR: u32 = 0xffff0080;
const REG_A0: usize = 10;
const REG_A1: usize = 11;

#[cfg(target_os = "zkvm")]
core::arch::global_asm!(include_str!("kernel.s"));

#[cfg(not(target_os = "zkvm"))]
fn main() {}

#[no_mangle]
unsafe extern "C" fn ecall_software_slow(fd: u32, mut buf: *const u8, mut len: u32) {
    // let msg = str_format!(str256, "ecall_software_slow({fd:#010x}, {buf:?}, {len})");
    // print(msg.to_str());

    let (mut nbytes, mut last_word) = (0u32, 0u32);

    let mut read_loop = || -> bool {
        while len > MAX_IO_BYTES {
            let rlen = host_ecall_read(fd, buf, MAX_IO_BYTES);
            let (a0, a1) = read_a0_a1();
            nbytes += a0;
            last_word = a1;
            if rlen < MAX_IO_BYTES {
                return false;
            }
            buf = buf.add(rlen as usize);
            len -= rlen;
        }
        true
    };

    if read_loop() && len > 0 {
        host_ecall_read(fd, buf, len);
        let (a0, a1) = read_a0_a1();
        nbytes += a0;
        last_word = a1;
    }

    set_ureg(REG_A0, nbytes);
    set_ureg(REG_A1, last_word);
}

unsafe fn host_ecall_read(fd: u32, buf: *const u8, len: u32) -> u32 {
    let rlen: u32;
    asm!("ecall",
        in("a7") HOST_ECALL_READ,
        inout("a0") fd => rlen,
        in("a1") buf,
        in("a2") len,
    );
    rlen
}

unsafe fn read_a0_a1() -> (u32, u32) {
    let mut buf = [0, 0];
    asm!("ecall",
        in("a7") HOST_ECALL_READ,
        in("a0") 0,
        in("a1") buf.as_mut_ptr(),
        in("a2") 2 * WORD_SIZE,
    );
    (buf[0], buf[1])
}

#[no_mangle]
unsafe extern "C" fn sys_log(msg_ptr: *const u8, msg_len: usize) {
    asm!("ecall",
        in("a7") HOST_ECALL_WRITE,
        in("a0") 0,
        in("a1") msg_ptr,
        in("a2") msg_len,
    );
}

unsafe fn set_ureg(idx: usize, word: u32) {
    let base = USER_REGS_ADDR as *mut u32;
    core::ptr::write_volatile(base.add(idx), word);
}

/// Print a message to the debug console.
fn print(msg: &str) {
    let msg = msg.as_bytes();
    unsafe {
        sys_log(msg.as_ptr(), msg.len());
    }
}

#[panic_handler]
fn panic(info: &PanicInfo) -> ! {
    let msg = str_format!(str256, "{}", info);
    print(msg.to_str());
    // unsafe { sys_panic(msg.as_ptr(), msg.len()) }
    unsafe { asm!("fence", options(noreturn)) }
}
