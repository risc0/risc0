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

// Handle atomic instructions, return cause of error
// (or MCAUSE_NONE on success)
uint32_t handleInstAtomic(uint32_t inst) {
  // Extract parts of the instruction
  uint32_t rs1 = (inst >> 15) & 0x1f;
  uint32_t rs2 = (inst >> 20) & 0x1f;
  uint32_t rd = (inst >> 7) & 0x1f;
  uint32_t func3 =  (inst >> 12) & 0x7;
  uint32_t op = (inst >> 27);
  // If 64-bit, fail
  if (func3 != 2) {
    return MCAUSE_ILLEGAL_INSTRUCTION;
  }
  // Get the address
  uint32_t addr = AT(USER_REGS_ADDR)[rs1];
  // If it's not aligned, fail
  if (addr % 4 != 0) {
    if (op == 0b00010) {
      return MCAUSE_LOAD_ADDRESS_MISALIGNED;
    } else {
      return MCAUSE_STORE_ADDRESS_MISALIGNED;
    }
  }
  // Get the value at the address
  uint32_t val = AT(addr)[0];
  uint32_t in = AT(USER_REGS_ADDR)[rs2];
  // To make LR/SC work, we need to track state between instructions
  static bool active = false;
  static uint32_t lastAddr = 0;
  // Process instruction
  if (op == 0b00010) { // LR, special case
    if (rs2 != 0) {
      return MCAUSE_ILLEGAL_INSTRUCTION;
    }
    active = true;
    lastAddr = addr;
    if (rd != 0) {
      AT(USER_REGS_ADDR)[rd] = val;
    }
    return MCAUSE_NONE;
  }
  if (op == 0b00011) { // SC, special case
    bool invalid = !active || lastAddr != addr;
    if (rd != 0) {
      AT(USER_REGS_ADDR)[rd] = invalid;
    }
    if (!invalid) {
      AT(addr)[0] = in;
    }
    active = false;
    return MCAUSE_NONE;
  }
  // Write old value
  if (rd != 0) {
    AT(USER_REGS_ADDR)[rd] = val;
  }
  // Apply op
  switch(op) {
    case 0b00001: // SWAP
      val = in; break;
    case 0b00000: // ADD
      val += in; break;
    case 0b00100: // XOR
      val ^= in; break;
    case 0b01100: // AND
      val &= in; break;
    case 0b01000: // OR
      val |= in; break;
    case 0b10000: // MIN
      val = (int32_t(val) < int32_t(in)) ? val : in; break;
    case 0b10100: // MAX
      val = (int32_t(val) < int32_t(in)) ? in : val; break;
    case 0b11000: // UMIN
      val = (val < in) ? val : in; break;
    case 0b11100: // UMAX
      val = (val < in) ? in : val; break;
    default:
      return MCAUSE_ILLEGAL_INSTRUCTION;
  }
  // Update value
  AT(addr)[0] = val;
  return MCAUSE_NONE;
}

uint32_t handleInstMemory(uint32_t inst) {
  uint32_t func3 =  (inst >> 12) & 0x7;
  switch(func3) {
    case 0: // Normal fence
      return MCAUSE_NONE;
    case 1: // fence.i
      die();  // TODO
  }
  return MCAUSE_ILLEGAL_INSTRUCTION;
}

// Process an instruction, return error (or MCAUSE_NONE on success)
uint32_t handleInst(uint32_t inst) {
  switch((inst >> 2) & 0x1f) {
    case(0b01011):
      return handleInstAtomic(inst);
    case(0b00011): 
      return handleInstMemory(inst);
    default:
      // Unhandled instruction, die as unimplemented 
      die();
  }
  return MCAUSE_NONE;  // Unreachable
}

// Fetch and decode compressed instructions, forward PC
uint32_t fetch(uint32_t& pc) {
  // Load low part of instructions
  uint32_t inst = *reinterpret_cast<uint16_t*>(pc);
  if (inst & 3 == 3) {
    // Uncompressed, add in high part
    inst |= uint32_t(*reinterpret_cast<uint16_t*>(pc + 2)) << 16;
    pc += 4;
  } else {
    // Compressed, lookup
    inst = AT(COMPRESSED_INST_LOOKUP_ADDR)[inst]; 
    pc += 2;
  }
  return inst;
}

extern "C" void trap_dispatch() {
  uint32_t pc = CSR(MEPC);
  uint32_t inst = fetch(pc);
  uint32_t ret = handleInst(inst);
  if (ret != MCAUSE_NONE) {
    die();  // For now, just fail if it's invalid
  }
  CSR(MEPC) = pc;
  mret();
}

extern "C" void ecall_dispatch() {
  terminate(0);
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
