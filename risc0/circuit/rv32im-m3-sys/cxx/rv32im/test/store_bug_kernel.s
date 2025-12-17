
.section .text
.globl _start;      
_start:
    la x2, tdat; # expands into auipc sp, 0x1 and mv sp,sp
	  sw x2, 8(x2); # this being seems to be what triggers it
    li a7, 0
    ecall

.data
tdat:
   .rept 20
   .word 0xdeadbeef
   .endr
