// Copyright 2026 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

#![cfg_attr(target_os = "zkvm", no_std)]
#![cfg_attr(target_os = "zkvm", no_main)]

#[cfg(not(target_os = "zkvm"))]
fn main() {}

#[cfg(any(target_os = "zkvm", rust_analyzer))]
#[allow(static_mut_refs)]
mod zkvm {
    use core::{
        arch::{asm, global_asm},
        cmp::min,
        fmt,
        mem::MaybeUninit,
    };
    use include_bytes_aligned::include_bytes_aligned;
    use risc0_zkvm_platform::syscall::{DIGEST_WORDS, Syscall};
    use sha2::digest::generic_array::GenericArray;

    const MACHINE_MODE: u32 = 1;
    const HOST_ECALL_READ: u32 = 1;
    const HOST_ECALL_WRITE: u32 = 2;
    const HOST_ECALL_SHA: u32 = 4;
    const HOST_ECALL_BIGINT: u32 = 5;
    const WORD_SIZE: u32 = 4;
    const BLOCK_WORDS: usize = 2 * DIGEST_WORDS;
    const MAX_IO_BYTES: u32 = 1024;
    const MAX_SHA_COUNT: u32 = 10;
    const USER_REGS_ADDR: u32 = 0xffff_0080;
    const USER_END_ADDR: usize = 0xc000_0000;
    const RV32IM_VERSION_ADDR: usize = 0xffff_0300;
    const REG_A0: usize = 10;
    const REG_A1: usize = 11;
    const REG_A4: usize = 14;

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

    const MODMUL_256: &[u8] = include_bytes_aligned!(4, "bigint_v1compat/modmul_256.blob");
    const MUL_256: &[u8] = include_bytes_aligned!(4, "bigint_v1compat/mul_256.blob");
    const BIGINT_OP_MULTIPLY: u32 = 0;
    const BIGINT_WIDTH_WORDS: usize = 256 / 8 / WORD_SIZE as usize;

    #[repr(C)]
    pub struct BigIntBlobHeader {
        pub nondet_program_size: u32,
        pub verify_program_size: u32,
        pub consts_size: u32,
        pub temp_size: u32,
    }

    fn assert_user_ptr<T>(ptr: *const T) {
        if ptr as usize >= USER_END_ADDR {
            illegal_instruction();
        }
    }

    fn assert_user_raw_slice(ptr: *const u8, nbytes: u32) {
        if nbytes > 0 && (ptr as usize).saturating_add(nbytes as usize) > USER_END_ADDR {
            illegal_instruction()
        }
    }

    #[unsafe(no_mangle)]
    unsafe extern "C" fn ecall_bigint_v1compat(
        result: *mut [u32; BIGINT_WIDTH_WORDS],
        op: u32,
        x: *const [u32; BIGINT_WIDTH_WORDS],
        y: *const [u32; BIGINT_WIDTH_WORDS],
        modulus: *const [u32; BIGINT_WIDTH_WORDS],
    ) {
        assert_user_ptr(result);
        assert_user_ptr(x);
        assert_user_ptr(y);
        assert_user_ptr(modulus);

        if op != BIGINT_OP_MULTIPLY {
            illegal_instruction();
        }

        unsafe {
            let mod_zero = (*modulus).iter().all(|e| *e == 0);
            let blob_ptr = if mod_zero {
                MUL_256.as_ptr()
            } else {
                MODMUL_256.as_ptr()
            };
            let header = blob_ptr as *const BigIntBlobHeader;
            let nondet_program_ptr = (header.add(1)) as *const u32;
            let verify_program_ptr = nondet_program_ptr.add((*header).nondet_program_size as usize);
            let consts_ptr = verify_program_ptr.add((*header).verify_program_size as usize);
            let temp_space = ((*header).temp_size as usize) << 2;

            if mod_zero {
                let mut temp_result = MaybeUninit::<[[u32; BIGINT_WIDTH_WORDS]; 2]>::uninit();

                asm!("sub sp, sp, {temp_space}", temp_space = in(reg) temp_space);
                host_ecall_bigint_3(
                    nondet_program_ptr,
                    verify_program_ptr,
                    consts_ptr,
                    blob_ptr,
                    x as *const u32,
                    y as *const u32,
                    temp_result.as_mut_ptr() as *const u32,
                );
                asm!("add sp, sp, {temp_space}", temp_space = in(reg) temp_space);

                let temp_result = temp_result.assume_init();

                // Check for overflow of the result
                if temp_result[1].iter().any(|e| *e != 0) {
                    illegal_instruction();
                }

                (*result).copy_from_slice(&temp_result[0]);
            } else {
                asm!("sub sp, sp, {temp_space}", temp_space = in(reg) temp_space);
                host_ecall_bigint_4(
                    nondet_program_ptr,
                    verify_program_ptr,
                    consts_ptr,
                    blob_ptr,
                    x as *const u32,
                    y as *const u32,
                    modulus as *const u32,
                    result as *const u32,
                );
                asm!("add sp, sp, {temp_space}", temp_space = in(reg) temp_space);
            }
        }
    }

    #[inline(always)]
    fn illegal_instruction() -> ! {
        unsafe { asm!("unimp", options(noreturn)) }
    }

    #[inline(always)]
    fn host_ecall_bigint_3(
        nondet_program_ptr: *const u32,
        verify_program_ptr: *const u32,
        consts_ptr: *const u32,
        blob_ptr: *const u8,
        a1: *const u32,
        a2: *const u32,
        a3: *const u32,
    ) {
        unsafe {
            asm!("ecall",
                in("a7") HOST_ECALL_BIGINT,
                in("t0") MACHINE_MODE,
                in("t1") nondet_program_ptr,
                in("t2") verify_program_ptr,
                in("t3") consts_ptr,
                in("a0") blob_ptr,
                in("a1") a1,
                in("a2") a2,
                in("a3") a3,
            )
        };
    }

    #[inline(always)]
    fn host_ecall_bigint_4(
        nondet_program_ptr: *const u32,
        verify_program_ptr: *const u32,
        consts_ptr: *const u32,
        blob_ptr: *const u8,
        a1: *const u32,
        a2: *const u32,
        a3: *const u32,
        a4: *const u32,
    ) {
        unsafe {
            asm!("ecall",
                in("a7") HOST_ECALL_BIGINT,
                in("t0") MACHINE_MODE,
                in("t1") nondet_program_ptr,
                in("t2") verify_program_ptr,
                in("t3") consts_ptr,
                in("a0") blob_ptr,
                in("a1") a1,
                in("a2") a2,
                in("a3") a3,
                in("a4") a4,
            )
        };
    }

    fn set_ureg(idx: usize, word: u32) {
        let base = USER_REGS_ADDR as *mut u32;
        unsafe { base.add(idx).write_volatile(word) };
    }

    #[allow(dead_code)]
    fn get_ureg(idx: usize) -> u32 {
        let base = USER_REGS_ADDR as *mut u32;
        unsafe { base.add(idx).read_volatile() }
    }

    #[allow(dead_code)]
    fn print(msg: &str) {
        let msg = msg.as_bytes();
        host_ecall_write(0, msg.as_ptr(), msg.len());
    }

    #[allow(dead_code)]
    struct LineBuf {
        buf: [u8; 256],
        len: usize,
    }

    #[allow(dead_code)]
    impl LineBuf {
        fn new() -> Self {
            Self {
                buf: [0; 256],
                len: 0,
            }
        }

        fn as_str(&self) -> &str {
            core::str::from_utf8(&self.buf[..self.len]).unwrap_or("<utf8-error>")
        }
    }

    impl fmt::Write for LineBuf {
        fn write_str(&mut self, s: &str) -> fmt::Result {
            let bytes = s.as_bytes();
            let space = self.buf.len().saturating_sub(self.len);
            let copy_len = bytes.len().min(space);
            self.buf[self.len..self.len + copy_len].copy_from_slice(&bytes[..copy_len]);
            self.len += copy_len;
            Ok(())
        }
    }

    #[macro_export]
    macro_rules! println {
        ($($arg:tt)*) => ({
            use core::fmt::Write;
            let mut buf = LineBuf::new();
            let _ = write!(&mut buf, $($arg)*);
            let _ = buf.write_str("\n");
            print(buf.as_str());
        })
    }

    #[panic_handler]
    fn panic(info: &core::panic::PanicInfo) -> ! {
        use no_std_strings::{str_format, str256};
        let msg = str_format!(str256, "{}", info);
        host_ecall_write(1, msg.as_ptr(), msg.len());
        illegal_instruction()
    }

    #[unsafe(no_mangle)]
    unsafe extern "C" fn ecall_sha(
        out_state: *const u32,
        in_state: *const u32,
        block1_ptr: *const u32,
        block2_ptr: *const u32,
        count: u32,
    ) {
        let rv32im_version = RV32IM_VERSION_ADDR as *mut u32;
        if unsafe { rv32im_version.read_volatile() } == 3 {
            sha_software(out_state, in_state, block1_ptr, block2_ptr, count);
        } else {
            sha_circuit(out_state, in_state, block1_ptr, block2_ptr, count);
        }
    }

    fn sha_circuit(
        out_state: *const u32,
        mut in_state: *const u32,
        block1_ptr: *const u32,
        block2_ptr: *const u32,
        mut count: u32,
    ) {
        let mut data_ptr = if block2_ptr == unsafe { block1_ptr.add(DIGEST_WORDS) } {
            block1_ptr
        } else {
            static mut TEMP_BLOCK: [u32; BLOCK_WORDS] = [0u32; BLOCK_WORDS];
            unsafe {
                let block1 = core::slice::from_raw_parts(block1_ptr, DIGEST_WORDS);
                let block2 = core::slice::from_raw_parts(block2_ptr, DIGEST_WORDS);
                TEMP_BLOCK[..DIGEST_WORDS].copy_from_slice(&*block1);
                TEMP_BLOCK[DIGEST_WORDS..].copy_from_slice(&*block2);
                TEMP_BLOCK.as_ptr() as *const u32
            }
        };

        loop {
            let chunk = min(count, MAX_SHA_COUNT);
            unsafe {
                asm!("ecall",
                    in("a7") HOST_ECALL_SHA,
                    in("a0") in_state,
                    in("a1") out_state,
                    in("a2") data_ptr,
                    in("a3") chunk,
                    in("a4") SHA_K.as_ptr(),
                )
            };
            count -= chunk;
            if count == 0 {
                break;
            }
            data_ptr = unsafe { data_ptr.add(chunk as usize * BLOCK_WORDS) };
            in_state = out_state;
        }
    }

    fn sha_software(
        out_state: *const u32,
        in_state: *const u32,
        block1_ptr: *const u32,
        block2_ptr: *const u32,
        count: u32,
    ) {
        let count = count as usize;
        // println!(
        //     "sha_software> out_state: {out_state:?}, in_state: {in_state:?}, block1_ptr: {block1_ptr:?}, block2_ptr: {block2_ptr:?}, count: {count}"
        // );

        let block_ptr = if block2_ptr == unsafe { block1_ptr.add(DIGEST_WORDS) } {
            // println!("buffer");
            block1_ptr
        } else {
            // println!("compress");

            static mut TEMP_BLOCK: [u32; BLOCK_WORDS] = [0u32; BLOCK_WORDS];
            unsafe {
                let block1 = core::slice::from_raw_parts(block1_ptr, DIGEST_WORDS);
                let block2 = core::slice::from_raw_parts(block2_ptr, DIGEST_WORDS);
                TEMP_BLOCK[..DIGEST_WORDS].copy_from_slice(block1);
                TEMP_BLOCK[DIGEST_WORDS..].copy_from_slice(block2);
                TEMP_BLOCK.as_ptr() as *const u32
            }
        };

        let total_words = count * BLOCK_WORDS;
        let blocks_u32 = core::ptr::slice_from_raw_parts(block_ptr, total_words);
        let blocks_u8 = unsafe {
            core::slice::from_raw_parts(blocks_u32 as *const u8, total_words * WORD_SIZE as usize)
        };
        let blocks = unsafe {
            core::slice::from_raw_parts(blocks_u8.as_ptr() as *const GenericArray<u8, _>, count)
        };

        let in_state = unsafe { core::slice::from_raw_parts(in_state, DIGEST_WORDS) };
        let state = unsafe { core::slice::from_raw_parts_mut(out_state as *mut u32, DIGEST_WORDS) };
        let state: &mut [u32; 8] = unsafe { &mut *(state.as_mut_ptr() as *mut [u32; 8]) };

        // Convert the state from big-endian to native byte order.
        for (dst, src) in state.iter_mut().zip(in_state.iter()) {
            *dst = u32::from_be(*src);
        }

        sha2::compress256(state, blocks);

        // Convert the state from big-endian to native byte order.
        for word in state.iter_mut() {
            *word = word.to_be();
        }
    }

    #[unsafe(no_mangle)]
    unsafe extern "C" fn ecall_software(nr: usize, fd: u32, buf: *mut u8, len: u32) {
        match Syscall::from(nr) {
            Syscall::Argc => sys_argc(fd),
            Syscall::Argv => sys_argv(fd, buf, len),
            Syscall::CycleCount => sys_cycle_count(fd),
            Syscall::Exit => sys_exit(fd),
            Syscall::Fork => sys_fork(fd),
            Syscall::Getenv => sys_getenv(fd, buf, len),
            Syscall::Keccak => sys_keccak(fd, buf, len),
            Syscall::Log => sys_log(fd),
            Syscall::Panic => sys_panic(fd),
            Syscall::Pipe => sys_pipe(fd, buf, len),
            Syscall::Random => sys_random(fd, buf, len),
            Syscall::Read => sys_read(fd, buf, len),
            Syscall::User => sys_user(fd, buf, len),
            Syscall::VerifyIntegrity => sys_verify_integrity(fd),
            Syscall::VerifyIntegrity2 => sys_verify_integrity2(fd),
            Syscall::Write => sys_write(fd),
            Syscall::Unknown(_) => unimplemented!(),
            Syscall::ProveZkr => todo!(),
        }
    }

    fn host_ecall_write(fd: u32, msg_ptr: *const u8, msg_len: usize) -> u32 {
        let rlen: u32;
        unsafe {
            asm!("ecall",
                in("a7") HOST_ECALL_WRITE,
                inout("a0") fd => rlen,
                in("a1") msg_ptr,
                in("a2") msg_len,
            )
        };
        rlen
    }

    fn host_ecall_read(fd: u32, ptr: *mut u8, nbytes: u32) -> u32 {
        let rlen: u32;
        unsafe {
            asm!("ecall",
                in("a7") HOST_ECALL_READ,
                inout("a0") fd => rlen,
                in("a1") ptr,
                in("a2") nbytes,
            )
        };
        rlen
    }

    fn host_ecall_read_trunc(fd: u32, ptr: *mut u8, nbytes: u32) -> u32 {
        let nbytes = min(nbytes, MAX_IO_BYTES);
        host_ecall_read(fd, ptr, nbytes)
    }

    fn host_syscall(fd: u32) -> u32 {
        host_ecall_read(fd, core::ptr::null_mut(), 0)
    }

    fn read_a0_a1() -> (u32, u32) {
        let mut buf = [0u32, 0u32];
        host_ecall_read(
            0,
            buf.as_mut_ptr() as *mut u8,
            core::mem::size_of_val(&buf) as u32,
        );
        (buf[0], buf[1])
    }

    fn host_syscall_a0_a1(fd: u32) -> (u32, u32) {
        host_syscall(fd);
        read_a0_a1()
    }

    // word-oriented
    // sys_keccak
    // sys_pipe

    // word-oriented, truncated
    // sys_argv
    // sys_getenv

    // word-oriented, chunked
    // sys_random

    // byte-oriented, chunked
    // sys_read

    fn sys_argc(fd: u32) {
        // a0: from_host -> argc
        // a1: from_host_words
        // a2: syscall_name

        let (a0, _a1) = host_syscall_a0_a1(fd);
        set_ureg(REG_A0, a0);
    }

    fn sys_argv(fd: u32, buf: *mut u8, nwords: u32) {
        // a0: from_host -> arg_len
        // a1: from_host_words
        // a2: syscall_name
        // a3: arg_index

        // Truncate the requested size since:
        // 1. The rv32im circuit can only transfer a max of 1KB.
        // 2. The host-side can only handle a single chunk.
        host_ecall_read_trunc(fd, buf, nwords * WORD_SIZE);
        let (a0, _a1) = read_a0_a1();
        set_ureg(REG_A0, a0);
    }

    fn sys_cycle_count(fd: u32) {
        // a0: from_host -> hi
        // a1: from_host_words -> lo
        // a2: syscall_name

        let (a0, a1) = host_syscall_a0_a1(fd);
        set_ureg(REG_A0, a0);
        set_ureg(REG_A1, a1);
    }

    fn sys_exit(fd: u32) {
        // a0: from_host -> ret
        // a1: from_host_words
        // a2: syscall_name

        let (a0, _a1) = host_syscall_a0_a1(fd);
        set_ureg(REG_A0, a0);
    }

    fn sys_fork(fd: u32) {
        // a0: from_host -> ret
        // a1: from_host_words
        // a2: syscall_name

        let (a0, _a1) = host_syscall_a0_a1(fd);
        set_ureg(REG_A0, a0);
    }

    fn sys_getenv(fd: u32, buf: *mut u8, nwords: u32) {
        // a0: from_host -> var_len
        // a1: from_host_words
        // a2: syscall_name
        // a3: varname
        // a4: varname_len

        // Truncate the requested size since:
        // 1. The rv32im circuit can only transfer a max of 1KB.
        // 2. The host-side can only handle a single chunk.
        host_ecall_read_trunc(fd, buf, nwords * WORD_SIZE);
        let (a0, _a1) = read_a0_a1();
        set_ureg(REG_A0, a0);
    }

    fn sys_keccak(fd: u32, buf: *mut u8, nwords: u32) {
        // a0: from_host -> ret
        // a1: from_host_words
        // a2: syscall_name
        // a3: keccak_mode
        // a4: in_state/claim_digest
        // a5: reserved/control_root

        // Truncate the requested size since:
        // 1. The rv32im circuit can only transfer a max of 1KB.
        // 2. The host-side can only handle a single chunk.
        host_ecall_read_trunc(fd, buf, nwords * WORD_SIZE);
        let (a0, _a1) = read_a0_a1();
        set_ureg(REG_A0, a0);
    }

    fn sys_log(fd: u32) {
        // a0: from_host
        // a1: from_host_words
        // a2: syscall_name
        // a3: msg_ptr
        // a4: msg_len

        host_syscall(fd);
    }

    fn sys_panic(fd: u32) {
        // a0: from_host
        // a1: from_host_words
        // a2: syscall_name
        // a3: msg_ptr
        // a4: msg_len

        host_syscall(fd);
    }

    fn sys_pipe(fd: u32, buf: *mut u8, nwords: u32) {
        // a0: from_host -> ret
        // a1: from_host_words
        // a2: syscall_name

        // Truncate the requested size since:
        // 1. The rv32im circuit can only transfer a max of 1KB.
        // 2. The host-side can only handle a single chunk.
        host_ecall_read_trunc(fd, buf, nwords * WORD_SIZE);
        let (a0, _a1) = read_a0_a1();
        set_ureg(REG_A0, a0);
    }

    fn sys_random(fd: u32, buf: *mut u8, nwords: u32) {
        // a0: from_host
        // a1: from_host_words
        // a2: syscall_name

        // The usermode `sys_rand` signature defines `recv_buf` as `*mut u32`.
        // It's assumed that `buf` will always be aligned.
        let nbytes = nwords * WORD_SIZE;
        assert_user_raw_slice(buf, nbytes);
        let slice = unsafe { core::slice::from_raw_parts_mut(buf, nbytes as usize) };
        for chunk in slice.chunks_mut(MAX_IO_BYTES as usize) {
            host_ecall_read(fd, chunk.as_mut_ptr(), chunk.len() as u32);
        }
    }

    fn sys_read(fd: u32, buf: *mut u8, nbytes: u32) {
        // a0: from_host -> nread_bytes
        // a1: from_host_words -> final_word
        // a2: syscall_name
        // a3: fd
        // a4: nbytes

        assert_user_raw_slice(buf, nbytes);
        let slice = unsafe { core::slice::from_raw_parts_mut(buf as *mut u8, nbytes as usize) };
        let user_nbytes = get_ureg(REG_A4);

        let mut total_bytes = 0u32;
        for chunk in slice.chunks_mut(MAX_IO_BYTES as usize) {
            let nbytes = chunk.len() as u32;
            set_ureg(REG_A4, nbytes);

            // Read protocol with host expects a "main" read of whole words, then sends any final
            // partial words in a seconds read for user (a0, a1).
            let nbytes_main = (nbytes / WORD_SIZE) * WORD_SIZE;
            host_ecall_read(fd, chunk.as_mut_ptr(), nbytes_main);

            let (nread_bytes, final_word) = read_a0_a1();
            if nread_bytes > nbytes {
                // Host returned an invalid number of bytes read.
                illegal_instruction()
            }

            // SAFETY: With the check that nread_bytes <= nbytes, which is the chunk size,
            // total_bytes can never exceed the size of the slice; this will not overflow.
            total_bytes += nread_bytes;

            // final_word handling
            // NOTE: If true, this implies that nbytes % WORD_SIZE != 0 in combination with the
            // length check above.
            if nread_bytes > nbytes_main {
                let final_bytes = final_word.to_le_bytes();
                let pos = nbytes_main as usize;
                let bytes_remain = (nread_bytes - nbytes_main) as usize;
                chunk[pos..pos + bytes_remain].copy_from_slice(&final_bytes[..bytes_remain]);
            }

            // short read
            if (nread_bytes as usize) < chunk.len() {
                break;
            }
        }

        set_ureg(REG_A0, total_bytes);
        set_ureg(REG_A4, user_nbytes);
    }

    fn sys_user(fd: u32, buf: *mut u8, nwords: u32) {
        // a0: from_host
        // a1: from_host_words
        // a2: syscall_name

        // Truncate the requested size since:
        // 1. The rv32im circuit can only transfer a max of 1KB.
        // 2. The host-side can only handle a single chunk.
        host_ecall_read_trunc(fd, buf, nwords * WORD_SIZE);
        let (a0, _a1) = read_a0_a1();
        set_ureg(REG_A0, a0);
    }

    fn sys_verify_integrity(fd: u32) {
        // a0: from_host -> ret
        // a1: from_host_words
        // a2: syscall_name
        // a3: buf_ptr
        // a4: buf_nbytes

        let (a0, _a1) = host_syscall_a0_a1(fd);
        set_ureg(REG_A0, a0);
    }

    fn sys_verify_integrity2(fd: u32) {
        // a0: from_host -> ret
        // a1: from_host_words
        // a2: syscall_name
        // a3: buf_ptr
        // a4: buf_nbytes

        let (a0, _a1) = host_syscall_a0_a1(fd);
        set_ureg(REG_A0, a0);
    }

    fn sys_write(fd: u32) {
        // a0: from_host
        // a1: from_host_words
        // a2: syscall_name
        // a3: fd
        // a4: buf_ptr
        // a5: buf_nbytes

        host_syscall(fd);
    }
}
