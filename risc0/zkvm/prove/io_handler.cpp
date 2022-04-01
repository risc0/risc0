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

#include <sstream>

#include "risc0/core/log.h"
#include "risc0/zkp/core/sha256.h"
#include "risc0/zkvm/platform/io.h"
#include "risc0/zkvm/platform/memory.h"
#include "risc0/zkvm/prove/step.h"

namespace risc0 {

static void processSHA(MemoryState& mem, const ShaDescriptor& desc) {
  uint16_t type = (desc.typeAndCount & 0xFFFF) >> 4;
  uint16_t count = desc.typeAndCount & 0xFFFF;
  LOG(1,
      "SHA256 type: " << type << ", count: " << count << ", idx: " << desc.idx
                      << ", source: " << hex(desc.source) << ", digest: " << hex(desc.digest));
  ShaDigest sha = impl::initState();
  uint32_t words[16];
  for (int i = 0; i < count; i++) {
    for (int j = 0; j < 16; j++) {
      uint32_t from = desc.source + i * 16 * 4 + j * 4;
      words[j] = mem.loadBE(from);
      LOG(1, "Input[" << hex(j, 2) << "]: " << hex(from) << " -> " << hex(words[j]));
    }
    LOG(1, "Compress");
    impl::compress(sha, words);
  }
  for (int i = 0; i < 8; i++) {
    LOG(1, "Output[" << hex(i, 1) << "]: " << hex(sha.words[i]));
    mem.store(desc.digest + i * 4, sha.words[i]);
  }
}

void IoHandler::onFault(const std::string& msg) {
  throw std::runtime_error(msg);
}

MemoryHandler::MemoryHandler() : io(nullptr) {}

MemoryHandler::MemoryHandler(IoHandler* io) : io(io) {}

void MemoryHandler::onInit(MemoryState& mem) {
  if (io) {
    io->onInit(mem);
  }
}

void MemoryHandler::onWrite(MemoryState& mem, uint32_t cycle, uint32_t addr, uint32_t value) {
  LOG(2, "MemoryHandler::onWrite> " << hex(addr) << ": " << hex(value));
  switch (addr) {
  case kGPIO_SHA: {
    LOG(1, "MemoryHandler::onWrite> GPIO_SHA");
    ShaDescriptor desc;
    mem.loadRegion(value, &desc, sizeof(desc));
    processSHA(mem, desc);
  } break;
  case kGPIO_Write: {
    LOG(1, "MemoryHandler::onWrite> GPIO_Write");
    IoDescriptor desc;
    mem.loadRegion(value, &desc, sizeof(desc));
    if (io) {
      std::vector<uint8_t> buf(desc.size);
      mem.loadRegion(desc.addr, buf.data(), desc.size);
      io->onWrite(buf);
    }
  } break;
  case kGPIO_Commit: {
    LOG(1, "MemoryHandler::onWrite> GPIO_Commit");
    IoDescriptor desc;
    mem.loadRegion(value, &desc, sizeof(desc));
    if (io) {
      std::vector<uint8_t> buf(desc.size);
      mem.loadRegion(desc.addr, buf.data(), desc.size);
      io->onCommit(buf);
    }
  } break;
  case kGPIO_Fault: {
    LOG(1, "MemoryHandler::onWrite> GPIO_Fault");
    FaultDescriptor desc;
    mem.loadRegion(value, &desc, sizeof(desc));
    if (io) {
      size_t len = mem.strlen(desc.addr);
      std::vector<char> buf(len);
      mem.loadRegion(desc.addr, buf.data(), len);
      std::string str(buf.data(), buf.size());
      io->onFault(str);
    }
  } break;
  case kGPIO_Log: {
    LOG(2, "MemoryHandler::onWrite> GPIO_Log");
    LogDescriptor desc;
    mem.loadRegion(value, &desc, sizeof(desc));
    size_t len = mem.strlen(desc.addr);
    std::vector<char> buf(len);
    mem.loadRegion(desc.addr, buf.data(), len);
    std::string str(buf.data(), buf.size());
    LOG(0, "R0VM[C" << cycle << "]> " << str);
  } break;
  case kGPIO_GetKey: {
    LOG(1, "MemoryHandler::onWrite> GPIO_GetKey");
    GetKeyDescriptor desc;
    mem.loadRegion(value, &desc, sizeof(desc));
    if (!io) {
      throw std::runtime_error("Get key called with no IO handler set");
    }
    size_t len = mem.strlen(desc.name);
    std::vector<char> buf(len);
    mem.loadRegion(desc.name, buf.data(), len);
    std::string str(buf.data(), buf.size());
    LOG(1, "  addr = " << hex(desc.addr));
    LOG(1, "  key = " << str);
    LOG(1, "  mode = " << desc.mode);
    KeyStore& store = io->getKeyStore();
    if (desc.mode == 0 && store.count(str)) {
      throw std::runtime_error("GetKey Mode = NEW and key exists: " + str);
    }
    if (desc.mode == 1 && !store.count(str)) {
      throw std::runtime_error("GetKey Mode = EXISTING and key does not exist: " + str);
    }
    const Key& key = store[str];
    mem.store(desc.addr, reinterpret_cast<const uint8_t*>(&key), sizeof(Key));
  } break;
  }
}

void MemoryState::dump(size_t logLevel) {
  LOG(logLevel, "MemoryState::dump> size: " << data.size());
  if (getLogLevel() >= logLevel) {
    for (auto pair : data) {
      LOG(logLevel, "  " << hex(pair.first * 4) << ": " << hex(pair.second));
    }
  }
}

size_t MemoryState::strlen(uint32_t addr) {
  size_t len = 0;
  while (loadByte(addr++)) {
    len++;
  }
  return len;
}

uint8_t MemoryState::loadByte(uint32_t addr) {
  // align to the nearest word
  uint32_t aligned = addr & ~(sizeof(uint32_t) - 1);
  size_t byte_offset = addr % sizeof(uint32_t);
  uint32_t word = load(aligned);
  return (word >> (byte_offset * 8)) & 0xff;
}

uint32_t MemoryState::load(uint32_t addr) {
  auto it = data.find(addr / 4);
  if (it == data.end()) {
    std::stringstream ss;
    ss << "addr out of range: " << hex(addr);
    throw std::out_of_range(ss.str());
  }
  return it->second;
}

void MemoryState::loadRegion(uint32_t addr, void* ptr, uint32_t len) {
  uint8_t* bytes = static_cast<uint8_t*>(ptr);
  for (size_t i = 0; i < len; i++) {
    bytes[i] = loadByte(addr++);
  }
}

uint32_t MemoryState::loadBE(uint32_t addr) {
  return loadByte(addr + 0) << 24 | //
         loadByte(addr + 1) << 16 | //
         loadByte(addr + 2) << 8 |  //
         loadByte(addr + 3);
}

void MemoryState::storeByte(uint32_t addr, uint8_t byte) {
  // align to the nearest word
  uint32_t aligned = addr & ~(sizeof(uint32_t) - 1);
  size_t byte_offset = addr % sizeof(uint32_t);
  uint32_t word = data[aligned / 4] & ~(0xff << (byte_offset * 8));
  word |= byte << (byte_offset * 8);
  store(aligned, word);
}

void MemoryState::store(uint32_t addr, const void* ptr, uint32_t len) {
  const uint8_t* bytes = static_cast<const uint8_t*>(ptr);
  for (size_t i = 0; i < len; i++) {
    storeByte(addr++, bytes[i]);
  }
}

void MemoryState::store(uint32_t addr, uint32_t value) {
  if (addr % 4 != 0) {
    throw std::runtime_error("Unaligned store");
  }
  uint32_t key = addr / 4;
  auto it = data.find(key);
  if (it != data.end()) {
    auto txn = history.lower_bound({key, 0, 0, 0});
    if (txn != history.end() && txn->addr == key && it->second != value) {
      // The guest has actually touched this memory, and we are not writing the same value
      throw std::runtime_error("Host cannot mutate existing memory.");
    }
    it->second = value;
  } else {
    data[key] = value;
  }
}

} // namespace risc0
