#include "jit/block_cache.h"

#include "core/log.h"
#include "rv32im/emu/decode.h"
#include "rv32im/emu/expand.h"

namespace risc0::jit {

namespace exec_details {
#include "jit/jit_asm_exec.h"
};

namespace preflight_details {
#include "jit/jit_asm_preflight.h"
};

constexpr size_t CYCLE_SHIFT = 33;

JitContext::JitContext(uint64_t quota) 
  : quota(quota)
  , curCycle(uint64_t(1) << CYCLE_SHIFT) 
  , stopCycle(uint64_t(0x7fffffff) << CYCLE_SHIFT)
{}

uint32_t JitContext::getCycle() { return curCycle >> CYCLE_SHIFT; }

void JitContext::incCycle() { curCycle += uint64_t(1) << CYCLE_SHIFT; }

int64_t JitContext::getQuota() { return quota; }

bool JitContext::reduceQuota(int64_t amount) { 
  quota -= amount;
  return quota >= 0;
}

uint32_t JitContext::getStopCycle() { return stopCycle >> CYCLE_SHIFT; }

void JitContext::setStopCycle(uint32_t cycle) {
  if (cycle > 0x7fffffff) {
    cycle = 0x7fffffff;
  }
  stopCycle = uint64_t(cycle) << CYCLE_SHIFT;
}

// TODO: Make this super minimal and self contained (i.e. don't use DecodedInst + getOpcode)
ExpandedInst expand(uint32_t inst) {
  if ((inst & 3) != 3) {
    static auto expandTable = rv32im::generateExpandTable();
    inst = expandTable[inst];
  }
  rv32im::DecodedInst decoded(inst);
  ExpandedInst ret;
  ret.rs1 = decoded.rs1;
  ret.rs2 = decoded.rs2;
  ret.rd = decoded.rd;
  rv32im::Opcode opcode = rv32im::getOpcode(inst);
  ret.opcode = uint8_t(opcode);
  switch(opcode) {
#define ENTRY(name, idx, op, immType, ...) \
    case rv32im::Opcode::name: ret.imm = decoded.imm ## immType(); break;
#include "rv32im/base/rv32im.inc"
#undef ENTRY
    case rv32im::Opcode::ANY:
      throw std::runtime_error("Trying to expand an illegal instruction");
  }
  return ret;
}

BlockCache::BlockCache(JitContext& ctx, JitTrace& trace, Memory& memory, uint32_t mode, bool execOnly)
  : ctx(ctx)
  , trace(trace)
  , memory(memory)
  , mode(mode)
  , a(4096)
  , execOnly(execOnly)
  , iCacheCycle(1)
{
  if (execOnly) {
    a.addBuiltins(exec_details::bytes, exec_details::bytes_len);
  } else {
    a.addBuiltins(preflight_details::bytes, preflight_details::bytes_len);
  }
  resetPoint = a.getOffset();
  uint32_t regPage = MACHINE_REGS_WORD >> MPAGE_SIZE_WORDS_PO2;
  PageDetails* regPagePtr = memory.lookup(nullptr, regPage, MODE_MACHINE, 0);
  uint32_t regOffset = (mode == MODE_MACHINE) ? (MACHINE_REGS_WORD & MPAGE_MASK_WORDS)
                                       : (USER_REGS_WORD & MPAGE_MASK_WORDS);
  regs = &((*regPagePtr)[regOffset]);
#define ENTRY(name, ...)  \
  instOffsets.push_back(execOnly ? exec_details::gsym_do_ ## name : preflight_details::gsym_do_ ## name);
#include "rv32im/base/rv32im.inc"
#undef ENTRY
}

void BlockCache::clear(uint32_t cycle) {
  a.reset(resetPoint);
  blocks.clear();
  decodeIdx.clear();
  iCacheCycle = cycle;
}

uint64_t BlockCache::invokePageMiss(uint64_t ctxAddr, uint64_t key) {
  JitContext* ctx = reinterpret_cast<JitContext*>(ctxAddr);
  return reinterpret_cast<uint64_t>(ctx->callbackObj->pageMiss(ctx, key));
};

ExitCause BlockCache::run(uint32_t& pc) {
  // Check for immediate exits
  if (ctx.getQuota() < 0) { return ExitCause::QUOTA_OUT; }
  if (ctx.getStopCycle() <= ctx.getCycle()) { return ExitCause::STOP_CYCLE; }
  // Compute worst case cycle use
  uint32_t maxCycles = std::min(
      uint32_t(ctx.getQuota() / minQuotaPerCycle),
      ctx.getStopCycle() - ctx.getCycle());
  // Make sure we have enough room to log them all
  if (ctx.getCycle() + maxCycles >= trace.inst.size()) {
    trace.inst.resize(ctx.getCycle() + maxCycles);
  }
  // Set up context
  ctx.regs = regs;
  ctx.pageTable = (mode == MODE_MACHINE) ? memory.getPhysTable() : memory.getVirtTable();
  ctx.log = trace.inst.data() + ctx.getCycle();
  ctx.pageMissFunc = invokePageMiss;
  ctx.callbackObj = &memory;
  ctx.loadKeyBase = Memory::makeKey(0, mode, ACCESS_LOAD);
  ctx.storeKeyBase = Memory::makeKey(0, mode, ACCESS_STORE);
  uint64_t ctxAddr = reinterpret_cast<uint64_t>(&ctx);
  uint32_t eoffset = (execOnly ? exec_details::gsym_enter : preflight_details::gsym_enter);
  // Enter into JIT + run loops
  uint32_t fixAddr = 0;
  while(true) {
    // Find or create block
    auto it = blocks.find(pc);
    uint32_t bstart;
    if (it == blocks.end()) {
      LOG(1, "Jitting BB = " << HexWord{pc});
      bstart = jitBlockAt(pc);
      blocks[pc] = bstart;
    } else {
      bstart = it->second;
    }
    // If we had a fixup request in prior block, do that
    if (fixAddr) {
      a.fixup(fixAddr, bstart);
    }
    // Run the block
    LOG(1, "Entering block, PC = " << HexWord{pc} << ", cycle = " << ctx.getCycle() << ", quota = " << ctx.getQuota());
    uint64_t ret = a.call(eoffset, ctxAddr, a.getAddr(bstart));
    // Split out return value
    fixAddr = ret >> 32;
    pc = ret & 0xffffffff;
    LOG(1, "  new PC = " << HexWord{pc} << ", new cycle = " << ctx.getCycle() << ", new quota = " << ctx.getQuota());
    // Maybe exit loop
    if (fixAddr == 0 && ExitCause(ctx.exitCause) != ExitCause::JALR) {
      return ExitCause(ctx.exitCause);
    }
  }
  return ExitCause::QUOTA_OUT;  // Unreachable
}

uint32_t BlockCache::jitBlockAt(uint32_t pc) {
  uint32_t blockOffset = a.getOffset();
  // Do pre-block cost analysis
  uint32_t quotaOff = a.doLoadImm32(Reg::R8, 0);
  a.doLoadImm32(Reg::R12, pc);  // Write PC so early exit know where we are
  a.doCall(execOnly ? exec_details::gsym_block_header : preflight_details::gsym_block_header);
  uint32_t cost = 0;
  bool done = false;
  while (!done) {
    DecodeEntry* decode = fetchInst(pc);
    if (!decode) {
      // Handle page fault case
      throw std::runtime_error("Unimplemented");
    }
    const auto& inst = decode->inst;
    if (rv32im::Opcode(inst.opcode) == rv32im::Opcode::ANY) {
      // Handle invalid instruction case
      throw std::runtime_error("Unimplemented");
    }
    LOG(2, "PC: " << HexWord{pc} << " - " << getOpcodeName(rv32im::Opcode(inst.opcode)) <<
           "  rd = " << uint32_t(inst.rd) << ", rs1 = " << uint32_t(inst.rs1) <<
           ", rs2 = " << uint32_t(inst.rs2) << ", imm = " << HexWord{inst.imm});
    uint32_t newPc = pc + (((decode->oinst & 3) == 3) ? 4 : 2);
    LOG(2, "inst = " << HexWord{decode->oinst} << ", newPc = " << HexWord{newPc});
    a.doLoadImm32(Reg::R8, (inst.rd == 0 ? 64 : inst.rd));
    a.doLoadImm32(Reg::R9, inst.rs1);
    a.doLoadImm32(Reg::R10, (inst.rs1 == inst.rs2) ? inst.rs2 + 64 : inst.rs2);;
    a.doLoadImm32(Reg::R11, inst.imm);
    a.doLoadImm32(Reg::R12, pc);
    a.doLoadImm32(Reg::RDX, decode->oinst);
    a.doCall(instOffsets[inst.opcode]);
    done = handleEnd(rv32im::Opcode(inst.opcode), inst.imm, pc, newPc);
    cost++;  // TODO handle variable costs
    pc = newPc;
  }
  a.fixupImm32(quotaOff, cost);
  return blockOffset;
}

// Decode a single PC
DecodeEntry* BlockCache::fetchInst(uint32_t pc) {
  auto it = decodeIdx.find(pc);
  if (it != decodeIdx.end()) {
    return &trace.decode[it->second];
  }
  // Start by fetching the word at PC
  DecodeEntry* entry = &trace.decode.emplace_back();
  auto [ok, l0] = fetchWord(entry->load0, pc / 4);
  if (!ok) {
    trace.decode.pop_back();
    return nullptr;
  }
  // If pc == 2 (mod 4), shift to lower value
  uint32_t inst = (pc % 4 == 2) ? l0 >> 16 : l0;
  uint32_t longInst;
  // Check if low bits are 11 (normal) or anything else (compressed)
  if ((inst & 3) == 3) {
    // if needed, add in second half to inst
    if (pc % 4 == 2) {
      // For unaligned addresses, always read next address
      auto [ok2, l1] = fetchWord(entry->load1, pc / 4 + 1);
      if (!ok2) {
        undoTxn(entry->load0, pc / 4);
        trace.decode.pop_back();
        return nullptr;
      }
      inst |= l1 << 16;
    } else {
      // For aligned addresses, read from a `null` word (and ignore the value)
      fetchWord(entry->load1, COMPRESSED_INST_LOOKUP_WORD, true);
    }
    longInst = inst;
  } else {
    // Remove any high bits, and then do a lookup to convert
    inst &= 0xffff;
    fetchWord(entry->load1, COMPRESSED_INST_LOOKUP_WORD + inst, true);
    longInst = entry->load1.value;
  }
  entry->pc = pc;
  entry->mode = mode;
  entry->loadCycle = ctx.getCycle();
  entry->iCacheCycle = iCacheCycle;
  entry->inst = expand(longInst);
  entry->oinst = inst;
  decodeIdx[pc] = trace.decode.size() - 1;
  // TODO: Reduce quota by cost of 1 decode
  return entry;
}

void BlockCache::undoTxn(MemTxn& save, uint32_t wordAddr) {
  uint32_t page = wordAddr >> MPAGE_SIZE_WORDS_PO2;
  uint32_t offset = wordAddr & MPAGE_MASK_WORDS;
  PageDetails* data = memory.lookup(&ctx, page, mode, ACCESS_FETCH);
  (*data)[offset] = save;
}

std::pair<bool, uint32_t> BlockCache::fetchWord(MemTxn& save, uint32_t wordAddr, bool asMachine) {
  uint32_t mmode = asMachine ? MODE_MACHINE : mode;
  uint32_t page = wordAddr >> MPAGE_SIZE_WORDS_PO2;
  uint32_t offset = wordAddr & MPAGE_MASK_WORDS;
  PageDetails* data = memory.lookup(&ctx, page, mmode, ACCESS_FETCH);
  if (!data) { return { false, 0 }; }
  save = (*data)[offset];
  (*data)[offset].cycle = 2*ctx.getCycle();
  return { true, save.value };
}

bool BlockCache::handleEnd(rv32im::Opcode opcode, uint32_t imm, uint32_t pc, uint32_t newPc) {
  switch (opcode) {
    case rv32im::Opcode::BEQ: return endBranch(CmpOp::JE, imm, pc, newPc);
    case rv32im::Opcode::BNE: return endBranch(CmpOp::JNE, imm, pc, newPc);
    case rv32im::Opcode::BLT: return endBranch(CmpOp::JL, imm, pc, newPc);
    case rv32im::Opcode::BGE: return endBranch(CmpOp::JNL, imm, pc, newPc);
    case rv32im::Opcode::BLTU: return endBranch(CmpOp::JB, imm, pc, newPc);
    case rv32im::Opcode::BGEU: return endBranch(CmpOp::JNB, imm, pc, newPc);
    case rv32im::Opcode::JAL: return endJal(imm, pc, newPc);
    case rv32im::Opcode::JALR:
    case rv32im::Opcode::ECALL:
    case rv32im::Opcode::MRET:
      return endRet();
    default: break;
  }
  return false;
}

  // Handle branch instruction
bool BlockCache::endBranch(CmpOp op, uint32_t imm, uint32_t pc, uint32_t newPc) {
  // Make a branch
  uint32_t branchFixup = a.doBranch(op, 0);
  // This will be the 'fallthough case', intially just fall through
  uint32_t fallthoughFixup = a.doLocalJump();
  // Set return value for dispatch (what to patch, where to patch to)
  uint64_t ret = (uint64_t(fallthoughFixup) << 32) | newPc;
  a.doLoadImm64(Reg::RAX, ret);
  a.doRet();
  // Ok, now handle branch patch
  uint32_t dest = pc + imm;
  uint32_t branchOffset = a.getOffset();
  a.fixup(branchFixup, branchOffset);
  ret = (uint64_t(branchFixup) << 32) | dest;
  a.doLoadImm64(Reg::RAX, ret);
  a.doRet();
  return true;
}

bool BlockCache::endJal(uint32_t imm, uint32_t pc, uint32_t newPc) {
  uint32_t fallthoughFixup = a.doLocalJump();
  uint32_t jmpPc = pc + imm;
  uint64_t ret = (uint64_t(fallthoughFixup) << 32) | jmpPc;
  a.doLoadImm64(Reg::RAX, ret);
  a.doRet();
  return true;
}

bool BlockCache::endRet() {
  a.doRet();
  return true;
}

}  // namespace risc0::rv32im::jit
