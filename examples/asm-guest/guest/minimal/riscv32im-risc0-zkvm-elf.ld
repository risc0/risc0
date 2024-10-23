/*
  Copyright 2024 Risc0, Inc.

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

MEMORY {
  ram        : ORIGIN = 0x00000400, LENGTH =  0x001FFC00
  system  (X)  : ORIGIN = 0x07000000, LENGTH =  80M
}

SECTIONS {
  . = 0x400;
  .text 0x400 : ALIGN(4) {
    KEEP (*(.init))
    . = ALIGN(4);
  } >ram
  
  /* There are only two instructions, so just specifying the addr to safely reference */
  .rodata 0x408 : ALIGN(4) {
    *(.rodata*)
  } >ram

  /DISCARD/ : {
    *(.riscv.attributes)
  }
}