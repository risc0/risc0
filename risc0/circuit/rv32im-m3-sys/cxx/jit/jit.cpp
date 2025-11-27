#include "jit/jit.h"

#include "core/log.h"
#include "jit/block_cache.h"
#include "jit/memory.h"

using namespace risc0::rv32im;

namespace risc0::jit {

struct Jit {
  JitContext ctx;
  JitTrace& trace;
  HostIO& io;
  Memory memory;
  BlockCache user;
  BlockCache supervisor;
  BlockCache machine;
  bool v2Compat;
  uint32_t mode;
  uint32_t pc;

  Jit(JitTrace& trace, MemoryImage& image, HostIO& io, size_t quota, bool execOnly) 
    : ctx(quota)
    , trace(trace)
    , io(io)
    , memory(image, trace)
    , user(ctx, trace, memory, MODE_USER, execOnly)
    , supervisor(ctx, trace, memory, MODE_SUPERVISOR, execOnly)
    , machine(ctx, trace, memory, MODE_MACHINE, execOnly)
  {}

  uint32_t peek(uint32_t wordAddr) {
    uint32_t page = wordAddr >> MPAGE_SIZE_WORDS_PO2;
    uint32_t offset = wordAddr & MPAGE_MASK_WORDS;
    PageDetails* data = memory.lookup(&ctx, page, MODE_MACHINE, ACCESS_LOAD);
    return (*data)[offset].value;
  }

  uint32_t read(MemTxn& txn, uint32_t wordAddr) {
    uint32_t page = wordAddr >> MPAGE_SIZE_WORDS_PO2;
    uint32_t offset = wordAddr & MPAGE_MASK_WORDS;
    PageDetails* data = memory.lookup(&ctx, page, MODE_MACHINE, ACCESS_LOAD);
    txn = (*data)[offset];
    (*data)[offset].cycle = ctx.getCycle() * 2;
    return txn.value;
  }

  void write(MemTxn& txn, uint32_t wordAddr, uint32_t value) {
    uint32_t page = wordAddr >> MPAGE_SIZE_WORDS_PO2;
    uint32_t offset = wordAddr & MPAGE_MASK_WORDS;
    PageDetails* data = memory.lookup(&ctx, page, MODE_MACHINE, ACCESS_LOAD);
    txn = (*data)[offset];
    txn.value = value;
    (*data)[offset].cycle = ctx.getCycle() * 2 + 1;
    (*data)[offset].value = value;
  }

  void trapInst() {
    throw std::runtime_error("Trap Inst");
  }

  void trapFetch() {
    throw std::runtime_error("Trap Fetch");
  }

  void resume() {
    v2Compat = !read(trace.resume.readCompat, CSR_WORD(MNOV2COMPAT));
    if (v2Compat) {
      mode = read(trace.resume.readMode, V2_COMPAT_SMODE) ? MODE_MACHINE : MODE_USER;
      pc = read(trace.resume.readPc, V2_COMPAT_SPC);
    } else {
      mode = read(trace.resume.readMode, CSR_WORD(MSMODE));
      pc = read(trace.resume.readPc, CSR_WORD(MSPC));
    }
  }

  void suspend() {
    // TODO
  }

  bool ecall() {
    return true;
  }

  void mret() {
    if (mode != MODE_MACHINE) {
     trapInst();
    }
    InstEntry& ie = trace.inst[ctx.getCycle()];
    ie.inst.opcode = uint8_t(Opcode::MRET);
    ie.extra = trace.mrets.size();
    trace.mrets.emplace_back();
    MretEntry& me = trace.mrets.back();
    pc = read(me.readPc, CSR_WORD(MEPC));
    mode = read(me.readMode, CSR_WORD(MEMODE));
    write(me.updateClearCache, CSR_WORD(MCLEARCACHE), 0);
    if (me.updateClearCache.value) {
      throw std::runtime_error("TIME TO CLEAR THE CACHE");
    }
    write(me.writeCycle, CSR_WORD(MSCYCLE), ctx.getCycle() + 1);
    ctx.setStopCycle(ctx.getCycle() + peek(CSR_WORD(MCOUNTDOWN)));
  }

  bool run() {
    resume();
    while(true) {
      ExitCause ec;
      switch(mode) {
        case MODE_USER:
          ec = user.run(pc);
          break;
        case MODE_SUPERVISOR:
          ec = supervisor.run(pc);
          break;
        case MODE_MACHINE:
          ec = machine.run(pc);
          break;
      }
      switch(ec) {
        case ExitCause::QUOTA_OUT:
          suspend();
          return false;
        case ExitCause::STOP_CYCLE:
          // TODO: handle interrupt
          throw std::runtime_error("STOP CYCLE");
        case ExitCause::ECALL:
          if (ecall()) {
            LOG(0, "ECALL TERMINATE");
            return true;
          }
          break;
        case ExitCause::ALIGNMENT:
          throw std::runtime_error("Alignment");
        case ExitCause::MRET:
          mret();
          break;
        case ExitCause::ANY:
          trapInst();
          break;
        default:
          LOG(0, "Mystery exit cause: " << uint32_t(ec));
          throw std::runtime_error("Invalid exit cause");
      }
    }
    return true;  // Unreachable
  }
};

bool doJit(JitTrace& trace, MemoryImage& image, HostIO& io, size_t quota, bool execOnly) {
  Jit jit(trace, image, io, quota, execOnly);
  return jit.run();
}

}  // namespace risc0::jit
