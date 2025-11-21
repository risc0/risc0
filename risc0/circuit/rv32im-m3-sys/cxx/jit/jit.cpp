#include "core/log.h"
#include "rv32im/emu/decode.h"
#include "rv32im/emu/expand.h"
#include "rv32im/emu/image.h"

#include <sys/mman.h>
#include <cstring>

#include "jit/jit_asm.h"

using namespace risc0;
using namespace risc0::rv32im;

struct ExpandedInst {
  uint8_t opcode;
  uint8_t rs1;
  uint8_t rs2;
  uint8_t rd;
  uint32_t imm;
};

struct MemoryInfo {
  uint32_t value;
  uint32_t cycle;
};

using PageDetails = std::array<MemoryInfo, MPAGE_SIZE_WORDS>;

// TODO: Make this super minimal and self contained (i.e. don't use DecodedInst + getOpcode)
ExpandedInst expand(uint32_t inst) {
  if ((inst & 3) != 3) {
    static auto expandTable = generateExpandTable();
    inst = expandTable[inst];
  }
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

// Define intel registers
enum class Reg : uint8_t {
  RAX = 0,
  RCX = 1,
  RDX = 2,
  RBX = 3,
  RSP = 4,
  RBP = 5,
  RSI = 6,
  RDI = 7,
  R8 = 8,
  R9 = 9,
  R10 = 10,
  R11 = 11,
  R12 = 12,
  R13 = 13,
  R14 = 14,
  R15 = 15,
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

typedef uint64_t (*FuncPtr1)(uint64_t);
typedef uint64_t (*FuncPtr2)(uint64_t, uint64_t);
typedef uint64_t (*FuncPtr3)(uint64_t, uint64_t, uint64_t);
typedef uint64_t (*FuncPtr4)(uint64_t, uint64_t, uint64_t, uint64_t);

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


  inline constexpr bool isExtended(Reg reg) {
    return uint8_t(reg) >= 8;
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

  void addBuiltins(const std::vector<uint8_t>& data) {
    memcpy(cur, data.data(), data.size());
    cur += data.size();
  }

  ~Assembler() {
    if (begin != MAP_FAILED) {
      munmap(begin, end - begin);
    }
  }

  void doLoadImm32(Reg reg, uint32_t imm) {
    if (isExtended(reg)) {
      writeByte(0x41);
    }
    // Move RAX, imm
    writeByte(0xb8 + (uint8_t(reg) & 7));
    writeU32(imm);
  }

  void doLoadImm64(Reg reg, uint64_t imm) {
    if (isExtended(reg)) {
      writeByte(0x49);
    } else {
      writeByte(0x48);
    }
    // Rex prefix for 64 bit mode
    writeByte(0xb8 + (uint8_t(reg) & 7));
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
  // Presume we need to cmp %eax, %ecx first
  uint32_t doBranch(CmpOp cmp, uint32_t offset) {
    // cmp %eax, %ecx
    writeByte(0x39);  // Opcode
    writeByte(0xC8);  // ModRM
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

  void doPush(Reg reg) {
    if (isExtended(reg)) {
      writeByte(0x41);
    }
    writeByte(0x50 + (uint8_t(reg) & 7));
  }

  void doPop(Reg reg) {
    if (isExtended(reg)) {
      writeByte(0x41);
    }
    writeByte(0x58 + (uint8_t(reg) & 7));
  }

  void doCall(uint32_t offset) {
    uint32_t self = (cur - begin) + 5;
    writeByte(0xe8);
    int32_t diff = offset - self;
    writeU32(diff);
  }

  void doRet() {
    writeByte(0xc3);
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
  uint32_t prevValue;
  uint32_t prevCycle;
};

struct LogEntry {
  ExpandedInst inst;
  uint32_t pc;
  uint32_t origInst;
  MemTxn rd;
  MemTxn rs1;
  MemTxn rs2;
};

struct JitExec;

// State passed to JIT code
struct JitContext {
  PageDetails** pages;
  LogEntry* log; 
  int64_t quota;
  uint64_t cycle;
  // 0 point is here
  // 128 for user + system + 'junk' space
  std::array<uint64_t, 128> riscvRegs;
  FuncPtr2 pageMissFunc;
  JitExec* callbackObj;
};

class JitExec {
private:
  JitContext ctx;
  std::vector<LogEntry> log;
  MemoryImage& image;
  Assembler a;
  std::vector<PageDetails*> pages;

  PageDetails* getPage(uint32_t page) {
    PageDetails* data = pages[page];
    if (!data) {
      data = new PageDetails;
      PagePtr ipage = image.getPage(page);
      for (size_t i = 0; i < MPAGE_SIZE_WORDS; i++) {
        (*data)[i].value = (*ipage)[i];
        (*data)[i].cycle = 0;
      }
      pages[page] = data;
    }
    return data;
  }

  // Read a word from the page table
  uint32_t readWord(uint32_t wordAddr) {
    uint32_t page = wordAddr >> MPAGE_SIZE_WORDS_PO2;
    PageDetails* data = getPage(page);
    // TODO: This is only called on fetch, update cycle #
    // basically make Decode info
    return (*data)[wordAddr & MPAGE_MASK_WORDS].value;
  }

  // Handle branch instruction
  bool endBranch(CmpOp op, const ExpandedInst& inst, uint32_t pc, uint32_t newPc) {
    // Make a branch
    uint32_t branchFixup = a.doBranch(op, 0);
    // This will be the 'fallthough case', intially just fall through
    uint32_t fallthoughFixup = a.doLocalJump();
    // Set return value for dispatch (what to patch, where to patch to)
    uint64_t ret = (uint64_t(fallthoughFixup) << 32) | newPc;
    a.doLoadImm64(Reg::RAX, ret);
    a.doRet();
    // Ok, now handle branch patch
    uint32_t dest = pc + inst.imm;
    uint32_t branchOffset = a.getOffset();
    a.fixup(branchFixup, branchOffset);
    ret = (uint64_t(branchFixup) << 32) | dest;
    a.doLoadImm64(Reg::RAX, ret);
    a.doRet();
    return true;
  }

  bool endJal(const ExpandedInst& inst, uint32_t pc, uint32_t newPc) {
    uint32_t fallthoughFixup = a.doLocalJump();
    uint32_t jmpPc = pc + inst.imm;
    uint64_t ret = (uint64_t(fallthoughFixup) << 32) | jmpPc;
    a.doLoadImm64(Reg::RAX, ret);
    a.doRet();
    return true;
  }

  bool endJalr(const ExpandedInst& inst, uint32_t pc, uint32_t newPc) {
    a.doRet();
    return true;
  }

  bool endEcall(const ExpandedInst& inst, uint32_t pc, uint32_t newPc) {
    uint64_t ret = uint64_t(0xffffffff00000000ull) | pc;
    a.doLoadImm64(Reg::RAX, ret);
    a.doRet();
    return true;
  }

  bool endMret(const ExpandedInst& inst, uint32_t pc, uint32_t newPc) {
    throw std::runtime_error("Mret Unimplemented");
  }

  bool doUnhandled(uint32_t& cost, const ExpandedInst& inst, uint32_t pc, uint32_t newPc) {
    throw std::runtime_error("Unhandled Unimplemented");
  }

  bool doInst(uint32_t& cost, uint32_t offset, const ExpandedInst& inst, uint32_t pc, uint32_t oinst) {
    uint32_t newPc = pc + (((oinst & 3) == 3) ? 4 : 2);
    a.doLoadImm32(Reg::R8, (inst.rd == 0 ? 64 : inst.rd));
    a.doLoadImm32(Reg::R9, inst.rs1);
    a.doLoadImm32(Reg::R10, (inst.rs1 == inst.rs2) ? inst.rs2 + 64 : inst.rs2);;
    a.doLoadImm32(Reg::R11, inst.imm);
    a.doLoadImm32(Reg::R12, pc);
    a.doLoadImm32(Reg::RDX, oinst);
    a.doCall(offset);
    cost++;  // TODO handle variable costs
    switch (Opcode(inst.opcode)) {
      case Opcode::BEQ: return endBranch(CmpOp::JE, inst, pc, newPc);
      case Opcode::BNE: return endBranch(CmpOp::JNE, inst, pc, newPc);
      case Opcode::BLT: return endBranch(CmpOp::JL, inst, pc, newPc);
      case Opcode::BGE: return endBranch(CmpOp::JNL, inst, pc, newPc);
      case Opcode::BLTU: return endBranch(CmpOp::JB, inst, pc, newPc);
      case Opcode::BGEU: return endBranch(CmpOp::JNB, inst, pc, newPc);
      case Opcode::JAL: return endJal(inst, pc, newPc);
      case Opcode::JALR: return endJalr(inst, pc, newPc);
      case Opcode::ECALL: return endEcall(inst, pc, newPc);
      case Opcode::MRET: return endMret(inst, pc, newPc);
      default: break;
    }
    return false;
  }

  uint64_t pageMiss(uint64_t page) {
    PageDetails* pageDetails = getPage(page);
    LOG(1, "Did page miss, page " << page << " -> " << pageDetails);
    return reinterpret_cast<uint64_t>(pageDetails);
  }

  static uint64_t invokePageMiss(uint64_t ctxAddr, uint64_t val) {
    ctxAddr -= offsetof(JitContext, riscvRegs);
    JitContext* ctx = reinterpret_cast<JitContext*>(ctxAddr);
    return ctx->callbackObj->pageMiss(val);
  };

public:
  JitExec(MemoryImage& image) 
    : image(image)
    , a(4096)
  {
    auto builtins = loadFile("jit/jit_asm.bin");
    a.addBuiltins(builtins);
    size_t maxLog = 2 * 1024 * 1024;
    pages.resize(MEMORY_SIZE_MPAGES);
    log.resize(maxLog);
    ctx.cycle = 0;
    ctx.quota = maxLog;
    ctx.log = log.data();
    ctx.pages = pages.data();
    ctx.pageMissFunc = invokePageMiss;
    ctx.callbackObj = this;
    // TODO: Copy from memory image
    for (size_t i = 0; i < 128; i++) {
      ctx.riscvRegs[i] = 0;
    }
  }

  ~JitExec() {
    for (PageDetails* page : pages) {
      delete page;
    }
  }

  uint64_t enterBlock(uint32_t offset) {
    uint64_t ctxAddr = reinterpret_cast<uint64_t>(&ctx.riscvRegs[0]);
    return a.call(gsym_enter, ctxAddr, a.getAddr(offset));
  }

  uint32_t readHalf(uint32_t pc) {
    return (readWord(pc/4) >> (8 * (pc % 4))) & 0xffff;
  }


  uint32_t fetch(uint32_t pc) {
    // Read low 16 of instruction
    uint32_t inst = readHalf(pc);
    if ((inst & 3) == 3) {
      inst |= (readHalf(pc + 2)) << 16;
    }
    return inst;
  }

  uint32_t jitBlockAt(uint32_t pc) {
    bool done = false;
    uint32_t blockOffset = a.getOffset();
    // TODO: Setup quota check
    uint32_t cost = 0;
    while (!done) {
      uint32_t inst = fetch(pc);
      ExpandedInst exInst = expand(inst);
      uint64_t exFlat;
      memcpy(&exFlat, &exInst, sizeof(ExpandedInst));
      LOG(2, "PC: " << HexWord{pc} << " - " << getOpcodeName(Opcode(exInst.opcode)) << 
          "  rd = " << uint32_t(exInst.rd) << ", rs1 = " << uint32_t(exInst.rs1) << 
          ", rs2 = " << uint32_t(exInst.rs2) << ", imm = " << HexWord{exInst.imm});
      uint32_t newPc = pc + (((inst & 3) == 3) ? 4 : 2);
      LOG(2, "inst = " << HexWord{inst} << ", newPc = " << HexWord{newPc});
      switch(Opcode(exInst.opcode)) {
#define ENTRY(name, ...)  \
        case Opcode::name:  \
          done = doInst(cost, gsym_do_ ## name, exInst, pc, inst); \
          break;
#include "rv32im/base/rv32im.inc"
#undef ENTRY
        default:
          done = doUnhandled(cost, exInst, pc, newPc);
          break;
      }
      pc = newPc;
    }
    // TODO: apply quota check
    // a.fixupImm(quotaDec, cost);
    return blockOffset; 
  }

  void jitLoop(uint32_t pc) {
    uint32_t fixAddr = 0;
    std::map<uint32_t, uint32_t> blockCache;
    while(true) {
      auto it = blockCache.find(pc);
      uint32_t bstart;
      if (it == blockCache.end()) {
        LOG(1, "Jitting BB = " << HexWord{pc});
        bstart = jitBlockAt(pc);
        if (bstart == 0) { return; }
        blockCache[pc] = bstart;
      } else {
        bstart = it->second;
      }
      if (fixAddr) {
        a.fixup(fixAddr, bstart);
      }
      LOG(1, "Entering block, PC = " << HexWord{pc} << ", cycle = " << (ctx.cycle >> 32) << ", quota = " << ctx.quota);
      uint64_t ret = enterBlock(bstart);
      fixAddr = ret >> 32;
      pc = ret & 0xffffffff;
      LOG(1, "  new PC = " << HexWord{pc} << ", new cycle = " << (ctx.cycle >> 32) << ", new quota = " << ctx.quota);
      //dump();
      if (ctx.quota < 0) { break; }
      if (fixAddr == 0xffffffff) {
        LOG(0, "ECALL HIT");
        return;
      }
    }
  }
};

void runTest(const std::string& testName) {
  std::string path = "rv32im/rvtest/" + testName;
  std::map<uint32_t, uint32_t> words;
  LOG(0, "Loading " << path);
  uint32_t entry = loadKernelV2(words, path);
  auto image = MemoryImage::fromWords(words);
  LOG(0, "Making JIT engine");
  JitExec jit(image);
  LOG(0, "Doing JIT");
  jit.jitLoop(entry);
}

void runBench() {
  std::string path = "rv32im/test/asm_loop_kernel";
  std::map<uint32_t, uint32_t> words;
  LOG(0, "Loading " << path);
  uint32_t entry = loadKernelV2(words, path);
  auto image = MemoryImage::fromWords(words);
  LOG(0, "Making JIT engine");
  JitExec jit(image);
  LOG(0, "Doing JIT");
  jit.jitLoop(entry);
}


int main() {
  runBench();
  runTest("rvc");
  runTest("add");
  runTest("sub");
  runTest("xor");
  runTest("or");
  runTest("and");
  runTest("slt");
  runTest("sltu");
  runTest("addi");
  runTest("xori");
  runTest("ori");
  runTest("andi");
  runTest("slti");
  runTest("sltiu");
  runTest("beq");
  runTest("bne");
  runTest("blt");
  runTest("bge");
  runTest("bltu");
  runTest("bgeu");
  runTest("jal");
  runTest("jalr");
  runTest("lui");
  runTest("auipc");
  runTest("sll");
  runTest("slli");
  runTest("mul");
  runTest("mulh");
  runTest("mulhsu");
  runTest("mulhu");
  runTest("srl");
  runTest("sra");
  runTest("srli");
  runTest("srai");
  runTest("div");
  runTest("divu");
  runTest("rem");
  runTest("remu");
  runTest("lb");
  runTest("lh");
  runTest("lw");
  runTest("lbu");
  runTest("lhu");
  runTest("sb");
  runTest("sh");
  runTest("sw");
}
