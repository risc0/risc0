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

#include <stdint.h>
#include <sys/errno.h>

#include "rv32im/base/constants.h"

inline void die() {
  asm("unimp\n");
}
#if 0

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

inline uint32_t hostRead(uint32_t fd, char* buf, uint32_t len) {
  register uintptr_t a0 asm("a0") = fd;
  register uintptr_t a1 asm("a1") = reinterpret_cast<uint32_t>(buf);
  register uintptr_t a2 asm("a2") = len;
  register uintptr_t a7 asm("a7") = 1;
  asm volatile("ecall\n"
               : "+r"(a0)                           // outputs
               : "r"(a0), "r"(a1), "r"(a2), "r"(a7) // inputs
               :                                    // no clobbers
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
               : "r"(a0), "r"(a1), "r"(a2), "r"(a7) // inputs
               :                                    // no clobbers
  );
  return a0;
}

#define AT(x) (reinterpret_cast<uint32_t*>(x))
#define CSR(x) AT(CSR_BASE_ADDR)[CSR_ ## x]
#define UREG(x) AT(USER_REGS_ADDR)[REG_ ## x]

void addToLog(char*& buf, const char* str) {
  while(*str) {
    *buf++ = *str++;
  }
}

void addToLog(char*& buf, uint32_t val) {
  for (size_t i = 8; i-->0; ) {
    *buf++ = "0123456789abcdef"[(val >> (4 * i)) & 0xf];
  }
}

void debugHelper(char*& buf) {}

template<typename T, typename... Rest>
void debugHelper(char*& buf, T first, Rest... args) {
  addToLog(buf, first);
  debugHelper(buf, args...);
}

char* logBuf = reinterpret_cast<char*>(0xf1000000);
  
template<typename... Args>
void debug(Args... args) {
  /*
  char* buf = logBuf;
  debugHelper(buf, args...);
  hostWrite(2, logBuf, buf - logBuf);
  */
}

template<typename... Args>
void info(Args... args) {
  char* buf = logBuf;
  debugHelper(buf, args...);
  hostWrite(0, logBuf, buf - logBuf);
}
template<typename... Args>
void error(Args... args) {
  char* buf = logBuf;
  debugHelper(buf, args...);
  hostWrite(0, logBuf, buf - logBuf);
  die();
}

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

bool supervisorTrap(uint32_t cause, uint32_t tval) {
  CSR(SCAUSE) = cause;
  CSR(STVAL) = tval;
  uint32_t cur = CSR(SSTATUS);
  // Extract SIE bit
  uint32_t sie = (cur >> 1) & 1;
  // Clear SPIE, SIE, and SPP)
  cur &= 0xfffffedd;
  // Make SPIE = SIE
  cur |= (sie << 5);
  // Set SPP
  cur |= CSR(MPREVMODE) << 8;
  CSR(SSTATUS) = cur;
  CSR(MPREVMODE) = 1;
  CSR(MCLEARCACHE) = 1;
  CSR(SEPC) = CSR(MEPC);
  CSR(MEPC) = CSR(STVEC);
  return false;
}

bool forwardInvalidInst(uint32_t inst) {
  return supervisorTrap(MCAUSE_ILLEGAL_INSTRUCTION, inst);
} 

bool handleInstSystem(uint32_t pc, uint32_t inst) {
  if (inst == 0x10500073) {
    // TODO: this is wait for interrupt, maybe actual skip ahead?
    // debug("WFI");
    return true; // NO-OP
  }
  uint32_t csrt = (inst >> 12) & 3;
  if (csrt == 0) {
    if ((inst & (~0x01ff8000)) == 0x12000073) {
      // debug("SFENCE.VMA"); 
      CSR(MCLEARCACHE) = 1;
      return true;
    }
    return forwardInvalidInst(inst);
  }
  uint32_t rd = (inst >> 7) & 0x1f;
  uint32_t isImm = (inst >> 14) & 1;
  uint32_t rs1 = (inst >> 15) & 0x1f;
  uint32_t csr = (inst >> 20);
  uint32_t newVal = expandCsrVal(rs1, isImm);;
  // TODO: check permissions
  uint32_t curVal = AT(CSR_BASE_ADDR)[csr];
  if (csr == CSR_SIP) {
    uint64_t timer64 = (uint64_t(CSR(MTIMERH)) << 32) | CSR(MTIMER);
    uint64_t time64 = (uint64_t(CSR(TIMEH)) << 32) | CSR(TIME);
    curVal = (timer64 <= time64) ? 0x20 : 0x00;
  }
  if (rd != 0) {
    AT(USER_REGS_ADDR)[rd] = curVal;
  }
  uint32_t prevVal = curVal;
  switch(csrt) {
    case 1: curVal = newVal; break;
    case 2: curVal |= newVal; break;
    case 3: curVal &= newVal; break;
    default:
      return forwardInvalidInst(inst);
  }
  // debug("MEPC (", CSR(MEPC), ") CSR: ", csr, ", orig=", prevVal, ", new=", curVal);
  AT(CSR_BASE_ADDR)[csr] = curVal;
  if (prevVal == curVal) { return true; }
  switch(csr) {
    case CSR_SIE:
      info("SIE WRITE: ", CSR(SIE));
      break;
    case CSR_SIP:
      info("SIP WRITE of ", curVal, ", prev = ", prevVal, ": reverting");
      CSR(SIP) = prevVal;
      break;
    case CSR_SSTATUS:
      AT(VM_INFO_ADDR)[0] = 
        (CSR(SATP) & (0x803fffff)) +
        (((CSR(SSTATUS) >> 18) & 3) << 29);
      CSR(MCLEARCACHE) = 1;
      break;
    case CSR_SENVCFG:
      error("SENVCFG WRITE");
    case CSR_SATP:
      //info("New SATP: ", CSR(SATP));
      AT(VM_INFO_ADDR)[0] = 
        (CSR(SATP) & (0x803fffff)) +
        (((CSR(SSTATUS) >> 18) & 3) << 29);
      CSR(MCLEARCACHE) = 1;
      break;
    default:
      break;
  }
  return true;
}

void vmTrap(uint32_t cause, uint32_t vaddr) {
  CSR(SCAUSE) = cause;
  CSR(STVAL) = vaddr;
  uint32_t cur = CSR(SSTATUS);
  // Extract SIE bit
  uint32_t sie = (cur >> 1) & 1;
  // Clear SPIE, SIE, and SPP)
  cur &= 0xfffffedd;
  // Make SPIE = SIE
  cur |= (sie << 5);
  // Set SPP
  cur |= CSR(MPREVMODE) << 8;
  CSR(SSTATUS) = cur;
  CSR(MPREVMODE) = 1;
  CSR(MCLEARCACHE) = 1;
  CSR(SEPC) = CSR(MEPC);
  CSR(MEPC) = CSR(STVEC);
  return;
}

uint32_t causeAccessFault(uint32_t aType) {
  switch(aType) {
    case ACCESS_FETCH: return MCAUSE_INSTRUCTION_ACCESS_FAULT;
    case ACCESS_LOAD: return MCAUSE_LOAD_ACCESS_FAULT;
    case ACCESS_STORE: return MCAUSE_STORE_ACCESS_FAULT;
  }
  error("Invalid access code");
  return 0;
}

uint32_t causePageFault(uint32_t aType) {
  switch(aType) {
    case ACCESS_FETCH: return MCAUSE_INSTRUCTION_PAGE_FAULT;
    case ACCESS_LOAD: return MCAUSE_LOAD_PAGE_FAULT;
    case ACCESS_STORE: return MCAUSE_STORE_PAGE_FAULT;
  }
  error("Invalid access code");
  return 0;
}

uint32_t translate(uint32_t& addr, uint32_t aType) {
  if ((CSR(SATP) & 0x80000000) == 0) {
    return MCAUSE_NONE;
  }
  uint32_t a = CSR(SATP) << 12;
  uint32_t smode = CSR(MPREVMODE);
  uint32_t sum = (CSR(SSTATUS) >> 18) & 1;
  uint32_t mxr = (CSR(SSTATUS) >> 19) & 1;
  uint32_t vPage = addr >> 12;
  uint32_t i, xwr, pte, pteAddr;
  for (i = 2; i-- > 0;) {
    pteAddr = a + ((vPage >> (10 * i)) & 0x3ff)*4;
    if (pteAddr >= MACHINE_MODE_PROTECTED_START_ADDR) { return causeAccessFault(aType); }
    pte = AT(pteAddr)[0];
    if ((pte & 1) == 0) { 
      return causePageFault(aType); 
    }
    xwr = (pte >> 1) & 7;
    if (xwr == 2 || xwr == 6) { return causePageFault(aType); } 
    a = (pte << 2) & 0xfffff000;
    if (xwr != 0) break;
  }
  if (!xwr) { return causePageFault(aType); }
  if (i == 1) {
    if (((pte >> 10) & 0x3ff) != 0) {
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
    return causePageFault(aType); 
  }
  pte |= (1 << 6);  // Set A bit always
  if (aType == ACCESS_STORE) { pte |= (1 << 7); } // Set D if write
  AT(pteAddr)[0] = pte;
  addr = a | (addr & 0xfff);
  return MCAUSE_NONE;
}

bool handleAtomic(uint32_t pc, uint32_t inst) {
  uint32_t rs1 = (inst >> 15) & 0x1f;
  uint32_t rs2 = (inst >> 20) & 0x1f;
  uint32_t rd = (inst >> 7) & 0x1f;
  uint32_t op = (inst >> 27);
  uint32_t addr = AT(USER_REGS_ADDR)[rs1];
  uint32_t cause = translate(addr, op == 0b00010 ? ACCESS_LOAD : ACCESS_STORE);
  if (cause != MCAUSE_NONE) {
    return supervisorTrap(cause, AT(USER_REGS_ADDR)[rs1]);
  }
  uint32_t val = AT(addr)[0];
  uint32_t in = AT(USER_REGS_ADDR)[rs2];
  if (rd != 0) {
    AT(USER_REGS_ADDR)[rd] = val * (op != 0b00011);
  }
  //uint32_t origVal = val;
  switch(op) {
    case 0b00010: // LD
      break;
    case 0b00011: // SD
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
      return forwardInvalidInst(inst);
  }
  //debug("Doing atomic, addr=", addr, ", val=", origVal, ", in=", in, ", op=", op, ", out=", val);
  AT(addr)[0] = val;
  return true;
}

void handleIllegalInst() {
  uint32_t pc = CSR(MEPC);
  //debug("PC = ", pc);
  uint32_t inst = CSR(MTVAL);
  uint32_t newPc = pc;
  if ((inst & 3) == 3) {
    newPc += 4;
  } else {
    inst = AT(COMPRESSED_INST_LOOKUP_ADDR)[inst & 0xffff];
    newPc += 2;
  }
  bool success = true;
  switch((inst >> 2) & 0x1f) {
    case(0b11100):
      success = handleInstSystem(pc, inst);
      break;
    case(0b01011):
      success = handleAtomic(pc, inst);
      break;
    case(0b00011):  // Fence: TODO fix is circuit
      // TODO: Does iCache matter here?
      success = true;
      break; // NOP
    default:
      success = forwardInvalidInst(inst);
  }
  if (success) {
    CSR(MEPC) = newPc;
  }
}

uint32_t handleSbiDebugConsole() {
  uint32_t func_id = UREG(A6);
  // debug("SBI debug console: ", func_id);
  char c;
  switch(func_id) {
    case 0: // sbi_debug_console_write
      return hostWrite(1, reinterpret_cast<char*>(UREG(A1)), UREG(A0));
    case 1: // sbi_debug_console_read
      //return hostRead(1, reinterpret_cast<char*>(UREG(A1)), UREG(A0));
      return 0;
    case 2: // sbi_debug_console_write_byte 
      c = UREG(A0);
      hostWrite(1, &c, 1);
      return 0;
    default:
      error("Invalid SBI debug console function: ", func_id);
  }
  return 0;
}

uint32_t handleSystemReset() {
  uint32_t func_id = UREG(A6);
  if (func_id != 0) {
    error("Invalid system reset function: ", func_id);
  }
  terminate(UREG(A0));
  return 0;
}

uint32_t handleTimer() {
  uint32_t func_id = UREG(A6);
  if (func_id != 0) {
    error("Invalid timer function: ", func_id);
  }
  //info("Setting timer to: ", UREG(A1), UREG(A0));
  CSR(MTIMER) = UREG(A0);
  CSR(MTIMERH) = UREG(A1);
  return 0;
}

uint32_t handleSbiBaseExt() {
  uint32_t func_id = UREG(A6);
  //debug("SBI base: ", func_id);
  switch(func_id) {
    case 0: // sbi_get_spec_version
      return 0x03000000;  // 3.0
    case 1: // sbi_get_impl_id
      return 1;  // SBI_OPENSBI_IMPID
    case 2: // sbi_get_impl_version
      return 0;  // TODO
    case 3: // sbi_probe_extension
      debug("Seeking extension: ", UREG(A0));
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
      error("Invalid base function: ", func_id);
  }
  return 0;
}

void handleEcall() {
  uint32_t ext_id = UREG(A7);
  uint32_t ret;
  switch(ext_id) {
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
      ret = 0;
      error("Invalid SBI extension: ", ext_id);
  }
  UREG(A0) = 0;
  UREG(A1) = ret;
  CSR(MEPC) += 4;
}
#endif 

extern "C" void onTrap() {
  /*
  uint32_t cause = CSR(MCAUSE);
  switch(cause) {
    case MCAUSE_ILLEGAL_INSTRUCTION:
      handleIllegalInst();
      break;
    case MCAUSE_ECALL_FROM_SMODE:
      handleEcall();
      break;
    default:
      info("BAD CASUSE: ", CSR(MCAUSE));
      die();
      //error("Unhandled trap type"); //, cause);
      break;
  }
  */
}

extern "C" void _trapEntry();

/*
void initializeCsrs() {
  // Only initialize ones that are explicitly non-zero
  CSR(MTVEC) = reinterpret_cast<uint32_t>(_trapEntry);  // Set trap handler address, calls onTrap
  CSR(MTIMER) = 0xffffffff;
  CSR(MTIMERH) = 0xffffffff;
}
*/

extern "C" void start() {
  //initializeCsrs();
  //UREG(A0) = 0;  // Set A0 to hart 0
  //UREG(A1) = 0xe0000000;  // Set A1 to pointer to dtb
  // MRET back into kernel entry
  //CSR(MPREVMODE) = MODE_SUPERVISOR;  // Set trap return mode for mret
  //CSR(MEPC) = 0xc0000000;  // Set trap return address to kernel entry point
  //asm volatile("mret\n" : : :);
}
