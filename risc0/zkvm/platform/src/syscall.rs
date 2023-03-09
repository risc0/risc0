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
use core::ptr::null_mut;

use crate::WORD_SIZE;

pub mod ecall {
    pub const HALT: u32 = 0;
    pub const OUTPUT: u32 = 1;
    pub const SOFTWARE: u32 = 2;
    pub const SHA: u32 = 3;
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
            $vis const $name: $crate::syscall::SyscallName
                = unsafe{
                    $crate::syscall::SyscallName::from_bytes_with_nul(concat!(
                        module_path!(),
                        "::",
                        stringify!($name),
                        "\0").as_ptr())
                };
    };
}

pub mod nr {
    declare_syscall!(pub SYS_PANIC);
    declare_syscall!(pub SYS_LOG);
    declare_syscall!(pub SYS_CYCLE_COUNT);
    declare_syscall!(pub SYS_INITIAL_INPUT);
    declare_syscall!(pub SYS_JOURNAL);
    declare_syscall!(pub SYS_STDERR);
    declare_syscall!(pub SYS_STDOUT);
    declare_syscall!(pub SYS_RANDOM);
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

#[repr(C)]
/// Returned registers (a0, a1) from a syscall invocation.
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
pub unsafe fn sys_halt() {
    #[cfg(target_os = "zkvm")]
    {
        asm!(
            "ecall",
            in("t0") ecall::HALT,
        );
        unreachable!();
    }
    #[cfg(not(target_os = "zkvm"))]
    unimplemented!()
}

#[inline(always)]
pub unsafe fn sys_output(output_id: u32, output_value: u32) {
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
pub unsafe fn sys_sha_compress(
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

pub unsafe extern "C" fn sys_rand(recv_buf: *mut u32, words: usize) {
    syscall_0(nr::SYS_RANDOM, recv_buf, words);
}

pub unsafe extern "C" fn sys_panic(msg_ptr: *const u8, len: usize) -> ! {
    syscall_2(nr::SYS_PANIC, null_mut(), 0, msg_ptr as u32, len as u32);
    unreachable!()
}

pub unsafe extern "C" fn sys_log(msg_ptr: *const u8, len: usize) {
    syscall_2(nr::SYS_LOG, null_mut(), 0, msg_ptr as u32, len as u32);
}

pub extern "C" fn sys_cycle_count() -> usize {
    unsafe {
        let Return(a0, _) = syscall_0(nr::SYS_CYCLE_COUNT, null_mut(), 0);
        a0 as usize
    }
}
