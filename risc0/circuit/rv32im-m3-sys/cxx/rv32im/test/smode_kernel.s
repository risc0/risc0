.section .text
.global _start
_start:
  la t0, onTrap
  csrw stvec, t0
  unimp
  jal exitOk

exitOk:
  li a0, 0
  li a1, 0
  ecall

.align 4
onTrap:
  csrr t0, sepc
  addi t0, t0, 4
  csrw sepc, t0
  sret




