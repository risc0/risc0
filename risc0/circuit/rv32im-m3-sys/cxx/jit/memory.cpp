#include "jit/memory.h"

namespace risc0::jit {

Memory::Memory(risc0::rv32im::MemoryImage& image, JitTrace& trace)
  : image(image)
  , trace(trace) 
  , iCacheCycle(1)
{}

uint32_t Memory::readPhysical(uint32_t cycle, MemTxn& savePrev, uint32_t wordAddr) {
  uint32_t page = wordAddr >> MPAGE_SIZE_WORDS_PO2;
  uint32_t offset = wordAddr & MPAGE_MASK_WORDS;
  PageDetails* data = lookup(page, MODE_MACHINE, 0);
  savePrev = (*data)[offset];
  (*data)[offset].cycle = 2*cycle;
  return savePrev.value;
}

void Memory::writePhysical(uint32_t cycle, MemTxn& savePrev, uint32_t wordAddr, uint32_t value) {
  uint32_t page = wordAddr >> MPAGE_SIZE_WORDS_PO2;
  uint32_t offset = wordAddr & MPAGE_MASK_WORDS;
  PageDetails* data = lookup(page, MODE_MACHINE, 0);
  savePrev = (*data)[offset];
  (*data)[offset].cycle = 2*cycle;
  (*data)[offset].value = value;
}

void Memory::undoPhysical(const MemTxn& prev, uint32_t wordAddr) {
  uint32_t page = wordAddr >> MPAGE_SIZE_WORDS_PO2;
  uint32_t offset = wordAddr & MPAGE_MASK_WORDS;
  PageDetails* data = lookup(page, MODE_MACHINE, 0);
  (*data)[offset] = prev;
}

PageDetails* Memory::lookup(uint32_t vpage, uint32_t mode, uint32_t access) {
  if (mode == MODE_MACHINE) {
    // Make key
    uint64_t key = vpage | 0xf0000000;
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
  // Make key
  uint64_t key = vpage | (mode << 30) | (access << 28);
  // Lookup and early return if found
  PageDetails* data = reinterpret_cast<PageDetails*>(virt.lookup(key));
  if (data) { return data; }
  // Resolve page, convert from MPAGE -> VPAGE and back
  uint32_t ppage = virtToPhys(vpage / 4, mode, access) * 4 + (vpage % 4);
  // Now lookup physical page
  data = lookup(ppage, MODE_MACHINE, 0);
  // Set into virt table + return
  virt.set(key, reinterpret_cast<uint64_t>(data));
  return data;
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
