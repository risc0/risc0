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

#include <stdint.h>
#include <sys/errno.h>

#include "rv32im/base/constants.h"

#define AT(x) (reinterpret_cast<uint32_t*>(x))
#define CSR(x) AT(CSR_BASE_ADDR)[CSR_ ## x]
#define UREG(x) AT(USER_REGS_ADDR)[REG_ ## x]

inline void mret() {
  asm("mret\n");
}

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

extern "C" void trap_dispatch() {
  // Write some stuff to userspace for tet
  uint32_t* data = reinterpret_cast<uint32_t*>(0xb0000000);
  data[0] = 2;
  data[1]++;

  // Advance PC to skip the instruction  
  uint32_t pc = CSR(MEPC);
  uint16_t low = AT(pc & (~3))[0] >> ((pc % 4) * 8);
  if ((low & 0x3) == 3) {
    CSR(MEPC) = pc + 4;
  } else {
    CSR(MEPC) = pc + 2;
  }

  // Return
  mret();
}

extern "C" void ecall_dispatch() {
  // Check if Linux exit call
  if (UREG(A7) == 93) {
    // If exit return is 0, terminate, otherwise die
    if (UREG(A0) == 0) {
      terminate(0);
    } else {
      die();
    }
  }
    
  // Write some stuff back for the user space program to 
  uint32_t* data = reinterpret_cast<uint32_t*>(0xb0000000);
  data[0] = 1;
  data[1]++;

  // Advance PC (always 4 bytes long since it's an ECALL)
  CSR(MEPC) += 4;

  // Return
  mret();
}

extern "C" void start() {
  // Set up user stack
  UREG(SP) = 0xbffffffc;
  // Set up dispatch table
  CSR(MTECALL) = reinterpret_cast<uint32_t>(ecall_dispatch);
  CSR(MTEXCEPT) = reinterpret_cast<uint32_t>(trap_dispatch);
  // Jump into userland
  mret();
}
