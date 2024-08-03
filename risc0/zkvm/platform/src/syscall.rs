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

#[cfg(target_os = "zkvm")]
use core::arch::asm;
use core::{cmp::min, ffi::CStr, ptr::null_mut, str::Utf8Error};

use crate::WORD_SIZE;

pub mod ecall {
    pub const HALT: u32 = 0;
    pub const INPUT: u32 = 1;
    pub const SOFTWARE: u32 = 2;
    pub const SHA: u32 = 3;
    pub const BIGINT: u32 = 4;
    pub const USER: u32 = 5;
    pub const MACHINE: u32 = 5;
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
    pub const REG_MAX: usize = 32; // maximum number of registers
}

pub const DIGEST_WORDS: usize = 8;
pub const DIGEST_BYTES: usize = WORD_SIZE * DIGEST_WORDS;

/// Number of words in each cycle received using the SOFTWARE ecall
pub const IO_CHUNK_WORDS: usize = 4;

// Limit syscall buffers so that the Executor doesn't get into an infinite
// split situation.
pub const MAX_BUF_BYTES: usize = 4 * 1024;
pub const MAX_BUF_WORDS: usize = MAX_BUF_BYTES / WORD_SIZE;
pub const MAX_SHA_COMPRESS_BLOCKS: usize = 1000;

pub mod bigint {
    pub const OP_MULTIPLY: u32 = 0;

    /// BigInt width, in bits, handled by the BigInt accelerator circuit.
    pub const WIDTH_BITS: usize = 256;

    /// BigInt width, in bytes, handled by the BigInt accelerator circuit.
    pub const WIDTH_BYTES: usize = WIDTH_BITS / 8;

    /// BigInt width, in words, handled by the BigInt accelerator circuit.
    pub const WIDTH_WORDS: usize = WIDTH_BYTES / crate::WORD_SIZE;
}

/// A UTF-8 NUL-terminated name of a syscall with static lifetime.
#[derive(Clone, Copy, Debug)]
#[repr(transparent)]
pub struct SyscallName(*const u8);

/// Construct a SyscallName declaration at compile time.
///
/// ```rust
/// use risc0_zkvm_platform::declare_syscall;
///
/// declare_syscall!(SYS_MY_SYSTEM_CALL);
/// ```
#[macro_export]
macro_rules! declare_syscall {
    (
        $(#[$meta:meta])*
        $vis:vis $name:ident
    ) => {
        // Go through `CStr` to avoid `unsafe` in the caller.
        $(#[$meta])*
        $vis const $name: $crate::syscall::SyscallName = match ::core::ffi::CStr::from_bytes_until_nul(
            concat!(module_path!(), "::", stringify!($name), "\0").as_bytes(),
        ) {
            Ok(c_str) => match $crate::syscall::SyscallName::from_c_str(c_str) {
                Ok(name) => name,
                Err(_) => unreachable!(),
            },
            Err(_) => unreachable!(),
        };
    };
}

pub mod nr {
    declare_syscall!(pub SYS_ARGC);
    declare_syscall!(pub SYS_ARGV);
    declare_syscall!(pub SYS_CYCLE_COUNT);
    declare_syscall!(pub SYS_EXIT);
    declare_syscall!(pub SYS_FORK);
    declare_syscall!(pub SYS_GETENV);
    declare_syscall!(pub SYS_LOG);
    declare_syscall!(pub SYS_PANIC);
    declare_syscall!(pub SYS_PIPE);
    declare_syscall!(pub SYS_RANDOM);
    declare_syscall!(pub SYS_READ);
    declare_syscall!(pub SYS_VERIFY_INTEGRITY);
    declare_syscall!(pub SYS_WRITE);
    declare_syscall!(pub SYS_EXECUTE_ZKR);
}

impl SyscallName {
    /// Converts a static C string to a system call name, if it is UTF-8.
    #[inline]
    pub const fn from_c_str(c_str: &'static CStr) -> Result<Self, Utf8Error> {
        match c_str.to_str() {
            Ok(_) => Ok(unsafe { Self::from_bytes_with_nul(c_str.as_ptr().cast()) }),
            Err(error) => Err(error),
        }
    }

    /// Converts a raw UTF-8 C string pointer to a system call name.
    ///
    /// # Safety
    ///
    /// The pointer must reference a static null-terminated UTF-8 string.
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

impl AsRef<str> for SyscallName {
    fn as_ref(&self) -> &str {
        self.as_str()
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
        ///
        /// # Safety
        ///
        /// `from_host` must be aligned and dereferenceable.
        #[cfg_attr(feature = "export-syscalls", no_mangle)]
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
                    inlateout("a0") from_host => a0,
                    inlateout("a1") from_host_words => a1,
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

fn ecall_1(t0: u32, a0: u32, a1: u32) {
    #[cfg(target_os = "zkvm")]
    unsafe {
        asm!(
            "ecall",
            in("t0") t0,
            in("a0") a0,
            in("a1") a1,
        )
    };
    #[cfg(not(target_os = "zkvm"))]
    {
        core::hint::black_box((t0, a0, a1));
        unimplemented!()
    }
}

fn ecall_4(t0: u32, a0: u32, a1: u32, a2: u32, a3: u32, a4: u32) {
    #[cfg(target_os = "zkvm")]
    unsafe {
        asm!(
            "ecall",
            in("t0") t0,
            in("a0") a0,
            in("a1") a1,
            in("a2") a2,
            in("a3") a3,
            in("a4") a4,
        )
    };
    #[cfg(not(target_os = "zkvm"))]
    {
        core::hint::black_box((t0, a0, a1, a2, a3, a4));
        unimplemented!()
    }
}

/// # Safety
///
/// `out_state` must be aligned and dereferenceable.
// [inline(never)] is added to mitigate potentially leaking information about program execution
// through the final value of the program counter (pc) on halt where there is more than one
// location in the program where `sys_halt` is called. As long as the halt instruction only exists
// in one place within the program, the pc will always be the same invariant with input.
#[inline(never)]
#[cfg_attr(feature = "export-syscalls", no_mangle)]
pub extern "C" fn sys_halt(user_exit: u8, out_state: *const [u32; DIGEST_WORDS]) -> ! {
    ecall_1(
        ecall::HALT,
        halt::TERMINATE | ((user_exit as u32) << 8),
        out_state as u32,
    );
    unreachable!();
}

/// # Safety
///
/// `out_state` must be aligned and dereferenceable.
// [inline(never)] is added to mitigate potentially leaking information about program execution
// through the final value of the program counter (pc) on pause where there is more than one
// location in the program where `sys_pause` is called. As long as the pause instruction only exists
// in one place within the program, the pc will always be the same invariant with input.
#[inline(never)]
#[cfg_attr(feature = "export-syscalls", no_mangle)]
pub unsafe extern "C" fn sys_pause(user_exit: u8, out_state: *const [u32; DIGEST_WORDS]) {
    ecall_1(
        ecall::HALT,
        halt::PAUSE | ((user_exit as u32) << 8),
        out_state as u32,
    );
}

#[cfg_attr(feature = "export-syscalls", no_mangle)]
pub extern "C" fn sys_input(index: u32) -> u32 {
    let t0 = ecall::INPUT;
    let index = index & 0x07;
    #[cfg(target_os = "zkvm")]
    unsafe {
        let a0: u32;
        asm!(
            "ecall",
            in("t0") t0,
            inlateout("a0") index => a0,
        );
        a0
    }
    #[cfg(not(target_os = "zkvm"))]
    {
        core::hint::black_box((t0, index));
        unimplemented!()
    }
}

/// # Safety
///
/// `out_state`, `in_state`, `block1_ptr`, and `block2_ptr` must be aligned and
/// dereferenceable.
#[inline(always)]
#[cfg_attr(feature = "export-syscalls", no_mangle)]
pub unsafe extern "C" fn sys_sha_compress(
    out_state: *mut [u32; DIGEST_WORDS],
    in_state: *const [u32; DIGEST_WORDS],
    block1_ptr: *const [u32; DIGEST_WORDS],
    block2_ptr: *const [u32; DIGEST_WORDS],
) {
    ecall_4(
        ecall::SHA,
        out_state as u32,
        in_state as u32,
        block1_ptr as u32,
        block2_ptr as u32,
        1,
    );
}

/// # Safety
///
/// `out_state`, `in_state`, and `buf` must be aligned and dereferenceable.
#[inline(always)]
#[cfg_attr(feature = "export-syscalls", no_mangle)]
pub unsafe extern "C" fn sys_sha_buffer(
    out_state: *mut [u32; DIGEST_WORDS],
    in_state: *const [u32; DIGEST_WORDS],
    buf: *const u8,
    count: u32,
) {
    let mut ptr = buf;
    let mut count_remain = count;
    let mut in_state = in_state;
    while count_remain > 0 {
        let count = min(count_remain, MAX_SHA_COMPRESS_BLOCKS as u32);
        ecall_4(
            ecall::SHA,
            out_state as u32,
            in_state as u32,
            ptr as u32,
            ptr.add(DIGEST_BYTES) as u32,
            count,
        );
        count_remain -= count;
        ptr = ptr.add(2 * DIGEST_BYTES * count as usize);
        in_state = out_state;
    }
}

/// # Safety
///
/// `result`, `x`, `y`, and `modulus` must be aligned and dereferenceable.
#[inline(always)]
#[cfg_attr(feature = "export-syscalls", no_mangle)]
pub unsafe extern "C" fn sys_bigint(
    result: *mut [u32; bigint::WIDTH_WORDS],
    op: u32,
    x: *const [u32; bigint::WIDTH_WORDS],
    y: *const [u32; bigint::WIDTH_WORDS],
    modulus: *const [u32; bigint::WIDTH_WORDS],
) {
    ecall_4(
        ecall::BIGINT,
        result as u32,
        op,
        x as u32,
        y as u32,
        modulus as u32,
    );
}

/// # Safety
///
/// `recv_buf` must be aligned and dereferenceable.
#[cfg_attr(feature = "export-syscalls", no_mangle)]
pub unsafe extern "C" fn sys_rand(recv_buf: *mut u32, words: usize) {
    syscall_0(nr::SYS_RANDOM, recv_buf, words);
}

/// # Safety
///
/// `msg_ptr` must be aligned and dereferenceable.
#[cfg_attr(feature = "export-syscalls", no_mangle)]
pub unsafe extern "C" fn sys_panic(msg_ptr: *const u8, len: usize) -> ! {
    syscall_2(nr::SYS_PANIC, null_mut(), 0, msg_ptr as u32, len as u32);

    // As a fallback for non-compliant hosts, issue an illegal instruction.
    #[cfg(target_os = "zkvm")]
    asm!("sw x0, 1(x0)");
    unreachable!()
}

/// # Safety
///
/// `msg_ptr` must be aligned and dereferenceable.
#[cfg_attr(feature = "export-syscalls", no_mangle)]
pub unsafe extern "C" fn sys_log(msg_ptr: *const u8, len: usize) {
    syscall_2(nr::SYS_LOG, null_mut(), 0, msg_ptr as u32, len as u32);
}

#[cfg_attr(feature = "export-syscalls", no_mangle)]
pub extern "C" fn sys_cycle_count() -> u64 {
    let Return(hi, lo) = unsafe { syscall_0(nr::SYS_CYCLE_COUNT, null_mut(), 0) };
    ((hi as u64) << 32) + lo as u64
}

/// Reads the given number of bytes into the given buffer, posix-style.  Returns
/// the number of bytes actually read.  On end of file, returns 0.
///
/// Like POSIX read, this is not guaranteed to read all bytes
/// requested.  If we haven't reached EOF, it is however guaranteed to
/// read at least one byte.
///
/// Users should prefer a higher-level abstraction.
///
/// # Safety
///
/// `recv_ptr` must be aligned and dereferenceable.
#[cfg_attr(feature = "export-syscalls", no_mangle)]
pub unsafe extern "C" fn sys_read(fd: u32, recv_ptr: *mut u8, nread: usize) -> usize {
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
    //   * Copies any unaligned bytes at the start or end of the region.

    // Fills 0-3 bytes from a u32 into memory, returning the pointer afterwards.
    unsafe fn fill_from_word(mut ptr: *mut u8, mut word: u32, nfill: usize) -> *mut u8 {
        debug_assert!(nfill < 4, "nfill={nfill}");
        for _ in 0..nfill {
            *ptr = (word & 0xFF) as u8;
            word >>= 8;
            ptr = ptr.add(1);
        }
        ptr
    }

    // Determine how many bytes at the beginning of the buffer we have
    // to read in order to become word-aligned.
    let ptr_offset = (recv_ptr as usize) & (WORD_SIZE - 1);
    let (main_ptr, main_requested, nread_first) = if ptr_offset == 0 {
        (recv_ptr, nread, 0)
    } else {
        let unaligned_at_start = min(nread, WORD_SIZE - ptr_offset);
        // Read unaligned bytes into "firstword".
        let Return(nread_first, firstword) =
            syscall_2(nr::SYS_READ, null_mut(), 0, fd, unaligned_at_start as u32);
        debug_assert_eq!(nread_first as usize, unaligned_at_start);

        // Align up to a word boundary to do the main copy.
        let main_ptr = fill_from_word(recv_ptr, firstword, unaligned_at_start);
        if nread == unaligned_at_start {
            // We only read part of a word, and don't have to read any full words.
            return nread;
        }
        (main_ptr, nread - unaligned_at_start, nread_first as usize)
    };

    // Copy in all of the word-aligned data
    let main_words = main_requested / WORD_SIZE;
    let (nread_main, lastword) =
        sys_read_internal(fd, main_ptr as *mut u32, main_words, main_requested);
    debug_assert!(nread_main <= main_requested);
    let read_words = nread_main / WORD_SIZE;

    // Copy in individual bytes after the word-aligned section.
    let unaligned_at_end = main_requested % WORD_SIZE;

    // The last 0-3 bytes are returned in lastword. Write those to complete the _requested_ read amount.
    fill_from_word(
        main_ptr.add(main_words * WORD_SIZE),
        lastword,
        unaligned_at_end,
    );

    nread_first + nread_main
}

/// Reads up to the given number of words into the buffer [recv_buf,
/// recv_buf + nwords).  Returns the number of bytes actually read.
/// sys_read_words is a more efficient interface than sys_read, but
/// varies from POSIX semantics.  Notably:
///
/// * The read length is specified in words, not bytes.  (The output
/// length is still returned in bytes)
///
/// * If not all data is available, `sys_read_words` will return a short read.
///
/// * recv_buf must be word-aligned.
///
/// * Return a short read in the case of EOF mid-way through.
///
/// # Safety
///
/// `recv_ptr' must be a word-aligned pointer and point to a region of
/// `nwords' size.
#[cfg_attr(feature = "export-syscalls", no_mangle)]
pub unsafe extern "C" fn sys_read_words(fd: u32, recv_ptr: *mut u32, nwords: usize) -> usize {
    sys_read_internal(fd, recv_ptr, nwords, nwords * WORD_SIZE).0
}

fn sys_read_internal(fd: u32, recv_ptr: *mut u32, nwords: usize, nbytes: usize) -> (usize, u32) {
    let mut nwords_remain = nwords;
    let mut nbytes_remain = nbytes;
    let mut nread_total_bytes = 0;
    let mut recv_ptr = recv_ptr;
    let mut final_word = 0;
    while nbytes_remain > 0 {
        debug_assert!(
            final_word == 0,
            "host returned non-zero final word on a fully aligned read"
        );
        let chunk_len = min(nbytes_remain, MAX_BUF_BYTES) as u32;
        let Return(nread_bytes, last_word) = unsafe {
            syscall_2(
                nr::SYS_READ,
                recv_ptr,
                min(nwords_remain, MAX_BUF_WORDS),
                fd,
                chunk_len,
            )
        };
        let nread_bytes = nread_bytes as usize;
        let nread_words = nread_bytes / WORD_SIZE;
        recv_ptr = unsafe { recv_ptr.add(nread_words) };
        final_word = last_word;
        nwords_remain -= nread_words;
        nread_total_bytes += nread_bytes;
        nbytes_remain -= nread_bytes;
        if nread_bytes < chunk_len as usize {
            // We've reached EOF, and the host has returned a partial word.
            break;
        }
    }
    (nread_total_bytes, final_word)
}

/// # Safety
///
/// `write_ptr` must be aligned and dereferenceable.
#[cfg_attr(feature = "export-syscalls", no_mangle)]
pub unsafe extern "C" fn sys_write(fd: u32, write_ptr: *const u8, nbytes: usize) {
    let mut nbytes_remain = nbytes;
    let mut write_ptr = write_ptr;
    while nbytes_remain > 0 {
        let nbytes = min(nbytes_remain, MAX_BUF_BYTES);
        syscall_3(
            nr::SYS_WRITE,
            null_mut(),
            0,
            fd,
            write_ptr as u32,
            nbytes as u32,
        );
        write_ptr = write_ptr.add(nbytes);
        nbytes_remain -= nbytes;
    }
}

/// Retrieves the value of an environment variable, and stores as much
/// of it as it can it in the memory at [out_words, out_words +
/// out_nwords).
///
/// Returns the length of the value, in bytes, or usize::MAX if the variable is
/// not set.
///
/// This is normally called twice to read an environment variable:
/// Once to get the length of the value, and once to fill in allocated
/// memory.
///
/// NOTE: Repeated calls to sys_getenv are not guaranteed to result in the same
/// data being returned. Returned data is entirely in the control of the host.
///
/// # Safety
///
/// `out_words` and `varname` must be aligned and dereferenceable.
#[cfg_attr(feature = "export-syscalls", no_mangle)]
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

/// Retrieves the count of arguments provided to program execution.
///
/// NOTE: Repeated calls to sys_argc are not guaranteed to result in the same
/// data being returned. Returned data is entirely in the control of the host.
#[cfg_attr(feature = "export-syscalls", no_mangle)]
pub extern "C" fn sys_argc() -> usize {
    let Return(a0, _) = unsafe { syscall_0(nr::SYS_ARGC, null_mut(), 0) };
    a0 as usize
}

/// Retrieves the argument with arg_index, and stores as much
/// of it as it can it in the memory at [out_words, out_words +
/// out_nwords).
///
/// Returns the length, in bytes, of the argument string. If the requested
/// argument index does not exist (i.e. `arg_index` >= argc) then this syscall
/// will not return.
///
/// This is normally called twice to read an argument: Once to get the length of
/// the value, and once to fill in allocated memory.
///
/// NOTE: Repeated calls to sys_argv are not guaranteed to result in the same
/// data being returned. Returned data is entirely in the control of the host.
///
/// # Safety
///
/// `out_words` must be aligned and dereferenceable.
#[cfg_attr(feature = "export-syscalls", no_mangle)]
pub unsafe extern "C" fn sys_argv(
    out_words: *mut u32,
    out_nwords: usize,
    arg_index: usize,
) -> usize {
    let Return(a0, _) = syscall_1(nr::SYS_ARGV, out_words, out_nwords, arg_index as u32);
    a0 as usize
}

#[cfg_attr(feature = "export-syscalls", no_mangle)]
pub extern "C" fn sys_alloc_words(nwords: usize) -> *mut u32 {
    unsafe { sys_alloc_aligned(WORD_SIZE * nwords, WORD_SIZE) as *mut u32 }
}

/// # Safety
///
/// This function should be safe to call, but clippy complains if it is not marked as `unsafe`.
#[cfg(feature = "export-syscalls")]
#[no_mangle]
pub unsafe extern "C" fn sys_alloc_aligned(bytes: usize, align: usize) -> *mut u8 {
    #[cfg(target_os = "zkvm")]
    extern "C" {
        // This symbol is defined by the loader and marks the end
        // of all elf sections, so this is where we start our
        // heap.
        //
        // This is generated automatically by the linker; see
        // https://lld.llvm.org/ELF/linker_script.html#sections-command
        static _end: u8;
    }

    // Pointer to next heap address to use, or 0 if the heap has not yet been
    // initialized.
    static mut HEAP_POS: usize = 0;

    // SAFETY: Single threaded, so nothing else can touch this while we're working.
    let mut heap_pos = unsafe { HEAP_POS };

    #[cfg(target_os = "zkvm")]
    if heap_pos == 0 {
        heap_pos = unsafe { (&_end) as *const u8 as usize };
    }

    // Honor requested alignment if larger than word size.
    // Note: align is typically a power of two.
    let align = usize::max(align, WORD_SIZE);

    let offset = heap_pos & (align - 1);
    if offset != 0 {
        heap_pos += align - offset;
    }

    let ptr = heap_pos as *mut u8;
    heap_pos += bytes;

    // Check to make sure heap doesn't collide with SYSTEM memory.
    if crate::memory::SYSTEM.start() < heap_pos {
        const MSG: &[u8] = "Out of memory!".as_bytes();
        unsafe { sys_panic(MSG.as_ptr(), MSG.len()) };
    }

    unsafe { HEAP_POS = heap_pos };
    ptr
}

/// Send a ReceiptClaim digest to the host to request verification.
///
/// A cooperative prover will only return if there is a verifying proof
/// associated with that claim digest, and will always return a result code
/// of 0 to register a0. The caller must encode the claim_digest into a
/// public assumptions list for inclusion in the guest output.
///
/// # Safety
///
/// `claim_digest` must be aligned and dereferenceable.
/// `control_root` must be aligned and dereferenceable.
#[cfg(feature = "export-syscalls")]
#[no_mangle]
pub unsafe extern "C" fn sys_verify_integrity(
    claim_digest: *const [u32; DIGEST_WORDS],
    control_root: *const [u32; DIGEST_WORDS],
) {
    let mut to_host = [0u32; DIGEST_WORDS * 2];
    to_host[..DIGEST_WORDS].copy_from_slice(claim_digest.as_ref().unwrap_unchecked());
    to_host[DIGEST_WORDS..].copy_from_slice(control_root.as_ref().unwrap_unchecked());

    let Return(a0, _) = unsafe {
        // Send the claim_digest to the host via software ecall.
        syscall_2(
            nr::SYS_VERIFY_INTEGRITY,
            null_mut(),
            0,
            to_host.as_ptr() as u32,
            (DIGEST_BYTES * 2) as u32,
        )
    };

    // Check to ensure the host indicated success by returning 0.
    // This should always be the case. This check is included for
    // forwards-compatibility.
    if a0 != 0 {
        const MSG: &[u8] = "sys_verify_integrity returned error result".as_bytes();
        unsafe { sys_panic(MSG.as_ptr(), MSG.len()) };
    }
}

// Make sure we only get one of these since it's stateful.
#[cfg(not(feature = "export-syscalls"))]
extern "C" {
    pub fn sys_alloc_aligned(nwords: usize, align: usize) -> *mut u8;
}

/// `sys_fork()` creates a new process by duplicating the calling process. The
/// new process is referred to as the child process. The calling process is
/// referred to as the parent process.
///
/// The child process and the parent process run in separate memory spaces. At
/// the time of `sys_fork()` both memory spaces have the same content.
///
/// # Return Value
///
/// On success, the PID of the child process (1) is returned in the parent, and
/// 0 is returned in the child. On failure, -1 is returned in the parent, no
/// child process is created.
#[cfg(feature = "export-syscalls")]
#[no_mangle]
pub extern "C" fn sys_fork() -> i32 {
    let Return(a0, _) = unsafe { syscall_0(nr::SYS_FORK, null_mut(), 0) };
    a0 as i32
}

/// `sys_pipe()` creates a pipe, a unidirectional data channel that can be used
/// for interprocess communication. The pointer `pipefd` is used to return two
/// file descriptors referring to the ends of the pipe. `pipefd[0]` refers to
/// the read end of the pipe. `pipefd[1]` refers to the write end of the pipe.
/// Data written to the write end of the pipe is buffered by the host until it
/// is read from the read end of the pipe.
///
/// # Return Value
///
/// On success, zero is returned.  On error, -1 is returned, and `pipefd` is
/// left unchanged.
///
/// # Safety
///
/// `pipefd` must be aligned, dereferenceable, and have capacity for 2 u32
/// values.
#[cfg(feature = "export-syscalls")]
#[no_mangle]
pub unsafe extern "C" fn sys_pipe(pipefd: *mut u32) -> i32 {
    let Return(a0, _) = syscall_0(nr::SYS_PIPE, pipefd, 2);
    a0 as i32
}

/// `sys_exit()` causes normal process termination.
///
/// Currently the `status` is unused and ignored.
#[cfg(feature = "export-syscalls")]
#[no_mangle]
pub extern "C" fn sys_exit(status: i32) -> ! {
    let Return(a0, _) = unsafe { syscall_0(nr::SYS_EXIT, null_mut(), 0) };
    #[allow(clippy::empty_loop)]
    loop {
        // prevent dishonest provers from relying on the ability to prove the
        // child process rather than the intended parent process.
    }
}

/// Executes a `ZKR' in the recursion circuit, specified by control
/// ID.  The control ID must be registered in the host's index of ZKRs.
///
/// This only triggers the execution of the ZKR; it does not add any
/// assumptions.  In order to prove that the ZKR executed correctly,
/// users must calculate the claim digest and add it to the list of
/// assumptions.
///
/// # Safety
///
/// `control_id` must be aligned and dereferenceable.
///
/// `input` must be aligned and have `input_len` u32s dereferenceable
#[cfg(feature = "export-syscalls")]
#[no_mangle]
pub unsafe extern "C" fn sys_execute_zkr(
    control_id: *const [u32; DIGEST_WORDS],
    input: *const u32,
    input_len: usize,
) {
    let Return(a0, _) = unsafe {
        syscall_3(
            nr::SYS_EXECUTE_ZKR,
            null_mut(),
            0,
            control_id as u32,
            input as u32,
            input_len as u32,
        )
    };

    // Check to ensure the host indicated success by returning 0.
    // Currently, this should always be the case. This check is
    // included for forwards-compatibility.
    if a0 != 0 {
        const MSG: &[u8] = "sys_execute_zkr returned error result".as_bytes();
        unsafe { sys_panic(MSG.as_ptr(), MSG.len()) };
    }
}
