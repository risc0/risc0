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

.equ USER_START_ADDR, 0x00010000
.equ STACK_TOP, 0xfff00000
.equ USER_REGS_ADDR, 0xffff0080
.equ MEPC_ADDR, 0xffff0200
.equ GLOBAL_OUTPUT_ADDR, 0xffff0240
.equ GLOBAL_INPUT_ADDR, 0xffff0260
.equ ECALL_DISPATCH_ADDR, 0xffff1000
.equ TRAP_DISPATCH, 0xffff2000
.equ ECALL_TABLE_SIZE, 8
.equ HOST_ECALL_TERMINATE, 0
.equ HOST_ECALL_READ, 1
.equ HOST_ECALL_POSEIDON2, 3
.equ HOST_ECALL_SHA, 4
.equ HOST_ECALL_BIGINT, 5
.equ WORD_SIZE, 4
.equ DIGEST_WORDS, 8
.equ REG_SP, 2
.equ REG_T0, 5
.equ REG_T1, 6
.equ REG_T2, 7
.equ REG_A0, 10
.equ REG_A1, 11
.equ REG_A2, 12
.equ REG_A3, 13
.equ REG_A4, 14
.equ REG_A5, 15
.equ REG_A6, 16
.equ REG_T3, 28
.equ REG_T6, 31
.equ USER_MODE, 0
.equ MACHINE_MODE, 1

.section .text
.global _start
_start:
    # Load the global pointer from the place the linker put it
    # Note: we definitely don't want this relaxed since the GP is invalid
    .option push
    .option norelax
    la gp, __global_pointer$
    .option pop

    # Set the kernel stack pointer near the top of kernel memory
    li sp, STACK_TOP

    # Initialize the ecall dispatch table
    li t0, ECALL_DISPATCH_ADDR
    la t1, _ecall_dispatch
    sw t1, 0(t0)

    # Initialize the trap dispatch address
    la a0, _trap_handler
    li a1, TRAP_DISPATCH
    sw a0, 0(a1)

    # Initialize useful constants
    li tp, USER_REGS_ADDR
    la s1, _ecall_table
    li s2, ECALL_TABLE_SIZE

    # Load the user program entry into MEPC
    li a0, USER_START_ADDR
    li a1, MEPC_ADDR
    lw a2, 0(a0)
    addi a2, a2, -WORD_SIZE
    sw a2, 0(a1)

    # Jump into userspace
    mret

_ecall_table:
    j _ecall_halt
    j _ecall_input
    j _ecall_software
    j _ecall_sha
    j _ecall_bigint
    unimp # user
    j _ecall_bigint2
    j _ecall_poseidon2

_ecall_dispatch:
    # Initialize useful constants again because we may have
    # trashed them in the trap handler
    li tp, USER_REGS_ADDR
    la s1, _ecall_table
    li s2, ECALL_TABLE_SIZE

    # load t0 from userspace
    lw a0, REG_T0 * WORD_SIZE (tp)
    # check that ecall request is within range
    bgeu a0, s2, 1f
    # adjust index so that it points to word sized entries
    slli a0, a0, 2
    # compute the table entry
    add a1, s1, a0
    # jump into dispatch table
    jr a1
1:
    unimp # panic

_ecall_halt:
    # copy output digest from pointer in a1 to GLOBAL_OUTPUT_ADDR
    lw t0, REG_A1 * WORD_SIZE (tp) # out_state
    li t1, GLOBAL_OUTPUT_ADDR
    lw t2, 0(t0)
    sw t2, 0(t1)
    lw t2, 4(t0)
    sw t2, 4(t1)
    lw t2, 8(t0)
    sw t2, 8(t1)
    lw t2, 12(t0)
    sw t2, 12(t1)
    lw t2, 16(t0)
    sw t2, 16(t1)
    lw t2, 20(t0)
    sw t2, 20(t1)
    lw t2, 24(t0)
    sw t2, 24(t1)
    lw t2, 28(t0)
    sw t2, 28(t1)

    # a0 has the following format for v1 ABI:
    # u8(0, 0, user_exit, halt_type)
    # We need this format to be compatible with Rv32imV2Claim:
    # u16(user_exit, halt_type)
    lw a0, REG_A0 * WORD_SIZE (tp)
    srli a1, a0, 8
    andi a1, a1, 0xff
    slli a1, a1, 16
    andi a0, a0, 0xff
    or a0, a1, a0
    andi t0, a0, 0xff

    li a1, 0
    li a7, HOST_ECALL_TERMINATE
    ecall

    # return to userspace if halt_type != HALT (i.e. 0)
    beq t0, zero, 1f
    mret

1:
    unimp

# return a word of the input digest to the user
_ecall_input:
    lw t0, REG_A0 * WORD_SIZE (tp) # index

    # check if index is > 8
    li t1, DIGEST_WORDS
    bge t0, t1, 1f

    # load word from `GLOBAL_INPUT_ADDR + index * WORD_SIZE`
    slli t0, t0, 2
    li t1, GLOBAL_INPUT_ADDR
    add t0, t0, t1
    lw t0, 0(t0)

    # store word into user register a0
    sw t0, REG_A0 * WORD_SIZE (tp)

    mret

1:
    unimp # panic

_ecall_software:
    lw a0, REG_T6 * WORD_SIZE (tp) # user/kernel syscall nr
    lw a1, REG_A2 * WORD_SIZE (tp) # syscall_ptr
    lw a2, REG_A0 * WORD_SIZE (tp) # from_host_ptr
    lw a3, REG_A1 * WORD_SIZE (tp) # from_host_len
    call ecall_software

    # return back to userspace
    mret

_ecall_sha:
    lw a0, REG_A0 * WORD_SIZE (tp) # out_state
    lw a1, REG_A1 * WORD_SIZE (tp) # in_state
    lw a2, REG_A2 * WORD_SIZE (tp) # block_ptr1
    lw a3, REG_A3 * WORD_SIZE (tp) # block_ptr2
    lw a4, REG_A4 * WORD_SIZE (tp) # count
    call ecall_sha

    # return back to userspace
    mret

_ecall_poseidon2:
    lw a0, REG_A0 * WORD_SIZE (tp) # state_addr
    lw a1, REG_A1 * WORD_SIZE (tp) # buf_in_addr
    lw a2, REG_A2 * WORD_SIZE (tp) # buf_out_addr
    lw a3, REG_A3 * WORD_SIZE (tp) # bits_count
    li a7, HOST_ECALL_POSEIDON2
    ecall

    # return back to userspace
    mret

_ecall_bigint2:
    # save stack pointer
    mv s0, sp

    # prepare ecall
    lw sp, REG_SP * WORD_SIZE (tp) # stack pointer
    li t0, USER_MODE
    lw t1, REG_T1 * WORD_SIZE (tp) # nondet_program_ptr
    lw t2, REG_T2 * WORD_SIZE (tp) # verify_program_ptr
    lw t3, REG_T3 * WORD_SIZE (tp) # consts_ptr
    lw a0, REG_A0 * WORD_SIZE (tp) # blob_ptr
    lw a1, REG_A1 * WORD_SIZE (tp) # a1
    lw a2, REG_A2 * WORD_SIZE (tp) # a2
    lw a3, REG_A3 * WORD_SIZE (tp) # a3
    lw a4, REG_A4 * WORD_SIZE (tp) # a4
    lw a5, REG_A5 * WORD_SIZE (tp) # a5
    lw a6, REG_A6 * WORD_SIZE (tp) # a6
    li a7, HOST_ECALL_BIGINT

    # call the circuit
    ecall

    # restore stack pointer
    mv sp, s0

    # return back to userspace
    mret

_ecall_bigint:
    # prepare a bigint ecall
    lw a0, REG_A0 * WORD_SIZE (tp) # result
    lw a1, REG_A1 * WORD_SIZE (tp) # op
    lw a2, REG_A2 * WORD_SIZE (tp) # x
    lw a3, REG_A3 * WORD_SIZE (tp) # y
    lw a4, REG_A4 * WORD_SIZE (tp) # modulus

    call ecall_bigint_v1compat

    # return back to userspace
    mret

_trap_handler:
    # Set the kernel stack pointer near the top of kernel memory
    li sp, STACK_TOP

    tail trap_handler