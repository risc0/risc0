/*
  Copyright 2026 Risc0, Inc.

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
MEMORY {
  stack        : ORIGIN = 0x00000400, LENGTH =  0x001FFC00
  ram          : ORIGIN = 0x00200800, LENGTH =  0x0BDFF800
  system  (X)  : ORIGIN = 0x0C000000, LENGTH =  0xF4000000
}

SECTIONS {
  . = 0x00200800;
  .text 0x00200800 : ALIGN(4) {
    KEEP (*(.init))
    . = ALIGN(4);
    *(.text*)
    . = ALIGN(4);
    *(.rodata*)
    . = ALIGN(4);
    *(.srodata*)
  } >ram

  . = ALIGN(4);

  .data : ALIGN(4) {
    *(.data .data.*)
    *(.gnu.linkonce.d.*)
    __global_pointer$ = . + 0x800;
    *(.sdata .sdata.* .sdata2.*)
    *(.gnu.linkonce.s.*)
  } >ram

  . = ALIGN(4);

  .bss (NOLOAD) : ALIGN(4) {
    __bss_start = .;
    *(.sbss*)
    *(.gnu.linkonce.sb.*)
    *(.bss .bss.*)
    *(.gnu.linkonce.b.*)
    *(COMMON)
    . = ALIGN(4);
    __bss_end = .;
  } >ram

  /* _end marker for zkvm allocator */
  _end = .;

  /* Stack top marker, used to initialize the stack pointer */
  __stack_init$ = 0x00200400;
  _stack_top = __stack_init$;


  /DISCARD/ : {
    *(.rel*)
    *(.comment)
    *(.eh_frame)
    *(.riscv.attributes)
  }
}