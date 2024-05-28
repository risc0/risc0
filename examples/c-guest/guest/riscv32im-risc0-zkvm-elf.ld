/*
  Copyright 2023 Risc0, Inc.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

OUTPUT_FORMAT("elf32-littleriscv", "elf32-littleriscv", "elf32-littleriscv")
OUTPUT_ARCH(riscv)
ENTRY(_start)

/* Must match risc0/zkvm/platform/src/memory.rs */
/* TODO double check these memory sections, probably not ideal */
MEMORY {
  stack        : ORIGIN = 0x00000400, LENGTH =  8M - 1K
  data    (RW) : ORIGIN = 0x00080000, LENGTH =  24M
  heap         : ORIGIN = 0x02000000, LENGTH =  80M
  prog    (X)  : ORIGIN = 0x07000000, LENGTH =  80M
}

SECTIONS {
  .text : {
    KEEP (*(.init))
    . = ALIGN(4);
    *(.text*)
    . = ALIGN(4);
    *(.rodata*)
    . = ALIGN(4);
    *(.srodata*)
  } >prog

  . = ALIGN(4);

  .data : {
    *(.data .data.*)
    *(.gnu.linkonce.d.*)
    __global_pointer$ = . + 0x800;
    *(.sdata .sdata.* .sdata2.*)
    *(.gnu.linkonce.s.*)
  } >data

  . = ALIGN(4);

  .bss (NOLOAD) : {
    __bss_start = .;
    *(.sbss*)
    *(.gnu.linkonce.sb.*)
    *(.bss .bss.*)
    *(.gnu.linkonce.b.*)
    *(COMMON)
    . = ALIGN(4);
    __bss_end = .;
  } >data

  /* _end marker for zkvm allocator */
  _end = ORIGIN(heap);

  __stack_init$ = ORIGIN(stack) + LENGTH(stack) - 4;
  _stack_top = __stack_init$;


  /DISCARD/ : {
    *(.rel*)
    *(.comment)
    *(.eh_frame)
    *(.riscv.attributes)
  }
}