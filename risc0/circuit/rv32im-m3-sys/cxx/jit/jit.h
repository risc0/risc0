#include "rv32im/emu/emu.h"

namespace risc0::rv32im::jit {

struct ExpandedInst {
  uint8_t opcode;
  uint8_t rs1;
  uint8_t rs2;
  uint8_t rd;
  uint32_t imm;
};

struct MemTxn {
  uint32_t value;
  uint32_t cycle;
};

struct InstEntry {
  ExpandedInst inst;
  uint32_t pc;
  uint32_t origInst;
  uint32_t iCacheCycle;
  uint32_t unitId;
  MemTxn rd;
  MemTxn rs1;
  MemTxn rs2;
};

struct DecodeEntry {
  uint32_t pc;
  uint32_t mode;
  uint32_t loadCycle;
  uint32_t iCacheCycle;
  MemTxn load0;
  MemTxn load1;
  ExpandedInst inst;
};

struct AddrTranslateEntry {
  uint32_t vaddr;
  uint32_t paddr;
  MemTxn load0;
  MemTxn load1;
};

struct PageEntry {
  uint32_t page;
  PagePtr origPage;
  PagePtr finalPage;
};

struct JitTrace {
  size_t totCycles;
  // List of all instructions executed, preflight only
  std::vector<InstEntry> inst;
  // List of all instructions decoded, preflight only
  std::vector<DecodeEntry> decode; 
  // List of all VM translations, preflight only
  std::vector<AddrTranslateEntry> translate;
  // Page pre + and post state, always valid
  std::vector<PageEntry> pages;
};

bool doJit(JitTrace& trace, MemoryImage& image, HostIO& io, size_t quota, bool execOnly = false);

}  // namespace risc0::rv32im::jit
