/*
  Copyright 2022 Risc0, Inc.

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
EXTERN(__start)

/* Must match risc0/zkvm/platform/memory.h */
MEMORY {
  stack        : ORIGIN = 0x00000000, LENGTH =  256K
  data    (RW) : ORIGIN = 0x00040000, LENGTH =  256K
  heap         : ORIGIN = 0x00080000, LENGTH =    1M
  input        : ORIGIN = 0x00180000, LENGTH =  256K
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

  __heap_start = ORIGIN(heap);
  __heap_end = __heap_start + LENGTH(heap);
  __heap_size = LENGTH(heap);

  __stack_init$ = ORIGIN(stack) + LENGTH(stack) - 4;

  /DISCARD/ : {
    *(.rel*)
    *(.comment)
    *(.eh_frame)
    *(.riscv.attributes)
  }
}
