// Copyright 2022 Risc0, Inc.
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

#pragma once

#include "risc0/core/key.h"
#include "risc0/zkp/core/fp.h"
#include "risc0/zkvm/circuit/constants.h"

#include <map>
#include <set>
#include <vector>

namespace risc0 {

using Buffer = std::vector<uint8_t>;
using BufferU32 = std::vector<uint32_t>;

struct MemoryEvent {
  uint32_t addr;
  uint32_t cycle;
  bool isWrite;
  uint32_t data;
  bool operator<(const MemoryEvent& rhs) const {
    if (addr != rhs.addr) {
      return addr < rhs.addr;
    }
    return cycle < rhs.cycle;
  }
};

struct MemoryState {
  std::map<uint32_t, uint32_t> data;
  std::set<MemoryEvent> history;

  void dump(size_t logLevel);

  uint8_t loadByte(uint32_t addr);
  uint32_t load(uint32_t addr);
  uint32_t loadBE(uint32_t addr);
  void loadRegion(uint32_t addr, void* ptr, uint32_t len);

  void storeByte(uint32_t addr, uint8_t byte);
  void store(uint32_t addr, uint32_t value);
  void store(uint32_t addr, const void* ptr, uint32_t len);

  size_t strlen(uint32_t addr);
};

struct IoHandler {
  virtual void onInit(MemoryState& mem) {}
  virtual void onWrite(const Buffer& data) {}
  virtual void onCommit(const Buffer& data) {}
  virtual void onFault(const std::string& msg);
  virtual KeyStore& getKeyStore() = 0;
};

class MemoryHandler {
public:
  MemoryHandler();
  MemoryHandler(IoHandler* io);

  // Called before the load of the ELF.  Can write to memory, but any memory loaded from the
  // ELF will override.
  virtual void onInit(MemoryState& mem);

  // Called after loading an ELF, can write to any memory not already loaded.
  virtual void onLoaded(MemoryState& mem) {}

  // onRead is called when uninitalized memory is read, giving the host a chance to return with a
  // value.
  virtual uint32_t onRead(MemoryState& mem, uint32_t addr) { return 0; }

  // onWrite is called when a word is written to memory, giving the host a chance to be notified of
  // new data.
  virtual void onWrite(MemoryState& mem, uint32_t cycle, uint32_t addr, uint32_t value);

  // Called after the system is halted, gets final memory state & final output.
  virtual void onHalt(const MemoryState& mem, const std::array<uint32_t, 8>& output) {}

private:
  IoHandler* io;
};

struct StepContext {
  MemoryHandler* io;
  MemoryState mem;
  uint32_t curStep;
  uint32_t numSteps;
  Fp globals[kGlobalSize];

  Fp get(const Fp* buf, size_t offset, size_t back);
  void set(Fp* buf, size_t offset, Fp val);
  Fp getDigits(const Fp* buf, size_t bits, size_t offset, size_t back, size_t size);
  Fp setDigits(Fp* buf, size_t bits, size_t offset, size_t size, Fp val);
  Fp getMux(const Fp* buf, size_t offset, size_t back, size_t size);
  void setMux(Fp* buf, size_t offset, size_t size, Fp val);
  void memWrite(Fp cycle, Fp addr, Fp low, Fp high);
  std::array<Fp, 2> memRead(Fp cycle, Fp addr);
  std::array<Fp, 5> memCheck(); // Cycle, Addr, IsWrite, Low, High
  std::array<Fp, 4> divide(Fp numerLow, Fp numerHigh, Fp denomLow, Fp denomHigh);
  void requireDigits(Fp* buf, size_t bits, size_t offset, size_t size);
  void requireMux(Fp* buf, size_t offset, size_t size, const char* msg);
  void requireZero(Fp val, const char* msg);
};

void setupCode(Fp* code,
               size_t numSteps,
               uint32_t startAddr,
               const std::map<uint32_t, uint32_t>& image);

void dataStepExec(StepContext& ctx, const Fp* code, Fp* data);
void dataStepCheck(StepContext& ctx, const Fp* code, Fp* data);
void accumStep(StepContext& ctx, const Fp* code, const Fp* data, Fp* accum);

} // namespace risc0
