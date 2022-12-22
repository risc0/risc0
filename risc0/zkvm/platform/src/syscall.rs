// Copyright 2022 RISC Zero, Inc.
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
use core::{arch::asm, cell::UnsafeCell};

#[cfg(target_os = "zkvm")]
use crate::memory;
use crate::{io::SliceDescriptor, WORD_SIZE};

pub mod ecall {
    pub const HALT: u32 = 0;
    pub const OUTPUT: u32 = 1;
    pub const SOFTWARE: u32 = 2;
    pub const SHA: u32 = 3;
    pub const FFPU: u32 = 4;
}

pub mod nr {
    pub const SYS_PANIC: u32 = 0;
    pub const SYS_LOG: u32 = 1;
    pub const SYS_IO: u32 = 2;
    pub const SYS_COMMIT: u32 = 3;
    pub const SYS_CYCLE_COUNT: u32 = 4;
    pub const SYS_COMPUTE_POLY: u32 = 5;
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

#[cfg(target_os = "zkvm")]
static mut READ_PTR: UnsafeCell<usize> = UnsafeCell::new(memory::INPUT.start());

#[inline(always)]
pub unsafe fn sys_panic(msg_ptr: *const u8, msg_len: usize) -> ! {
    #[cfg(target_os = "zkvm")]
    {
        asm!(
            "ecall",
            in("t0") ecall::SOFTWARE,
            in("a7") nr::SYS_PANIC,
            inout("a0") msg_ptr => _,
            inout("a1") msg_len => _,
        );
        unreachable!();
    }
    #[cfg(not(target_os = "zkvm"))]
    unimplemented!()
}

#[inline(always)]
pub unsafe fn sys_log(msg_ptr: *const u8, msg_len: usize) {
    #[cfg(target_os = "zkvm")]
    asm!(
        "ecall",
        in("t0") ecall::SOFTWARE,
        in("a7") nr::SYS_LOG,
        inout("a0") msg_ptr => _,
        inout("a1") msg_len => _,
    );
    #[cfg(not(target_os = "zkvm"))]
    unimplemented!()
}

#[inline(always)]
pub unsafe fn sys_io(channel: u32, buf_ptr: *const u8, buf_len: usize) -> &'static [u8] {
    #[cfg(target_os = "zkvm")]
    {
        let read_ptr: &mut usize = &mut *READ_PTR.get();
        let out_ptr = *read_ptr as *const u8;
        let out_nbytes: usize;
        asm!(
            "ecall",
            in("t0") ecall::SOFTWARE,
            in("a7") nr::SYS_IO,
            inout("a0") channel => out_nbytes,
            inout("a1") buf_ptr => _,
            in("a2") buf_len,
            in("a3") out_ptr,
        );
        let out_nwords = (out_nbytes + WORD_SIZE - 1) / WORD_SIZE;
        let read_end = read_ptr.checked_add(out_nwords * WORD_SIZE).unwrap();
        // if read_end > memory::INPUT.end() {
        //     panic!("host_recv overran input buffer with {nwords} word read");
        // }
        *read_ptr = read_end;
        core::slice::from_raw_parts(out_ptr, out_nbytes)
    }
    #[cfg(not(target_os = "zkvm"))]
    unimplemented!()
}

#[inline(always)]
pub unsafe fn sys_commit(buf_ptr: *const u32, buf_len: usize) {
    #[cfg(target_os = "zkvm")]
    {
        asm!(
            "ecall",
            in("t0") ecall::SOFTWARE,
            in("a7") nr::SYS_COMMIT,
            inout("a0") buf_ptr => _,
            inout("a1") buf_len => _,
        );
    }
    #[cfg(not(target_os = "zkvm"))]
    unimplemented!()
}

#[inline(always)]
pub unsafe fn sys_cycle_count() -> usize {
    #[cfg(target_os = "zkvm")]
    {
        let cycle: usize;
        asm!(
            "ecall",
            in("t0") ecall::SOFTWARE,
            in("a7") nr::SYS_CYCLE_COUNT,
            out("a0") cycle,
            out("a1") _,
        );
        cycle
    }
    #[cfg(not(target_os = "zkvm"))]
    unimplemented!()
}

#[inline(always)]
pub unsafe fn sys_ffpu(code: &[u32], args: &[*mut u32]) {
    #[cfg(target_os = "zkvm")]
    {
        let code_start: *const u32 = code.as_ptr();
        let code_end: *const u32 = code_start.add(code.len());

        let args_ptr: *const *mut u32 = args.as_ptr();
        asm!(
            "ecall",
            in("t0") ecall::FFPU,
            in("a0") code_start,
            in("a1") args_ptr,
            in("a2") code_end,
        );
    }
    #[cfg(not(target_os = "zkvm"))]
    unimplemented!()
}

#[inline(always)]
pub unsafe fn sys_compute_poly(
    arg0_ptr: *const SliceDescriptor, // eval_u
    arg1_ptr: *const u32,             // poly_mix
    arg2_ptr: *const SliceDescriptor, // out
    arg3_ptr: *const SliceDescriptor, // mix
) -> &'static [u32] {
    #[cfg(target_os = "zkvm")]
    {
        let read_ptr: &mut usize = &mut *READ_PTR.get();
        let out_ptr = *read_ptr as *const u32;
        let out_nwords: usize;
        asm!(
            "ecall",
            in("t0") ecall::SOFTWARE,
            in("a7") nr::SYS_COMPUTE_POLY,
            inout("a0") arg0_ptr => out_nwords,
            inout("a1") arg1_ptr => _,
            in("a2") arg2_ptr,
            in("a3") arg3_ptr,
            in("a4") out_ptr,
        );
        let read_end = read_ptr.checked_add(out_nwords * WORD_SIZE).unwrap();
        *read_ptr = read_end;
        core::slice::from_raw_parts(out_ptr, out_nwords)
    }
    #[cfg(not(target_os = "zkvm"))]
    unimplemented!()
}

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
