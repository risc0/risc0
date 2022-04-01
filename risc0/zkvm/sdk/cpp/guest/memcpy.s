# Copyright 2022 Risc0, Inc.
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

.section .text;

.globl memcpy;
memcpy:
    move t0, a0  /* Save dest for later return */
    add t1, a0, a2 /* Add size to dest */
    li t6, 4
    bltu a2, t6, bytes_copy /* Dont even bother with alignment if we have < 4 bytes */
align_dest_loop:
    andi t2, a0, 3 /* Get low bits of dest */
    beq t2, x0, dest_aligned /* If it's aligned, jump ahead */
    lb t3, 0(a1) /* Load byte from source */
    sb t3, 0(a0) /* Store byte to dest */
    addi a0, a0, 1 /* Bump dest */
    addi a1, a1, 1 /* Bump src */
    j align_dest_loop
dest_aligned:
    andi t2, a1, 3 /* Get low bits of src */
    bne t2, x0, bytes_copy /* If dest + src have different alignment just copy bytes */
word_copy:
    sub t2, t1, a0  /* Check how many bytes we have left */
    andi t2, t2, 0xfffffffc /* Clear low 2 bits */
    beq t2, x0, bytes_copy  /* < 4 bytes, dumb loop */
    li t3, 64  /* Load 32 with max size (64 bytes) */
    bltu t2, t3, fancy_jump /* If we are moving < 64, ready to go */
    add a0, a0, t3
    add a1, a1, t3
    j word_copy_unroll
fancy_jump:;
    /* Pre-add src + dest (since loop looks back in memory) */
    add a0, a0, t2
    add a1, a1, t2
    /* Compute jump addr = word_copy_back - 2*bytes */
    slli t2, t2, 1
    la t3, word_copy_back
    sub t3, t3, t2
    /* Jump! */
    jalr x0, t3, 0
word_copy_unroll:
    lw t3, -64(a1)
    sw t3, -64(a0)
    lw t3, -60(a1)
    sw t3, -60(a0)
    lw t3, -56(a1)
    sw t3, -56(a0)
    lw t3, -52(a1)
    sw t3, -52(a0)
    lw t3, -48(a1)
    sw t3, -48(a0)
    lw t3, -44(a1)
    sw t3, -44(a0)
    lw t3, -40(a1)
    sw t3, -40(a0)
    lw t3, -36(a1)
    sw t3, -36(a0)
    lw t3, -32(a1)
    sw t3, -32(a0)
    lw t3, -28(a1)
    sw t3, -28(a0)
    lw t3, -24(a1)
    sw t3, -24(a0)
    lw t3, -20(a1)
    sw t3, -20(a0)
    lw t3, -16(a1)
    sw t3, -16(a0)
    lw t3, -12(a1)
    sw t3, -12(a0)
    lw t3, -8(a1)
    sw t3, -8(a0)
    lw t3, -4(a1)
    sw t3, -4(a0)
word_copy_back:
    j word_copy
bytes_copy:
    beq a0, t1, done /* No bytes, skip loop */
bytes_copy_loop:
    lb t3, 0(a1) /* Load byte from source */
    sb t3, 0(a0) /* Store byte to dest */
    addi a0, a0, 1 /* Bump dest */
    addi a1, a1, 1 /* Bump src */
    bne a0, t1, bytes_copy_loop
done:
    move a0, t0 /* Restore dest addr */
    ret
