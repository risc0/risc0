
.section .text
.global _start
_start:
  li a0, 2
loop:
  addi a0, a0, -1
  bne a0, x0, loop
  li a7, 0
  la a1, loop 
  lw a2, (a1)
  ecall

