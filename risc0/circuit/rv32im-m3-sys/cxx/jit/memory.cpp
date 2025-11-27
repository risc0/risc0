#include "jit/memory.h"

namespace risc0::jit {

uint64_t Memory::makeKey(uint32_t page, uint32_t mode, uint32_t access) {
  if (mode == MODE_MACHINE) { access = 3; }
  return page | (mode << 30) | (access << 28);
}
uint32_t Memory::getPage(uint64_t key) { return key & 0x0fffffff; }
uint32_t Memory::getMode(uint64_t key) { return (key >> 30) & 3; }
uint32_t Memory::getAccess(uint64_t key) { return (key >> 28) & 3; }

Memory::Memory(risc0::rv32im::MemoryImage& image, JitTrace& trace)
  : image(image)
  , trace(trace) 
  , iCacheCycle(1)
{}

uint32_t Memory::peekPhysical(JitContext* ctx, uint32_t wordAddr) {
  uint32_t page = wordAddr >> MPAGE_SIZE_WORDS_PO2;
  uint32_t offset = wordAddr & MPAGE_MASK_WORDS;
  PageDetails* data = lookup(ctx, page, MODE_MACHINE, ACCESS_LOAD);
  return (*data)[offset].value;
}

PageDetails* Memory::lookup(JitContext* ctx, uint32_t vpage, uint32_t mode, uint32_t access) {
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
  uint32_t ppage = virtToPhys(vpage / 4, mode, access) * 4 + (vpage % 4);
  // Now lookup physical page
  data = lookup(ctx, ppage, MODE_MACHINE, 0);
  // Set into virt table + return
  virt.set(key, reinterpret_cast<uint64_t>(data));
  return data;
}

PageDetails* Memory::pageMiss(JitContext* ctx, uint64_t key) {
  return lookup(ctx, getPage(key), getMode(key), getAccess(key));
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
  // TODO: identity map for now
  return vpage;
}

}  // namespace risc0::jit
