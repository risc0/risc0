#include "core/log.h"
#include "jit/memory.h"
#include "jit/intel_asm.h"

namespace risc0::jit {

class BlockCache;

// TODO: Make this real
// How much quota does the smallest cycle take
constexpr uint64_t minQuotaPerCycle = 1;

// State passed to JIT code
class JitContext {
  friend BlockCache;
public:
  JitContext(uint64_t quota);

  uint32_t getCycle();
  void incCycle();

  int64_t getQuota();
  // Returns true is quota is still >= 0
  bool reduceQuota(int64_t amount);

  uint32_t getStopCycle();
  void setStopCycle(uint32_t cycle);

private:
  MemTxn* regs;
  void* pageTable;
  InstEntry* log;
  int64_t quota;
  uint64_t curCycle;
  uint64_t stopCycle;
  uint64_t exitCause;
  FuncPtr2 pageMissFunc;
  Memory* callbackObj;
  uint64_t loadKeyBase;
  uint64_t storeKeyBase;
};

enum class ExitCause {
  QUOTA_OUT = 0,
  STOP_CYCLE = 1,
  ECALL = 2,
  ALIGNMENT = 3,
  MRET = 4,
  JALR = 5,
  ANY = 6,
};

class BlockCache {
public:
  BlockCache(JitContext& ctx, JitTrace& trace, Memory& memory, uint32_t mode, bool execOnly);

  // Enter at PC, run until some event, return cause, update PC
  ExitCause run(uint32_t& pc);

  // Clear
  void clear(uint32_t cycle);

private:
  JitContext& ctx;
  JitTrace& trace;
  Memory& memory;
  uint32_t mode;
  Assembler a;
  bool execOnly;
  MemTxn* regs;
  uint32_t iCacheCycle;
  uint32_t resetPoint;
  std::map<uint32_t, uint32_t> blocks;  // TODO: Make accessable from ASM
  std::map<uint32_t, uint32_t> decodeIdx;
  std::vector<uint32_t> instOffsets;

  uint32_t jitBlockAt(uint32_t pc);
  DecodeEntry* fetchInst(uint32_t pc);
  std::pair<bool, uint32_t> fetchWord(MemTxn& save, uint32_t wordAddr, bool asMachine = false);
  void undoTxn(MemTxn& save, uint32_t wordAddr);

  static uint64_t invokePageMiss(uint64_t ctxAddr, uint64_t key);
  bool handleEnd(rv32im::Opcode opcode, uint32_t imm, uint32_t pc, uint32_t newPc);
  bool endBranch(CmpOp op, uint32_t imm, uint32_t pc, uint32_t newPc);
  bool endJal(uint32_t imm, uint32_t pc, uint32_t newPc);
  bool endRet();
};

}  // namespace risc0::jit
