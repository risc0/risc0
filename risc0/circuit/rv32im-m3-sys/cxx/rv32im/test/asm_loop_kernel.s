
.section .text
.global _start
_start:
  li a0, 10000000
loop:
  addi a0, a0, -1
  bne a0, x0, loop
  li a7, 0
  ecall

