#pragma once

#include "jit/fast_map.h"
#include "jit/trace.h"
#include "rv32im/base/constants.h"

namespace risc0::jit {

class JitContext;

using PageDetails = std::array<MemTxn, MPAGE_SIZE_WORDS>;

class Memory {
  // PO2 of worst case # of pages (2^16) times 4 (to make sure fullness < 1/4th)
  constexpr static size_t MAP_PO2 = 18;

public:
  static uint64_t makeKey(uint32_t page, uint32_t mode, uint32_t access);
  static uint32_t getPage(uint64_t key);
  static uint32_t getMode(uint64_t key);
  static uint32_t getAccess(uint64_t key);

  // Construct
  Memory(risc0::rv32im::MemoryImage& image, JitTrace& trace);

  // Peek at physical memory, might induce page in, but otherwise
  // free of side effects
  uint32_t peekPhysical(JitContext* ctx, uint32_t wordAddr);

  // Do a page lookup, here pages are at 1k granularity
  // If VM resolution fails (page fault, etc), return nullptr
  PageDetails* lookup(JitContext* ctx, uint32_t vpage, uint32_t mode, uint32_t access);
  PageDetails* pageMiss(JitContext* ctx, uint64_t key);

  // Reset virtual memory state (i.e. bump iCacheCycle)
  void clearVM(uint32_t cycle);

  // Commit memory at end of segment
  void commit();

  // Let asm code peek into details
  void* getPhysTable() { return phys.getTable(); } 
  void* getVirtTable() { return virt.getTable(); } 

private:
  // Do a page lookup, here pages are at 4k granularity
  uint32_t virtToPhys(uint32_t vpage, uint32_t mode, uint32_t access);

  risc0::rv32im::MemoryImage& image;
  JitTrace& trace;
  uint32_t iCacheCycle;
  // Map key:
  //   uint64_t key = vpage | (mode << 30) | (access < 28);
  //   Except when mode == MACHINE, access is 3
  FastMap<MAP_PO2> phys;  // Physical page key (MPAGE size) -> actual data
  FastMap<MAP_PO2> virt;  // Virtual page key (MPAGE size) -> actual data
  FastMap<MAP_PO2> vmPage;  // Virtual page key (VPAGE size) -> translation entry index
};

};
