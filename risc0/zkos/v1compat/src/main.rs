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

#![cfg_attr(target_os = "zkvm", no_std)]
#![cfg_attr(target_os = "zkvm", no_main)]

#[cfg(not(target_os = "zkvm"))]
fn main() {}

// #[cfg(target_os = "zkvm")]
mod zkvm {
    use core::{
        arch::{asm, global_asm},
        cmp::min,
    };

    const HOST_ECALL_READ: u32 = 1;
    const HOST_ECALL_WRITE: u32 = 2;
    const HOST_ECALL_SHA: u32 = 4;
    const WORD_SIZE: u32 = 4;
    const DIGEST_WORDS: usize = 8;
    const BLOCK_WORDS: usize = 2 * DIGEST_WORDS;
    const MAX_IO_BYTES: u32 = 1024;
    const MAX_SHA_COUNT: u32 = 10;
    const USER_REGS_ADDR: u32 = 0xffff_0080;
    const REG_A0: usize = 10;
    const REG_A1: usize = 11;

    const SHA_K: [u32; 64] = [
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4,
        0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe,
        0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f,
        0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
        0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc,
        0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
        0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070, 0x19a4c116,
        0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7,
        0xc67178f2,
    ];

    global_asm!(include_str!("kernel.s"));

    #[no_mangle]
    unsafe extern "C" fn ecall_software(fd: u32, mut buf: *const u8, mut len: u32) -> ! {
        // use no_std_strings::{str256, str_format};
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

        asm!("mret", options(noreturn))
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

    unsafe fn set_ureg(idx: usize, word: u32) {
        let base = USER_REGS_ADDR as *mut u32;
        core::ptr::write_volatile(base.add(idx), word);
    }

    // fn print(msg: &str) {
    //     let msg = msg.as_bytes();
    //     unsafe {
    //         sys_log(msg.as_ptr(), msg.len());
    //     }
    // }

    // unsafe fn sys_log(msg_ptr: *const u8, msg_len: usize) {
    //     asm!("ecall",
    //         in("a7") HOST_ECALL_WRITE,
    //         in("a0") 0,
    //         in("a1") msg_ptr,
    //         in("a2") msg_len,
    //     );
    // }

    #[panic_handler]
    fn panic(info: &core::panic::PanicInfo) -> ! {
        use no_std_strings::{str256, str_format};
        let msg = str_format!(str256, "{}", info);
        unsafe { sys_panic(msg.as_ptr(), msg.len()) }
    }

    unsafe fn sys_panic(msg_ptr: *const u8, msg_len: usize) -> ! {
        asm!("ecall",
            in("a7") HOST_ECALL_WRITE,
            in("a0") 1,
            in("a1") msg_ptr,
            in("a2") msg_len,
        );
        asm!("fence", options(noreturn))
    }

    #[no_mangle]
    unsafe extern "C" fn ecall_sha(
        out_state: *const u32,
        mut in_state: *const u32,
        block1_ptr: *const u32,
        block2_ptr: *const u32,
        mut count: u32,
    ) -> ! {
        let mut data_ptr = if block2_ptr == block1_ptr.add(DIGEST_WORDS) {
            block1_ptr
        } else {
            static mut TEMP_BLOCK: [u32; BLOCK_WORDS] = [0u32; BLOCK_WORDS];
            let block1 = core::ptr::slice_from_raw_parts(block1_ptr, DIGEST_WORDS);
            let block2 = core::ptr::slice_from_raw_parts(block2_ptr, DIGEST_WORDS);
            TEMP_BLOCK[..DIGEST_WORDS].copy_from_slice(&*block1);
            TEMP_BLOCK[DIGEST_WORDS..].copy_from_slice(&*block2);
            TEMP_BLOCK.as_ptr() as *const u32
        };

        loop {
            let chunk = min(count, MAX_SHA_COUNT);
            asm!("ecall",
                in("a7") HOST_ECALL_SHA,
                in("a0") in_state,
                in("a1") out_state,
                in("a2") data_ptr,
                in("a3") chunk,
                in("a4") SHA_K.as_ptr(),
            );
            count -= chunk;
            if count == 0 {
                break;
            }
            data_ptr = data_ptr.add(chunk as usize * BLOCK_WORDS);
            in_state = out_state;
        }

        asm!("mret", options(noreturn))
    }
}
