OUTPUT_FORMAT("elf32-littleriscv", "elf32-littleriscv", "elf32-littleriscv")
OUTPUT_ARCH(riscv)
ENTRY(_start)
EXTERN(__start)

/* Must match risc0/r0vm/platform/memory.h */
MEMORY {
  stack        : ORIGIN = 0x00000000, LENGTH =  256K
  data    (RW) : ORIGIN = 0x00040000, LENGTH =  256K
  heap         : ORIGIN = 0x00080000, LENGTH =  1280K
  gpio         : ORIGIN = 0x001C0000, LENGTH =  256K
  prog    (X)  : ORIGIN = 0x00200000, LENGTH =    1M
  sha          : ORIGIN = 0x00300000, LENGTH =  256K
  wom          : ORIGIN = 0x00340000, LENGTH =  768K
}

SECTIONS {
  .text : {
    *(.text._start)
    *(.text.__start)
    *(.text*)
    *(.rodata*)
    *(.srodata*)
  } >prog

  .data : {
    *(.data .data.*)
    *(.gnu.linkonce.d.*)
    __global_pointer$ = . + 0x800;
    *(.sdata .sdata.* .sdata2.*)
    *(.gnu.linkonce.s.*)
  } >data

  . = ALIGN(4);
  .bss (NOLOAD) :  {
    __bss_begin = .;
    *(.sbss*)
    *(.gnu.linkonce.sb.*)
    *(.bss .bss.*)
    *(.gnu.linkonce.b.*)
    *(COMMON)
    . = ALIGN(4);
    __result = .;
    /* Result is 9 words * 4 = 36 bytes, 8 words for output, and 1 word for output size*/
    __bss_end = . + 36;
  } >data
  __bss_size = __bss_end - __bss_begin;
  __stack_init$ = ORIGIN(stack) + LENGTH(stack) - 4;

  /DISCARD/ : {
    *(.rel*)
    *(.comment)
    *(.eh_frame)
    *(.riscv.attributes)
  }
}
