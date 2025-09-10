# Tests edge case in jalr spec for misaligned addresses
.section .text
.global rvtest_entry_point

.equ illegal_insn, 0x00000000 # assumption: emulator should panic when it hits this

rvtest_entry_point:
    la x10, target      # load address of target, which is aligned
    addi x10, x10, 1    # jalr should round this down and still jump to target
    jalr x11, x10, 0
    j fail              # ensure failure in case we somehow fall through

.align 4
target:
    j pass

fail:
    .word illegal_insn

pass:
    li t0, 0
    li a0, 0
    li a1, 1024
    ecall
