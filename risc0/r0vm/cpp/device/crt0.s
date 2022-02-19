.section .text._start;
.globl _start;
_start:
    .option push;
    .option norelax;
    la gp, __global_pointer$;
    .option pop;
    la sp, __stack_init$;
    la a0, __result
    jal ra, __start
    la x10, __result
    lw x1, 0(x10)
    lw x2, 4(x10)
    lw x3, 8(x10)
    lw x4, 12(x10)
    lw x5, 16(x10)
    lw x6, 20(x10)
    lw x7, 24(x10)
    lw x8, 28(x10)
    lw x9, 32(x10)
    ecall

.globl _fault;
_fault:
    sw x0, 1(x0)
