#include "core/log.h"
#include "rv32im/emu/decode.h"
#include "rv32im/emu/image.h"

#include <sys/mman.h>
#include <cstring>

using namespace risc0;
using namespace risc0::rv32im;

struct ExpandedInst {
  uint8_t opcode;
  uint8_t rs1;
  uint8_t rs2;
  uint8_t rd;
  uint32_t imm;
};

// TODO: Make this super minimal and self contained (i.e. don't use DecodedInst + getOpcode)
ExpandedInst expand(uint32_t inst) {
  DecodedInst decoded(inst);
  ExpandedInst ret;
  ret.rs1 = decoded.rs1;
  ret.rs2 = decoded.rs2;
  ret.rd = decoded.rd;
  Opcode opcode = getOpcode(inst);
  ret.opcode = uint8_t(opcode);
  switch(opcode) {
#define ENTRY(name, idx, op, immType, ...) \
    case Opcode::name: ret.imm = decoded.imm ## immType(); break;
#include "rv32im/base/rv32im.inc"
#undef ENTRY
    case Opcode::ANY:
      throw std::runtime_error("Trying to expand an illegal instruction");
  }
  return ret;
}

typedef uint64_t (*FuncPtr1)(uint64_t);
typedef uint64_t (*FuncPtr2)(uint64_t, uint64_t);
typedef uint64_t (*FuncPtr3)(uint64_t, uint64_t, uint64_t);
typedef uint64_t (*FuncPtr4)(uint64_t, uint64_t, uint64_t, uint64_t);

// Define intel registers
enum class Reg : uint8_t {
  EAX = 0,
  ECX = 1,
  EDX = 2,
  EBX = 3,
  ESP = 4,
  EBP = 5,
  ESI = 6,
  EDI = 7,
  R8D = 8,
  R9D = 9,
  R10D = 10,
  R11D = 11,
  R12D = 12,
  R13D = 13,
  R14D = 14,
  R15D = 15,
};

// X86 binary opcodes
enum class BinOp : uint8_t {
  MOV = 0x89,
  ADD = 0x01,
  SUB = 0x29,
  XOR = 0x31,
  OR = 0x09,
  AND = 0x21,
};

// X86 unary opcode
enum class UnaryOp : uint16_t {
  SHL_CL = 0xd34,
  SHR_CL = 0xd35,
  SAR_CL = 0xd37,
  SUB_IMM8 = 0x835,
  SUB_IMM32 = 0x815,
  ADD_IMM8 = 0x830,
  ADD_IMM32 = 0x810,
  JMP = 0xff4,
  CALL= 0xff2,
  // PUSH = 0xff6,
};

enum class CmpOp : uint8_t {
  JO   = 0x80,  // Jump if overflow
  JNO  = 0x81,  // Jump if not overflow
  JB   = 0x82,  // Jump if below (unsigned) / carry
  JNB  = 0x83,  // Jump if not below
  JE   = 0x84,  // Jump if equal / zero
  JNE  = 0x85,  // Jump if not equal
  JBE  = 0x86,  // Jump if below or equal (unsigned)
  JNBE = 0x87,  // Jump if not below or equal
  JS   = 0x88,  // Jump if sign
  JNS  = 0x89,  // Jump if not sign
  JP   = 0x8A,  // Jump if parity
  JNP  = 0x8B,  // Jump if not parity
  JL   = 0x8C,  // Jump if less (signed)
  JNL  = 0x8D,  // Jump if not less (signed)
  JLE  = 0x8E,  // Jump if less or equal (signed)
  JNLE = 0x8F,  // Jump if not less or equal (signed)
};

class Assembler {
private:
  // Memory region to JIT to
  uint8_t* begin;
  uint8_t* cur;
  uint8_t* end;

  // Some code to write to the current buffer
  inline void writeByte(uint8_t val) {
    *cur = val;
    cur++;
  }

  inline void writeU32(uint32_t val) {
    writeByte(val);
    writeByte(val >> 8);
    writeByte(val >> 16);
    writeByte(val >> 24);
  }

  inline void writeU64(uint64_t val) {
    writeU32(val);
    writeU32(val >> 32);
  }

  // Define mode for modRM
  enum Mode {
    MODE_INDIRECT = 0b00,
    MODE_DISP_8 = 0b01,
    MODE_DISP_32 = 0b01,
    MODE_DIRECT = 0b11,
  };

  // Check if an intel register is from the 'extended' set (and thus needs a prefix)
  inline constexpr bool isExtended(Reg reg) {
    return uint8_t(reg) >= 8;
  }

  // Bit pack things in the rm byte
  inline constexpr uint8_t modRM(Mode mode, uint8_t reg, Reg rm) {
    return 
      (uint8_t(mode) << 6) | 
      ((uint8_t(reg) & 7) << 3) |
      (uint8_t(rm) & 7);
  }

  inline constexpr Mode computeMode(int32_t disp) {
    if (disp == 0) { return MODE_INDIRECT; }
    else if (int32_t(int8_t(disp)) == disp) { return MODE_DISP_8; }
    else { return MODE_DISP_32; }
  }

  inline void doBinary(bool is64, uint8_t opcode, Reg reg, Mode mode, Reg rm, int32_t disp = 0) {
    // If 64 bit, or if either register is extended, do REX prefix
    if (is64 || isExtended(reg) || isExtended(rm)) {
      uint8_t prefix = 0x40 | (is64 << 3) | (isExtended(reg) << 2) | isExtended(rm);
      writeByte(prefix);
    }
    // Write opcode
    writeByte(opcode);
    // Write modRM
    writeByte(modRM(mode, uint8_t(reg), rm));
    if (mode != MODE_DIRECT && ((uint8_t(rm) & 7) == 4)) {
      // Crazy x86 overloads SP/R12 and adds a SIB byte
      // 0x24 basically means 'use SP/R12 as normal'
      writeByte(0x24);
    }
    // Write diplacement if any
    if (mode == MODE_DISP_8) {
      writeByte(disp);
    } else if (mode == MODE_DISP_32) {
      writeU32(disp);
    }
  }

  inline void doUnary(bool is64, UnaryOp op, Mode mode, Reg rm, uint32_t disp = 0) {
    // If register is extended, do REX preix
    if (is64 | isExtended(rm)) {
      uint8_t prefix = 0x40 | (is64 << 3) | isExtended(rm);
      writeByte(prefix);
    }
    // Write opcode
    writeByte(uint16_t(op) >> 4);
    // Write modRM
    writeByte(modRM(mode, uint16_t(op) & 0x7, rm));
    if (mode != MODE_DIRECT && ((uint8_t(rm) & 7) == 4)) {
      // Crazy x86 overloads SP/R12 and adds a SIB byte
      // 0x24 basically means 'use SP/R12 as normal'
      writeByte(0x24);
    }
    // Write diplacement if any
    if (mode == MODE_DISP_8) {
      writeByte(disp);
    } else if (mode == MODE_DISP_32) {
      writeU32(disp);
    }
  }

public:
  Assembler(size_t pages) {
    size_t size = pages * 4096;
    begin = (uint8_t*) mmap(NULL, size, PROT_READ | PROT_WRITE | PROT_EXEC,
                      MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (begin == MAP_FAILED) {
      throw std::runtime_error("Allocation of Jit region failed");
    }
    cur = begin;
    end = cur + size;
  }

  ~Assembler() {
    if (begin != MAP_FAILED) {
      munmap(begin, end - begin);
    }
  }
  // 32 bit op %src, %dest
  inline void doRR32(BinOp op, Reg src, Reg dest) {
    doBinary(false, uint8_t(op), src, MODE_DIRECT, dest);
  }
  // 32 bit op %src, disp(%dest)
  inline void doRM32(BinOp op, Reg src, Reg dest, int32_t disp) {
    doBinary(false, uint8_t(op), src, computeMode(disp), dest, disp);
  }
  // 32 bit op disp(%src), %dest
  inline void doMR32(BinOp op, Reg src, int32_t disp, Reg dest) {
    doBinary(false, uint8_t(op) + 2, dest, computeMode(disp), src, disp);
  }
  // 64 bit op %src, %dest
  inline void doRR64(BinOp op, Reg src, Reg dest) {
    doBinary(true, uint8_t(op), src, MODE_DIRECT, dest);
  }
  // 64 bit op %src, disp(%dest)
  inline void doRM64(BinOp op, Reg src, Reg dest, int64_t disp) {
    doBinary(true, uint8_t(op), src, computeMode(disp), dest, disp);
  }
  // 64 bit op disp(%src), %dest
  inline void doMR64(BinOp op, Reg src, int64_t disp, Reg dest) {
    doBinary(true, uint8_t(op) + 2, dest, computeMode(disp), src, disp);
  }
  // 32 bit op %reg
  inline void doR32(UnaryOp op, Reg reg) {
    doUnary(false, op, MODE_DIRECT, reg);
  }
  // 32 bit op disp(%reg)
  inline void doM32(UnaryOp op, Reg reg, int32_t disp) {
    doUnary(false, op, computeMode(disp), reg, disp);
  }
  // 64 bit op %reg
  inline void doR64(UnaryOp op, Reg reg) {
    doUnary(true, op, MODE_DIRECT, reg);
  }
  // 64 bit op disp(%reg)
  inline void doM64(UnaryOp op, Reg reg, int32_t disp) {
    doUnary(true, op, computeMode(disp), reg, disp);
  }
  inline void imm8(int8_t val) {
    writeByte(val);
  }
  inline void imm32(int32_t val) {
    writeU32(val);
  }
  inline void imm64(int64_t val) {
    writeU64(val);
  }

  void doLoadImm32(Reg reg, uint32_t imm) {
    // Move RAX, imm
    writeByte(0xb8 + uint8_t(reg));
    writeU32(imm);
  }

  void doLoadImm64(Reg reg, uint64_t imm) {
    // Rex prefix for 64 bit mode
    writeByte(0x48);
    writeByte(0xb8 + uint8_t(reg));
    writeU64(imm);
  }

  // Jump to a given offset: -1 means jump to end of this instruction which
  // is used to put a NO-op that can later be retargeted.  Returns the offset
  // of the immediate to allow later adjustment
  uint32_t doLocalJump(uint32_t offset = 0xffffffff) {
    uint32_t curOffset = (cur - begin);
    uint32_t diff = offset - (curOffset + 5);
    if (offset == 0xffffffff) {
      diff = 0;
    }
    // Write PC local jump
    writeByte(0xe9);
    writeU32(diff);
    return curOffset + 1;
  }

  // Branch to a location, returns an offset to allow rewriting of the destination
  uint32_t doBranch(CmpOp cmp, uint32_t offset) {
    uint32_t curOffset = (cur - begin);
    uint32_t diff = offset - (curOffset + 6);
    writeByte(0x0f);
    writeByte(uint8_t(cmp));
    writeU32(diff);
    return curOffset + 2;
  }

  void fixup(uint32_t fixupOffset, uint32_t newDest) {
    uint8_t* code = begin + fixupOffset;
    uint32_t diff = newDest - (fixupOffset + 4);
    code[0] = diff & 0xff;
    code[1] = (diff >> 8) & 0xff;
    code[2] = (diff >> 16) & 0xff;
    code[3] = (diff >> 24) & 0xff;
  }

  void fixupImm(uint32_t fixupOffset, uint32_t imm) {
    uint8_t* code = begin + fixupOffset;
    code[0] = imm & 0xff;
    code[1] = (imm >> 8) & 0xff;
    code[2] = (imm >> 16) & 0xff;
    code[3] = (imm >> 24) & 0xff;
  }

  void doRet() {
    writeByte(0xc3);
  }

  // Call func with arg
  // I save *all* the caller save registers, which is maybe a bit extreme
  // Well, except RAX, which is the return value...
  // Also, not very perf optimized, this really should only be used for debug
  void doCall(FuncPtr1 func, uint64_t arg) {
    // Save most things
    writeByte(0x51); // Push RCX
    writeByte(0x52); // Push RDX
    writeByte(0x56); // Push RSI
    writeByte(0x57); // Push RDI
    writeByte(0x41); writeByte(0x50); // Push R8
    writeByte(0x41); writeByte(0x51); // Push R9
    writeByte(0x41); writeByte(0x52); // Push R10
    writeByte(0x41); writeByte(0x53); // Push R11
    // Align stack (presumably we are == 8 % 16)
    doR64(UnaryOp::SUB_IMM8, Reg::ESP); imm8(8);
    // Load arg into EDS 
    doLoadImm64(Reg::EDI, arg);
    // Load RAX with address to jump to
    doLoadImm64(Reg::EAX, reinterpret_cast<uint64_t>(func));
    // Call through RAX
    doR32(UnaryOp::CALL, Reg::EAX);
    // Undo stack alignment
    doR64(UnaryOp::ADD_IMM8, Reg::ESP); imm8(8);
    // Pop all the things I pushed
    writeByte(0x41); writeByte(0x5b); // Pop R11
    writeByte(0x41); writeByte(0x5a); // Pop R10
    writeByte(0x41); writeByte(0x59); // Pop R9
    writeByte(0x41); writeByte(0x58); // Pop R8
    writeByte(0x5f); // Pop RDI
    writeByte(0x5e); // Pop RSI
    writeByte(0x5a); // Pop RDX
    writeByte(0x59); // Pop RCX
  }

  // Get the offset of the next instruction
  uint32_t getOffset() {
    return (cur - begin);
  }

  uint64_t getAddr(uint64_t offset) {
    return reinterpret_cast<uint64_t>(begin + offset);
  }

  // Call into generated code at a given offset
  uint64_t call(uint32_t offset, uint64_t arg) {
    FuncPtr1 fptr = reinterpret_cast<FuncPtr1>(begin + offset);
    return fptr(arg); 
  }
  uint64_t call(uint32_t offset, uint64_t arg1, uint64_t arg2) {
    FuncPtr2 fptr = reinterpret_cast<FuncPtr2>(begin + offset);
    return fptr(arg1, arg2); 
  }
  uint64_t call(uint32_t offset, uint64_t arg1, uint64_t arg2, uint64_t arg3) {
    FuncPtr3 fptr = reinterpret_cast<FuncPtr3>(begin + offset);
    return fptr(arg1, arg2, arg3); 
  }
};

struct MemTxn {
  uint32_t prevCycle;
  uint32_t prevValue;
};

struct LogEntry {
  uint32_t pc;
  uint32_t iCacheCycle;
  uint64_t inst;
  MemTxn rd;
  MemTxn rs1;
  MemTxn rs2;
};

class JitExec {
private:
  // Things that actually live in JIT visible context
  uint32_t pad;
  uint32_t pc;
  int64_t quota;
  uint64_t cycle;
  // 128 for user + system + 'junk' space
  std::array<uint64_t, 128> riscvRegs;

  // Normal things
  std::vector<LogEntry> log;
  MemoryImage& image;
  Assembler a;
  std::vector<Page*> pages;
  uint32_t enterOffset;
  uint32_t exitOffset;

  // Read a word from the page table
  uint32_t readWord(uint32_t wordAddr) {
    uint32_t page = wordAddr >> MPAGE_SIZE_WORDS_PO2;
    Page* data = pages[page];
    if (!data) {
      data = new Page;
      *data = *image.getPage(page);
      pages[page] = data;
    }
    return (*data)[wordAddr & MPAGE_MASK_WORDS];
  }

  // Build a generic block entry that saves various things
  // and jumps into a basic block
  void makeEnter() {
    enterOffset = a.getOffset();
    // Make room on stack for 6 saved 64 bit registers
    a.doR64(UnaryOp::SUB_IMM8, Reg::ESP);
    a.imm8(6 * sizeof(uint64_t));
    // Save callee-save registers I will overwrite
    for (size_t i = 0; i < 4; i++) {
      a.doRM64(BinOp::MOV, Reg(12 + i), Reg::ESP, i * sizeof(uint64_t));
    }
    a.doRM64(BinOp::MOV, Reg::EBX, Reg::ESP, 4 * sizeof(uint64_t));
    a.doRM64(BinOp::MOV, Reg::EBP, Reg::ESP, 5 * sizeof(uint64_t));
    // Laod RISC-V registers
    for (size_t i = 0; i < 8; i++) {
      a.doMR64(BinOp::MOV, R_CTX, (8 + i) * sizeof(uint64_t), Reg(8 + i));
    }
    // Load cycle + quota
    a.doMR64(BinOp::MOV, R_CTX, CTX_CYCLE_OFFSET, R_CYCLE);
    a.doMR64(BinOp::MOV, R_CTX, CTX_QUOTA_OFFSET, R_QUOTA);
    // Jump to address in rdx (third parameter)
    a.doR64(UnaryOp::JMP, Reg::EDX);
  }

  // Build a generic block that returns back.
  void makeExit() {
    exitOffset = a.getOffset();
    // Save RISC-V registers
    for (size_t i = 0; i < 8; i++) {
      a.doRM64(BinOp::MOV, Reg(8 + i), R_CTX, (8 + i) * sizeof(uint64_t));
    }
    // Save cycle + quota
    a.doRM64(BinOp::MOV, R_CYCLE, R_CTX, CTX_CYCLE_OFFSET);
    a.doRM64(BinOp::MOV, R_QUOTA, R_CTX, CTX_QUOTA_OFFSET);
    // Load callee-save registers
    for (size_t i = 0; i < 4; i++) {
      a.doMR64(BinOp::MOV, Reg::ESP, i * sizeof(uint64_t), Reg(12 + i));
    }
    a.doMR64(BinOp::MOV, Reg::ESP, 4 * sizeof(uint64_t), Reg::EBX);
    a.doMR64(BinOp::MOV, Reg::ESP, 5 * sizeof(uint64_t), Reg::EBP);
    // Undo stack manipulation
    a.doR64(UnaryOp::ADD_IMM8, Reg::ESP);
    a.imm8(6 * sizeof(uint64_t));
    // Return
    a.doRet();
  }

  static constexpr Reg R_CTX = Reg::ESI;
  static constexpr Reg R_LOG = Reg::EDI;
  static constexpr Reg R_CYCLE = Reg::EBX;
  static constexpr Reg R_QUOTA = Reg::EBP;

  static constexpr int32_t LOG_RD_OFFSET = 16;
  static constexpr int32_t LOG_RS1_OFFSET = 24;
  static constexpr int32_t LOG_RS2_OFFSET = 32;

  static constexpr int32_t CTX_CYCLE_OFFSET = -8;
  static constexpr int32_t CTX_QUOTA_OFFSET = -16;
  static constexpr int32_t CTX_PC_OFFSET = -20;

  // Common rv32 registers are kept local in x86 registers, rest are in memory
  constexpr bool isCommon(uint8_t rvReg) {
    return rvReg >= 8 && rvReg < 16;
  }

  // Make sure the rv32im register is in an X86 register
  void loadReg(Reg into, uint8_t rvReg) {
    if (isCommon(rvReg)) {
      a.doRR64(BinOp::MOV, Reg(rvReg), into);
    } else {
      a.doMR64(BinOp::MOV, R_CTX, 8 * rvReg, into);
    }
  }
  // Store a X86 register back to an rv32im register
  void storeReg(Reg from, uint8_t rvReg) {
    if (rvReg == 0) { rvReg = 64; }
    if (isCommon(rvReg)) {
      a.doRR64(BinOp::MOV, from, Reg(rvReg));
    } else {
      a.doRM64(BinOp::MOV, from, R_CTX, 8 * rvReg);
    }
  }
  
  // Write the original value + cycle of RD to the log
  // Note: in the case that RS1 / RS2 == RD, this might be
  // out of date, but no information is lost do witgen can
  // correct it.
  void logRd(uint8_t rd) {
    if (rd == 0) { rd = 64; }
    loadReg(Reg::EAX, rd);
    a.doRM64(BinOp::MOV, Reg::EAX, R_LOG, LOG_RD_OFFSET);
  }

  // Log reads of RS1 + RS2, and load into RAX, RCX
  // Then update cycle # and write back
  void loadDual(uint8_t rs1, uint8_t rs2) {
    bool isSame = (rs1 == rs2);
    // If isSame, read from dummy address
    if (isSame) { rs2 += 64; }
    // Do loads
    loadReg(Reg::EAX, rs1);
    loadReg(Reg::ECX, rs2);
    // Write old state to log
    a.doRM64(BinOp::MOV, Reg::EAX, R_LOG, LOG_RS1_OFFSET);
    a.doRM64(BinOp::MOV, Reg::ECX, R_LOG, LOG_RS2_OFFSET);
    // Zero high bits byt moving registers to themselves as 32 bit
    a.doRR32(BinOp::MOV, Reg::EAX, Reg::EAX);
    a.doRR32(BinOp::MOV, Reg::ECX, Reg::ECX);
    // Or in cycle number
    a.doRR64(BinOp::OR, R_CYCLE, Reg::EAX);
    a.doRR64(BinOp::OR, R_CYCLE, Reg::ECX);
    // Write back
    storeReg(Reg::EAX, rs1);
    storeReg(Reg::ECX, rs2);
    // if isSame, copy at the end to ignore dummy read
    if (isSame) { a.doRR64(BinOp::MOV, Reg::EAX, Reg::ECX); }
  }

  // Log RS1 + load to EAX
  void loadRs1(uint8_t rs1) {
    // Load into EAX
    loadReg(Reg::EAX, rs1);
    // Write old state to log
    a.doRM64(BinOp::MOV, Reg::EAX, R_LOG, LOG_RS1_OFFSET);
    // Zero high bits
    a.doRR32(BinOp::MOV, Reg::EAX, Reg::EAX);
    // Or in cycle number
    a.doRR64(BinOp::OR, R_CYCLE, Reg::EAX);
    // Write back
    storeReg(Reg::EAX, rs1);
  }

  inline void incCycle() {
    // Add 2^32 to cycle
    a.doLoadImm64(Reg::ECX, 0x100000000ull);
    a.doRR64(BinOp::ADD, Reg::ECX, R_CYCLE);
  }

  inline void doRegPre(ExpandedInst& inst) {
    logRd(inst.rd);  // Save RD pre-state
    loadDual(inst.rs1, inst.rs2);  // Load + log RS1 + RS2
  }

  inline void doImmPre(ExpandedInst& inst) {
    logRd(inst.rd);
    loadRs1(inst.rs1);
    a.doLoadImm32(Reg::ECX, inst.imm);
  }

  inline void doRegPost(ExpandedInst& inst) {
    // Increment cycle to write half
    incCycle();
    // Set RD cycle # to write cycle (note: EAX top 32 is clear)
    a.doRR64(BinOp::OR, R_CYCLE, Reg::EAX);
    // Store
    storeReg(Reg::EAX, inst.rd);
    // Increment again to next cycle
    incCycle();
  }

  // Handle the common binary 3 regisster ops
  void doRegBinary(BinOp op, ExpandedInst& inst) {
    doRegPre(inst);
    a.doRR32(op, Reg::ECX, Reg::EAX);  // Do actual operation
    doRegPost(inst);
  }

  // Handle common binary IMM ops
  void doImmBinary(BinOp op, ExpandedInst& inst) {
    doImmPre(inst);
    a.doRR32(op, Reg::ECX, Reg::EAX); 
    doRegPost(inst);
  }

  // Handle branch instruction
  void doBranch(CmpOp op, ExpandedInst& inst, uint32_t pc, uint32_t nextPc) {
    loadDual(inst.rs1, inst.rs2);  // Load + log RS1 + RS2
    a.doRR32(BinOp::SUB, Reg::ECX, Reg::EAX); // Copute rs1 - rs2
    // Make a branch
    uint32_t branchFixup = a.doBranch(op, 0);
    // This will be the 'fallthough case', intially just fall through
    uint32_t fallthoughFixup = a.doLocalJump();
    // Set return value for dispatch (what to patch, where to patch to)
    uint64_t ret = (uint64_t(fallthoughFixup) << 32) | nextPc;
    a.doLoadImm64(Reg::EAX, ret);
    a.doLocalJump(exitOffset);
    // Ok, now handle branch patch
    uint32_t dest = pc + inst.imm;
    uint32_t branchOffset = a.getOffset();
    ret = (uint64_t(branchFixup) << 32) | dest;
    a.doLoadImm64(Reg::EAX, ret);
    a.doLocalJump(exitOffset);
    a.fixup(branchFixup, branchOffset);
  }

  // Do AUIPC instruction
  void doAUIPC(ExpandedInst& inst, uint32_t pc) {
    logRd(inst.rd);
    a.doLoadImm32(Reg::EAX, pc + inst.imm);
    doRegPost(inst);
  }

  // Do LUI instruction
  void doLUI(ExpandedInst& inst) {
    logRd(inst.rd);
    a.doLoadImm32(Reg::EAX, inst.imm);
    doRegPost(inst);
  }

  // Check qouta, exit if it would be below 0.  Initially make
  // cost == 0, but return offset of immediate fill in later
  uint32_t checkQuota(uint32_t pc) {
    // Load AX with PC is case quota check fails
    a.doLoadImm32(Reg::EAX, pc);
    // Subtract from quota
    a.doR64(UnaryOp::SUB_IMM32, R_QUOTA);
    uint32_t immPos = a.getOffset();
    a.imm32(0);
    // Exit if negative
    a.doBranch(CmpOp::JS, exitOffset);
    return immPos;
  }

public:
  JitExec(MemoryImage& image) 
    : image(image)
    , a(1024)
  {
    pages.resize(MEMORY_SIZE_MPAGES);
    log.resize(1000);
    cycle = 0;
    quota = 10000000;
    // TODO: Copy from memory image
    for (size_t i = 0; i < 128; i++) {
      riscvRegs[i] = 0;
    }
    makeEnter();
    makeExit();
  }

  ~JitExec() {
    for (Page* page : pages) {
      delete page;
    }
  }

  uint64_t enterBlock(uint32_t offset) {
    uint64_t logAddr = reinterpret_cast<uint64_t>(log.data());
    uint64_t regsAddr = reinterpret_cast<uint64_t>(&riscvRegs[0]);
    return a.call(enterOffset, logAddr, regsAddr, a.getAddr(offset));
  }

  uint32_t jitBlockAt(uint32_t pc) {
    bool done = false;
    uint32_t blockOffset = a.getOffset();
    uint32_t quotaDec = checkQuota(pc);
    uint32_t cost = 0;
    while (!done) {
      uint32_t inst = readWord(pc/4);
      ExpandedInst exInst = expand(inst);
      LOG(0, "PC: " << HexWord{pc} << " - " << getOpcodeName(Opcode(exInst.opcode)));
      LOG(0, "  rd = " << uint32_t(exInst.rd) << ", rs1 = " << uint32_t(exInst.rs1) << 
          ", rs2 = " << uint32_t(exInst.rs2) << ", imm = " << std::hex << exInst.imm << std::dec);
      switch(Opcode(exInst.opcode)) {
        case Opcode::ADDI:
          doImmBinary(BinOp::ADD, exInst);
          cost += 1;
          break;
        case Opcode::BNE:
          doBranch(CmpOp::JNE, exInst, pc, pc + 4); 
          cost += 1;
          done = true;
          break;
        case Opcode::AUIPC:
          doAUIPC(exInst, pc); 
          cost += 1;
          break;
        case Opcode::LUI:
          doLUI(exInst); 
          cost += 1;
          break;
        default:
          throw std::runtime_error("Unhandled instruction");
      }
      pc += 4;
    }
    a.fixupImm(quotaDec, cost);
    a.doLocalJump(exitOffset);
    return blockOffset; 
  }

  void jitLoop(uint32_t pc) {
    uint32_t fixAddr = 0;
    std::map<uint32_t, uint32_t> blockCache;
    while(true) {
      auto it = blockCache.find(pc);
      uint32_t bstart;
      if (it == blockCache.end()) {
        LOG(0, "Jitting BB = " << HexWord{pc});
        bstart = jitBlockAt(pc);
        blockCache[pc] = bstart;
      } else {
        bstart = it->second;
      }
      if (fixAddr) {
        a.fixup(fixAddr, bstart);
      }
      LOG(0, "Entering block, PC = " << HexWord{pc} << ", cycle = " << (cycle >> 32) << ", quota = " << quota);
      uint64_t ret = enterBlock(bstart);
      LOG(0, "  new cycle = " << (cycle >> 32) << ", new quota = " << quota);
      fixAddr = ret >> 32;
      pc = ret & 0xffffffff;
      if (quota < 0) { break; }
    }
  }

  void dump() {
    for (size_t i = 0; i < 32; i++) {
      LOG(0, "Reg[" << i << "] = " << std::hex << riscvRegs[i] << std::dec);
    }
    LOG(0, "Cycle = " << std::hex << cycle << std::dec);
  }
};

int main() {
  std::map<uint32_t, uint32_t> words;
  //uint32_t entry = loadKernelV2(words, "rv32im/rvtest/add");
  uint32_t entry = loadKernelV2(words, "rv32im/test/asm_loop_kernel");
  auto image = MemoryImage::fromWords(words);

  JitExec jit(image);
  //jit.doTest();
  jit.jitLoop(entry);
  LOG(0, "Did something");
  jit.dump();

  /*
  Assembler a(1024);
  uint32_t func = a.getOffset();
  // Adjust stack alignment by 8, calling convention is picky
  a.doR64(UnaryOp::SUB_IMM8, Reg::ESP);
  a.imm8(8);
  // Do call
  a.loadRaxImm(reinterpret_cast<uint64_t>(testFunc));
  a.doR(UnaryOp::CALL, Reg::EAX);
  // Fix stack
  a.doR64(UnaryOp::ADD_IMM8, Reg::ESP);
  a.imm8(8); // Adjust stack alignment by 8
  // Return
  a.ret();
  uint64_t ret = a.call(func, 23);
  LOG(0, "Ret = " << ret);
  */
}
