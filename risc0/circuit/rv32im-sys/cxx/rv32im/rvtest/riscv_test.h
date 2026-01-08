// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

#define __riscv_xlen 32
#define TESTNUM x31

#define RVTEST_RV32U                                                                               \
  .macro init;                                                                                     \
  .endm

#define RVTEST_FAIL unimp;

// Invoke the terminate/halt ecall. This works for both user-mode and machine-mode ABIs.
#define RVTEST_PASS                                                                                \
  li t0, 0;                                                                                        \
  li a0, 0;                                                                                        \
  la a1, final_digest;                                                                             \
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

#define RVTEST_DATA_BEGIN                                                                          \
  .data;                                                                                           \
  final_digest:                                                                                    \
  .zero 32;

#define RVTEST_DATA_END
