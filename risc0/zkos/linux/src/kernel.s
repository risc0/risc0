// Copyright 2024 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

.equ KSTACK_TOP, 0xfff00000
.equ ECALL_DISPATCH, 0xffff1000

.section .text
.global _start
_start:
    # Load the global pointer from the place the linker put it
    # Note: we definitely don't want this relaxed since the GP is invalid
    .option push
    .option norelax
    la gp, __global_pointer$
    .option pop

    # Set the kernel stack pointer near the top of kernel memory
    li sp, KSTACK_TOP

    # Initialize the ecall dispatch address
    la a0, _ecall_dispatch
    li a1, ECALL_DISPATCH
    sw a0, 0(a1)

    tail kstart

_ecall_dispatch:
    # Set the kernel stack pointer near the top of kernel memory
    li sp, KSTACK_TOP

    tail ecall_dispatch

