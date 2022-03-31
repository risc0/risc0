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

.globl memset;
memset:
    move t0, a0  /* Save dest for later return */
    add t1, a0, a2 /* Add size to dest */
    li t6, 8
    bltu a2, t6, bytes_fill /* Dont even bother with alignment if we have < 8 bytes */
align_dest_loop:
    andi t2, a0, 3 /* Get low bits of dest */
    beq t2, x0, dest_aligned /* If it's aligned, jump ahead */
    sb a1, 0(a0) /* Store byte to dest */
    addi a0, a0, 1 /* Bump dest */
    j align_dest_loop
dest_aligned:
    andi a1, a1, 0xff /* Get low byte of fill value */
    slli t2, a1, 8 /* Shift + or it back in */
    or a1, a1, t2
    slli t2, a1, 16 /* Shift + or it again */
    or a1, a1, t2
word_fill:
    sub t2, t1, a0  /* Check how many bytes we have left */
    andi t2, t2, 0xfffffffc /* Clear low 2 bits */
    beq t2, x0, bytes_fill  /* < 4 bytes, dumb loop */
    li t3, 64  /* Load 32 with max size (64 bytes) */
    bltu t2, t3, fancy_jump_s /* If we are moving >= 64, ready to go */
    add a0, a0, t3
    j word_fill_unroll
fancy_jump_s:
    /* Pre-add dest (since loop looks back in memory) */
    add a0, a0, t2
    /* Compute jump addr = word_fill_back - bytes */
    la t3, word_fill_back
    sub t3, t3, t2
    /* Jump! */
    jalr x0, t3, 0
word_fill_unroll:
    sw a1, -64(a0)
    sw a1, -60(a0)
    sw a1, -56(a0)
    sw a1, -52(a0)
    sw a1, -48(a0)
    sw a1, -44(a0)
    sw a1, -40(a0)
    sw a1, -36(a0)
    sw a1, -32(a0)
    sw a1, -28(a0)
    sw a1, -24(a0)
    sw a1, -20(a0)
    sw a1, -16(a0)
    sw a1, -12(a0)
    sw a1, -8(a0)
    sw a1, -4(a0)
word_fill_back:
    j word_fill
bytes_fill:
    beq a0, t1, done /* No bytes, skip loop */
bytes_fill_loop:
    sb a1, 0(a0) /* Store byte to dest */
    addi a0, a0, 1 /* Bump dest */
    bne a0, t1, bytes_fill_loop
done:
    move a0, t0 /* Restore dest addr */
    ret
