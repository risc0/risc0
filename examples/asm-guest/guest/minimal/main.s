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

.section .text._start
.global _start
_start:
  # ECALL halt (register defaults to 0, so no need to explicitly set)
  # addi t0, x0, 0
  # Clear a0 register as HALT_TERMINATE is 0.
  # addi a0, x0, 0
  # Load out state into a1
  # la a1, hash
  
  # This is to reduce the la instruction from 2 to 1, given the linker script puts the hash address
  # statically at 0x408 which is within the 12 bit immediate value and doesn't require relative
  # addressing.
  # The address 0x408 is encoded as the memory starts at 0x400 and the program is two instructions.
  addi a1,zero,0x408
  ecall
  # Assumes that the `sys_halt` ecall will stop execution, and not continuing executing. Should
  # put an `unimp` instruction after here to be safe against a malicious host in practice.

.section .rodata
hash:
  # Sha256 digest of empty commit and assumption
  .word 0x5C176F83, 0x53F3C062, 0x42651683, 0x340B8B7E, 0x19D2D1F6, 0xAE4D7602, 0xB8C606B4, 0xB075B53D
