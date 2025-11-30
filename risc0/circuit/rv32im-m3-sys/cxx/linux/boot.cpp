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

#define USE_JIT YES

#ifdef USE_JIT
#include "jit/jit.h"
#else
#include "rv32im/emu/emu.h"
#endif


using namespace risc0;
using namespace risc0::rv32im;

#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

struct DebugHostIO : public HostIO {
  std::string holdLinux;
  uint32_t onWrite(uint32_t fd, const uint8_t* data, uint32_t size) override {
    if (size == 0) {
      return 0;
    }
    if (fd == uint32_t(-1)) {
      fwrite(data, 1, size, stdout);
      fflush(stdout);
    } else {
      LOG(0, std::string(reinterpret_cast<const char*>(data), size));
    }
    return size;
  }

  uint32_t onRead(uint32_t fd, uint8_t* data, uint32_t size) override {
    if (size == 0) { return 0; }
    char c;
    ssize_t bytes_read = read(STDIN_FILENO, &c, 1);

    if (bytes_read > 0) {
      data[0] = c;
      return 1;
    } else {
      return 0;
    }
    return 0;
  }
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

extern FILE* pcFile;

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

  /*
  // Setup keyboard input goo
  int flags = fcntl(STDIN_FILENO, F_GETFL, 0); // Get current flags
  fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK); // Add O_NONBLOCK
  struct termios old_tio, new_tio;

  // Get current terminal settings
  tcgetattr(STDIN_FILENO, &old_tio);
  new_tio = old_tio;

  // Disable canonical mode (ICANON) and echo (ECHO)
  new_tio.c_lflag &= ~(ICANON | ECHO);

  // Set the new terminal settings
  tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
  */

  //pcFile = fopen("/tmp/pcs", "rb");

  // Run
  DebugHostIO io;
  LOG(0, "Executing");
  size_t i = 0;
  while (true) {
    size_t rows = 1024 * 1024;
    std::vector<RowInfo> ri(rows);
    std::vector<uint32_t> aux(rows * computeMaxWitPerRow());
#ifdef USE_JIT
    using namespace risc0::jit;
    JitTrace trace;
    bool done = doJit(trace, image, io, 500 * rows, false);
    LOG(0, "HEY, done = " << done);
    break;
#else
    Trace trace(rows, ri.data(), aux.data());
    bool done = emulate(trace, image, io, rows);
#endif
    if (done)
      break;
    i++;
    if (i > 0) break;
  }
  fclose(pcFile);
}
