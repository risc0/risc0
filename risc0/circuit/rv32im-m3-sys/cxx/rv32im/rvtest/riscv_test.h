// Copyright 2025 RISC Zero, Inc.
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

#define __riscv_xlen 32
#define TESTNUM x31

#define RVTEST_RV32U                                                                               \
  .macro init;                                                                                     \
  .endm

#define RVTEST_FAIL unimp;
#define RVTEST_PASS                                                                                \
  li a7, 0;                                                                                        \
  ecall;

#define RVTEST_CODE_BEGIN                                                                          \
  .text;                                                                                           \
  .globl _start;                                                                                   \
  _start:                                                                                          \
  .option push;                                                                                    \
  .option norelax;                                                                                 \
  la gp, __global_pointer$;                                                                        \
  .option pop;

#define RVTEST_CODE_END

#define RVTEST_DATA_BEGIN .data
#define RVTEST_DATA_END
