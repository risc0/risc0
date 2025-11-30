#include "jit/jit.h"

#include "core/log.h"
#include "jit/block_cache.h"
#include "jit/memory.h"

using namespace risc0::rv32im;

extern FILE* pcFile;

namespace risc0::jit {

struct Jit {
  JitContext ctx;
  JitTrace& trace;
  HostIO& io;
  Memory memory;
  BlockCache user;
  BlockCache supervisor;
  BlockCache machine;
  bool execOnly;
  bool v2Compat;
  uint32_t mode;
  uint32_t pc;

  Jit(JitTrace& trace, MemoryImage& image, HostIO& io, size_t quota, bool execOnly) 
    : ctx(quota)
    , trace(trace)
    , io(io)
    , memory(image, trace, ctx)
    , user(ctx, trace, memory, MODE_USER, execOnly)
    , supervisor(ctx, trace, memory, MODE_SUPERVISOR, execOnly)
    , machine(ctx, trace, memory, MODE_MACHINE, execOnly)
    , execOnly(execOnly)
  {}

  uint8_t peekByte(uint32_t addr) {
    return uint8_t(peek(addr / 4) >> ((addr % 4) * 8));
  }
  uint32_t peek(uint32_t wordAddr) { 
    return memory.peekPhysical(wordAddr); 
  }
  uint32_t read(MemTxn& txn, uint32_t wordAddr) {
    return memory.readPhysical(txn, wordAddr);
  }
  void write(MemTxn& txn, uint32_t wordAddr, uint32_t value) {
    return memory.writePhysical(txn, wordAddr, value);
  }

  void trap(uint32_t type, uint32_t val) {
    LOG(1, "Doing TRAP, type = " << type << ", val = " << HexWord{val});
    if (mode == MODE_MACHINE) {
      LOG(0, "Double TRAP");
      LOG(0, "  Type = " << type << ", val = " << val);
      LOG(0, "  PC = " << HexWord{pc} << ", cycle = " << ctx.getCycle());
      throw std::runtime_error("Double trap");
    }
    if (!execOnly) {
      InstEntry& ie = trace.inst[ctx.getCycle()];
      ie.inst.opcode = uint8_t(Opcode::ANY);  // Use 'any' for traps
      ie.extra = trace.traps.size();
    }
    TrapEntry te;
    write(te.writePc, CSR_WORD(MEPC), pc);
    write(te.writeMode, CSR_WORD(MEMODE), mode);
    write(te.writeVal, CSR_WORD(MTVAL), val);
    uint32_t dispatch;
    switch (type) {
      case TRAP_ECALL: dispatch = CSR_WORD(MTRAPECALL); break;
      case TRAP_INST: dispatch = CSR_WORD(MTRAPINST); break;
      case TRAP_FETCH: dispatch = CSR_WORD(MTRAPFETCH); break;
      case TRAP_INTER: dispatch = CSR_WORD(MTRAPINTER); break;
      default:
        throw std::runtime_error("Invalid trap type");
    }
    pc = read(te.readDispatch, dispatch);
    mode = MODE_MACHINE;
    uint32_t oldCycle = read(te.readCycle, CSR_WORD(MSCYCLE));
    uint32_t delta = ctx.getCycle() - oldCycle;
    uint64_t time = peek(CSR_WORD(MTIME)) | (uint64_t(peek(CSR_WORD(MTIMEH))) << 32);
    time += delta;
    write(te.updateTime, CSR_WORD(MTIME), time & 0xffffffff);
    write(te.updateTimeh, CSR_WORD(MTIMEH), time >> 32);
    if (!execOnly) {
      trace.traps.push_back(te);
    }
    ctx.setStopCycle(0x7fffffff);
    ctx.incCycle();
  }

  void resume() {
    if (pcFile) {
      uint32_t readPc;
      fread(&readPc, sizeof(uint32_t), 1, pcFile);
    }
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

  void ecallTerminate() {
    LOG(0, "DONE");
  }

  void ecallRead() {
    uint32_t fd = peek(MACHINE_REGS_WORD + REG_A0);
    uint32_t addr = peek(MACHINE_REGS_WORD + REG_A1);
    uint32_t len = peek(MACHINE_REGS_WORD + REG_A2);
    LOG(0, "Ecall Read: " << fd << ", " << addr << ", " << len);
    throw std::runtime_error("Unimplemented");
  }

  void ecallWrite() {
    uint32_t fd = peek(MACHINE_REGS_WORD + REG_A0);
    uint32_t addr = peek(MACHINE_REGS_WORD + REG_A1);
    uint32_t len = peek(MACHINE_REGS_WORD + REG_A2);
    // LOG(0, "Ecall Write: " << fd << ", " << addr << ", " << len);
    std::vector<uint8_t> data;
    for (size_t i = 0; i < len; i++) {
      data.push_back(peekByte(addr + i));
    }
    uint32_t rlen = io.onWrite(fd, data.data(), len);
    MemTxn ignore;
    write(ignore, MACHINE_REGS_WORD + REG_A0, rlen);
    ctx.incCycle();
    pc += 4;
  }

  bool ecall() {
    if (mode != MODE_MACHINE) {
      trap(TRAP_ECALL, 0x00000073);
      return false;
    }
    uint32_t id = peek(MACHINE_REGS_WORD + REG_A7);
    switch(id) {
      case HOST_ECALL_TERMINATE:
        ecallTerminate();
        return true;
      case HOST_ECALL_READ:
        ecallRead();
        return false;
      case HOST_ECALL_WRITE:
        ecallWrite();
        return false;
      default:
        LOG(0, "Unimplement machine mode ecall: " << id);
        throw std::runtime_error("Unimplemented ecall");
    }
    return true;
  }

  void mret() {
    if (mode != MODE_MACHINE) {
      trap(TRAP_INST, 0x30200073);
      return;
    }
    if (!execOnly) {
      // Add extra to the entry
      InstEntry& ie = trace.inst[ctx.getCycle()];
      ie.extra = trace.mrets.size();
    }
    MretEntry me;
    pc = read(me.readPc, CSR_WORD(MEPC));
    mode = read(me.readMode, CSR_WORD(MEMODE));
    write(me.updateClearCache, CSR_WORD(MCLEARCACHE), 0);
    write(me.writeCycle, CSR_WORD(MSCYCLE), ctx.getCycle() + 1);
    if (!execOnly) {
      trace.mrets.push_back(me);
    }
    if (me.updateClearCache.value) {
      //LOG(0, "Clearing cache");
      user.clear(ctx.getCycle());
      supervisor.clear(ctx.getCycle());
      memory.clearVM(ctx.getCycle());
    }
    ctx.incCycle();
    ctx.setStopCycle(ctx.getCycle() + peek(CSR_WORD(MCOUNTDOWN)));
  }

  bool run() {
    resume();
    while(true) {
      size_t origCycle = ctx.getCycle();
      ExitCause ec = ExitCause(0);
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
          LOG(0, "Suspending due to quota");
          return false;
        case ExitCause::STOP_CYCLE:
          // Clear stop cycle
          //setR0LogLevel(2);
          trap(TRAP_INTER, 0);
          break;
        case ExitCause::ECALL:
          if (ecall()) {
            LOG(0, "ECALL TERMINATE");
            return true;
          }
          break;
        case ExitCause::MRET:
          mret();
          break;
        case ExitCause::ALIGNMENT:
        case ExitCause::ANY:
          if (execOnly) {
            trap(TRAP_INST, trace.inst[0].origInst);
          } else {
            trap(TRAP_INST, trace.inst[ctx.getCycle()].origInst);
          }
          break;
        case ExitCause::FETCH:
          trap(TRAP_FETCH, pc);
          break;
        default:
          LOG(0, "Mystery exit cause: " << uint32_t(ec));
          throw std::runtime_error("Invalid exit cause");
      }
      if (pcFile) {
        for (size_t i = origCycle; i < ctx.getCycle(); i++) {
          uint32_t readPc;
          uint32_t iPc = trace.inst[i].pc;
          Opcode iOp = Opcode(trace.inst[i].inst.opcode);
          fread(&readPc, sizeof(uint32_t), 1, pcFile);
          //LOG(0, "i = " << i << ", pc = " << pc << "inst = " << getOpcodeName(iOp));
          if (readPc != trace.inst[i].pc) {
            LOG(0, "PC mismatch: cycle = " << i << ", readPc = " << HexWord{readPc} << ", recordedPc = " << HexWord{trace.inst[i].pc});
            throw std::runtime_error("So sad");
          }
        }
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
