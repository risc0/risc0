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

.equ STACK_TOP, 0xfff00000
.equ USER_REGS_ADDR, 0xffff0080
.equ ECALL_DISPATCH_ADDR, 0xffff1000
.equ ECALL_TABLE_SIZE, 7
.equ HOST_ECALL_TERMINATE, 0
.equ HOST_ECALL_READ, 1
.equ HOST_ECALL_SHA, 4
.equ WORD_SIZE, 4
.equ REG_T0, 5
.equ REG_A0, 10
.equ REG_A1, 11
.equ REG_A2, 12
.equ REG_A3, 13
.equ REG_A4, 14

.section .text
.global _start
_start:
    // Load the global pointer from the place the linker put it
    // Note: we definitely don't want this relaxed since the GP is invalid
    .option push
    .option norelax
    la gp, __global_pointer$
    .option pop

    // Set the kernel stack pointer near the top of kernel memory
    li sp, STACK_TOP

    // Initialize the ecall dispatch table
    li t0, ECALL_DISPATCH_ADDR
    la t1, ecall_dispatch
    sw t1, 0(t0)

    // Initialize useful constants
    li t3, USER_REGS_ADDR
    la t4, ecall_table
    li t5, ECALL_TABLE_SIZE

    // Jump into userspace
    mret

ecall_table:
    j ecall_halt
    j ecall_input
    j ecall_software
    j ecall_sha
    j ecall_bigint
    j ecall_user
    j ecall_bigint2

ecall_dispatch:
    // load t0 from userspace
    lw a0, REG_T0 * WORD_SIZE (t3)
    // check that ecall request is within range
    bge a0, t5, panic
    // adjust index so that it points to word sized entries
    slli a0, a0, 2
    // compute the table entry
    add a1, t4, a0
    // jump into dispatch table
    jr a1

ecall_halt:
    li a7, HOST_ECALL_TERMINATE
    ecall

ecall_input:
    fence

ecall_software:
    // prepare a software ecall
    li a7, HOST_ECALL_READ
    lw a0, REG_A2 * WORD_SIZE (t3) // syscall_ptr -> fd
    lw a1, REG_A0 * WORD_SIZE (t3) // from_host_ptr -> buf
    lw a2, REG_A1 * WORD_SIZE (t3) // from_host_len -> len
    slli a2, a2, 2
    // call the host
    ecall

    // read (a0, a1) back from host
    // fd == 0 means read (a0, a1) from host
    li a0, 0
    // read into user registers starting at a0
    addi a1, t3, REG_A0 * WORD_SIZE
    // read two words from host
    li a2, 2 * WORD_SIZE
    // call the host
    ecall

    // return back to userspace
    mret

ecall_sha:
    // prepare a sha ecall
    li a7, HOST_ECALL_SHA
    lw a0, REG_A0 * WORD_SIZE (t3) // out_state
    lw a1, REG_A1 * WORD_SIZE (t3) // in_state
    lw a2, REG_A2 * WORD_SIZE (t3) // block_ptr1
    lw a3, REG_A3 * WORD_SIZE (t3) // block_ptr2
    lw a4, REG_A4 * WORD_SIZE (t3) // count
    // call the host
    ecall
    // return back to userspace
    mret

ecall_bigint:
    fence

ecall_user:
    fence

ecall_bigint2:
    fence

panic:
    fence
