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

.equ KSTACK_TOP, 0xfff00000
.equ ECALL_DISPATCH, 0xffff1000
.equ TRAP_DISPATCH, 0xffff2000

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
    li sp, KSTACK_TOP

    # Initialize the kernel allocator
    call init_kernel_allocator

    # Initialize the ecall dispatch address
    la a0, _ecall_dispatch
    li a1, ECALL_DISPATCH
    sw a0, 0(a1)

    # Initialize the trap dispatch table
    # Set up IllegalInstruction handler (cause = 2) at TRAP_DISPATCH + 2
    la a0, _trap_illegal_instruction
    li a1, TRAP_DISPATCH
    addi a1, a1, 8  # 2 * 4 bytes (cause 2)
    sw a0, 0(a1)

    la a0, _trap_instruction_misaligned
    li a1, TRAP_DISPATCH # cause 0
    sw a0, 0(a1)

    la a0, _trap_instruction_fault
    li a1, TRAP_DISPATCH
    addi a1, a1, 4  # 1 * 4 bytes (cause 1)
    sw a0, 0(a1)

    la a0, _trap_breakpoint
    li a1, TRAP_DISPATCH
    addi a1, a1, 12  # 3 * 4 bytes (cause 3)
    sw a0, 0(a1)

    la a0, _trap_load_address_misaligned
    li a1, TRAP_DISPATCH
    addi a1, a1, 16  # 4 * 4 bytes (cause 4)
    sw a0, 0(a1)

    la a0, _trap_load_access_fault
    li a1, TRAP_DISPATCH
    addi a1, a1, 20  # 5 * 4 bytes (cause 5)
    sw a0, 0(a1)

    la a0, _trap_store_address_misaligned
    li a1, TRAP_DISPATCH
    addi a1, a1, 24  # 6 * 4 bytes (cause 6)
    sw a0, 0(a1)

    la a0, _trap_store_access_fault
    li a1, TRAP_DISPATCH
    addi a1, a1, 28  # 7 * 4 bytes (cause 7)
    sw a0, 0(a1)


    tail kstart

_ecall_dispatch:
    # Set the kernel stack pointer near the top of kernel memory
    li sp, KSTACK_TOP

    tail ecall_dispatch

_trap_illegal_instruction:
    # Set the kernel stack pointer near the top of kernel memory
    li sp, KSTACK_TOP

    tail illegal_instruction_dispatch

_trap_instruction_misaligned:
    li sp, KSTACK_TOP
    
    tail instruction_misaligned_dispatch

_trap_instruction_fault:
    li sp, KSTACK_TOP
    
    tail instruction_fault_dispatch

_trap_breakpoint:
    li sp, KSTACK_TOP
    
    tail breakpoint_dispatch

_trap_load_address_misaligned:
    li sp, KSTACK_TOP
    
    tail load_address_misaligned_dispatch

_trap_load_access_fault:
    li sp, KSTACK_TOP
    
    tail load_access_fault_dispatch

_trap_store_address_misaligned:
    li sp, KSTACK_TOP
    
    tail store_address_misaligned_dispatch

_trap_store_access_fault:
    li sp, KSTACK_TOP
    
    tail store_access_fault_dispatch