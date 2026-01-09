// Copyright 2026 RISC Zero, Inc.
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

#include <stdint.h>
#include <sys/errno.h>

#include "rv32im/base/constants.h"

inline void die() {
  asm("unimp\n");
}

// Implement machine mode ECALLS

inline void terminate(uint32_t val) {
  register uintptr_t a0 asm("a0") = val;
  register uintptr_t a7 asm("a7") = 0;
  asm volatile("ecall\n"
               :                  // no outputs
               : "r"(a0), "r"(a7) // inputs
               :                  // no clobbers
  );
}

inline void do_poseidon2(uint32_t state, uint32_t bufIn, uint32_t bufOut, uint32_t countAndBits) {
  register uintptr_t a0 asm("a0") = state;
  register uintptr_t a1 asm("a1") = bufIn;
  register uintptr_t a2 asm("a2") = bufOut;
  register uintptr_t a3 asm("a3") = countAndBits;
  register uintptr_t a7 asm("a7") = 3;
  asm volatile("ecall\n"
               :                                             // no outputs
               : "r"(a0), "r"(a1), "r"(a2), "r"(a3), "r"(a7) // inputs
               :                                             // no clobbers
  );
}

void test_p2_basic() {
  static constexpr uint32_t bufIn[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  static constexpr uint32_t goal[8] = {
      1749308481, 879447913, 499502012, 1842374203, 1869354733, 71489094, 19273002, 690566044};
  uint32_t bufOut[8];
  do_poseidon2((uint32_t)0, (uint32_t)bufIn, (uint32_t)bufOut, PFLAG_IS_ELEM | 1);
  for (size_t i = 0; i < 8; i++) {
    if (bufOut[i] != goal[i]) {
      die();
    }
  }
}

void test_p2_short() {
  static constexpr uint32_t bufIn[8] = {
      0x10000, 0x30002, 0x50004, 0x70006, 0x90008, 0xB000A, 0xD000C, 0xF000E};
  static constexpr uint32_t goal[8] = {
      1749308481, 879447913, 499502012, 1842374203, 1869354733, 71489094, 19273002, 690566044};
  uint32_t bufOut[8];
  do_poseidon2((uint32_t)0, (uint32_t)bufIn, (uint32_t)bufOut, 1);
  for (size_t i = 0; i < 8; i++) {
    if (bufOut[i] != goal[i]) {
      die();
    }
  }
}

void test_p2_long() {
  static uint32_t bufIn[32] = {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15,
                               16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};
  static constexpr uint32_t goal[8] = {
      1257374621, 1235708219, 1590109606, 1571950965, 936452277, 615799448, 844422484, 1109152478};
  uint32_t bufOut[8];
  do_poseidon2((uint32_t)0, (uint32_t)bufIn, (uint32_t)bufOut, PFLAG_IS_ELEM | 2);
  for (size_t i = 0; i < 8; i++) {
    if (bufOut[i] != goal[i]) {
      die();
    }
  }
}

void test_p2_continue() {
  static uint32_t bufIn[32] = {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15,
                               16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};
  static constexpr uint32_t goal[8] = {
      1257374621, 1235708219, 1590109606, 1571950965, 936452277, 615799448, 844422484, 1109152478};
  uint32_t bufOut[8];
  uint32_t bufState[8] = {
      0,
  };
  do_poseidon2((uint32_t)bufState, (uint32_t)bufIn, (uint32_t)bufOut, PFLAG_IS_ELEM | 1);
  do_poseidon2((uint32_t)bufState, (uint32_t)(bufIn + 16), (uint32_t)bufOut, PFLAG_IS_ELEM | 1);
  for (size_t i = 0; i < 8; i++) {
    if (bufOut[i] != goal[i]) {
      die();
    }
  }
}

void test_p2_check() {
  static constexpr uint32_t bufIn[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  static constexpr uint32_t goal[8] = {
      1749308481, 879447913, 499502012, 1842374203, 1869354733, 71489094, 19273002, 690566044};
  do_poseidon2((uint32_t)0, (uint32_t)bufIn, (uint32_t)goal, PFLAG_CHECK_OUT | PFLAG_IS_ELEM | 1);
}

extern "C" void start() {
  test_p2_basic();
  test_p2_short();
  test_p2_long();
  test_p2_continue();
  test_p2_check();
  terminate(0);
}
