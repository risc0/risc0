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

inline void die() {
  asm("unimp\n");
}

#define AT(x) (reinterpret_cast<uint32_t*>(x))
#define CSR(x) AT(CSR_BASE_ADDR)[CSR_ ## x]
#define UREG(x) AT(USER_REGS_ADDR)[REG_ ## x]

// Implement machine mode ECALLS
inline void terminate(uint32_t a0Val, uint32_t a1Val) {
  register uintptr_t a0 asm("a0") = a0Val;
  register uintptr_t a1 asm("a0") = a1Val;
  register uintptr_t a7 asm("a7") = 0;
  asm volatile("ecall\n"
               :                  // no outputs
               : "r"(a0), "r"(a1), "r"(a7) // inputs
               :                  // no clobbers
  );
}

inline uint32_t hostRead(uint32_t fd, char* buf, uint32_t len) {
  register uintptr_t a0 asm("a0") = fd;
  register uintptr_t a1 asm("a1") = reinterpret_cast<uint32_t>(buf);
  register uintptr_t a2 asm("a2") = len;
  register uintptr_t a7 asm("a7") = 1;
  asm volatile("ecall\n"
               : "+r"(a0)                           // outputs
               : "r"(a1), "r"(a2), "r"(a7) // inputs
               : "memory"                           // no clobbers
  );
  return a0;
}

inline uint32_t hostWrite(uint32_t fd, const char* buf, uint32_t len) {
  register uintptr_t a0 asm("a0") = fd;
  register uintptr_t a1 asm("a1") = reinterpret_cast<uint32_t>(buf);
  register uintptr_t a2 asm("a2") = len;
  register uintptr_t a7 asm("a7") = 2;
  asm volatile("ecall\n"
               : "+r"(a0)                           // outputs
               : "r"(a1), "r"(a2), "r"(a7) // inputs
               :                                    // no clobbers
  );
  return a0;
}

// Very primitive logging system
struct LogHelper {
  char* buf;
  LogHelper() {
    buf = reinterpret_cast<char*>(0xf1000000);
  }
  LogHelper& operator<<(const char* str) {
    while(*str) {
      *buf++ = *str++;
    }
    return *this;
  }
  LogHelper& operator<<(uint32_t val) {
    for (size_t i = 8; i-->0; ) {
      *buf++ = "0123456789abcdef"[(val >> (4 * i)) & 0xf];
    }
    return *this;
  }
  char* start() { return reinterpret_cast<char*>(0xf1000000); }
  uint32_t size() { return buf - reinterpret_cast<char*>(0xf1000000); }

};

#define LOG(level, ...) do { \
  LogHelper log; \
  log << __VA_ARGS__; \
  hostWrite(level, log.start(), log.size()); \
} while(0)

#define FATAL(...) do { \
  LOG(0, __VA_ARGS__); \
  die(); \
} while(0)

uint32_t causeAccessFault(uint32_t aType) {
  switch(aType) {
    case ACCESS_FETCH: return MCAUSE_INSTRUCTION_ACCESS_FAULT;
    case ACCESS_LOAD: return MCAUSE_LOAD_ACCESS_FAULT;
    case ACCESS_STORE: return MCAUSE_STORE_ACCESS_FAULT;
  }
  FATAL("Invalid access code");
  return 0;
}

uint32_t causePageFault(uint32_t aType) {
  switch(aType) {
    case ACCESS_FETCH: return MCAUSE_INSTRUCTION_PAGE_FAULT;
    case ACCESS_LOAD: return MCAUSE_LOAD_PAGE_FAULT;
    case ACCESS_STORE: return MCAUSE_STORE_PAGE_FAULT;
  }
  FATAL("Invalid access code");
  return 0;
}

uint32_t translate(uint32_t& addr, uint32_t aType) {
  if ((CSR(SATP) & 0x80000000) == 0) {
    return MCAUSE_NONE;
  }
  uint32_t a = CSR(SATP) << 12;
  uint32_t smode = CSR(MEMODE);
  uint32_t sum = (CSR(SSTATUS) >> 18) & 1;
  uint32_t mxr = (CSR(SSTATUS) >> 19) & 1;
  uint32_t vPage = addr >> 12;
  uint32_t i, xwr, pte, pteAddr;
  for (i = 2; i-- > 0;) {
    pteAddr = a + ((vPage >> (10 * i)) & 0x3ff)*4;
    if (pteAddr >= FIRMWARE_START_ADDR) { return causeAccessFault(aType); }
    pte = AT(pteAddr)[0];
    if ((pte & 1) == 0) {
      // LOG(0, "NOT VALID");
      return causePageFault(aType); 
    }
    xwr = (pte >> 1) & 7;
    if (xwr == 2 || xwr == 6) { 
      // LOG(0, "Reserved mode");
      return causePageFault(aType); 
    } 
    a = (pte << 2) & 0xfffff000;
    if (xwr != 0) break;
  }
  if (!xwr) { 
    // LOG(0, "NOT XWR mode");
    return causePageFault(aType); 
  }
  if (i == 1) {
    if (((pte >> 10) & 0x3ff) != 0) {
      // LOG(0, "Unaligned mega page");
      return causePageFault(aType);
    }
    a |= ((vPage & 0x3ff) << 12);
  }
  uint32_t u = (pte >> 4) & 1;
  uint32_t x = (pte >> 3) & 1;
  uint32_t w = (pte >> 2) & 1;
  uint32_t r = (pte >> 1) & 1;
  if (mxr && x) { r = 1; }
  if (!u && !smode) { return causePageFault(aType); }
  if (u && !sum && smode) { return causePageFault(aType); }
  if ((aType == ACCESS_FETCH && !x) ||
      (aType == ACCESS_LOAD && !r) ||
      (aType == ACCESS_STORE && !w)) {
    // LOG(0, "Invalid access: u = " << u << ", smode = " << smode << ", mxr = " << mxr << ", u = " << u << ", xwr = " << xwr);
    return causePageFault(aType); 
  }
  pte |= (1 << 6);  // Set A bit always
  if (aType == ACCESS_STORE) { pte |= (1 << 7); } // Set D if write
  AT(pteAddr)[0] = pte;
  addr = a | (addr & 0xfff);
  return MCAUSE_NONE;
}

// Helper to save some redundant work
uint32_t forwardInvalid() {
  CSR(STVAL) = CSR(MTVAL);
  return MCAUSE_ILLEGAL_INSTRUCTION;
}

// Interpret CSR rs1  as reg or imm
uint32_t expandCsrVal(uint32_t reg, uint32_t isImm) {
  if (isImm) {
    if (reg & 0x10) {
      return 0xfffffff0 | reg;
    } else {
      return reg;
    }
  } else {
    return AT(USER_REGS_ADDR)[reg];
  }
}

void invalidateCache() {
  CSR(MCLEARCACHE) = 1;
}


void recomputeVmInfo() {
  uint32_t orig = CSR(MVINFO);
  uint32_t cur = (CSR(SATP) & 0x803fffff) |
    ((CSR(SSTATUS) & 0x000c0000) << 11);
  if (orig != cur) {
    // LOG(0, "NEW VINFO: " << cur);
    CSR(MVINFO) = cur;
    invalidateCache();
  }
}

void supervisorTrap(uint32_t cause) {
  // Setup to return to supervisor mode
  CSR(SCAUSE) = cause;
  //LOG(0, "Setting SCAUSE = " << CSR(SCAUSE));
  //LOG(0, "STVAL = " << CSR(STVAL));
  uint32_t cur = CSR(SSTATUS);
  // Extract SIE bit
  uint32_t sie = (cur >> 1) & 1;
  // Clear SPIE, SIE, and SPP)
  cur &= 0xfffffedd;
  // Make SPIE = SIE
  cur |= (sie << 5);
  // Set SPP
  cur |= CSR(MEMODE) << 8;
  CSR(SSTATUS) = cur;
  // Set new mode to supervisor
  CSR(MEMODE) = MODE_SUPERVISOR;
  // Set supervisor return to original trap locaion
  CSR(SEPC) = CSR(MEPC);
  // Make mret point at STVEC
  CSR(MEPC) = CSR(STVEC);
  // LOG(0, "New mode = " << CSR(MEMODE));
  recomputeVmInfo();
}

uint32_t doSRET() {
  // LOG(0, "Doing SRET");
  uint32_t cur = CSR(SSTATUS);
  // Extract SPIE bit
  uint32_t spie = (cur >> 5) & 1;
  // Extract SPP bit
  uint32_t newMode = (cur >> 8) & 1;
  // Clear SPIE, SIE, and SPP)
  cur &= 0xfffffedd;
  // Make SIE = SPIE
  cur |= (spie << 1);
  // Set SPIE
  cur |= (1 << 5);
  // Update SSTATUS
  CSR(SSTATUS) = cur;
  CSR(MEPC) = CSR(SEPC);
  CSR(MEMODE) = newMode;
  return MCAUSE_SRET;
}

// Handle system instructions
uint32_t handleInstSystem(uint32_t inst) {
  if (inst == 0x10500073) {
    // TODO: this is wait for interrupt, maybe actual skip ahead?
    return MCAUSE_NONE;  // No-op
  }
  if (inst == 0x10200073) {
    return doSRET();
  }
  uint32_t csrt = (inst >> 12) & 3;
  if (csrt == 0) {
    if ((inst & (~0x01ff8000)) == 0x12000073) {
      // SFENCE.VMA
      invalidateCache();
      return MCAUSE_NONE;  // No-op
    }
    return forwardInvalid();
  }
  // Bascially, a CSR intruciton, deocde
  uint32_t rd = (inst >> 7) & 0x1f;
  uint32_t isImm = (inst >> 14) & 1;
  uint32_t rs1 = (inst >> 15) & 0x1f;
  uint32_t csr = (inst >> 20);
  uint32_t newVal = expandCsrVal(rs1, isImm);;
  // Check permissions
  if (csrt == 1 || rs1 != 0) {
    // We are doing a write, if R0 induce trap
    if ((inst & 0xc0000000) == 0xc0000000) {
      return forwardInvalid();
    }
  }
  uint32_t allowedMode = (inst >> 28) & 3;
  if (allowedMode > CSR(MEMODE)) {
    return forwardInvalid();
  }
  // Quickly fix time if needed
  switch(csr) {
    case CSR_CYCLE:
    case CSR_TIME:
    case CSR_INSTRET:
      AT(CSR_BASE_ADDR)[csr] = CSR(MTIME);
      break;
    case CSR_CYCLEH:
    case CSR_TIMEH:
    case CSR_INSTRETH:
      AT(CSR_BASE_ADDR)[csr] = CSR(MTIMEH);
      break;
  }
  // Load current value
  uint32_t curVal = AT(CSR_BASE_ADDR)[csr];
  if (rd != 0) {
    // Write to rd
    AT(USER_REGS_ADDR)[rd] = curVal;
  }
  uint32_t prevVal = curVal;
  // Modify value as per instruction type
  switch(csrt) {
    case 1: curVal = newVal; break;
    case 2: curVal |= newVal; break;
    case 3: curVal &= newVal; break;
    default:
      return forwardInvalid();
  }
  // Store new value
  AT(CSR_BASE_ADDR)[csr] = curVal;
  // If not modified, we are done
  if (prevVal == curVal) { return MCAUSE_NONE; }
  switch(csr) {
    // Special CSR handling goes here
    case CSR_SATP:
      recomputeVmInfo();
      break;
    case CSR_SSTATUS:
      recomputeVmInfo();
      break;
    default:
      break;
  }
  return MCAUSE_NONE;
}

// Handle atomic instructions
uint32_t handleInstAtomic(uint32_t inst) {
  // Extract parts of the instruction
  uint32_t rs1 = (inst >> 15) & 0x1f;
  uint32_t rs2 = (inst >> 20) & 0x1f;
  uint32_t rd = (inst >> 7) & 0x1f;
  uint32_t func3 =  (inst >> 12) & 0x7;
  uint32_t op = (inst >> 27);
  // If 64-bit, fail
  if (func3 != 2) {
    return forwardInvalid();
  }
  // Get the address
  uint32_t addr = AT(USER_REGS_ADDR)[rs1];
  // If it's not aligned, fail
  if (addr % 4 != 0) {
    CSR(STVAL) = addr;
    if (op == 0b00010) {
      return MCAUSE_LOAD_ADDRESS_MISALIGNED;
    } else {
      return MCAUSE_STORE_ADDRESS_MISALIGNED;
    }
  }
  // Translate, if it's not legit, fail
  uint32_t cause = translate(addr, op == 0b00010 ? ACCESS_LOAD : ACCESS_STORE);
  if (cause != MCAUSE_NONE) {
    CSR(STVAL) = addr;
    return cause;
  }
  uint32_t val = AT(addr)[0];
  uint32_t in = AT(USER_REGS_ADDR)[rs2];
  static bool active = false;
  static uint32_t lastAddr = 0;
  // Process instruction
  if (op == 0b00010) { // LR
    if (rs2 != 0) {
      return forwardInvalid();
    }
    active = true;
    lastAddr = addr;
    if (rd != 0) {
      AT(USER_REGS_ADDR)[rd] = val;
    }
    return MCAUSE_NONE;
  }
  if (op == 0b00011) { // SC
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

  if (rd != 0) {
    AT(USER_REGS_ADDR)[rd] = val;
  }
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
      // Invalid instruction!
      return forwardInvalid();
  }
  AT(addr)[0] = val;
  return MCAUSE_NONE;
}

uint32_t handleMiscMemory(uint32_t inst) {
  uint32_t func3 =  (inst >> 12) & 0x7;
  switch(func3) {
    case 0: // Normal fence
      return MCAUSE_NONE;
    case 1: // fence.i
      invalidateCache();
      return MCAUSE_NONE;
  }
  return forwardInvalid();
}

uint32_t handleLoad(uint32_t inst) {
  uint32_t func3 =  (inst >> 12) & 0x7;
  if (func3 == 3 || func3 > 5) {
    // Not a valid load subtype
    return forwardInvalid();
  }
  uint32_t rs1 = (inst >> 15) & 0x1f;
  uint32_t immI = ((inst >> 31) * 0xfffff000) + (inst >> 20);
  uint32_t addr = AT(USER_REGS_ADDR)[rs1] + immI;
  // LOG(0, "func3 = " << func3 << ", addr = " << addr);
  // If unaligned, forward as invalid alignment
  switch(func3) {
    case 1: // LH
    case 5: // LHU
      if (addr % 2 != 0) {
        // LOG(0, "MISALIGNED");
        CSR(STVAL) = addr;
        //CSR(MDEBUG) = true;
        return MCAUSE_LOAD_ADDRESS_MISALIGNED;
      }
      break;
    case 2:
      if (addr % 4 != 0) {
        // LOG(0, "MISALIGNED");
        CSR(STVAL) = addr;
        //CSR(MDEBUG) = true;
        return MCAUSE_LOAD_ADDRESS_MISALIGNED;
      }
      break;
  }
  // OK, data is aligned, try to translate VM address
  // LOG(0, "MEPC = " << CSR(MEPC));
  // LOG(0, "Attempting to translate: " << addr);
  // LOG(0, "Mode = " << CSR(MEMODE) << ", SSTATUS = " << CSR(SSTATUS));
  uint32_t cause = translate(addr, ACCESS_LOAD);
  if (cause != MCAUSE_NONE) {
    CSR(STVAL) = addr;
    // LOG(0, "Val = " << addr << ", cause = " << cause);
    return cause;
  }
  // Hmm, load seems to have been valid, prover is byzantine
  // disallow proof
  die();
  return MCAUSE_NONE;
}

uint32_t handleStore(uint32_t inst) {
  uint32_t func3 =  (inst >> 12) & 0x7;
  if (func3 > 3) {
    // Not a valid load subtype
    return forwardInvalid();
  }
  uint32_t rs1 = (inst >> 15) & 0x1f;
  uint32_t rd = (inst & 0x00000f80) >> 7;
  uint32_t func7 = (inst & 0xfe000000) >> 25;
  uint32_t topBit = (inst & 0x80000000) >> 31;
  uint32_t immS = (topBit * 0xfffff000) | (func7 << 5) | rd;
  uint32_t addr = AT(USER_REGS_ADDR)[rs1] + immS;
  // LOG(0, "func3 = " << func3 << ", addr = " << addr);
  // If unaligned, forward as invalid alignment
  switch(func3) {
    case 1: // SH
      if (addr % 2 != 0) {
        // LOG(0, "MISALIGNED");
        CSR(STVAL) = addr;
        return MCAUSE_LOAD_ADDRESS_MISALIGNED;
      }
      break;
    case 2:  // SW
      if (addr % 4 != 0) {
        // LOG(0, "MISALIGNED");
        CSR(STVAL) = addr;
        return MCAUSE_LOAD_ADDRESS_MISALIGNED;
      }
      break;
  }
  // OK, data is aligned, try to translate VM address
  // LOG(0, "MEPC = " << CSR(MEPC));
  // LOG(0, "Attempting to translate: " << addr);
  // LOG(0, "Mode = " << CSR(MEMODE) << ", SSTATUS = " << CSR(SSTATUS));
  uint32_t cause = translate(addr, ACCESS_STORE);
  if (cause != MCAUSE_NONE) {
    CSR(STVAL) = addr;
    // LOG(0, "Val = " << addr << ", cause = " << cause);
    return cause;
  }
  // Hmm, load seems to have been valid, prover is byzantine
  // disallow proof
  die();
  return MCAUSE_NONE;
}

// Process an instruction after fetch + translation to full width
// Return trap cauase if we want to forward trap to supervisor
// STVAL should be set directly
uint32_t handleInst(uint32_t inst) {
  switch((inst >> 2) & 0x1f) {
    case(0b00000):
      return handleLoad(inst);
    case(0b01000):
      return handleStore(inst);
    case(0b00011):  // Fence, ignore
      return handleMiscMemory(inst);
    case(0b01011):
      return handleInstAtomic(inst);
    case(0b11100):
      return handleInstSystem(inst);
    default:
      // TODO: Handle all the cases
      FATAL("Unimplemented: inst = " << inst);
  }
  return MCAUSE_NONE;
}

// On nondeterministic trap, process instruction and
// 1) Handle it in firmware + return
// 2) Forward trap to supervisor
// 3) Die (i.e. nondet trap on valid instruction, etc)
extern "C" void onTrapInst() {
  uint32_t inst = CSR(MTVAL);
  uint32_t instLen;
  uint32_t instLong;
  if ((inst & 3) == 3) {
    instLen = 4;
    instLong = inst;
  } else {
    instLen = 2;
    instLong = AT(COMPRESSED_INST_LOOKUP_ADDR)[inst];
  }
  uint32_t mcause = handleInst(instLong);
  uint64_t& time = *reinterpret_cast<uint64_t*>(&CSR(MTIME));
  if (mcause == MCAUSE_NONE) {
    // Success, advance time, bump PC, and continue
    time++;
    CSR(MEPC) += instLen;
  } else if (mcause != MCAUSE_SRET) {
    // If it failed, forward to supervisor
    supervisorTrap(mcause);
  }
  // Update countdown
  uint64_t& timer = *reinterpret_cast<uint64_t*>(&CSR(MTIMER));
  uint32_t sie = (CSR(SSTATUS) >> 1) & 1;
  uint32_t mode = CSR(MEMODE);
  uint32_t ie = (mode == MODE_USER || sie) && (CSR(SIE) & 0x20);
  uint32_t countdown = 0x7fffffff;
  if (ie) {
    if (time >= timer) {
      CSR(MCOUNTDOWN) = 0;
    } else {
      uint64_t until = timer - time;
      if (until < countdown) {
        countdown = until;
      }
    }
  }
  CSR(MCOUNTDOWN) = countdown;
}

extern "C" void onTrapFetch() {
  // LOG(0, "Trap fetch: Mode = " << CSR(MEMODE) << ", SSTATUS = " << CSR(SSTATUS));
  // Get PC we trapped on
  uint32_t pc = CSR(MEPC);
  // Translate address
  uint32_t mcause = translate(pc, ACCESS_FETCH);
  if (mcause != MCAUSE_NONE) {
    // LOG(0, "PC = " <<  pc << ", cause = " << mcause);
    // If it fails, trap to supervisor
    CSR(STVAL) = pc;
    supervisorTrap(mcause);
    return;
  }
  // Load low part of instructions
  uint32_t inst = *reinterpret_cast<uint16_t*>(pc);
  if ((inst & 3) == 3 && (pc & 0xfff) == 0xffe) {
    // Full instruction crosses page boundary
    uint32_t pc2 = CSR(MEPC) + 2;
    mcause = translate(pc2, ACCESS_FETCH);
    if (mcause != MCAUSE_NONE) {
      // LOG(0, "PC = " <<  pc << ", cause = " << mcause);
      // If it fails, trap to supervisor
      CSR(STVAL) = pc2;
      supervisorTrap(mcause);
      return;
    }
  }
  LOG(0, "Fetch trap failed to trap, evil prover");
  die();
}

uint32_t handleSbiBaseExt() {
  uint32_t func_id = UREG(A6);
  switch(func_id) {
    case 0: // sbi_get_spec_version
      return 0x03000000;  // 3.0
    case 1: // sbi_get_impl_id
      return 1;  // SBI_OPENSBI_IMPID
    case 2: // sbi_get_impl_version
      return 0;  // TODO
    case 3: // sbi_probe_extension
      switch(UREG(A0)) {
        case 0x4442434E: // DBCN: Debug console
        //case 0x53525354: // SRST: System reset 
        case 0x54494D45: // Time: Timer
          return 1;
        default:
          return 0;
      }
    case 4: // sbi_get_mvendorid 
    case 5: // sbi_get_marchid 
    case 6: // sbi_get_mimpid 
      return 0;
    default:
      LOG(0, "Invalid base function: " << func_id);
      die();
  }
  return 0;
}

uint32_t handleSbiDebugConsole() {
  uint32_t func_id = UREG(A6);
  char c;
  switch(func_id) {
    case 0: // sbi_debug_console_write
      return hostWrite(-1, reinterpret_cast<char*>(UREG(A1)), UREG(A0));
    case 1: // sbi_debug_console_read
      // TODO: Check is there is data to read and read it
      return 0;
    case 2: // sbi_debug_console_write_byte 
      c = UREG(A0);
      hostWrite(-1, &c, 1);
      return 0;
    default:
      LOG(0, "Invalid SBI debug console function: " << func_id);
      die();
  }
  return 0;
}

uint32_t handleSystemReset() {
  uint32_t func_id = UREG(A6);
  if (func_id != 0) {
    LOG(0, "Invalid system reset function: " << func_id);
    die();
  }
  terminate(0, UREG(A0));
  return 0;
}

uint32_t handleTimer() {
  uint32_t func_id = UREG(A6);
  if (func_id != 0) {
    LOG(0, "Invalid timer function: " << func_id);
    die();
  }
  //info("Setting timer to: ", UREG(A1), UREG(A0));
  CSR(MTIMER) = UREG(A0);
  CSR(MTIMERH) = UREG(A1);
  return 0;
}

extern "C" void onTrapEcall() {
  uint64_t& time = *reinterpret_cast<uint64_t*>(&CSR(MTIME));
  time++;
  if (CSR(MEMODE) == MODE_USER) {
    // LOG(0, "User mode ECALL");
    CSR(STVAL) = 0;
    supervisorTrap(MCAUSE_ECALL_FROM_UMODE);
    return;
  }
  uint32_t ext_id = UREG(A7);
  uint32_t ret = 0;
  switch(ext_id) {
    case 0:
      terminate(UREG(A0), UREG(A1));
      break;
    case 0x10:
      ret = handleSbiBaseExt();
      break;
    case 0x4442434E:
      ret = handleSbiDebugConsole();
      break;
    case 0x53525354:
      ret = handleSystemReset();
      break;
    case 0x54494D45:
      ret = handleTimer();
      break;
    default:
      LOG(0, "Request for invalid SBI extension: " << ext_id);
  }
  UREG(A0) = 0;
  UREG(A1) = ret;
  CSR(MEPC) += 4;
}

extern "C" void onTrapInter() {
  CSR(MCOUNTDOWN) = 0x7fffffff;
  CSR(STVAL) = 0;
  supervisorTrap(MCAUSE_TIMER_INTERRUPT);
}

extern "C" void _trapEcall();
extern "C" void _trapInst();
extern "C" void _trapFetch();
extern "C" void _trapInter();

void initializeCsrs() {
  // Only initialize ones that are explicitly non-zero
  CSR(MCOUNTDOWN) = 0x7fffffff;
  CSR(MTRAPECALL) = reinterpret_cast<uint32_t>(_trapEcall);  // Set trap handler address, calls onTrap
  CSR(MTRAPINST) = reinterpret_cast<uint32_t>(_trapInst);  // Set trap handler address, calls onTrap
  CSR(MTRAPFETCH) = reinterpret_cast<uint32_t>(_trapFetch);  // Set trap handler address, calls onTrap
  CSR(MTRAPINTER) = reinterpret_cast<uint32_t>(_trapInter);  // Set trap handler address, calls onTrap
}

extern "C" void start() {
  initializeCsrs();
  asm volatile("mret\n" : : :);
}
