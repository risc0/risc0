# Copyright 2024 RISC Zero, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# riscv32-unknown-elf-gcc -nostdlib loop.s -o loop.bin
# riscv32-unknown-elf-strip loop.bin

.section .text

.global _start
_start:
    # Load loop iteration count word from stdin via `read` syscall
    #
    # NOTE: We don't check for errors since we assume the host will provide
    # correct input
    li      t0, 2         # `ecall::SOFTWARE`
    li      t6, 12        # `Syscall::Read`
    la      a0, count     # Set syscall buffer pointer
    li      a1, 4         # Set syscall buffer length in bytes
    la      a2, sys_read  # Set syscall name C string
    li      a3, 0         # Set read file to `STDIN_FILENO`
    li      a4, 4         # Set read length to 1 word (in bytes)
    ecall                 # `ecall(t0, a0, a1, a2, a3, a4)`

    # Prepare loop.
    li      a4, 0         # Initialize `iter` word
    lw      a5, count     # Load `count` word from `read` result

loop:
    addi    a4, a4, 1     # iter += 1
    bltu    a4, a5, loop  # if (iter < count) goto loop

    # Halt syscall to terminate.
    li      t0, 0         # `ecall::HALT`
    li      a0, 0         # `halt::TERMINATE` with 0 exit code
    la      a1, digest    # Set output digest
    ecall                 # `ecall(t0, a0, a1)`

.section .data

# Memory location for the `read` syscall to write the loop iteration count.
count:
    .align 4
    .word 0

.section .rodata

# SHA2-256 hash of the null journal & assumption
digest:
    .align 4
    .word 0x5c176f83, 0x53f3c062, 0x42651683, 0x340b8b7e, 0x19d2d1f6, 0xae4d7602, 0xb8c606b4, 0xb075b53d

# Null-terminated `read` syscall name
sys_read:
    .align 4
    .asciz "risc0_zkvm_platform::syscall::nr::SYS_READ"
