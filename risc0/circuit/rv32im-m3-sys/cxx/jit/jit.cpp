#include "jit/jit.h"

#include "core/log.h"
#include "rv32im/emu/decode.h"
#include "rv32im/emu/expand.h"
#include "jit/intel_asm.h"

namespace risc0::rv32im::jit {

namespace exec_details {
#include "jit/jit_asm_exec.h"
};

namespace preflight_details {
#include "jit/jit_asm_preflight.h"
};

using PageDetails = std::array<MemTxn, MPAGE_SIZE_WORDS>;

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

struct JitExec;

// State passed to JIT code
struct JitContext {
  PageDetails** pages;
  InstEntry* log; 
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
  std::vector<InstEntry> log;
  MemoryImage& image;
  Assembler a;
  std::vector<PageDetails*> pages;
  bool execOnly;

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
#ifdef PREFLIGHT
    a.doLoadImm32(Reg::R10, (inst.rs1 == inst.rs2) ? inst.rs2 + 64 : inst.rs2);;
#else
    a.doLoadImm32(Reg::R10, inst.rs2);
#endif
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
  JitExec(MemoryImage& image, bool execOnly) 
    : image(image)
    , a(4096)
    , execOnly(execOnly)
  {
    if (execOnly) {
      a.addBuiltins(exec_details::bytes, exec_details::bytes_len);
    } else {
      a.addBuiltins(preflight_details::bytes, preflight_details::bytes_len);
    }
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
    uint32_t eoffset = (execOnly ? exec_details::gsym_enter : preflight_details::gsym_enter);
    return a.call(eoffset, ctxAddr, a.getAddr(offset));
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
      uint32_t offset;
      switch(Opcode(exInst.opcode)) {
#define ENTRY(name, ...)  \
        case Opcode::name:  \
          offset = (execOnly ? exec_details::gsym_do_ ## name : preflight_details::gsym_do_ ## name); \
          done = doInst(cost, offset, exInst, pc, inst); \
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
  void run() {
    uint32_t entry = readWord(V2_COMPAT_SPC);
    LOG(0, "MSPC = " << HexWord{entry});
    jitLoop(entry);
  }
};

bool doJit(JitTrace& trace, MemoryImage& image, HostIO& io, size_t quota, bool execOnly) {
  JitExec jit(image, execOnly);
  jit.run();
  return true;
}

}  // namespace risc0::rv32im::jit
