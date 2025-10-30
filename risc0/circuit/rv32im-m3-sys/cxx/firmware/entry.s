.section .text
.global _start
_start:
  /* Load the global pointer from the place the linker put it */
  /* Note: we definitely don't want this relaxed since the GP is invalid */
  .option push
  .option norelax
  la gp, __global_pointer$
  .option pop
  /* Set the kernel stack pointer near the top of firmware memory */
  li sp, 0xff000000
  /* Jump to kernel start at the C level */
  call start

.extern onTrap
.extern onEcall

.global _trapEntry
_trapEntry:
  call onTrap 
  mret

.global _ecallEntry
_ecallEntry:
  call onEcall
  mret

