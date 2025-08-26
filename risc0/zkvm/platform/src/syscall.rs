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

#[cfg(target_os = "zkvm")]
use core::arch::asm;
use core::{cmp::min, ffi::CStr, ptr::null_mut, slice, str::Utf8Error};

use num_enum::{FromPrimitive, IntoPrimitive};
use paste::paste;

use crate::WORD_SIZE;

pub mod ecall {
    pub const HALT: u32 = 0;
    pub const INPUT: u32 = 1;
    pub const SOFTWARE: u32 = 2;
    pub const SHA: u32 = 3;
    pub const BIGINT: u32 = 4;
    pub const USER: u32 = 5;
    pub const BIGINT2: u32 = 6;
    pub const POSEIDON2: u32 = 7;
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

pub mod keccak_mode {
    pub const KECCAK_PERMUTE: u32 = 0;
    pub const KECCAK_PROVE: u32 = 1;
}

pub const DIGEST_WORDS: usize = 8;
pub const DIGEST_BYTES: usize = WORD_SIZE * DIGEST_WORDS;

pub const KECCACK_STATE_BYTES: usize = 200;
pub const KECCACK_STATE_WORDS: usize = 200 / WORD_SIZE;
pub const KECCACK_STATE_DWORDS: usize = 200 / 8;

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
    declare_syscall!(pub SYS_KECCAK);
    declare_syscall!(pub SYS_LOG);
    declare_syscall!(pub SYS_PANIC);
    declare_syscall!(pub SYS_PIPE);
    #[deprecated]
    pub const SYS_PROVE_KECCAK: crate::syscall::SyscallName = unsafe {
        crate::syscall::SyscallName::from_bytes_with_nul(
            c"risc0-zkvm-platform::syscall::SYS_PROVE_KECCAK".as_ptr() as *const u8,
        )
    };
    declare_syscall!(pub SYS_PROVE_ZKR);
    declare_syscall!(pub SYS_RANDOM);
    declare_syscall!(pub SYS_READ);
    declare_syscall!(pub SYS_VERIFY_INTEGRITY);
    declare_syscall!(pub SYS_VERIFY_INTEGRITY2);
    declare_syscall!(pub SYS_WRITE);
}

#[repr(usize)]
#[derive(Copy, Clone, Debug, Eq, PartialEq, IntoPrimitive, FromPrimitive)]
pub enum Syscall {
    #[num_enum(catch_all)]
    Unknown(usize) = 0,
    Argc = 1,
    Argv = 2,
    CycleCount = 3,
    Exit = 4,
    Fork = 5,
    Getenv = 6,
    Keccak = 7,
    Log = 8,
    Panic = 9,
    Pipe = 10,
    Random = 11,
    Read = 12,
    User = 13,
    VerifyIntegrity = 14,
    VerifyIntegrity2 = 15,
    Write = 16,
    ProveZkr = 17,
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
        $(, $a0:ident $(, $a1:ident $(, $a2: ident $(, $a3: ident $(, $a4: ident )? )? )? )? )?
    ) => {
        /// Invoke a raw system call
        ///
        /// # Safety
        ///
        /// `from_host` must be aligned and dereferenceable.
        #[cfg_attr(feature = "export-syscalls", unsafe(no_mangle))]
        #[deprecated]
        pub unsafe extern "C" fn $func_name(
            syscall_name: SyscallName,
            from_host: *mut u32,
            from_host_words: usize
            $(,$a0: u32 $(,$a1: u32 $(,$a2: u32 $(,$a3: u32 $(,$a4: u32)? )? )? )? )?
        ) -> Return {
            unimplemented!();
        }


        paste! {
            /// Invoke a raw system call
            ///
            /// # Safety
            ///
            /// `from_host` must be aligned and dereferenceable.
            #[cfg_attr(feature = "export-syscalls", unsafe(no_mangle))]
            pub unsafe extern "C" fn [<$func_name _nr>] (
                syscall: usize,
                syscall_name: SyscallName,
                from_host: *mut u32,
                from_host_words: usize
                $(,$a0: u32 $(,$a1: u32 $(,$a2: u32 $(,$a3: u32 $(,$a4: u32)? )? )? )? )?
            ) -> Return {
                #[cfg(target_os = "zkvm")] {
                    let a0: u32;
                    let a1: u32;
                    unsafe {
                        ::core::arch::asm!(
                            "ecall",
                            in("t0") $crate::syscall::ecall::SOFTWARE,
                            in("t6") syscall,
                            inlateout("a0") from_host => a0,
                            inlateout("a1") from_host_words => a1,
                            in("a2") syscall_name.as_ptr()
                            $(,in("a3") $a0 $(,in("a4") $a1 $(,in("a5") $a2 $(,in("a6") $a3 $(,in("a7") $a4 )? )? )? )? )?
                        );
                    }
                    Return(a0, a1)
                }
                #[cfg(not(target_os = "zkvm"))]
                unimplemented!()
            }
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
#[cfg_attr(feature = "export-syscalls", no_mangle)]
#[cfg_attr(not(feature = "export-syscalls"), inline(always))]
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
#[cfg_attr(feature = "export-syscalls", no_mangle)]
#[cfg_attr(not(feature = "export-syscalls"), inline(always))]
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
/// `state_addr`, `in_buf_addr`, and `out_buf_addr` must be word-aligned and
/// dereferenceable.
#[cfg_attr(feature = "export-syscalls", no_mangle)]
#[cfg_attr(not(feature = "export-syscalls"), inline(always))]
pub unsafe extern "C" fn sys_poseidon2(
    _state_addr: *mut [u32; DIGEST_WORDS],
    _in_buf_addr: *const u8,
    _out_buf_addr: *mut [u32; DIGEST_WORDS],
    _bits_count: u32,
) {
    unimplemented!()
}

/// # Safety
///
/// `result`, `x`, `y`, and `modulus` must be aligned and dereferenceable.
#[cfg_attr(feature = "export-syscalls", no_mangle)]
#[cfg_attr(not(feature = "export-syscalls"), inline(always))]
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
    unsafe { syscall_0_nr(Syscall::Random.into(), nr::SYS_RANDOM, recv_buf, words) };
}

/// # Safety
///
/// `msg_ptr` must be aligned and dereferenceable.
#[cfg_attr(feature = "export-syscalls", no_mangle)]
pub unsafe extern "C" fn sys_panic(msg_ptr: *const u8, len: usize) -> ! {
    unsafe {
        syscall_2_nr(
            Syscall::Panic.into(),
            nr::SYS_PANIC,
            null_mut(),
            0,
            msg_ptr as u32,
            len as u32,
        )
    };

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
    unsafe {
        syscall_2_nr(
            Syscall::Log.into(),
            nr::SYS_LOG,
            null_mut(),
            0,
            msg_ptr as u32,
            len as u32,
        )
    };
}

#[cfg_attr(feature = "export-syscalls", no_mangle)]
pub extern "C" fn sys_cycle_count() -> u64 {
    let Return(hi, lo) = unsafe {
        syscall_0_nr(
            Syscall::CycleCount.into(),
            nr::SYS_CYCLE_COUNT,
            null_mut(),
            0,
        )
    };
    ((hi as u64) << 32) + lo as u64
}

#[allow(dead_code)]
fn print(msg: &str) {
    let msg = msg.as_bytes();
    unsafe {
        sys_log(msg.as_ptr(), msg.len());
    }
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
#[cfg_attr(feature = "export-syscalls", unsafe(no_mangle))]
pub unsafe extern "C" fn sys_read(fd: u32, recv_ptr: *mut u8, nbytes: usize) -> usize {
    let Return(nbytes_read, final_word) = unsafe {
        syscall_2_nr(
            Syscall::Read.into(),
            nr::SYS_READ,
            recv_ptr as *mut u32,
            nbytes,
            fd,
            nbytes as u32,
        )
    };

    nbytes_read as usize
}

/// Reads up to the given number of words into the buffer [recv_buf,
/// recv_buf + nwords).  Returns the number of bytes actually read.
/// sys_read_words is a more efficient interface than sys_read, but
/// varies from POSIX semantics.  Notably:
///
/// * The read length is specified in words, not bytes.  (The output
///   length is still returned in bytes)
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
    let nbytes = nwords * WORD_SIZE;
    let Return(nbytes_read, final_word) = unsafe {
        syscall_2_nr(
            Syscall::Read.into(),
            nr::SYS_READ,
            recv_ptr,
            nbytes,
            fd,
            nbytes as u32,
        )
    };
    nbytes_read as usize
}

/// # Safety
///
/// `write_ptr` must be aligned and dereferenceable.
#[cfg_attr(feature = "export-syscalls", no_mangle)]
pub unsafe extern "C" fn sys_write(fd: u32, write_ptr: *const u8, nbytes: usize) {
    unsafe {
        syscall_3_nr(
            Syscall::Write.into(),
            nr::SYS_WRITE,
            null_mut(),
            0,
            fd,
            write_ptr as u32,
            nbytes as u32,
        )
    };
}

// Some environment variable names are considered safe by default to use in the guest, provided by
// the host, and are included in this list. It may be useful to allow guest developers to register
// additional variable names as part of their guest program.
const ALLOWED_ENV_VARNAMES: &[&[u8]] = &[
    b"RUST_BACKTRACE",
    b"RUST_LIB_BACKTRACE",
    b"RISC0_KECCAK_PO2",
];

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
    if cfg!(not(feature = "sys-getenv")) {
        let mut allowed = false;
        for allowed_varname in ALLOWED_ENV_VARNAMES {
            let varname_buf = unsafe { slice::from_raw_parts(varname, varname_len) };
            if *allowed_varname == varname_buf {
                allowed = true;
                break;
            }
        }
        if !allowed {
            const MSG_1: &[u8] = "sys_getenv not enabled for var".as_bytes();
            unsafe { sys_log(MSG_1.as_ptr(), MSG_1.len()) };
            unsafe { sys_log(varname, varname_len) };
            const MSG_2: &[u8] = "sys_getenv is disabled; can be enabled with the sys-getenv feature flag on risc0-zkvm-platform".as_bytes();
            unsafe { sys_panic(MSG_2.as_ptr(), MSG_2.len()) };
        }
    }
    let Return(a0, _) = unsafe {
        syscall_2_nr(
            Syscall::Getenv.into(),
            nr::SYS_GETENV,
            out_words,
            out_nwords,
            varname as u32,
            varname_len as u32,
        )
    };
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
    if cfg!(not(feature = "sys-args")) {
        const MSG: &[u8] = "sys_argc is disabled; can be enabled with the sys-args feature flag on risc0-zkvm-platform".as_bytes();
        unsafe { sys_panic(MSG.as_ptr(), MSG.len()) };
    }
    let Return(a0, _) = unsafe { syscall_0_nr(Syscall::Argc.into(), nr::SYS_ARGC, null_mut(), 0) };
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
    if cfg!(not(feature = "sys-args")) {
        const MSG: &[u8] = "sys_argv is disabled; can be enabled with the sys-args feature flag on risc0-zkvm-platform".as_bytes();
        unsafe { sys_panic(MSG.as_ptr(), MSG.len()) };
    }
    let Return(a0, _) = unsafe {
        syscall_1_nr(
            Syscall::Argv.into(),
            nr::SYS_ARGV,
            out_words,
            out_nwords,
            arg_index as u32,
        )
    };
    a0 as usize
}

#[cfg_attr(feature = "export-syscalls", no_mangle)]
#[deprecated]
pub extern "C" fn sys_alloc_words(nwords: usize) -> *mut u32 {
    unsafe { sys_alloc_aligned(WORD_SIZE * nwords, WORD_SIZE) as *mut u32 }
}

/// # Safety
///
/// This function should be safe to call, but clippy complains if it is not marked as `unsafe`.
#[cfg(all(feature = "export-syscalls", not(target_os = "zkvm")))]
#[no_mangle]
pub unsafe extern "C" fn sys_alloc_aligned(bytes: usize, align: usize) -> *mut u8 {
    unimplemented!("sys_alloc_aligned called outside of target_os = zkvm");
}

/// # Safety
///
/// This function should be safe to call, but clippy complains if it is not marked as `unsafe`.
#[cfg(all(
    feature = "export-syscalls",
    feature = "heap-embedded-alloc",
    target_os = "zkvm"
))]
#[no_mangle]
pub unsafe extern "C" fn sys_alloc_aligned(bytes: usize, align: usize) -> *mut u8 {
    use core::alloc::GlobalAlloc;
    crate::heap::embedded::HEAP.alloc(core::alloc::Layout::from_size_align(bytes, align).unwrap())
}

/// # Safety
///
/// This function should be safe to call, but clippy complains if it is not marked as `unsafe`.
#[cfg(all(
    feature = "export-syscalls",
    not(feature = "heap-embedded-alloc"),
    target_os = "zkvm"
))]
#[no_mangle]
pub unsafe extern "C" fn sys_alloc_aligned(bytes: usize, align: usize) -> *mut u8 {
    crate::heap::bump::alloc_aligned(bytes, align)
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

    // Send the claim_digest to the host via software ecall.
    let Return(a0, _) = unsafe {
        syscall_2_nr(
            Syscall::VerifyIntegrity.into(),
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

/// TODO: Send a ReceiptClaim digest to the host to request verification. Meant for proofs that use union.
///
/// # Safety
///
/// `claim_digest` must be aligned and dereferenceable.
/// `control_root` must be aligned and dereferenceable.
#[cfg(feature = "export-syscalls")]
#[no_mangle]
pub unsafe extern "C" fn sys_verify_integrity2(
    claim_digest: *const [u32; DIGEST_WORDS],
    control_root: *const [u32; DIGEST_WORDS],
) {
    let mut to_host = [0u32; DIGEST_WORDS * 2];
    to_host[..DIGEST_WORDS].copy_from_slice(claim_digest.as_ref().unwrap_unchecked());
    to_host[DIGEST_WORDS..].copy_from_slice(control_root.as_ref().unwrap_unchecked());

    // Send the claim_digest to the host via software ecall.
    let Return(a0, _) = unsafe {
        syscall_2_nr(
            Syscall::VerifyIntegrity2.into(),
            nr::SYS_VERIFY_INTEGRITY2,
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
        const MSG: &[u8] = "sys_verify_integrity2 returned error result".as_bytes();
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
    let Return(a0, _) = unsafe { syscall_0_nr(Syscall::Fork.into(), nr::SYS_FORK, null_mut(), 0) };
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
    let Return(a0, _) = unsafe { syscall_0_nr(Syscall::Pipe.into(), nr::SYS_PIPE, pipefd, 2) };
    a0 as i32
}

/// `sys_exit()` causes normal process termination.
///
/// Currently the `status` is unused and ignored.
#[cfg(feature = "export-syscalls")]
#[no_mangle]
pub extern "C" fn sys_exit(status: i32) -> ! {
    let Return(a0, _) = unsafe { syscall_0_nr(Syscall::Exit.into(), nr::SYS_EXIT, null_mut(), 0) };
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
/// `claim_digest` must be aligned and dereferenceable.
/// `control_id` must be aligned and dereferenceable.
/// `control_root` must be aligned and dereferenceable.
/// `input` must be aligned and have `input_len` u32s dereferenceable
#[cfg_attr(all(feature = "export-syscalls", feature = "unstable"), no_mangle)]
#[stability::unstable]
pub unsafe extern "C" fn sys_prove_zkr(
    claim_digest: *const [u32; DIGEST_WORDS],
    control_id: *const [u32; DIGEST_WORDS],
    control_root: *const [u32; DIGEST_WORDS],
    input: *const u32,
    input_len: usize,
) {
    let Return(a0, _) = unsafe {
        syscall_5_nr(
            Syscall::ProveZkr.into(),
            nr::SYS_PROVE_ZKR,
            null_mut(),
            0,
            claim_digest as u32,
            control_id as u32,
            control_root as u32,
            input as u32,
            input_len as u32,
        )
    };

    // Check to ensure the host indicated success by returning 0.
    // Currently, this should always be the case. This check is
    // included for forwards-compatibility.
    if a0 != 0 {
        const MSG: &[u8] = "sys_prove_zkr returned error result".as_bytes();
        unsafe { sys_panic(MSG.as_ptr(), MSG.len()) };
    }
}

/// Permute the keccak state on the host
///
/// # Safety
#[cfg_attr(feature = "export-syscalls", no_mangle)]
pub unsafe extern "C" fn sys_keccak(
    in_state: *const [u64; KECCACK_STATE_DWORDS],
    out_state: *mut [u64; KECCACK_STATE_DWORDS],
) -> i32 {
    let Return(a0, _) = unsafe {
        syscall_3_nr(
            Syscall::Keccak.into(),
            nr::SYS_KECCAK,
            out_state as *mut u32,
            KECCACK_STATE_WORDS,
            keccak_mode::KECCAK_PERMUTE,
            in_state as u32,
            0,
        )
    };
    a0 as i32
}

/// Executes the keccak circuit, and then executes the lift predicate
/// in the recursion circuit.
///
/// This only triggers the execution of the circuits; it does not add
/// any assumptions.  In order to prove that it executed correctly,
/// users must calculate the claim digest and add it to the list of
/// assumptions.
///
/// # Safety
///
/// `claim_digest` must be aligned and dereferenceable.
/// `control_root` must be aligned and dereferenceable.
/// `input` must be aligned and have `input_len` u32s dereferenceable
#[cfg_attr(feature = "export-syscalls", no_mangle)]
pub unsafe extern "C" fn sys_prove_keccak(
    claim_digest: *const [u32; DIGEST_WORDS],
    control_root: *const [u32; DIGEST_WORDS],
) {
    let Return(a0, _) = unsafe {
        syscall_3_nr(
            Syscall::Keccak.into(),
            nr::SYS_KECCAK,
            null_mut(),
            0,
            keccak_mode::KECCAK_PROVE,
            claim_digest as u32,
            control_root as u32,
        )
    };

    // Check to ensure the host indicated success by returning 0.
    // Currently, this should always be the case. This check is
    // included for forwards-compatibility.
    if a0 != 0 {
        const MSG: &[u8] = "sys_prove_keccak returned error result".as_bytes();
        unsafe { sys_panic(MSG.as_ptr(), MSG.len()) };
    }
}

#[repr(C)]
pub struct BigIntBlobHeader {
    pub nondet_program_size: u32,
    pub verify_program_size: u32,
    pub consts_size: u32,
    pub temp_size: u32,
}

macro_rules! impl_sys_bigint2 {
    ($func_name:ident, $a1:ident
        $(, $a2: ident
            $(, $a3: ident
                $(, $a4: ident
                    $(, $a5: ident
                        $(, $a6: ident)?
                    )?
                )?
            )?
        )?
    ) => {
        /// Invoke a bigint2 program.
        ///
        /// # Safety
        ///
        /// `blob_ptr` and all arguments must be aligned and dereferenceable.
        #[cfg_attr(feature = "export-syscalls", no_mangle)]
        pub unsafe extern "C" fn $func_name(blob_ptr: *const u8, a1: *const u32
            $(, $a2: *const u32
                $(, $a3: *const u32
                    $(, $a4: *const u32
                        $(, $a5: *const u32
                            $(, $a6: *const u32)?
                        )?
                    )?
                )?
            )?
        ) {
            #[cfg(target_os = "zkvm")]
            {
                let header = blob_ptr as *const $crate::syscall::BigIntBlobHeader;
                let nondet_program_ptr = (header.add(1)) as *const u32;
                let verify_program_ptr = nondet_program_ptr.add((*header).nondet_program_size as usize);
                let consts_ptr = verify_program_ptr.add((*header).verify_program_size as usize);
                let temp_space = ((*header).temp_size as usize) << 2;

                ::core::arch::asm!(
                    "sub sp, sp, {temp_space}",
                    "ecall",
                    "add sp, sp, {temp_space}",
                    temp_space = in(reg) temp_space,
                    in("t0") ecall::BIGINT2,
                    in("t1") nondet_program_ptr,
                    in("t2") verify_program_ptr,
                    in("t3") consts_ptr,
                    in("a0") blob_ptr,
                    in("a1") a1,
                    $(in("a2") $a2,
                        $(in("a3") $a3,
                            $(in("a4") $a4,
                                $(in("a5") $a5,
                                    $(in("a6") $a6)?
                                )?
                            )?
                        )?
                    )?
                );
            }

            #[cfg(not(target_os = "zkvm"))]
            unimplemented!()
        }
    }
}

impl_sys_bigint2!(sys_bigint2_1, a1);
impl_sys_bigint2!(sys_bigint2_2, a1, a2);
impl_sys_bigint2!(sys_bigint2_3, a1, a2, a3);
impl_sys_bigint2!(sys_bigint2_4, a1, a2, a3, a4);
impl_sys_bigint2!(sys_bigint2_5, a1, a2, a3, a4, a5);
impl_sys_bigint2!(sys_bigint2_6, a1, a2, a3, a4, a5, a6);
