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

#[cfg(target_os = "zkvm")]
use core::arch::asm;
use core::{cmp::min, ptr::null_mut};

use crate::WORD_SIZE;

pub mod ecall {
    pub const HALT: u32 = 0;
    pub const OUTPUT: u32 = 1;
    pub const SOFTWARE: u32 = 2;
    pub const SHA: u32 = 3;
}

pub mod halt {
    pub const TERMINATE: u32 = 0;
    pub const PAUSE: u32 = 1;
    pub const SPLIT: u32 = 2;
}

pub mod reg_abi {
    pub const REG_ZERO: usize = 0; // zero constant
    pub const REG_RA: usize = 1; // return address
    pub const REG_SP: usize = 2; // stack pointer
    pub const REG_GP: usize = 3; // global pointer
    pub const REG_TP: usize = 4; // thread pointer
    pub const REG_T0: usize = 5; // temporary
    pub const REG_T1: usize = 6; // temporary
    pub const REG_T2: usize = 7; // temporary
    pub const REG_S0: usize = 8; // saved register
    pub const REG_FP: usize = 8; // frame pointer
    pub const REG_S1: usize = 9; // saved register
    pub const REG_A0: usize = 10; // fn arg / return value
    pub const REG_A1: usize = 11; // fn arg / return value
    pub const REG_A2: usize = 12; // fn arg
    pub const REG_A3: usize = 13; // fn arg
    pub const REG_A4: usize = 14; // fn arg
    pub const REG_A5: usize = 15; // fn arg
    pub const REG_A6: usize = 16; // fn arg
    pub const REG_A7: usize = 17; // fn arg
    pub const REG_S2: usize = 18; // saved register
    pub const REG_S3: usize = 19; // saved register
    pub const REG_S4: usize = 20; // saved register
    pub const REG_S5: usize = 21; // saved register
    pub const REG_S6: usize = 22; // saved register
    pub const REG_S7: usize = 23; // saved register
    pub const REG_S8: usize = 24; // saved register
    pub const REG_S9: usize = 25; // saved register
    pub const REG_S10: usize = 26; // saved register
    pub const REG_S11: usize = 27; // saved register
    pub const REG_T3: usize = 28; // temporary
    pub const REG_T4: usize = 29; // temporary
    pub const REG_T5: usize = 30; // temporary
    pub const REG_T6: usize = 31; // temporary
    pub const REG_PC: usize = 32; // program counter
    pub const REG_MAX: usize = 33; // maximum number of registers
}

pub const DIGEST_WORDS: usize = 8;
pub const DIGEST_BYTES: usize = WORD_SIZE * DIGEST_WORDS;

/// Compute `ceil(a / b)` via truncated integer division.
#[allow(dead_code)]
const fn div_ceil(a: u32, b: u32) -> u32 {
    (a + b - 1) / b
}

/// Round `a` up to the nearest multipe of `b`.
#[allow(dead_code)]
const fn round_up(a: u32, b: u32) -> u32 {
    div_ceil(a, b) * b
}

// TODO: We can probably use ffi::CStr::from_bytes_with_nul once it's
// const-stablized instead of rolling our own structure:
// https://github.com/rust-lang/rust/issues/101719

/// A NUL-terminated name of a syscall with static lifetime.
#[derive(Clone, Copy, Debug)]
#[repr(transparent)]
pub struct SyscallName(*const u8);

/// Construct a SyscallName declaration at compile time.
///
/// ```
/// use risc0_zkvm_platform::declare_syscall;
///
/// declare_syscall!(SYS_MY_SYSTEM_CALL);
/// ```
#[macro_export]
macro_rules! declare_syscall {
    ($(#[$meta:meta])*
     $vis:vis $name:ident) => {
        $(#[$meta])*
        $vis const $name: $crate::syscall::SyscallName = unsafe {
            $crate::syscall::SyscallName::from_bytes_with_nul(concat!(
                module_path!(),
                "::",
                stringify!($name),
                "\0").as_ptr())
        };
    };
}

pub mod nr {
    declare_syscall!(pub SYS_CYCLE_COUNT);
    declare_syscall!(pub SYS_GETENV);
    declare_syscall!(pub SYS_LOG);
    declare_syscall!(pub SYS_PANIC);
    declare_syscall!(pub SYS_RANDOM);
    declare_syscall!(pub SYS_READ_AVAIL);
    declare_syscall!(pub SYS_READ);
    declare_syscall!(pub SYS_WRITE);
}

impl SyscallName {
    pub const unsafe fn from_bytes_with_nul(ptr: *const u8) -> Self {
        Self(ptr)
    }

    pub fn as_ptr(&self) -> *const u8 {
        self.0
    }

    pub fn as_str(&self) -> &str {
        core::str::from_utf8(unsafe { core::ffi::CStr::from_ptr(self.as_ptr().cast()).to_bytes() })
            .unwrap()
    }
}

/// Returned registers (a0, a1) from a syscall invocation.
#[repr(C)]
pub struct Return(pub u32, pub u32);

macro_rules! impl_syscall {
    ($func_name:ident
     // Ugh, unfortunately we can't make this a regular macro list since the asm macro
     // doesn't expand register names so in($register) doesn't work.
     $(, $a0:ident
       $(, $a1:ident
         $(, $a2: ident
           $(, $a3: ident
             $(, $a4: ident
             )?
           )?
         )?
       )?
     )?) => {
        /// Invoke a raw system call
        #[no_mangle]
        pub unsafe extern "C" fn $func_name(syscall: SyscallName,
                                 from_host: *mut u32,
                                 from_host_words: usize
                                 $(,$a0: u32
                                   $(,$a1: u32
                                     $(,$a2: u32
                                       $(,$a3: u32
                                         $(,$a4: u32
                                         )?
                                       )?
                                     )?
                                   )?
                                 )?
        ) -> Return {
            #[cfg(target_os = "zkvm")] {
                let a0: u32;
                let a1: u32;
                ::core::arch::asm!(
                    "ecall",
                    in("t0") $crate::syscall::ecall::SOFTWARE,
                    inout("a0") from_host => a0,
                    inout("a1") from_host_words => a1,
                    in("a2") syscall.as_ptr()
                        $(,in("a3") $a0
                          $(,in("a4") $a1
                            $(,in("a5") $a2
                              $(,in("a6") $a3
                                $(,in("a7") $a4
                                )?
                              )?
                            )?
                          )?
                        )?);
                Return(a0, a1)
            }
            #[cfg(not(target_os = "zkvm"))]
            unimplemented!()
        }
    }
}

impl_syscall!(syscall_0);
impl_syscall!(syscall_1, a3);
impl_syscall!(syscall_2, a3, a4);
impl_syscall!(syscall_3, a3, a4, a5);
impl_syscall!(syscall_4, a3, a4, a5, a6);
impl_syscall!(syscall_5, a3, a4, a5, a6, a7);

#[inline(always)]
#[no_mangle]
pub unsafe extern "C" fn sys_halt() -> ! {
    #[cfg(target_os = "zkvm")]
    {
        asm!(
            "ecall",
            in("t0") ecall::HALT,
            in("a0") halt::TERMINATE,
        );
        unreachable!();
    }
    #[cfg(not(target_os = "zkvm"))]
    unimplemented!()
}

#[inline(always)]
#[no_mangle]
pub unsafe extern "C" fn sys_pause() {
    #[cfg(target_os = "zkvm")]
    {
        asm!(
            "ecall",
            in("t0") ecall::HALT,
            in("a0") halt::PAUSE,
        );
    }
    #[cfg(not(target_os = "zkvm"))]
    unimplemented!()
}

#[inline(always)]
#[no_mangle]
pub unsafe extern "C" fn sys_output(output_id: u32, output_value: u32) {
    assert!(
        output_id < 9,
        "Invalid output ID. Expected: 0 - 8. Actual {output_id}"
    );
    #[cfg(target_os = "zkvm")]
    {
        asm!(
            "ecall",
            in("t0") ecall::OUTPUT,
            in("a0") output_id,
            in("a1") output_value,
        );
    }
    #[cfg(not(target_os = "zkvm"))]
    unimplemented!()
}

#[inline(always)]
#[no_mangle]
pub unsafe extern "C" fn sys_sha_compress(
    out_state: *mut [u32; DIGEST_WORDS],
    in_state: *const [u32; DIGEST_WORDS],
    block1_ptr: *const [u32; DIGEST_WORDS],
    block2_ptr: *const [u32; DIGEST_WORDS],
) {
    #[cfg(target_os = "zkvm")]
    {
        asm!(
            "ecall",
            in("t0") ecall::SHA,
            in("a0") out_state,
            in("a1") in_state,
            in("a2") block1_ptr,
            in("a3") block2_ptr,
            in("a4") 1,
        );
    }
    #[cfg(not(target_os = "zkvm"))]
    unimplemented!()
}

#[inline(always)]
pub unsafe fn sys_sha_buffer(
    out_state: *mut [u32; DIGEST_WORDS],
    in_state: *const [u32; DIGEST_WORDS],
    buf: *const u8,
    count: u32,
) {
    #[cfg(target_os = "zkvm")]
    {
        asm!(
            "ecall",
            in("t0") ecall::SHA,
            in("a0") out_state,
            in("a1") in_state,
            in("a2") buf,
            in("a3") buf.add(DIGEST_BYTES),
            in("a4") count,
        );
    }
    #[cfg(not(target_os = "zkvm"))]
    unimplemented!()
}

#[no_mangle]
pub unsafe extern "C" fn sys_rand(recv_buf: *mut u32, words: usize) {
    syscall_0(nr::SYS_RANDOM, recv_buf, words);
}

#[no_mangle]
pub unsafe extern "C" fn sys_panic(msg_ptr: *const u8, len: usize) -> ! {
    syscall_2(nr::SYS_PANIC, null_mut(), 0, msg_ptr as u32, len as u32);
    unreachable!()
}

#[no_mangle]
pub unsafe extern "C" fn sys_log(msg_ptr: *const u8, len: usize) {
    syscall_2(nr::SYS_LOG, null_mut(), 0, msg_ptr as u32, len as u32);
}

#[no_mangle]
pub unsafe extern "C" fn sys_cycle_count() -> usize {
    let Return(a0, _) = syscall_0(nr::SYS_CYCLE_COUNT, null_mut(), 0);
    a0 as usize
}

/// Reads the given number of bytes into the given buffer, posix-style.  Returns
/// the number of bytes actually read.  On end of file, returns 0.
///
/// Like POSIX read, this is not guaranteed to read all bytes
/// requested.  If we haven't reached EOF, it is however guaranteed to
/// read at least one byte.
///
/// Users should prefer a higher-level abstraction.
#[no_mangle]
pub unsafe extern "C" fn sys_read(fd: u32, recv_buf: *mut u8, nrequested: usize) -> usize {
    // The SYS_READ system call can do a given number of word-aligned reads
    // efficiently. The semantics of the system call are:
    //
    //   (nread, word) = syscall_2(nr::SYS_READ, outbuf,
    //                             num_words_in_outbuf, fd, nbytes);
    //
    // This reads exactly nbytes from the file descriptor, and fills the words
    // in outbuf, followed by up to 4 bytes returned in "word", and fills
    // the rest with NULs.  It returns the number of bytes read.
    //
    // sys_read exposes this as a byte-aligned read by:
    //   * Uses sys_read_avail to determine how many bytes actually need to be read
    //     to avoid having to null-pad the whole buffer if we're not reading very
    //     much
    //   * Copies any unaligned bytes at the start or end of the region.

    // Fills 0-3 bytes from a u32 into memory, returning the pointer afterwards.
    unsafe fn fill_from_word(mut ptr: *mut u8, mut word: u32, nfill: usize) -> *mut u8 {
        debug_assert!(nfill < 4, "nfill={nfill}");
        for _ in 0..nfill {
            *ptr = (word & 0xFF) as u8;
            word = word >> 8;
            ptr = ptr.add(1);
        }
        ptr
    }

    // Find out how many bytes to actually read, given how many we requested.
    let Return(navail, _) = syscall_1(nr::SYS_READ_AVAIL, null_mut(), 0, fd);
    let nread = min(nrequested, navail as usize);

    // Determine how many bytes at the beginning of the buffer we have
    // to read in order to become word-aligned.
    let ptr_offset = (recv_buf as usize) & (WORD_SIZE - 1);
    let unaligned_at_start = if ptr_offset == 0 {
        0
    } else {
        min(nread, WORD_SIZE - ptr_offset)
    };

    // Read unaligned bytes into "firstword".
    let Return(nread_first, firstword) =
        syscall_2(nr::SYS_READ, null_mut(), 0, fd, unaligned_at_start as u32);
    debug_assert_eq!(nread_first as usize, unaligned_at_start);

    // Align up to a word boundry to do the main copy.
    let main_ptr = fill_from_word(recv_buf, firstword, unaligned_at_start);
    if nread == unaligned_at_start {
        // We only read part of a word, and don't have to read any full words.
        return nread;
    }
    // Copy in all of the word-aligned data
    let main_requested = nread - unaligned_at_start;
    let main_words = main_requested / WORD_SIZE;
    let Return(nread_main, lastword) = syscall_2(
        nr::SYS_READ,
        main_ptr as *mut u32,
        main_words,
        fd,
        main_requested as u32,
    );
    debug_assert_eq!(nread_main as usize, main_requested);

    // Copy in individual bytes after the word-aligned section.
    let unaligned_at_end = (main_requested as usize) % WORD_SIZE;
    fill_from_word(
        main_ptr.add(main_words * WORD_SIZE),
        lastword,
        unaligned_at_end,
    );

    nread
}

/// Reads up to the given number of words into the buffer [recv_buf,
/// recv_buf + nwords).  Returns the number of bytes actually read.
/// sys_read_words is a more efficient interface than sys_read, but
/// varies from POSIX semantics.  Notably:
///
/// * The read length is specified in words, not bytes.  (The output
/// length is still returned in bytes)
///
/// * If not all data is available, sys_read_words will block on the
/// input stream instead of returning a short read.
///
/// * recv_buf must be word-aligned.
///
/// * All of the buffer is overwritten, even in the case of EOF
/// mid-way through.
///
/// # Safety
///
/// `recv_buf' must be a word-aligned pointer and point to a region of
/// `nwords' size.
pub unsafe extern "C" fn sys_read_words(fd: u32, recv_buf: *mut u32, nwords: usize) -> usize {
    let nbytes_requested = nwords * WORD_SIZE;
    let Return(nread, _) = syscall_2(
        nr::SYS_READ,
        recv_buf,
        nwords,
        fd,
        (nwords * WORD_SIZE) as u32,
    );
    assert!(nread as usize <= nbytes_requested);
    nread as usize
}

#[no_mangle]
pub unsafe extern "C" fn sys_write(fd: u32, write_buf: *const u8, nbytes: usize) {
    syscall_3(
        nr::SYS_WRITE,
        null_mut(),
        0,
        fd,
        write_buf as u32,
        nbytes as u32,
    );
}

/// Retrieves the value of an environment variable, and stores as much
/// of it as it can it in the memory at [out_words, out_words +
/// out_nwords).  Returns the length of the value.
///
/// This is normally called twice to read an environment variable:
/// Once to get the length of the value, and once to fill in allocated
/// memory.
#[no_mangle]
pub unsafe extern "C" fn sys_getenv(
    out_words: *mut u32,
    out_nwords: usize,
    varname: *const u8,
    varname_len: usize,
) -> usize {
    let Return(a0, _) = syscall_2(
        nr::SYS_GETENV,
        out_words,
        out_nwords,
        varname as u32,
        varname_len as u32,
    );
    if a0 == u32::MAX {
        usize::MAX
    } else {
        a0 as usize
    }
}

// Number of words remaining in the heap that haven't yet been allocated.
static mut HEAP_WORDS_REMAINING: usize = crate::memory::HEAP.len_words();

#[no_mangle]
pub unsafe extern "C" fn sys_alloc_words(nwords: usize) -> *mut u32 {
    // SAFETY: Single threaded, so nothing else can touch this while we're working.
    let heap_words_remaining: &mut usize = unsafe { &mut HEAP_WORDS_REMAINING };
    let new_words_remaining = heap_words_remaining
        .checked_sub(nwords)
        .expect("Out of memory!");
    // SAFETY: We've already checked to make sure we haven't
    // overflowed the heap, so the pointer arithmetic here should not
    // cause any undefined behavior.
    let ptr = unsafe { (crate::memory::HEAP.end() as *mut u32).sub(*heap_words_remaining) };
    *heap_words_remaining = new_words_remaining;
    ptr
}
