
.section .text
.global _start
_start:
  /* Load the global pointer from the place the linker put it */
  /* Note: we definitely don't want this relaxed since the GP is invalid */
  .option push
  .option norelax
  la gp, __global_pointer$
  .option pop
  /* Set the kernel stack pointer near the top of kernel memory */
  li sp, 0xfff00000
  /* Jump to kernel start at the C level */
  call start

