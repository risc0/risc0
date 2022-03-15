# Copyright 2022 Risc0, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

.section .text._start;
.globl _start;
_start:
    .option push;
    .option norelax;
    la gp, __global_pointer$;
    .option pop;
    la sp, __stack_init$;
    la a0, __result
    jal ra, __start
    la x10, __result
    lw x1, 0(x10)
    lw x2, 4(x10)
    lw x3, 8(x10)
    lw x4, 12(x10)
    lw x5, 16(x10)
    lw x6, 20(x10)
    lw x7, 24(x10)
    lw x8, 28(x10)
    lw x9, 32(x10)
    ecall

.globl _fault;
_fault:
    sw x0, 1(x0)
