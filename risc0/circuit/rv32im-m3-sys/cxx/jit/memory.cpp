#include "jit/memory.h"

#include "jit/block_cache.h"

namespace risc0::jit {

uint64_t Memory::makeKey(uint32_t page, uint32_t mode, uint32_t access) {
  if (mode == MODE_MACHINE) { access = 3; }
  return page | (mode << 30) | (access << 28);
}
uint32_t Memory::getPage(uint64_t key) { return key & 0x0fffffff; }
uint32_t Memory::getMode(uint64_t key) { return (key >> 30) & 3; }
uint32_t Memory::getAccess(uint64_t key) { return (key >> 28) & 3; }

Memory::Memory(risc0::rv32im::MemoryImage& image, JitTrace& trace, JitContext& ctx)
  : image(image)
  , trace(trace)
  , ctx(ctx)
  , iCacheCycle(1)
{}

uint32_t Memory::peekPhysical(uint32_t wordAddr) {
  uint32_t page = wordAddr >> MPAGE_SIZE_WORDS_PO2;
  uint32_t offset = wordAddr & MPAGE_MASK_WORDS;
  PageDetails* data = lookup(page, MODE_MACHINE, ACCESS_LOAD);
  return (*data)[offset].value;
}

uint32_t Memory::readPhysical(MemTxn& txn, uint32_t wordAddr) {
  uint32_t page = wordAddr >> MPAGE_SIZE_WORDS_PO2;
  uint32_t offset = wordAddr & MPAGE_MASK_WORDS;
  PageDetails* data = lookup(page, MODE_MACHINE, ACCESS_LOAD);
  txn = (*data)[offset];
  (*data)[offset].cycle = ctx.getCycle() * 2;
  return txn.value;
}

void Memory::writePhysical(MemTxn& txn, uint32_t wordAddr, uint32_t value) {
  uint32_t page = wordAddr >> MPAGE_SIZE_WORDS_PO2;
  uint32_t offset = wordAddr & MPAGE_MASK_WORDS;
  PageDetails* data = lookup(page, MODE_MACHINE, ACCESS_LOAD);
  txn = (*data)[offset];
  (*data)[offset].cycle = ctx.getCycle() * 2 + 1;
  (*data)[offset].value = value;
}

void Memory::undoTxn(MemTxn& old, uint32_t wordAddr) {
  uint32_t page = wordAddr >> MPAGE_SIZE_WORDS_PO2;
  uint32_t offset = wordAddr & MPAGE_MASK_WORDS;
  PageDetails* data = lookup(page, MODE_MACHINE, ACCESS_LOAD);
  (*data)[offset] = old;
}

PageDetails* Memory::lookup(uint32_t vpage, uint32_t mode, uint32_t access) {
  // TODO: Compute and reduce quota
  uint64_t key = makeKey(vpage, mode, access);
  if (mode == MODE_MACHINE) {
    // Do lookup
    PageDetails* data = reinterpret_cast<PageDetails*>(phys.lookup(key));
    // If match, early exit
    if (data) { return data; }
    // Otherwise, copy page 
    data = new PageDetails;
    rv32im::PagePtr ipage = image.getPage(vpage);
    for (size_t i = 0; i < MPAGE_SIZE_WORDS; i++) {
      (*data)[i].value = (*ipage)[i];
      (*data)[i].cycle = 0;
    }
    // Add into map + return
    phys.set(key, reinterpret_cast<uint64_t>(data));
    return data;
  }
  // Lookup and early return if found
  PageDetails* data = reinterpret_cast<PageDetails*>(virt.lookup(key));
  if (data) { return data; }
  // Resolve page, convert from MPAGE -> VPAGE and back
  uint32_t ppage = virtToPhys(vpage / 4, mode, access);
  if (ppage == 0xffffffff) {
    return nullptr;
  }
  ppage = ppage * 4 + (vpage % 4);
  // Now lookup physical page
  data = lookup(ppage, MODE_MACHINE, 0);
  // Set into virt table + return
  virt.set(key, reinterpret_cast<uint64_t>(data));
  return data;
}

PageDetails* Memory::pageMiss(uint64_t key) {
  return lookup(getPage(key), getMode(key), getAccess(key));
}

void Memory::clearVM(uint32_t cycle) {
  iCacheCycle = cycle;
  virt.clear();
  vmPage.clear();
}

void Memory::commit() {
  // TODO: commit to image
}

uint32_t Memory::virtToPhys(uint32_t vpage, uint32_t mode, uint32_t access) {
  uint32_t key = makeKey(vpage, mode, access);
  uint32_t vmIdx = vmPage.lookup(key);
  if (vmIdx != 0) { 
    return trace.translate[vmIdx - 1].ppage; 
  }
  AddrTranslateEntry entry;
  entry.key = key;
  entry.loadCycle = ctx.getCycle();
  entry.iCacheCycle = iCacheCycle;
  uint32_t vinfo = readPhysical(entry.loadInfo, CSR_WORD(MVINFO));
  if ((vinfo & 0x80000000) == 0) {
    readPhysical(entry.loadPTE[0], MACHINE_REGS_WORD);
    readPhysical(entry.loadPTE[1], MACHINE_REGS_WORD + 64);
    entry.ppage = vpage;
    trace.translate.push_back(entry);
    vmPage.set(key, trace.translate.size());
    return vpage;
  }
  uint32_t a = vinfo << 12;
  uint32_t smode = mode == MODE_SUPERVISOR;
  uint32_t sum = (vinfo >> 29) & 1;
  uint32_t mxr = (vinfo >> 30) & 1;
  uint32_t i, xwr, pte, pteAddr;
  uint32_t saveAddr[2];
  bool err = false;
  for (i = 2; i-- > 0;) {
    pteAddr = a + ((vpage >> (10 * i)) & 0x3ff)*4;
    err |= (pteAddr >= FIRMWARE_START_ADDR);
    saveAddr[i] = pteAddr/4;
    pte = readPhysical(entry.loadPTE[i], pteAddr/4);
    err |= ((pte & 1) == 0);
    xwr = (pte >> 1) & 7;
    err |= (xwr == 2 || xwr == 6);
    a = (pte << 2) & 0xfffff000;
    if (xwr != 0) break;
  }
  err |= (!xwr);
  if (i == 1) {
    readPhysical(entry.loadPTE[0], MACHINE_REGS_WORD);
    err |= (((pte >> 10) & 0x3ff) != 0);
    a |= ((vpage & 0x3ff) << 12);
  }
  uint32_t u = (pte >> 4) & 1;
  uint32_t x = (pte >> 3) & 1;
  uint32_t w = (pte >> 2) & 1;
  uint32_t r = (pte >> 1) & 1;
  if (mxr && x) { r = 1; }
  err |= (!u && !smode);
  err |= (u && !sum && smode);
  err |= 
     ((access == ACCESS_FETCH && !x) ||
      (access == ACCESS_LOAD && !r) ||
      (access == ACCESS_STORE && !w));
  pte |= (1 << 6);  // Set A bit always
  if (access== ACCESS_STORE) { pte |= (1 << 7); } // Set D if write
  // Note: we already copied old state on read txn, so don't copy it again
  MemTxn ignore;
  writePhysical(ignore, pteAddr/4, pte);
  if (err) {
    static uint32_t count = 0;
    LOG(0, "Page translation error: vpage = " << HexWord{vpage} << ", mode = " << mode << ", access = " << access);
    undoTxn(entry.loadInfo, CSR_WORD(MVINFO));
    undoTxn(entry.loadPTE[0], saveAddr[0]);
    undoTxn(entry.loadPTE[1], saveAddr[1]);
    setR0LogLevel(2);
    count++;
    if (count == 2) {
      throw std::runtime_error("FAILED");
    }
    return 0xffffffff;
  }
  entry.ppage = a >> 12;
  //LOG(0, "vPage=" << HexWord{vpage} << ", pPage=" << HexWord{entry.ppage} << ", mode=" << mode << ", access = " << access);
  trace.translate.push_back(entry);
  vmPage.set(key, trace.translate.size());
  return entry.ppage;
}

}  // namespace risc0::jit
