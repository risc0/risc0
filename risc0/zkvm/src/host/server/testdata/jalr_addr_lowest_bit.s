# Copyright 2026 RISC Zero, Inc.
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

# riscv32-unknown-elf-gcc -nostdlib jalr_addr_lowest_bit.s -o jalr_addr_lowest_bit.bin

# This test shows that JALR ignores the lowest bit of the address

.section .text

.global _start
_start:
    # assembler will load the address of jumped into t0
    la t0, jumped1

    # set lowest bit of t0 to 1
    ori t0, t0, 1

    # jalr to address in t0+0
    jalr ra, t0, 0

jumped1:
    # jalr to jumped2
    # this forces observation of the pc and catch if jalr didn't make it even.
    jalr ra, t0, 8

    # success
    jal exit

jumped2:
    ret

exit:
    # Halt syscall to terminate.
    li      t0, 0         # `ecall::HALT`
    li      a0, 0         # `halt::TERMINATE` with 0 exit code
    la      a1, digest    # Set output digest
    ecall                 # `ecall(t0, a0, a1)`

.section .rodata

# SHA2-256 hash of the null journal & assumption
digest:
    .align 4
    .word 0x5c176f83, 0x53f3c062, 0x42651683, 0x340b8b7e, 0x19d2d1f6, 0xae4d7602, 0xb8c606b4, 0xb075b53d
