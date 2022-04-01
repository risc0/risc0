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

#include "risc0/zkvm/sdk/cpp/host/receipt.h"

#include "risc0/core/log.h"
#include "risc0/zkp/core/sha256_cpu.h"
#include "risc0/zkp/prove/prove.h"
#include "risc0/zkp/verify/verify.h"
#include "risc0/zkvm/prove/method_id.h"
#include "risc0/zkvm/prove/riscv.h"
#include "risc0/zkvm/verify/riscv.h"

#include <sstream>

namespace risc0 {

struct Receipt::Impl {
  Impl(const Buffer& buffer_) : buffer(buffer_), stream(buffer), reader(stream) {}

  Buffer buffer;
  CheckedStreamReader stream;
  ArchiveReader<CheckedStreamReader> reader;
};

Receipt::Receipt(const BufferU32& seal, const Buffer& journal)
    : seal(seal), impl(new Impl(journal)) {}

const Buffer& Receipt::getJournal() const {
  return impl->buffer;
}

ArchiveReader<CheckedStreamReader>& Receipt::getReader() const {
  return impl->reader;
}

void Receipt::verify(const std::string& filename) const {
  LOG(1, "Reading code id from " << filename + ".id");
  MethodID code = readMethodID(filename + ".id");
  std::unique_ptr<VerifyCircuit> circuit = getRiscVVerifyCircuit(code);
  risc0::verify(*circuit, seal.data(), seal.size());
  if (impl->buffer.size() != seal[8]) {
    std::stringstream ss;
    ss << "Receipt::verify> journal size (" << impl->buffer.size()
       << ") does not match receipt seal (" << seal[8] << ")";
    throw std::runtime_error(ss.str());
  }
  if (impl->buffer.size() > 32) {
    ShaDigest digest = shaHash(impl->buffer.data(), impl->buffer.size());
    if (memcmp(&digest, seal.data(), sizeof(ShaDigest)) != 0) {
      throw std::runtime_error("Receipt journal/seal root mismatch");
    }
  } else {
    if (memcmp(impl->buffer.data(), seal.data(), impl->buffer.size()) != 0) {
      throw std::runtime_error("Receipt journal/seal root mismatch");
    }
  }
}

struct Prover::Impl : public IoHandler {
  Impl(const std::string& elfPath)
      : elfPath(elfPath)
      , outputStream(outputBuffer)
      , commitStream(commitBuffer)
      , inputWriter(inputStream)
      , outputReader(outputStream)
      , commitReader(commitStream) {}

  virtual ~Impl() {}

  void onInit(MemoryState& mem) override {
    LOG(1, "Prover::onInit>");
    uint32_t addr = kMemInputStart;
    for (uint32_t word : inputStream.vec) {
      if (addr > kMemInputEnd) {
        throw std::runtime_error("Out of memory: inputs");
      }
      LOG(1, "  " << hex(addr) << ": " << hex(word));
      mem.store(addr, word);
      addr += sizeof(uint32_t);
    }
  }

  void onWrite(const Buffer& buf) override {
    LOG(1, "IoHandler::onWrite> " << buf.size());
    outputBuffer.insert(outputBuffer.end(), buf.begin(), buf.end());
  }

  void onCommit(const Buffer& buf) override {
    LOG(1, "IoHandler::onCommit> " << buf.size());
    commitBuffer.insert(commitBuffer.end(), buf.begin(), buf.end());
  }

  KeyStore& getKeyStore() override { return keyStore; }

  std::string elfPath;
  KeyStore keyStore;
  Buffer outputBuffer;
  Buffer commitBuffer;
  VectorStreamWriter inputStream;
  CheckedStreamReader outputStream;
  CheckedStreamReader commitStream;
  ArchiveWriter<VectorStreamWriter> inputWriter;
  ArchiveReader<CheckedStreamReader> outputReader;
  ArchiveReader<CheckedStreamReader> commitReader;
};

CheckedStreamReader::CheckedStreamReader(const Buffer& buffer) : buffer(buffer), cursor(0) {}

uint8_t CheckedStreamReader::read_byte() {
  if (cursor >= buffer.size()) {
    throw std::out_of_range("Read out of bounds");
  }
  return buffer[cursor++];
}

uint32_t CheckedStreamReader::read_word() {
  uint32_t b1 = read_byte();
  uint32_t b2 = read_byte();
  uint32_t b3 = read_byte();
  uint32_t b4 = read_byte();
  return b1 | b2 << 8 | b3 << 16 | b4 << 24;
}

uint64_t CheckedStreamReader::read_dword() {
  uint64_t low = read_word();
  uint64_t high = read_word();
  return low | high << 32;
}

void CheckedStreamReader::read_buffer(void* buf, size_t len) {
  uint32_t* dst = static_cast<uint32_t*>(buf);
  for (size_t i = 0; i < len; i++) {
    *dst++ = read_word();
  }
}

Prover::Prover(const std::string& elfPath) : impl(new Impl(elfPath)) {}

Prover::~Prover() = default;

KeyStore& Prover::getKeyStore() {
  return impl->getKeyStore();
}

void Prover::setKey(const std::string& name, const Key& key) {
  impl->getKeyStore()[name] = key;
}

const Buffer& Prover::getOutput() {
  return impl->outputBuffer;
}

const Buffer& Prover::getCommit() {
  return impl->commitBuffer;
}

ArchiveWriter<VectorStreamWriter>& Prover::getInputWriter() {
  return impl->inputWriter;
}

ArchiveReader<CheckedStreamReader>& Prover::getOutputReader() {
  return impl->outputReader;
}

ArchiveReader<CheckedStreamReader>& Prover::getCommitReader() {
  return impl->commitReader;
}

void Prover::writeInput(const void* ptr, size_t size) {
  LOG(1, "Prover::writeInput> size: " << size);
  const uint8_t* ptr_u8 = static_cast<const uint8_t*>(ptr);
  while (size >= sizeof(uint32_t)) {
    uint32_t word = 0;
    word |= *ptr_u8++;
    word |= *ptr_u8++ << 8;
    word |= *ptr_u8++ << 16;
    word |= *ptr_u8++ << 24;
    LOG(1, "  write_word: " << hex(word));
    impl->inputStream.write_word(word);
    size -= sizeof(uint32_t);
  }

  if (size) {
    LOG(1, "  tail: " << size);
    uint32_t word = 0;
    for (size_t i = 0; i < size; i++) {
      word |= *ptr_u8++ << (8 * i);
    }
    LOG(1, "  write_word: " << hex(word));
    impl->inputStream.write_word(word);
  }
}

Receipt Prover::run() {
  // Set the memory handlers to call back to the impl
  MemoryHandler handler(impl.get());
  // Make the circuit
  std::unique_ptr<ProveCircuit> circuit = getRiscVProveCircuit(impl->elfPath.c_str(), handler);
  BufferU32 seal = prove(*circuit);
  // Attach the full version of the output journal + construct receipt object
  Receipt receipt{seal, getCommit()};
  // Verify receipt to make sure it works
  receipt.verify(impl->elfPath);
  return receipt;
}

} // namespace risc0
