// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "rv32im/emu/emu.h"

using namespace risc0;
using namespace risc0::rv32im;

struct DebugHostIO : public HostIO {
  std::string holdLinux;
  uint32_t onWrite(uint32_t fd, const uint8_t* data, uint32_t size) override {
    if (size == 0) {
      return 0;
    }
    std::string str(reinterpret_cast<const char*>(data), size);
    if (fd == uint32_t(-1)) {
      std::cout << str;
    } else {
      LOG(fd, std::string(reinterpret_cast<const char*>(data), size));
    }
    return size;
  }
  uint32_t onRead(uint32_t fd, uint8_t* data, uint32_t size) override { return 0; }
};

void loadFileIntoMemory(std::map<uint32_t, uint32_t>& words, const char* filename, uint32_t addr) {
  // Load actual file
  auto bytes = risc0::loadFile(filename);
  LOG(0, "LOADING " << filename << ": size = " << bytes.size());
  // Make sure it is a even number of words
  bytes.resize(((bytes.size() + 3) / 4) * 4);
  // Load dts into memory at kaddr
  for (size_t i = 0; i < bytes.size() / 4; i++) {
    uint32_t word = 0;
    for (size_t j = 0; j < 4; j++) {
      word |= bytes[4 * i + j] << (8 * j);
    }
    words[addr / 4 + i] = word;
  }
}

int main() {
  // Make an empty memory state
  std::map<uint32_t, uint32_t> words;

  // Setup instruction expansion table
  fillExpandTable(words);
  // Load firmware
  uint32_t firmwareEntry = loadRaw(words, "firmware/firmware");
  // Set resume state to jump into firmware entry
  words[CSR_WORD(MNOV2COMPAT)] = 1;
  words[CSR_WORD(MSPC)] = firmwareEntry;
  words[CSR_WORD(MSMODE)] = MODE_MACHINE;
  // Load kernel
  uint32_t kernelEntry = loadRaw(words, "linux/linux.elf");
  // Set firmware to jump to kernel
  words[CSR_WORD(MEPC)] = kernelEntry;
  words[CSR_WORD(MEMODE)] = MODE_SUPERVISOR;
  // Load DTB in highish kernel memory
  loadFileIntoMemory(words, "linux/risc0.dtb", 0xe0000000);
  // Set 'inputs' to kernel:
  words[USER_REGS_WORD + REG_A0] = 0;          // Hart 0
  words[USER_REGS_WORD + REG_A1] = 0xe0000000; // DTB
  // Load root fs into 0xe1000000
  loadFileIntoMemory(words, "linux/rootfs.cpio", 0xe1000000);

  // Make an image
  auto image = MemoryImage::fromWords(words);

  // Run
  DebugHostIO io;
  LOG(0, "Executing");
  while (true) {
    size_t rows = 1024 * 1024;
    std::vector<RowInfo> ri(rows);
    std::vector<uint32_t> aux(rows * computeMaxWitPerRow());
    Trace trace(rows, ri.data(), aux.data());
    bool done = emulate(trace, image, io, rows);
    if (done)
      break;
  }
}
